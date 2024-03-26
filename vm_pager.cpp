#include "vm_pager.h"
#include "vm_arena.h"
#include <unordered_map>
#include <vector>
#include <iostream>

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

#define VM_PAGES 256
static pid_t current_pid = 0;


// process arena bookkeeping // 

struct vpn_data{
    //ppage (literal address)
    //read_enable
    //write_enable
    page_table_entry_t* pte;
    int state = 0;
    bool valid = false;
    // bool dirty = false;
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
std::unordered_map<char*, std::unordered_map<int,std::vector<vpn_data*>>> file_reservations;

// std::vector<std::vector<pid_t>> file_reservations; // pid -> swapfile block

// VPN PT bookkeeping //


// PPN bookkeeping //

struct PPN_data{
    bool valid = false;
    std::vector<vpn_data*> vpn_list;
    bool referenced = false;
    bool dirty = false;
};

std::vector<PPN_data> ppn_clock;
int clock_index = 0;


//can optimise with map if have speed concerns

// block permissions for swap files: block -> pid authority hashmap
// buf must be size of a page exactly
// void populate_physmem(int block, char* buf){
//     // assert(block < memory_pages);

//     //zero out memory
//     bzero(reinterpret_cast<void*>(reinterpret_cast<const uintptr_t>(vm_physmem) + (VM_PAGESIZE * block)), VM_PAGESIZE);

//     //populate with buffer
//     for(auto i = 0; i < VM_PAGESIZE; ++i){
//         static_cast<char *>(vm_physmem)[i] = buf[i];
//     }
// }

// HELPER FUNCTIONS 

void* ppn_to_ptr(int ppn){
    return reinterpret_cast<void*>(reinterpret_cast<const uintptr_t>(vm_physmem) + (ppn * VM_PAGESIZE));
}

void vm_init(unsigned int memory_pages, unsigned int swap_blocks){
    // make zero page as 1st block
    //char buffer[VM_PAGESIZE];
    //bzero(buffer, VM_PAGESIZE);
    memset(vm_physmem, 0, VM_PAGESIZE);

    //populate_physmem(0, buffer);

    // configure mem pages and swap blocks
    pm_memory_pages = memory_pages;
    vm_swap_blocks = swap_blocks;
    
    swap_reservations.resize(swap_blocks, -1);
    
    ppn_clock.resize(memory_pages, {false, {}, false});
    std::cout << "INITIALIZED PAGER" << std::endl;
}


int vm_create(pid_t parent_pid, pid_t child_pid){
    // initialize new page table for pid
    page_table_entry_t* arr = new page_table_entry_t[VM_PAGES];
    vpn_data* arr2 = new vpn_data[VM_PAGES];

    page_tables[child_pid] = arr;
    vpn_data_tables[child_pid] = arr2;

    // clear
    for(int i = 0; i<256; i++){
        arr[i].ppage = 0;
        arr[i].read_enable = 0;
        arr[i].write_enable = 0;
        arr2[i].pte = &arr[i];
        //arr[i].dirty = 0;
        arr2[i].resident = 0;
        arr2[i].valid = 0;
        arr2[i].state = 0;
    }
    return 0;
    //check if we only return 0 for 4 credit
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
int reserve_ppn(int vpn, bool read_only=false){
    int ppn = -1;
    
    //-------------GET + EVICT---------//
    
    // check for lowest empty ppn
    for(int i = 1; i < ppn_clock.size(); ++i){
        if(ppn_clock[i].valid == false){
            // claim ppn i
            ppn = i;
        }
    }
    if(ppn == -1){ // evict
        // clock algorithm for eviction
        while(ppn_clock[clock_index].referenced != false){
            if(clock_index == 0){
                clock_index = 1;
                continue;
            } 
            auto cur = ppn_clock[clock_index];
            // clock changes reference - modify other vp
            ppn_clock[clock_index].referenced = false;
            for(auto vpn_d : ppn_clock[clock_index].vpn_list){
                if(vpn_d->state == 5){
                    vpn_d->state = 6;
                    //ppn_clock[vpn_d->pte->ppage].dirty = false;
                    //vpn_d->dirty = false;
                }
                if(vpn_d->state == 2){
                    vpn_d->state = 3;
                    //ppn_clock[vpn_d->pte->ppage].dirty = true;
                    //vpn_d->dirty = true;
                }
                vpn_d->pte->read_enable = 0;
                vpn_d->pte->write_enable = 0;
            }
            clock_index = (clock_index + 1) % ppn_clock.size();
        }
        auto victim = ppn_clock[clock_index];
        // copy data back to disk
        for(auto cur_vpn : victim.vpn_list){
            // if(cur_vpn->state == 6){
            //     break;
            // }
            if(ppn_clock[cur_vpn->pte->ppage].dirty){
                file_write(nullptr, cur_vpn->block, reinterpret_cast<void*>(reinterpret_cast<const uintptr_t>(vm_physmem) + clock_index)); // two VPNs are written
            }
            cur_vpn->resident = 0;
            ppn_clock[cur_vpn->pte->ppage].dirty = false;
            //cur_vpn->dirty = 0;
            cur_vpn->pte->read_enable = 0;
            cur_vpn->pte->write_enable = 0;
            cur_vpn->state = 4;
        }
        ppn_clock[clock_index].valid = false;
        
        ppn = clock_index;
    }

    //-------------SET---------//

    vpn_data_tables[current_pid][vpn].resident = 1;
    if(!read_only){
        ppn_clock[clock_index].dirty = 1;
        page_tables[current_pid][vpn].write_enable = 1;
        vpn_data_tables[current_pid][vpn].state = 2;
    }
    else{
        vpn_data_tables[current_pid][vpn].state = 5;
    }
    
    page_tables[current_pid][vpn].read_enable = 1;
    page_tables[current_pid][vpn].ppage = ppn;

    ppn_clock[ppn].valid = true;
    ppn_clock[ppn].referenced = true;
    ppn_clock[ppn].vpn_list.push_back(&vpn_data_tables[current_pid][vpn]);
    return ppn;
}

int vm_fault(const void* addr, bool write_flag){
    // When does vm fault get called?
    // 1. not appropriate access?
    // 2. addr not valid
    int vpn = translate_addr(addr);
    // initial state
    auto &vpn_d = vpn_data_tables[current_pid][vpn];
    
    if(vpn_d.state == 6){
        if(write_flag){
            vpn_d.pte->read_enable = 1;
            vpn_d.pte->write_enable = 1;
            ppn_clock[vpn_d.pte->ppage].dirty = 1;
            ppn_clock[vpn_d.pte->ppage].referenced = true;
            vpn_d.state = 2;
        }
        else{
            vpn_d.pte->read_enable = 1;
            ppn_clock[vpn_d.pte->ppage].referenced = true;
            vpn_d.state = 5;
        }
    }
    if(vpn_d.state == 5){
        if(write_flag){
            vpn_d.pte->write_enable = 1;
            ppn_clock[vpn_d.pte->ppage].dirty = 1;
            vpn_d.state = 2;
        }
    }
    if(vpn_d.state == 4){
        if(write_flag){
            int ppn = reserve_ppn(vpn, false);
            auto &cur = vpn_data_tables[current_pid][vpn];
            file_read(cur.filename, cur.block, ppn_to_ptr(ppn));
        }
        else{
            // go to state 5
            reserve_ppn(vpn, true);
        }
    }
    if(vpn_d.state == 3){
        vpn_d.pte->read_enable = 1;
        vpn_d.pte->write_enable = 1;
        ppn_clock[vpn_d.pte->ppage].referenced = true;
        vpn_d.state = 2;
    }
    if(vpn_d.state == 1){
        if(write_flag){
            // allocate new PPN 
            reserve_ppn(vpn, false);
            //add to clock

            // vpn_data_tables[current_pid][vpn].state = 2;
            // vpn_data_tables[current_pid][vpn].resident = 1;
            // vpn_data_tables[current_pid][vpn].dirty = 1;
            // page_tables[current_pid][vpn].write_enable = 1;
            // page_tables[current_pid][vpn].read_enable = 1;
            // page_tables[current_pid][vpn].ppage = ppn;

            // ppn_clock[ppn].valid = true;
            // ppn_clock[ppn].referenced = true;
            // ppn_clock[ppn].vpn_list.push_back(&vpn_data_tables[current_pid][vpn]); //check this
        }
    }
    if(vpn_d.state == 0){
        return -1;
    }
    
    ppn_clock[vpn_d.pte->ppage].referenced = true;

    return 0;
    
}

void vm_destroy(){
 //clear up memory for corresponding PID address space

    // remove from file reservations

    for(int i = 0; i<VM_PAGES; i++){
        auto &cur = vpn_data_tables[current_pid][i];
        if(!cur.valid){
            continue;
        }
        if(cur.filename==nullptr){
            if(swap_reservations[cur.block]){
                swap_reservations[i] = -1;
                if(cur.resident){
                    ppn_clock[cur.pte->ppage].valid = false;
                }
            }
        }
        else {
            auto &vec = file_reservations[cur.filename][cur.block];
            for(int i = 0; i < vec.size(); ++i){
                if(&cur == vec[i]){
                    if(vec.size() == 1){
                        if(cur.resident){
                            ppn_clock[cur.pte->ppage].valid = false;
                        }
                    }
                    vec.erase(vec.begin() + i);
                    --i;
                }
            }
        }

    }

    // for(int i = 0; i<swap_reservations.size(); i++){
    //     if(swap_reservations[i] == current_pid){
    //         swap_reservations[i] = -1;
    //     }
    // }
    //remove physical pages from memory: such as CLOCK
    
    delete [] page_tables[current_pid];
    page_tables.erase(current_pid);

    delete [] vpn_data_tables[current_pid];
    vpn_data_tables.erase(current_pid);

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

void* vpn_to_ptr(int vpn){
    return reinterpret_cast<void*>(reinterpret_cast<const uintptr_t>(VM_ARENA_BASEADDR) + (vpn * VM_PAGESIZE));
}

// reserves next vpn
int reserve_next_vpn(int reserved_block){
    for(int i = 0; i < 256; ++i){
        if(vpn_data_tables[current_pid][i].valid == false){
            vpn_data_tables[current_pid][i].valid = true;
            vpn_data_tables[current_pid][i].state = 1;
            vpn_data_tables[current_pid][i].resident = true;
            vpn_data_tables[current_pid][i].block = reserved_block;

            page_tables[current_pid][i].ppage = 0;
            page_tables[current_pid][i].read_enable = true;
            return i;
        }
    }
    return -1;
}

void* vm_map(const char* filename, unsigned int block){
    if(filename == nullptr){ // swap backed page
        // reserve spot in swap file
        int reserved_block = reserve_swap();
        if(reserved_block == -1) return nullptr;
        int vpn = reserve_next_vpn(reserved_block);
        if(vpn == -1) return nullptr;
        return vpn_to_ptr(vpn);
    } else {
        int vpn = reserve_next_vpn(block);
        if(vpn == -1) return nullptr;
        
        strcpy(vpn_data_tables[current_pid][vpn].filename,filename);
        auto fr = file_reservations[vpn_data_tables[current_pid][vpn].filename][block];
        if(fr.size() != 0){
            if(fr[0]->resident == true){
                page_tables[current_pid][vpn].ppage = fr[0]->pte->ppage;
                vpn_data_tables[current_pid][vpn].state = fr[0]->state;
            }
        }
        fr.push_back(&vpn_data_tables[current_pid][vpn]);
        return vpn_to_ptr(vpn);
    }

}