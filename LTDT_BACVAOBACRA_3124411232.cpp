#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("BacVaoBacRa.inp");
    ofstream fout("BacVaoBacRa.out");
    if (!fin) {
        cerr << "Không mở được file vào.\n";
        return 1;
    }
    int n;
    fin >> n;
    int indeg[1000] = { 0 };
    int outdeg[1000] = { 0 };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x;
            fin >> x;
            if (x) {
                outdeg[i]++;
                indeg[j]++;
            }
        }
    }

    fout << n << '\n';
    for (int i = 0; i < n; ++i) {
        fout << indeg[i] << ' ' << outdeg[i] << '\n';
    }

    // In ra màn hình để kiểm tra nhanh (không bắt buộc)
    cout << "Da ghi ket qua ra BacVaoBacRa.out\n";
    cout << n << '\n';
    for (int i = 0; i < n; ++i) cout << indeg[i] << ' ' << outdeg[i] << '\n';

    return 0;
}
