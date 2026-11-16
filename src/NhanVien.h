#ifndef NHANVIEN_H
#define NHANVIEN_H
#pragma once
#include "struct.h"

int TimKiemNhanVien(const DanhSachNhanVien& ds, const string& maNV);
// Ten file khong co thu muc se duoc tim trong thu muc chua chuong trinh.
string DuongDanFileNhanVien(const string& tenFile = "NhanVien.txt");
// Doc vao danh sach rong; file thieu duoc xem nhu danh sach rong.
bool DocFileNhanVien(DanhSachNhanVien& ds, const string& tenFile = "NhanVien.txt");
bool GhiFileNhanVien(const DanhSachNhanVien& ds, const string& tenFile = "NhanVien.txt");
// Nhap lien tiep den khi nhan Esc; true neu da them it nhat mot nhan vien.
bool ThemNhanVien(DanhSachNhanVien& ds, const string& tenFile = "NhanVien.txt");
void InDanhSachNhanVien(const DanhSachNhanVien& ds);
#endif
