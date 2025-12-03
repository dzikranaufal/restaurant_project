#include <stdio.h>
#include <string.h>

typedef struct{
    int kode;
    char nama[100];
    int harga;
    char kategori[50];
} Menu;
Menu daftarMenu[50] = {
    {001, "Ayam Geprek sambal bawang", 15000, "Makanan"},
    {002, "Nasi Goreng Spesial", 20000, "Makanan"},
    {003, "Milkshake", 20000, "Minuman"},
    {004, "Sambal Cumi", 15000, "Makanan"},
    {005, "Cheescake Bluberry", 25000, "Dessert"},
    {006, "Orange Juice", 10000, "Minuman"}
};
int jumlah = 6;


void tampilData(){
    printf("\n===== Daftar Menu Restoran =====\n");
    for(int i = 0; i < jumlah; i++){
        printf("[%d] %s - Rp%d (%s)\n", 
            daftarMenu[i].kode, 
            daftarMenu[i].nama, 
            daftarMenu[i].harga, 
            daftarMenu[i].kategori);
    }
    printf("==================================");
}


void tambahData(Menu daftarMenu[], int *jumlah){
    printf("\n=== Tambah Menu ===\n");

    printf("Masukkan Kode        : ");
    scanf("%d", &daftarMenu[*jumlah].kode);

    printf("Masukkan Nama       : ");
    scanf(" %[^\n]s", daftarMenu[*jumlah].nama);

    printf("Masukkan Harga      : ");
    scanf("%d", &daftarMenu[*jumlah].harga);

    printf("Masukkan Kategori   : ");
    scanf(" %[^\n]s", daftarMenu[*jumlah].kategori);

    (*jumlah)++;
    printf("Menu berhasil ditambahkan!\n");
}


int main(){
    int pilih;
    int jumlah = 0;

    do{
    printf("\n=== MENU RESTORAN ===\n");
    printf("1. Tambah Data\n");
    printf("2. Tampil Data\n");
    printf("3. Hapus Data\n");
    printf("0. Keluar\n");
    printf("Pilih menu: ");
    scanf("%d", &pilih);
    
    switch (pilih){
    case 1:tambahData(daftarMenu, &jumlah);
        break;
    case 2:tampilData();
        break;
    case 0:
        printf("Program selesai.\n");
        break;

    default:
        printf("Pilihan tidak valid!!\n");
        break;
    }

    }while (pilih !=0);

    return 0;
}


