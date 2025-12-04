#ifndef ORDER_H
#define ORDER_H

typedef struct {
    int kodeMenu;
    int jumlah;
    int subtotal;
} Order;

extern Order daftarOrder[50];
extern int jumlahOrder;

// fungsi
void tambahOrder();
void tampilOrder();
int cariHargaMenu(int kodeMenu); // ambil harga dari menu.c (temenmu punya)

#endif
