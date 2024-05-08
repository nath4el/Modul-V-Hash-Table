#include <iostream>
#include <vector>

using namespace std;

// Struktur untuk menyimpan data mahasiswa
struct Mahasiswa
{
    long long nim;
    string nama;
    int nilai;
    Mahasiswa(long long n, string nm, int v) : nim(n), nama(nm), nilai(v) {}
};

// Kelas HashTable untuk implementasi hash table
class HashTable
{
private:
    static const int TABLE_SIZE = 100;
    vector<Mahasiswa *> table[TABLE_SIZE];

    // Fungsi hash sederhana
    int hashFunction(long long key)
    {
        return key % TABLE_SIZE;
    }

public:
    // Fungsi untuk menambahkan data mahasiswa ke hash table
    void insert(long long nim, string nama, int nilai)
    {
        int index = hashFunction(nim);
        Mahasiswa *mahasiswa = new Mahasiswa(nim, nama, nilai);
        table[index].push_back(mahasiswa);
    }

    // Fungsi untuk mencari data mahasiswa berdasarkan NIM
    Mahasiswa *searchByNIM(long long nim)
    {
        int index = hashFunction(nim);
        for (Mahasiswa *m : table[index])
        {
            if (m->nim == nim)
                return m;
        }
        return nullptr;
    }

    // Fungsi untuk menghapus data mahasiswa berdasarkan NIM
    void remove(long long nim)
    {
        int index = hashFunction(nim);
        for (auto it = table[index].begin(); it != table[index].end(); ++it)
        {
            if ((*it)->nim == nim)
            {
                delete *it;
                table[index].erase(it);
                break;
            }
        }
    }

    // Fungsi untuk mencari data mahasiswa berdasarkan rentang nilai (80-90)
    vector<Mahasiswa *> searchByRange()
    {
        vector<Mahasiswa *> result;
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            for (Mahasiswa *m : table[i])
            {
                if (m->nilai >= 80 && m->nilai <= 90)
                    result.push_back(m);
            }
        }
        return result;
    }
};

int main()
{
    HashTable hashTable;
    int choice;

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Tambah Data Mahasiswa\n";
        cout << "2. Hapus Data Mahasiswa\n";
        cout << "3. Cari Data Mahasiswa berdasarkan NIM\n";
        cout << "4. Cari Data Mahasiswa berdasarkan Rentang Nilai (80-90)\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            long long nim;
            int nilai;
            string nama;
            cout << "Masukkan NIM (10 digit): ";
            cin >> nim;
            cout << "Masukkan Nama: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Masukkan Nilai: ";
            cin >> nilai;
            hashTable.insert(nim, nama, nilai);
            cout << "Data mahasiswa berhasil ditambahkan.\n";
            break;
        }
        case 2:
        {
            long long nim;
            cout << "Masukkan NIM mahasiswa yang akan dihapus: ";
            cin >> nim;
            hashTable.remove(nim);
            cout << "Data mahasiswa berhasil dihapus.\n";
            break;
        }
        case 3:
        {
            long long nim;
            cout << "Masukkan NIM mahasiswa yang ingin dicari: ";
            cin >> nim;
            Mahasiswa *m = hashTable.searchByNIM(nim);
            if (m != nullptr)
                cout << "Data ditemukan - NIM: " << m->nim << ", Nama: " << m->nama << ", Nilai: " << m->nilai << endl;
            else
                cout << "Data tidak ditemukan.\n";
            break;
        }
        case 4:
        {
            vector<Mahasiswa *> result = hashTable.searchByRange();
            if (result.empty())
            {
                cout << "Tidak ada mahasiswa dengan nilai dalam rentang 80-90.\n";
            }
            else
            {
                cout << "Mahasiswa dengan nilai dalam rentang 80-90:\n";
                for (Mahasiswa *m : result)
                {
                    cout << "NIM: " << m->nim << ", Nama: " << m->nama << ", Nilai: " << m->nilai << endl;
                }
            }
            break;
        }
        case 5:
        {
            cout << "Terima kasih!\n";
            break;
        }
        default:
            cout << "Pilihan tidak valid. Silakan pilih kembali.\n";
        }
    } while (choice != 5);

    return 0;
}
