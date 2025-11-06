#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;

int n;
int a[105][105];     // Ma trận kề (1-based)
bool visited[105];   // Đánh dấu liên thông
vector<int> euler;   // Lưu chu trình Euler

// Duyệt DFS để kiểm tra liên thông (chỉ để kiểm tra, vẫn dùng đệ quy nhỏ)
void dfs(int u) {
    visited[u] = true;
    for (int v = 1; v <= n; v++)
        if (a[u][v] > 0 && !visited[v])
            dfs(v);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];

    // 1️ Kiểm tra bậc chẵn
    for (int i = 1; i <= n; i++) {
        int deg = 0;
        for (int j = 1; j <= n; j++) deg += a[i][j];
        if (deg % 2 != 0) {
            cout << 0 << "\n";
            return 0;
        }
    }

    // 2 Kiểm tra liên thông (bỏ các đỉnh cô lập)
    int start = -1;
    for (int i = 1; i <= n; i++) {
        int deg = 0;
        for (int j = 1; j <= n; j++) deg += a[i][j];
        if (deg > 0) { start = i; break; }
    }

    if (start == -1) { // Đồ thị rỗng
        cout << 1 << "\n"; // Chu trình rỗng vẫn hợp lệ
        return 0;
    }

    memset(visited, 0, sizeof(visited));
    dfs(start);
    for (int i = 1; i <= n; i++) {
        int deg = 0;
        for (int j = 1; j <= n; j++) deg += a[i][j];
        if (deg > 0 && !visited[i]) {
            cout << 0 << "\n";
            return 0;
        }
    }

    // 3️ Thuật toán Hierholzer không đệ quy
    stack<int> st;
    st.push(start);

    while (!st.empty()) {
        int u = st.top();
        bool found = false;
        for (int v = 1; v <= n; v++) {
            if (a[u][v] > 0) {        // còn cạnh
                st.push(v);
                a[u][v]--;            // xóa cạnh hai chiều
                a[v][u]--;
                found = true;
                break;
            }
        }
        if (!found) {                 // không còn cạnh, thêm vào kết quả
            euler.push_back(u);
            st.pop();
        }
    }

    // 4 In kết quả
    cout << 1 << "\n";
    for (int i = 0; i < (int)euler.size(); i++)
        cout << euler[i] << (i + 1 == (int)euler.size() ? '\n' : ' ');

    return 0;
}