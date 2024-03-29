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
        char* swap3 = static_cast<char *>(vm_map(nullptr, 0));
        cout << swap1;
        strcpy(swap1, "igyafeiug");
        cout << swap1;
        strcpy(swap2, "data2.bin");
        char* file2 = static_cast<char *>(vm_map (swap2, 3));
        char* file3 = static_cast<char *>(vm_map (swap2, 4));
        for(int i = 0; i<1000; i++) cout << file2[i];
        vm_yield();
        for(int i = 0; i<1000; i++) cout << file2[i];
    }
    else{
        char* swap1 = static_cast<char *>(vm_map(nullptr, 0));
        char* swap2 = static_cast<char *>(vm_map(nullptr, 0));
        cout << swap2;
        strcpy(swap2, "data2.bin");
        cout << swap2;
        char* file2 = static_cast<char *>(vm_map (swap2, 3));
        for(int i = 0; i<1000; i++) cout << file2[i];
        char* file3 = static_cast<char *>(vm_map (swap2, 4));
        for(int i = 0; i<1000; i++) cout << file3[i];
        strcpy(file3, "hiadbuofaobobifovufeouv");
        vm_yield();
    }
}