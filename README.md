# 🧺 LaundryYuk! - Sistem Administrasi Laundry

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Data Structures](https://img.shields.io/badge/Data_Structures-Multi--Linked_List-blue?style=for-the-badge)

## 📖 Deskripsi Proyek
**LaundryYuk!** adalah program aplikasi berbasis *Command Line Interface* (CLI) menggunakan bahasa C++. Proyek ini dikembangkan sebagai pemenuhan Tugas Besar mata kuliah Struktur Data. Sistem ini bertujuan untuk mendigitalisasi dan mempermudah pencatatan administrasi pada usaha *laundry*. Dimulai dari manajemen data pelanggan, layanan pakaian, hingga pencatatan transaksi yang menghubungkan keduanya.

## ⚙️ Struktur Data
Program ini menonjolkan implementasi **Multi-Linked List (MLL)** dengan pembagian struktur sebagai berikut:
- **Parent List (Double Linked List):** Menyimpan entitas utama program, yaitu data **Customer/Pelanggan**.
- **Child List (Single Linked List):** Menyimpan entitas sekunder, yaitu data **Layanan** yang tersedia dari usaha laundry.
- **List Relasi (Multi-Linked List):** Menghubungkan node Parent dan Child untuk mencatat riwayat transaksi secara dinamis dan terstruktur.


## ✨ Fitur Utama
```
-> Insert, Search, Update, dan Delete (CRUD) pada data Pelangga (List Parent).
-> Insert, Search, Update, dan Delete (CRUD) pada data Layanan (List Child).
-> Membuat, memutus, dan mencari relasi antara data Pelanggan dan Layanan.
-> Menampilkan seluruh relasi antara Pelanggan dengan Layanan yang digunakan.
-> Menghitung jumlah dari masing-masing relasi yakni, Pelanggan yang menggunakan Layanan (dan sebaliknya) serta Pelanggan yang belum menggunakan layanan (dan sebaliknya)
```

## 🚀 Cara Menjalankan Program
Pastikan kompilator C++ (seperti MinGW/GCC) sudah terpasang di komputermu.

1. *Clone repository* ini:
   ```bash
   git clone https://github.com/M4VAIS3/Struktur-Data_Sistem-Administrasi-laundry.git
    ```
2. Buka terminal
3. Lakukan kompilasi sistem dengan mengetik kode berikut:
    ```bash
    g++ main.cpp sistemLaundry.cpp -o LaundryYuk
    ```
4. Jalankan file executable, misal:
    ```bash
    ./LaundryYuk
    ```

## 📁 Struktur Direktori
- main.cpp : File utama yang berisi fungsi utama dan antarmuka program (CLI).
- sistemLaundry.h : File header yang berisi deklarasi _struct, pointer_, dan prototipe fungsi/prosedur.
- sistemLaundry.cpp : File implementasi logika struktur data dan fungsi operasi MLL.
- .gitignore : Berkas konfigurasi untuk mengabaikan _compiled binary_ (seperti .exe) agar tidak masuk ke _repository_.
- README.md : Dokumentasi informasi proyek.

## 👥 Tim Pengembang
```
- Michio Avryant Gervaise (103062430007)
- Syahrul Ramadhan (103062430017)
- Rahul Adiswara (103062400104)
```