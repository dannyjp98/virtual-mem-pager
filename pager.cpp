#include "vm_pager.h"
#include "vm_arena.h"
#include <unordered_map>

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

page_table_entry_t PT[32];
std::unordered_map<int, page_table_entry_t*> pid_address;

// block permissions for swap files: block -> pid authority hashmap


void vm_init(unsigned int memory_pages, unsigned int swap_blocks){
    //page_table_base_register = first address space initialized

}


int vm_create(pid_t parent_pid, pid_t child_pid){

}

void vm_switch(pid_t pid){
    // page_table_base_register = pid_addresses[pid];
    // set current_pid = pid;
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