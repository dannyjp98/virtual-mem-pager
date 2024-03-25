#include "vm_pager.h"
#include "vm_arena.h"
#include <unordered_map>
#include <vector>

#include <cassert>

/*
each process has its own 1 level page table (1D array)
when a diff process runs -> swap to its page table (with pid - hashmap? pid to page table array)
can map to physical mem and also disk

MMU looks in our page table. If read/write not granted, we handle fault ourselves.
1. VPN 1 maps to PPN ?? -> needs to fault to bring in to page table
2. incorrect r/w bits? check on EVERY load or store -> fault

PTE has physical page number, r, and w



Page Table: array of struct PTE{PPN, R, W}, index is VPN
Page Table Mapping: hashmap from PID to Page Table

*not responsible for entire virtual address space, ONLY arena x6000....

Every load and store, references MMU. MMU references PTBR
arena refers to whatever the user has allocated and can use.

copy-on-write:

usually swap space = physical mem
eager swap preservation

arena size = 0b1000000000000000000000000
page entry = 0b1000000000000000000000000

// STATE DIAGRAM

1. what states can page be in? no read + no write, read + no write, read + write
2. what info does each page track? read, write, resident, referenced?
3. what events transition states? read fault, write fault, ..

everytime we reference something thats currently unreferenced -> trigger a fault

recommendations:

*/

static pid_t current_pid = 0;


// process arena bookkeeping // 

struct vpn_data{
    //ppage (literal address)
    //read_enable
    //write_enable
    page_table_entry_t* pte;
    int state = 0;
    bool valid = false;
    bool dirty = false;
    bool resident = false;
    char* filename = nullptr;
    int block = 0;
};

//page table is 256 (arena size / page size)

std::unordered_map<pid_t, page_table_entry_t*> page_tables;
std::unordered_map<pid_t, vpn_data*> vpn_data_tables;

int pm_memory_pages = 0;
int vm_swap_blocks = 0;

std::vector<pid_t> swap_reservations; // pid -> swapfile block

// VPN PT bookkeeping //


// PPN bookkeeping //

struct PPN_data{
    bool valid = false;
    std::vector<vpn_data*> vpn_list;
    bool referenced = false;
    
    
};

std::vector<PPN_data> ppn_clock;
int clock_index = 0;


//can optimise with map if have speed concerns

// block permissions for swap files: block -> pid authority hashmap
// buf must be size of a page exactly
void populate_physmem(int block, char* buf){
    // assert(block < memory_pages);

    //zero out memory
    bzero(reinterpret_cast<void*>(reinterpret_cast<const uintptr_t>(vm_physmem) + (VM_PAGESIZE * block)), VM_PAGESIZE);

    //populate with buffer
    for(auto i = 0; i < VM_PAGESIZE; ++i){
        static_cast<char *>(vm_physmem)[i] = buf[i];
    }
}

void vm_init(unsigned int memory_pages, unsigned int swap_blocks){
    // make zero page as 1st block
    char buffer[VM_PAGESIZE];
    bzero(buffer, VM_PAGESIZE);
    populate_physmem(0, buffer);

    // configure mem pages and swap blocks
    pm_memory_pages = memory_pages;
    vm_swap_blocks = swap_blocks;
    
    swap_reservations.resize(swap_blocks, -1);
    
    ppn_clock.resize(memory_pages, {false, {}, false});
}


int vm_create(pid_t parent_pid, pid_t child_pid){
    // initialize new page table for pid
    page_table_entry_t* arr = new page_table_entry_t[256];
    vpn_data* arr2 = new vpn_data[256];

    page_tables[child_pid] = arr;
    vpn_data_tables[child_pid] = arr2;

    // clear
    for(int i = 0; i<256; i++){
        arr[i].ppage = 0;
        arr[i].read_enable = 0;
        arr[i].write_enable = 0;
        arr2[i].pte = &arr[i];
        arr2[i].dirty = 0;
        arr2[i].resident = 0;
        arr2[i].valid = 0;
        arr2[i].state = 0;
    }
}

void vm_switch(pid_t pid){
    // set current pid
    current_pid = pid;

    // switch PTBR to be correct PT
    page_table_base_register = page_tables[pid];
}

int translate_addr(const void* addr){
    const uintptr_t index = reinterpret_cast<const uintptr_t>(addr) - reinterpret_cast<const uintptr_t>(VM_ARENA_BASEADDR);
    return index / VM_PAGESIZE;
}

// gets free ppn or makes a slot if not available
int get_free_ppn(){
    // check for lowest empty ppn
    for(int i = 0; i < ppn_clock.size(); ++i){
        if(ppn_clock[i].valid == false){
            // claim ppn i
            return i;
        }
    }
    // clock algorithm for eviction
    while(ppn_clock[clock_index].referenced != false){
        auto cur = ppn_clock[clock_index];
        // clock changes reference - modify other vp
        ppn_clock[clock_index].referenced = false;
        for(auto vpn_d : ppn_clock[clock_index].vpn_list){
            vpn_d->state = 3;
            vpn_d->pte->read_enable = 0;
            vpn_d->pte->write_enable = 0;
        }
        clock_index = (clock_index + 1) % ppn_clock.size();
    }
    auto victim = ppn_clock[clock_index];
    // copy data back to disk
    for(auto vpn_d : victim.vpn_list){
        if(vpn_d->dirty){
            file_write(nullptr, vpn_d->block, reinterpret_cast<void*>(reinterpret_cast<const uintptr_t>(vm_physmem) + clock_index)); // two VPNs are written
            break;
        }
    }
    ppn_clock[clock_index].valid = false;
    return clock_index;
}

int vm_fault(const void* addr, bool write_flag){
    // When does vm fault get called?
    // 1. not appropriate access?
    // 2. addr not valid
    int vpn = translate_addr(addr);
    // initial state
    auto &vpn_d = vpn_data_tables[current_pid][vpn];
    

    if(vpn_data_tables[current_pid][vpn].filename == nullptr){
        if(vpn_d.state == 3){
            vpn_d.pte->read_enable = 1;
            vpn_d.pte->write_enable = 1;
        }
        else if(vpn_d.state = 1){
            if(write_flag){
                // allocate new PPN 
                int ppn = get_free_ppn();
                //add to clock

                vpn_data_tables[current_pid][vpn].state = 2;
                vpn_data_tables[current_pid][vpn].resident = 1;
                vpn_data_tables[current_pid][vpn].dirty = 1;
                page_tables[current_pid][vpn].write_enable = 1;
                page_tables[current_pid][vpn].read_enable = 1;
                page_tables[current_pid][vpn].ppage = ppn;

                ppn_clock[ppn].valid = true;
                ppn_clock[ppn].referenced = true;
                ppn_clock[ppn].vpn_list.push_back(&vpn_data_tables[current_pid][vpn]); //check this
            }
        }
        else if(vpn_d.state = 0){
            
        }
    }
    else{
        
    }
    
    ppn_clock[vpn_d.pte->ppage].referenced = true;
    
}

void vm_destroy(){
 //clear up memory for corresponding PID address space
    delete [] page_tables[current_pid];
    page_tables.erase(current_pid);

    delete [] vpn_data_tables[current_pid];
    vpn_data_tables.erase(current_pid);

    for(int i = 0; i<swap_reservations.size(); i++){
        if(swap_reservations[i] == current_pid){
            swap_reservations[i] = -1;
        }
    }
    
    //remove physical pages from memory: such as CLOCK

    //add fucntionlaioty for bpoth swap and file
}

// reserves spot in swap file
int reserve_swap(){
    for(int i = 0; i<swap_reservations.size(); i++){
        if(swap_reservations[i] == -1){
            swap_reservations[i] = current_pid;
            return i;
        }
    }
    // no block available
    return -1;
}

// reserves next vpn
void* reserve_next_vpn(int reserved_block){
    for(int i = 0; i < 256; ++i){
        if(vpn_data_tables[current_pid][i].valid == false){
            vpn_data_tables[current_pid][i].valid = true;
            vpn_data_tables[current_pid][i].state = 1;
            vpn_data_tables[current_pid][i].resident = true;
            vpn_data_tables[current_pid][i].block = reserved_block;

            page_tables[current_pid][i].ppage = 0;
            page_tables[current_pid][i].read_enable = true;
            return reinterpret_cast<void*>(reinterpret_cast<const uintptr_t>(VM_ARENA_BASEADDR) + (i * VM_PAGESIZE));
        }
    }
    return nullptr;
}

void* vm_map(const char* filename, unsigned int block){
    if(filename == nullptr){ // swap backed page
        // reserve spot in swap file
        int reserved_block = reserve_swap();
        if(reserved_block == -1) return nullptr;
        return reserve_next_vpn(reserved_block);
    } else {
        return nullptr;
    }

}

// new functions

// call evict when you
void evict(){
    // clock algorithm
}





//std::vector<pid_t> arena_reservations; // idx: arena block -> owning pid

// returns arena block free and reserve for pid
// int reserve_arena(pid_t pid){
//     for(int i = 0; i < arena_reservations.size(); ++i){
//         if(arena_reservations[i] == -1){
//             arena_reservations[i] = pid;
//             return i;
//         }
//     }
//     // no blocks available, so create a new one
//     arena_reservations.push_back(pid);
//     return arena_reservations.size()-1;
// }

// // frees up pid's arena (on destroy)
// void free_arena(pid_t pid){
//     for(int i = 0; i < arena_reservations.size(); ++i){
//         if(arena_reservations[i] == pid){
//             arena_reservations[i] == -1;
//         }
//     }
// }

// // returns the first virtual address in arena block
// void* translate_arena_block(int block){
//     return VM_ARENA_BASEADDR + (VM_ARENA_SIZE * block);
// }