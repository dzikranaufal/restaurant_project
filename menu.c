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

//tambahin nanti function hapus, sorting, edit, search disini.
