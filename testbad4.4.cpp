// test case from lab

#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;
using std::endl;

int main()
{
    auto *page0 = static_cast<char *>(vm_map(nullptr, 0));
    cout << "here" << endl;
    char* filename = page0;
    // char* filename = page0 + VM_PAGESIZE - VM_PAGESIZE;
    cout << "before strcpy" << endl;    
    strcpy(filename, "luofsuboobubo.txt"); // triggers faults for both page 0 and page 1
    cout << "after strcpy" << endl;
    auto *file = static_cast<char *>(vm_map(filename, 0));

    for (unsigned int i=0; i<1930; i++) {
	    cout << file[i];
    }
}