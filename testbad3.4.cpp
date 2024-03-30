// test case from lab

#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;
using std::endl;

int main()
{

    char* filename = "data1.bin";
    try {
        auto *file = static_cast<char *>(vm_map(filename, 0));
        for (unsigned int i=0; i<1930; i++) {
            cout << file[i];
        }
    } catch (...) {
        cout << "bugged out" << endl;
    }

    char* filename1 = static_cast<char *>(vm_map(nullptr, 0));
    strcpy(filename1, "data3.bin");

    auto *file1 = static_cast<char *>(vm_map(filename1, 0));
    strcpy(file1, "data3.bin");

    auto *file2 = static_cast<char *>(vm_map(file1, 0));
    for (unsigned int i=0; i<1930; i++) {
            cout << file2[i];
    }
}