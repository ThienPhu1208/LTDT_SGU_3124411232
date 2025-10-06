#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;

struct Edge {
    int to;
    int id; // ID của cạnh để đánh dấu đã dùng
};

int n, m;                   // n: số đỉnh, m: số cạnh
vector<vector<Edge>> adj;    // danh sách kề
vector<bool> used;           // used[id] = true nếu cạnh đã được đi
vector<int> deg;             // bậc của từng đỉnh
vector<int> euler;           // kết quả chu trình

// DFS nhỏ để kiểm tra liên thông
void dfs(int u, vector<int>& vis) {
    vis[u] = 1;
    for (auto& e : adj[u])
        if (!vis[e.to]) dfs(e.to, vis);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    adj.assign(n + 1, {});
    deg.assign(n + 1, 0);
    used.assign(m + 1, false);

    // Nhập m cạnh
    // Đồ thị vô hướng: mỗi cạnh có ID duy nhất
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({ v, i });
        adj[v].push_back({ u, i });
        deg[u]++; deg[v]++;
    }

    // 1 Kiểm tra bậc chẵn
    for (int i = 1; i <= n; i++) {
        if (deg[i] % 2 != 0) {
            cout << 0 << "\n";
            return 0;
        }
    }

    // 2 Kiểm tra liên thông (bỏ đỉnh bậc 0)
    int start = -1;
    for (int i = 1; i <= n; i++)
        if (deg[i] > 0) { start = i; break; }

    if (start == -1) { // không có cạnh nào
        cout << 1 << "\n";
        return 0;
    }

    vector<int> vis(n + 1, 0);
    dfs(start, vis);
    for (int i = 1; i <= n; i++)
        if (deg[i] > 0 && !vis[i]) {
            cout << 0 << "\n";
            return 0;
        }

    // 3 Hierholzer không đệ quy
    stack<int> st;
    vector<int> idx(n + 1, 0); // chỉ số cạnh đang xét
    st.push(start);

    while (!st.empty()) {
        int u = st.top();
        while (idx[u] < (int)adj[u].size() && used[adj[u][idx[u]].id])
            idx[u]++; // bỏ qua cạnh đã dùng

        if (idx[u] == (int)adj[u].size()) {
            // không còn cạnh, thêm u vào kết quả
            euler.push_back(u);
            st.pop();
        }
        else {
            Edge e = adj[u][idx[u]];
            used[e.id] = true;
            st.push(e.to);
        }
    }

    // 4 In kết quả
    cout << 1 << "\n";
    for (int i = 0; i < (int)euler.size(); i++) {
        cout << euler[i];
        if (i + 1 < (int)euler.size()) cout << " ";
    }
    cout << "\n";

    return 0;
}