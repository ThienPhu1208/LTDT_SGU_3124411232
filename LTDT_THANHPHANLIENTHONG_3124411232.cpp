#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int n;
int ke[100001][1001];    // danh sách kề
int soKe[100001];        // số đỉnh kề của mỗi đỉnh
bool visited[100001];
int q[100001];           // hàng đợi
int comp[100001][1001];  // lưu các đỉnh của từng thành phần
int sizeComp[100001];    // số đỉnh trong từng thành phần

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream fin("ThanhPhanLienThong.INP");
    ofstream fout("ThanhPhanLienThong.OUT");

    if (!fin) {
        cout << "Khong mo duoc file ThanhPhanLienThong.INP\n";
        return 0;
    }

    fin >> n;
    for (int i = 1; i <= n; i++) {
        int v;
        soKe[i] = 0;
        while (fin >> v) {
            if (v == -1) break;
            ke[i][soKe[i]++] = v;
        }
    }

    memset(visited, false, sizeof(visited));
    int soTP = 0; // số thành phần liên thông

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            // BFS tìm thành phần liên thông bắt đầu từ i
            int front = 0, rear = 0;
            q[rear++] = i;
            visited[i] = true;
            sizeComp[soTP] = 0;

            while (front < rear) {
                int u = q[front++];
                comp[soTP][sizeComp[soTP]++] = u;

                for (int k = 0; k < soKe[u]; k++) {
                    int v = ke[u][k];
                    if (!visited[v]) {
                        visited[v] = true;
                        q[rear++] = v;
                    }
                }
            }
            soTP++;
        }
    }

    // Ghi kết quả ra file
    fout << soTP << "\n";
    for (int i = 0; i < soTP; i++) {
        for (int j = 0; j < sizeComp[i]; j++) {
            fout << comp[i][j] << (j + 1 == sizeComp[i] ? '\n' : ' ');
        }
    }

    fin.close();
    fout.close();
    return 0;
}
