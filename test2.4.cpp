// test process address independence
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;

int main()
{
    char* buffer1 = static_cast<char *>(vm_map(nullptr, 0));
    char* buffer2 = static_cast<char *>(vm_map(nullptr, 0));
    char* buffer3 = static_cast<char *>(vm_map(nullptr, 0));
    char* buffer4 = static_cast<char *>(vm_map(nullptr, 0));
    //char* buffer5 = static_cast<char *>(vm_map(nullptr, 0));


    /* Allocate swap-backed page from the arena */

    /* Write the name of the file that will be mapped */
    strcpy(buffer1, "buffer1");
    strcpy(buffer2, "buffer2");
    strcpy(buffer3, "buffer3");
    strcpy(buffer4, "buffer4");
    //strcpy(buffer5, "buffer5");

    /* Map a page from the specified file */
    strcpy(buffer1, "buffer1 again");

    /* Print the first part of the paper */
    for (unsigned int i=0; i<10; i++) {
	    cout << buffer1[i];
    }
    strcpy(buffer2, "buffer2");
    for (unsigned int i=0; i<7; i++) {
	    cout << buffer2[i];
    }
    for (unsigned int i=0; i<7; i++) {
	    cout << buffer4[i];
    }
}