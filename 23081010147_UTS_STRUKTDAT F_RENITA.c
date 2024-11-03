#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 20
#define MAX_MAHASISWA 20

typedef struct Mahasiswa {
    char nama[MAX_NAME];
    char jenis_kelamin;
    struct Mahasiswa* next;
    struct Mahasiswa* prev;
} Mahasiswa;

Mahasiswa* head = NULL;
Mahasiswa* tail = NULL;

int ada_cindy() {
    Mahasiswa* current = head;
    if (current != NULL) {
        do {
            if (strcmp(current->nama, "Cindy") == 0) {
                return 1;
            }
            current = current->next;
        } while (current != head);
    }
    return 0;
}

int cindy_dapat_ditambahkan() {
    Mahasiswa* current = head;
    if (current != NULL) {
        do {
            if (current->jenis_kelamin == 'L' || current->jenis_kelamin == 'l') {
                return 0;
            }
            current = current->next;
        } while (current != head);
    }
    return 1;
}

void tambah_mahasiswa(char* nama, char jenis_kelamin) {
    if (strcmp(nama, "Cindy") == 0 && (jenis_kelamin == 'P' || jenis_kelamin == 'p')) {
        if (ada_cindy()) {
            printf("Mahasiswa '%s' sudah ada.\n", nama);
            return; // Cindy sudah ada, tidak perlu ditambahkan lagi
        }
        if (!cindy_dapat_ditambahkan()) {
            printf("Mahasiswa '%s' tidak bisa ditambahkan karena ada laki-laki di sampingnya.\n", nama);
            return;
        }
    }

    if (strlen(nama) > MAX_NAME) {
        printf("Lingkaran sudah penuh, nama tidak boleh lebih dari %d karakter.\n", MAX_NAME);
        return;
    }

    int count = 0;
    Mahasiswa* current = head;
    if (current != NULL) {
        do {
            count++;
            current = current->next;
        } while (current != head);
    }

    if (count >= MAX_MAHASISWA) {
        printf("Lingkaran sudah penuh, tidak bisa menambahkan mahasiswa baru.\n");
        return;
    }

    if (strcmp(nama, "irsyad") == 0) {
        current = head;
        if (current != NULL) {
            do {
                if (strcmp(current->nama, "arsyad") != 0) {
                    printf("Mahasiswa '%s' tidak bisa ditambahkan karena tidak ada arsyad di sampingnya.\n", nama);
                    return;
                }
                current = current->next;
            } while (current != head);
        }
    }

    Mahasiswa* new_mhs = (Mahasiswa*)malloc(sizeof(Mahasiswa));
    if (new_mhs == NULL) {
        printf("Alokasi memori gagal.\n");
        return;
    }
    strcpy(new_mhs->nama, nama);
    new_mhs->jenis_kelamin = jenis_kelamin;

    if (head == NULL) {
        head = tail = new_mhs;
        new_mhs->next = new_mhs->prev = new_mhs;
    } else {
        new_mhs->next = head;
        new_mhs->prev = tail;
        tail->next = new_mhs;
        head->prev = new_mhs;
        tail = new_mhs;
    }
    printf("'%s' berhasil ditambahkan.\n", nama);
}

void hapus_mahasiswa(char* nama) {
    if (head == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }
    Mahasiswa* current = head;
    do {
        if (strcmp(current->nama, nama) == 0) {
            if (current == head && current == tail) {
                free(current);
                head = tail = NULL;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                if (current == head) head = current->next;
                if (current == tail) tail = current->prev;
                free(current);
            }
            printf("'%s' berhasil dihapus.\n", nama);
            return;
        }
        current = current->next;
    } while (current != head);
    printf("'%s' tidak ditemukan.\n", nama);
}

void tampilkan_lingkaran() {
    if (head == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }
    Mahasiswa* current = head;
    printf("Lingkaran Besar:\n");
    do {
        printf("%s (% c)", current->nama, current->jenis_kelamin);
        current = current->next;
        if (current != head) {
            printf(" - ");
        }
    } while (current != head);
    printf("\n");
}

void pisahkan_lingkaran() {
    if (head == NULL) {
        printf("Lingkaran kosong, tidak bisa dipisahkan.\n");
        return;
    }

    printf("Lingkaran Mahasiswa:\n");
    Mahasiswa* current = head;
    int found_male = 0;

    do {
        if (current->jenis_kelamin == 'L' || current->jenis_kelamin == 'l') {
            printf("%s ", current->nama);
            found_male = 1;
            current = current->next;
            while (current != head && (current->jenis_kelamin == 'L' || current->jenis_kelamin == 'l')) {
                printf("- %s ", current->nama);
                current = current->next;
            }
        } else {
            current = current->next;
        }
    } while (current != head);

    if (!found_male)
        printf("Tidak ada mahasiswa.\n");
    printf("\n");

    printf("Lingkaran Mahasiswi:\n");
    current = head;
    int found_female = 0;

    do {
        if (current->jenis_kelamin == 'P' || current->jenis_kelamin == 'p') {
            printf("%s ", current->nama);
            found_female = 1;
            current = current->next;
            while (current != head && (current->jenis_kelamin == 'P' || current->jenis_kelamin == 'p')) {
                printf("- %s ", current->nama);
                current = current->next;
            }
        } else {
            current = current->next;
        }
    } while (current != head);

    if (!found_female)
        printf("Tidak ada mahasiswi.\n");
    printf("\n");
}

int main() {
    int choice;
    char nama[MAX_NAME];
    char jenis_kelamin;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Tambahkan mahasiswa/mahasiswi\n");
        printf("2. Hapus mahasiswa/mahasiswi\n");
        printf("3. Tampilkan lingkaran besar\n");
        printf("4. Pisahkan lingkaran\n");
        printf("5. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nama: ");
                scanf("%s", nama);
                printf("Jenis Kelamin (L/P): ");
                scanf(" %c", &jenis_kelamin);
                tambah_mahasiswa(nama, jenis_kelamin);
                break;
            case 2:
                printf("Nama: ");
                scanf("%s", nama);
                hapus_mahasiswa(nama);
                break;
            case 3:
                tampilkan_lingkaran();
                break;
            case 4:
                pisahkan_lingkaran();
                break;
            case 5:
                printf("Program selesai.\n");
                return 0;
            default:
                printf("Pilihan tidak valid.\n");
        }
    }
    return 0;
}
