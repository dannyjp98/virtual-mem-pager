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
    auto *page1 = static_cast<char *>(vm_map(nullptr, 1));
    auto *page2 = static_cast<char *>(vm_map(nullptr, 4));
    auto *page3 = static_cast<char *>(vm_map(nullptr, 10));
    cout << "here" << endl;
    strcpy(page0, "daibiub"); // triggers faults for both page 0 and page 1
    strcpy(page1, "deibiub"); // triggers faults for both page 0 and page 1
    strcpy(page2, "dfibiub"); // triggers faults for both page 0 and page 1
    strcpy(page3, "dgibiub"); // triggers faults for both page 0 and page 1
    cout << "after strcpy" << endl;
}