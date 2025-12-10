#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "utils.h"

Menu daftarMenu[50] = {
    {1, "Ayam Geprek sambal bawang", 15000, "Makanan"},
    {2, "Nasi Goreng Spesial", 20000, "Makanan"},
    {3, "Milkshake", 20000, "Minuman"},
    {4, "Sambal Cumi", 15000, "Makanan"},
    {5, "Cheescake Bluberry", 25000, "Dessert"},
    {6, "Orange Juice", 10000, "Minuman"}
};

int jumlah = 6;

void tampilData() {
    clearScreen();
    printf("\n===== Daftar Menu Restoran =====\n");
    for(int i = 0; i < jumlah; i++){
        printf("[%d] %s - Rp%d (%s)\n", daftarMenu[i].kode, daftarMenu[i].nama, daftarMenu[i].harga, daftarMenu[i].kategori);
    }
    printf("==================================\n");
    pauseScreen();
}

void tambahData() {
    clearScreen();
    printf("\n=== Tambah Menu ===\n");

    printf("Masukkan Kode        : ");
    scanf("%d", &daftarMenu[jumlah].kode);

    printf("Masukkan Nama        : ");
    scanf(" %[^\n]", daftarMenu[jumlah].nama);

    printf("Masukkan Harga       : ");
    scanf("%d", &daftarMenu[jumlah].harga);

    printf("Masukkan Kategori    : ");
    scanf(" %[^\n]", daftarMenu[jumlah].kategori);

    jumlah++;
    printf("Menu berhasil ditambahkan!\n");
}

void hapusData() {
    clearScreen();
    
    int kode;
    printf("\n=== Hapus Menu ===\n");
    printf("Masukkan kode menu yang ingin dihapus: ");
    scanf("%d", &kode);

    int index = -1;
    for(int i = 0; i < jumlah; i++){
        if (daftarMenu[i].kode == kode){
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Data tidak ditemukan!\n");
    } else {
        for (int i = index; i < jumlah-1; i++){
            daftarMenu[i] = daftarMenu[i+1];
        }
        jumlah--;
        printf("Data berhasil dihapus!\n");
    }
    pauseScreen();
}

void editData() {
    clearScreen();
    int kode;
    printf("\n=== Edit Menu ===\n");
    printf("Masukkan kode menu yang ingin diedit: ");
    scanf("%d", &kode);

    int index = -1;
    for(int i = 0; i < jumlah; i++){
        if (daftarMenu[i].kode == kode){
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Data tidak ditemukan!\n");
    } else {
        printf("Masukkan Menu baru     : ");
        scanf(" %[^\n]", daftarMenu[index].nama);

        printf("Masukkan Harga baru    : ");
        scanf("%d", &daftarMenu[index].harga);

        printf("Masukkan Kategori baru : ");
        scanf(" %[^\n]", daftarMenu[index].kategori);

        printf("Menu berhasil diperbarui!\n");
    }
    pauseScreen();
}

void sortingMenu() {
    clearScreen();
    printf("\n=== Sorting Harga Asc ===\n");

    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (daftarMenu[j].harga > daftarMenu[j+1].harga) {
                Menu temp = daftarMenu[j];
                daftarMenu[j] = daftarMenu[j+1];
                daftarMenu[j+1] = temp;
            }
        }
    }

    printf("Sorting selesai!\n");
    pauseScreen();
}

void searchMenu() {
    clearScreen();

    char cari[50];
    printf("\n=== Searching Menu Berdasarkan Nama ===\n");
    printf("Masukkan nama menu: ");
    scanf(" %[^\n]", cari);

    int index = 0;
    for(int i = 0; i < jumlah; i++){
        if (strstr(daftarMenu[i].nama, cari)){
            printf("[%d] %s - Rp%d (%s)\n", daftarMenu[i].kode, daftarMenu[i].nama, daftarMenu[i].harga, daftarMenu[i].kategori);
            index = 1;
        }
    }
    if (!index) printf("Menu tidak ditemukan!\n");
    pauseScreen();
}
