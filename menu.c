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

char* kategoriList(int pilih) {
    switch(pilih) {
        case 1: return "Makanan";
        case 2: return "Minuman";
        case 3: return "Dessert";
        default: return "Lainnya";
    }
}

void sortHargaAsc();
void sortHargaDesc();

void tampilData() {
    clearScreen();

    int pilih;
    printf("=== TAMPILKAN MENU ===\n");
    printf("1. Harga Termurah (ASC)\n");
    printf("2. Harga Termahal (DESC)\n");
    printf("Pilih: ");
    scanf("%d", &pilih);

    if (pilih == 1)
        sortHargaAsc();
    else if (pilih == 2)
        sortHargaDesc();

    clearScreen();
    printf("\n========================== DAFTAR MENU ===========================\n");
    printf("| %-5s | %-30s | %-8s | %-10s |\n", "Kode", "Nama Menu", "Harga", "Kategori");
    printf("------------------------------------------------------------------\n");
    
    for(int i = 0; i < jumlah; i++){
        printf("| %-5d | %-30s | %-8d | %-10s |\n", daftarMenu[i].kode, daftarMenu[i].nama, daftarMenu[i].harga, daftarMenu[i].kategori);
    }
    printf("==================================================================\n");
}

void sortHargaAsc() {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (daftarMenu[j].harga > daftarMenu[j + 1].harga) {
                Menu temp = daftarMenu[j];
                daftarMenu[j] = daftarMenu[j + 1];
                daftarMenu[j + 1] = temp;
            }
        }
    }
}

void sortHargaDesc() {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (daftarMenu[j].harga < daftarMenu[j + 1].harga) {
                Menu temp = daftarMenu[j];
                daftarMenu[j] = daftarMenu[j + 1];
                daftarMenu[j + 1] = temp;
            }
        }
    }
}

void tambahData() {
    clearScreen();

    printf("\n=== Tambah Menu ===\n");

    daftarMenu[jumlah].kode = jumlah + 1; 
    printf("Kode menu otomatis: %d\n", daftarMenu[jumlah].kode);

    printf("Masukkan Nama        : ");
    scanf(" %[^\n]", daftarMenu[jumlah].nama);

    printf("Masukkan Harga       : ");
    scanf("%d", &daftarMenu[jumlah].harga);

    int pilihKategori;
    printf("Pilih Kategori:\n");
    printf("1. Makanan\n2. Minuman\n3. Dessert\n> ");
    scanf("%d", &pilihKategori);

    strcpy(daftarMenu[jumlah].kategori, kategoriList(pilihKategori));

    jumlah++;
    printf("Menu berhasil ditambahkan!\n");
    pauseScreen();
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
    printf("Masukkan kode menu: ");
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
        pauseScreen();
        return;
    } 
    printf("Masukkan Menu baru     : ");
    scanf(" %[^\n]", daftarMenu[index].nama);

    printf("Masukkan Harga baru    : ");
    scanf("%d", &daftarMenu[index].harga);

    int pilihKategori;
    printf("Pilih kategori baru:\n1. Makanan\n2. Minuman\n3. Dessert\n> ");
    scanf("%d", &pilihKategori);

    strcpy(daftarMenu[index].kategori, kategoriList(pilihKategori));
    printf("Menu berhasil diperbarui!\n");
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
