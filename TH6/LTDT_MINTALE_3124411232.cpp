#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>
using namespace std;

struct Node {
    int x, y;
    int cost;
    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, xi, yi, xj, yj;
    cin >> N >> M >> xi >> yi >> xj >> yj;

    vector<vector<int>> A(N + 1, vector<int>(M + 1));
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            cin >> A[i][j];

    // Kiểm tra ô đầu/cuối có hợp lệ không
    if (A[xi][yi] == 0 || A[xj][yj] == 0) {
        cout << 0;
        return 0;
    }

    const int INF = 1e9;
    vector<vector<int>> dist(N + 1, vector<int>(M + 1, INF));
    vector<vector<pair<int, int>>> parent(N + 1, vector<pair<int, int>>(M + 1, { -1, -1 }));

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    dist[xi][yi] = 0;
    pq.push({ xi, yi, 0 });

    int dx[4] = { 1, -1, 0, 0 };
    int dy[4] = { 0, 0, 1, -1 };

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        if (cur.cost != dist[cur.x][cur.y])
            continue;

        if (cur.x == xj && cur.y == yj)
            break;

        for (int k = 0; k < 4; ++k) {
            int nx = cur.x + dx[k];
            int ny = cur.y + dy[k];
            if (nx < 1 || nx > N || ny < 1 || ny > M) continue;
            if (A[nx][ny] == 0) continue;

            int newCost = cur.cost + ((nx == xj && ny == yj) ? 0 : A[nx][ny]);
            if (newCost < dist[nx][ny]) {
                dist[nx][ny] = newCost;
                parent[nx][ny] = { cur.x, cur.y };
                pq.push({ nx, ny, newCost });
            }
        }
    }

    if (dist[xj][yj] == INF) {
        cout << 0;
        return 0;
    }

    cout << 1 << "\n";
    cout << dist[xj][yj] << "\n";

    // Khôi phục đường đi
    vector<pair<int, int>> path;
    int cx = xj, cy = yj;
    while (cx != -1 && cy != -1) {
        path.push_back({ cx, cy });
        auto p = parent[cx][cy];
        cx = p.first;
        cy = p.second;
    }
    reverse(path.begin(), path.end());

    for (auto [r, c] : path)
        cout << r << " " << c << "\n";

    return 0;
}
