#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;
using std::endl;

int main()
{
    cout << "reached here" << endl;
    /* Allocate swap-backed page from the arena */
    char* buffer1 = static_cast<char *>(vm_map(nullptr, 0));
    char* buffer2 = static_cast<char *>(vm_map(nullptr, 0));
    char* buffer3 = static_cast<char *>(vm_map(nullptr, 0));
    //char* buffer4 = static_cast<char *>(vm_map(nullptr, 0));


    cout << "reading buffer 1" << endl;
    for (unsigned int i=0; i<30; i++) {
	    cout << buffer1[i];
    }
    cout << endl;

    cout << "reading buffer 2" << endl;
    for (unsigned int i=0; i<30; i++) {
	    cout << buffer2[i];
    }
    cout << endl;
    /* Write the name of the file that will be mapped */
    strcpy(buffer1, "buffer1asasdadiwiejfijijefijijfiejfeiaoeifnoeifneoun");
    strcpy(buffer3, "buffer3aseeeeeeeasdadiwiejfijijefijijfiejfeiaoeifnoeifneoun");

    /* Print the first part of the paper */
    for (unsigned int i=0; i<30; i++) {
	    cout << buffer1[i];
    }
    for (unsigned int i=0; i<30; i++) {
	    cout << buffer2[i];
    }
     for (unsigned int i=0; i<30; i++) {
	    cout << buffer3[i];
    }
}