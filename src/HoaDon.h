#ifndef HOADON_H
#define HOADON_H

#include "struct.h"
#include "Validate.h"

// =========================================================
// 1. CAC HAM BO TRO XU LY DANH SACH LIEN KET CHI TIET HOA DON
// =========================================================

// Tao mot NodeCTHD moi de chua du lieu 1 dong chi tiet vat tu
NodeCTHD* TaoNodeCTHD(ChiTietHoaDon ct);

// Them mot chi tiet vat tu vao DAU danh sach lien ket (ap dung cho dscthd tam)
void ThemCTHD(ListCTHD &dscthd, ChiTietHoaDon ct);

// Xoa 1 vat tu khoi danh sach chi tiet tam thoi theo Ma VT (dung khi dang lap hoa don)
void XoaCTHDTrongDSTam(ListCTHD &dscthd, string maVT);

// Giai phong toan bo bo nho cua chuoi Danh sach lien ket Chi tiet hoa don
void GiaiPhongDSCTHD(ListCTHD &dscthd);


// =========================================================
// 2. CAC HAM XU LY FILE (HOADON.TXT)
// =========================================================

// Ghi toan bo danh sach hoa don cua tat ca nhan vien ra file HoaDon.txt
void LuuFileHoaDon(DanhSachNhanVien dsNV);

// Doc du lieu tu file HoaDon.txt va doc vao danh sach nhan vien khi khoi chay
void DocFileHoaDon(DanhSachNhanVien &dsNV);


// =========================================================
// 3. CAC HAM CHUC NANG CHINH (CAU E VA CAU F)
// =========================================================

// Cau e: Lap hoa don Nhap hoac Xuat
// Truyens &dsNV de moc hoa don moi vao nhan vien, &root de cap nhat ton kho
void LapHoaDon(DanhSachNhanVien &dsNV, TreeVatTu &root);

// Cau f: In chi tiet 1 hoa don dua vao So HD do nguoi dung nhap vao
void InHoaDon(DanhSachNhanVien dsNV, TreeVatTu root);

#endif
