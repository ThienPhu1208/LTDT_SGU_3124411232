#include <iostream>
using namespace std;

int main() {
    long long N;
    while (cin >> N) {
        long long soChuSo0 = 0;
        long long tam = N;
        while (tam > 0) {
            tam /= 5;
            soChuSo0 += tam;
        }
        cout << soChuSo0 << endl;
    }
    return 0;
}