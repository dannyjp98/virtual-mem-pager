#include "vm_pager.h"
#include "vm_arena.h"
#include <string.h>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <deque>

#include <cassert>

using std::cout;
using std::endl;

// DATA STRUCTURES

int VM_PAGES;
static pid_t current_pid = 0;
int pm_memory_pages = 0;
int vm_swap_blocks = 0;

struct vpn_data{
    page_table_entry_t* pte = nullptr;
    int state = 0;
    bool valid = false;
    bool resident = false;
    std::string filename = "";
    bool is_file_backed = false;
    int block = 0;
};

struct ppn_data{
    bool valid = false;
    bool referenced = false;
    bool dirty = false;
    std::string filename = "";
    int block = 0;
    bool is_file_backed = false;
    vpn_data* swap_vpn = nullptr;
};

std::unordered_map<pid_t, page_table_entry_t*> page_tables; // page table for PTE
std::unordered_map<pid_t, vpn_data*> vpn_data_tables; // extra VPN data

std::vector<pid_t> swap_reservations; // holds swap reservations
std::unordered_map<std::string, std::unordered_map<int,std::vector<vpn_data*>>> file_reservations; // holds file reservations

std::vector<ppn_data> ppn_vec; // vector to abstract phys mem
std::deque<int> clock_q; // queue for clock

// HELPER FUNCTIONS

// remove PPN from clock
void removePPN(int ppn){
    bool found = false;
    for(int i = 0; i<clock_q.size(); i++){
        if(clock_q[i] == ppn){
            assert(!found);
            clock_q.erase(clock_q.begin() + i);
            found = true;
        }
    }
}

// convert virtual address to VPN
int vaddr_to_vpn(const void* addr){ // translate
    if(reinterpret_cast<const uintptr_t>(addr) < reinterpret_cast<const uintptr_t>(VM_ARENA_BASEADDR)) return -1;
    if(reinterpret_cast<const uintptr_t>(addr) >= (reinterpret_cast<const uintptr_t>(VM_ARENA_BASEADDR) + VM_ARENA_SIZE)) return -1;

    const uintptr_t index = reinterpret_cast<const uintptr_t>(addr) - reinterpret_cast<const uintptr_t>(VM_ARENA_BASEADDR);
    return index / VM_PAGESIZE;
}

// get virtual address offset
int get_addr_offset(const void* addr){
    const uintptr_t offset = reinterpret_cast<const uintptr_t>(addr) - reinterpret_cast<const uintptr_t>(VM_ARENA_BASEADDR);
    return offset % VM_PAGESIZE;
}

// read filename from vaddr, fault if necessary
std::pair<std::string, bool> read_filename(const char* vaddr){
    std::string output = "";
    int fn_vpn = vaddr_to_vpn(vaddr);
    if(fn_vpn == -1) return {"", false};
    int fn_offset = get_addr_offset(vaddr);

    if(page_table_base_register[fn_vpn].read_enable == 0){
        if(vm_fault(vaddr, false) == -1) return {"", false};
    }

    assert(page_table_base_register[fn_vpn].read_enable == 1);

    int fn_ppn = page_table_base_register[fn_vpn].ppage;
    const char* physmem = static_cast<const char*>(vm_physmem);
    while(*(physmem + (fn_ppn*VM_PAGESIZE) + fn_offset) != 0){
        output += *(physmem + (fn_ppn*VM_PAGESIZE + fn_offset));
        fn_offset++;

        if(fn_offset >= VM_PAGESIZE){           
            fn_vpn++;
            fn_offset = 0;
            auto new_addr = reinterpret_cast<const char*>(VM_ARENA_BASEADDR) + fn_vpn * VM_PAGESIZE;
            if(page_table_base_register[fn_vpn].read_enable == 0){
                if(vm_fault(new_addr, false) == -1) return {"", false};
            }
            assert(page_table_base_register[fn_vpn].read_enable == 1);
            fn_ppn = page_table_base_register[fn_vpn].ppage;
        }
    }
    return {output, true};
}

// copy model file-backed page to other references
void copy_to_refs(vpn_data* model){
    if(model->is_file_backed == false) return;
    auto &ref_list = file_reservations[model->filename][model->block];
    if(ref_list.empty()) return;

    for(auto &cur : ref_list){
        if(model == cur) continue;

        cur->resident = model->resident;
        cur->state = model->state;
        cur->valid = model->valid;
        cur->pte->read_enable = model->pte->read_enable;

        cur->pte->write_enable = model->pte->write_enable;
        cur->pte->ppage = model->pte->ppage;
    }
}

// clear clock at ppn
void clear_clock(int ppn){
    ppn_vec[ppn].valid = false;
    ppn_vec[ppn].dirty = false;
    ppn_vec[ppn].referenced = false;
    ppn_vec[ppn].swap_vpn = nullptr;
    ppn_vec[ppn].filename = "";
    ppn_vec[ppn].is_file_backed = false;
    ppn_vec[ppn].block = 0;
}

// convert PPN to pointer in physical memory
void* ppn_to_ptr(int ppn){
    return reinterpret_cast<void*>(static_cast<char*>(vm_physmem) + (ppn * VM_PAGESIZE));
}

// convert VPN to pointer in virtual memory
void* vpn_to_ptr(int vpn){
    return reinterpret_cast<void*>(reinterpret_cast<const uintptr_t>(VM_ARENA_BASEADDR) + (vpn * VM_PAGESIZE));
}


// make a reservation in the swap file
int reserve_swap(){
    for(int i = 0; i<swap_reservations.size(); i++){
        if(swap_reservations[i] == -1){
            swap_reservations[i] = current_pid;
            return i;
        }
    }
    return -1;
}

// get next vpn to reserve
int reserve_next_vpn(int reserved_block){
    for(int i = 0; i < VM_PAGES; ++i){
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

// CORE FUNCTIONS
void vm_init(unsigned int memory_pages, unsigned int swap_blocks){
    memset(vm_physmem, 0, VM_PAGESIZE);
    VM_PAGES = VM_ARENA_SIZE/VM_PAGESIZE;
    pm_memory_pages = memory_pages;
    vm_swap_blocks = swap_blocks;
    swap_reservations.resize(swap_blocks, -1);
    ppn_vec.resize(memory_pages);
}


int vm_create(pid_t parent_pid, pid_t child_pid){
    page_table_entry_t* arr = new page_table_entry_t[VM_PAGES];
    vpn_data* arr2 = new vpn_data[VM_PAGES];
    page_tables[child_pid] = arr;
    vpn_data_tables[child_pid] = arr2;
    for(int i = 0; i<VM_PAGES; i++){
        arr[i].ppage = 0;
        arr[i].read_enable = 0;
        arr[i].write_enable = 0;
        arr2[i].pte = &arr[i];
    }
    return 0;
}

void vm_switch(pid_t pid){
    current_pid = pid;
    page_table_base_register = page_tables[pid];
}

// find ppn to evict and clear that ppn
int evict(){
    while(!clock_q.empty()){
        int cur_ppn = clock_q.front();
        if(ppn_vec[clock_q.front()].referenced == false) break;
        else{
            ppn_vec[clock_q.front()].referenced = false;

            clock_q.pop_front();
            clock_q.push_back(cur_ppn);

            if(ppn_vec[cur_ppn].is_file_backed == false){ // swap backed
                auto vpn_d = ppn_vec[cur_ppn].swap_vpn;
                if(vpn_d->state == 5){
                    vpn_d->state = 6;
                }
                if(vpn_d->state == 2){
                    vpn_d->state = 3;
                }
                vpn_d->pte->read_enable = 0;
                vpn_d->pte->write_enable = 0;
            }   
            else{ // file backed
                auto &ref_list = file_reservations[ppn_vec[cur_ppn].filename][ppn_vec[cur_ppn].block];
                
                for(auto vpn_d : ref_list){
                    if(vpn_d->state == 5){
                        vpn_d->state = 6;
                    }
                    if(vpn_d->state == 2){
                        vpn_d->state = 3;
                    }
                    vpn_d->pte->read_enable = 0;
                    vpn_d->pte->write_enable = 0;
                }
            }
        }
    }
    
    int ppn_to_evict = clock_q.front();
    clock_q.pop_front();

    auto &victim = ppn_vec[ppn_to_evict];

    if(victim.is_file_backed == false){ // swap backed
        auto cur_vpn = victim.swap_vpn;
        if(ppn_vec[cur_vpn->pte->ppage].dirty){
            file_write(nullptr, cur_vpn->block, ppn_to_ptr(ppn_to_evict));
        }
        cur_vpn->resident = 0;
        cur_vpn->pte->read_enable = 0;
        cur_vpn->pte->write_enable = 0;
        cur_vpn->state = 4;
    } else { // file backed
        if(ppn_vec[ppn_to_evict].dirty){
            file_write(ppn_vec[ppn_to_evict].filename.c_str(), ppn_vec[ppn_to_evict].block, ppn_to_ptr(ppn_to_evict));
        }
        auto &ref_list = file_reservations[ppn_vec[ppn_to_evict].filename][ppn_vec[ppn_to_evict].block];
        for(auto& cur_vpn : ref_list){
            cur_vpn->resident = 0;
            cur_vpn->pte->read_enable = 0;
            cur_vpn->pte->write_enable = 0;
            cur_vpn->state = 4;
        }
    }
    clear_clock(ppn_to_evict);
    return ppn_to_evict;
}

// find a ppn to reserve and return reserved ppn
int reserve_ppn(int vpn, bool write_flag=true){
    int ppn = -1;
    // if vacancy in phys mem, take it
    for(int i = 1; i < ppn_vec.size(); ++i){
        if(ppn_vec[i].valid == false){
            ppn = i;
            break;
        }
    }
    // otherwise evict
    if(ppn == -1){
        ppn = evict();
    }

    // set necessary info to reserve physical page
    clock_q.push_back(ppn);

    auto &model_page = vpn_data_tables[current_pid][vpn];

    model_page.resident = 1;
    if(write_flag){
        ppn_vec[ppn].dirty = 1;
        model_page.pte->write_enable = 1;
        model_page.state = 2;
    }
    else{
        model_page.state = 5;
    }
    
    model_page.pte->read_enable = 1;
    model_page.pte->ppage = ppn;

    ppn_vec[ppn].valid = true;
    ppn_vec[ppn].referenced = true;

    if(model_page.is_file_backed == false){ // swap backed
        ppn_vec[ppn].is_file_backed = false;
        ppn_vec[ppn].filename = "";
        ppn_vec[ppn].block = model_page.block;
        ppn_vec[ppn].swap_vpn = &model_page;
    }
    else{ // file backed
        ppn_vec[ppn].is_file_backed = true;
        copy_to_refs(&vpn_data_tables[current_pid][vpn]);
        ppn_vec[ppn].filename = model_page.filename;
        ppn_vec[ppn].block = model_page.block;
        ppn_vec[ppn].swap_vpn = nullptr;
    }

    return ppn;
}

int vm_fault(const void* addr, bool write_flag){
    int vpn = vaddr_to_vpn(addr);
    if(vpn == -1) return -1;
    auto &vpn_d = vpn_data_tables[current_pid][vpn];
    if(vpn_d.state == 6){
        if(write_flag){
            vpn_d.pte->read_enable = 1;
            vpn_d.pte->write_enable = 1;
            ppn_vec[vpn_d.pte->ppage].dirty = 1;
            ppn_vec[vpn_d.pte->ppage].referenced = true;
            vpn_d.state = 2;
        }
        else{
            vpn_d.pte->read_enable = 1;
            ppn_vec[vpn_d.pte->ppage].referenced = true;
            vpn_d.state = 5;
        }
        copy_to_refs(&vpn_d);
    }
    else if(vpn_d.state == 5){
        vpn_d.pte->write_enable = 1;
        ppn_vec[vpn_d.pte->ppage].dirty = 1;
        vpn_d.state = 2;
        copy_to_refs(&vpn_d);
    }
    else if(vpn_d.state == 4){
        int ppn = reserve_ppn(vpn, write_flag);
        
        auto &cur = vpn_data_tables[current_pid][vpn];
        int status = 0;
        if(cur.is_file_backed == false){
            status = file_read(nullptr, cur.block, ppn_to_ptr(ppn));
        }
        else{
            status = file_read(cur.filename.c_str(), cur.block, ppn_to_ptr(ppn));
        }
        if(status == -1){
            ppn_vec[vpn_d.pte->ppage].valid = false;
            ppn_vec[vpn_d.pte->ppage].referenced = true;
            cur.valid = false;
            cur.pte->write_enable = 0;
            cur.pte->read_enable = 0;
            return -1;
        }
    }
    else if(vpn_d.state == 3){
        vpn_d.pte->read_enable = 1;
        vpn_d.pte->write_enable = 1;
        ppn_vec[vpn_d.pte->ppage].referenced = true;
        vpn_d.state = 2;
        copy_to_refs(&vpn_d);
    }
    else if(vpn_d.state == 1){
        if(write_flag){
            int ppn = reserve_ppn(vpn, write_flag);
            memset(ppn_to_ptr(ppn), 0, VM_PAGESIZE);
        }
    }
    else if(vpn_d.state == 0){
        return -1;
    }
    
    ppn_vec[vpn_d.pte->ppage].referenced = true;

    return 0;
}

void vm_destroy(){
    for(int i = 0; i<VM_PAGES; i++){
        auto &cur = vpn_data_tables[current_pid][i];
        if(!cur.valid){
            continue;
        }
        if(cur.is_file_backed == false){ // swap backed
            if(swap_reservations[cur.block]){
                swap_reservations[cur.block] = -1;
                if(cur.resident){
                    clear_clock(cur.pte->ppage);
                    removePPN(cur.pte->ppage);
                }
            }
        }
        else { // file backed
            for(int i = 0; i < file_reservations[cur.filename][cur.block].size(); ++i){
                if(&cur == file_reservations[cur.filename][cur.block][i]){
                    file_reservations[cur.filename][cur.block].erase(file_reservations[cur.filename][cur.block].begin() + i);
                    --i;
                }
            }
        }

    }

    // clean up dynamically allocated memory
    delete [] page_tables[current_pid];
    page_tables.erase(current_pid);

    delete [] vpn_data_tables[current_pid];
    vpn_data_tables.erase(current_pid);
}

void* vm_map(const char* filename, unsigned int block){
    if(filename == nullptr){ // swap backed
        int reserved_block = reserve_swap();
        if(reserved_block == -1) return nullptr;
        int vpn = reserve_next_vpn(reserved_block);
        if(vpn == -1) return nullptr;
        vpn_data_tables[current_pid][vpn].is_file_backed = false;
        vpn_data_tables[current_pid][vpn].filename = "";
        return vpn_to_ptr(vpn);
    } else { // file backed
        auto filenamepair = read_filename(filename);
        if(filenamepair.second == false){
            return nullptr;
        }

        std::string filen = filenamepair.first;
        int vpn = reserve_next_vpn(block);
        if(vpn == -1) return nullptr;
        
        vpn_data_tables[current_pid][vpn].is_file_backed = true;
        vpn_data_tables[current_pid][vpn].filename = filen;
        auto &fr = file_reservations[filen][block];
        if(fr.size() != 0){
            page_tables[current_pid][vpn].ppage = fr[0]->pte->ppage;
            page_tables[current_pid][vpn].read_enable = fr[0]->pte->read_enable;
            page_tables[current_pid][vpn].write_enable = fr[0]->pte->write_enable;

            vpn_data_tables[current_pid][vpn].resident = fr[0]->resident;
            vpn_data_tables[current_pid][vpn].state = fr[0]->state;
            vpn_data_tables[current_pid][vpn].valid = fr[0]->valid;       
        }
        else{ // no other live references
            bool toCopy = false;
            // check if stale reference in physical memory already
            for(int i = 0; i < ppn_vec.size(); i++){
                auto &cur = ppn_vec[i];
                if(!cur.is_file_backed || !cur.valid) continue;
                if(cur.filename == filen && cur.block == block) // have match so copy
                {
                    toCopy = true;
                    page_tables[current_pid][vpn].ppage = i;

                    // set state
                    if(cur.dirty == 1 && cur.referenced == 0){
                        vpn_data_tables[current_pid][vpn].state = 3;
                    }
                    else if(cur.dirty == 1 && cur.referenced == 1){
                        vpn_data_tables[current_pid][vpn].state = 2;
                    }
                    else if(cur.dirty == 0 && cur.referenced == 0){
                        vpn_data_tables[current_pid][vpn].state = 6;
                    }
                    else if(cur.dirty == 0 && cur.referenced == 1){
                        vpn_data_tables[current_pid][vpn].state = 5;
                    }
                    
                    // deconstruct ppn_data to get all bits
                    if(cur.referenced == false){
                        page_tables[current_pid][vpn].read_enable = 0;
                        page_tables[current_pid][vpn].write_enable = 0;
                    }
                    else if(cur.dirty == true){
                        page_tables[current_pid][vpn].read_enable = 1;
                        page_tables[current_pid][vpn].write_enable = 1;
                    }
                    else{
                        page_tables[current_pid][vpn].read_enable = 1;
                        page_tables[current_pid][vpn].write_enable = 0;
                    } 

                    vpn_data_tables[current_pid][vpn].resident = 1;
                    vpn_data_tables[current_pid][vpn].valid = 1;
                    break;
                }
            }
            if(!toCopy){ // if no existing file backed page exists, make new one
                vpn_data_tables[current_pid][vpn].resident = 0;
                vpn_data_tables[current_pid][vpn].state = 4;
                vpn_data_tables[current_pid][vpn].valid = 1;
                page_tables[current_pid][vpn].read_enable = 0;
                page_tables[current_pid][vpn].write_enable = 0;
            }
        }
        
        // add file reservation
        fr.push_back(&vpn_data_tables[current_pid][vpn]);
        return vpn_to_ptr(vpn);
    }
}
