#ifndef UI_H
#define UI_H

#include <iostream>
#include <windows.h>
#include <conio.h> 
#include <string>

// ==========================================================
// KHAI BAO CAC HAM CHUC NANG GIAO DIEN (UI)
// ==========================================================

// Ham di chuyen con tro chuot tren man hinh console den toa do (x, y)
void gotoxy(int x, int y);

// Ham thay doi mau sac cho van ban (to mau chu va mau nen)
void textcolor(int color);

// Ham an hoac hien con tro chuot (cuc nhap nhay tren man hinh)
void ShowConsoleCursor(bool showFlag);

// Ham ve khung vien hinh chu nhat bao quanh menu
void drawFrame();

// Ham in cac thong tin co dinh (Ten truong, ten Nguyen Khoa, ma sinh vien...)
void printStaticText();

// Ham in danh sach 10 chuc nang va to mau muc dang duoc chon
void printMenuItems(int selectedIndex);

// Ham xu ly vong lap chinh, nhan phim mui ten va dieu huong switch-case
void menuController();

#endif
