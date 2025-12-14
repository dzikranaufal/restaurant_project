#ifndef ORDER_H
#define ORDER_H

#define MAX_ORDER 50
#define MAX_ORDER_ITEMS 50

typedef struct {
    int kodeMenu;
    char nama[100];
    int harga;
    int qty;
    int subtotal;
} OrderItem;

typedef struct {
    int idOrder;
    OrderItem items[MAX_ORDER_ITEMS];
    int jumlahItem;
    int total;
} Order;

extern Order daftarOrder[MAX_ORDER];
extern int jumlahOrder;

int cariHargaMenu(int kodeMenu);

void tambahOrder(); 
void tampilOrder(); 
void tampilRingkasanOrder();
void tampilDetailOrder(int idOrder);
void printStruk(Order *pesanan, int index);  
void hapusOrder(int index);  


#endif