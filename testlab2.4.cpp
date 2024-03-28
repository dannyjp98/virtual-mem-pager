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
    auto *filename = static_cast<char*>(vm_map(nullptr, 0));
    std::strcpy(filename, "lampson83.txt");
    if(fork()){
        auto *fb_page = static_cast<char*>(vm_map(filename, 0));
        fb_page[0] = 'B';
        vm_yield();
    } else {
        auto *fb_page = static_cast<char *>(vm_map(filename, 0));
        assert(fb_page[0] == 'B');
        fb_page[0] = 'H';
    }
}