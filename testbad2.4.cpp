// test case from lab

#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;
using std::endl;

int main()
{
    for (unsigned int i=0; i<1930; i++) {
	    auto *page0 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(page0, "fboiaoibbo");
    }
}