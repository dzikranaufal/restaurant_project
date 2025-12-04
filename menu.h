#ifndef MENU_H
#define MENU_H

typedef struct {
    int kode;
    char nama[100];
    int harga;
    char kategori[50];
} Menu;

extern Menu daftarMenu[50];
extern int jumlah;

void tampilData();
void tambahData();

#endif
