#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX = 1005; // Dùng n nhỏ để dễ chạy ví dụ, n <= 1e5 cần danh sách động
int n, x;
int a[MAX][MAX]; // Ma trận kề
bool visited[MAX];
int ketQua[MAX];
int dem = 0;

void DFS(int u)
{
    visited[u] = true;
    ketQua[dem++] = u;
    for (int v = 1; v <= n; v++)
    {
        if (a[u][v] && !visited[v])
            DFS(v);
    }
}

int main()
{
    ifstream fin("LienThongDFS.INP");
    ofstream fout("LienThongDFS.OUT");

    fin >> n >> x;
    memset(a, 0, sizeof(a));
    memset(visited, false, sizeof(visited));

    // Đọc danh sách kề
    for (int i = 1; i <= n; i++)
    {
        int v;
        while (fin >> v && v != -1)
        {
            a[i][v] = a[v][i] = 1;
        }
    }

    DFS(x);

    fout << dem << "\n";
    for (int i = 0; i < dem; i++)
        fout << ketQua[i] << (i == dem - 1 ? "" : " ");
    fout << "\n";

    fin.close();
    fout.close();
    return 0;
}
