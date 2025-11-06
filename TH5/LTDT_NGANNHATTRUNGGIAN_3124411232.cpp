#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <tuple>

using namespace std;

using Weight = long long;

const Weight INF = numeric_limits<Weight>::max();

struct DijkstraResult {
    Weight distance = INF;
    vector<int> path;
};

DijkstraResult dijkstra(int n, const vector<vector<pair<int, int>>>& adj, int start, int target) {
    vector<Weight> dist(n + 1, INF);
    vector<int> parent(n + 1, 0);

    dist[start] = 0;

    priority_queue<pair<Weight, int>, vector<pair<Weight, int>>, greater<pair<Weight, int>>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        Weight d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        if (u == target) {
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

    DijkstraResult result;
    if (dist[target] == INF) {
        return result;
    }

    result.distance = dist[target];

    int current = target;
    while (current != 0) {
        result.path.push_back(current);
        if (current == start) break;
        current = parent[current];
    }

    reverse(result.path.begin(), result.path.end());

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s, t, x;

    if (!(cin >> n >> m >> s >> t >> x)) return 0;

    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ v, w });
    }

    DijkstraResult result_sx = dijkstra(n, adj, s, x);
    DijkstraResult result_xt = dijkstra(n, adj, x, t);

    if (result_sx.distance == INF || result_xt.distance == INF) {
        cout << "0 " << -1 << endl;
    }
    else {
        Weight total_distance = result_sx.distance + result_xt.distance;

        vector<int> final_path = result_sx.path;
        for (size_t i = 1; i < result_xt.path.size(); ++i) {
            final_path.push_back(result_xt.path[i]);
        }

        cout << final_path.size() << " " << total_distance << endl;

        for (size_t i = 0; i < final_path.size(); ++i) {
            cout << final_path[i] << (i == final_path.size() - 1 ? "" : " ");
        }
        cout << endl;
    }

    return 0;
}