# 📚 Bài Tập Cấu Trúc Dữ Liệu và Giải Thuật

Repository chứa các bài tập về cấu trúc dữ liệu và giải thuật được viết bằng C++.

---

## 📋 Danh Sách Bài Tập

### 🔹 Bài 1: Sắp Xếp Theo Thời Gian và Địa Điểm
**File:** `bai1_sort_by_time_location.cpp`

**Mô tả:**
- Sắp xếp dữ liệu theo thời gian và địa điểm
- Sử dụng thuật toán sắp xếp để tổ chức dữ liệu theo tiêu chí

**Input:** `test_bai1.txt`

**Cách chạy:**
```bash
g++ -std=c++11 bai1_sort_by_time_location.cpp -o bai1
./bai1
```

---

### 🔹 Bài 2: Hash Table với Separate Chaining
**File:** `bai2_hash_table_separate_chaining.cpp`

**Mô tả:**
- Cài đặt Hash Table sử dụng kỹ thuật Separate Chaining
- Xử lý xung đột bằng Linked List tại mỗi bucket
- **Quy tắc:** Hash value được đọc từ file (không tính toán)
- **Xử lý key trùng:** Cập nhật value thành index mới nhất

**Cấu trúc dữ liệu:**
```cpp
const int TABLE_SIZE = 5;
struct Node {
    char key;      // Chữ cái (A-Z)
    int value;     // Thứ tự xuất hiện (0-12)
    Node* next;    // Con trỏ đến node tiếp theo
}
```

**Input format (`test_bai2.txt`):**
```
13          // Số lượng phần tử
S 2         // Key, Hash_Value
E 0
A 0
R 4
C 4
H 4
E 0         // Key 'E' trùng → Cập nhật value = 6
X 2
A 0         // Key 'A' trùng → Cập nhật value = 8
M 4
P 3
L 3
E 0         // Key 'E' trùng lần 2 → Cập nhật value = 12
```

**Output mẫu:**
```
Bucket [0]: A(8) -> E(12)
Bucket [1]: null
Bucket [2]: X(7) -> S(0)
Bucket [3]: L(11) -> P(10)
Bucket [4]: M(9) -> H(5) -> C(4) -> R(3)
```

**Giải thích:**
- E xuất hiện ở dòng 1, 6, 12 → Giữ index cuối cùng: **E(12)**
- A xuất hiện ở dòng 2, 8 → Giữ index cuối cùng: **A(8)**
- Hash value = 0 → Bucket [0]
- Hash value = 2 → Bucket [2]
- Hash value = 3 → Bucket [3]
- Hash value = 4 → Bucket [4]

**Cách chạy:**
```bash
g++ -std=c++11 bai2_hash_table_separate_chaining.cpp -o bai2
./bai2
```

---

### 🔹 Bài 3: Edge Weighted Digraph
**File:** `bai3_edge_weighted_digraph.cpp`

**Mô tả:**
- Cài đặt đồ thị có hướng có trọng số (Edge Weighted Directed Graph)
- Xử lý các cạnh có trọng số trong đồ thị có hướng

**Input:** `test_bai3.txt`

**Cách chạy:**
```bash
g++ -std=c++11 bai3_edge_weighted_digraph.cpp -o bai3
./bai3
```

---

### 🔹 Bài 4: Đếm Từ trong Đoạn Văn
**File:** `bai4_word_segment_counter.cpp`

**Mô tả:**
- Đếm số lần xuất hiện của các từ trong đoạn văn
- Phân tích và thống kê tần suất từ

**Input:** `test_bai4.txt`

**Cách chạy:**
```bash
g++ -std=c++11 bai4_word_segment_counter.cpp -o bai4
./bai4
```

---

**📅 Cập nhật:** 14/01/2026
