#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX = 1005;   // với n <= 1e5 thì cần danh sách động, ở đây demo ví dụ nhỏ
int n, x, y;
int a[MAX][MAX];        // ma trận kề
bool visited[MAX];
int parent[MAX];        // lưu đỉnh cha để truy vết đường đi
bool found = false;

void DFS(int u)
{
    if (found) return;      // đã tìm thấy y thì dừng
    visited[u] = true;
    if (u == y)
    {
        found = true;
        return;
    }
    for (int v = 1; v <= n; v++)
    {
        if (a[u][v] && !visited[v])
        {
            parent[v] = u;
            DFS(v);
            if (found) return; // nếu đã tìm thấy, dừng sớm
        }
    }
}

int main()
{
    ifstream fin("DuongDiDFS.INP");
    ofstream fout("DuongDiDFS.OUT");

    fin >> n >> x >> y;
    memset(a, 0, sizeof(a));
    memset(visited, false, sizeof(visited));
    memset(parent, -1, sizeof(parent));

    // đọc danh sách kề
    for (int i = 1; i <= n; i++)
    {
        int v;
        while (fin >> v && v != -1)
        {
            a[i][v] = a[v][i] = 1;
        }
    }

    DFS(x);

    if (!found)
    {
        fout << "0\n"; // không có đường đi
    }
    else
    {
        // truy vết đường đi ngược từ y về x
        int path[MAX];
        int k = 0;
        for (int v = y; v != -1; v = parent[v])
            path[k++] = v;

        fout << k << "\n";
        for (int i = k - 1; i >= 0; i--)
        {
            fout << path[i];
            if (i > 0) fout << " ";
        }
        fout << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
