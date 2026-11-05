#ifndef UI_H
#define UI_H

#include <iostream>
#include <windows.h>
#include <conio.h> 
#include <string>

#include "struct.h"
#include "NhanVien.h"
#include "HoaDon.h"

// Di chuyen con tro console den toa do (x, y)
void gotoxy(int x, int y);

// Thay doi mau chu va mau nen hien thi
void textcolor(int color);

// An hoac hien con tro chuot nhap nhay
void ShowConsoleCursor(bool showFlag);

// Ve khung vien bao quanh menu
void drawFrame();

// In thong tin co dinh (tieu de truong, thong tin sinh vien)
void printStaticText();

// In danh sach 10 muc menu va highlight muc dang chon
void printMenuItems(int selectedIndex);

// Quan ly vong lap menu chinh va dieu huong chuc nang
void menuController(DanhSachNhanVien &dsNV, TreeVatTu &root);

#endif
