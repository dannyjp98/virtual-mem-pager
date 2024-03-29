// most basic test of swap backed and file backed
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;
using std::endl;


int main()
{
    
    if(fork()){
        char* filename1 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(filename1, "data2.bin");
        char* file1 = static_cast<char *>(vm_map (filename1, 3));
        for(int i = 0; i<1000; i++) cout << file1[i];
        char* file2 = static_cast<char *>(vm_map (filename1, 3));
        vm_yield();
    }
    else{
        char* filename1 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(filename1, "data2.bin");
        char* file1 = static_cast<char *>(vm_map (filename1, 3));
        for(int i = 0; i<1000; i++) cout << file1[i];
        char* file2 = static_cast<char *>(vm_map (filename1, 3));

        vm_yield();

        //force clock algorithm
        char* swap1 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap1, "asdasda");
        char* swap2 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap2, "asdaddddsda");
        char* swap3 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap3, "asdaddsda");
        char* swap4 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap4, "asdaddddddsda");
    }
}
