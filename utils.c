#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
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

    printf("\n======= LOGIN =======\n");
    printf("Username: ");
    scanf("%s", user);

    printf("Password: ");
    inputPassword(pass);  

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
        printf("\n===== MENU ADMIN =====\n");
        printf("1. Tambah Menu\n");
        printf("2. Tampil Menu\n");
        printf("3. Hapus Menu\n");
        printf("4. Edit Menu\n");
        printf("5. Search Menu\n");
        printf("6. Tambah Order\n");
        printf("7. Tampil Order\n");
        printf("0. Logout\n");
        printf("Pilih: ");
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
        printf("\n===== MENU CASHIER =====\n");
        printf("1. Tambah Order\n");
        printf("2. Tampil Order\n");
        printf("0. Logout\n");
        printf("Pilih: ");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1: tambahOrder(); break;
            case 2: tampilOrder(); break;
            case 0: printf("Logout...\n"); break;
            default: printf("Pilihan salah!\n");
        }

    } while (pilih != 0);
}