#ifndef NHANVIEN_H
#define NHANVIEN_H

#pragma once
#include "struct.h"
#include <string>

// =========================================================
// 1. CAC HAM TIM KIEM NHAN VIEN
// =========================================================

// Tim kiem nhi phan (Binary Search) theo MANV trong danh sach da sap xep
int TimkiemNhanVien(const DanhSachNhanVien& dsNV, const std::string& maNV);
int TimKiemNhanVien(const DanhSachNhanVien& dsNV, const std::string& maNV);

// =========================================================
// 2. CAC HAM THAO TAC FILE (DOC/GHI FILE NHANVIEN.TXT)
// =========================================================

// Lay duong dan tuyet doi den file NhanVien.txt trong cung thu muc file exe
std::string DuongDanFileNhanVien(const std::string& tenFile = "NhanVien.txt");

// Doc danh sach nhan vien tu file NhanVien.txt vao bo nho
bool DocFileNhanVien(DanhSachNhanVien& dsNV, const std::string& tenFile = "NhanVien.txt");

// Ghi danh sach nhan vien tu bo nho ra file NhanVien.txt (ghi qua file tam .tmp)
bool GhiFileNhanVien(const DanhSachNhanVien& dsNV, const std::string& tenFile = "NhanVien.txt");

// Ham ho tro luu file tuong thich voi giao dien cu
void LuuFileNhanVien(const DanhSachNhanVien& dsNV);

// =========================================================
// 3. CAC HAM CHUC NANG QUAN LY NHAN VIEN
// =========================================================

// Giao dien them moi / cap nhat nhan vien tu ban phim va ghi file
bool ThemNhanVien(DanhSachNhanVien& dsNV, const std::string& tenFile = "NhanVien.txt");

// In danh sach nhan vien phan trang (sap xep theo Ten, Ho)
void InDanhSachNhanVien(const DanhSachNhanVien& dsNV);

// Giai phong tat ca con tro nhan vien va dua so luong ve 0
void GiaiPhongDSNhanVien(DanhSachNhanVien& dsNV);

#endif
