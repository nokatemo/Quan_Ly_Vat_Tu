
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cmath>
#include <cctype>
using namespace std;

// Xoa man hinh tren terminal ho tro ANSI
void xoaManHinh() {
    cout << "\033[2J\033[H" << flush;
}

// Kiem tra chuoi co rong hoac chi chua khoang trang
bool tenRong(const string& ten) {
    for (char c : ten) {
        if (!isspace(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

// Nhap so luong hoc sinh
int nhapSoLuong() {
    string dong;
    int N;

    while (true) {
        cout << "Nhap so luong hoc sinh (> 0): ";

        
        if (!getline(cin, dong)) {
            return 0;
        }

        stringstream ss(dong);
        string du;

        if ((ss >> N) && !(ss >> du) && N > 0) {
            return N;
        }

        cout << "N khong hop le! Hay nhap so nguyen duong.\n";
    }
}

// Nhap diem hop le tu 0 den 10
bool nhapDiem(double& diem) {
    string dong;

    while (true) {
        cout << "Nhap diem (0 - 10): ";

        if (!getline(cin, dong)) {
            return false;
        }

        stringstream ss(dong);
        string du;
        double giaTri;

        if ((ss >> giaTri) &&
            !(ss >> du) &&
            isfinite(giaTri) &&
            giaTri >= 0 &&
            giaTri <= 10) {

            diem = giaTri;
            return true;
        }

        cout << "Diem khong hop le! Nhap lai.\n";
    }
}

// 1. Ham nhap thong tin hoc sinh
bool nhapThongTin(string ten[], double diem[], int N) {
    for (int i = 0; i < N; i++) {
        xoaManHinh();

        cout << "=== HOC SINH " << i + 1
             << "/" << N << " ===\n";

        do {
            cout << "Nhap ten hoc sinh: ";

            if (!getline(cin, ten[i])) {
                return false;
            }

            if (tenRong(ten[i])) {
                cout << "Ten khong duoc de trong!\n";
            }

        } while (tenRong(ten[i]));

        if (!nhapDiem(diem[i])) {
            return false;
        }
    }

    return true;
}

// 2. Ham tinh diem trung binh
double tinhTrungBinh(const double diem[], int N) {
    double tong = 0;

    for (int i = 0; i < N; i++) {
        tong += diem[i];
    }

    return tong / N;
}

// 3. Ham tim vi tri diem cao nhat
int timMax(const double diem[], int N) {
    int vtmax = 0;

    for (int i = 1; i < N; i++) {
        if (diem[i] > diem[vtmax]) {
            vtmax = i;
        }
    }

    return vtmax;
}

int main() {
    int N = nhapSoLuong();

    if (N == 0) {
        cout << "\nDa dung nhap du lieu.\n";
        return 0;
    }

    string* ten = new string[N];
    double* diem = new double[N];

    if (!nhapThongTin(ten, diem, N)) {
        delete[] ten;
        delete[] diem;

        cout << "\nNhap du lieu bi gian doan.\n";
        return 0;
    }

    double tb = tinhTrungBinh(diem, N);
    int vtmax = timMax(diem, N);

    xoaManHinh();

    cout << "===== DANH SACH HOC SINH =====\n";

    for (int i = 0; i < N; i++) {
        cout << i + 1 << ". "
             << ten[i] << ": "
             << diem[i] << endl;
    }

    cout << "\nDiem trung binh cua lop: "
         << tb << endl;

    cout << "Hoc sinh co diem cao nhat: "
         << ten[vtmax] << endl;

    cout << "Diem cao nhat: "
         << diem[vtmax] << endl;

    delete[] ten;
    delete[] diem;

    return 0;
}
