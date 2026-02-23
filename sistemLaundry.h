// Header program Pengolahan Data Sistem Laundry - Kelompok 4
#include <iostream>
#include <string>
using namespace std;

// Struktur data customer sebagai list parent
struct Customer {
    string idCust;
    string namaCust;
    string noTelp;
    string alamat;
    string statusMember;
};

struct elmCustomer {
    Customer info;
    elmCustomer* next;
    elmCustomer* prev;
};

struct ListCustomer {
    elmCustomer* first;
};

// Struktur data Layanan Laundry sebagai list child
struct Layanan{
    string kodeLayanan;
    string jenisLayanan;
    string kategori;
    int harga; // harga per kg untuk pakaian reguler, per pcs untuk pakaian atau kategpori khusus
};

struct elmLayanan {
    Layanan info;
    elmLayanan* next;
};

struct ListLayanan {
    elmLayanan* first;
};

// Struktur data Transaksi sebagai list relasi antara list parent dan child
struct Transaksi {
    string idTransaksi;
    string tanggalMasuk;
    string tanggalSelesai;
    float berat;
    int totalHarga;
    string statusTransaksi;  
};

struct elmRelasi {
    Transaksi info;
    elmRelasi* next;
    elmCustomer* cust; // pointer ke elemen customer
    elmLayanan* layanan; // pointer ke elemen layanan
};

struct ListRelasi {
    elmRelasi* first;
};

// Deklarasi fungsi untuk list customer
void createListCustomer(ListCustomer &L);
void insertFirstCustomer(ListCustomer &L, Customer dataCust);
void deleteCustomer(ListCustomer &L, string idCust);
elmCustomer* findCustomer(ListCustomer L, string idCust);
void showAllCustomer(ListCustomer L);

// Deklarasi fungsi untuk list layanan
void createListLayanan(ListLayanan &L);
void insertFirstLayanan(ListLayanan &L, Layanan dataLayanan);
void deleteLayanan(ListLayanan &L, string kodeLayanan);
elmLayanan* findLayanan(ListLayanan L, string kodeLayanan);
void showAllLayanan(ListLayanan L);

// Deklarasi fungsi untuk list relasi
void createListRelasi(ListRelasi &L);
void insertFirstRelasi(ListRelasi &L, Transaksi dataTransaksi, elmCustomer* cust, elmLayanan* layanan);
void deleteRelasi(ListRelasi &L, string idTransaksi);
bool findRelasiCustomerLayanan(ListRelasi LR, string idCust, string kodeLayanan);

// Deklarasi fungsi show khusus dari list relasi
void showLayananDariCustomer(ListRelasi LR, string idCust);
void showCustomerDariLayanan(ListRelasi LR, string kodeLayanan);
void showAllCustomerwithLayanan(ListRelasi LR, ListCustomer LC);
void showAllLayananwithCustomer(ListLayanan LL, ListRelasi LR);

// Deklarasi fungsi count (hitung jumlah)
int countLayananDariCustomer(ListRelasi LR, string idCust);
int countCustomerDariLayanan(ListRelasi LR, string kodeLayanan);
int countLayanantanpaCust(ListRelasi LR, ListLayanan LL);
int countCusttanpaLayanan(ListRelasi LR, ListCustomer LC);

// Fungsi edit relasi yang  mengganti layanan dari customer dan sebaliknya
void editRelasi(ListRelasi &LR, string idTransaksi, elmCustomer* newCust, elmLayanan* newLayanan);