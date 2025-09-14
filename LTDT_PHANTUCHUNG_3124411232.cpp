#include <iostream>
using namespace std;

int main() {
    int nx, ny, nz;
    int x[1000], y[1000], z[1000];
    int danhDau[10001] = { 0 };
    int ketQua[1000], dem = 0;

    cin >> nx;
    for (int i = 0; i < nx; i++) {
        cin >> x[i];
        danhDau[x[i]] = 1;
    }

    cin >> ny;
    for (int i = 0; i < ny; i++) {
        cin >> y[i];
        if (danhDau[y[i]] == 1) danhDau[y[i]] = 2;
    }

    cin >> nz;
    for (int i = 0; i < nz; i++) {
        cin >> z[i];
        if (danhDau[z[i]] == 2) danhDau[z[i]] = 3;
    }

    for (int i = 1; i <= 10000; i++) {
        if (danhDau[i] == 3) ketQua[dem++] = i;
    }

    cout << dem << endl;
    for (int i = 0; i < dem; i++) cout << ketQua[i] << " ";
    cout << endl;

    return 0;
}