#include <iostream>
#include <cstring>   // memset
using namespace std;

int n;                      // Số đỉnh của đồ thị
int MT[105][105];           // Ma trận kề (1..n)
int duongDi[105];           // Lưu đường đi đang xét
bool daDi[105];             // Đánh dấu đỉnh đã đi
bool timThay = false;       // Đã tìm được chu trình chưa?

// Hàm quay lui
void TimChuTrinh(int viTri)
{
    if (timThay) return; // Nếu đã tìm thấy thì dừng

    // Nếu đã đi qua n đỉnh
    if (viTri == n)
    {
        // Kiểm tra có cạnh nối từ đỉnh cuối về đỉnh đầu không
        if (MT[duongDi[n - 1]][duongDi[0]] == 1)
        {
            cout << 1 << "\n";
            for (int i = 0; i < n; i++)
                cout << duongDi[i] << " ";
            cout << duongDi[0] << "\n"; // Quay về đỉnh đầu
            timThay = true;
        }
        return;
    }

    int dinhTruoc = duongDi[viTri - 1];
    // Thử đi đến từng đỉnh chưa đi và có cạnh nối
    for (int dinh = 1; dinh <= n; dinh++)
    {
        if (!daDi[dinh] && MT[dinhTruoc][dinh] == 1)
        {
            duongDi[viTri] = dinh;
            daDi[dinh] = true;

            TimChuTrinh(viTri + 1);

            daDi[dinh] = false; // quay lui
            if (timThay) return;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> MT[i][j];

    // Bắt đầu từ đỉnh 1 (có thể đổi nếu muốn thử đỉnh khác)
    memset(daDi, false, sizeof(daDi));
    duongDi[0] = 1;
    daDi[1] = true;

    TimChuTrinh(1);

    if (!timThay)
        cout << 0 << "\n";

    return 0;
}