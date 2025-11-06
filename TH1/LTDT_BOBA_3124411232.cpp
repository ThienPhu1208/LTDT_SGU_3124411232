#include <iostream>
#include <cstring>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        char s[1000005];
        cin >> s;

        int n = 0;
        while (s[n] != '\0') n++;

        int maxCount = 0;
        for (int i = 0; i <= n - 3; i++) {
            int count = 1;
            for (int j = i + 1; j <= n - 3; j++) {
                if (s[i] == s[j] && s[i + 1] == s[j + 1] && s[i + 2] == s[j + 2]) {
                    count++;
                }
            }
            if (count > maxCount) {
                maxCount = count;
            }
        }

        cout << maxCount << endl;
    }
    return 0;
}