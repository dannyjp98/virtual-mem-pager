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
        char* swap1 = static_cast<char *>(vm_map(nullptr, 0));
        char* swap2 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap1, "data3.bin");
        strcpy(swap2, "data2.bin");

        char* file1 = static_cast<char *>(vm_map (swap1, 3));
        cout << file1[0] << endl; //move into physmemory
        strcpy(file1, "asdfasdfasd"); //fault for writing
        cout << swap1[0] << endl; //testing moving referenced to 1;
        
        char* rootfile1 = static_cast<char *>(vm_map (swap1, 3));
        char* sharedfile1 = static_cast<char *>(vm_map (swap1, 3));
        cout << rootfile1[0] << endl; // move root file into memory
        cout << sharedfile1[0] << endl; //move into physmemory
        char* sharedfile2 = static_cast<char *>(vm_map (swap1, 3));
        strcpy(rootfile1, "asdfasdfasd"); //make root file dirty
        cout << sharedfile2[0] << endl; //move into physmemory
        char* sharedfile3 = static_cast<char *>(vm_map (swap1, 3));
        cout << sharedfile3[0] << endl; //move into physmemory

        // force an eviction

        char* swap3 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap3, "dsd.bin");
        char* swap4 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap4, "wewe.bin");
        char* swap5 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap5, "data3.fgee");

        char* rootfile1e = static_cast<char *>(vm_map (swap1, 3));
        char* sharedfile1e = static_cast<char *>(vm_map (swap1, 3));
        cout << rootfile1e[0] << endl; // move root file into memory
        cout << sharedfile1e[0] << endl; //move into physmemory
        char* sharedfile2e = static_cast<char *>(vm_map (swap1, 3));
        strcpy(rootfile1e, "asdfasdfasd"); //make root file dirty
        cout << sharedfile2e[0] << endl; //move into physmemory
        strcpy(swap1, "data2.bin");
        char* sharedfile3e = static_cast<char *>(vm_map (swap1, 3));
        cout << sharedfile3e[0] << endl; //move into physmemory
        vm_yield();
        vm_yield();
    }
    else{
        char* swap1 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap1, "data3.bin");
        char* swap2e1= static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap2e1, "data3.bin");
        vm_yield();
        
        char* rootfile1 = static_cast<char *>(vm_map (swap1, 3));
        char* sharedfile1 = static_cast<char *>(vm_map (swap1, 3));
        cout << rootfile1[0] << endl; // move root file into memory
        cout << sharedfile1[0] << endl; //move into physmemory
        char* sharedfile2 = static_cast<char *>(vm_map (swap1, 3));
        strcpy(rootfile1, "asdfasdfasd"); //make root file dirty
        cout << sharedfile2[0] << endl; //move into physmemory
        char* sharedfile3 = static_cast<char *>(vm_map (swap1, 3));
        cout << sharedfile3[0] << endl; //move into physmemory

        vm_yield();

        char* rootfile1 = static_cast<char *>(vm_map (swap1, 3));
        char* sharedfile1 = static_cast<char *>(vm_map (swap1, 3));
        cout << rootfile1[0] << endl; // move root file into memory
        cout << sharedfile1[0] << endl; //move into physmemory
        char* sharedfile2 = static_cast<char *>(vm_map (swap1, 3));
        strcpy(rootfile1, "asdfasdfasd"); //make root file dirty
        cout << sharedfile2[0] << endl; //move into physmemory
        char* sharedfile3 = static_cast<char *>(vm_map (swap1, 3));
        cout << sharedfile3[0] << endl; //move into physmemory

        char* swap3e = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap3e, "dsd.bin");
        char* swap4e = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap4e, "dsggd.bin");
        char* swap5e = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap5e, "dddddsd.bin");
    }
}
