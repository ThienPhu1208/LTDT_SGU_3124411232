#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX = 10005;
int n, x, y, z;
int a[MAX][MAX]; // Ma trận kề (dùng với n nhỏ hơn, nếu n lớn phải dùng danh sách kề động)
int deg[MAX];    // Bậc mỗi đỉnh
bool visited[MAX];
int queueBFS[MAX];

void BFS(int start) {
    int front = 0, back = 0;
    visited[start] = true;
    queueBFS[back++] = start;
    while (front < back) {
        int u = queueBFS[front++];
        for (int v = 1; v <= n; v++) {
            if (a[u][v] && !visited[v]) {
                visited[v] = true;
                queueBFS[back++] = v;
            }
        }
    }
}

int demTPLT() {
    memset(visited, false, sizeof(visited));
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            cnt++;
            BFS(i);
        }
    }
    return cnt;
}

int main() {
    ifstream fin("CanhCauDinhKhopBFS.INP");
    ofstream fout("CanhCauDinhKhopBFS.OUT");

    fin >> n >> x >> y >> z;
    memset(a, 0, sizeof(a));
    memset(deg, 0, sizeof(deg));

    for (int i = 1; i <= n; i++) {
        int v;
        while (fin >> v && v != -1) {
            a[i][v] = a[v][i] = 1;
        }
    }

    // Đếm thành phần liên thông ban đầu
    int tpBanDau = demTPLT();

    // --- Kiểm tra cạnh cầu ---
    a[x][y] = a[y][x] = 0; // tạm bỏ cạnh (x,y)
    int tpMoi = demTPLT();
    if (tpMoi > tpBanDau) fout << "canh cau\n";
    else fout << "khong la canh cau\n";
    a[x][y] = a[y][x] = 1; // khôi phục

    // --- Kiểm tra đỉnh khớp ---
    for (int i = 1; i <= n; i++) a[z][i] = a[i][z] = 0; // tạm bỏ đỉnh z
    int tpMoi2 = demTPLT();
    bool isolated = true;
    for (int i = 1; i <= n; i++) if (deg[i] > 0 && i != z) isolated = false;
    if (tpMoi2 > tpBanDau) fout << "dinh khop\n";
    else fout << "khong la dinh khop\n";

    fin.close();
    fout.close();

    return 0;
}
