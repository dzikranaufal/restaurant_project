#include <stdio.h>
#include <string.h>
#include "ansi.h"
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
    
    printf("\n");
    printf(BOLD "╔════════════════════════════════════════════╗\n" RESET);
    printf(BOLD "║               DAFTAR MENU                  ║\n" RESET);
    printf(BOLD "╚════════════════════════════════════════════╝\n" RESET);

    for (int k = 0; k < 3; k++) {
        printf("\n");
        printf(BOLD "┌────────────────────────────────────────────┐\n" RESET);
        printf(BOLD "│ %-42s │\n" RESET, kategori[k]);
        printf(BOLD "├────┬────────────────────────────────┬──────┤\n" RESET);
        printf(BOLD "│ ID │ Nama Menu                      │ Harga│\n" RESET);
        printf(BOLD "├────┼────────────────────────────────┼──────┤\n" RESET);

        int ada = 0;

        for (int i = 0; i < jumlah; i++) {
            if (strcmp(daftarMenu[i].kategori, kategori[k]) == 0) {
                printf("│ %-2d │ %-30s │ %5d│\n", daftarMenu[i].kode, daftarMenu[i].nama, daftarMenu[i].harga);
                ada = 1;
            }
        }

        if (!ada) {
            printf("│ %-44s │\n", "Tidak ada menu");
        }

        printf(BOLD "└────┴────────────────────────────────┴──────┘\n" RESET);
    }
    pauseScreen();
}

void menuController() {
    int pilih;
    clearScreen();

    printf("\n");
    printf(BOLD "╔══════════════════════════════╗\n" RESET);
    printf(BOLD "║          SORT MENU           ║\n" RESET);
    printf(BOLD "╠══════════════════════════════╣\n" RESET);
    printf(BOLD "║ 1. " RESET "Harga Termurah       ║\n");
    printf(BOLD "║ 2. " RESET "Harga Termahal       ║\n");
    printf(BOLD "║ 3. " RESET "Nama A - Z           ║\n");
    printf(BOLD "║ 4. " RESET "Nama Z - A           ║\n");
    printf(BOLD "╠══════════════════════════════╣\n" RESET);
    printf(BOLD "║ 0. " RESET "Tanpa Sorting        ║\n");
    printf(BOLD "╚══════════════════════════════╝\n" RESET);
    printf(BOLD "Pilih menu ➜ " RESET);
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
        printf(BOLD "Menu penuh! Tidak bisa menambah data.\n" RESET);
        pauseScreen();
        return;
    }

    daftarMenu[jumlah].kode = jumlah + 1;

    printf("\n");
    printf(BOLD "╔════════════════════════════════╗\n" RESET);
    printf(BOLD "║           TAMBAH MENU          ║\n" RESET);
    printf(BOLD "╚════════════════════════════════╝\n" RESET);

    printf(BOLD "Kode     : " RESET "%d\n", daftarMenu[jumlah].kode);

    printf(BOLD "Nama     : " RESET);
    scanf(" %[^\n]", daftarMenu[jumlah].nama);

    printf(BOLD "Harga    : " RESET);
    scanf("%d", &daftarMenu[jumlah].harga);

    int k;
    printf(BOLD "Kategori :\n" RESET);
    printf("  1. Makanan\n");
    printf("  2. Minuman\n");
    printf("  3. Dessert\n");
    printf(BOLD "  Pilih ➜ " RESET);
    scanf("%d", &k);

    if (k == 1)
        strcpy(daftarMenu[jumlah].kategori, "Makanan");
    else if (k == 2)
        strcpy(daftarMenu[jumlah].kategori, "Minuman");
    else
        strcpy(daftarMenu[jumlah].kategori, "Dessert");

    jumlah++;

    printf("\n" BOLD "Menu berhasil ditambahkan!\n" RESET);
    pauseScreen();
}

void hapusData() {
    clearScreen();
    
    int kode;

    printf("\n");
    printf(BOLD "╔══════════════════════════════╗\n" RESET);
    printf(BOLD "║           HAPUS MENU         ║\n" RESET);
    printf(BOLD "╚══════════════════════════════╝\n" RESET);
    printf(BOLD "Masukkan kode menu ➜ " RESET);
    scanf("%d", &kode);

    int index = -1;
    for (int i = 0; i < jumlah; i++) {
        if (daftarMenu[i].kode == kode) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\n" BOLD "Data tidak ditemukan!\n" RESET);
        pauseScreen();
        return;
    }

    printf("\nData yang dihapus:\n");
    printf("Kode  : %d\n", daftarMenu[index].kode);
    printf("Nama  : %s\n", daftarMenu[index].nama);
    printf("Harga : Rp%d\n", daftarMenu[index].harga);
    printf("Kategori: %s\n", daftarMenu[index].kategori);

    char konfirmasi;
    printf(BOLD "\nYakin ingin menghapus? (y/n) ➜ " RESET);
    scanf(" %c", &konfirmasi);

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        for (int i = index; i < jumlah - 1; i++) {
            daftarMenu[i] = daftarMenu[i + 1];
        }
        jumlah--;
        printf("\n" BOLD "Data berhasil dihapus!\n" RESET);
    } else {
        printf("\n" BOLD "Penghapusan dibatalkan.\n" RESET);
    }

    pauseScreen();
}


void editData() {
    clearScreen();

    int kode, index = -1;

    printf("\n");
    printf(BOLD "╔══════════════════════════════╗\n" RESET);
    printf(BOLD "║            EDIT MENU         ║\n" RESET);
    printf(BOLD "╚══════════════════════════════╝\n" RESET);

    printf(BOLD "Masukkan kode menu ➜ " RESET);
    scanf("%d", &kode);

    for (int i = 0; i < jumlah; i++) {
        if (daftarMenu[i].kode == kode) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\n" BOLD "Menu tidak ditemukan!\n" RESET);
        pauseScreen();
        return;
    }

    printf("\nData saat ini:\n");
    printf("Kode     : %d\n", daftarMenu[index].kode);
    printf("Nama     : %s\n", daftarMenu[index].nama);
    printf("Harga    : Rp%d\n", daftarMenu[index].harga);
    printf("Kategori : %s\n", daftarMenu[index].kategori);

    printf("\n" BOLD "Masukkan data baru\n" RESET);

    printf(BOLD "Nama     : " RESET);
    scanf(" %[^\n]", daftarMenu[index].nama);

    printf(BOLD "Harga    : " RESET);
    scanf("%d", &daftarMenu[index].harga);

    int k;
    printf(BOLD "Kategori :\n" RESET);
    printf("  1. Makanan\n");
    printf("  2. Minuman\n");
    printf("  3. Dessert\n");
    printf(BOLD "  Pilih ➜ " RESET);
    scanf("%d", &k);

    if (k == 1)
        strcpy(daftarMenu[index].kategori, "Makanan");
    else if (k == 2)
        strcpy(daftarMenu[index].kategori, "Minuman");
    else
        strcpy(daftarMenu[index].kategori, "Dessert");

    printf("\n" BOLD "Menu berhasil diperbarui!\n" RESET);
    pauseScreen();
}


void searchMenu() {
    clearScreen();

    char cari[50];
    int ditemukan = 0;

    printf("\n");
    printf(BOLD "╔════════════════════════════════════════════╗\n" RESET);
    printf(BOLD "║        SEARCH MENU (BERDASARKAN NAMA)      ║\n" RESET);
    printf(BOLD "╚════════════════════════════════════════════╝\n" RESET);

    printf(BOLD "Masukkan nama menu ➜ " RESET);
    scanf(" %[^\n]", cari);

    printf("\n");
    printf(BOLD "Hasil pencarian:\n" RESET);

    printf(BOLD "┌────┬────────────────────────────────┬────────┬──────────┐\n" RESET);
    printf(BOLD "│ ID │ Nama Menu                      │ Harga  │ Kategori │\n" RESET);
    printf(BOLD "├────┼────────────────────────────────┼────────┼──────────┤\n" RESET);

    for (int i = 0; i < jumlah; i++) {
        if (strstr(daftarMenu[i].nama, cari)) {
            printf("│ %-2d │ %-30s │ %6d │ %-8s │\n", daftarMenu[i].kode, daftarMenu[i].nama, daftarMenu[i].harga, daftarMenu[i].kategori);
            ditemukan = 1;
        }
    }

    if (!ditemukan) {
        printf("│ %-44s │\n", "Menu tidak ditemukan");
    }

    printf(BOLD "└────┴────────────────────────────────┴────────┴──────────┘\n" RESET);

    pauseScreen();
}

