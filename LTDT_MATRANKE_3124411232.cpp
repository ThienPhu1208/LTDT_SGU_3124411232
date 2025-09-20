#include <iostream>
#include <fstream>

using namespace std;

// Đọc ma trận kề từ file và trả về n; đồng thời khởi tạo ma trận động a
int docMaTranKe(const char* tenFile, int*** a) {
    ifstream fin(tenFile);
    if (!fin) {
        cerr << "Không thể mở file " << tenFile << " để đọc.\n";
        exit(1);
    }

    int n;
    fin >> n;
    // cấp phát mảng 2 chiều động size n x n
    int** mat = new int* [n];
    for (int i = 0; i < n; ++i) {
        mat[i] = new int[n];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> mat[i][j];
        }
    }

    fin.close();
    *a = mat;
    return n;
}

// Tính bậc các đỉnh, lưu vào mảng bac (đã cấp phát size n)
void tinhBac(int** a, int n, int* bac) {
    for (int i = 0; i < n; ++i) {
        int s = 0;
        for (int j = 0; j < n; ++j) s += a[i][j];
        bac[i] = s;
    }
}

// Giải phóng ma trận động
void giaiPhong(int** a, int n) {
    for (int i = 0; i < n; ++i) delete[] a[i];
    delete[] a;
}

int main() {
    const char* finName = "MaTranKe.inp";
    const char* foutName = "MaTranKe.out";

    int** mat = nullptr;
    int n = docMaTranKe(finName, &mat);

    int* bac = new int[n];
    tinhBac(mat, n, bac);

    ofstream fout(foutName);
    if (!fout) {
        cerr << "Không thể mở file " << foutName << " để ghi.\n";
        return 1;
    }

    fout << n << '\n';
    for (int i = 0; i < n; ++i) {
        fout << bac[i] << '\n';
    }
    fout.close();

    // In ra màn hình ví dụ kết quả (để kiểm tra nhanh)
    cout << "Da ghi ket qua ra file: " << foutName << "\n";
    cout << "N = " << n << "\n";
    for (int i = 0; i < n; ++i) cout << bac[i] << '\n';

    // Giải phóng bộ nhớ
    delete[] bac;
    giaiPhong(mat, n);

    return 0;
}
