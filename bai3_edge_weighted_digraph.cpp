#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// Cấu trúc Edge (Cạnh có hướng có trọng số)
struct Edge
{
    int from;      // Đỉnh xuất phát
    int to;        // Đỉnh đích
    double weight; // Trọng số
    Edge *next;    // Con trỏ đến edge tiếp theo

    Edge(int f, int t, double w) : from(f), to(t), weight(w), next(nullptr) {}
};

// Hash Table cho Edge-weighted Digraph
class GraphHashTable
{
private:
    Edge **adjacencyList; // Mảng các linked list (adj[i] = danh sách cạnh từ đỉnh i)
    int V;                // Số đỉnh
    int E;                // Số cạnh

public:
    // Constructor
    GraphHashTable(int vertices, int edges) : V(vertices), E(edges)
    {
        adjacencyList = new Edge *[V];
        for (int i = 0; i < V; i++)
        {
            adjacencyList[i] = nullptr;
        }
    }

    // Destructor
    ~GraphHashTable()
    {
        for (int i = 0; i < V; i++)
        {
            Edge *current = adjacencyList[i];
            while (current)
            {
                Edge *temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] adjacencyList;
    }

    // Thêm cạnh vào ĐẦU linked list (Insert at Head)
    // Cạnh thêm SAU sẽ đứng TRƯỚC trong list
    void addEdge(int from, int to, double weight)
    {
        Edge *newEdge = new Edge(from, to, weight);

        // LUÔN thêm vào đầu list
        newEdge->next = adjacencyList[from];
        adjacencyList[from] = newEdge;
    }

    // Hiển thị graph dạng hash table
    void displayHashTable()
    {
        cout << "\n╔════════════════════════════════════════════════════════╗\n";
        cout << "║     EDGE-WEIGHTED DIGRAPH (Hash Table Format)         ║\n";
        cout << "╚════════════════════════════════════════════════════════╝\n\n";
        cout << "Số đỉnh (V) = " << V << endl;
        cout << "Số cạnh (E) = " << E << endl;
        cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";

        for (int i = 0; i < V; i++)
        {
            cout << "adj[" << i << "]: ";

            Edge *current = adjacencyList[i];
            if (!current)
            {
                cout << "(empty)" << endl;
            }
            else
            {
                while (current)
                {
                    cout << "[" << current->from << " → " << current->to
                         << " | " << fixed << setprecision(2) << current->weight << "]";
                    if (current->next)
                        cout << " → ";
                    current = current->next;
                }
                cout << endl;
            }
        }
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    }

    // Hiển thị dạng bảng

    // Đọc từ file
    static GraphHashTable *readFromFile(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "❌ Không thể mở file: " << filename << endl;
            return nullptr;
        }

        int V, E;
        file >> V >> E;

        cout << "✅ Đọc file thành công: " << filename << endl;
        cout << "   Số đỉnh: " << V << ", Số cạnh: " << E << endl;

        GraphHashTable *graph = new GraphHashTable(V, E);

        int from, to;
        double weight;
        int count = 0;

        while (file >> from >> to >> weight)
        {
            graph->addEdge(from, to, weight);
            count++;
            cout << "   [" << count << "] Thêm cạnh: " << from << " → " << to
                 << " (weight: " << fixed << setprecision(2) << weight << ")" << endl;
        }

        file.close();
        return graph;
    }

    // Nhập từ bàn phím
    static GraphHashTable *inputFromConsole()
    {
        int V, E;
        cout << "Nhập số đỉnh (V): ";
        cin >> V;
        cout << "Nhập số cạnh (E): ";
        cin >> E;

        GraphHashTable *graph = new GraphHashTable(V, E);

        cout << "\nNhập " << E << " cạnh (from to weight):\n";
        for (int i = 0; i < E; i++)
        {
            int from, to;
            double weight;
            cout << "Cạnh " << (i + 1) << ": ";
            cin >> from >> to >> weight;
            graph->addEdge(from, to, weight);
        }

        return graph;
    }

    // Tìm kiếm cạnh
    bool searchEdge(int from, int to)
    {
        if (from < 0 || from >= V)
            return false;

        Edge *current = adjacencyList[from];
        while (current)
        {
            if (current->to == to)
            {
                cout << "🔍 Tìm thấy: " << from << " → " << to
                     << " (weight: " << fixed << setprecision(2) << current->weight << ")" << endl;
                return true;
            }
            current = current->next;
        }
        cout << "❌ Không tìm thấy cạnh: " << from << " → " << to << endl;
        return false;
    }
};

int main()
{
    cout << "╔═══════════════════════════════════════════════════════╗\n";
    cout << "║  EDGE-WEIGHTED DIGRAPH - HASH TABLE IMPLEMENTATION   ║\n";
    cout << "╚═══════════════════════════════════════════════════════╝\n\n";

    // Tự động đọc từ file test_bai3.txt
    cout << "Đọc từ file test_bai3.txt...\n\n";
    GraphHashTable *graph = GraphHashTable::readFromFile("test_bai3.txt");

    if (!graph)
    {
        cout << "❌ Lỗi khởi tạo graph!\n";
        return 1;
    }

    // Hiển thị hash table
    graph->displayHashTable();

    delete graph;

    return 0;
}

/*
╔════════════════════════════════════════════════════════════╗
║                    GIẢI THÍCH THUẬT TOÁN                   ║
╠════════════════════════════════════════════════════════════╣
║                                                            ║
║ 1. CẤU TRÚC DỮ LIỆU:                                       ║
║    - Hash Table: Mảng adjacencyList[V]                     ║
║    - Mỗi adj[i] là một linked list chứa các cạnh từ i     ║
║    - Key: Đỉnh xuất phát (from) → Index trong mảng        ║
║                                                            ║
║ 2. HASH FUNCTION:                                          ║
║    hash(from) = from (Direct addressing)                   ║
║    - Đơn giản, không cần tính toán                        ║
║    - adj[0] chứa cạnh từ đỉnh 0                           ║
║    - adj[1] chứa cạnh từ đỉnh 1, ...                      ║
║                                                            ║
║ 3. SEPARATE CHAINING:                                      ║
║    - Mỗi bucket (adj[i]) là một linked list               ║
║    - Nhiều cạnh từ cùng 1 đỉnh → nối vào linked list      ║
║    - INSERT AT HEAD: Luôn thêm vào đầu list               ║
║                                                            ║
║ 4. QUY TẮC THÊM CẠNH:                                      ║
║    - Cạnh thêm SAU sẽ đứng TRƯỚC trong list               ║
║    - VD: Thêm 4→5, sau đó 4→7                             ║
║      → adj[4]: [4→7] → [4→5]                              ║
║           (4→7 thêm sau nên đứng trước)                   ║
║                                                            ║
║ 5. VÍ DỤ:                                                  ║
║    Input theo thứ tự:                                      ║
║    4 5 0.35  ← Thêm đầu tiên                              ║
║    5 4 0.35                                                ║
║    4 7 0.37  ← Thêm sau, cùng from=4                      ║
║                                                            ║
║    Quá trình thêm vào adj[4]:                             ║
║    Bước 1: adj[4] = [4→5|0.35]                            ║
║    Bước 2: adj[4] = [4→7|0.37] → [4→5|0.35]              ║
║                     ↑ Thêm vào đầu!                       ║
║                                                            ║
║    Tương tự adj[5]:                                        ║
║    5 4 0.35  → adj[5] = [5→4|0.35]                        ║
║    5 7 0.28  → adj[5] = [5→7|0.28] → [5→4|0.35]          ║
║    5 1 0.32  → adj[5] = [5→1|0.32] → [5→7|0.28] → [5→4|0.35]  ║
║                        ↑ Cạnh cuối thêm, đứng đầu!        ║
║                                                            ║
║    KẾT QUẢ CUỐI:                                           ║
║    adj[0]: [0→2|0.26] → [0→4|0.38]                        ║
║           (0→4 thêm sau nên đứng sau)                     ║
║    adj[4]: [4→7|0.37] → [4→5|0.35]                        ║
║           (4→7 thêm sau nên đứng trước)                   ║
║    adj[5]: [5→1|0.32] → [5→7|0.28] → [5→4|0.35]          ║
║           (5→1 thêm cuối nên đứng đầu)                    ║
║    adj[6]: [6→4|0.93] → [6→0|0.58] → [6→2|0.40]          ║
║           (6→4 thêm cuối nên đứng đầu)                    ║
║                                                            ║
║ 6. ĐỘ PHỨC TẠP:                                            ║
║    - Insert: O(k) với k = số cạnh từ cùng 1 đỉnh          ║
║    - Search: O(k)                                          ║
║    - Space: O(V + E)                                       ║
║                                                            ║
╚════════════════════════════════════════════════════════════╝
*/
