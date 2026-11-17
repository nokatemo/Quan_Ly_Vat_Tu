#ifndef NHANVIEN_H
#define NHANVIEN_H
#pragma once
#include "struct.h"

// ==========================================================
// KHAI BAO CAC HAM XU LY NHAN VIEN (DUNG CODE CO BAN, DE HIEU)
// ==========================================================

// 1. Tim kiem nhi phan nhan vien theo Ma NV (tra ve vi tri trong mang, hoac -1 neu khong co)
int TimKiemNhanVien(const DanhSachNhanVien& ds, const string& maNV);

// 2. Doc danh sach nhan vien tu file NhanVien.txt vao mang
bool DocFileNhanVien(DanhSachNhanVien& ds, const string& tenFile = "NhanVien.txt");

// 3. Ghi danh sach nhan vien tu mang ra file NhanVien.txt
bool GhiFileNhanVien(const DanhSachNhanVien& ds, const string& tenFile = "NhanVien.txt");

// 4. Giao dien nhap nhan vien moi + hien bang danh sach theo MNV ngay ben duoi
bool ThemNhanVien(DanhSachNhanVien& ds, const string& tenFile = "NhanVien.txt");

// 5. In danh sach nhan vien sap xep theo Ten, Ho (dung Bubble Sort)
void InDanhSachNhanVien(const DanhSachNhanVien& ds);

#endif
