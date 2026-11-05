#ifndef UI_H
#define UI_H

#include <iostream>
#include <windows.h>
#include <conio.h> 
#include <string>

#include "struct.h"
#include "NhanVien.h"
#include "HoaDon.h"

// Cac ham giao dien ho tro
void gotoxy(int x, int y);
void textcolor(int color);
void ShowConsoleCursor(bool showFlag);
void drawFrame();
void drawBox(int x, int y, int w, int h, int color);
void clearLine(int x, int y, int length);
void printStaticText();
void printMenuItems(int selectedIndex);

// Ham dieu khien menu chinh
void menuController(DanhSachNhanVien &dsNV, TreeVatTu &root);

#endif
