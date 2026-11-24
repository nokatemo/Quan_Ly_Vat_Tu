#ifndef UI_H
#define UI_H

#include <iostream>
#include <windows.h>
#include <conio.h> 
#include <string>

#include "struct.h"
#include "NhanVien.h"
#include "HoaDon.h"
#include "ThongKe_Top10.h"

using namespace std;

// ==========================================================
// THONG SO TOA DO VA KICH THUOC KHUNG CHINH DUNG CHUNG
// ==========================================================
const int WIDTH = 98;
const int HEIGHT = 28;
const int OFFSET_X = 11;
const int OFFSET_Y = 1;
const int SO_NHAN_VIEN_MOI_TRANG = 12;

int getDynamicOffsetX();

// ==========================================================
// CAC HAM HO TRO DO HOA CONSOLE & KHUNG CHINH
// ==========================================================
void gotoxy(int x, int y);
void textcolor(int color);
void ShowConsoleCursor(bool showFlag);
void drawBox(int x, int y, int w, int h, int color = 8, bool doubleLine = false);
void clearLine(int x, int y, int length);
void showSplashScreen();
void drawFrame();
void printStaticText();
void clearContentArea();
void veKhungPhuMenuChinh();
void printMenuItems(int selectedIndex);

// ==========================================================
// CAC HAM GIAO DIEN NHAN VIEN (TUONG THICH CODE CU)
// ==========================================================
void VeKhungNhanVien(const string& tieuDe);
void HienSoLuongNhanVien(int soLuong);
void HienThongBaoDayNhanVien();
void HienFormNhanVien(const NhanVien& nv, int oDangChon, int viTriConTro, const string& thongBao = "");
void HienBangNhanVien(const NhanVien* const ds[], int soLuong, int trang);

// ==========================================================
// DIEU KHIEN MENU CHINH
// ==========================================================
void menuController(DanhSachNhanVien &dsNV, TreeVatTu &root);

#endif
