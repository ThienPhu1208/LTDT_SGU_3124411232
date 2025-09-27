#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>
using namespace std;

const int MAX = 1005;   // demo nhỏ, n lớn cần cấu trúc động
int n, x;
int a[MAX][MAX];        // ma trận kề
bool visited[MAX];
int ketQua[MAX];
int dem = 0;

void DFS_KhongDeQuy(int start)
{
    stack<int> st;
    st.push(start);
    visited[start] = true;

    while (!st.empty())
    {
        int u = st.top();
        st.pop();
        ketQua[dem++] = u;

        // duyệt tất cả đỉnh kề u
        for (int v = 1; v <= n; v++)
        {
            if (a[u][v] && !visited[v])
            {
                visited[v] = true;
                st.push(v);
            }
        }
    }
}

int main()
{
    ifstream fin("LienThongDFS_KhongDeQuy.INP");
    ofstream fout("LienThongDFS_KhongDeQuy.OUT");

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

    DFS_KhongDeQuy(x);

    fout << dem << "\n";
    for (int i = 0; i < dem; i++)
        fout << ketQua[i] << (i == dem - 1 ? "" : " ");
    fout << "\n";

    fin.close();
    fout.close();
    return 0;
}
