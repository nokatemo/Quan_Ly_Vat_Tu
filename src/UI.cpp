#include "UI.h"
#include "NhanVien.h"
#include "ThongKe_DoanhThu.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include "struct.h"
using namespace std;

// ==========================================================
// PHAN 1: CAI DAT THONG SO MENU CHINH
// ==========================================================

int getDynamicOffsetX() {
    return OFFSET_X;
}

const int NUM_ITEMS = 10;
string menuItems[NUM_ITEMS] = {
    "1. Cap Nhat Vat Tu",
    "2. In Danh Sach Vat Tu Ton Kho",
    "3. Cap Nhat Nhan Vien",
    "4. In Danh Sach Nhan Vien",
    "5. Lap Hoa Don Nhap / Xuat",
    "6. In Chi Tiet 1 Hoa Don",
    "7. Thong Ke Hoa Don Theo Thoi Gian",
    "8. Top 10 Vat Tu Doanh Thu Cao Nhat",
    "9. Thong Ke Doanh Thu Theo Thang",
    "0. Thoat Chuong Trinh"
};

// ==========================================================
// PHAN 2: CAC HAM HO TRO GIAO DIEN (CON TRO, MAU SAC, VE KHUNG)
// ==========================================================

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = static_cast<SHORT>(x);
    coord.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textcolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void drawBox(int x, int y, int w, int h, int color, bool doubleLine) {
    if (w < 2 || h < 2) return;
    char tl = doubleLine ? char(201) : char(218);
    char tr = doubleLine ? char(187) : char(191);
    char bl = doubleLine ? char(200) : char(192);
    char br = doubleLine ? char(188) : char(217);
    char hz = doubleLine ? char(205) : char(196);
    char vt = doubleLine ? char(186) : char(179);

    textcolor(color);
    gotoxy(x, y);
    cout << tl << string(w - 2, hz) << tr;

    for (int i = 1; i < h - 1; ++i) {
        gotoxy(x, y + i);
        cout << vt;
        gotoxy(x + w - 1, y + i);
        cout << vt;
    }

    gotoxy(x, y + h - 1);
    cout << bl << string(w - 2, hz) << br;
    textcolor(15);
}

void veTieuDeChucNang(const string& tieuDe) {
    int offsetX = getDynamicOffsetX();
    int titleX = offsetX + (WIDTH - (int)tieuDe.length()) / 2;
    gotoxy(titleX, OFFSET_Y + 3);
    textcolor(14);
    cout << tieuDe;
    textcolor(15);
}

void veThanhHuongDan(int x, int y, const string& noiDung) {
    int offsetX = getDynamicOffsetX();
    gotoxy(offsetX + 2, y);
    textcolor(7);
    cout << string(WIDTH - 3, ' ');

    gotoxy(x, y);
    textcolor(10);
    cout << "[" << noiDung << "]";
    textcolor(15);
}

void hienThiONhap(int x, int y, const string& giaTri, int maxLen,
                  int viTriConTro, bool dangChon, int doRongXoa) {
    gotoxy(x, y);
    textcolor(7);
    cout << string(doRongXoa, ' ');

    string hienThi = giaTri.substr(0, maxLen);
    gotoxy(x, y);
    textcolor(dangChon ? 15 : 11);
    cout << "[" << left << setw(maxLen) << hienThi << "]";
    textcolor(15);
}

// ==========================================================
// PHAN 3: MAN HINH KHOI DONG PTIT (SPLASH SCREEN)
// ==========================================================

void showSplashScreen() {
    system("cls");
    ShowConsoleCursor(false);

    int offsetX = getDynamicOffsetX();
    drawBox(offsetX + 4, 3, 88, 24, 6, true);
    drawBox(offsetX + 6, 4, 84, 22, 3, false);

    const string blockP[6] = {
        string(6, char(219)) + " ",
        string(2, char(219)) + "   " + string(2, char(219)),
        string(6, char(219)) + " ",
        string(2, char(219)) + "     ",
        string(2, char(219)) + "     ",
        string(2, char(219)) + "     "
    };
    const string blockT[6] = {
        string(6, char(219)),
        "  " + string(2, char(219)) + "  ",
        "  " + string(2, char(219)) + "  ",
        "  " + string(2, char(219)) + "  ",
        "  " + string(2, char(219)) + "  ",
        "  " + string(2, char(219)) + "  "
    };
    const string blockI[6] = {
        string(6, char(219)),
        "  " + string(2, char(219)) + "  ",
        "  " + string(2, char(219)) + "  ",
        "  " + string(2, char(219)) + "  ",
        "  " + string(2, char(219)) + "  ",
        string(6, char(219))
    };

    int wordX = offsetX + 31;
    int wordY = 6;
    for (int r = 0; r < 6; ++r) {
        gotoxy(wordX, wordY + r);
        textcolor(12); cout << blockP[r] << "   " << blockT[r] << "   ";
        textcolor(14); cout << blockI[r] << "   " << blockT[r];
    }

    gotoxy(offsetX + 12, 14);
    textcolor(8);
    cout << string(72, char(196));

    gotoxy(offsetX + 17, 15);
    textcolor(14);
    cout << "HOC VIEN CONG NGHE BUU CHINH VIEN THONG - PHAN HIEU TP. HCM";

    gotoxy(offsetX + 25, 17);
    textcolor(11);
    cout << "HE THONG QUAN LY VAT TU & HOA DON NHAP XUAT";

    gotoxy(offsetX + 29, 18);
    textcolor(7);
    cout << "Mon hoc: Cau Truc Du Lieu & Giai Thuat";

    int barX = offsetX + 23;
    int barY = 21;
    int totalSteps = 42;

    for (int step = 0; step <= totalSteps; ++step) {
        int percent = (step * 100) / totalSteps;
        gotoxy(barX, barY);
        textcolor(3);  cout << "[";
        textcolor(10); cout << string(step, char(219));
        textcolor(8);  cout << string(totalSteps - step, char(176)) << "] ";
        textcolor(14); cout << setw(3) << percent << "%";

        gotoxy(offsetX + 31, barY + 1);
        textcolor(7);
        if (percent < 40)      cout << "Dang khoi tao cau truc du lieu...   ";
        else if (percent < 80) cout << "Dang nap du lieu tu file he thong... ";
        else                   cout << "Hoan tat! Dang mo giao dien chinh... ";

        if (_kbhit()) {
            _getch();
            break;
        }
        Sleep(35);
    }

    textcolor(15);
}

// ==========================================================
// PHAN 4: CAC HAM VE KHUNG CHINH VA MENU DASHBOARD
// ==========================================================

void drawFrame() {
    int offsetX = getDynamicOffsetX();
    textcolor(6);

    gotoxy(offsetX, OFFSET_Y);
    cout << char(201) << string(WIDTH - 1, char(205)) << char(187);

    gotoxy(offsetX, OFFSET_Y + 2);
    cout << char(204) << string(WIDTH - 1, char(205)) << char(185);

    gotoxy(offsetX, OFFSET_Y + 24);
    cout << char(204) << string(WIDTH - 1, char(205)) << char(185);

    gotoxy(offsetX, OFFSET_Y + 28);
    cout << char(200) << string(WIDTH - 1, char(205)) << char(188);

    for (int i = 1; i < HEIGHT; i++) {
        if (i == 2 || i == 24) continue;
        gotoxy(offsetX, OFFSET_Y + i);         cout << char(186);
        gotoxy(offsetX + WIDTH, OFFSET_Y + i); cout << char(186);
    }

    textcolor(15);
    gotoxy(0, 0);
}

void printStaticText() {
    int offsetX = getDynamicOffsetX();
    gotoxy(offsetX + 1, OFFSET_Y + 1);
    textcolor(7); cout << string(WIDTH - 1, ' ');

    string title = "HOC VIEN CONG NGHE BUU CHINH VIEN THONG - PHAN HIEU TP. HCM";
    int titleX = offsetX + (WIDTH - (int)title.length()) / 2;
    gotoxy(titleX, OFFSET_Y + 1);
    textcolor(14);
    cout << title;

    gotoxy(offsetX + 14, OFFSET_Y + 25);
    textcolor(11); cout << "Thanh vien 1: ";
    textcolor(15); cout << "Bui Vu Nguyen Khoa";
    textcolor(8);  cout << "  |  ";
    textcolor(14); cout << "N25DECE097";
    textcolor(8);  cout << "  |  ";
    textcolor(10); cout << "E25CQCE03-N";

    gotoxy(offsetX + 14, OFFSET_Y + 26);
    textcolor(11); cout << "Thanh vien 2: ";
    textcolor(15); cout << "Ngo Minh Tien     ";
    textcolor(8);  cout << "  |  ";
    textcolor(14); cout << "N25DECE121";
    textcolor(8);  cout << "  |  ";
    textcolor(10); cout << "E25CQCE03-N";

    gotoxy(offsetX + 14, OFFSET_Y + 27);
    textcolor(11); cout << "Thanh vien 3: ";
    textcolor(15); cout << "Tran Trung Nguyen ";
    textcolor(8);  cout << "  |  ";
    textcolor(14); cout << "N25DECE105";
    textcolor(8);  cout << "  |  ";
    textcolor(10); cout << "E25CQCE03-N";

    textcolor(15);
    gotoxy(0, 0);
}

void clearContentArea() {
    int offsetX = getDynamicOffsetX();
    textcolor(7);
    string blankRow(WIDTH - 1, ' ');

    for (int row = OFFSET_Y + 3; row <= OFFSET_Y + 23; ++row) {
        gotoxy(offsetX + 1, row);
        cout << blankRow;
    }

    textcolor(6);
    gotoxy(offsetX, OFFSET_Y + 24);
    cout << char(204) << string(WIDTH - 1, char(205)) << char(185);

    textcolor(15);
    gotoxy(offsetX + 1, OFFSET_Y + 3);
}

void veKhungPhuMenuChinh() {
    int offsetX = getDynamicOffsetX();
    drawBox(offsetX + 3, OFFSET_Y + 3, 56, 20, 3, false);
    gotoxy(offsetX + 6, OFFSET_Y + 3);
    textcolor(14); cout << " DANH MUC CHUC NANG ";

    drawBox(offsetX + 61, OFFSET_Y + 3, 32, 11, 3, false);
    gotoxy(offsetX + 64, OFFSET_Y + 3);
    textcolor(11); cout << " THONG TIN DE TAI ";

    gotoxy(offsetX + 63, OFFSET_Y + 5);
    textcolor(7);  cout << "Don vi:";
    gotoxy(offsetX + 63, OFFSET_Y + 6);
    textcolor(15); cout << "PTIT - Phan hieu TP. HCM";

    gotoxy(offsetX + 63, OFFSET_Y + 8);
    textcolor(7);  cout << "De tai:";
    gotoxy(offsetX + 63, OFFSET_Y + 9);
    textcolor(15); cout << "Quan Ly Vat Tu & Hoa Don";

    gotoxy(offsetX + 63, OFFSET_Y + 11);
    textcolor(7);  cout << "Cau truc du lieu:";
    gotoxy(offsetX + 63, OFFSET_Y + 12);
    textcolor(10); cout << "- Cay BST & Mang Con Tro";

    drawBox(offsetX + 61, OFFSET_Y + 15, 32, 8, 3, false);
    gotoxy(offsetX + 64, OFFSET_Y + 15);
    textcolor(14); cout << " PHIM DIEU KHIEN ";

    gotoxy(offsetX + 63, OFFSET_Y + 17);
    textcolor(11); cout << "UP / DOWN"; textcolor(7); cout << " : Chon chuc nang";
    gotoxy(offsetX + 63, OFFSET_Y + 18);
    textcolor(11); cout << "TAB      "; textcolor(7); cout << " : Chuyen nhanh";
    gotoxy(offsetX + 63, OFFSET_Y + 19);
    textcolor(11); cout << "ENTER    "; textcolor(7); cout << " : Mo chuc nang";
    gotoxy(offsetX + 63, OFFSET_Y + 20);
    textcolor(11); cout << "ESC      "; textcolor(7); cout << " : Quay lai / Thoat";
}

void printMenuItems(int selectedIndex) {
    int offsetX = getDynamicOffsetX();
    int startY = OFFSET_Y + 5;

    for (int i = 0; i < NUM_ITEMS; i++) {
        int rowY = startY + i;
        gotoxy(offsetX + 5, rowY);

        if (i == selectedIndex) {
            textcolor(31);
            cout << " > " << left << setw(49) << menuItems[i];
        } else {
            int tagColor = 11;
            if (i < 2)       tagColor = 11;
            else if (i < 4)  tagColor = 10;
            else if (i < 6)  tagColor = 14;
            else if (i < 9)  tagColor = 13;
            else             tagColor = 12;

            string prefix = menuItems[i].substr(0, 3);
            string label  = menuItems[i].substr(3);

            textcolor(15);
            cout << "   ";
            textcolor(tagColor);
            cout << prefix;
            textcolor(i == NUM_ITEMS - 1 ? 12 : 15);
            cout << left << setw(46) << label;
        }
    }

    textcolor(15);
    gotoxy(0, 0);
}

// ==========================================================
// PHAN 5: GIAO DIEN MODULE NHAN VIEN (CHUC NANG 3 & 4)
// Tat ca nam gon trong vung Y = 3 .. 23 (khong cham vach Y=24)
// ==========================================================

void VeKhungNhanVien(const string& tieuDe) {
    int offsetX = getDynamicOffsetX();
    int boxX = offsetX + 3;
    int boxW = 90;

    clearContentArea();
    ShowConsoleCursor(false);
    veTieuDeChucNang(tieuDe);

    // Hop nhap thong tin o nua tren (Y = 4 .. 11, cao 8 dong)
    drawBox(boxX, OFFSET_Y + 4, boxW, 9, 3, false); // chinh  8 -> 9
    gotoxy(boxX + 3, OFFSET_Y + 4);
    textcolor(10); cout << " THONG TIN NHAN VIEN ";

    veThanhHuongDan(offsetX + 7, OFFSET_Y + 23, "UP/DOWN/TAB: Chuyen o | ENTER/F2: Luu | PgUp/PgDn: Trang DS | ESC: Ve Menu");
}

void HienSoLuongNhanVien(int soLuong) {
    int offsetX = getDynamicOffsetX();
    int boxX = offsetX + 3;
    gotoxy(boxX + 60, OFFSET_Y + 4);
    textcolor(3);  cout << " Tong so: ";
    textcolor(14); cout << setw(3) << soLuong;
    textcolor(11); cout << " / 500 ";
    textcolor(15);
}

void HienFormNhanVien(const NhanVien& nv, int oDangChon, int viTri, const string& thongBao) {
    int offsetX = getDynamicOffsetX();
    int boxX = offsetX + 3;
    int x = boxX + 3;
    int inputX = x + 36; // chinh tu 34 - 36

    const string nhan[4] = {
        "1. Ma nhan vien (toi da 5 ky tu):",
        "2. Ho va ten dem:",
        "3. Ten:",
        "4. Phai (Nam / Nu):"
    };
    const string giaTri[4] = { nv.MANV, nv.ho, nv.ten, nv.phai };
    const int maxLens[4]   = { 5, 20, 10, 3 };

    for (int i = 0; i < 4; ++i) {
        int rowY = OFFSET_Y + 5 + i;
        gotoxy(x, rowY);
        textcolor(oDangChon == i ? 14 : 11);
        cout << (oDangChon == i ? "> " : "  ") << left << setw(34) << nhan[i];

        hienThiONhap(inputX, rowY, giaTri[i], 22, viTri, oDangChon == i, 26);
    }

    // Nut Luu o dong Y = 9	
    gotoxy(offsetX + 30, OFFSET_Y + 10);
    if (oDangChon == 4) {
        ShowConsoleCursor(false);
        textcolor(31);
        cout << " > [ LUU NHAN VIEN - ENTER / F2 ] < ";
    } else {
        textcolor(14);
        cout << "   [ LUU NHAN VIEN - ENTER / F2 ]   ";
    }

    // Dong hien thi thong bao loi o dong Y = 10 (ben trong hop nhap)
    gotoxy(x + 2, OFFSET_Y + 11);
    textcolor(12);
    cout << thongBao << string(max(0, 82 - (int)thongBao.length()), ' ');
    textcolor(15);

    if (oDangChon >= 0 && oDangChon <= 3) {
        int rowY = OFFSET_Y + 5 + oDangChon;
        int cur = max(0, min(viTri, (int)giaTri[oDangChon].length()));
        gotoxy(inputX + 1 + cur, rowY);
        ShowConsoleCursor(true);
    }
}

void HienThongBaoDayNhanVien() {
    int offsetX = getDynamicOffsetX();
    ShowConsoleCursor(false);
    gotoxy(offsetX + 6, OFFSET_Y + 11); // 10 -> 11;
    textcolor(12);
    cout << "(!) Danh sach da du 500 nhan vien! Nhan ESC hoac ENTER de quay ve menu.";
    textcolor(15);
}

// Bang danh sach nhan vien sap xep theo MNV nam ngay ben duoi Form nhap (Y = 12 .. 22)
void HienBangNhanVienTheoMaKhiNhap(const NhanVien* const ds[], int soLuong,
                                   int trang, int viTriVuaThem) {
    int offsetX = getDynamicOffsetX();
    int posX = offsetX + 3;
    int startY = OFFSET_Y + 13;

    int soTrang = (soLuong == 0) ? 1 : (soLuong + SO_NV_MOI_TRANG_NHAP - 1) / SO_NV_MOI_TRANG_NHAP;
    if (trang < 0) trang = 0;
    if (trang >= soTrang) trang = soTrang - 1;

    // Vien tren bang (tong rong = 90)
    textcolor(3);
    gotoxy(posX, startY);
    cout << char(218) << string(6, char(196))  << char(194)
         << string(12, char(196)) << char(194)
         << string(35, char(196)) << char(194)
         << string(21, char(196)) << char(194)
         << string(10, char(196)) << char(191);

    gotoxy(posX + 3, startY);
    textcolor(14); cout << " DANH SACH NHAN VIEN (THEO MNV) ";
    gotoxy(posX + 72, startY);
    textcolor(10); cout << " Trang " << (trang + 1) << "/" << soTrang << " ";

    // Header cot
    gotoxy(posX, startY + 1);
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left << setw(6)  << " STT";
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left << setw(12) << " MA NV";
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left << setw(35) << " HO VA TEN DEM";
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left << setw(21) << " TEN";
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left << setw(10) << " PHAI";
    textcolor(3);  cout << char(179);

    gotoxy(posX, startY + 2);
    textcolor(3);
    cout << char(195) << string(6, char(196))  << char(197)
         << string(12, char(196)) << char(197)
         << string(35, char(196)) << char(197)
         << string(21, char(196)) << char(197)
         << string(10, char(196)) << char(180);

    // In 4 dong nhan vien (tu Y = 15 den Y = 18)
    for (int i = 0; i < SO_NV_MOI_TRANG_NHAP; ++i) {
        int viTri = trang * SO_NV_MOI_TRANG_NHAP + i;
        int currentY = startY + 3 + i;
        gotoxy(posX, currentY);

        if (viTri < soLuong) {
            const NhanVien* nv = ds[viTri];
            int rowColor = (viTri == viTriVuaThem) ? 10 : 15;
            textcolor(3);        cout << char(179);
            textcolor(rowColor); cout << " " << left << setw(5)  << (viTri + 1);
            textcolor(3);        cout << char(179);
            textcolor(11);       cout << " " << left << setw(11) << nv->MANV;
            textcolor(3);        cout << char(179);
            textcolor(rowColor); cout << " " << left << setw(34) << nv->ho;
            textcolor(3);        cout << char(179);
            textcolor(rowColor); cout << " " << left << setw(20) << nv->ten;
            textcolor(3);        cout << char(179);
            textcolor(nv->phai == "Nam" ? 10 : 13);
            cout << " " << left << setw(9) << nv->phai;
            textcolor(3);        cout << char(179);
        } else {
            textcolor(3);
            cout << char(179) << string(6, ' ')  << char(179)
                 << string(12, ' ') << char(179)
                 << string(35, ' ') << char(179)
                 << string(21, ' ') << char(179)
                 << string(10, ' ') << char(179);
        }
    }

    // Vien day bang tai Y = 19
    gotoxy(posX, startY + 3 + SO_NV_MOI_TRANG_NHAP);
    textcolor(3);
    cout << char(192) << string(6, char(196))  << char(193)
         << string(12, char(196)) << char(193)
         << string(35, char(196)) << char(193)
         << string(21, char(196)) << char(193)
         << string(10, char(196)) << char(217);
    textcolor(15);
}

// Bang danh sach nhan vien day du (Chuc nang 4, nam gon trong Y = 3 .. 23)
void HienBangNhanVien(const NhanVien* const thutu[], int soLuong, int trang) {
    clearContentArea();
    ShowConsoleCursor(false);

    int offsetX = getDynamicOffsetX();
    int soTrang = (soLuong == 0) ? 1 : (soLuong + SO_NHAN_VIEN_MOI_TRANG - 1) / SO_NHAN_VIEN_MOI_TRANG;
    if (trang < 0) trang = 0;
    if (trang >= soTrang) trang = soTrang - 1;

    veTieuDeChucNang("4. DANH SACH NHAN VIEN - TRANG " + to_string(trang + 1) + "/" + to_string(soTrang));

    int posX = offsetX + 3;
    int startY = OFFSET_Y + 5;

    gotoxy(posX, startY - 1);
    textcolor(11); cout << "Sap xep: ";
    textcolor(7);  cout << "Ten tang dan (trung ten -> Ho tang dan)";

    gotoxy(posX + 68, startY - 1);
    textcolor(11); cout << "Tong: ";
    textcolor(10); cout << setw(3) << soLuong;
    textcolor(11); cout << " nhan vien";

    textcolor(3);
    gotoxy(posX, startY);
    cout << char(218) << string(6, char(196))  << char(194)
         << string(12, char(196)) << char(194)
         << string(35, char(196)) << char(194)
         << string(21, char(196)) << char(194)
         << string(10, char(196)) << char(191);

    gotoxy(posX, startY + 1);
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left << setw(6)  << " STT";
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left << setw(12) << " Ma NV";
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left << setw(35) << " Ho Va Ten Dem";
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left << setw(21) << " Ten";
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left << setw(10) << " Phai";
    textcolor(3);  cout << char(179);

    gotoxy(posX, startY + 2);
    textcolor(3);
    cout << char(195) << string(6, char(196))  << char(197)
         << string(12, char(196)) << char(197)
         << string(35, char(196)) << char(197)
         << string(21, char(196)) << char(197)
         << string(10, char(196)) << char(180);

    int startIdx = trang * SO_NHAN_VIEN_MOI_TRANG;
    int endIdx = min(soLuong, startIdx + SO_NHAN_VIEN_MOI_TRANG);
    int rowIdx = 0;

    for (int i = startIdx; i < endIdx; ++i) {
        int currentY = startY + 3 + rowIdx;
        const NhanVien* nv = thutu[i];

        gotoxy(posX, currentY);
        textcolor(3);  cout << char(179);
        textcolor(7);  cout << " " << left << setw(5)  << (i + 1);
        textcolor(3);  cout << char(179);
        textcolor(11); cout << " " << left << setw(11) << nv->MANV;
        textcolor(3);  cout << char(179);
        textcolor(15); cout << " " << left << setw(34) << nv->ho;
        textcolor(3);  cout << char(179);
        textcolor(14); cout << " " << left << setw(20) << nv->ten;
        textcolor(3);  cout << char(179);
        textcolor(nv->phai == "Nam" ? 10 : 13);
        cout << " " << left << setw(9) << nv->phai;
        textcolor(3);  cout << char(179);
        rowIdx++;
    }

    for (; rowIdx < SO_NHAN_VIEN_MOI_TRANG; ++rowIdx) {
        int currentY = startY + 3 + rowIdx;
        gotoxy(posX, currentY);
        textcolor(3);
        cout << char(179) << string(6, ' ')  << char(179)
             << string(12, ' ') << char(179)
             << string(35, ' ') << char(179)
             << string(21, ' ') << char(179)
             << string(10, ' ') << char(179);
    }

    // Vien day nam tai Y = 20 (an toan tuyet doi phia tren thanh huong dan Y = 23)
    gotoxy(posX, startY + 3 + SO_NHAN_VIEN_MOI_TRANG);
    textcolor(3);
    cout << char(192) << string(6, char(196))  << char(193)
         << string(12, char(196)) << char(193)
         << string(35, char(196)) << char(193)
         << string(21, char(196)) << char(193)
         << string(10, char(196)) << char(217);

    if (soLuong == 0) {
        gotoxy(posX + 26, startY + 8);
        textcolor(12);
        cout << "-> Danh sach nhan vien hien dang rong!";
    }

    veThanhHuongDan(posX + 10, OFFSET_Y + 23, "LEFT/RIGHT: Chuyen trang | HOME/END: Dau/Cuoi | ESC/ENTER: Ve Menu");
    textcolor(15);
}

// ==========================================================
// PHAN 6: BO NAO TRUNG TAM DIEU KHIEN MENU & SWITCH CASE
// ==========================================================

void menuController() {
    SetConsoleOutputCP(437);
    SetConsoleCP(437);

    //TreeVatTu root;
    //initTreeVatTu(root);
    //LoadTreeVatTuFromFile(root, "VatTu.txt");

    DanhSachNhanVien dsnv;
    dsnv.soLuong = 0;
    DocFileNhanVien(dsnv, "NhanVien.txt");
    //LoadHoaDonFromFile(dsnv, "HoaDon.txt");

    system("mode con cols=120 lines=32");
    ShowConsoleCursor(false);

    showSplashScreen();

    system("cls");
    drawFrame();
    printStaticText();
    veKhungPhuMenuChinh();

    int selectedIndex = 0;
    bool isRunning = true;

    while (isRunning) {
        printMenuItems(selectedIndex);

        int key = _getch();

        if (key == -32 || key == 224 || key == 0) {
            key = _getch();

            if (key == 72) {
                selectedIndex--;
                if (selectedIndex < 0) selectedIndex = NUM_ITEMS - 1;
            } else if (key == 80) {
                selectedIndex++;
                if (selectedIndex >= NUM_ITEMS) selectedIndex = 0;
            }
        }
        else if (key == 9) {
            selectedIndex = (selectedIndex + 1) % NUM_ITEMS;
        }
        else if (key == 13) {
            switch (selectedIndex) {
                case 0:
                    //quanLyVatTu(root, dsnv);
                    //SaveTreeVatTuToFile(root, "VatTu.txt");
                    break;

                case 1:
                    //inDSVatTuTheoTen(root);
                    break;

                case 2: // Chuc nang 3: Cap nhat nhan vien
                     ThemNhanVien(dsnv);
                    break;
                case 3: InDanhSachNhanVien(dsnv);
                    break;

                case 4:
                case 5:
                    break;

                case 6:
                   // if (dsnv.soLuong == 0) {
                     //   DocFileNhanVien(dsnv, "NhanVien.txt");
                     //   LoadHoaDonFromFile(dsnv, "HoaDon.txt");
                  //  }
                   // thongKeHoaDonTheoThoiGian(dsnv);
                    break;

                case 7:
                    break;

                case 8: // Chuc nang 9: Thong ke doanh thu theo thang
                    ThongKeDoanhThuTheoThang(dsnv);
                    break;

                case 9: {
                    int offsetX = getDynamicOffsetX();
                    int confirmX = offsetX + 6;
                    int confirmY = OFFSET_Y + 17;
                    int chonThoat = 1;
                    bool daXacNhan = false;

                    while (!daXacNhan) {
                        gotoxy(confirmX, confirmY);
                        textcolor(14);
                        cout << "Ban co chac chan muon thoat chuong trinh?";

                        gotoxy(confirmX + 6, confirmY + 2);
                        textcolor(chonThoat == 0 ? 31 : 10);
                        cout << (chonThoat == 0 ? " > [ CO ] < " : "   [ CO ]   ");

                        gotoxy(confirmX + 24, confirmY + 2);
                        textcolor(chonThoat == 1 ? 79 : 12);
                        cout << (chonThoat == 1 ? " > [ KHONG ] < " : "   [ KHONG ]   ");

                        int c = _getch();
                        if (c == -32 || c == 224 || c == 0) {
                            c = _getch();
                            if (c == 75 || c == 77) chonThoat = 1 - chonThoat;
                        } else if (c == 9) {
                            chonThoat = 1 - chonThoat;
                        } else if (c == 27) {
                            chonThoat = 1;
                            daXacNhan = true;
                        } else if (c == 13) {
                            daXacNhan = true;
                        }
                    }

                    if (chonThoat == 0) {
                       // freeTreeVatTu(root);
                       // giaiPhongDanhSachNhanVien(dsnv);
                        system("cls");
                        drawBox(offsetX + 18, 10, 62, 7, 10, true);
                        gotoxy(offsetX + 24, 13);
                        textcolor(14);
                        cout << "Cam on ban da su dung chuong trinh! Hen gap lai.";
                        textcolor(15);
                        Sleep(2000);
                        isRunning = false;
                    } else {
                        textcolor(7);
                        gotoxy(confirmX, confirmY);     cout << string(50, ' ');
                        gotoxy(confirmX, confirmY + 2); cout << string(50, ' ');
                        textcolor(15);
                    }
                    break;
                }
            }

            if (isRunning) {
                ShowConsoleCursor(false);
                clearContentArea();
                veKhungPhuMenuChinh();
            }
        }
    }
}
