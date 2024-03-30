// most basic test of swap backed and file backed
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;
using std::endl;


int main()
{
    for(int i = 0; i<1000; i++){
        char* swap100 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap100, "ba");
    }
}