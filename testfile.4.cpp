// most basic test of swap backed and file backed
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;
using std::endl;


int main()
{
    /* Allocate swap-backed page from the arena */
    char* filename = static_cast<char *>(vm_map(nullptr, 0));

    /* Write the name of the file that will be mapped */
    strcpy(filename, "data1.bin");
    char* p1 = static_cast<char *>(vm_map (filename, 1));
    filename[4] = '2';
    char* p2 = static_cast<char *>(vm_map (filename, 1));
    /* Map a page from the specified file */
    /* Print the first part of the paper */
    for (unsigned int i=0; i<1930; i++) {
	    cout << p1[i];
    }
    
    for (unsigned int i=0; i<1930; i++) {
	    cout << p2[i];
    }
}