#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("DanhSachCanh.inp");
    ofstream fout("DanhSachCanh.out");

    int n, m;
    fin >> n >> m;

    int degree[100005] = { 0 }; // đủ lớn cho n ≤ 10^5

    int u, v;
    for (int i = 0; i < m; i++) {
        fin >> u >> v;
        degree[u]++;
        degree[v]++;  // vì đồ thị vô hướng
    }

    // In ra đúng yêu cầu
    fout << n << '\n';
    cout << n << '\n';  // in ra màn hình
    for (int i = 1; i <= n; i++) {
        fout << degree[i] << '\n';
        cout << degree[i] << '\n';
    }

    fin.close();
    fout.close();
    return 0;
}
