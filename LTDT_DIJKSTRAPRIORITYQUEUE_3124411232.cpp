#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <tuple>

using namespace std;

using Weight = long long;

const Weight INF = numeric_limits<Weight>::max();

pair<Weight, vector<int>> dijkstra(int n, const vector<vector<pair<int, int>>>& adj, int s, int t) {
    vector<Weight> dist(n + 1, INF);
    vector<int> parent(n + 1, 0);

    dist[s] = 0;

    priority_queue<pair<Weight, int>, vector<pair<Weight, int>>, greater<pair<Weight, int>>> pq;
    pq.push({ 0, s });

    while (!pq.empty()) {
        Weight d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        if (u == t) {
            break;
        }

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }

    vector<int> path;
    if (dist[t] == INF) {
        return { INF, path };
    }

    int current = t;
    while (current != 0) {
        path.push_back(current);
        if (current == s) break;
        current = parent[current];
    }

    reverse(path.begin(), path.end());

    return { dist[t], path };
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s, t;

    if (!(cin >> n >> m >> s >> t)) return 0;

    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ v, w });
    }

    auto result = dijkstra(n, adj, s, t);
    Weight shortest_distance = result.first;
    vector<int> path = result.second;

    if (shortest_distance == INF) {
        cout << "0 " << -1 << "\n";
    }
    else {
        cout << path.size() << " " << shortest_distance << "\n";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}