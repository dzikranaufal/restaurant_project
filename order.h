#ifndef ORDER_H
#define ORDER_H

typedef struct {
    int idOrder;
    int kodeMenu;
    int jumlah;
    int total;
} Order;

extern Order daftarOrder[50];
extern int jumlahOrder;

void tambahOrder();
void tampilOrder();
int cariHargaMenu(int kodeMenu); 

#endif