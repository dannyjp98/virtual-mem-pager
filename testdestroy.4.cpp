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
        for(int i = 0; i < 200; ++i){
            char* swap = static_cast<char *>(vm_map(nullptr, 0));
        }

        char* filename1 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(filename1, "data2.bin");
        //faulting here
        cout << "got here before file map" << endl;
        char* file1 = static_cast<char *>(vm_map (filename1, 0));

        cout << "finished file1 map" << endl;

        char* file3 = static_cast<char *>(vm_map (filename1, 3));
        cout << "finished file3 map" << endl;

        char* file4 = static_cast<char *>(vm_map (filename1, 2));
        cout << "finished file4 map" << endl;

        char* file5 = static_cast<char *>(vm_map (filename1, 0));
        cout << "finished file5 map" << endl;



        char* filename2 = static_cast<char *>(vm_map(nullptr, 0));
        cout << "finished filename2 map" << endl;

        cout << "here" << endl;
        strcpy(filename2, "data2.bin");
        cout << "done" << endl;
        cout << "finished filename2 strcpy" << endl;

        char* file2 = static_cast<char *>(vm_map (filename2, 2));
        cout << "finished file2 map" << endl;

        for(int i = 0; i < 10; ++i) cout << file1[i];
        cout << "finished printing file1" << endl;
        for(int i = 0; i < 10; ++i) cout << file2[i];
         cout << "finished printing file2" << endl;
        for(int i = 0; i < 10; ++i) cout << file3[i];
         cout << "finished printing file3" << endl;
        for(int i = 0; i < 10; ++i) cout << file4[i];
        for(int i = VM_PAGESIZE-500; i < 10; ++i) cout << file4[i];

         cout << "finished printing file4" << endl;
        for(int i = 0; i < 10; ++i) cout << file5[i];
         cout << "finished printing file5" << endl;
        for(int i = 0; i < 10; ++i) cout << file1[i];
         cout << "finished printing file1 again" << endl;
        
        cout << "finished printing all parent" << endl;

        vm_yield();
    }
    else{
        char* filename1 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(filename1, "data2.bin");
        char* file1 = static_cast<char *>(vm_map(filename1, 3));

        for(int i = 0; i < 10; ++i) cout << file1[i];

        vm_yield();
        // child destroyed
        for(int i = 0; i < 10; ++i) cout << file1[i];
        strcpy(file1, "finished destroying previous process");
        for(int i = 0; i < 10; ++i) cout << file1[i];

        char* filename2 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(filename2, "data2.bin");
        char* file2 = static_cast<char *>(vm_map(filename2, 2));
        for(int i = 0; i < 10; ++i) cout << file2[i];
        strcpy(file2, "writing to file 2");
        for(int i = 0; i < 200; ++i){
            char* swap = static_cast<char *>(vm_map(nullptr, 0));
        }
    }
}