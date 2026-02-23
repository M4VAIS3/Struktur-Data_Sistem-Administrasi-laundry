// Program utama aplikasi sistem administrasi laundry: LaundrYuk
#include <iostream>
#include <string>
#include "sistemLaundry.h"

using namespace std;

// Fungsi primitif untuk input dan menu yang digunakan dalam program
void menu();
Customer inputCustomer();
Layanan inputLayanan();
Transaksi inputTransaksi();

int main() {
    // deklarasi variabel list untuk customer, layanan, dan relasi
    ListCustomer LC;
    ListLayanan LL;
    ListRelasi LR;

    // buat list kosong untuk customer, layanan, dan relasi
    createListCustomer(LC);
    createListLayanan(LL);
    createListRelasi(LR);

    int pilihan; // variabel untuk menyimpan pilihan menu
    // loop menu hingga user memilih untuk keluar
    do {
        menu();
        cout << "Pilih menu: ";
        if (!(cin >> pilihan)) { // jika yang diinput bilangan bulat atau integer, maka
            cin.clear(); // bersihkan error pada cin untuk memulihkan cin ke keadaan semula
            cin.ignore(10000, '\n'); // mengabaikan karakter yang tersisa di input sampai menemukan newline atau maks di 10000 karakter
            pilihan = -1; // set pilihan ke nilai invalid
        }
        cin.ignore();

        switch (pilihan) {
            // Menu untuk menambah, menampilkan, mencari, dan menghapus customer 
            case 1: { // Tambah customer
                Customer c = inputCustomer();
                insertFirstCustomer(LC, c);
                cout << "\n[SUCCESS] Customer berhasil ditambahkan!\n";
                break;
            }
            case 2: { // Tampilkan semua customer
                cout << "\n";
                showAllCustomer(LC);
                break;
            }
            case 3: { // Cari customer
                string id;
                cout << "Masukkan ID customer yang dicari: ";
                getline(cin, id);
                elmCustomer* found = findCustomer(LC, id);
                if (found != nullptr) {
                    cout << "\n[DITEMUKAN] Customer dengan ID " << id << ":\n";
                    cout << "Nama      : " << found->info.namaCust << endl;
                    cout << "No. Telp  : " << found->info.noTelp << endl;
                    cout << "Alamat    : " << found->info.alamat << endl;
                    cout << "Membership: " << found->info.statusMember << endl;
                } else {
                    cout << "\n[TIDAK DITEMUKAN] Customer dengan ID " << id << " tidak ada.\n";
                }
                break;
            }
            case 4: { // Hapus customer
                string id;
                cout << "Masukkan ID customer yang akan dihapus: ";
                getline(cin, id);
                deleteCustomer(LC, id);
                cout << "\n[INFO] Jika customer dengan ID tersebut ada, maka telah dihapus.\n";
                break;
            }

            // Menu untuk menambah , menampilkan, mencari, dan menghapus layanan
            case 5: { // Tambah layanan
                Layanan l = inputLayanan();
                insertFirstLayanan(LL, l);
                cout << "\n[SUCCESS] Layanan berhasil ditambahkan!\n";
                break;
            }
            case 6: { // Tampilkan layanan
                cout << "\n";
                showAllLayanan(LL);
                break;
            }
            case 7: { // Cari layanan
                string kode;
                cout << "Masukkan kode layanan yang dicari: ";
                getline(cin, kode);
                elmLayanan* found = findLayanan(LL, kode);
                if (found != nullptr) {
                    cout << "\n[DITEMUKAN] Layanan dengan kode " << kode << ":\n";
                    cout << "Jenis Layanan : " << found->info.jenisLayanan << endl;
                    cout << "Kategori      : " << found->info.kategori << endl;
                    cout << "Harga         : Rp " << found->info.harga << endl;
                } else {
                    cout << "\n[TIDAK DITEMUKAN] Layanan dengan kode " << kode << " tidak ada.\n";
                }
                break;
            }
            case 8: { // Hapus layanan
                string kode;
                cout << "Masukkan kode layanan yang akan dihapus: ";
                getline(cin, kode);
                deleteLayanan(LL, kode);
                cout << "\n[INFO] Jika layanan dengan kode tersebut ada, maka telah dihapus.\n";
                break;
            }

            // Menu untuk menambah, menghapus, mengedittransaksi serta mengecek relasi dari customer dan layanan
            case 9: { // Tambah transaksi
                Transaksi t = inputTransaksi();
                string idCust, kodeLayanan;
                cout << "Masukkan ID customer untuk transaksi: ";
                getline(cin, idCust);
                cout << "Masukkan kode layanan untuk transaksi: ";
                getline(cin, kodeLayanan);

                elmCustomer* ec = findCustomer(LC, idCust);
                elmLayanan* el = findLayanan(LL, kodeLayanan);

                if (ec == nullptr) {
                    cout << "\n[ERROR] Customer tidak ditemukan. Silakan tambahkan customer terlebih dahulu.\n";
                } else if (el == nullptr) {
                    cout << "\n[ERROR] Layanan tidak ditemukan. Silakan tambahkan layanan terlebih dahulu.\n";
                } else {
                    t.totalHarga = t.berat * el->info.harga;
                    insertFirstRelasi(LR, t, ec, el);
                    cout << "\n[SUCCESS] Transaksi berhasil ditambahkan!\n";
                    cout << "Total Harga: Rp " << t.totalHarga << endl;
                }
                break;
            }
            case 10: { // Hapus transaksi
                string idT;
                cout << "Masukkan ID transaksi yang akan dihapus: ";
                getline(cin, idT);
                deleteRelasi(LR, idT);
                cout << "\n[INFO] Jika transaksi dengan ID tersebut ada, maka telah dihapus.\n";
                break;
            }
            case 11: { // Edit relasi
                string idT, newCustId, newLayananKode;
                cout << "Masukkan ID transaksi yang akan diedit: ";
                getline(cin, idT);
                cout << "Masukkan ID customer baru (kosongkan jika tidak ingin mengganti): ";
                getline(cin, newCustId);
                cout << "Masukkan kode layanan baru (kosongkan jika tidak ingin mengganti): ";
                getline(cin, newLayananKode);

                elmCustomer* nc = nullptr;
                elmLayanan* nl = nullptr;

                if (!newCustId.empty()) {
                    nc = findCustomer(LC, newCustId);
                    if (nc == nullptr) {
                        cout << "\n[ERROR] Customer baru tidak ditemukan.\n";
                        break;
                    }
                }

                if (!newLayananKode.empty()) {
                    nl = findLayanan(LL, newLayananKode);
                    if (nl == nullptr) {
                        cout << "\n[ERROR] Layanan baru tidak ditemukan.\n";
                        break;
                    }
                }

                editRelasi(LR, idT, nc, nl);
                cout << "\n[SUCCESS] Relasi berhasil diperbarui!\n";
                break;
            }
            case 12: { // Cek relasi customer dan layanan
                string idC, kodeL;
                cout << "Masukkan ID customer: ";
                getline(cin, idC);
                cout << "Masukkan kode layanan: ";
                getline(cin, kodeL);
                
                if (findRelasiCustomerLayanan(LR, idC, kodeL)) {
                    cout << "\n[DITEMUKAN] Customer " << idC << " dan Layanan " << kodeL << " memiliki relasi transaksi.\n";
                } else {
                    cout << "\n[TIDAK DITEMUKAN] Customer " << idC << " dan Layanan " << kodeL << " tidak memiliki relasi.\n";
                }
                break;
            }

            // Menu untuk menampilkan relasi dari customer ke layanan, layanan ke customer, dll.
            case 13: { // Show layanan dari customer tertentu
                string idC;
                cout << "Masukkan ID customer: ";
                getline(cin, idC);
                cout << "\n";
                showLayananDariCustomer(LR, idC);
                break;
            }
            case 14: { // Show customer dari layanan tertentu
                string kodeL;
                cout << "Masukkan kode layanan: ";
                getline(cin, kodeL);
                cout << "\n";
                showCustomerDariLayanan(LR, kodeL);
                break;
            }
            case 15: { // Show semua customer dengan layanan
                cout << "\n";
                showAllCustomerwithLayanan(LR, LC);
                break;
            }
            case 16: { // Show semua layanan dengan customer
                cout << "\n";
                showAllLayananwithCustomer(LL, LR);
                break;
            }

            // Menu untuk menghitung jumlah layanan dari customer, customer dari layanan, dll.
            case 17: { // Count layanan dari customer tertentu
                string idC;
                cout << "Masukkan ID customer: ";
                getline(cin, idC);
                int jumlah = countLayananDariCustomer(LR, idC);
                cout << "\n[HASIL] Jumlah transaksi layanan dari customer " << idC << ": " << jumlah << endl;
                break;
            }
            case 18: { // Count customer dari layanan tertentu
                string kodeL;
                cout << "Masukkan kode layanan: ";
                getline(cin, kodeL);
                int jumlah = countCustomerDariLayanan(LR, kodeL);
                cout << "\n[HASIL] Jumlah customer yang menggunakan layanan " << kodeL << ": " << jumlah << endl;
                break;
            }
            case 19: { // Count layanan tanpa customer
                int jumlah = countLayanantanpaCust(LR, LL);
                cout << "\n[HASIL] Jumlah layanan yang belum pernah digunakan: " << jumlah << endl;
                break;
            }
            case 20: { // Count customer tanpa layanan
                int jumlah = countCusttanpaLayanan(LR, LC);
                cout << "\n[HASIL] Jumlah customer yang belum pernah transaksi: " << jumlah << endl;
                break;
            }

            case 0:
                cout << "\n====================================\n";
                cout << "Terima kasih telah menggunakan LaundrYuk!\n";
                cout << "====================================\n";
                break;
            default:
                cout << "\n[ERROR] Pilihan tidak valid! Silakan pilih menu yang tersedia.\n";
        }
        
        if (pilihan != 0) {
            cout << "\n====================================\n";
        }
    } while (pilihan != 0);

    return 0;
}

void menu() {
    cout << "\n====================================\n";
    cout << "    SISTEM ADMINISTRASI LAUNDRYUK!!\n";
    cout << "====================================\n";
    cout << "\n--- MENU CUSTOMER ---\n";
    cout << "1.  Tambah Customer\n";
    cout << "2.  Tampilkan Semua Customer\n";
    cout << "3.  Cari Customer\n";
    cout << "4.  Hapus Customer\n";
    
    cout << "\n--- MENU LAYANAN ---\n";
    cout << "5.  Tambah Layanan\n";
    cout << "6.  Tampilkan Semua Layanan\n";
    cout << "7.  Cari Layanan\n";
    cout << "8.  Hapus Layanan\n";
    
    cout << "\n--- MENU TRANSAKSI ---\n";
    cout << "9.  Tambah Transaksi (Relasi)\n";
    cout << "10. Hapus Transaksi\n";
    cout << "11. Edit Relasi Transaksi\n";
    cout << "12. Cek Relasi Customer & Layanan\n";
    
    cout << "\n--- MENU TAMPILAN RELASI ---\n";
    cout << "13. Tampilkan Layanan dari Customer Tertentu\n";
    cout << "14. Tampilkan Customer dari Layanan Tertentu\n";
    cout << "15. Tampilkan Semua Customer dengan Layanan\n";
    cout << "16. Tampilkan Semua Layanan dengan Customer\n";
    
    cout << "\n--- MENU STATISTIK ---\n";
    cout << "17. Hitung Jumlah Transaksi Customer\n";
    cout << "18. Hitung Jumlah Pengguna Layanan\n";
    cout << "19. Hitung Layanan Tanpa Customer\n";
    cout << "20. Hitung Customer Tanpa Transaksi\n";
    
    cout << "\n0.  Keluar\n";
    cout << "====================================\n";
}

Customer inputCustomer() {
    Customer c;
    cout << "\n--- Input Data Customer ---\n";
    cout << "Masukkan ID Customer: "; 
    getline(cin, c.idCust);
    cout << "Masukkan Nama Customer: "; 
    getline(cin, c.namaCust);
    cout << "Masukkan No. Telp: "; 
    getline(cin, c.noTelp);
    cout << "Masukkan Alamat: "; 
    getline(cin, c.alamat);
    cout << "Masukkan Status Member (Regular/Silver/Gold/Platinum): "; 
    getline(cin, c.statusMember);
    return c;
}

Layanan inputLayanan() {
    Layanan l;
    cout << "\n--- Input Data Layanan ---\n";
    cout << "Masukkan Kode Layanan: "; 
    getline(cin, l.kodeLayanan);
    cout << "Masukkan Jenis Layanan (Cuci Kering/Cuci Setrika/Setrika/Express): "; 
    getline(cin, l.jenisLayanan);
    cout << "Masukkan Kategori Pakaian (Reguler/Bed Cover/Selimut/Handuk): "; 
    getline(cin, l.kategori);
    cout << "Masukkan Harga per KG: Rp "; 
    cin >> l.harga; 
    cin.ignore();
    return l;
}

Transaksi inputTransaksi() {
    Transaksi t;
    cout << "\n--- Input Data Transaksi ---\n";
    cout << "Masukkan ID Transaksi: "; 
    getline(cin, t.idTransaksi);
    cout << "Masukkan Tanggal Masuk (DD/MM/YYYY): "; 
    getline(cin, t.tanggalMasuk);
    cout << "Masukkan Tanggal Selesai (DD/MM/YYYY): "; 
    getline(cin, t.tanggalSelesai);
    cout << "Masukkan Berat (kg): "; 
    cin >> t.berat; 
    cin.ignore();
    t.totalHarga = 0; // akan dihitung otomatis
    cout << "Masukkan Status Transaksi (Proses/Selesai/Diambil): "; 
    getline(cin, t.statusTransaksi);
    return t;
}