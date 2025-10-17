#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

struct Circle {
    double x, y, r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, S, T;
    if (!(cin >> N >> S >> T)) return 0;
    vector<Circle> a(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> a[i].x >> a[i].y >> a[i].r;
    }

    auto gap = [&](int i, int j) -> double {
        double dx = a[i].x - a[j].x;
        double dy = a[i].y - a[j].y;
        double centerDist = sqrt(dx * dx + dy * dy);
        double g = centerDist - (a[i].r + a[j].r);
        if (g < 0) g = 0;
        return g;
        };

    const int INF = 1000000000;
    vector<int> bestJ(N + 1, INF);
    vector<int> bestSteps(N + 1, INF);
    vector<int> parent(N + 1, -1);
    vector<int> moveIsJump(N + 1, 0);

    using TUP = tuple<int, int, int>;
    priority_queue<TUP, vector<TUP>, greater<TUP>> pq;

    bestJ[S] = 0;
    bestSteps[S] = 1;
    pq.emplace(0, 1, S);

    while (!pq.empty()) {
        auto [cj, cs, u] = pq.top();
        pq.pop();
        if (cj != bestJ[u] || cs != bestSteps[u]) continue;
        if (u == T) break;

        for (int v = 1; v <= N; ++v) {
            if (v == u) continue;
            double g = gap(u, v);
            if (g <= 50.0 + 1e-9) {
                int nj = cj;
                int ns = cs + 1;
                if (make_pair(nj, ns) < make_pair(bestJ[v], bestSteps[v])) {
                    bestJ[v] = nj;
                    bestSteps[v] = ns;
                    parent[v] = u;
                    moveIsJump[v] = 0;
                    pq.emplace(nj, ns, v);
                }
            }
            else if (g <= 60.0 + 1e-9) {
                int nj = cj + 1;
                int ns = cs + 1;
                if (make_pair(nj, ns) < make_pair(bestJ[v], bestSteps[v])) {
                    bestJ[v] = nj;
                    bestSteps[v] = ns;
                    parent[v] = u;
                    moveIsJump[v] = 1;
                    pq.emplace(nj, ns, v);
                }
            }
        }
    }

    if (bestJ[T] == INF) {
        cout << 0 << "\n";
        return 0;
    }

    vector<int> path;
    int cur = T;
    while (cur != -1) {
        path.push_back(cur);
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());

    cout << 1 << "\n";
    cout << bestJ[T] << " " << (int)path.size() << "\n";
    for (size_t i = 1; i < path.size(); ++i) {
        int node = path[i];
        cout << node << " " << moveIsJump[node] << "\n";
    }

    return 0;
}
