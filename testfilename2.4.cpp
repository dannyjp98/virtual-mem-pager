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
    char* file1 = static_cast<char *>(vm_map("data1.bin", 1));
    cout << "successfully mapped" << endl;

    auto *filename1 = static_cast<char *>(vm_map(nullptr, 0));
    auto *filename2 = static_cast<char *>(vm_map(nullptr, 0));
    auto *filename3 = static_cast<char *>(vm_map(nullptr, 0));

    strcpy(filename1, "data1.bin");
    strcpy(filename2, "data1.bin");
    strcpy(filename3, "data1.bin");

    char* file2 = static_cast<char *>(vm_map(filename1, 1));
    char* file3 = static_cast<char *>(vm_map(filename2, 1));

    strcpy(file2, "asdasdasd");
    strcpy(file3, "dssdwe");
    cout << file2[0];
    cout << file3[0];
    
    char* file4 = static_cast<char *>(vm_map(filename3, 1));
    cout << file4[0];
    
    cout << "finished main test" << endl;


    cout << file1[1];
    strcpy(file1, "asddssw");

    cout << "should segfault before this" << endl;
}