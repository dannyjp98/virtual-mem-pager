// most basic test of swap backed and file backed
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;
using std::endl;


int main()
{
    for(int i = 0; i<150; i++){
        char* filename = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(filename, "data1.bin");
    }
    for(int i = 0; i<1000; i++){
        char* filename = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(filename, "data1.bin");
        char* file = static_cast<char *>(vm_map(filename, 0));
        cout << file[0];
    }
}