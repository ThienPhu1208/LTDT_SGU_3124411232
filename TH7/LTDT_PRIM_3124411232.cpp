#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

struct Edge {
    int to, weight;
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

int n, m;
vector<pair<int, int>> adj[1001]; // adj[u] = {v, w}
bool visited[1001];
int totalWeight = 0;
vector<pair<int, int>> MST; // Lưu các cạnh trong cây khung

void Prim(int start) {
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq; // Hàng đợi ưu tiên theo trọng số

    visited[start] = true;
    for (auto e : adj[start]) {
        pq.push({ e.first, e.second });
    }

    while (!pq.empty()) {
        Edge cur = pq.top(); pq.pop();
        int v = cur.to;
        int w = cur.weight;

        if (visited[v]) continue; // Bỏ qua đỉnh đã thăm

        // Thêm cạnh vào cây khung
        visited[v] = true;
        totalWeight += w;
        MST.push_back({ v, w });

        // Đưa các cạnh kề vào hàng đợi
        for (auto next : adj[v]) {
            if (!visited[next.first]) pq.push({ next.first, next.second });
        }
    }
}

int main() {
    ifstream fin("test.inp");
    if (!fin.is_open()) {
        cout << "Khong mo duoc file test.inp!\n";
        return 0;
    }

    fin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w });
    }
    fin.close();

    Prim(1); // Bắt đầu từ đỉnh 1

    cout << "Cac canh thuoc cay khung nho nhat (theo Prim):\n";
    for (auto e : MST)
        cout << "Canh noi toi dinh " << e.first << " co trong so = " << e.second << endl;
    cout << "Tong trong so cay khung = " << totalWeight << endl;

    return 0;
}
