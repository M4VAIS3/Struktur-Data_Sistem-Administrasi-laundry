#include "sistemLaundry.h"
#include <iostream>
using namespace std;
//////////////////////////////
// LIST CUSTOMER (PARENT)
//////////////////////////////
// Prosedur untuk membuat list customer kosong
void createListCustomer(ListCustomer &L)
{
    L.first = nullptr;
};

// Prosedur untuk menambahkan elemen baru di awal list customer
void insertFirstCustomer(ListCustomer &L, Customer data)
{
    // Alokasikan data ke elemen baru
    elmCustomer *newElm = new elmCustomer;
    newElm->info = data;
    newElm->next = L.first;
    newElm->prev = nullptr;

    if (L.first != nullptr)
    {
        L.first->prev = newElm; // jika bagian awal list terisi, prev dari elemen pertama diatur ke elemen baru
    }
    L.first = newElm; // perbarui elemen baru sebagai elemen pertama
};

void deleteCustomer(ListCustomer &L, string idCust)
{
    elmCustomer *current = L.first; // deklarasi pointer sementara untuk traversing list
    // Traverse list dilakukan jika elemen yang dipointing tidak kosong
    while (current != nullptr)
    {
        if (current->info.idCust == idCust)
        { // Jika idCust ditemukan
            // Jika elemen yang akan dihapus adalah elemen pertama
            if (current->prev == nullptr)
            {
                L.first = current->next; // jika prev dari elemen pertama adalah nullptr, maka perbarui first ke elemen berikutnya
                if (L.first != nullptr)
                {
                    L.first->prev = nullptr; // jika elemen berikutnya tidak kosong, atur prev dari elemen berikutnya ke nullptr
                }
            }
            else
            {
                // Jika elemen yang akan dihapus bukan elemen pertama
                current->prev->next = current->next; // Hubungkan prev dengan next menjadi satu
                if (current->next != nullptr)
                {
                    current->next->prev = current->prev; // jika next dari elemen yang akan dihapus tidak kosong, atur prev dari next ke prev
                }
            }
            delete current; // Hapus elemen yang ditemukan
            return;
        }
        current = current->next; // Lanjutkan ke elemen berikutnya
    }
};

elmCustomer *findCustomer(ListCustomer L, string idCust)
{
    elmCustomer *current = L.first; // Pointer untuk traversing list
    while (current != nullptr)
    {
        if (current->info.idCust == idCust)
        {                   // Jika idCust ditemukan
            return current; // Kembalikan pointer ke elemen yang ditemukan
        }
        current = current->next; // Lanjutkan ke elemen berikutnya
    }
    return nullptr; // Jika tidak ditemukan, kembalikan nullptr
};

void showAllCustomer(ListCustomer L)
{
    elmCustomer *current = L.first; // Pointer untuk traversing list
    // Jika list kosong, maka akan menampilkan pesan
    if (current == nullptr)
    {
        std::cout << "List customer kosong." << std::endl;
        return;
    }
    cout << "Daftar Customer:" << endl;
    while (current != nullptr)
    {
        cout << "ID: " << current->info.idCust
             << ", Nama: " << current->info.namaCust
             << ", No. Telp: " << current->info.noTelp
             << ", Alamat: " << current->info.alamat
             << ", Status Member: " << current->info.statusMember << endl;
        current = current->next; // Lanjutkan ke elemen berikutnya
    }
};

//////////////////////////////
// LIST LAYANAN (CHILD)
//////////////////////////////

void createListLayanan(ListLayanan &L)
{
    L.first = nullptr;
}

void insertFirstLayanan(ListLayanan &L, Layanan dataLayanan)
{
    elmLayanan *P = new elmLayanan;
    P->info = dataLayanan;
    P->next = L.first;
    L.first = P;
}

void deleteLayanan(ListLayanan &L, string kodeLayanan)
{
    if (L.first == nullptr)
        return;

    elmLayanan *P = L.first, *prev = nullptr;

    while (P != nullptr && P->info.kodeLayanan != kodeLayanan)
    {
        prev = P;
        P = P->next;
    }

    if (P != nullptr)
    {
        if (prev == nullptr)
        {
            L.first = P->next;
        }
        else
        {
            prev->next = P->next;
        }
        delete P;
    }
}

elmLayanan *findLayanan(ListLayanan L, string kodeLayanan)
{
    elmLayanan *P = L.first;
    while (P != nullptr)
    {
        if (P->info.kodeLayanan == kodeLayanan)
        {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

void showAllLayanan(ListLayanan L)
{
    elmLayanan *P = L.first;
    while (P != nullptr)
    {
        cout << "Kode Layanan      : " << P->info.kodeLayanan << endl;
        cout << "Jenis Layanan     : " << P->info.jenisLayanan << endl;
        cout << "Kategori Pakaian  : " << P->info.kategori << endl;
        cout << "Harga             : " << P->info.harga << endl;
        cout << "-----------------------------" << endl;
        P = P->next;
    }
}

//////////////////////////////
// LIST RELASI (TRANSAKSI)
//////////////////////////////

void createListRelasi(ListRelasi &L)
{
    L.first = nullptr;
}

void insertFirstRelasi(ListRelasi &L, Transaksi dataTransaksi, elmCustomer *cust, elmLayanan *layanan)
{
    elmRelasi *P = new elmRelasi;
    P->info = dataTransaksi;
    P->cust = cust;
    P->layanan = layanan;
    P->next = L.first;
    L.first = P;
}

void deleteRelasi(ListRelasi &L, string idTransaksi)
{
    if (L.first == nullptr)
        return;

    elmRelasi *P = L.first, *prev = nullptr;

    while (P != nullptr && P->info.idTransaksi != idTransaksi)
    {
        prev = P;
        P = P->next;
    }

    if (P != nullptr)
    {
        if (prev == nullptr)
        {
            L.first = P->next;
        }
        else
        {
            prev->next = P->next;
        }
        delete P;
    }
}

bool findRelasiCustomerLayanan(ListRelasi LR, string idCust, string kodeLayanan)
{
    elmRelasi *R = LR.first;
    while (R != nullptr)
    {
        if (R->cust != nullptr && R->layanan != nullptr &&
            R->cust->info.idCust == idCust && 
            R->layanan->info.kodeLayanan == kodeLayanan)
        {
            return true;
        }
        R = R->next;
    }
    return false;
}

void showLayananDariCustomer(ListRelasi LR, string idCust)
{
    elmRelasi *R = LR.first;
    bool found = false;

    cout << "Layanan yang digunakan Customer " << idCust << ":\n";

    while (R != nullptr)
    {
        if (R->cust != nullptr && R->cust->info.idCust == idCust)
        {
            cout << "- " << R->layanan->info.jenisLayanan
                 << " (Kode: " << R->layanan->info.kodeLayanan << ")"
                 << ", Berat: " << R->info.berat << " kg"
                 << ", Total Harga: " << R->info.totalHarga << endl;
            found = true;
        }
        R = R->next;
    }

    if (!found)
        cout << "Tidak ada layanan yang digunakan customer ini.\n";
}

void showCustomerDariLayanan(ListRelasi LR, string kodeLayanan)
{
    elmRelasi *R = LR.first;
    bool found = false;

    cout << "Customer yang pernah menggunakan layanan " << kodeLayanan << ":\n";

    while (R != nullptr)
    {
        if (R->layanan != nullptr && R->layanan->info.kodeLayanan == kodeLayanan)
        {
            cout << "- " << R->cust->info.namaCust
                 << " (ID: " << R->cust->info.idCust << ")"
                 << ", Berat: " << R->info.berat << " kg"
                 << ", Total Harga: " << R->info.totalHarga << endl;
            found = true;
        }
        R = R->next;
    }

    if (!found)
        cout << "Belum ada customer yang memakai layanan ini.\n";
}

void showAllCustomerwithLayanan(ListRelasi LR, ListCustomer LC)
{
    elmCustomer *C = LC.first;

    if (C == nullptr)
    {
        cout << "List customer kosong.\n";
        return;
    }

    while (C != nullptr)
    {
        cout << "\nCustomer: " << C->info.namaCust
             << " (ID: " << C->info.idCust << ")\n";

        elmRelasi *R = LR.first;
        bool found = false;

        while (R != nullptr)
        {
            if (R->cust == C)
            {
                cout << "  - " << R->layanan->info.jenisLayanan
                     << " (Kode: " << R->layanan->info.kodeLayanan << ")"
                     << ", Berat: " << R->info.berat
                     << " kg, Total: " << R->info.totalHarga << endl;
                found = true;
            }
            R = R->next;
        }

        if (!found)
            cout << "  Tidak ada layanan yang digunakan.\n";

        C = C->next;
    }
}

void showAllLayananwithCustomer(ListLayanan LL, ListRelasi LR)
{
    elmLayanan *L = LL.first;

    if (L == nullptr)
    {
        cout << "List layanan kosong.\n";
        return;
    }

    while (L != nullptr)
    {
        cout << "\nLayanan: " << L->info.jenisLayanan
             << " (Kode: " << L->info.kodeLayanan << ")\n";

        elmRelasi *R = LR.first;
        bool found = false;

        while (R != nullptr)
        {
            if (R->layanan == L)
            {
                cout << "  - Customer: " << R->cust->info.namaCust
                     << " (ID: " << R->cust->info.idCust << ")"
                     << ", Berat: " << R->info.berat << " kg"
                     << ", Total: " << R->info.totalHarga << endl;
                found = true;
            }
            R = R->next;
        }

        if (!found)
            cout << "  Belum ada customer yang memakai layanan ini.\n";

        L = L->next;
    }
}

int countLayananDariCustomer(ListRelasi LR, string idCust)
{
    int count = 0;
    elmRelasi *R = LR.first;

    while (R != nullptr)
    {
        if (R->cust != nullptr && R->cust->info.idCust == idCust)
            count++;
        R = R->next;
    }

    return count;
}

int countCustomerDariLayanan(ListRelasi LR, string kodeLayanan)
{
    int count = 0;
    elmRelasi *R = LR.first;

    while (R != nullptr)
    {
        if (R->layanan != nullptr && R->layanan->info.kodeLayanan == kodeLayanan)
            count++;
        R = R->next;
    }

    return count;
}

int countLayanantanpaCust(ListRelasi LR, ListLayanan LL)
{
    int count = 0;
    elmLayanan *L = LL.first;

    while (L != nullptr)
    {
        bool hasRelasi = false;
        elmRelasi *R = LR.first;

        while (R != nullptr)
        {
            if (R->layanan == L)
            {
                hasRelasi = true;
                break;
            }
            R = R->next;
        }

        if (!hasRelasi)
            count++;

        L = L->next;
    }

    return count;
}

int countCusttanpaLayanan(ListRelasi LR, ListCustomer LC)
{
    int count = 0;
    elmCustomer *C = LC.first;

    while (C != nullptr)
    {
        bool hasRelasi = false;
        elmRelasi *R = LR.first;

        while (R != nullptr)
        {
            if (R->cust == C)
            {
                hasRelasi = true;
                break;
            }
            R = R->next;
        }

        if (!hasRelasi)
            count++;

        C = C->next;
    }

    return count;
}

void editRelasi(ListRelasi &LR, string idTransaksi, elmCustomer *newCust, elmLayanan *newLayanan)
{
    elmRelasi *R = LR.first;
    while (R != nullptr && R->info.idTransaksi != idTransaksi)
    {
        R = R->next;
    }
    
    if (R != nullptr)
    {
        if (newCust != nullptr)
            R->cust = newCust;
        if (newLayanan != nullptr)
            R->layanan = newLayanan;
    }
}