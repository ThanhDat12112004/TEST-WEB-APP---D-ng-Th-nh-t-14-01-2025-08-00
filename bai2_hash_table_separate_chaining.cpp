#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int TABLE_SIZE = 5;

// Node trong linked list của mỗi bucket
struct Node {
    char key;      // Chữ cái
    int value;     // Thứ tự xuất hiện (index)
    Node* next;    // Con trỏ đến node tiếp theo

    // Constructor
    Node(char k, int v) : key(k), value(v), next(nullptr) {}
};

// Hash Table với Separate Chaining
class HashTable {
private:
    Node* table[TABLE_SIZE];

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node* current = table[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    // Insert: hash được truyền vào từ file, value là index (thứ tự dòng)
    // Nếu key trùng thì UPDATE value (giữ index mới nhất)
    void insert(char key, int hashValue, int index) {
        // Tìm xem key đã tồn tại trong bucket chưa
        Node* current = table[hashValue];
        while (current) {
            if (current->key == key) {
                // Key trùng → CẬP NHẬT value thành index mới nhất
                current->value = index;
                return;
            }
            current = current->next;
        }

        // Key chưa tồn tại → Thêm vào đầu bucket
        Node* newNode = new Node(key, index);
        newNode->next = table[hashValue];
        table[hashValue] = newNode;
    }

    // Hiển thị Hash Table
    void display() {
        cout << "\n===== HASH TABLE (Separate Chaining) =====\n";

        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Bucket [" << i << "]: ";

            if (!table[i]) {
                cout << "null";
            } else {
                Node* current = table[i];
                while (current) {
                    cout << current->key << "(" << current->value << ")";
                    if (current->next) cout << " -> ";
                    current = current->next;
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }

    // Hiển thị dạng bảng chi tiết
};

int main() {
    HashTable ht;

    // Đọc từ file test_bai2.txt
    ifstream file("test_bai2.txt");
    if (!file.is_open()) {
        cout << "Không mở được file test_bai2.txt" << endl;
        return 1;
    }

    int n;
    file >> n;

    cout << "╔════════════════════════════════════════════════╗\n";
    cout << "║  HASH TABLE WITH SEPARATE CHAINING (Bài 2)   ║\n";
    cout << "╚════════════════════════════════════════════════╝\n\n";
    cout << "Đọc từ file test_bai2.txt: " << n << " phần tử\n";

    cout << "\n━━━ NHẬP DỮ LIỆU ━━━\n";
    cout << "+-----+-----+-------+-------+\n";
    cout << "| STT | Key | Value | Hash  |\n";
    cout << "+-----+-----+-------+-------+\n";

    // Đọc và insert từng phần tử
    for (int i = 0; i < n; i++) {
        char key;
        int hashValue; // Đọc hash từ file
        file >> key >> hashValue;

        // Chuyển chữ thường thành hoa
        if (key >= 'a' && key <= 'z') {
            key = key - 'a' + 'A';
        }

        cout << "| " << setw(3) << (i+1) << " |  " << key << "  |  "
             << setw(3) << i << "  |   " << hashValue << "   |\n";

        // Insert: hash từ file, value = index (i)
        ht.insert(key, hashValue, i);
    }
    cout << "+-----+-----+-------+-------+\n";
    file.close();

    // Hiển thị kết quả
    ht.display();

    return 0;
}
