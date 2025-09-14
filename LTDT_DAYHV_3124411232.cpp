#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    int s[100001] = { 0 };
    bool laHoanVi = true;

    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        if (x < 1 || x > N || s[x] == 1) {
            laHoanVi = false;
        }
        s[x] = 1;
    }

    cout << (laHoanVi ? "YES" : "NO") << '\n';
    return 0;
}
