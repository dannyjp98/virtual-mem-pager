// test case from lab

#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;
using std::endl;

int main()
{
    cout << "start of test" << endl;
    char* file1 = static_cast<char *>(vm_map("asdasdasd", 0));
    cout << "successfully mapped" << endl;

    auto *filename = static_cast<char *>(vm_map(nullptr, 0));
    char* file2 = static_cast<char *>(vm_map(filename, 0));
    strcpy(file2, "asdasdasd");
    cout << "finished test" << endl;

    char* bigname = static_cast<char *>(vm_map(nullptr, 0));
    memset(bigname, 'h', VM_PAGESIZE);
    char* bignamefile = static_cast<char *>(vm_map(bigname, 0));
    cout << bignamefile[0];
}