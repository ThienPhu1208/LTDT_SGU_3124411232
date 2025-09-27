#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int n, x, y;
int ke[100001][1001];   // danh sách kề
int soKe[100001];       // số đỉnh kề mỗi đỉnh
bool visited[100001];
int truoc[100001];      // lưu đỉnh cha trong BFS
int q[100001];          // hàng đợi
int duongdi[100001];    // mảng lưu kết quả đường đi

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream fin("DuongDiBFS.INP");
    ofstream fout("DuongDiBFS.OUT");

    if (!fin) {
        cout << "Khong mo duoc file DuongDiBFS.INP\n";
        return 0;
    }

    // Đọc dữ liệu
    fin >> n >> x >> y;
    for (int i = 1; i <= n; i++) {
        int v;
        soKe[i] = 0;
        while (fin >> v) {
            if (v == -1) break;
            ke[i][soKe[i]++] = v;
        }
    }

    // BFS
    memset(visited, false, sizeof(visited));
    memset(truoc, -1, sizeof(truoc));

    int front = 0, rear = 0;
    q[rear++] = x;
    visited[x] = true;

    while (front < rear) {
        int u = q[front++];
        for (int i = 0; i < soKe[u]; i++) {
            int v = ke[u][i];
            if (!visited[v]) {
                visited[v] = true;
                truoc[v] = u; // ghi nhận cha của v
                q[rear++] = v;
                if (v == y) break; // đã tìm thấy y, có thể dừng
            }
        }
    }

    // Truy vết đường đi từ y ngược về x
    int dem = 0;
    if (!visited[y]) {
        fout << "0\n"; // không có đường đi
    }
    else {
        int cur = y;
        while (cur != -1) {
            duongdi[dem++] = cur;
            cur = truoc[cur];
        }

        // Đảo ngược mảng để có thứ tự từ x -> y
        fout << dem << "\n";
        for (int i = dem - 1; i >= 0; i--) {
            fout << duongdi[i];
            if (i > 0) fout << " ";
        }
        fout << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
