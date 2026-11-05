#include "NhanVien.h"
#include <iostream>
#include <fstream>

using namespace std;

// Tim kiem nhan vien theo thuat toan Tim Kiem Nhi Phan (Binary Search)
// Yeu cau: Mang dsNV.ds phai duoc sap xep tang dan theo MANV
int TimkiemNhanVien(DanhSachNhanVien dsNV, string maNV) {
    int left = 0;
    int right = dsNV.soLuong - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (dsNV.ds[mid]->MANV == maNV) {
            return mid; // Tim thay -> Tra ve vi tri index trong mang
        }
        if (maNV < dsNV.ds[mid]->MANV) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return -1; // Khong tim thay
}

// Doc danh sach nhan vien tu file NhanVien.txt
void DocFileNhanVien(DanhSachNhanVien &dsNV) {
    ifstream f("NhanVien.txt", ios::in);
    if (!f.is_open()) {
        cout << "Thong bao: Khong tim thay file NhanVien.txt!\n";
        return;
    }

    f >> dsNV.soLuong;
    for (int i = 0; i < dsNV.soLuong; i++) {
        dsNV.ds[i] = new NhanVien();
        f >> dsNV.ds[i]->MANV;
        f.ignore();
        getline(f, dsNV.ds[i]->HO, '|');
        getline(f, dsNV.ds[i]->TEN, '|');
        f >> dsNV.ds[i]->PHAI;
        dsNV.ds[i]->dshd = NULL; // Khoi tao dshd ban dau rong
    }

    f.close();
    cout << "Doc file NhanVien.txt thanh cong!\n";
}

// Ghi danh sach nhan vien ra file NhanVien.txt
void LuuFileNhanVien(DanhSachNhanVien dsNV) {
    ofstream f("NhanVien.txt", ios::out);
    if (!f.is_open()) {
        cout << "Loi: Khong the mo file NhanVien.txt de ghi!\n";
        return;
    }

    f << dsNV.soLuong << endl;
    for (int i = 0; i < dsNV.soLuong; i++) {
        f << dsNV.ds[i]->MANV << " "
          << dsNV.ds[i]->HO << "|"
          << dsNV.ds[i]->TEN << "|"
          << dsNV.ds[i]->PHAI << endl;
    }

    f.close();
    cout << "Ghi file NhanVien.txt thanh cong!\n";
}

// Giai phong bo nho m?ng con tro nhan vien
void GiaiPhongDSNhanVien(DanhSachNhanVien &dsNV) {
    for (int i = 0; i < dsNV.soLuong; i++) {
        delete dsNV.ds[i];
    }
    dsNV.soLuong = 0;
}
