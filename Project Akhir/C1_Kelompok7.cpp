#include <iostream>
#include <unistd.h>
#include <limits>
#include <cmath>
#include <vector>
using namespace std;

struct Login{
   string Username;
   string Password;
};

struct Jemaah {
    int id_jemaah;
    string NamaJemaah;
    string AlamatJemaah;
    int UmurJemaah;
    int Tahun;
};

struct Antrian {
    int NoAntrian;
    string NamaAntrian;
    string AlamatAntrian;
    int UmurAntrian;
};
struct NodeUser {
    Login log;
    NodeUser* next;
};

struct NodeJemaah {
    Jemaah jmh;
    NodeJemaah* next;
};

struct NodeAntrian {
    Antrian Antrianjmh;
    NodeAntrian* next;
};

string AdminUsername = "admin";
string AdminPW = "admin";

NodeUser* headLogin = NULL;
NodeAntrian* headAntrian = NULL;
NodeJemaah* headJemaah = NULL;


void MenuUtama();
void MenuLogin();
void Register();
bool CekUsername(const string& username);
bool registerUser(const Login& newUser);

void MenuUser();
int countNodesAntrian(NodeAntrian* headAntrian);
void LihatDataAntrian();
void TambahAntrian();
void enqueueAntrian(const Antrian& newAntrian);

void MenuAdmin();
void TambahJemaah();
void ProsesTambahJemaah(const Jemaah& newJemaah);
bool CekIDJemaah(int idToCheck);
bool dequeueAntrian();
void LihatDataJemaah();
void HapusDataJemaah();
void UpdateJemaah();

void MenuSorting();
void SortUmur(NodeJemaah* head);
void SortTahun(NodeJemaah* head) ;
void SortId(NodeJemaah* head);
Jemaah getNodeData(NodeJemaah* head, int index);
void setNodeData(NodeJemaah* head, int index, Jemaah jemaah);

void MenuSearch();
void SearchUmur(NodeJemaah* head, int GetUmur);
void SearchTahun(NodeJemaah* head, int GetTahun);

void LihatDataUser();


int main(){
    MenuUtama();
}

// Tampilan awal
void MenuUtama(){
    string GetPilihan;
    system("cls");
    cout<<"===============================\n";
    cout<<"[1] . LOGIN\n";
    cout<<"[2] . REGISTER\n";
    cout<<"[0] . Exit Program\n";
    cout<<"===============================\n";
    
    while (true){
        cout<<"PILIHAN : ";cin>>GetPilihan;
        if (GetPilihan == "1"){
            MenuLogin();
        }

        else if (GetPilihan == "2"){
            Register();
        }
        else if (GetPilihan == "0"){
            exit(0);
        }
        else{
            cout<<"\nPILIHAN TIDAK TERSEDIA";
            sleep(2);
            MenuUtama();
        }
    }
}

// Tampilan Login pada ADMIN
void MenuLogin() {
    system("cls");
    string GetUsername, GetPassword;
    int kesalahan = 0;

    cout << "Mohon Login" << endl;
    // Selama value 'kesalahan' kurang dari sama dengan 3 maka program akan jalan
    while (kesalahan < 3) {
        cout << "Username: ";
        cin >> GetUsername;
        cout << "Password: ";
        cin >> GetPassword;

        bool found = false;

        // Mengecek apakah Username ada dalam linked list
        NodeUser* current = headLogin;
        while (current != NULL) {
            if (current->log.Username == GetUsername && current->log.Password == GetPassword) {
                found = true;
                system("cls");
                MenuUser();
            }
            current = current->next;
        }
        // Jika Input tidak ada di dalam linked list maka akan mengecek apakah GetUsername Dan GetPassword memiliki value 'admin'
        if (!found) {
            if (GetUsername == "admin" && GetPassword == "admin") {
                found = true;
                system("cls");
                MenuAdmin();
            }
        }
        // Jika dua kondisi diatas salah
        if (!found) {
            cout << "USER TIDAK DITEMUKAN" << endl;
            sleep(1);
        }
        // maka varible kesalahan mengalami increment
        kesalahan++;
    }
    
    // jika value 'kesalahan' telah mencapai 3, maka akan memanggil fungsi 'MenuUtama'
    if (kesalahan >= 3) {
        cout << "Anda telah mencoba login sebanyak 3 kali. Program akan keluar." << endl;
        MenuUtama();
    }
}

void Register(){
    Login newUser;
    // Meminta input username dari pengguna
    cout << "Masukkan Username: ";
    cin >> newUser.Username;
    
    // Meminta input password dari pengguna
    cout << "Masukkan Password: ";
    cin >> newUser.Password;
    
    // Memeriksa apakah register pengguna baru berhasil
    if (registerUser(newUser)) {
        // Jika berhasil, menampilkan pesan sukses dan ke menu utama
        cout << "Registrasi berhasil." << endl;
        sleep(2);
        MenuUtama();
    } 
    else {
        // Jika gagal maka akan mengulangi proses register
        cout << "Registrasi gagal. NamaUser atau Username sudah ada." << endl;
        sleep(2);
        Register();
    }
}

// Fungsi untuk memeriksa apakah username sudah ada dalam linked list
bool CekUsername(const string& username) {
    // Pointer untuk melakukan traversal pada linked list
    NodeUser* current = headLogin;

    // Melakukan traversal pada linked list node user
    while (current != NULL) {
        // Jika ditemukan username yang sama, kembalikan nilai true
        if (current->log.Username == username) {
            return true;
        }
        current = current->next;
    }
    // Jika tidak ditemukan, kembalikan nilai false
    return false;
}

// Fungsi untuk mendaftarkan pengguna baru ke dalam linked list
bool registerUser(const Login& newUser) {
    // Memanggil fungsi 'CekUsername' untuk memeriksa keberadaan username
    if (CekUsername(newUser.Username)) {
        return false;// Jika username sudah ada, kembalikan false
    }

     // Membuat node baru untuk menyimpan data login pengguna
    NodeUser* newNode = new NodeUser;
    newNode->log = newUser;
    newNode->next = headLogin;
    headLogin = newNode;// Menambahkan node baru ke depan linked list
    return true;// Kembalikan true untuk menandakan pendaftaran berhasil
}



void MenuUser(){
    string GetPilihan;
    while (true){
        cout<<"            MENU USER          \n";
        cout<<"===============================\n";
        cout<<"[1] . Tambah Data Antrian\n";
        cout<<"[2] . Lihat Antrian Jamaah\n";
        cout<<"[3] . Lihat Data Calon Jemaah Haji\n";
        cout<<"[0] . LOG OUT\n";
        cout<<"===============================\n";
        cout<<"Masukan Pilihan : ";cin>>GetPilihan;
        if (GetPilihan == "1"){
            system("cls");
            TambahAntrian();
        }

        else if (GetPilihan == "2"){
            if (headAntrian == NULL) {
                system("cls");
                cout << "ANTRIAN KOSONG" << endl;
                sleep(2);
            }
            else{
                system("cls");
                LihatDataAntrian();
            }
        }
        else if (GetPilihan == "3"){
            if (headJemaah == NULL) {
                system("cls");
                cout << "Tidak ada Calon Jemaah Haji saat ini\n";
                sleep(2);
            }
            else{
                system("cls");
                SortId(headJemaah);
                LihatDataJemaah();
            }
        }
        else if (GetPilihan == "0"){
            MenuUtama();
        }

        else{
            system("cls");
            cout<<"PILIHAN TIDAK TERSEDIA";
            sleep(1);
        } 
    }
    
}

// Fungsi ini berfungsi untuk menghitung panjang node Antrian
int countNodesAntrian(NodeAntrian* headAntrian) {
    int count = 0;
    NodeAntrian* current = headAntrian;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void LihatDataAntrian() {
    NodeAntrian* current = headAntrian;
    cout << "===================================================\n";
    cout << "                 LIST Antrian Jemaah               \n";
    cout << "===================================================\n";
    while (current != NULL) {
        cout<<"No Antrian = "<<current->Antrianjmh.NoAntrian<<endl;
        cout<<"Nama Antrian Jemaah = "<<current->Antrianjmh.NamaAntrian<<endl;
        cout<<"Alamat Antrian Jemaah = "<<current->Antrianjmh.AlamatAntrian<<endl;
        cout<<"Umur Antrian Jemaah = "<<current->Antrianjmh.UmurAntrian<<endl;
        cout<<"-------------------------------------------------\n";
        current = current->next;
    }
    cout << "===================================================\n";
}

// Fungsi untuk menambahkan antrian ke dalam linked list antrian
void enqueueAntrian(const Antrian& newAntrian) {

    // Membuat node baru untuk menyimpan data antrian
    NodeAntrian* newNodeAntrian = new NodeAntrian;
    newNodeAntrian->Antrianjmh = newAntrian;
    newNodeAntrian->next = NULL;

    // Jika linked list antrian kosong, tambahkan node baru sebagai head
    if (headAntrian == NULL) {
        headAntrian = newNodeAntrian;
    } else {
        // Jika tidak kosong, cari node terakhir dalam linked list
        NodeAntrian* current = headAntrian;
        while (current->next != NULL) {
            current = current->next;
        }
        // Tambahkan node baru sebagai node terakhir
        current->next = newNodeAntrian;
    }
}

// Fungsi untuk menambahkan data antrian baru
void TambahAntrian(){
    string GetNama,GetAlamat;
    int GetUmur,GetAntrian;

    // Menghitung nomor antrian baru berdasarkan jumlah node saat ini
    GetAntrian = countNodesAntrian(headAntrian) + 1;
    cout << "Masukkan Nama Antrian: ";
    cin.ignore();
    getline(cin, GetNama);
    cout << "Masukkan Alamat Antrian: ";
    // cin.ignore();
    getline(cin, GetAlamat);
    cout << "Masukkan Umur Antrian: ";
    while (!(cin >> GetUmur) || GetUmur < 12 ){
        cout << "Maaf Jamaah Terlalu Muda.\nUmur: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

     // Membuat objek Antrian baru dengan data yang diinput
    Antrian newAntrian;
    newAntrian.NoAntrian = GetAntrian;
    newAntrian.NamaAntrian = GetNama;
    newAntrian.AlamatAntrian = GetAlamat;
    newAntrian.UmurAntrian = GetUmur;

    // Menambahkan antrian baru ke dalam linked list antrian
    enqueueAntrian(newAntrian);

    system("cls");
    cout<<"DATA TELAH DITAMBAHKAN KE DALAM ANTRIAN\n";
    sleep(2);

}



void MenuAdmin(){
    string GetPilihan;
    while (true){
        cout<<"             MENU ADMIN          \n";
        cout << "===============================\n";
        cout << "[1] . Lihat Data Jemaah\n";
        cout << "[2] . Proses Antrian\n";
        cout << "[3] . Hapus Jemaah\n";
        cout << "[4] . Update Jemaah\n";
        cout << "[5] . Menu Searching\n";
        cout << "[6] . Lihat User\n";
        cout << "[0] . Log Out\n";
        cout << "===============================" << endl;
        cout << "Masukan Pilihan : "; cin >> GetPilihan;
        if (GetPilihan == "1"){
            if (headJemaah == NULL) {
                system("cls");
                cout << "DATA KOSONG, Mohon Proses Antrian terlebih dahulu.\n";
                sleep(2);
            }
            else{
                system("cls");
                MenuSorting();
            }
        }
        else if (GetPilihan == "2"){
            if (headAntrian == NULL) {
                system("cls");
                cout << "ANTRIAN KOSONG" << endl;
                sleep(2);
            }
            else{
                system("cls");
                TambahJemaah();
            }
        }
        else if (GetPilihan == "3"){
            system("cls");
            HapusDataJemaah();
        }
        else if (GetPilihan == "4"){
            system("cls");
            UpdateJemaah();
        }
        else if (GetPilihan == "5"){
            system("cls");
            MenuSearch();
        }
        else if (GetPilihan == "6"){
            system("cls");
            LihatDataUser();
        }
        
        else if (GetPilihan == "0"){
            MenuUtama();
        }
        else{
            system("cls");
            cout << "PILIHAN TIDAK TERSEDIA" << endl;
            sleep(2);
        } 
    }
}

// Fungsi untuk menambahkan data Jemaah baru
void TambahJemaah() {
    int GetId, GetTahun;

    // Menampilkan data antrian jemaah yang akan ditambahkan
    cout << "DATA JEMAAH\n";
    cout << "Nama Antrian Jemaah = " << headAntrian->Antrianjmh.NamaAntrian << endl;
    cout << "Alamat Antrian Jemaah = " << headAntrian->Antrianjmh.AlamatAntrian << endl;
    cout << "Umur Antrian Jemaah = " << headAntrian->Antrianjmh.UmurAntrian << endl;
    cout << "-------------------------------------------------\n";

    // Meminta input ID Jemaah dengan validasi
    cout << "Masukan ID Jemaah: ";
    while (!(cin >> GetId) || GetId <= 0) {
        cout << "Mohon hanya memasukkan angka dan Lebih dari 0.\nID Jemaah: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Memeriksa apakah ID Jemaah sudah ada
    if (CekIDJemaah(GetId)) {
        cout << "ID Jemaah " << GetId << " Sudah ada." << endl;
    } 
    else {
        cout << "Masukkan Tahun Keberangkatan: ";
        while (!(cin >> GetTahun) || GetTahun <= 2023) {
            cout << "Mohon hanya memasukkan tahun lebih dari 2023.\nTahun Keberangkatan: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    
        }

        // Membuat objek Jemaah baru dengan data dari antrian
        Jemaah newJemaah;
        newJemaah.Tahun = GetTahun;
        newJemaah.NamaJemaah = headAntrian->Antrianjmh.NamaAntrian;
        newJemaah.AlamatJemaah = headAntrian->Antrianjmh.AlamatAntrian;
        newJemaah.UmurJemaah = headAntrian->Antrianjmh.UmurAntrian;
        newJemaah.id_jemaah = GetId;

        // Memproses penambahan Jemaah dan menghapus data dari antrian
        ProsesTambahJemaah(newJemaah);
        dequeueAntrian();
        system("cls");
        cout<<"DATA JAMAAH TELAH DITAMBAHAKAN\n";
        sleep(2);
    }
}

// Fungsi untuk memeriksa keberadaan ID Jemaah dalam linked list Jemaah
bool CekIDJemaah(int idToCheck) {
    NodeJemaah* current = headJemaah;

    while (current) {
        if (current->jmh.id_jemaah == idToCheck) {
            
            return true;// Jika ID Jemaah sudah ada, kembalikan true
        }
        current = current->next;
    }

    return false;// Jika tidak ditemukan, kembalikan false
}

// Fungsi untuk memproses penambahan data Jemaah ke dalam linked list Jemaah
void ProsesTambahJemaah(const Jemaah& newJemaah) {
    // Membuat node baru untuk menyimpan data Jemaah
    NodeJemaah* newNodeJemaah = new NodeJemaah;
    newNodeJemaah->jmh = newJemaah;
    newNodeJemaah->next = NULL;

    // Jika linked list Jemaah kosong, tambahkan node baru sebagai head
    if (headJemaah == NULL) {
        headJemaah = newNodeJemaah;
    } else {
        // Jika tidak kosong, cari node terakhir dalam linked list
        NodeJemaah* current = headJemaah;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNodeJemaah;
    }
}

// Fungsi untuk menghapus data antrian dari linked list antrian
bool dequeueAntrian() {
    // Menyimpan pointer ke node antrian yang akan dihapus
    NodeAntrian* temp = headAntrian;
    // Memindahkan pointer headAntrian ke node antrian berikutnya
    headAntrian = headAntrian->next;
    // Menghapus node antrian yang telah dipindahkan
    delete temp;

    // Mengurangi nomor antrian setiap node setelah dequeue
    NodeAntrian* current = headAntrian;
    int antrianNo = 1;
    while (current != NULL) {
        current->Antrianjmh.NoAntrian = antrianNo++;
        current = current->next;
    }
}

void LihatDataJemaah() {
    NodeJemaah* current = headJemaah;
    cout << "===================================================\n";
    cout << "                 LIST Jemaah Jemaah               \n";
    cout << "===================================================\n";
    while (current != NULL) {
        cout<<"ID: " << current->jmh.id_jemaah<< endl;
        cout<<"Nama Jemaah Jemaah = "<<current->jmh.NamaJemaah<<endl;
        cout<<"Alamat Jemaah Jemaah = "<<current->jmh.AlamatJemaah<<endl;
        cout<<"Umur Jemaah Jemaah = "<<current->jmh.UmurJemaah<<endl;
        cout<<"Tahun Keberangkatan = "<<current->jmh.Tahun<<endl;
        cout<<"-------------------------------------------------\n";
        current = current->next;
    }
    cout << "===================================================\n";
}

// Fungsi untuk menghapus data Jemaah berdasarkan ID
void HapusDataJemaah() {
    int GetId;
    NodeJemaah* current = headJemaah;
    NodeJemaah* prev = NULL;
    cout << "Masukkan ID Jemaah: ";
    while (!(cin >> GetId) || GetId <= 0) {
        cout << "Mohon hanya memasukkan angka dan Lebih dari 0.\nID Jemaah: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Mencari data Jemaah berdasarkan ID
    while (current && current->jmh.id_jemaah != GetId) {
        prev = current;
        current = current->next;
    }

    // Jika data Jemaah tidak ditemukan
    if (!current) {
        system("cls");
        cout << "ID Jemaah " << GetId << " Tidak DItemukan." << endl;
        sleep(2);
        return;
    }

    // Menghapus data Jemaah
    if (prev) {
        prev->next = current->next;
        delete current;
    } else {
        // Jika yang dihapus adalah node pertama (head)
        headJemaah = current->next;
        delete current;
    }
    system("cls");
    cout << "ID Jemaah " << GetId << " Telah Dihapus.\n";
    sleep(2);
}

// Fungsi untuk memperbarui data Jemaah berdasarkan ID
void UpdateJemaah() {
    // Deklarasi variabel untuk menyimpan input pengguna
    int GetId, GetUmur, GetTahun;
    string GetNama, GetAlamat;

    // Pointer untuk menelusuri linked list Jemaah
    NodeJemaah* current = headJemaah;

    // Meminta input ID Jemaah dari pengguna
    cout << "Masukkan ID Jemaah: ";
    while (!(cin >> GetId) || GetId <= 0) {
        cout << "Mohon hanya memasukkan angka dan Lebih dari 0.\nID Jemaah: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Mencari data Jemaah berdasarkan ID
    while (current) {
        if (current->jmh.id_jemaah == GetId) {
            // Menampilkan data Jemaah yang akan diperbarui
            cout << "DATA LAMA:" << endl;
            cout << "===================================\n";
            cout << "ID: " << current->jmh.id_jemaah << endl;
            cout << "Nama: " << current->jmh.NamaJemaah << endl;
            cout << "Alamat: " << current->jmh.AlamatJemaah << endl;
            cout << "Umur: " << current->jmh.UmurJemaah << endl;
            cout << "Tahun Keberangkatan: " << current->jmh.Tahun << endl;
            cout << "===================================\n";
            cout << "      MASUKAN DATA TERBARU\n";
            cout << "===================================\n";

            // Meminta input data terbaru dari pengguna
            cout << "Nama: ";
            cin.ignore();
            getline(cin, GetNama);
            cout << "Alamat: ";
            getline(cin, GetAlamat);
            cout << "Umur: ";
            while (!(cin >> GetUmur) || GetUmur < 12) {
                cout << "Maaf Jamaah Terlalu Muda.\nUmur: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Tahun Keberangkatan: ";
            while (!(cin >> GetTahun) || GetTahun <= 2023) {
                cout << "Mohon hanya memasukkan tahun lebih dari 2023.\nTahun Keberangkatan: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            // Memperbarui data Jemaah dengan data baru
            current->jmh.NamaJemaah = GetNama;
            current->jmh.AlamatJemaah = GetAlamat;
            current->jmh.UmurJemaah = GetUmur;
            current->jmh.Tahun = GetTahun;

            // Membersihkan layar dan memberikan konfirmasi
            system("cls");
            cout << "Data Jemaah telah diperbarui." << endl;
            sleep(2);
            return;
        }
        // Pindah ke node Jemaah berikutnya
        current = current->next;
    }

    // Jika ID Jemaah tidak ditemukan
    system("cls");
    cout << "ID Jemaah " << GetId << " Tidak Ditemukan." << endl;
    sleep(2);
}



void MenuSorting() {
    // Mendeklarasikan variabel string untuk menyimpan pilihan menu pengguna
    string GetMenu;

    // Mengurutkan data Jemaah berdasarkan ID
    SortId(headJemaah);

    // Menampilkan data Jemaah
    LihatDataJemaah();

    // Menampilkan opsi menu untuk pengurutan
    cout << "==========================\n";
    cout << "[1]. Sorting Umur\n";
    cout << "[2]. Sorting Tahun\n";
    cout << "[0]. Kembali\n";
    cout << "==========================\n";
    cout << "Masukan Pilihan: "; cin >> GetMenu;

    // Memeriksa pilihan menu pengguna
    if (GetMenu == "1") {
        // Jika pengguna memilih opsi 1, membersihkan layar, mengurutkan berdasarkan umur, menampilkan data, dan kembali ke menu admin
        system("cls");
        SortUmur(headJemaah);
        LihatDataJemaah();
        MenuAdmin();
    } else if (GetMenu == "2") {
        // Jika pengguna memilih opsi 2, membersihkan layar, mengurutkan berdasarkan tahun, menampilkan data, dan kembali ke menu admin
        system("cls");
        SortTahun(headJemaah);
        LihatDataJemaah();
        MenuAdmin();
    } else if (GetMenu == "0") {
        // Jika pengguna memilih opsi 0, membersihkan layar, dan kembali ke menu admin
        system("cls");
        MenuAdmin();
    }else {
        // Jika pengguna memasukkan pilihan yang tidak valid, membersihkan layar, menampilkan pesan kesalahan, menunggu selama 2 detik, dan menampilkan menu pengurutan lagi
        system("cls");
        cout << "PILIHAN TIDAK TERSEDIA\n";
        sleep(2);
        MenuSorting();
    }
}

// Shell Sort berdasarkan umur Jemaah
void SortUmur(NodeJemaah* head) {
    int n = 0;
    NodeJemaah* current = head;

    // Menghitung jumlah elemen dalam linked list
    while (current != NULL) {
        n++;
        current = current->next;
    }

    // Dimulai dengan selisih besar dan mengurangi selisih dalam setiap iterasi
    for (int selisih = n / 2; selisih > 0; selisih /= 2) {
        // Melakukan insertion sort untuk elemen pada selisih tertentu
        for (int i = selisih; i < n; i++) {
            // Mendapatkan data dari node saat ini pada posisi i
            Jemaah temp = getNodeData(head, i);
            int j = i;

            // Memindahkan elemen yang lebih besar dari temp.UmurJemaah ke kanan
            // dalam selisih yang ditentukan oleh selisih saat ini
            while (j >= selisih && getNodeData(head, j - selisih).UmurJemaah > temp.UmurJemaah) {
                setNodeData(head, j, getNodeData(head, j - selisih));
                j -= selisih;
            }

            // Menempatkan elemen saat ini (temp) pada posisi yang benar
            setNodeData(head, j, temp);
        }
    }
}


//Shell Sort berdasarkan tahun Jemaah
void SortTahun(NodeJemaah* head) {
    int n = 0;
    NodeJemaah* current = head;
    
    // Menghitung jumlah elemen dalam linked list
    while (current != NULL) {
        n++;
        current = current->next;
    }
    
    // Algoritma Shell Sort
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            // Menyimpan data Jemaah pada posisi i ke dalam variabel sementara
            Jemaah temp = getNodeData(head, i);
            int j = i;
            
            // Memindahkan elemen-elemen yang lebih besar pada jarak gap
            // ke posisi yang lebih dekat ke elemen pada posisi i
            while (j >= gap && getNodeData(head, j - gap).Tahun > temp.Tahun) {
                setNodeData(head, j, getNodeData(head, j - gap));
                j -= gap;
            }
            
            // Menempatkan data Jemaah pada posisi yang tepat dalam subarray
            setNodeData(head, j, temp);
        }
    }
}


// Fungsi untuk mengurutkan elemen-elemen linked list berdasarkan ID_Jemaah menggunakan algoritma Shell Sort
void SortId(NodeJemaah* head) {
    int n = 0; // Variabel untuk menyimpan jumlah elemen dalam linked list
    NodeJemaah* current = head; // Pointer untuk traversal linked list
    
    // Menghitung jumlah elemen dalam linked list
    while (current != NULL) {
        n++;
        current = current->next;
    }
    
    // Algoritma Shell Sort
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            // Menyimpan data dari node ke dalam variabel sementara
            Jemaah temp = getNodeData(head, i);
            int j = i;
            
            // Melakukan pergeseran elemen-elemen yang lebih besar dari temp ke posisi yang sesuai
            while (j >= gap && getNodeData(head, j - gap).id_jemaah > temp.id_jemaah) {
                // Memindahkan data dari posisi yang lebih besar ke posisi yang lebih kecil
                setNodeData(head, j, getNodeData(head, j - gap));
                j -= gap;
            }
            
            // Menempatkan elemen temp pada posisi yang benar dalam linked list
            setNodeData(head, j, temp);
        }
    }
}


// Fungsi untuk mendapatkan data Jemaah pada node tertentu
Jemaah getNodeData(NodeJemaah* head, int index) {
    // Inisialisasi pointer current dengan head (node pertama)
    NodeJemaah* current = head;
    
    // Iterasi melalui linked list hingga mencapai node dengan indeks yang diinginkan
    for (int i = 0; i < index; i++) {
        current = current->next; // Pindahkan pointer current ke node selanjutnya
    }
    
    // Kembalikan data Jemaah yang terdapat pada node dengan indeks yang diinginkan
    return current->jmh;
}


// Fungsi untuk mengubah data Jemaah pada node tertentu
void setNodeData(NodeJemaah* head, int index, Jemaah jemaah) {
    // Inisialisasi pointer current untuk menunjuk ke head (node pertama)
    NodeJemaah* current = head;
    
    // Loop untuk mencapai node pada index yang diinginkan
    for (int i = 0; i < index; i++) {
        // Pindahkan pointer current ke node berikutnya
        current = current->next;
    }
    
    // Ubah data Jemaah pada node yang telah dijangkau
    current->jmh = jemaah;
}


void MenuSearch(){
    string GetMenu; // Variabel untuk menyimpan pilihan menu
    int GetUmur, GetTahun; // Variabel untuk menyimpan input umur dan tahun

    // Menampilkan menu pencarian
    cout<<"==========================\n";
    cout<<"[1]. Search Berdasarkan Umur\n";
    cout<<"[2]. Search Berdasarkan Tahun\n";
    cout<<"[0]. Kembali\n";
    cout<<"==========================\n";
    cout<<"Masukan Pilihan: "; cin >> GetMenu; // Meminta pengguna memasukkan pilihan menu

    // Jika pilihan menu adalah 1
    if (GetMenu == "1") {
        SortUmur(headJemaah); // Mengurutkan data berdasarkan umur
        cout << "Masukkan umur jemaah yang ingin dicari: ";
        
        // Validasi input umur, memastikan umur yang dimasukkan lebih dari 12
        while (!(cin >> GetUmur) || GetUmur < 12) {
            cout << "Maaf Jamaah Terlalu Muda.\nUmur: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        SearchUmur(headJemaah, GetUmur); // Memanggil fungsi pencarian berdasarkan umur
        MenuAdmin(); // Kembali ke menu admin setelah selesai pencarian
    } 
    // Jika pilihan menu adalah 2
    if (GetMenu == "2") {
        SortTahun(headJemaah); // Mengurutkan data berdasarkan tahun
        cout << "Masukkan tahun keberangkatan jemaah yang ingin dicari: ";
        
        // Validasi input tahun, memastikan tahun yang dimasukkan lebih dari 2023
        while (!(cin >> GetTahun) || GetTahun <= 2023) {
            cout << "Mohon hanya memasukkan tahun lebih dari 2023.\nTahun Keberangkatan: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    
        }

        SearchTahun(headJemaah, GetTahun); // Memanggil fungsi pencarian berdasarkan tahun
        MenuAdmin(); // Kembali ke menu admin setelah selesai pencarian
    } 
    // Jika pilihan menu adalah 0
    else if (GetMenu == "0") {
        MenuAdmin(); // Kembali ke menu admin
    }
    // Jika pilihan menu tidak valid
    else {
        system("cls"); // Membersihkan layar
        cout<<"PILIHAN TIDAK TERSEDIA\n";
        sleep(2); // Menunggu 2 detik
        MenuSorting(); // Kembali ke menu sorting
    }
}


// Fungsi untuk mencari Jemaah berdasarkan umur.
void SearchUmur(NodeJemaah* head, int GetUmur) {
    // Menghitung jumlah total node.
    int n = 0;
    NodeJemaah* temp = head;
    while (temp != NULL) {
        n++;
        temp = temp->next;
    }

    // Menghitung langkah untuk melompati sejumlah node dalam pencarian.
    int step = sqrt(n);
    int prev = 0;
    temp = head;

    // Melakukan pencarian Jemaah dengan umur lebih kecil dari yang dicari.
    while (temp != NULL && temp->jmh.UmurJemaah < GetUmur) {
        prev = temp->jmh.UmurJemaah;
        
        // Melompati sejumlah node sesuai dengan langkah yang telah dihitung.
        for (int i = 0; i < step && temp != NULL; i++) {
            temp = temp->next;
        }
    }

    // Menampilkan hasil pencarian jika umur Jemaah ditemukan.
    if (temp != NULL && temp->jmh.UmurJemaah == GetUmur) {
        cout << "Jemaah ditemukan:" << endl;
        cout << "ID: " << temp->jmh.id_jemaah << endl;
        cout << "Nama: " << temp->jmh.NamaJemaah << endl;
        cout << "Alamat: " << temp->jmh.AlamatJemaah << endl;
        cout << "Umur: " << temp->jmh.UmurJemaah << endl;
        cout << "Tahun Keberangkatan: " << temp->jmh.Tahun << endl;
        cout << "---------------------------------------" << endl;
    } 
    // Menampilkan pesan jika umur Jemaah tidak ditemukan.
    else {
        system("cls");
        cout << "Jemaah dengan umur " << GetUmur << " tidak ditemukan." << endl;
        sleep(2);
        MenuAdmin();
    }
}


// Fungsi untuk mencari Jemaah berdasarkan Tahun Keberangkatan
void SearchTahun(NodeJemaah* head, int GetTahun) {
    // Menghitung jumlah node dalam linked list
    int n = 0;
    NodeJemaah* temp = head;
    while (temp != NULL) {
        n++;
        temp = temp->next;
    }

    // Menghitung langkah untuk melompati sejumlah node yang tetap antara iterasi
    int step = sqrt(n);
    int prev = 0;
    temp = head;

    // Melakukan pencarian Jemaah dengan menggunakan skala langkah
    while (temp != NULL && temp->jmh.Tahun < GetTahun) {
        prev = temp->jmh.Tahun;
        // Melompati sejumlah node sesuai dengan langkah yang telah dihitung
        for (int i = 0; i < step && temp != NULL; i++) {
            temp = temp->next;
        }
    }

    // Menampilkan informasi Jemaah jika ditemukan
    if (temp != NULL && temp->jmh.Tahun == GetTahun) {
        cout << "Jemaah ditemukan:" << endl;
        cout << "ID: " << temp->jmh.id_jemaah << endl;
        cout << "Nama: " << temp->jmh.NamaJemaah << endl;
        cout << "Alamat: " << temp->jmh.AlamatJemaah << endl;
        cout << "Umur: " << temp->jmh.UmurJemaah << endl;
        cout << "Tahun Keberangkatan: " << temp->jmh.Tahun << endl;
        cout << "---------------------------------------" << endl;
    } else {
        // Menampilkan pesan jika Jemaah tidak ditemukan
        system("cls"); // Membersihkan layar console (hanya berlaku di sistem Windows)
        cout << "Jemaah dengan Tahun Keberangkatan " << GetTahun << " tidak ditemukan." << endl;
        sleep(2); // Menunda eksekusi program selama 2 detik
        MenuAdmin(); // Kembali ke menu admin setelah menampilkan pesan
    }
}



void LihatDataUser() {
    // Memeriksa apakah daftar pengguna (headLogin) masih kosong
    if (headLogin == NULL) {
        // Jika kosong, tampilkan pesan bahwa belum ada pengguna dan kembali dari fungsi
        cout << "Belum ada User." << endl;
        return;
    }

    // Inisialisasi pointer current untuk mengakses setiap node dalam daftar pengguna
    NodeUser* current = headLogin;

    // Menampilkan header untuk daftar pengguna
    cout << "===================================================\n";
    cout << "                     LIST USER                     \n";
    cout << "===================================================\n";

    // Iterasi melalui daftar pengguna dan menampilkan informasi setiap pengguna
    while (current != NULL) {
        // Menampilkan username dari node saat ini
        cout << "Username : " << current->log.Username << endl;

        // Menampilkan password dari node saat ini
        cout << "Password : " << current->log.Password << endl;

        // Menampilkan pemisah antar pengguna
        cout << "-------------------------------------------------\n";

        // Pindah ke node pengguna berikutnya dalam daftar
        current = current->next;
    }

    // Menampilkan footer untuk daftar pengguna
    cout << "===================================================\n";
}



