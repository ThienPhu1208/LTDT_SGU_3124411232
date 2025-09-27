#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 1005; // demo, với n lớn hơn cần cấp phát động
int n;
int a[MAX][MAX];
int color[MAX]; // 0: chưa tô, 1: màu 1, -1: màu 2

bool BFS(int start)
{
    queue<int> q;
    q.push(start);
    color[start] = 1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 1; v <= n; v++)
        {
            if (a[u][v])
            {
                if (color[v] == 0)
                {
                    color[v] = -color[u];
                    q.push(v);
                }
                else if (color[v] == color[u])
                {
                    return false; // cùng màu -> không phân đôi
                }
            }
        }
    }
    return true;
}

int main()
{
    ifstream fin("DoThiPhanDoi.INP");
    ofstream fout("DoThiPhanDoi.OUT");

    fin >> n;
    memset(a, 0, sizeof(a));
    memset(color, 0, sizeof(color));

    for (int i = 1; i <= n; i++)
    {
        int v;
        while (fin >> v && v != -1)
        {
            a[i][v] = a[v][i] = 1;
        }
    }

    bool ok = true;
    for (int i = 1; i <= n && ok; i++)
    {
        if (color[i] == 0)
        {
            if (!BFS(i)) ok = false;
        }
    }

    if (ok) fout << "Do thi phan doi\n";
    else    fout << "Do thi khong phan doi\n";

    fin.close();
    fout.close();
    return 0;
}
