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
        char* swap0 = static_cast<char *>(vm_map(nullptr, 0));
        char* swap1 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap1, "data3.bin");
        char* file2 = static_cast<char *>(vm_map (swap1, 0));
        char* file1 = static_cast<char *>(vm_map (swap1, 0));
        cout << file2[0];
        cout << file1[0];
        char* file3 = static_cast<char *>(vm_map (swap1, 1));
        strcpy(file3, "ojnfjnosfonfson");
        char* file4 = static_cast<char *>(vm_map (swap1, 1));
        strcpy(file1, "adougduogaogoid");
        char* file5 = static_cast<char *>(vm_map (swap1, 0));
        cout << file2[0];
        fork();
        char* file6 = static_cast<char *>(vm_map (swap1, 0));
        strcpy(file2, "fafaaougdoiad");
        cout << file1[0];
        char* file7 = static_cast<char *>(vm_map (swap1, 0));
        cout << swap1;
        char* file8 = static_cast<char *>(vm_map (swap1, 2));
        cout << file8[0];
        char* file9 = static_cast<char *>(vm_map (swap1, 0));
        char* file10 = static_cast<char *>(vm_map (swap1, 1));
        char* file11 = static_cast<char *>(vm_map (swap1, 2));
        cout << file10[0];
        char* file12 = static_cast<char *>(vm_map (swap1, 1));
        cout << swap1;
        char* file13 = static_cast<char *>(vm_map (swap1, 3));
        cout << file13[0];
        fork();
        strcpy(file1, "adoiduoaebboudaead");
        strcpy(file3, "adibuuvdaebudeaboud");
        strcpy(file8, "dai[deipbgdepgiipde]");

        char* swap00 = static_cast<char *>(vm_map(nullptr, 0));
        char* swap2 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(swap2, "data4.bin");
        char* filea = static_cast<char *>(vm_map (swap2, 0));
        char* fileb = static_cast<char *>(vm_map (swap2, 1));
        cout << filea[0];
        cout << fileb[0];
        char* filec = static_cast<char *>(vm_map (swap2, 0));
        char* filed = static_cast<char *>(vm_map (swap2, 1));
        char* filee = static_cast<char *>(vm_map (swap2, 2));
        cout << filee[0];
        cout << filed[0];
        strcpy(filed, "bfaebuobfaeboao");
        char* filef = static_cast<char *>(vm_map (swap2, 3));
        cout << filef[0]; // filee still in
        strcpy(filee, "ivyafvuoubfaoubefao");
        char* fileg = static_cast<char *>(vm_map (swap2, 3));
        char* fileh = static_cast<char *>(vm_map (swap2, 2));
        char* filei = static_cast<char *>(vm_map (swap2, 1));
        char* filej = static_cast<char *>(vm_map (swap2, 0));
        fork();
        char* filek = static_cast<char *>(vm_map (swap2, 4));
        cout << filek[4];
        strcpy(fileg, "ugeqdguoougegou");
        char* filel = static_cast<char *>(vm_map (swap2, 3));
        char* filem = static_cast<char *>(vm_map (swap2, 2));
        char* filen = static_cast<char *>(vm_map (swap2, 4));


        //SECOND TIME 

        char* wap0 = static_cast<char *>(vm_map(nullptr, 0));
        char* wap1 = static_cast<char *>(vm_map(nullptr, 0));
        fork();
        strcpy(wap1, "data3.bin");
        char* ile2 = static_cast<char *>(vm_map (wap1, 0));
        char* ile1 = static_cast<char *>(vm_map (wap1, 0));
        cout << ile2[0];
        cout << ile1[0];
        char* ile3 = static_cast<char *>(vm_map (wap1, 1));
        strcpy(ile3, "ojnfjnosfonfson");
        char* ile4 = static_cast<char *>(vm_map (wap1, 1));
        strcpy(ile1, "adougduogaogoid");
        char* ile5 = static_cast<char *>(vm_map (wap1, 0));
        cout << ile2[0];
        char* ile6 = static_cast<char *>(vm_map (wap1, 0));
        strcpy(ile2, "fafaaougdoiad");
        cout << ile1[0];
        char* ile7 = static_cast<char *>(vm_map (wap1, 0));
        cout << wap1;
        char* ile8 = static_cast<char *>(vm_map (wap1, 2));
        cout << ile8[0];
        char* ile9 = static_cast<char *>(vm_map (wap1, 0));
        char* ile10 = static_cast<char *>(vm_map (wap1, 1));
        char* ile11 = static_cast<char *>(vm_map (wap1, 2));
        cout << ile10[0];
        char* ile12 = static_cast<char *>(vm_map (wap1, 1));
        cout << wap1;
        char* ile13 = static_cast<char *>(vm_map (wap1, 3));
        cout << ile13[0];
        fork();
        strcpy(ile1, "adoiduoaebboudaead");
        strcpy(ile3, "adibuuvdaebudeaboud");
        strcpy(ile8, "dai[deipbgdepgiipde]");

        char* wap00 = static_cast<char *>(vm_map(nullptr, 0));
        char* wap2 = static_cast<char *>(vm_map(nullptr, 0));
        strcpy(wap2, "data4.bin");
        char* ilea = static_cast<char *>(vm_map (wap2, 0));
        char* ileb = static_cast<char *>(vm_map (wap2, 1));
        cout << ilea[0];
        cout << ileb[0];
        char* ilec = static_cast<char *>(vm_map (wap2, 0));
        char* iled = static_cast<char *>(vm_map (wap2, 1));
        char* ilee = static_cast<char *>(vm_map (wap2, 2));
        cout << ilee[0];
        cout << iled[0];
        fork();
        strcpy(iled, "bfaebuobfaeboao");
        char* ilef = static_cast<char *>(vm_map (wap2, 3));
        cout << ilef[0]; // filee still in
        strcpy(ilee, "ivyafvuoubfaoubefao");
        char* ileg = static_cast<char *>(vm_map (wap2, 3));
        char* ileh = static_cast<char *>(vm_map (wap2, 2));
        char* ilei = static_cast<char *>(vm_map (wap2, 1));
        char* ilej = static_cast<char *>(vm_map (wap2, 0));
        char* ilek = static_cast<char *>(vm_map (wap2, 4));
        cout << ilek[4];
        strcpy(ileg, "ugeqdguoougegou");
        char* ilel = static_cast<char *>(vm_map (wap2, 3));
        fork();
        char* ilem = static_cast<char *>(vm_map (wap2, 2));
        char* ilen = static_cast<char *>(vm_map (wap2, 4));
        
    }
    else{
        if(fork()){
            char* swap0 = static_cast<char *>(vm_map(nullptr, 0));
            char* swap1 = static_cast<char *>(vm_map(nullptr, 0));
            strcpy(swap1, "data3.bin");
            char* file2 = static_cast<char *>(vm_map (swap1, 0));
            char* file1 = static_cast<char *>(vm_map (swap1, 0));
            cout << file2[0];
            cout << file1[0];
            char* file3 = static_cast<char *>(vm_map (swap1, 1));
            strcpy(file3, "ojnfjnosfonfson");
            char* file4 = static_cast<char *>(vm_map (swap1, 1));
            strcpy(file1, "adougduogaogoid");
            char* file5 = static_cast<char *>(vm_map (swap1, 0));
            cout << file2[0];
            char* file6 = static_cast<char *>(vm_map (swap1, 0));
            strcpy(file2, "fafaaougdoiad");
            cout << file1[0];
            char* file7 = static_cast<char *>(vm_map (swap1, 0));
            cout << swap1;
            char* file8 = static_cast<char *>(vm_map (swap1, 2));
            cout << file8[0];
            fork();
            char* file9 = static_cast<char *>(vm_map (swap1, 0));
            char* file10 = static_cast<char *>(vm_map (swap1, 1));
            char* file11 = static_cast<char *>(vm_map (swap1, 2));
            cout << file10[0];
            char* file12 = static_cast<char *>(vm_map (swap1, 1));
            cout << swap1;
            char* file13 = static_cast<char *>(vm_map (swap1, 3));
            cout << file13[0];
            strcpy(file1, "adoiduoaebboudaead");
            strcpy(file3, "adibuuvdaebudeaboud");
            strcpy(file8, "dai[deipbgdepgiipde]");
            fork();

            vm_yield();

            char* swap00 = static_cast<char *>(vm_map(nullptr, 0));
            char* swap2 = static_cast<char *>(vm_map(nullptr, 0));
            strcpy(swap2, "data4.bin");
            char* filea = static_cast<char *>(vm_map (swap2, 0));
            char* fileb = static_cast<char *>(vm_map (swap2, 1));
            cout << filea[0];
            cout << fileb[0];
            char* filec = static_cast<char *>(vm_map (swap2, 0));
            char* filed = static_cast<char *>(vm_map (swap2, 1));
            char* filee = static_cast<char *>(vm_map (swap2, 2));
            cout << filee[0];
            cout << filed[0];
            fork();
            strcpy(filed, "bfaebuobfaeboao");
            char* filef = static_cast<char *>(vm_map (swap2, 3));
            cout << filef[0]; // filee still in
            strcpy(filee, "ivyafvuoubfaoubefao");
            char* fileg = static_cast<char *>(vm_map (swap2, 3));
            char* fileh = static_cast<char *>(vm_map (swap2, 2));
            char* filei = static_cast<char *>(vm_map (swap2, 1));
            char* filej = static_cast<char *>(vm_map (swap2, 0));
            char* filek = static_cast<char *>(vm_map (swap2, 4));
            cout << filek[4];
            strcpy(fileg, "ugeqdguoougegou");
            char* filel = static_cast<char *>(vm_map (swap2, 3));
            char* filem = static_cast<char *>(vm_map (swap2, 2));
            char* filen = static_cast<char *>(vm_map (swap2, 4));


            vm_yield();
            fork();

            char* wap0 = static_cast<char *>(vm_map(nullptr, 0));
            char* wap1 = static_cast<char *>(vm_map(nullptr, 0));
            strcpy(wap1, "data3.bin");
            char* ile2 = static_cast<char *>(vm_map (wap1, 0));
            char* ile1 = static_cast<char *>(vm_map (wap1, 0));
            cout << ile2[0];
            cout << ile1[0];
            char* ile3 = static_cast<char *>(vm_map (wap1, 1));
            strcpy(ile3, "ojnfjnosfonfson");
            char* ile4 = static_cast<char *>(vm_map (wap1, 1));
            strcpy(ile1, "adougduogaogoid");
            char* ile5 = static_cast<char *>(vm_map (wap1, 0));
            cout << ile2[0];
            char* ile6 = static_cast<char *>(vm_map (wap1, 0));
            strcpy(ile2, "fafaaougdoiad");
            cout << ile1[0];
            char* ile7 = static_cast<char *>(vm_map (wap1, 0));
            cout << wap1;
            fork();
            char* ile8 = static_cast<char *>(vm_map (wap1, 2));
            cout << ile8[0];
            char* ile9 = static_cast<char *>(vm_map (wap1, 0));
            char* ile10 = static_cast<char *>(vm_map (wap1, 1));
            char* ile11 = static_cast<char *>(vm_map (wap1, 2));
            cout << ile10[0];
            char* ile12 = static_cast<char *>(vm_map (wap1, 1));
            cout << wap1;
            char* ile13 = static_cast<char *>(vm_map (wap1, 3));
            cout << ile13[0];
            strcpy(ile1, "adoiduoaebboudaead");
            strcpy(ile3, "adibuuvdaebudeaboud");
            strcpy(ile8, "dai[deipbgdepgiipde]");

            char* wap00 = static_cast<char *>(vm_map(nullptr, 0));
            char* wap2 = static_cast<char *>(vm_map(nullptr, 0));
            strcpy(wap2, "data4.bin");
            char* ilea = static_cast<char *>(vm_map (wap2, 0));
            char* ileb = static_cast<char *>(vm_map (wap2, 1));
            fork();
            cout << ilea[0];
            cout << ileb[0];
            char* ilec = static_cast<char *>(vm_map (wap2, 0));
            char* iled = static_cast<char *>(vm_map (wap2, 1));
            char* ilee = static_cast<char *>(vm_map (wap2, 2));
            cout << ilee[0];
            cout << iled[0];
            strcpy(iled, "bfaebuobfaeboao");
            char* ilef = static_cast<char *>(vm_map (wap2, 3));
            cout << ilef[0]; // filee still in
            strcpy(ilee, "ivyafvuoubfaoubefao");
            char* ileg = static_cast<char *>(vm_map (wap2, 3));
            char* ileh = static_cast<char *>(vm_map (wap2, 2));
            char* ilei = static_cast<char *>(vm_map (wap2, 1));
            char* ilej = static_cast<char *>(vm_map (wap2, 0));
            char* ilek = static_cast<char *>(vm_map (wap2, 4));
            cout << ilek[4];
            strcpy(ileg, "ugeqdguoougegou");
            char* ilel = static_cast<char *>(vm_map (wap2, 3));
            char* ilem = static_cast<char *>(vm_map (wap2, 2));
            char* ilen = static_cast<char *>(vm_map (wap2, 4));
        }
        else{
            char* swap0 = static_cast<char *>(vm_map(nullptr, 0));
            char* swap1 = static_cast<char *>(vm_map(nullptr, 0));
            strcpy(swap1, "data3.bin");
            char* file2 = static_cast<char *>(vm_map (swap1, 0));
            char* file1 = static_cast<char *>(vm_map (swap1, 0));
            cout << file2[0];
            cout << file1[0];
            char* file3 = static_cast<char *>(vm_map (swap1, 1));
            strcpy(file3, "ojnfjnosfonfson");
            char* file4 = static_cast<char *>(vm_map (swap1, 1));
            strcpy(file1, "adougduogaogoid");
            char* file5 = static_cast<char *>(vm_map (swap1, 0));
            cout << file2[0];
            char* file6 = static_cast<char *>(vm_map (swap1, 0));
            strcpy(file2, "fafaaougdoiad");
            cout << file1[0];
            char* file7 = static_cast<char *>(vm_map (swap1, 0));
            cout << swap1;
            char* file8 = static_cast<char *>(vm_map (swap1, 2));
            cout << file8[0];
            char* file9 = static_cast<char *>(vm_map (swap1, 0));
            char* file10 = static_cast<char *>(vm_map (swap1, 1));
            char* file11 = static_cast<char *>(vm_map (swap1, 2));
            cout << file10[0];
            char* file12 = static_cast<char *>(vm_map (swap1, 1));
            cout << swap1;
            char* file13 = static_cast<char *>(vm_map (swap1, 3));
            cout << file13[0];
            strcpy(file1, "adoiduoaebboudaead");
            strcpy(file3, "adibuuvdaebudeaboud");
            strcpy(file8, "dai[deipbgdepgiipde]");

            vm_yield();

            fork();

            char* swap00 = static_cast<char *>(vm_map(nullptr, 0));
            char* swap2 = static_cast<char *>(vm_map(nullptr, 0));
            strcpy(swap2, "data4.bin");
            char* filea = static_cast<char *>(vm_map (swap2, 0));
            char* fileb = static_cast<char *>(vm_map (swap2, 1));
            cout << filea[0];
            cout << fileb[0];
            char* filec = static_cast<char *>(vm_map (swap2, 0));
            char* filed = static_cast<char *>(vm_map (swap2, 1));
            char* filee = static_cast<char *>(vm_map (swap2, 2));
            cout << filee[0];
            cout << filed[0];
            strcpy(filed, "bfaebuobfaeboao");
            char* filef = static_cast<char *>(vm_map (swap2, 3));
            cout << filef[0]; // filee still in
            strcpy(filee, "ivyafvuoubfaoubefao");
            char* fileg = static_cast<char *>(vm_map (swap2, 3));
            char* fileh = static_cast<char *>(vm_map (swap2, 2));
            char* filei = static_cast<char *>(vm_map (swap2, 1));
            char* filej = static_cast<char *>(vm_map (swap2, 0));
            char* filek = static_cast<char *>(vm_map (swap2, 4));
            cout << filek[4];
            strcpy(fileg, "ugeqdguoougegou");
            char* filel = static_cast<char *>(vm_map (swap2, 3));
            char* filem = static_cast<char *>(vm_map (swap2, 2));
            char* filen = static_cast<char *>(vm_map (swap2, 4));


            vm_yield();

            fork();

            char* wap0 = static_cast<char *>(vm_map(nullptr, 0));
            char* wap1 = static_cast<char *>(vm_map(nullptr, 0));
            strcpy(wap1, "data3.bin");
            char* ile2 = static_cast<char *>(vm_map (wap1, 0));
            char* ile1 = static_cast<char *>(vm_map (wap1, 0));
            cout << ile2[0];
            cout << ile1[0];
            char* ile3 = static_cast<char *>(vm_map (wap1, 1));
            strcpy(ile3, "ojnfjnosfonfson");
            char* ile4 = static_cast<char *>(vm_map (wap1, 1));
            strcpy(ile1, "adougduogaogoid");
            char* ile5 = static_cast<char *>(vm_map (wap1, 0));
            cout << ile2[0];
            char* ile6 = static_cast<char *>(vm_map (wap1, 0));
            strcpy(ile2, "fafaaougdoiad");
            cout << ile1[0];
            char* ile7 = static_cast<char *>(vm_map (wap1, 0));
            cout << wap1;
            char* ile8 = static_cast<char *>(vm_map (wap1, 2));
            cout << ile8[0];
            char* ile9 = static_cast<char *>(vm_map (wap1, 0));
            char* ile10 = static_cast<char *>(vm_map (wap1, 1));
            char* ile11 = static_cast<char *>(vm_map (wap1, 2));
            cout << ile10[0];
            char* ile12 = static_cast<char *>(vm_map (wap1, 1));
            cout << wap1;
            char* ile13 = static_cast<char *>(vm_map (wap1, 3));
            cout << ile13[0];
            strcpy(ile1, "adoiduoaebboudaead");
            strcpy(ile3, "adibuuvdaebudeaboud");
            strcpy(ile8, "dai[deipbgdepgiipde]");

            char* wap00 = static_cast<char *>(vm_map(nullptr, 0));
            char* wap2 = static_cast<char *>(vm_map(nullptr, 0));
            strcpy(wap2, "data4.bin");
            char* ilea = static_cast<char *>(vm_map (wap2, 0));
            char* ileb = static_cast<char *>(vm_map (wap2, 1));
            cout << ilea[0];
            cout << ileb[0];
            char* ilec = static_cast<char *>(vm_map (wap2, 0));
            char* iled = static_cast<char *>(vm_map (wap2, 1));
            char* ilee = static_cast<char *>(vm_map (wap2, 2));
            cout << ilee[0];
            cout << iled[0];
            strcpy(iled, "bfaebuobfaeboao");
            char* ilef = static_cast<char *>(vm_map (wap2, 3));
            cout << ilef[0]; // filee still in
            strcpy(ilee, "ivyafvuoubfaoubefao");
            char* ileg = static_cast<char *>(vm_map (wap2, 3));
            char* ileh = static_cast<char *>(vm_map (wap2, 2));
            char* ilei = static_cast<char *>(vm_map (wap2, 1));
            char* ilej = static_cast<char *>(vm_map (wap2, 0));
            char* ilek = static_cast<char *>(vm_map (wap2, 4));
            cout << ilek[4];
            strcpy(ileg, "ugeqdguoougegou");
            char* ilel = static_cast<char *>(vm_map (wap2, 3));
            char* ilem = static_cast<char *>(vm_map (wap2, 2));
            char* ilen = static_cast<char *>(vm_map (wap2, 4));
        }
    }
}
