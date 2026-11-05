#ifndef NHANVIEN_H
#define NHANVIEN_H

#include "struct.h"

// Tim kiem nhan vien trong mang con tro bang Tim Kiem Nhi Phan (Binary Search)
int TimkiemNhanVien(DanhSachNhanVien dsNV, string maNV);

// Doc file danh sach nhan vien tu NhanVien.txt
void DocFileNhanVien(DanhSachNhanVien &dsNV);

// Ghi file danh sach nhan vien ra NhanVien.txt
void LuuFileNhanVien(DanhSachNhanVien dsNV);

// Giai phong bo nho mang con tro nhan vien
void GiaiPhongDSNhanVien(DanhSachNhanVien &dsNV);

#endif
