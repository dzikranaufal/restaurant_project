#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "utils.h"

Menu daftarMenu[50] = {
    {1, "Ayam Geprek sambal bawang", 15000, "Makanan"},
    {2, "Nasi Goreng Spesial", 20000, "Makanan"},
    {3, "Milkshake", 20000, "Minuman"},
    {4, "Sambal Cumi", 15000, "Makanan"},
    {5, "Cheescake Bluberry", 25000, "Makanan"},
    {6, "Orange Juice", 10000, "Minuman"}
};

int jumlah = 6;

void sortMenu(SortType type) {
    if (type == SORT_NONE) return;

    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            int swap = 0;

            switch (type) {
                case SORT_HARGA_ASC:
                    swap = daftarMenu[j].harga > daftarMenu[j + 1].harga;
                    break;
                case SORT_HARGA_DESC:
                    swap = daftarMenu[j].harga < daftarMenu[j + 1].harga;
                    break;
                case SORT_NAMA_ASC:
                    swap = strcmp(daftarMenu[j].nama, daftarMenu[j + 1].nama) > 0;
                    break;
                case SORT_NAMA_DESC:
                    swap = strcmp(daftarMenu[j].nama, daftarMenu[j + 1].nama) < 0;
                    break;
                default:
                    break;
            }

            if (swap) {
                Menu temp = daftarMenu[j];
                daftarMenu[j] = daftarMenu[j + 1];
                daftarMenu[j + 1] = temp;
            }
        }
    }
}

void tampilMenuPerKategori() {
    clearScreen();

    const char *kategori[] = {"Makanan", "Minuman", "Dessert"};

    printf("=========== DAFTAR MENU ===========\n");

    for (int k = 0; k < 3; k++) {
        printf("\n--- %s ---\n", kategori[k]);
        int ada = 0;

        for (int i = 0; i < jumlah; i++) {
            if (strcmp(daftarMenu[i].kategori, kategori[k]) == 0) {
                printf("[%d] %-30s Rp%d\n", daftarMenu[i].kode, daftarMenu[i].nama, daftarMenu[i].harga);
                ada = 1;
            }
        }

        if (!ada)
            printf("(Tidak ada menu)\n");
    }

    printf("===================================\n");
}

void menuController() {
    int pilih;
    clearScreen();

    printf("=== SORT MENU ===\n");
    printf("1. Harga Termurah\n");
    printf("2. Harga Termahal\n");
    printf("3. Nama A-Z\n");
    printf("4. Nama Z-A\n");
    printf("0. Tanpa Sorting\n");
    printf("Pilih: ");
    scanf("%d", &pilih);

    switch (pilih) {
        case 1: sortMenu(SORT_HARGA_ASC); break;
        case 2: sortMenu(SORT_HARGA_DESC); break;
        case 3: sortMenu(SORT_NAMA_ASC); break;
        case 4: sortMenu(SORT_NAMA_DESC); break;
        default: sortMenu(SORT_NONE); break;
    }

    tampilMenuPerKategori();
    pauseScreen();
}

void tambahData() {
    clearScreen();

    if (jumlah >= MAX_MENU) {
        printf("Menu penuh!\n");
        pauseScreen();
        return;
    }

    daftarMenu[jumlah].kode = jumlah + 1;
    printf("Kode otomatis: %d\n", daftarMenu[jumlah].kode);

    printf("Nama menu  : ");
    scanf(" %[^\n]", daftarMenu[jumlah].nama);

    printf("Harga      : ");
    scanf("%d", &daftarMenu[jumlah].harga);

    int k;
    printf("Kategori:\n1. Makanan\n2. Minuman\n3. Dessert\n> ");
    scanf("%d", &k);

    if (k == 1) strcpy(daftarMenu[jumlah].kategori, "Makanan");
    else if (k == 2) strcpy(daftarMenu[jumlah].kategori, "Minuman");
    else strcpy(daftarMenu[jumlah].kategori, "Dessert");

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

    int kode, index = -1;
    printf("Kode menu: ");
    scanf("%d", &kode);

    for (int i = 0; i < jumlah; i++) {
        if (daftarMenu[i].kode == kode) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Menu tidak ditemukan!\n");
        pauseScreen();
        return;
    }

    printf("Nama baru  : ");
    scanf(" %[^\n]", daftarMenu[index].nama);

    printf("Harga baru : ");
    scanf("%d", &daftarMenu[index].harga);

    int k;
    printf("Kategori:\n1. Makanan\n2. Minuman\n3. Dessert\n> ");
    scanf("%d", &k);

    if (k == 1) strcpy(daftarMenu[index].kategori, "Makanan");
    else if (k == 2) strcpy(daftarMenu[index].kategori, "Minuman");
    else strcpy(daftarMenu[index].kategori, "Dessert");

    printf("Menu diperbarui!\n");
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
