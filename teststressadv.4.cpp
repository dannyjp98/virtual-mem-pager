// most basic test of swap backed and file backed
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;
using std::endl;


int main()
{
    char* swap1 = static_cast<char *>(vm_map(nullptr, 0));
    char* swap2 = static_cast<char *>(vm_map(nullptr, 0));
    char* swap3 = static_cast<char *>(vm_map(nullptr, 0));
    char* swap4 = static_cast<char *>(vm_map(nullptr, 0));
    strcpy(swap1, "data1.bin");
    strcpy(swap2, "data2.bin");
    fork();
    strcpy(swap3, "data3.bin");
    strcpy(swap4, "data4.bin");

    char* file1 = static_cast<char *>(vm_map (swap1, 1));;
    char* file2 = static_cast<char *>(vm_map (swap1, 1));;
    char* file3 = static_cast<char *>(vm_map (swap2, 2));;
    char* file4 = static_cast<char *>(vm_map (swap2, 3));;
    char* file5 = static_cast<char *>(vm_map (swap3, 1));;
    char* file6 = static_cast<char *>(vm_map (swap3, 2));;
    char* file7 = static_cast<char *>(vm_map (swap4, 2));;
    char* file8 = static_cast<char *>(vm_map (swap4, 2));;

    for(int i = 0; i < 200; ++i){
        if(i%3==0){
            strcpy(swap1, "asdasda");
            cout << swap3[0];
            strcpy(swap1, "asdasqwpij");
            strcpy(swap3, "dddddxdasd");
            cout << file3[0];
            cout << file5[0];
            cout << file2[0];
            strcpy(file4, "dddee");
            cout << swap3[0];
        }
        if(i%2==0){
            strcpy(file3, "asdasqwpij");
            cout << file2[0];
            cout << file3[0];
            strcpy(file1, "fjfjf");

            cout << swap2[0];
            if(file4) cout << file4[0];
        }
        if(i%4==0){
            strcpy(swap2, "qcwdqcw");
            cout << swap2;
            cout << swap3;
            vm_yield();
            strcpy(file6, "uh2ohoi");
            cout << swap1;
            strcpy(file8, "fjfjf");
        }
        if(i%5==0){
            strcpy(file2, "jpirjipi");
            cout << file2[0];
            cout << file6[0];
            cout << swap2;
            strcpy(swap2, "ergrfdqw");
            cout << swap2;
        }
        if(i%7==0){
            strcpy(file6, "vnnvnnv");
            cout << file3[0];
            strcpy(swap2, "pihfqoqw");
            cout << swap1;
            cout << file2[0];
            cout << file7[0];
            fork();
            cout << file8[0];
            cout << file1[0];
            strcpy(file1, "uh2ohoi");
        }
        if(i%11==0){
            cout << swap1[0];
            cout << swap2[0];
            cout << file1[0];
            cout << file2[0];
            cout << file4[0];
            cout << file5[0];
        }
    }
}