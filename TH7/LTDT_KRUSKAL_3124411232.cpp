#include <iostream>
#include <vector>
#include<fstream>
#include <algorithm>
using namespace std;


#define FI "test.inp"

struct Edge {
    int u, v, w;
};

int n, m;
vector<Edge> edges;
vector<Edge> MST;
int parent[1001], rankSet[1001];
int totalWeight = 0;

// Tìm gốc của tập chứa đỉnh u
int findSet(int u) {
    if (u != parent[u])
        parent[u] = findSet(parent[u]); // nén đường đi
    return parent[u];
}

// Hợp nhất 2 tập
void unionSet(int u, int v) {
    u = findSet(u);
    v = findSet(v);
    if (u == v) return;

    if (rankSet[u] < rankSet[v]) parent[u] = v;
    else if (rankSet[u] > rankSet[v]) parent[v] = u;
    else {
        parent[v] = u;
        rankSet[u]++;
    }
}

int main() {

    ifstream fi (FI);



    fi >> n >> m;
    edges.resize(m);

    // Nhập danh sách cạnh
    for (int i = 0; i < m; i++)
        fi >> edges[i].u >> edges[i].v >> edges[i].w;

    // Khởi tạo DSU
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rankSet[i] = 0;
    }

    // Sắp xếp cạnh theo trọng số tăng dần
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.w < b.w;
        });

    // Thuật toán Kruskal
    for (auto e : edges) {
        int u = e.u, v = e.v, w = e.w;
        if (findSet(u) != findSet(v)) {
            unionSet(u, v);
            MST.push_back(e);
            totalWeight += w;
            if ((int)MST.size() == n - 1) break;
        }
    }

    // In kết quả
    cout << MST.size() << " " << totalWeight << endl;
    for (auto e : MST)
        cout << e.u << " " << e.v << " " << e.w << endl;

    return 0;
}
