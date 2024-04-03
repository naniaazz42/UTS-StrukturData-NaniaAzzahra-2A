#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Struct untuk menyimpan informasi produk ATK
struct Product {
    string name;
    float price;
};

// Array 1 dimensi untuk menyimpan harga produk ATK
float prices[] = {2500, 4000, 7000, 5000, 4000, 3000, 5000, 5000, 12000, 15000, 2000, 5000, 3000, 8000, 7000};

// Deskripsi produk ATK dalam array 2 dimensi
string descriptions[][2] = {
    {"Pensil", "Pensil 2B"},
    {"Bolpoin", "Bolpoin hitam"},
    {"Buku Tulis", "Buku tulis B5"},
    {"Buku Gambar", "Buku gambar A4"},
    {"Penggaris", "Penggaris plastik 30 cm"},
    {"Penghapus", "Penghapus karet"},
    {"Tipe-X", "Tipe-X cair"},
    {"Stabilo", "Warna random"},
    {"Pensil Warna", "Pensil warna isi 12 pcs"},
    {"Spidol Warna", "Spidol warna isi 12 pcs"},
    {"Serutan Pensil", "Warna random"},
    {"Pengait Kertas", "Pengait kertas plastik"},
    {"Map File", "Warna random"},
    {"Spidol Papan Tulis", "Warna hitam"},
    {"Penghapus Spidol", "Warna random"},

};

// Struct untuk node dalam linked list pesanan
struct OrderNode {
    Product data;
    int quantity;
    OrderNode* next;
};

// Fungsi untuk menampilkan menu produk ATK
void displayMenu() {
    cout << "Menu Produk ATK:\n";
    cout << "-------------------------------------------------\n";
    for (int i = 0; i < sizeof(descriptions) / sizeof(descriptions[0]); ++i) {
        cout << i + 1 << ". " << descriptions[i][0] << " - Rp " << prices[i] << endl;
        cout << "   " << descriptions[i][1] << endl;
    }
    cout << endl;
}

// Fungsi untuk menambah pesanan ke linked list
void addOrder(OrderNode** head, Product product, int quantity) {
    OrderNode* newNode = new OrderNode;
    newNode->data = product;
    newNode->quantity = quantity;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        OrderNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Fungsi untuk menampilkan pesanan
void displayOrders(OrderNode* head) {
    cout << "Pesanan Anda:\n";
    cout << "------------------------------------------------------------------------\n";
    cout << "| No |          Produk           |     Jumlah    |        Harga        |\n";
    cout << "------------------------------------------------------------------------\n";
    int count = 1;
    float total = 0;
    OrderNode* temp = head;
    while (temp != NULL) {
        cout << "| ";
        cout << setw(2) << left << count << " | ";
        cout << setw(26) << left << temp->data.name << " | ";
        cout << setw(6) << right << temp->quantity << "        | ";
        cout << "Rp " << setw(14) << fixed << setprecision(2) << temp->quantity * temp->data.price << " |\n";
        total += temp->data.price * temp->quantity;
        temp = temp->next;
        count++;
    }
    cout << "-----------------------------------------------------------------------\n";
    cout << "|                                   Total Harga: Rp " << setw(14) << fixed << setprecision(2) << total << " |\n";
    cout << "-----------------------------------------------------------------------\n\n";
}

// Fungsi untuk menghitung total harga pesanan
float calculateTotal(OrderNode* head) {
    float total = 0;
    OrderNode* temp = head;
    while (temp != NULL) {
        total += temp->data.price * temp->quantity;
        temp = temp->next;
    }
    return total;
}

// Fungsi untuk membersihkan semua pesanan
void clearOrders(OrderNode** head) {
    while (*head != NULL) {
        OrderNode* temp = *head;
        *head = (*head)->next;
        delete temp;
    }
}

int main() {
    OrderNode* orders = NULL;

    int choice;
    bool menuDisplayed = false; // Variabel untuk melacak, apakah daftar menu telah ditampilkan

    while (true) {
        cout << "=================================================================" << endl;
        cout << "                 SELAMAT DATANG DI TOKO ATK NAZA RAYA            " << endl;
        cout << "         Jln.Syekh Quro, Pulokalapa, Kec.Lemahabang Wadas,       " << endl;
        cout << "                   Kab. Karawang, Jawa Barat 41383               " << endl;
        cout << "=================================================================" << endl;
        cout << "| 1. Tampilkan Menu                                             |" << endl;
        cout << "| 2. Pesan Produk ATK                                           |" << endl;
        cout << "| 3. Tampilkan Pesanan                                          |" << endl;
        cout << "| 4. Selesai dan Bayar                                          |" << endl;
        cout << "| 0. Keluar                                                     |" << endl;
        cout << "=================================================================" << endl;
        cout << "Pilih: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Terima kasih telah berkunjung!" << endl;
            // Membersihkan pesanan sebelum keluar
            clearOrders(&orders);
            break;
        } else if (choice == 1) {
            cout << "Menu Produk ATK:\n";
            displayMenu();
        } else if (choice == 2) {
            char orderAgain;
            if (!menuDisplayed) { // Jika daftar menu belum ditampilkan
                cout << "Menu Produk ATK:\n";
                cout << "-------------------------------------------------\n";
                for (int i = 0; i < sizeof(descriptions) / sizeof(descriptions[0]); ++i) {
                    cout << i + 1 << ". " << descriptions[i][0] << " - Rp " << prices[i] << endl;
                }
                cout << endl;
                menuDisplayed = true; // Tandai bahwa daftar menu telah ditampilkan
            }
            do {
                int productIndex, quantity;
                cout << "Pilih nomor produk yang ingin dipesan: ";
                cin >> productIndex;
                if (productIndex >= 1 && productIndex <= sizeof(descriptions) / sizeof(descriptions[0])) {
                    cout << "Masukkan jumlah pesanan: ";
                    cin >> quantity;
                    Product product;
                    product.name = descriptions[productIndex - 1][0];
                    product.price = prices[productIndex - 1];
                    addOrder(&orders, product, quantity);
                    cout << "Pesanan berhasil ditambahkan." << endl << endl;
                } else {
                    cout << "Produk tidak valid." << endl << endl;
                    continue; // Melanjutkan ke iterasi berikutnya dalam loop do-while
                }

                cout << "Apakah ingin order lagi? (y/t): ";
                cin >> orderAgain;
            } while (orderAgain == 'y' || orderAgain == 'Y');
        } else if (choice == 3) {
            displayOrders(orders);
        } else if (choice == 4) {
            if (orders == NULL) {
                cout << "Belum ada pesanan yang ditempatkan." << endl;
                continue; // Kembali ke awal loop
            }

            cout << "\n=== PEMBAYARAN ===" << endl;
            float totalBayar = calculateTotal(orders);
            cout << "-----------------------------------" << endl;
            cout << "|         STRUK PEMBAYARAN        |" << endl;
            cout << "-----------------------------------" << endl;
            cout << "| Produk              Jumlah      |" << endl;
            cout << "-----------------------------------" << endl;

            OrderNode* temp = orders;
            while (temp != NULL) {
                cout << "| " << setw(20) << left << temp->data.name << " " << setw(6) << right << temp->quantity << "  |" << endl;
                temp = temp->next;
            }
            cout << "-----------------------------------" << endl;
            cout << "| Total Bayar:       Rp " << setw(8) << fixed << setprecision(2) << totalBayar << "  |" << endl;
            cout << "-----------------------------------" << endl;

            float pembayaran;
            cout << "Masukkan jumlah pembayaran: Rp ";
            cin >> pembayaran;

            if (pembayaran < totalBayar) {
                cout << "\nPembayaran kurang. Transaksi dibatalkan." << endl;
            } else {
                float kembalian = pembayaran - totalBayar;
                cout << "\n-----------------------------------" << endl;
                cout << "|          KEMBALIAN                |" << endl;
                cout << "-------------------------------------" << endl;
                cout << "| Kembalian Anda:    Rp " << setw(8) << fixed << setprecision(2) << kembalian << "   |" << endl;
                cout << "-------------------------------------" << endl;

                // Membersihkan pesanan
                clearOrders(&orders);
            }
        } else {
            cout << "Pilihan tidak valid." << endl << endl;
        }
    }

    return 0;
}
