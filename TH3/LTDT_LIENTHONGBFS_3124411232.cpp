#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int n, x;
int ke[100001][1001];  // danh sách kề
int soKe[100001];      // số đỉnh kề mỗi đỉnh
bool visited[100001];
int ketqua[100001];    // lưu các đỉnh liên thông
int q[100001];         // hàng đợi

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream fin("LienThongBFS.INP");
    ofstream fout("LienThongBFS.OUT");

    if (!fin) {
        cout << "Khong mo duoc file LienThongBFS.INP\n";
        return 0;
    }

    fin >> n >> x;
    for (int i = 1; i <= n; i++) {
        int v;
        soKe[i] = 0;
        while (fin >> v) {
            if (v == -1) break;
            ke[i][soKe[i]++] = v;
        }
    }

    // Thuật toán BFS
    memset(visited, false, sizeof(visited));
    int front = 0, rear = 0;
    q[rear++] = x;
    visited[x] = true;
    int dem = 0;

    while (front < rear) {
        int u = q[front++];
        if (u != x) ketqua[dem++] = u; // không ghi lại chính x
        for (int i = 0; i < soKe[u]; i++) {
            int v = ke[u][i];
            if (!visited[v]) {
                visited[v] = true;
                q[rear++] = v;
            }
        }
    }

    // Xuất kết quả ra file
    fout << dem << "\n";
    for (int i = 0; i < dem; i++)
        fout << ketqua[i] << (i + 1 == dem ? '\n' : ' ');

    fin.close();
    fout.close();
    return 0;
}

