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
        // for(int i = 0; i < 253; ++i){
        //     char* swap = static_cast<char *>(vm_map(nullptr, 0));
        // }

        char* filename1 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(filename1, "data2.bin");
        char* file1 = static_cast<char *>(vm_map (filename1, 2));

        cout << "finished file1 map" << endl;

        char* file3 = static_cast<char *>(vm_map (filename1, 3));
        cout << "finished file3 map" << endl;

        char* file4 = static_cast<char *>(vm_map (filename1, 2));
        cout << "finished file4 map" << endl;

        char* file5 = static_cast<char *>(vm_map (filename1, 0));
        cout << "finished file5 map" << endl;



        char* filename2 = static_cast<char *>(vm_map(nullptr, 0));
        cout << "finished filename2 map" << endl;

        strcpy(filename2, "data2.bin");
        cout << "finished filename2 strcpy" << endl;

        char* file2 = static_cast<char *>(vm_map (filename2, 2));
        cout << "finished file2 map" << endl;

        cout << file1 << endl;
        cout << "finished printing file1" << endl;
        cout << file2 << endl;
         cout << "finished printing file2" << endl;
        cout << file3 << endl;
         cout << "finished printing file3" << endl;
        cout << file4 << endl;
         cout << "finished printing file4" << endl;
        cout << file5 << endl;
         cout << "finished printing file5" << endl;
        cout << file1 << endl;
         cout << "finished printing file1 again" << endl;
        
        cout << "finished printing all parent" << endl;

        vm_yield();
    }
    else{
        char* filename1 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(filename1, "data2.bin");
        char* file1 = static_cast<char *>(vm_map(filename1, 3));

        cout << file1 << endl;

        vm_yield();
        // child destroyed
        cout << file1 << endl;
        strcpy(file1, "finished destroying previous process");
        cout << file1 << endl;

        char* filename2 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(filename2, "data2.bin");
        char* file2 = static_cast<char *>(vm_map(filename2, 2));
        cout << file2 << endl;
        strcpy(file2, "writing to file 2");
        for(int i = 0; i < 20; ++i){
            char* swap = static_cast<char *>(vm_map(nullptr, 0));
        }
    }
}