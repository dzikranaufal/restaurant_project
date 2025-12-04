#include <stdio.h>
#include "utils.h"

int main() {
    while (1) {
        clearScreen(); 
        int role = login();

        if (role == 1) {
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
