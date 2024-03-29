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

    // test read empty swap
    cout << swap1[0];
    cout << swap2[0];
    cout << swap3[0];
    strcpy(swap4, "data4.bin");
    cout << swap4[0];
    cout << swap1[0];
    strcpy(swap1, "data1.bin");
    strcpy(swap2, "data2.bin");
    strcpy(swap3, "data3.bin");
    cout << endl << "starting loop" << endl;

    for(int i = 0; i < 20; ++i){
        char* file1 = static_cast<char *>(vm_map (swap1, 1));
        char* file2p1 = static_cast<char *>(vm_map (swap2, 3));
        char* file2p2 = static_cast<char *>(vm_map (swap2, 4));

        char* file3 = static_cast<char *>(vm_map (swap3, 2));
        char* file4 = static_cast<char *>(vm_map (swap4, 4));
        char* file1_copy = static_cast<char *>(vm_map (swap1, 1));
        char* file4_copy = static_cast<char *>(vm_map (swap4, 4));
        char* file4_copy2 = static_cast<char *>(vm_map (swap4, 4));

        char* filename = static_cast<char *>(vm_map (swap4, 4));

        cout << "FILE 3" << file3 << "END OF LINE" << endl;
        cout << swap3[0];
        cout << swap1[0];
        strcpy(file1, "baijfbuifbuiabo");
        strcpy(file3, "dasdwe");

        cout << file1[0];
        cout << file1[VM_PAGESIZE - 1];
        cout << file2p1[3];
        char* endof2 = file2p1 + VM_PAGESIZE-4;
        strcpy(endof2, "abunchofnewdatathatslongerthan4");
        cout << endof2 << endl;
        cout << file2p2;
        cout << file3[5];
        cout << file4[2];
        strcpy(file3, file4);
        file4[5] = '5';
        char* file4_copy3 = static_cast<char *>(vm_map (swap4, 4));
        cout << file4_copy3[5];
        cout << file4_copy2[0];
        cout << file4_copy;
        cout << file1_copy;
    }
}