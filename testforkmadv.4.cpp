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
        cout << swap1;
        strcpy(swap1, "igyafeiug");
        cout << swap1;
                fork();
        strcpy(swap2, "data2.bin");
        char* file2 = static_cast<char *>(vm_map (swap2, 3));
        char* file3 = static_cast<char *>(vm_map (swap2, 4));
        for(int i = 0; i<1000; i++){
            cout << "FILE 2" << file2[i] << "END OF LINE";
        }
        cout << endl;
        fork();
        vm_yield();
        fork();
        for(int i = 0; i<1000; i++){
            cout << "FILE 3" << file3[i] << "END OF LINE";
        }
        cout << endl;
        vm_yield();
        for(int i = 0; i<1000; i++){
            cout << "FILE 3" << file3[i] << "END OF LINE";
        }
        cout << endl;
        strcpy(file3, "yogsfdodhj");
        fork();
        vm_yield();
        strcpy(file3, "nodohoda");
        char* file6 = static_cast<char *>(vm_map (swap2, 2));
        strcpy(file6, "bjaobih");
        strcpy(swap2, "ihpsihpfdpih");
    }
    else{
        if(fork()){
            char* swap1 = static_cast<char *>(vm_map(nullptr, 0));
            char* swap2 = static_cast<char *>(vm_map(nullptr, 0));
            cout << swap2;
            strcpy(swap2, "data2.bin");
            cout << swap2;
            char* file2 = static_cast<char *>(vm_map (swap2, 3));
            fork();
            
            for(int i = 0; i<1000; i++) cout << file2[i];

            cout << endl;
            char* file3 = static_cast<char *>(vm_map (swap2, 4));
            
            for(int i = 0; i<1000; i++) cout << file3[i];

            cout << endl;
                    fork();
            strcpy(file3, "hiadbuofaobobifovufeouv");
            vm_yield();   
            char* swap5 = static_cast<char *>(vm_map(nullptr, 0));
            char* swap6 = static_cast<char *>(vm_map(nullptr, 0));
            char* swap7 = static_cast<char *>(vm_map(nullptr, 0));
            char* swap8 = static_cast<char *>(vm_map(nullptr, 0)); 
            strcpy(swap5, "ha");
            strcpy(swap6, "ha");
            strcpy(swap7, "ha");
            strcpy(swap8, "ha");
            cout << "Swap8" << swap8 << "END OF LINE" << endl;
            cout << "Swap5" << swap8 << "END OF LINE" << endl;
            vm_yield();
            strcpy(swap5, "ga");
            strcpy(swap6, "ba");
                    fork();
            strcpy(swap7, "ba");
            strcpy(swap8, "ba");
            vm_yield();
            char* file6 = static_cast<char *>(vm_map (swap2, 2));
            
            for(int i = 0; i<1000; i++) cout << file6[i];

            cout << endl;
            
            for(int i = 0; i<1000; i++) cout << file3[i];

            cout << endl;
            for(int i = 0; i<1000; i++) cout << file2[i];
                    fork();

            cout << endl;
            cout << "Swap8" << swap8 << "END OF LINE" << endl;
            cout << "Swap5" << swap5 << "END OF LINE" << endl;
        }
        else{
            char* swap1 = static_cast<char *>(vm_map(nullptr, 0));
            char* swap2 = static_cast<char *>(vm_map(nullptr, 0));
            cout << swap2;
            strcpy(swap2, "data2.bin");
            cout << swap2;
            char* file2 = static_cast<char *>(vm_map (swap2, 3));
            for(int i = 0; i<1000; i++) cout << file2[i];
                    fork();

            cout << endl;
            char* file3 = static_cast<char *>(vm_map (swap2, 4));
            for(int i = 0; i<1000; i++) cout << file3[i];

            cout << endl;
            strcpy(file3, "hiadbuofaobobifovufeouv");
            vm_yield();   
            char* swap5 = static_cast<char *>(vm_map(nullptr, 0));
            char* swap6 = static_cast<char *>(vm_map(nullptr, 0));
            char* swap7 = static_cast<char *>(vm_map(nullptr, 0));
                    fork();
            char* swap8 = static_cast<char *>(vm_map(nullptr, 0)); 
                    fork();
            strcpy(swap5, "ha");
            strcpy(swap6, "ha");
            strcpy(swap7, "ha");
            strcpy(swap8, "ha");
            cout << "Swap8" << swap8 << "END OF LINE" << endl;
            cout << "Swap5" << swap8 << "END OF LINE" << endl;
            vm_yield();
            strcpy(swap5, "ga");
            strcpy(swap6, "ba");
            strcpy(swap7, "ba"); // causes error
            strcpy(swap8, "ba");
            vm_yield();
            char* file6 = static_cast<char *>(vm_map (swap2, 2));
                    fork();
            for(int i = 0; i<1000; i++) cout << file6[i];

            cout << endl;
            for(int i = 0; i<1000; i++) cout << file3[i];
                    fork();

            cout << endl;
            for(int i = 0; i<1000; i++) cout << file2[i];

            cout << endl;
            cout << "Swap8" << swap8 << "END OF LINE" << endl;
            cout << "Swap5" << swap5 << "END OF LINE" << endl;
        }
    }
}