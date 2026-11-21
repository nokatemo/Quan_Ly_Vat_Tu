#ifndef UI_H
#define UI_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

// ==========================================================
// THONG SO TOA DO VA KICH THUOC CHUAN CUA KHUNG CHINH
// ==========================================================
const int OFFSET_X = 12;
const int OFFSET_Y = 0;
const int WIDTH    = 96;
const int HEIGHT   = 28;

const int SO_NHAN_VIEN_MOI_TRANG = 12; // So dong moi trang o Menu 4 (vua khit Y = 3..23)
const int SO_NV_MOI_TRANG_NHAP   = 4;  // So dong moi trang o bang duoi Form nhap (Menu 3)

struct NhanVien;

// ==========================================================
// CAC HAM HO TRO GIAO DIEN DUNG CHUNG
// ==========================================================
int getDynamicOffsetX();
void gotoxy(int x, int y);
void textcolor(int color);
void ShowConsoleCursor(bool showFlag);

void drawBox(int x, int y, int w, int h, int color = 3, bool doubleLine = false);
void clearContentArea();
void veTieuDeChucNang(const std::string& tieuDe);
void veThanhHuongDan(int x, int y, const std::string& noiDung);
void hienThiONhap(int x, int y, const std::string& giaTri, int maxLen,
                  int viTriConTro, bool dangChon, int doRongXoa);

// ==========================================================
// CAC HAM GIAO DIEN MODULE NHAN VIEN (CHUC NANG 3 & 4)
// ==========================================================
void VeKhungNhanVien(const std::string& tieuDe);
void HienSoLuongNhanVien(int soLuong);
void HienThongBaoDayNhanVien();
void HienFormNhanVien(const NhanVien& nv, int oDangChon, int viTriConTro,
                      const std::string& thongBao = "");
void HienBangNhanVienTheoMaKhiNhap(const NhanVien* const ds[], int soLuong,
                                   int trang = 0, int viTriVuaThem = -1);
void HienBangNhanVien(const NhanVien* const ds[], int soLuong, int trang);

// ==========================================================
// CAC HAM DIEU KHIEN MENU CHINH
// ==========================================================
void showSplashScreen();
void drawFrame();
void printStaticText();
void veKhungPhuMenuChinh();
void printMenuItems(int selectedIndex);
void menuController();

#endif
