#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

using Weight = long long;

const Weight INF = 1e18;

void floyd_warshall(int n, vector<vector<Weight>>& dist) {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;

    if (!(cin >> n >> m)) return 0;

    vector<vector<Weight>> dist(n + 1, vector<Weight>(n + 1, INF));

    for (int i = 1; i <= n; ++i) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        Weight w;
        cin >> u >> v >> w;

        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }

    floyd_warshall(n, dist);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (dist[i][j] == INF) {
                cout << dist[i][j] << (j == n ? "" : " ");
            }
            else {
                cout << dist[i][j] << (j == n ? "" : " ");
            }
        }
        cout << "\n";
    }

    return 0;
}