#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ansi.h"
#include "order.h"
#include "menu.h" 
#include "utils.h" 

Order daftarOrder[MAX_ORDER];
int jumlahOrder = 0;

static void cetakStruk(FILE *out, Order *pesanan) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    int pajak = pesanan->total * 10 / 100;
    int totalDenganPajak = pesanan->total + pajak;

    fprintf(out, "====================\n");
    fprintf(out, "       Cashier\n");
    fprintf(out, "====================\n");
    fprintf(out, "id:%02d\n", pesanan->idOrder);
    fprintf(out, "time:%02d/%02d/%04d %02d:%02d %s\n", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900, local->tm_hour, local->tm_min, pesanan->namaOrder);
    fprintf(out, "====================\n");

    for (int i = 0; i < pesanan->jumlahItem; i++) {
        fprintf(out, "%d %-14s%7d\n", pesanan->items[i].qty, pesanan->items[i].nama, pesanan->items[i].subtotal);
    }

    fprintf(out, "====================\n");
    fprintf(out, "SUBTOTAL%13d\n", pesanan->total);
    fprintf(out, "PB%19d\n", pajak);
    fprintf(out, "====================\n");
    fprintf(out, "TOTAL%16d\n", totalDenganPajak);
}


int cariHargaMenu(int kodeMenu) {
    for (int i = 0; i < jumlah; i++) {
        if (daftarMenu[i].kode == kodeMenu) {
            return daftarMenu[i].harga;
        }
    }
    return -1;
}

void tambahOrder() {
    clearScreen();

    if (jumlahOrder >= MAX_ORDER) {
        printf(BOLD "Kapasitas pesanan sudah penuh!\n" RESET);
        pauseScreen();
        return;
    }

    printf("\n");
    printf(BOLD "╔════════════════════════════════════╗\n" RESET);
    printf(BOLD "║        TAMBAH PESANAN BARU         ║\n" RESET);
    printf(BOLD "╚════════════════════════════════════╝\n" RESET);

    Order *pesanan = &daftarOrder[jumlahOrder];
    memset(pesanan, 0, sizeof(Order));
    pesanan->idOrder = jumlahOrder + 1;

    printf(BOLD "ID Order : " RESET "%d\n", pesanan->idOrder);

    printf(BOLD "Nama Pembeli ➜ " RESET);
    scanf(" %[^\n]", pesanan->namaOrder);

    /* Tampilkan menu */
    tampilMenuPerKategori();

    int jenisMenu;
    printf(BOLD "\nBerapa jenis menu yang dipesan? (maks %d) ➜ " RESET, MAX_ORDER_ITEMS);
    scanf("%d", &jenisMenu);

    if (jenisMenu <= 0 || jenisMenu > MAX_ORDER_ITEMS) {
        printf(BOLD "Jumlah tidak valid!\n" RESET);
        pauseScreen();
        return;
    }

    for (int i = 0; i < jenisMenu; i++) {
        int kodeMenu, qty;

        printf("\n");
        printf(BOLD "┌──────────────────────────────┐\n" RESET);
        printf(BOLD "│ Item ke-%-20d │\n" RESET, i + 1);
        printf(BOLD "└──────────────────────────────┘\n" RESET);

        printf(BOLD "Kode Menu ➜ " RESET);
        scanf("%d", &kodeMenu);

        int harga = cariHargaMenu(kodeMenu);
        if (harga == -1) {
            printf(BOLD "Kode menu tidak ditemukan!\n" RESET);
            i--;
            continue;
        }

        char namaMenu[100] = "";
        for (int j = 0; j < jumlah; j++) {
            if (daftarMenu[j].kode == kodeMenu) {
                strcpy(namaMenu, daftarMenu[j].nama);
                break;
            }
        }

        printf(BOLD "Jumlah ➜ " RESET);
        scanf("%d", &qty);

        if (qty <= 0) {
            printf(BOLD "Jumlah tidak valid!\n" RESET);
            i--;
            continue;
        }

        OrderItem *item = &pesanan->items[pesanan->jumlahItem];
        item->kodeMenu = kodeMenu;
        strcpy(item->nama, namaMenu);
        item->harga = harga;
        item->qty = qty;
        item->subtotal = harga * qty;

        pesanan->total += item->subtotal;
        pesanan->jumlahItem++;

        printf(BOLD "> " RESET "%s x%d = Rp%d\n", namaMenu, qty, item->subtotal);
    }

    jumlahOrder++;

    printf("\n");
    printf(BOLD "╔══════════════════════════════╗\n" RESET);
    printf(BOLD "║   PESANAN BERHASIL DISIMPAN  ║\n" RESET);
    printf(BOLD "╚══════════════════════════════╝\n" RESET);
    printf(BOLD "Total Bayar : Rp%d\n" RESET, pesanan->total);

    pauseScreen();
}


void tampilDetailOrder(int idOrder) {
    clearScreen();

    if (idOrder <= 0 || idOrder > jumlahOrder) {
        printf("ID tidak valid\n");
        pauseScreen();
        return;
    }

    Order *pesanan = &daftarOrder[idOrder - 1];
    cetakStruk(stdout, pesanan);

    printf("\n1. Print Struk\n2. Selesai\n0. Kembali\nPilihan: ");

    int pilih;
    scanf("%d", &pilih);

    if (pilih == 1) printStruk(pesanan, idOrder - 1);
    else if (pilih == 2) hapusOrder(idOrder - 1);

    pauseScreen();
}

void tampilOrder() {
    clearScreen();

    if (jumlahOrder == 0) {
        printf(BOLD "Belum ada pesanan!\n" RESET);
        pauseScreen();
        return;
    }

    printf("\n");
    printf(BOLD "╔════════════════════════════════════════════╗\n" RESET);
    printf(BOLD "║               DAFTAR PESANAN               ║\n" RESET);
    printf(BOLD "╚════════════════════════════════════════════╝\n" RESET);

    printf(BOLD "┌────┬────────────────┬────────────┐\n" RESET);
    printf(BOLD "│ ID │ Nama Pembeli   │ Total      │\n" RESET);
    printf(BOLD "├────┼────────────────┼────────────┤\n" RESET);

    for (int i = 0; i < jumlahOrder; i++) {
        printf("│ %-2d │ %-14s │ Rp%-9d │\n", daftarOrder[i].idOrder, daftarOrder[i].namaOrder, daftarOrder[i].total);
    }

    printf(BOLD "└────┴────────────────┴────────────┘\n" RESET);

    int id;
    printf(BOLD "\nMasukkan ID pesanan (0 = batal) ➜ " RESET);
    scanf("%d", &id);

    if (id > 0 && id <= jumlahOrder) {
        tampilDetailOrder(id);
    }
}


void hapusOrder(int index) {
    if (index < 0 || index >= jumlahOrder) return;

    for (int i = index; i < jumlahOrder - 1; i++) daftarOrder[i] = daftarOrder[i + 1];

    memset(&daftarOrder[jumlahOrder - 1], 0, sizeof(Order));
    jumlahOrder--;

    printf("Pesanan dihapus\n");
}

void printStruk(Order *pesanan, int index) {
    char file[32];
    sprintf(file, "struk_%02d.txt", pesanan->idOrder);

    FILE *fp = fopen(file, "w");
    if (!fp) return;

    cetakStruk(fp, pesanan);
    fprintf(fp, "\nTerima kasih!\n");

    fclose(fp);
    printf("Struk dicetak: %s\n", file);

    hapusOrder(index);
}