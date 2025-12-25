#include <stdio.h>
#include <string.h>

#define MAX_KONTAK 100


//struktur data
typedef struct {
    char nama[50];
    char nomor[20];
    char email[50];
} Kontak;

Kontak daftarKontak[MAX_KONTAK];
int jumlahKontak = 0;

// simpen ke file (file processing)
void simpanKeFile() {
    FILE *file = fopen("kontak.txt", "w");
    for (int i = 0; i < jumlahKontak; i++) {
        fprintf(file, "%s;%s;%s\n", daftarKontak[i].nama, daftarKontak[i].nomor, daftarKontak[i].email);
    }
    fclose(file);
}

// Fungsi untuk membaca dari file (function kerja di file processing)
void bacaDariFile() {
    FILE *file = fopen("kontak.txt", "r");
    if (file == NULL) return;
    while (fscanf(file, "%[^;];%[^;];%[^\n]\n", daftarKontak[jumlahKontak].nama, daftarKontak[jumlahKontak].nomor, daftarKontak[jumlahKontak].email) != EOF) {
        jumlahKontak++;
    }
    fclose(file);
}

// nambah kontak baru ( selection)
void tambahKontak() {
    if (jumlahKontak >= MAX_KONTAK) {
        printf("Buku kontak penuh!\n");
        return;
    }
    printf("Nama: ");
    scanf(" %[^\n]", daftarKontak[jumlahKontak].nama);
    printf("Nomor: ");
    scanf(" %[^\n]", daftarKontak[jumlahKontak].nomor);
    printf("Email: ");
    scanf(" %[^\n]", daftarKontak[jumlahKontak].email);
    jumlahKontak++;
    simpanKeFile();
    printf("Kontak berhasil ditambahkan.\n");
}

// Tampilkan semua kontak (looping)
void tampilkanKontak() {
    printf("\nDaftar Kontak:\n");
    for (int i = 0; i < jumlahKontak; i++) {
        printf("%d. %s | %s | %s\n", i + 1, daftarKontak[i].nama, daftarKontak[i].nomor, daftarKontak[i].email);
    }
}

// Cari kontak berdasarkan nama (searching memakai )
void cariKontak() {
    char keyword[50];
    printf("Masukkan nama yang dicari: ");
    scanf(" %[^\n]", keyword);
    int ditemukan = 0;
    for (int i = 0; i < jumlahKontak; i++) {
        if (strstr(daftarKontak[i].nama, keyword)) {
            printf("Ditemukan: %s | %s | %s\n", daftarKontak[i].nama, daftarKontak[i].nomor, daftarKontak[i].email);
            ditemukan = 1;
        }
    }
    if (!ditemukan) {
        printf("Kontak tidak ditemukan.\n");
    }
}

// Edit kontak (file processing)
void editKontak() {
    tampilkanKontak();
    int index;
    printf("Pilih nomor kontak yang ingin diedit: ");
    scanf("%d", &index);
    index--;
    if (index >= 0 && index < jumlahKontak) {
        printf("Nama baru: ");
        scanf(" %[^\n]", daftarKontak[index].nama);
        printf("Nomor baru: ");
        scanf(" %[^\n]", daftarKontak[index].nomor);
        printf("Email baru: ");
        scanf(" %[^\n]", daftarKontak[index].email);
        simpanKeFile();
        printf("Kontak berhasil diperbarui.\n");
    } else {
        printf("Indeks tidak valid.\n");
    }
}

// Hapus kontak (file processing)
void hapusKontak() {
    tampilkanKontak();
    int index;
    printf("Pilih nomor kontak yang ingin dihapus: ");
    scanf("%d", &index);
    index--;
    if (index >= 0 && index < jumlahKontak) {
        for (int i = index; i < jumlahKontak - 1; i++) {
            daftarKontak[i] = daftarKontak[i + 1];
        }
        jumlahKontak--;
        simpanKeFile();
        printf("Kontak berhasil dihapus.\n");
    } else {
        printf("Indeks tidak valid.\n");
    }
}

// Urutkan kontak berdasarkan nama (bubble sort)
void urutkanKontak() {
    for (int i = 0; i < jumlahKontak - 1; i++) {
        for (int j = 0; j < jumlahKontak - i - 1; j++) {
            if (strcmp(daftarKontak[j].nama, daftarKontak[j + 1].nama) > 0) {
                Kontak temp = daftarKontak[j];
                daftarKontak[j] = daftarKontak[j + 1];
                daftarKontak[j + 1] = temp;
            }
        }
    }
    printf("Kontak berhasil diurutkan berdasarkan nama.\n");
}

int main() {
    bacaDariFile();
    int pilihan;
    do {
        printf("\n=== Aplikasi Manajemen Kontak ===\n");
        printf("1. Tampilkan Kontak\n");
        printf("2. Tambah Kontak\n");
        printf("3. Cari Kontak\n");
        printf("4. Edit Kontak\n");
        printf("5. Hapus Kontak\n");
        printf("6. Urutkan Kontak\n");
        printf("7. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: tampilkanKontak(); break;
            case 2: tambahKontak(); break;
            case 3: cariKontak(); break;
            case 4: editKontak(); break;
            case 5: hapusKontak(); break;
            case 6: urutkanKontak(); break;
            case 7: printf("Terima kasih telah menggunakan aplikasi ini.\n"); break;
            default: printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 7);

    return 0;
}