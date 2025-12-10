#include <stdio.h>
#include "order.h"
#include "menu.h" 
#include "utils.h" 

Order daftarOrder[50];
int jumlahOrder = 0;

int cariHargaMenu(int kodeMenu) {
    clearScreen();
    for (int i = 0; i < jumlah; i++) {
        if (daftarMenu[i].kode == kodeMenu) {
            return daftarMenu[i].harga;
        }
    }
    return -1; 
}

void tambahOrder() {
    clearScreen();
    int kode, qty;
    tampilData();
    printf("\n=== Tambah Pesanan ===\n");

    printf("Masukkan kode menu: ");
    scanf("%d", &kode);

    int harga = cariHargaMenu(kode);
    if (harga == -1) {
        printf("Kode menu tidak ditemukan!\n");
        return;
    }

    printf("Masukkan jumlah: ");
    scanf("%d", &qty);

    daftarOrder[jumlahOrder].kodeMenu = kode;
    daftarOrder[jumlahOrder].jumlah = qty;
    daftarOrder[jumlahOrder].subtotal = harga * qty;

    jumlahOrder++;

    printf("Pesanan berhasil ditambahkan!\n");
}

void tampilOrder() {
    clearScreen();
    printf("\n=== Daftar Pesanan ===\n");

    if (jumlahOrder == 0) {
        printf("Belum ada pesanan.\n");
        return;
    }

    int total = 0;

    for (int i = 0; i < jumlahOrder; i++) {
        printf("[%d] Kode Menu: %d | Jumlah: %d | Subtotal: Rp%d\n", i + 1, daftarOrder[i].kodeMenu, daftarOrder[i].jumlah, daftarOrder[i].subtotal);
        total += daftarOrder[i].subtotal;
    }

    printf("----------------------------------\n");
    printf("Total Bayar: Rp%d\n", total);
    pauseScreen();
}
