#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream fin("DanhSachKe.inp");
    ofstream fout("DanhSachKe.out");
    if (!fin) { cerr << "Không mở được file vào.\n"; return 1; }

    int n;
    fin >> n;
    string line;
    getline(fin, line); // đọc bỏ newline sau số n

    vector<int> bac(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (!getline(fin, line)) line = ""; // nếu dòng rỗng hoặc file kết thúc sớm
        stringstream ss(line);
        int x;
        while (ss >> x) {
            if (x == -1) break;  // gặp -1 thì dừng đọc
            bac[i]++;            // mỗi đỉnh kề -> tăng bậc
        }
    }

    //  In ra màn hình và ghi file
    cout << n << '\n';
    fout << n << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << bac[i] << '\n';
        fout << bac[i] << '\n';
    }

    return 0;
}
