#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;
using std::endl;

int main()
{
    char* filename = static_cast<char *>(vm_map(nullptr, 0));

    /* Write the name of the file that will be mapped */
    strcpy(filename, "data4.bin");

    cout << "Testing basic filebacked eviction" << endl;
    /* Allocate swap-backed page from the arena */
    char* buffer1 = static_cast<char *>(vm_map(filename, 0));
    char* buffer2 = static_cast<char *>(vm_map(filename, 1));
    char* buffer06 = static_cast<char *>(vm_map(filename, 0));
    char* buffer3 = static_cast<char *>(vm_map(filename, 2));
    char* buffer05 = static_cast<char *>(vm_map(filename, 0));
    char* buffer4 = static_cast<char *>(vm_map(filename, 3));

    cout << "filename: " << filename << endl;
    
    cout << "buffer 1: ";
    for (unsigned int i=0; i<30; i++) {
	    cout << buffer1[i];
    }
    cout << endl;

    cout << "buffer 2: ";
    for (unsigned int i=0; i<30; i++) {
	    cout << buffer2[i];
    }
    cout << endl;

    cout << "buffer 06: ";
    for (unsigned int i=0; i<30; i++) {
	    cout << buffer06[i];
    }
    cout << endl;

    cout << "buffer 3: ";
     for (unsigned int i=0; i<30; i++) {
	    cout << buffer3[i];
    }
    cout << endl;

    cout << "buffer 05: ";
    for (unsigned int i=0; i<30; i++) {
	    cout << buffer05[i];
    }
    cout << endl;

    cout << "buffer 4: ";
    for (unsigned int i=0; i<30; i++) {
	    cout << buffer4[i];
    }
    cout << endl;

    cout << "filename: ";
    cout << filename << endl;
}