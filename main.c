#include <stdio.h>
#include <windows.h>  
#include "utils.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    while (1) {
        clearScreen(); 
        int role = login();

        if (role == 1){
            clearScreen();
            adminMenu();
        }
        else if (role == 2) {
            clearScreen();
            cashierMenu();
        }
        else {
            printf("Username atau password salah!\n");
            pauseScreen();
        }
        
    }
    return 0;
}
