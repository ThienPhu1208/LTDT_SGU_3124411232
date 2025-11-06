#include <vector>
using namespace std;

// 🔹 Chuyển từ ma trận kề sang danh sách kề
void MaTranSangDanhSach(int soDinh, int MT[100][100], vector<int> DS[]) {
    for (int i = 1; i <= soDinh; i++)
        for (int j = 1; j <= soDinh; j++)
            if (MT[i][j] == 1)          // nếu có cạnh giữa i và j
                DS[i].push_back(j);     // thêm j vào danh sách của i
}

// 🔹 Chuyển từ ma trận kề sang danh sách cạnh
void MaTranSangCanh(int soDinh, int MT[100][100], vector<pair<int, int>>& DSCanh) {
    for (int i = 1; i <= soDinh; i++)
        for (int j = i + 1; j <= soDinh; j++) // chỉ duyệt nửa trên (đồ thị vô hướng)
            if (MT[i][j] == 1)
                DSCanh.push_back({ i, j });
}

// 🔹 Chuyển từ danh sách kề sang ma trận kề
void DanhSachSangMaTran(int soDinh, vector<int> DS[], int MT[100][100]) {
    for (int i = 1; i <= soDinh; i++)
        for (int j : DS[i])                  // duyệt từng đỉnh kề của i
            MT[i][j] = MT[j][i] = 1;         // vô hướng nên gán cả 2 chiều
}

// 🔹 Chuyển từ danh sách kề sang danh sách cạnh
void DanhSachSangCanh(int soDinh, vector<int> DS[], vector<pair<int, int>>& DSCanh) {
    for (int i = 1; i <= soDinh; i++)
        for (int j : DS[i])
            if (i < j) DSCanh.push_back({ i, j }); // tránh trùng cạnh
}

// 🔹 Chuyển từ danh sách cạnh sang ma trận kề
void CanhSangMaTran(int soDinh, vector<pair<int, int>> DSCanh, int MT[100][100]) {
    for (auto canh : DSCanh)
        MT[canh.first][canh.second] = MT[canh.second][canh.first] = 1;
}

// 🔹 Chuyển từ danh sách cạnh sang danh sách kề
void CanhSangDanhSach(int soDinh, vector<pair<int, int>> DSCanh, vector<int> DS[]) {
    for (auto canh : DSCanh) {
        DS[canh.first].push_back(canh.second);
        DS[canh.second].push_back(canh.first);
    }
}
