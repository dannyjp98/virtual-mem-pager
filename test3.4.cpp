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
    char* buffer = static_cast<char *>(vm_map(nullptr, 0));

    /* Write the name of the file that will be mapped */
    strcpy(buffer, "asasdadiwiejfijijefijijfiejfeiaoeifnoeifneoun");
    /* Print the first part of the paper */
    for (unsigned int i=0; i<30; i++) {
	    cout << buffer[i];
    }
}