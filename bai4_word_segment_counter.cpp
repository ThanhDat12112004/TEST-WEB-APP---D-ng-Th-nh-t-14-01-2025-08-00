#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <cctype>
using namespace std;

// Hàm loại bỏ dấu câu
string removePunctuation(string word)
{
    string result = "";
    for (char c : word)
    {
        if (isalnum(c))
        {
            result += c;
        }
    }
    return result;
}

// Hàm chuyển về chữ thường
string toLowerCase(string word)
{
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    return word;
}

// Class đếm từ theo đoạn
class WordSegmentCounter
{
private:
    // Map: key=từ, value=set các đoạn mà từ đó xuất hiện
    map<string, set<int>> wordSegments;

public:
    // Đọc file và xử lý
    void processFile(const string &filename)
    {
        ifstream file(filename);

        if (!file.is_open())
        {
            cout << "❌ Không thể mở file: " << filename << endl;
            return;
        }

        // Đọc toàn bộ nội dung file
        string content;
        string line;
        while (getline(file, line))
        {
            content += line + " ";
        }
        file.close();

        cout << "✅ Đọc file thành công!\n\n";
        cout << "━━━━ NỘI DUNG FILE ━━━━\n";
        cout << content << endl;

        // Xử lý từng đoạn (phân tách bởi dấu phẩy)
        processContent(content);
    }

    // Xử lý chuỗi input
    void processContent(const string &content)
    {
        stringstream ss(content);
        string segment;
        int segmentNum = 1;

        // Tách theo dấu phẩy
        while (getline(ss, segment, ','))
        {
            processSegment(segment, segmentNum);
            segmentNum++;
        }

    }

    // Xử lý một đoạn
    void processSegment(const string &segment, int segmentNum)
    {
        stringstream ss(segment);
        string word;

        while (ss >> word)
        {
            // Loại bỏ dấu câu
            word = removePunctuation(word);

            // Chuyển về chữ thường
            word = toLowerCase(word);

            // Bỏ qua từ rỗng
            if (word.empty())
                continue;

            // Thêm đoạn này vào set của từ
            wordSegments[word].insert(segmentNum);

        }
    }

    // Hiển thị kết quả theo format đề bài
    void displayResults()
    {
        cout << "\n╔════════════════════════════════════════╗\n";
        cout << "║     KẾT QUẢ (Theo format đề bài)     ║\n";
        cout << "╚════════════════════════════════════════╝\n\n";

        for (const auto &pair : wordSegments)
        {
            string word = pair.first;
            set<int> segments = pair.second;

            cout << word << " ";

            // Nếu chỉ xuất hiện ở 1 đoạn
            if (segments.size() == 1)
            {
                cout << *segments.begin();
            }
            else
            {
                // Xuất hiện ở nhiều đoạn: in đoạn đầu-đoạn cuối
                cout << *segments.begin() << "-" << *segments.rbegin();
            }

            cout << endl;
        }
    }

};

int main()
{
    cout << "╔═══════════════════════════════════════════════════╗\n";
    cout << "║   CHƯƠNG TRÌNH ĐẾM TỪ THEO ĐOẠN (C++)           ║\n";
    cout << "╚═══════════════════════════════════════════════════╝\n\n";

    // Tự động đọc từ file test_bai4.txt
    string filename = "test_bai4.txt";
    cout << "Đọc từ file: " << filename << "\n\n";

    WordSegmentCounter counter;
    counter.processFile(filename);
    counter.displayResults();

    return 0;
}

/*
╔═══════════════════════════════════════════════════════════╗
║                    GIẢI THÍCH CHI TIẾT                    ║
╠═══════════════════════════════════════════════════════════╣
║                                                           ║
║ 1. INPUT:                                                 ║
║    "It was the best of times, it was the worst of times, ║
║     it was the age of wisdom, it was the age of           ║
║     foolishness,"                                         ║
║                                                           ║
║ 2. PHÂN ĐOẠN (theo dấu phẩy):                             ║
║    Đoạn 1: "It was the best of times"                    ║
║    Đoạn 2: "it was the worst of times"                   ║
║    Đoạn 3: "it was the age of wisdom"                    ║
║    Đoạn 4: "it was the age of foolishness"               ║
║                                                           ║
║ 3. ĐẾM TỪ:                                                ║
║    - "it": xuất hiện ở đoạn 1, 2, 3, 4                   ║
║      → Output: it 1-4                                     ║
║                                                           ║
║    - "age": xuất hiện ở đoạn 3, 4                        ║
║      → Output: age 3-4                                    ║
║                                                           ║
║    - "best": chỉ xuất hiện ở đoạn 1                      ║
║      → Output: best 1                                     ║
║                                                           ║
║    - "the": xuất hiện ở đoạn 1, 2, 3, 4                  ║
║      → Output: the 1-4                                    ║
║                                                           ║
║ 4. CẤU TRÚC DỮ LIỆU:                                      ║
║    map<string, set<int>> wordSegments;                    ║
║    - Key: Từ (string)                                     ║
║    - Value: Set các đoạn xuất hiện (set<int>)            ║
║                                                           ║
║    VD: wordSegments["age"] = {3, 4}                      ║
║        wordSegments["it"] = {1, 2, 3, 4}                 ║
║                                                           ║
║ 5. OUTPUT FORMAT:                                         ║
║    <từ> <đoạn_đầu>-<đoạn_cuối>                           ║
║    Nếu chỉ 1 đoạn: <từ> <đoạn>                           ║
║                                                           ║
╚═══════════════════════════════════════════════════════════╝
*/
