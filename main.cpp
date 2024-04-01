#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Struct untuk menyimpan informasi makanan
struct Food {
    string name;
    float price;
};

// Array 1 dimensi untuk menyimpan harga makanan
float prices[] = {45000, 50000, 35000, 40000, 6000, 6000, 10000, 2000, 2000};

// Deskripsi makanan dalam array 2 dimensi
string descriptions[][2] = {
    {"Kwetiaw Kangkung Blacan", "Kwetiaw dengan kangkung dan blacan."},
    {"Mie Goreng Spesial", "Mie goreng dengan bumbu spesial."},
    {"Nasi Goreng Ikan Asin", "Nasi goreng dengan ikan asin."},
    {"Nasi Cumi Ceria Pete", "Nasi dengan cumi dan pete."},
    {"Es Teh Manis"},
    {"Es Jeruk"},
    {"Es Campur"},
    {"Kerupuk"},
    {"Gorengan"},
};

// Struct untuk node dalam linked list
struct OrderNode {
    Food data;
    int quantity;
    OrderNode* next;
};

// Fungsi untuk menampilkan menu makanan
void displayMenu() {
    cout << "Menu Makanan:\n";
    cout << "-------------------------------------------------\n";
    for (int i = 0; i < sizeof(descriptions) / sizeof(descriptions[0]); ++i) {
        cout << i + 1 << ". " << descriptions[i][0] << " - Rp " << prices[i] << endl;
        cout << "   " << descriptions[i][1] << endl;
    }
    cout << endl;
}

// Fungsi untuk menambah pesanan ke linked list
void addOrder(OrderNode** head, Food food, int quantity) {
    OrderNode* newNode = new OrderNode;
    newNode->data = food;
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
    cout << "| No |          Makanan           |     Jumlah    |        Harga       |\n";
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

// Fungsi untuk membersihkan layar (hanya untuk Windows)
void clearScreen() {
    system("cls");
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
    bool menuDisplayed = false; // Variabel untuk melacak apakah daftar menu telah ditampilkan

    while (true) {
        clearScreen(); // Membersihkan layar sebelum menampilkan menu
        cout << "=====================================================================================================================================" << endl;
        cout << "                                                            RUMAH MAKAN PODO SUKO                       " << endl;
        cout << "                                                       Jl. Panjaitan No.09 Kedungwungu                  " << endl;
        cout << "=====================================================================================================================================" << endl;
        cout << "| 1. Tampilkan Menu                                                                                                                 |" << endl;
        cout << "| 2. Pesan Makanan                                                                                                                  |" << endl;
        cout << "| 3. Tampilkan Pesanan                                                                                                              |" << endl;
        cout << "| 4. Selesai dan Bayar                                                                                                              |" << endl;
        cout << "| 0. Keluar                                                                                                                         |" << endl;
        cout << "=====================================================================================================================================" << endl;
        cout << "Pilih: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Sampai jumpa lagi!" << endl;
            // Membersihkan pesanan sebelum keluar
            clearOrders(&orders);
            break;
        } else if (choice == 1) {
            cout << "\nMenu Makanan:\n";
            displayMenu();
            system("pause"); // Jeda untuk menahan layar
        } else if (choice == 2) {
            char orderAgain;
            if (!menuDisplayed) { // Jika daftar menu belum ditampilkan
                cout << "Menu Makanan:\n";
                cout << "-------------------------------------------------\n";
                for (int i = 0; i < sizeof(descriptions) / sizeof(descriptions[0]); ++i) {
                    cout << i + 1 << ". " << descriptions[i][0] << " - Rp " << prices[i] << endl;
                    cout << "   " << descriptions[i][1] << endl;
                }
                cout << endl;
                menuDisplayed = true; // Tandai bahwa daftar menu telah ditampilkan
            }
            do {
                int menuIndex, quantity;
                cout << "Pilih nomor makanan yang ingin dipesan: ";
                cin >> menuIndex;
                if (menuIndex >= 1 && menuIndex <= sizeof(descriptions) / sizeof(descriptions[0])) {
                    cout << "Masukkan jumlah pesanan: ";
                    cin >> quantity;
                    Food food;
                    food.name = descriptions[menuIndex - 1][0];
                    food.price = prices[menuIndex - 1];
                    addOrder(&orders, food, quantity);
                    cout << "Pesanan berhasil ditambahkan." << endl << endl;
                } else {
                    cout << "Menu tidak valid." << endl << endl;
                    continue; // Melanjutkan ke iterasi berikutnya dalam loop do-while
                }

                cout << "Apakah ingin order lagi? (y/n): ";
                cin >> orderAgain;
            } while (orderAgain == 'y' || orderAgain == 'Y');
            system("pause"); // Jeda untuk menahan layar
        } else if (choice == 3) {
            displayOrders(orders);
            system("pause"); // Jeda untuk menahan layar
        } else if (choice == 4) {
            if (orders == NULL) {
                cout << "Belum ada pesanan yang ditempatkan." << endl;
                system("pause"); // Jeda untuk menahan layar
                continue; // Kembali ke awal loop
            }

            cout << "\n=== PEMBAYARAN ===" << endl;
            float totalBayar = calculateTotal(orders);
            cout << "-----------------------------------" << endl;
            cout << "|         STRUK PEMBAYARAN        |" << endl;
            cout << "-----------------------------------" << endl;
            cout << "| Menu                Jumlah      |" << endl;
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
                cout << "\n-------------------------------------" << endl;
                cout << "|          KEMBALIAN                |" << endl;
                cout << "-------------------------------------" << endl;
                cout << "| Kembalian Anda:    Rp " << setw(8) << fixed << setprecision(2) << kembalian << "   |" << endl;
                cout << "| Terima kasih atas kunjungan Anda!|" << endl;
                cout << "-------------------------------------" << endl;

                // Membersihkan pesanan
                clearOrders(&orders);
            }

            system("pause"); // Jeda untuk menahan layar
        } else {
            cout << "Pilihan tidak valid." << endl << endl;
            system("pause"); // Jeda untuk menahan layar
        }
    }

    return 0;
}
