// test case from lab

#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;
using std::endl;

int main()
{
    if(fork()){
        strcpy(reinterpret_cast<char*>(VM_ARENA_BASEADDR) + VM_PAGESIZE + 2, "souhfofsuohf");
    }
    else{
        strcpy(reinterpret_cast<char*>(VM_ARENA_BASEADDR) - 5, "souhfofsuohf");
    }
}