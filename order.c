#include <stdio.h>
#include <string.h>
#include <time.h>
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
        printf("Kapasitas pesanan sudah penuh\n");
        pauseScreen();
        return;
    }

    printf("=== TAMBAH PESANAN BARU ===\n\n");

    Order *pesanan = &daftarOrder[jumlahOrder];
    memset(pesanan, 0, sizeof(Order));

    printf("Masukan nama pembeli: ");
    scanf(" %[^\n]", pesanan->namaOrder);
    
    tampilMenuPerKategori();
    
    pesanan->idOrder = jumlahOrder + 1;

    int jenisMenu;
    printf("Berapa jenis menu yang ingin dipesan? (maks %d): ", MAX_ORDER_ITEMS);
    scanf("%d", &jenisMenu);

    if (jenisMenu <= 0 || jenisMenu > MAX_ORDER_ITEMS) {
        printf("Jumlah tidak valid\n");
        pauseScreen();
        return;
    }

    for (int i = 0; i < jenisMenu; i++) {
        int kodeMenu, qty;
        printf("\nItem ke-%d\n", i + 1);
        printf("Kode menu: ");
        scanf("%d", &kodeMenu);

        int harga = cariHargaMenu(kodeMenu);
        if (harga == -1) {
            printf("Kode menu tidak ditemukan!\n");
            i--;
            continue;
        }

        char namaMenu[100];
        for (int j = 0; j < jumlah; j++) {
            if (daftarMenu[j].kode == kodeMenu) {
                strcpy(namaMenu, daftarMenu[j].nama);
                break;
            }
        }

        printf("Jumlah pesanan: ");
        scanf("%d", &qty);
        if (qty <= 0) {
            printf("Jumlah tidak valid!\n");
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

        printf("%s x%d = Rp%d\n", namaMenu, qty, item->subtotal);
    }

    jumlahOrder++;
    printf("\nPesanan berhasil ditambahkan!\n");
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
        printf("Belum ada pesanan\n");
        pauseScreen();
        return;
    }

    printf("ID | Nama Pembeli | Total\n");
    printf("---------------------------\n");

    for (int i = 0; i < jumlahOrder; i++) {
        printf("%2d | %-12s | Rp.%d\n", daftarOrder[i].idOrder, daftarOrder[i].namaOrder, daftarOrder[i].total);
    }

    int id;
    printf("\nMasukan ID pesanan (0 batal): ");
    scanf("%d", &id);

    if (id > 0 && id <= jumlahOrder)
    tampilDetailOrder(id);
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