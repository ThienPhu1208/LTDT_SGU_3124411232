#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#define FI "test.inp"

int n, m;
vector<int> adj[1001];
bool visited[1001];
vector<pair<int, int>> tree;

void DFS(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            tree.push_back({ u, v });
            DFS(v);
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

    DFS(1);

    cout << tree.size() << endl;
    for (auto e : tree)
        cout << e.first << " " << e.second << endl;

    return 0;
}
