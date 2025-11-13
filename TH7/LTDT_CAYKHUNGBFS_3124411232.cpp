#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

#define FI "test.inp"

int n, m;
vector<int> adj[1001];
bool visited[1001];
vector<pair<int, int>> tree; // Lưu các cạnh trong cây khung

void BFS(int start) {
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                tree.push_back({ u, v }); // Lưu cạnh thuộc cây khung
                q.push(v);
            }
        }
    }
}

int main() {
    ifstream fi(FI);
    fi >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        fi >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Bắt đầu BFS từ đỉnh 1
    BFS(1);

    // In kết quả ra màn hình
    cout << tree.size() << endl;
    for (auto e : tree)
        cout << e.first << " " << e.second << endl;

    return 0;
}
