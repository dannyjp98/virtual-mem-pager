// test case from lab

#include <iostream>
#include <cstring>
#include <cassert>
#include <unistd.h>
#include "vm_app.h"

using std::cout;
using std::endl;

int main()
{
    if(fork() != 0){
        auto *page0 = static_cast<char*>(vm_map(nullptr, 0));
        auto *page1 = static_cast<char*>(vm_map(nullptr, 0));
        auto *page2 = static_cast<char*>(vm_map(nullptr, 0));
    } else {
        auto *page0 = static_cast<char*>(vm_map(nullptr, 0));
        std::strcpy(page0, "Hello, world!");
    }
}