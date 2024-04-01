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
        fork();        
        char* swap4 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap4, "datin");
        cout << swap2;
        strcpy(swap3, "xyz");
        cout << swap1;
        strcpy(swap1, "g9jf9i");

        fork();
        char* swap10 = static_cast<char *>(vm_map(nullptr, 0));
        char* swap20 = static_cast<char *>(vm_map(nullptr, 0));
        char* swap30 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap10, "igyafeiug");
        strcpy(swap20, "data2.bin");
        strcpy(swap30, "drfw9");
        fork();
        char* swap40 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap40, "datin");
        cout << swap20;
        strcpy(swap30, "xyz");
        cout << swap10;
        strcpy(swap10, "g9jf9i");

        fork();

        char* wap1 = static_cast<char *>(vm_map(nullptr, 0));
        char* wap2 = static_cast<char *>(vm_map(nullptr, 0));
        char* wap3 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(wap1, "cfcsg");
        strcpy(wap2, "datscdbin");
        strcpy(wap3, "cdsw9");
        char* wap11 = static_cast<char *>(vm_map(nullptr, 0));
        char* wap21 = static_cast<char *>(vm_map(nullptr, 0));
        char* wap31 = static_cast<char *>(vm_map(nullptr, 0));
        fork();
        strcpy(wap11, "igeiug");
        strcpy(wap21, "dat");
        strcpy(wap31, "dw9");
        cout << wap1;
        cout << wap2;
        cout << wap3;
        char* wap111 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(wap111, "idwnn9dw9ng");
        strcpy(wap2, "idwnwdu9nnwdnu99unwdng");
        cout << wap3;
        fork();
        strcpy(wap1, "idcdcfdcfdfcd");
        char* wap1111 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(wap1111, "idwdwdwg");
        cout << wap3;
        strcpy(wap2, "idwndwdedewededdeng");
        strcpy(wap11, "idwdoniein0nwedddeng");
        fork();

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

        fork();

        char* swap10 = static_cast<char *>(vm_map(nullptr, 0));
        char* swap20 = static_cast<char *>(vm_map(nullptr, 0));
        char* swap30 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap10, "cfcsg");
        strcpy(swap20, "datscdbin");
        strcpy(swap30, "cdsw9");
        char* swap110 = static_cast<char *>(vm_map(nullptr, 0));
        char* swap210 = static_cast<char *>(vm_map(nullptr, 0));
        char* swap310 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap110, "igeiug");
        strcpy(swap210, "dat");
        strcpy(swap310, "dw9");
        cout << swap10;
        cout << swap20;
        cout << swap30;
        char* swap1110 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap1110, "idwnn9dw9ng");
        strcpy(swap20, "idwnwdu9nnwdnu99unwdng");
        cout << swap30;
        strcpy(swap10, "idcdcfdcfdfcd");
        char* swap11110 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap11110, "idwdwdwg");
        cout << swap30;
        strcpy(swap20, "idwndwdedewededdeng");
        strcpy(swap110, "idwdoniein0nwedddeng");

        fork();

        char* wap1 = static_cast<char *>(vm_map(nullptr, 0));
        char* wap2 = static_cast<char *>(vm_map(nullptr, 0));
        char* wap3 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(wap1, "igyafeiug");
        strcpy(wap2, "data2.bin");
        strcpy(wap3, "drfw9");
        char* wap4 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(wap4, "datin");
        cout << wap2;
        strcpy(wap3, "xyz");
        cout << wap1;
        strcpy(wap1, "g9jf9i");
        
        fork();

    }
}
