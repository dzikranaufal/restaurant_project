#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "ansi.h"
#include "utils.h"
#include "menu.h"
#include "order.h"

void clearScreen() {
    system("cls");
}

void pauseScreen() {
    printf("\nTekan ENTER untuk melanjutkan...");
    getchar(); 
    getchar();   
}

void inputPassword(char *pass) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();

        if (ch == 13) { 
            pass[i] = '\0';
            printf("\n");
            break;
        }
        else if (ch == 8) { 
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else {
            pass[i++] = ch;
            printf("*");
        }
    }
}

int login() {
    char user[50], pass[50];

    printf("╔══════════════════════════════╗\n");
    printf("║          LOGIN SISTEM        ║\n");
    printf("╠══════════════════════════════╣\n");
    printf("║ Username : ");
    scanf("%49s", user);

    printf("║ Password : ");
    inputPassword(pass);
    printf("\n╚══════════════════════════════╝\n");

    printf("\nMemverifikasi akun...\n"); 

    if (strcmp(user, "admin") == 0 && strcmp(pass, "admin123") == 0) {
        return 1; 
    }
    if (strcmp(user, "cashier") == 0 && strcmp(pass, "cash123") == 0) {
        return 2; 
    }

    return 0; 
}
void adminMenu() {
    int pilih;
    do {
        clearScreen();
        printf("\n");
        printf(BOLD "╔══════════════════════════════╗\n" RESET);
        printf(BOLD "║          MENU ADMIN          ║\n" RESET);
        printf(BOLD "╠══════════════════════════════╣\n" RESET);
        printf(BOLD "║ 1. " RESET "Tambah Menu               ║\n");
        printf(BOLD "║ 2. " RESET "Tampil Menu               ║\n");
        printf(BOLD "║ 3. " RESET "Hapus Menu                ║\n");
        printf(BOLD "║ 4. " RESET "Edit Menu                 ║\n");
        printf(BOLD "║ 5. " RESET "Search Menu               ║\n");
        printf(BOLD "║ 6. " RESET "Tambah Order              ║\n");
        printf(BOLD "║ 7. " RESET "Tampil Order              ║\n");
        printf(BOLD "╠══════════════════════════════╣\n" RESET);
        printf(BOLD "║ 0. " RESET "Logout                    ║\n");
        printf(BOLD "╚══════════════════════════════╝\n" RESET);
        printf(BOLD "Pilih menu ➜ " RESET);
        scanf("%d", &pilih);

        switch (pilih) {
            case 1: tambahData(); break;
            case 2: menuController(); break;
            case 3: hapusData(); break;
            case 4: editData(); break;
            case 5: searchMenu(); break;
            case 6: tambahOrder(); break;
            case 7: tampilOrder(); break;
            case 0: printf("Logout...\n"); break;
            default: printf("Pilihan salah!\n");
        }

    } while (pilih != 0);
}

void cashierMenu() {
    int pilih;
    do {
        clearScreen();
        printf("\n");
        printf(BOLD "╔══════════════════════════════╗\n" RESET);
        printf(BOLD "║         MENU CASHIER         ║\n" RESET);
        printf(BOLD "╠══════════════════════════════╣\n" RESET);
        printf(BOLD "║ 1. " RESET "Tambah Order              ║\n");
        printf(BOLD "║ 2. " RESET "Tampil Order              ║\n");
        printf(BOLD "╠══════════════════════════════╣\n" RESET);
        printf(BOLD "║ 0. " RESET "Logout                    ║\n");
        printf(BOLD "╚══════════════════════════════╝\n" RESET);
        printf(BOLD "Pilih menu ➜ " RESET);
        scanf("%d", &pilih);

        switch (pilih) {
            case 1: tambahOrder(); break;
            case 2: tampilOrder(); break;
            case 0: printf("Logout...\n"); break;
            default: printf("Pilihan salah!\n");
        }

    } while (pilih != 0);
}