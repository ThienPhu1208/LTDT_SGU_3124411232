#include <iostream>
using namespace std;

bool laNguyenTo(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

int demSoMu(int n, int p) {
    int kq = 0;
    while (n > 0) {
        n /= p;
        kq += n;
    }
    return kq;
}

int main() {
    int N;
    while (cin >> N) {
        for (int i = 2; i <= N; i++) {
            if (laNguyenTo(i)) {
                int soMu = demSoMu(N, i);
                cout << soMu << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
