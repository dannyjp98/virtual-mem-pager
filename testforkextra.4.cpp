// most basic test of swap backed and file backed
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "vm_app.h"

using std::cout;
using std::endl;

int i = -1;


int main()
{
    
    if(fork()){
        cout << "-------------FIRST------------" << endl;
        char* swap1 = static_cast<char *>(vm_map(nullptr, 0));
        i = i+1;
        cout << "reserved 20 " << i << endl;
        char* swap2 = static_cast<char *>(vm_map(nullptr, 0));
         i = i+1;
        cout << "reserved 23 " << i << endl;
        char* swap3 = static_cast<char *>(vm_map(nullptr, 0));
         i = i+1;
        cout << "reserved 26 " << i << endl;
        cout << swap1;
        strcpy(swap1, "igyafeiug");
        cout << swap1;
        strcpy(swap2, "data2.bin");
        char* file2 = static_cast<char *>(vm_map (swap2, 3));
        char* file3 = static_cast<char *>(vm_map (swap2, 4));
        for(int i = 0; i<1; i++){
            cout << "FILE 2" << file2[i];
        }
        cout << endl;
        vm_yield();
        cout << "T------------BACK FROM FIRSTT------------" << endl;
        for(int i = 0; i<1; i++){
            cout << "FILE 3" << file3[i];
        }
        cout << endl;
        vm_yield();
        for(int i = 0; i<1; i++){
            cout << "FILE 3" << file3[i];
        }
        cout << endl;
        strcpy(file3, "yogsfdodhj");
        vm_yield();
        strcpy(file3, "nodohoda");
        char* file6 = static_cast<char *>(vm_map (swap2, 2));
        strcpy(file6, "bjaobih");
        strcpy(swap2, "ihpsihpfdpih");
    }
    else{
        if(fork()){
            cout << "T------------SECONDT------------" << endl;
            char* swap1 = static_cast<char *>(vm_map(nullptr, 0));
             i = i+1;
            cout << "reserved 60 " << i << endl;
            char* swap2 = static_cast<char *>(vm_map(nullptr, 0));
             i = i+1;
        cout << "reserved 63 " << i << endl;
            cout << swap2;
            strcpy(swap2, "data2.bin");
            cout << swap2;
            char* file2 = static_cast<char *>(vm_map (swap2, 3));
            
            for(int i = 0; i<1; i++) cout << file2[i];

            cout << endl;
            char* file3 = static_cast<char *>(vm_map (swap2, 4));
            
            for(int i = 0; i<1; i++) cout << file3[i];

            cout << endl;
            strcpy(file3, "hiadbuofaobobifovufeouv");
            vm_yield();  
            cout << "------------BACK FROM SECONDT------------" << endl; 
            char* swap5 = static_cast<char *>(vm_map(nullptr, 0));
             i = i+1;
        cout << "reserved 82 " << i << endl;
            char* swap6 = static_cast<char *>(vm_map(nullptr, 0));
             i = i+1;
        cout << "reserved 85 " << i << endl;
            char* swap7 = static_cast<char *>(vm_map(nullptr, 0));
             i = i+1;
        cout << "reserved 88 " << i << endl;
            char* swap8 = static_cast<char *>(vm_map(nullptr, 0)); 
             i = i+1;
        cout << "reserved 91 " << i << endl;
            strcpy(swap5, "ha");
            strcpy(swap6, "ha");
            strcpy(swap7, "ha");
            strcpy(swap8, "ha");
            cout << "Swap8" << swap8 << "END OF LINE" << endl;
            cout << "Swap5" << swap8 << "END OF LINE" << endl;
            vm_yield();
            strcpy(swap5, "ga");
            strcpy(swap6, "ba");
            strcpy(swap7, "ba");
            strcpy(swap8, "ba");
            vm_yield();
            char* file6 = static_cast<char *>(vm_map (swap2, 2));
            
            for(int i = 0; i<1; i++) cout << file6[i];

            cout << endl;
            
            for(int i = 0; i<1; i++) cout << file3[i];

            cout << endl;
            for(int i = 0; i<1; i++) cout << file2[i];

            cout << endl;
            cout << "Swap8" << swap8 << "END OF LINE" << endl;
            cout << "Swap5" << swap5 << "END OF LINE" << endl;
        }
        else{
            cout << "T------------THIRDT------------" << endl;
            char* swap1 = static_cast<char *>(vm_map(nullptr, 0));
             i = i+1;
        cout << "reserved 123 " << i << endl;
            char* swap2 = static_cast<char *>(vm_map(nullptr, 0));
             i = i+1;
        cout << "reserved 126 " << i << endl;
            cout << swap2;
            strcpy(swap2, "data2.bin");
            cout << swap2;
            char* file2 = static_cast<char *>(vm_map (swap2, 3));
            for(int i = 0; i<1; i++) cout << file2[i];

            cout << endl;
            char* file3 = static_cast<char *>(vm_map (swap2, 4));
            for(int i = 0; i<1; i++) cout << file3[i];

            cout << endl;
            strcpy(file3, "hiadbuofaobobifovufeouv");
            vm_yield();
            cout << "T------------BACK FROM THIRDT------------" << endl;   
            char* swap5 = static_cast<char *>(vm_map(nullptr, 0));
             i = i+1;
        cout << "reserved 143 " << i << endl;
            char* swap6 = static_cast<char *>(vm_map(nullptr, 0));
             i = i+1;
        cout << "reserved 146 " << i << endl;
            char* swap7 = static_cast<char *>(vm_map(nullptr, 0));
             i = i+1;
        cout << "reserved 149 " << i << endl;
            char* swap8 = static_cast<char *>(vm_map(nullptr, 0)); 
             i = i+1;
        cout << "reserved 152 " << i << endl;
            strcpy(swap5, "ha");
            strcpy(swap6, "ha");
            strcpy(swap7, "ha");
            strcpy(swap8, "ha");
            cout << "Swap8" << swap8 << "END OF LINE" << endl;
            cout << "Swap5" << swap8 << "END OF LINE" << endl;
            vm_yield();
            strcpy(swap5, "ga");
            strcpy(swap6, "ba");
            strcpy(swap7, "ba");
            strcpy(swap8, "ba");
            vm_yield();
            char* file6 = static_cast<char *>(vm_map (swap2, 2));
            for(int i = 0; i<1; i++) cout << file6[i];

            cout << endl;
            for(int i = 0; i<1; i++) cout << file3[i];

            cout << endl;
            for(int i = 0; i<1; i++) cout << file2[i];

            cout << endl;
            cout << "Swap8" << swap8 << "END OF LINE" << endl;
            cout << "Swap5" << swap5 << "END OF LINE" << endl;
        }
    }
}