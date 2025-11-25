#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;  // n: số thành phố, m: số cạnh

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> color(n + 1, 0);
    int maxColor = 0;

    for (int i = 1; i <= n; i++) {
        vector<bool> used(n + 1, false);
        for (int j : adj[i])
            if (color[j] != 0)
                used[color[j]] = true;

        int c;
        for (c = 1; c <= n; c++)
            if (!used[c]) break;

        color[i] = c;
        if (c > maxColor) maxColor = c;
    }

    cout << maxColor << "\n";
    for (int c = 1; c <= maxColor; c++) {
        for (int i = 1; i <= n; i++)
            if (color[i] == c)
                cout << i << " ";
        cout << "\n";
    }

    return 0;
}
