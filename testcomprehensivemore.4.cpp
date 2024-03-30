// most basic test of swap backed and file backed
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;
using std::endl;


int main()
{
    
    if(fork()){
        char* swap1 = static_cast<char *>(vm_map(nullptr, 0));
        char* swap2 = static_cast<char *>(vm_map(nullptr, 0));
        char* swap3 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap1, "igyafeiug");
        strcpy(swap2, "data2.bin");
        strcpy(swap3, "drfw9");
        char* swap4 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap4, "datin");
        cout << swap2;
        strcpy(swap3, "xyz");
        cout << swap1;
        strcpy(swap1, "g9jf9i");
    }
    else{
        char* swap1 = static_cast<char *>(vm_map(nullptr, 0));
        char* swap2 = static_cast<char *>(vm_map(nullptr, 0));
        char* swap3 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap1, "cfcsg");
        strcpy(swap2, "datscdbin");
        strcpy(swap3, "cdsw9");
        char* swap11 = static_cast<char *>(vm_map(nullptr, 0));
        char* swap21 = static_cast<char *>(vm_map(nullptr, 0));
        char* swap31 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap11, "igeiug");
        strcpy(swap21, "dat");
        strcpy(swap31, "dw9");
        cout << swap1;
        cout << swap2;
        cout << swap3;
        char* swap111 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap111, "idwnn9dw9ng");
        strcpy(swap2, "idwnwdu9nnwdnu99unwdng");
        cout << swap3;
        strcpy(swap1, "idcdcfdcfdfcd");
        char* swap1111 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap1111, "idwdwdwg");
        cout << swap3;
        strcpy(swap2, "idwndwdedewededdeng");
        strcpy(swap11, "idwdoniein0nwedddeng");
    }
}
