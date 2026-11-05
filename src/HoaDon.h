#ifndef HOADON_H
#define HOADON_H

#include "struct.h"
#include "Validate.h"
#include "VatTu.h"
#include "NhanVien.h"

// 1. CAC HAM BO TRO DANH SACH LIEN KET CHI TIET HOA DON
NodeCTHD* TaoNodeCTHD(ChiTietHoaDon ct);
void ThemCTHD(ListCTHD &dscthd, ChiTietHoaDon ct);
void XoaCTHDTrongDSTam(ListCTHD &dscthd, string maVT);
void GiaiPhongDSCTHD(ListCTHD &dscthd);
bool KiemTraTrungVatTuTrongGio(ListCTHD head, const string& maVT);

// 2. CAC HAM XU LY FILE (HOADON.TXT)
void LuuFileHoaDon(DanhSachNhanVien dsNV);
void DocFileHoaDon(DanhSachNhanVien &dsNV);

// 3. CAC HAM CHUC NANG CHINH VADI GIAO DIEN CONSOLE (CAU E VA F)
void giaodienLapHoaDon(DanhSachNhanVien &dsNV, TreeVatTu &root);
void giaodienInHoaDon(DanhSachNhanVien dsNV, TreeVatTu root);

#endif
