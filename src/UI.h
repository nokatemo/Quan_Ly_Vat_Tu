#ifndef UI_H
#define UI_H

#include <iostream>
#include <windows.h>
#include <conio.h> 
#include <string>

#include "struct.h"
#include "NhanVien.h"
#include "HoaDon.h"

// =========================================================
// 1. CAC HAM HO TRO XU LY CONSOLE VA DO HOA CONSOLE (WIN32 API)
// =========================================================

// Di chuyen con tro console den toa do (x, y)
void gotoxy(int x, int y);

// Thay doi mau chu (text color) va mau nen (background color) trong console
void textcolor(int color);

// An hoac hien con tro nhap nhay tren man hinh console
void ShowConsoleCursor(bool showFlag);

// Ve khung vien bang ky tu dac biet theo vi tri, kich thuoc va mau sac
void drawBox(int x, int y, int w, int h, int color);

// Xoa mot dong tai toa do (x, y) voi chieu dai xoa xac dinh
void clearLine(int x, int y, int length);

// Ve khung vien bao ngoai toan man hinh ung dung
void drawFrame();

// In thong tin tinh: Tieu de truong hoc va thong tin cac thanh vien thuc hien
void printStaticText();

// In danh sach cac muc trong Menu chinh voi highlight phan tu dang chon
void printMenuItems(int selectedIndex);

// =========================================================
// 2. CAC HAM GIAO DIEN FORM VA BANG HIEN THI NHAN VIEN
// =========================================================

// Hang so quy dinh so luong nhan vien hien thi tren 1 trang bang
const int SO_NHAN_VIEN_MOI_TRANG = 12;

// Ve khung va tieu de chuan cho cac giao dien quan ly Nhan Vien
void VeKhungNhanVien(const std::string& tieuDe);

// Hien thi so luong nhan vien hien co trong he thong tren header
void HienSoLuongNhanVien(int soLuong);

// Hien thi thong bao khi danh sach nhan vien da dat toi da (500 nhan vien)
void HienThongBaoDayNhanVien();

// Hien thi Form nhap/sua thong tin nhan vien voi thuat toan can giua chuoi va con tro nhap nhay
void HienFormNhanVien(const NhanVien& nv, int oDangChon, int viTriConTro, const std::string& thongBao = "");

// Hien thi bang danh sach nhan vien phan trang va sap xep theo Ten, Ho
void HienBangNhanVien(const NhanVien* const ds[], int soLuong, int trang);

// =========================================================
// 3. GIAO DIEN THOAT VA HAM DIEU KHIEN MENU CHINH
// =========================================================

// Hien thi giao dien va hieu ung thoat chuong trinh
void GiaoDienThoatChuongTrinh();

// Ham dieu khien chinh (Controller) luong hoat dong va chuyen trang thai Menu
void menuController(DanhSachNhanVien &dsNV, TreeVatTu &root);

#endif
