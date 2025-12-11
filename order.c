#include <stdio.h>
#include <string.h>
#include <time.h>
#include "order.h"
#include "menu.h" 
#include "utils.h" 

Order daftarOrder[MAX_ORDER];
int jumlahOrder = 0;

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
        printf("Maaf, kapasitas pesanan sudah penuh!\n");
        pauseScreen();
        return;
    }
    
    printf("=== TAMBAH PESANAN BARU ===\n\n");
    tampilData();
    printf("\n");
    
    int indexKosong = -1;
    for (int i = 0; i < MAX_ORDER; i++) {
        if (daftarOrder[i].idOrder == 0) {
            indexKosong = i;
            break;
        }
    }
    
    if (indexKosong == -1) {
        printf("Tidak ada slot pesanan yang tersedia!\n");
        pauseScreen();
        return;
    }
    
    Order *pesananBaru = &daftarOrder[indexKosong];
    pesananBaru->idOrder = indexKosong + 1;
    pesananBaru->jumlahItem = 0;
    pesananBaru->total = 0;
    
    int jumlahJenisMenu;
    printf("Berapa jenis menu yang ingin dipesan? (maksimal %d): ", MAX_ORDER_ITEMS);
    scanf("%d", &jumlahJenisMenu);
    
    if (jumlahJenisMenu <= 0 || jumlahJenisMenu > MAX_ORDER_ITEMS) {
        printf("Jumlah jenis menu tidak valid!\n");
        pauseScreen();
        return;
    }
    
    for (int i = 0; i < jumlahJenisMenu; i++) {
        printf("\n--- Item ke-%d ---\n", i + 1);
        
        int kodeMenu;
        printf("Masukkan kode menu: ");
        scanf("%d", &kodeMenu);
        
        int hargaMenu = cariHargaMenu(kodeMenu);
        if (hargaMenu == -1) {
            printf("Kode menu tidak ditemukan! Coba lagi.\n");
            i--;
            continue;
        }
        
        char namaMenu[100] = "Tidak Diketahui";
        for (int j = 0; j < jumlah; j++) {
            if (daftarMenu[j].kode == kodeMenu) {
                strcpy(namaMenu, daftarMenu[j].nama);
                break;
            }
        }
        
        int jumlah;
        printf("Masukkan jumlah pesanan: ");
        scanf("%d", &jumlah);
        
        if (jumlah <= 0) {
            printf("Jumlah harus lebih dari 0! Coba lagi.\n");
            i--;
            continue;
        }
        
        int subtotal = hargaMenu * jumlah;
        
        int indexItem = pesananBaru->jumlahItem;
        pesananBaru->items[indexItem].kodeMenu = kodeMenu;
        strcpy(pesananBaru->items[indexItem].nama, namaMenu);
        pesananBaru->items[indexItem].harga = hargaMenu;
        pesananBaru->items[indexItem].qty = jumlah;
        pesananBaru->items[indexItem].subtotal = subtotal;
        
        pesananBaru->total += subtotal;
        pesananBaru->jumlahItem++;
        
        printf("✓ %s x%d = Rp%d\n", namaMenu, jumlah, subtotal);
    }
    
    jumlahOrder++;
    printf("\n==== PESANAN BERHASIL DITAMBAHKAN ====\n");
    printf("ID Pesanan: %d\n", pesananBaru->idOrder);
    printf("Total Harga: Rp%d\n", pesananBaru->total);
    
    pauseScreen();
}

void tampilRingkasanOrder() {
    clearScreen();
    printf("=== RINGKASAN SEMUA PESANAN ===\n\n");
    
    if (jumlahOrder == 0) {
        printf("Belum ada pesanan yang dibuat.\n");
        pauseScreen();
        return;
    }
    
    printf("ID Pesanan | Jumlah Item | Total Harga\n");
    printf("-----------|-------------|------------\n");
    
    int adaPesanan = 0;
    for (int i = 0; i < MAX_ORDER; i++) {
        if (daftarOrder[i].idOrder != 0) {
            printf("%10d | %11d | Rp%d\n",  daftarOrder[i].idOrder,  daftarOrder[i].jumlahItem,  daftarOrder[i].total);
            adaPesanan = 1;
        }
    }
    
    if (!adaPesanan) {
        printf("Tidak ada pesanan yang aktif.\n");
    }
    
    pauseScreen();
}

void tampilDetailOrder(int idOrder) {
    clearScreen();
    
    if (idOrder <= 0 || idOrder > MAX_ORDER) {
        printf("ID pesanan tidak valid!\n");
        pauseScreen();
        return;
    }
    
    int ditemukan = 0;
    int indexPesanan = -1;
    
    for (int i = 0; i < MAX_ORDER; i++) {
        if (daftarOrder[i].idOrder == idOrder) {
            ditemukan = 1;
            indexPesanan = i;
            break;
        }
    }
    
    if (!ditemukan) {
        printf("Pesanan dengan ID %d tidak ditemukan!\n", idOrder);
        pauseScreen();
        return;
    }
    
    Order *pesanan = &daftarOrder[indexPesanan];
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    
    int pajak = pesanan->total * 10 / 100;
    int totalDenganPajak = pesanan->total + pajak;
    
    printf("====================\n");
    printf("      Cashier\n");
    printf("====================\n");
    printf("id:%02d\n", pesanan->idOrder);
    printf("time:%02d/%02d/%04d\n", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
    printf("====================\n");
    
    for (int i = 0; i < pesanan->jumlahItem; i++) {
        OrderItem *item = &pesanan->items[i];
        char namaTampil[15];
    
        strncpy(namaTampil, item->nama, 14);
        namaTampil[14] = '\0';
        printf("%d %-14s%7d\n", item->qty, namaTampil, item->subtotal);
    }
    
    printf("====================\n");
    printf("SUBTOTAL%13d\n", pesanan->total);
    printf("PB%19d\n", pajak);
    printf("====================\n");
    printf("TOTAL%16d\n", totalDenganPajak);
    printf("\n");
    printf("Terima kasih!\n");
    printf("PILIH OPSI:\n");
    printf("1. PRINT STRUK (buat file .txt dan hapus pesanan)\n");
    printf("2. SELESAI (hapus pesanan tanpa print)\n");
    printf("3. KEMBALI (biarkan pesanan tetap ada)\n");
    printf("Pilihan: ");
    
    int pilihan;
    scanf("%d", &pilihan);
    
    switch(pilihan) {
        case 1: 
            printStrukKeFile(pesanan, indexPesanan);
            break;
            
        case 2: 
            hapusPesananDariArray(indexPesanan);
            break;
            
        case 3:
            printf("Pesanan tetap disimpan.\n");
            break;
            
        default:
            printf("Pilihan tidak valid!\n");
    }
    pauseScreen();
}

void tampilOrder() {
    clearScreen();
    printf("=== LIHAT PESANAN ===\n\n");
    
    if (jumlahOrder == 0) {
        printf("Belum ada pesanan.\n");
        pauseScreen();
        return;
    }
    
    printf("Daftar Pesanan Aktif:\n");
    for (int i = 0; i < MAX_ORDER; i++) {
        if (daftarOrder[i].idOrder != 0) {
            printf("[ID %d] Items: %d | Total: Rp%d\n", daftarOrder[i].idOrder, daftarOrder[i].jumlahItem, daftarOrder[i].total);
        }
    }
    
    int idYangDicari;
    printf("\nMasukkan ID pesanan untuk melihat detail (0 untuk batal): ");
    scanf("%d", &idYangDicari);
    
    if (idYangDicari != 0) {
        tampilDetailOrder(idYangDicari);  
    }
}

void hapusPesananDariArray(int index) {
    if (index < 0 || index >= MAX_ORDER) {
        printf("Index tidak valid!\n");
        return;
    }
    
    if (daftarOrder[index].idOrder == 0) {
        printf("Pesanan sudah tidak ada!\n");
        return;
    }
    
    printf("Menghapus pesanan ID: %02d...\n", daftarOrder[index].idOrder);
    
    daftarOrder[index].idOrder = 0;
    daftarOrder[index].jumlahItem = 0;
    daftarOrder[index].total = 0;
    
    for (int i = 0; i < MAX_ORDER_ITEMS; i++) {
        daftarOrder[index].items[i].kodeMenu = 0;
        daftarOrder[index].items[i].nama[0] = '\0';
        daftarOrder[index].items[i].harga = 0;
        daftarOrder[index].items[i].qty = 0;
        daftarOrder[index].items[i].subtotal = 0;
    }
    
    jumlahOrder--;
    
    printf("✓ Pesanan berhasil dihapus!\n");
}

void printStrukKeFile(Order *pesanan, int index) {
    // Buat nama file
    char filename[50];
    sprintf(filename, "struk_%02d.txt", pesanan->idOrder);
    
    // Buka file untuk ditulis
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Gagal membuat file struk!\n");
        return;
    }
    
    // Dapatkan waktu
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    int pajak = pesanan->total * 10 / 100;
    int totalDenganPajak = pesanan->total + pajak;
    
    // Tulis struk ke file
    fprintf(file, "====================\n");
    fprintf(file, "      Cashier\n");
    fprintf(file, "====================\n");
    fprintf(file, "id:%02d\n", pesanan->idOrder);
    fprintf(file, "time:%02d/%02d/%04d %02d:%02d\n", 
            local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
            local->tm_hour, local->tm_min);
    fprintf(file, "====================\n");
    
    for (int i = 0; i < pesanan->jumlahItem; i++) {
        OrderItem *item = &pesanan->items[i];
        fprintf(file, "%d %-14s%7d\n", 
                item->qty, item->nama, item->subtotal);
    }
    
    fprintf(file, "====================\n");
    fprintf(file, "SUBTOTAL%13d\n", pesanan->total);
    fprintf(file, "PB%19d\n", pajak);
    fprintf(file, "====================\n");
    fprintf(file, "TOTAL%16d\n", totalDenganPajak);
    fprintf(file, "====================\n");
    fprintf(file, "\nTerima kasih atas kunjungan Anda!\n");
    
    fclose(file);
    
    printf("\nSTRUK berhasil dicetak ke file: %s\n", filename);
    printf("Pesanan akan dihapus dari sistem...\n");
    
    hapusPesananDariArray(index);
}