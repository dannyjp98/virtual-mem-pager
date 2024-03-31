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

    char* file1 = static_cast<char *>(vm_map (swap1, 1));
    char* file2p1 = static_cast<char *>(vm_map (swap2, 3));
    char* file2p2 = static_cast<char *>(vm_map (swap2, 4));

    cout << file2p2[0];

    for(int i = 0; i < VM_PAGESIZE; ++i){
        cout << file2p2[i];
    }

    char* file3 = static_cast<char *>(vm_map (swap3, 2));
    char* file4 = static_cast<char *>(vm_map (swap4, 4));
    char* file1_copy = static_cast<char *>(vm_map (swap1, 1));
    for(int i = 0; i < VM_PAGESIZE; ++i){
        cout << file1_copy[i];
    }
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
    cout << swap1[0];
    cout << swap2[0];
    strcpy(file2p2, swap1);
    strcpy(file4, file4_copy3);
    strcpy(file1,file1);

    char* swap35 = static_cast<char *>(vm_map(nullptr, 0));
    char* swap36 = static_cast<char *>(vm_map(nullptr, 0));
    strcpy(swap35,"data1.bin");
    strcpy(swap36,"data1.bin");

    strcpy(swap1, "lampson83.txt");


    char* file35 = static_cast<char *>(vm_map (swap35, 1));
    char* file36 = static_cast<char *>(vm_map (swap36, 1));
    char* file37 = static_cast<char *>(vm_map (swap1, 4));
    strcpy(file37, "lampson83.txt");
    char* file38 = static_cast<char *>(vm_map (file37, 1));

    cout << file38[0];
    strcpy(file36, "eeeeeeeee");
    cout << file35[0];
    cout << swap1[0];
    char* file39 = static_cast<char *>(vm_map (file37, 1));
    cout << file39[0];
    cout << swap2[1];
    cout << file35[0];
    cout << file38[0];
    cout << swap3[1];
    cout << swap4[0];
    cout << swap35[0];
    cout << swap36[1];
    cout << file38[0];
}