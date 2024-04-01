// most basic test of swap backed and file backed
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;
using std::endl;


int main()
{
    char* swap1 = static_cast<char *>(vm_map(nullptr, 0));
    strcpy(swap1, "data2.bin");

    char* swap2 = static_cast<char *>(vm_map(nullptr, 0));
    strcpy(swap2, "data1.bin");

    char* file1 = static_cast<char *>(vm_map (swap1, 0));
    char* file2 = static_cast<char *>(vm_map (swap2, 0));
    cout << swap1;

    if(fork()){
        cout << "starting parent thread" << endl;
        cout << swap1;
        vm_yield();
        cout << swap1;
        strcpy(swap1, "data3.bin");
        cout << swap1;
        file1 = static_cast<char *>(vm_map (swap1, 1));
        cout << file1[0];
        vm_yield();
        char* junk1 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(junk1, "asdasda");
        char* junk2 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(junk2, "asdasda");
        char* junk3 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(junk3, "asdasda");
        vm_yield();
        file2 = static_cast<char *>(vm_map (swap2, 1));
        cout << file2[0];
        strcpy(file2, "asdasda");
        vm_yield();


    }
    else{
        cout << "starting child thread" << endl;
        cout << swap1;
        vm_yield();
        cout << swap1;
        strcpy(swap1, "data4.bin");
        cout << swap1;
        file1 = static_cast<char *>(vm_map (swap1, 1));
        cout << file1[0];
        vm_yield();
        char* junk1 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(junk1, "asdasda");
        char* junk2 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(junk2, "asdasda");
        vm_yield();
        char* junk3 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(junk3, "asdasda");
        file2 = static_cast<char *>(vm_map (swap2, 1));
        cout << file2[0];
        vm_yield();
        strcpy(file2, "asdasda");

    }
}