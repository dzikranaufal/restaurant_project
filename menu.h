#ifndef MENU_H
#define MENU_H

#define MAX_MENU 50

typedef struct {
    int kode;
    char nama[100];
    int harga;
    char kategori[50];
} Menu;

typedef enum {
    SORT_NONE,
    SORT_HARGA_ASC,
    SORT_HARGA_DESC,
    SORT_NAMA_ASC,
    SORT_NAMA_DESC
} SortType;

extern Menu daftarMenu[50];
extern int jumlah;

void sortMenu(SortType type);
void tampilMenuPerKategori();

void menuController();
void tambahData();
void hapusData();
void editData();
void searchMenu();

#endif
