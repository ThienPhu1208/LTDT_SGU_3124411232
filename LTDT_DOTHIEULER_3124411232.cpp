#include <iostream>
#include <stack>
using namespace std;

const int MAX = 105;   // Tăng nếu cần
int n;
int a[MAX][MAX];       // Ma trận số cạnh
int deg[MAX];          // Bậc mỗi đỉnh
int path[MAX * MAX * 2];   // Lưu kết quả (đủ lớn)
int pos = 0;

void DFScheck(int u, bool visited[]) {
    visited[u] = true;
    for (int v = 1; v <= n; v++)
        if (a[u][v] > 0 && !visited[v])
            DFScheck(v, visited);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            deg[i] += a[i][j];
        }

    // Kiểm tra bậc chẵn
    for (int i = 1; i <= n; i++)
        if (deg[i] % 2 != 0) {
            cout << 0 << "\n";
            return 0;
        }

    // Kiểm tra liên thông
    int start = -1;
    for (int i = 1; i <= n; i++)
        if (deg[i] > 0) { start = i; break; }
    if (start == -1) {  // Không có cạnh nào
        cout << 1 << "\n1\n";
        return 0;
    }
    bool visited[MAX] = {};
    DFScheck(start, visited);
    for (int i = 1; i <= n; i++)
        if (deg[i] > 0 && !visited[i]) {
            cout << 0 << "\n";
            return 0;
        }

    // Hierholzer đơn giản với ma trận
    stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int u = st.top();
        int v;
        for (v = 1; v <= n; v++)
            if (a[u][v] > 0) break;
        if (v <= n) {
            st.push(v);
            a[u][v]--;      // Giảm số cạnh hai chiều
            a[v][u]--;
        }
        else {
            path[pos++] = u;
            st.pop();
        }
    }

    cout << 1 << "\n";
    for (int i = pos - 1; i >= 0; i--) {
        cout << path[i];
        if (i) cout << ' ';
    }
    cout << "\n";
    return 0;
}
