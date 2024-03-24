#include "vm_pager.h"
#include "vm_arena.h"
#include <unordered_map>

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


// STATE DIAGRAM

1. what states can page be in? no read + no write, read + no write, read + write
2. what info does each page track? read, write, resident, referenced?
3. what events transition states? read fault, write fault, ..

everytime we reference something thats currently unreferenced -> trigger a fault

recommendations:

*/

static pid_t current_pid = -1;

page_table_entry_t PT[32];

//page table is 256 (arena size / page size)
std::unordered_map<pid_t, page_table_entry_t*> page_tables;

int memory_pages = 0;
int swap_blocks = 0;

// block permissions for swap files: block -> pid authority hashmap
// buf must be size of a page exactly
void populate_physmem(int block, char* buf){
    assert(block < memory_pages);

    //zero out memory
    bzero(static_cast<char *>(vm_physmem)[VM_PAGESIZE * block], VM_PAGESIZE);

    //populate with buffer
    for(auto i = 0; i < VM_PAGESIZE; ++i){
        static_cast<char *>(vm_physmem)[i] = buf[i];
    }
}

void vm_init(unsigned int memory_pages, unsigned int swap_blocks){
    //make zero page
    populate_physmem(0, '\0');
    

}


int vm_create(pid_t parent_pid, pid_t child_pid){
    // initialize new page table for pid
    page_table_entry_t* arr = new page_table_entry_t[256];
    page_tables[child_pid] = arr;
}

void vm_switch(pid_t pid){
    // set current pid
    current_pid = pid;

    // switch PTBR to be correct PT
    page_table_base_register = page_tables[pid];

}

int vm_fault(const void* addr, bool write_flag){
    // When does vm fault get called?
    // 1. not appropriate access?
    // 2. addr not valid
}

void vm_destroy(){
 //clear up memory for corresponding PID address space
}


void* vm_map(const char* filename, unsigned int block){
    if(filename == nullptr){ // swap backed page

    } else {

    }
}

// new functions

// call evict when you
void evict(){
    // clock algorithm
}