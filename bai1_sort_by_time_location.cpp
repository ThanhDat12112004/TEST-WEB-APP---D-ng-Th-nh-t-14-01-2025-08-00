#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Cấu trúc dữ liệu để lưu thông tin
struct Record
{
    string location; // Vị trí (Location)
    string time;     // Thời gian (HH:MM:SS)

    // Constructor
    Record(string loc, string t) : location(loc), time(t) {}

    // Hàm hiển thị
    void display() const
    {
        cout << location << " " << time << endl;
    }
};

// 1. So sánh theo time (thời gian)
bool compareByTime(const Record &a, const Record &b)
{
    return a.time < b.time;
}

// 2. So sánh theo location (chữ cái A-Z) - NOT STABLE
bool compareByLocation(const Record &a, const Record &b)
{
    return a.location < b.location;
}

// 3. So sánh theo location, nếu cùng location thì so sánh theo time - STABLE
bool compareByLocationAndTime(const Record &a, const Record &b)
{
    if (a.location == b.location)
    {
        return a.time < b.time;
    }
    return a.location < b.location;
}

// Hàm hiển thị danh sách
void displayRecords(const vector<Record> &records)
{
    for (const auto &record : records)
    {
        record.display();
    }
    cout << "------------------------" << endl;
}

int main()
{
    vector<Record> records;

    // Tự động đọc từ file test_bai1.txt
    ifstream file("test_bai1.txt");
    if (!file.is_open())
    {
        cout << "Khong mo duoc file test_bai1.txt" << endl;
        return 1;
    }

    int n;
    file >> n;

    cout << "=== CHUONG TRINH SAP XEP ===" << endl;
    cout << "Doc tu file test_bai1.txt: " << n << " ban ghi" << endl;

    // Đọc dữ liệu (format: Location Time)
    for (int i = 0; i < n; i++)
    {
        string loc, t;
        file >> loc >> t;
        records.push_back(Record(loc, t));
    }
    file.close();

    cout << "\n=== DU LIEU GOC ===" << endl;
    displayRecords(records);

    // Tạo bản sao để sort
    vector<Record> sortedByTime = records;
    vector<Record> sortedByLocation = records;
    vector<Record> sortedByBoth = records;

    // 1. Sắp xếp theo TIME
    sort(sortedByTime.begin(), sortedByTime.end(), compareByTime);
    cout << "\n=== 1. SAP XEP THEO TIME ===" << endl;
    displayRecords(sortedByTime);

    // 2. Sắp xếp theo LOCATION (không stable)
    sort(sortedByLocation.begin(), sortedByLocation.end(), compareByLocation);
    cout << "\n=== 2. SAP XEP THEO LOCATION (not stable) ===" << endl;
    displayRecords(sortedByLocation);

    // 3. Sắp xếp theo LOCATION và TIME (stable)
    sort(sortedByBoth.begin(), sortedByBoth.end(), compareByLocationAndTime);
    cout << "\n=== 3. SAP XEP THEO LOCATION VA TIME (stable) ===" << endl;
    displayRecords(sortedByBoth);

    return 0;
}
