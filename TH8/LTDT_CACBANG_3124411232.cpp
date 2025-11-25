#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

int main() {
    map<string, vector<string>> adj;

    // ======== Khai báo đồ thị theo hình bản đồ ========
    adj["CALIFORNIA"] = { "NEVADA", "ARIZONA" };
    adj["NEVADA"] = { "CALIFORNIA", "UTAH", "ARIZONA" };
    adj["UTAH"] = { "NEVADA", "COLORADO", "ARIZONA" };
    adj["COLORADO"] = { "UTAH", "NEBRASKA", "KANSAS", "OKLAHOMA", "ARIZONA" };
    adj["NEBRASKA"] = { "COLORADO", "KANSAS" };
    adj["KANSAS"] = { "NEBRASKA", "COLORADO", "OKLAHOMA" };
    adj["OKLAHOMA"] = { "COLORADO", "KANSAS", "ARKANSAS", "TEXAS" };
    adj["TEXAS"] = { "OKLAHOMA", "ARKANSAS", "LOUISIANA" };
    adj["ARKANSAS"] = { "OKLAHOMA", "TEXAS", "MISSISIPI", "LOUISIANA" };
    adj["LOUISIANA"] = { "TEXAS", "ARKANSAS", "MISSISIPI" };
    adj["MISSISIPI"] = { "ARKANSAS", "LOUISIANA", "GEORGIA", "FLORIDA" };
    adj["GEORGIA"] = { "MISSISIPI", "FLORIDA" };
    adj["FLORIDA"] = { "GEORGIA", "MISSISIPI" };
    adj["ARIZONA"] = { "CALIFORNIA", "NEVADA", "UTAH", "COLORADO" };

    // ======== Danh sách đỉnh ========
    vector<string> nodes;
    for (auto& p : adj) nodes.push_back(p.first);

    // ======== Sắp xếp theo bậc giảm dần ========
    sort(nodes.begin(), nodes.end(), [&](const string& a, const string& b) {
        return adj[a].size() > adj[b].size();
        });

    map<string, int> color;
    int maxColor = 0;

    // ======== Tô màu theo thứ tự Welsh–Powell ========
    for (auto& u : nodes) {
        vector<bool> used(100, false);
        for (auto& v : adj[u])
            if (color[v] != 0)
                used[color[v]] = true;

        int c;
        for (c = 1; c <= 100; c++)
            if (!used[c]) break;

        color[u] = c;
        maxColor = max(maxColor, c);
    }

    // ======== Xuất kết quả ========
    cout << "So mau su dung: " << maxColor << "\n";
    for (int c = 1; c <= maxColor; c++) {
        cout << "Mau " << c << ": ";
        for (auto& u : nodes)
            if (color[u] == c)
                cout << u << " ";
        cout << "\n";
    }

    return 0;
}
