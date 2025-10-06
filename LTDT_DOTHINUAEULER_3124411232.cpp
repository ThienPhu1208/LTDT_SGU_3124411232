#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 105;  // n ≤ 1e5, nhưng minh họa nhỏ
int n;
int a[MAX][MAX];
int deg[MAX];
int used[MAX][MAX];
int path[MAX * MAX];
int pTop;

void dfs_check(int u, int visited[])
{
    visited[u] = 1;
    for (int v = 1; v <= n; v++)
        if (a[u][v] && !visited[v])
            dfs_check(v, visited);
}

// Hierholzer tìm đường đi Euler
void euler(int u)
{
    for (int v = 1; v <= n; v++)
    {
        while (a[u][v] > 0)
        {
            a[u][v]--;
            a[v][u]--;
            euler(v);
        }
    }
    path[pTop++] = u;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> a[i][j];
            deg[i] += a[i][j];
        }

    // Đếm đỉnh bậc lẻ
    int odd[2], oddCount = 0;
    for (int i = 1; i <= n; i++)
        if (deg[i] % 2 == 1)
        {
            if (oddCount < 2) odd[oddCount] = i;
            oddCount++;
        }

    // Kiểm tra liên thông (bỏ đỉnh cô lập)
    int visited[MAX];
    memset(visited, 0, sizeof(visited));
    int start = 1;
    while (start <= n && deg[start] == 0) start++;
    if (start <= n) dfs_check(start, visited);

    for (int i = 1; i <= n; i++)
        if (deg[i] > 0 && !visited[i])
        {
            cout << 0 << "\n";
            return 0;
        }

    // Nửa Euler cần đúng 2 đỉnh lẻ
    if (oddCount != 2)
    {
        cout << 0 << "\n";
        return 0;
    }

    // Tìm đường Euler bắt đầu từ 1 trong 2 đỉnh lẻ
    pTop = 0;
    euler(odd[0]);

    cout << 1 << "\n";
    for (int i = pTop - 1; i >= 0; i--)
        cout << path[i] << (i ? ' ' : '\n');

    return 0;
}