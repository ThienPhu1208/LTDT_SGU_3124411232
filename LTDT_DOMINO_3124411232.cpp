#include <iostream>
#include <cstring>
using namespace std;

int n;
int domA[200], domB[200]; // Lưu từng quân domino
int adj[7][200];          // adj[x][k] = id của quân domino k nối với x
int deg[7];               // bậc của mỗi đỉnh
int used[200];            // quân domino đã dùng chưa
int stackV[200], top;     // ngăn xếp đỉnh
int result[200], rTop;    // kết quả: thứ tự id quân domino

// DFS dùng ngăn xếp để tìm chu trình Euler
void Hierholzer(int start)
{
    top = 0;
    stackV[top++] = start;
    while (top > 0)
    {
        int u = stackV[top - 1];
        int i;
        for (i = 0; i < n; i++)
        {
            if (!used[i] && (domA[i] == u || domB[i] == u))
            {
                used[i] = 1;
                int v = (domA[i] == u) ? domB[i] : domA[i];
                stackV[top++] = v;
                break;
            }
        }
        if (i == n) // không còn cạnh đi tiếp
        {
            top--;
            if (top > 0)
            {
                // lấy id quân domino nối 2 đỉnh stackV[top-1] và stackV[top]
                for (int k = 0; k < n; k++)
                {
                    if (used[k] == 1 &&
                        ((domA[k] == stackV[top - 1] && domB[k] == u) ||
                            (domB[k] == stackV[top - 1] && domA[k] == u)))
                    {
                        if (used[k] == 1)
                        {
                            result[rTop++] = k;
                            used[k] = 2; // đánh dấu đã ghi vào kết quả
                            break;
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    cin >> n;
    memset(deg, 0, sizeof(deg));
    for (int i = 0; i < n; i++)
    {
        cin >> domA[i] >> domB[i];
        deg[domA[i]]++;
        deg[domB[i]]++;
    }

    // Kiểm tra bậc chẵn
    for (int i = 0; i <= 6; i++)
        if (deg[i] % 2 != 0)
        {
            cout << 0 << "\n";
            return 0;
        }

    // Tìm đỉnh bắt đầu
    int start = -1;
    for (int i = 0; i <= 6; i++)
        if (deg[i] > 0) { start = i; break; }

    if (start == -1)
    {
        cout << 1 << "\n"; // không có quân nào
        return 0;
    }

    // Kiểm tra liên thông (DFS đơn giản)
    int stack2[10], top2 = 0, vis[7];
    memset(vis, 0, sizeof(vis));
    stack2[top2++] = start;
    vis[start] = 1;
    while (top2 > 0)
    {
        int u = stack2[--top2];
        for (int k = 0; k < n; k++)
        {
            if (domA[k] == u && !vis[domB[k]])
            {
                vis[domB[k]] = 1;
                stack2[top2++] = domB[k];
            }
            if (domB[k] == u && !vis[domA[k]])
            {
                vis[domA[k]] = 1;
                stack2[top2++] = domA[k];
            }
        }
    }
    for (int i = 0; i <= 6; i++)
        if (deg[i] > 0 && !vis[i])
        {
            cout << 0 << "\n";
            return 0;
        }

    // Tìm đường Euler
    rTop = 0;
    memset(used, 0, sizeof(used));
    Hierholzer(start);

    if (rTop != n)
    {
        cout << 0 << "\n";
        return 0;
    }

    cout << 1 << "\n";
    // In ra các quân domino theo thứ tự đã dùng
    // (đường đi Euler)
    for (int i = rTop - 1; i >= 0; i--)
        cout << domA[result[i]] << " " << domB[result[i]] << "\n";

    return 0;
}