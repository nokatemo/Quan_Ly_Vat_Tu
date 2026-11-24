#include "UI.h"
#include <iostream>
#include <iomanip>
#include <conio.h> 
#include <windows.h>

using namespace std;

// ==========================================================
// PHAN 1: CAI DAT THONG SO TOA DO VA DANH SACH MENU
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
// PHAN 2: CAC HAM HO TRO GIAO DIEN (CON TRO & MAU SAC)
// ==========================================================

// Di chuyen con tro console den toa do (x, y)
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = static_cast<SHORT>(x);
    coord.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Doi mau chu va mau nen console
void textcolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// An hoac hien con tro nhap nhay tren man hinh
void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; 
    SetConsoleCursorInfo(out, &cursorInfo);
}

// Ve khung hinh chu nhat net don hoac net doi
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

// Xoa mot doan van ban tren cung mot dong
void clearLine(int x, int y, int length) {
    gotoxy(x, y);
    for (int i = 0; i < length; i++) cout << " ";
    gotoxy(x, y);
}

// ==========================================================
// PHAN 3: MAN HINH KHOI DONG PTIT (SPLASH SCREEN)
// ==========================================================

void showSplashScreen() {
    system("cls");
    ShowConsoleCursor(false);

    int offsetX = getDynamicOffsetX();
    drawBox(offsetX + 5, 3, 88, 24, 6, true);
    drawBox(offsetX + 7, 4, 84, 22, 3, false);

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

    int wordX = offsetX + 32;
    int wordY = 6;
    for (int r = 0; r < 6; ++r) {
        gotoxy(wordX, wordY + r);
        textcolor(12); cout << blockP[r] << "   " << blockT[r] << "   ";
        textcolor(14); cout << blockI[r] << "   " << blockT[r];
    }

    gotoxy(offsetX + 13, 14);
    textcolor(8);
    cout << string(72, char(196));

    gotoxy(offsetX + 18, 15);
    textcolor(14);
    cout << "HOC VIEN CONG NGHE BUU CHINH VIEN THONG - PHAN HIEU TP. HCM";

    gotoxy(offsetX + 32, 17);
    textcolor(11);
    cout << "HE THONG QUAN LY VAT TU";

    gotoxy(offsetX + 30, 18);
    textcolor(7);
    cout << "Mon hoc: Cau Truc Du Lieu & Giai Thuat";

    int barX = offsetX + 24;
    int barY = 21;
    int totalSteps = 42;

    for (int step = 0; step <= totalSteps; ++step) {
        int percent = (step * 100) / totalSteps;
        gotoxy(barX, barY);
        textcolor(3);  cout << "[";
        textcolor(10); cout << string(step, char(219));
        textcolor(8);  cout << string(totalSteps - step, char(176)) << "] ";
        textcolor(14); cout << setw(3) << percent << "%";

        gotoxy(offsetX + 32, barY + 1);
        textcolor(7);
        if (percent < 40)      cout << "Dang khoi tao cau truc du lieu...   ";
        else if (percent < 80) cout << "Dang nap du lieu tu file he thong... ";
        else                   cout << "Hoan tat! Dang mo giao dien chinh... ";

        if (_kbhit()) {
            _getch();
            break;
        }
        Sleep(45);
    }

    textcolor(15);
}

// ==========================================================
// PHAN 4: CAC HAM VE KHUNG CHINH VA MENU DASHBOARD
// ==========================================================

// Ve khung vien doi tong the cua Menu Chinh
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

// In ten truong o Header va thong tin 3 thanh vien o Footer (Chi hien o Menu)
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

// Xoa vung noi dung ben trong khung
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

// Ve 3 khung phu ben trong Menu Chinh
void veKhungPhuMenuChinh() {
    int offsetX = getDynamicOffsetX();

    // Khung 1: Danh muc chuc nang
    drawBox(offsetX + 3, OFFSET_Y + 3, 56, 20, 3, false);
    gotoxy(offsetX + 6, OFFSET_Y + 3);
    textcolor(14); cout << " DANH MUC CHUC NANG ";

    // Khung 2: Thong tin de tai (Da cap nhat ten de tai va bo sung DSLK)
    drawBox(offsetX + 61, OFFSET_Y + 3, 34, 11, 3, false);
    gotoxy(offsetX + 64, OFFSET_Y + 3);
    textcolor(11); cout << " THONG TIN DE TAI ";

    gotoxy(offsetX + 63, OFFSET_Y + 4);
    textcolor(7);  cout << "Don vi:";
    gotoxy(offsetX + 63, OFFSET_Y + 5);
    textcolor(15); cout << "PTIT - Phan hieu TP. HCM";

    gotoxy(offsetX + 63, OFFSET_Y + 7);
    textcolor(7);  cout << "De tai:";
    gotoxy(offsetX + 63, OFFSET_Y + 8);
    textcolor(15); cout << "Quan Ly Vat Tu";

    gotoxy(offsetX + 63, OFFSET_Y + 10);
    textcolor(7);  cout << "Cau truc du lieu:";
    gotoxy(offsetX + 63, OFFSET_Y + 11);
    textcolor(10); cout << "- Cay BST & Mang Con Tro";
    gotoxy(offsetX + 63, OFFSET_Y + 12);
    textcolor(10); cout << "- Danh Sach Lien Ket Don";

    // Khung 3: Phim dieu khien (Da bo dong TAB: Chuyen nhanh)
    drawBox(offsetX + 61, OFFSET_Y + 15, 34, 8, 3, false);
    gotoxy(offsetX + 64, OFFSET_Y + 15);
    textcolor(14); cout << " PHIM DIEU KHIEN ";

    gotoxy(offsetX + 63, OFFSET_Y + 17);
    textcolor(11); cout << "UP / DOWN"; textcolor(7); cout << " : Chon chuc nang";
    gotoxy(offsetX + 63, OFFSET_Y + 19);
    textcolor(11); cout << "ENTER    "; textcolor(7); cout << " : Mo chuc nang";
    gotoxy(offsetX + 63, OFFSET_Y + 21);
    textcolor(11); cout << "ESC      "; textcolor(7); cout << " : Quay lai / Thoat";
}

// In danh sach 10 chuc nang va highlight dong dang chon
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
// PHAN 5: GIAO DIEN NHAN VIEN (GIU NGUYEN TUONG THICH CODE CU)
// ==========================================================

namespace {
    const int KHUNG_NV_X = 12;
    const int KHUNG_NV_Y = 1;
    const int KHUNG_NV_RONG = 98;
    const int KHUNG_NV_CAO = 26;
    const int O_NHAP_NV_X = 58;
    const int RONG_O_NHAP = 24;

    void XoaDongNV(int dong, int chieuRong = KHUNG_NV_RONG - 4) {
        clearLine(KHUNG_NV_X + 2, dong, chieuRong);
    }

    string CanCot(const string& text, int rong) {
        string noiDung = text.substr(0, max(0, rong - 2));
        return " " + noiDung + string(max(0, rong - 2 - (int)noiDung.size()), ' ') + " ";
    }

    string DongBang(const string cot[5]) {
        const int rong[] = {6, 10, 32, 16, 10};
        string dong = "|";
        for (int i = 0; i < 5; i++) dong += CanCot(cot[i], rong[i]) + "|";
        return dong;
    }

    string VienBang() {
        const int rong[] = {6, 10, 32, 16, 10};
        string vien = "+";
        for (int i = 0; i < 5; i++) vien += string(rong[i], '-') + "+";
        return vien;
    }
}

void VeKhungNhanVien(const string& tieuDe) {
    ShowConsoleCursor(false);
    drawBox(KHUNG_NV_X, KHUNG_NV_Y, KHUNG_NV_RONG, KHUNG_NV_CAO, 14, false);

    int padLeft = (KHUNG_NV_RONG - (int)tieuDe.length()) / 2;
    if (padLeft < 1) padLeft = 1;

    textcolor(14);
    gotoxy(KHUNG_NV_X + 2, KHUNG_NV_Y + 1);
    for (int i = 0; i < KHUNG_NV_RONG - 3; i++) cout << "=";

    gotoxy(KHUNG_NV_X + padLeft, KHUNG_NV_Y + 2);
    textcolor(11);
    cout << tieuDe;

    textcolor(14);
    gotoxy(KHUNG_NV_X + 2, KHUNG_NV_Y + 3);
    for (int i = 0; i < KHUNG_NV_RONG - 3; i++) cout << "=";
    textcolor(11);
}

void HienSoLuongNhanVien(int soLuong) {
    XoaDongNV(KHUNG_NV_Y + 5);
    gotoxy(KHUNG_NV_X + 4, KHUNG_NV_Y + 5);
    textcolor(10);
    cout << "Da co: " << soLuong << " nhan vien. Nhap thong tin de them nhan vien moi.";
    textcolor(11);
}

void HienThongBaoDayNhanVien() {
    XoaDongNV(KHUNG_NV_Y + 20);
    gotoxy(KHUNG_NV_X + 4, KHUNG_NV_Y + 20);
    textcolor(12);
    cout << "=> THONG BAO: Danh sach da du toi da 500 nhan vien!";
    
    XoaDongNV(KHUNG_NV_Y + 24);
    gotoxy(KHUNG_NV_X + 4, KHUNG_NV_Y + 24);
    textcolor(10);
    cout << "[Nhan ESC hoac ENTER de quay ve menu chinh]";
    textcolor(11);
    ShowConsoleCursor(false);
}

void HienFormNhanVien(const NhanVien& nv, int oDangChon, int viTriConTro, const string& thongBao) {
    const string nhan[] = {
        "1. Ma nhan vien (toi da 5 ky tu)",
        "2. Ho va ten dem",
        "3. Ten",
        "4. Phai (Nam / Nu)"
    };
    const string giaTri[] = {nv.MANV, nv.HO, nv.TEN, nv.PHAI};
    const int dong[] = {8, 11, 14, 17};

    int padLeftSelected = 0;

    for (int i = 0; i < 4; i++) {
        XoaDongNV(dong[i]);
        gotoxy(KHUNG_NV_X + 4, dong[i]);
        textcolor(oDangChon == i ? 14 : 11);
        cout << (oDangChon == i ? "=> " : "   ") << nhan[i];

        gotoxy(O_NHAP_NV_X, dong[i]);
        textcolor(oDangChon == i ? 15 : 11);

        string txt = giaTri[i].substr(0, RONG_O_NHAP);
        int len = (int)txt.length();
        int padLeft = (RONG_O_NHAP - len) / 2;
        int padRight = RONG_O_NHAP - len - padLeft;

        if (oDangChon == i) {
            padLeftSelected = padLeft;
        }

        cout << "[ " << string(padLeft, ' ') << txt << string(padRight, ' ') << " ]";
    }

    XoaDongNV(20);
    gotoxy(KHUNG_NV_X + 33, 20);
    if (oDangChon == 4) textcolor(31);
    else textcolor(14);
    cout << "[ LUU NHAN VIEN - ENTER / F2 ]";
    textcolor(11);

    XoaDongNV(22);
    if (!thongBao.empty()) {
        gotoxy(KHUNG_NV_X + 4, 22);
        textcolor(12);
        cout << "=> LOI: " << thongBao;
        textcolor(11);
    }

    XoaDongNV(24);
    gotoxy(KHUNG_NV_X + 4, 24);
    textcolor(10);
    cout << "[Len/Xuong/Tab: Chuyen o | Trai/Phai: Sua | Enter/F2: Luu | ESC: Huy & Ve Menu]";
    textcolor(11);

    ShowConsoleCursor(oDangChon < 4);
    if (oDangChon < 4) {
        gotoxy(O_NHAP_NV_X + 2 + padLeftSelected + viTriConTro, dong[oDangChon]);
    }
}

void HienBangNhanVien(const NhanVien* const ds[], int soLuong, int trang) {
    VeKhungNhanVien("DANH SACH NHAN VIEN KHO");

    gotoxy(KHUNG_NV_X + 4, KHUNG_NV_Y + 5);
    textcolor(10);
    if (soLuong == 0) cout << "Chua co nhan vien trong he thong. Hay them nhan vien tu menu.";
    else cout << "Tong so: " << soLuong << " nhan vien | Sap xep theo Ten, Ho";

    const string tieuDe[] = {"STT", "MA NV", "HO VA TEN DEM", "TEN", "PHAI"};
    const int bangX = KHUNG_NV_X + 6;
    const string vien = VienBang();

    textcolor(14);
    gotoxy(bangX, 7); cout << vien;
    textcolor(11);
    gotoxy(bangX, 8); cout << DongBang(tieuDe);
    textcolor(14);
    gotoxy(bangX, 9); cout << vien;

    int pageSize = SO_NHAN_VIEN_MOI_TRANG;
    for (int i = 0; i < pageSize; i++) {
        int viTri = trang * pageSize + i;
        string cot[5];
        if (viTri < soLuong) {
            const NhanVien& nv = *ds[viTri];
            cot[0] = to_string(viTri + 1);
            cot[1] = nv.MANV;
            cot[2] = nv.HO;
            cot[3] = nv.TEN;
            cot[4] = nv.PHAI;
        }
        gotoxy(bangX, 10 + i);
        textcolor(11);
        cout << DongBang(cot);
    }

    textcolor(14);
    gotoxy(bangX, 22); cout << vien;

    int soTrang = soLuong == 0 ? 1 : (soLuong + pageSize - 1) / pageSize;
    string phanTrang = "[ Trang " + to_string(trang + 1) + " / " + to_string(soTrang) + " ]";
    gotoxy(KHUNG_NV_X + (KHUNG_NV_RONG - (int)phanTrang.size()) / 2, 23);
    textcolor(14);
    cout << phanTrang;

    gotoxy(KHUNG_NV_X + 4, 24);
    textcolor(10);
    cout << "[Trai/Phai, Up/Down: Chuyen trang | ESC/Enter: Quay ve Menu]";
    textcolor(11);
    ShowConsoleCursor(false);
}

// ==========================================================
// PHAN 6: BO NAO TRUNG TAM DIEU KHIEN MENU & SWITCH CASE
// ==========================================================

void menuController(DanhSachNhanVien &dsNV, TreeVatTu &root) {
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
        else if (key == 13) {
            switch (selectedIndex) {
                case 0:
                case 1:
                    break;
                case 2: 
                    system("cls");
                    ThemNhanVien(dsNV);
                    break;
                case 3: 
                    system("cls");
                    InDanhSachNhanVien(dsNV);
                    break;
                case 4: 
                    system("cls");
                    giaodienLapHoaDon(dsNV, root);
                    break;
                case 5: 
                    system("cls");
                    giaodienInHoaDon(dsNV, root);
                    break;
                case 6:
                    break;
                case 7: // Cau h: Top 10 vat tu doanh thu cao nhat
                    giaodienTop10VatTu(dsNV, root);
                    break;
                case 8:
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
                        } else if (c == 27) {
                            chonThoat = 1;
                            daXacNhan = true;
                        } else if (c == 13) {
                            daXacNhan = true;
                        }
                    }

                    if (chonThoat == 0) {
                        system("cls");
                        drawBox(offsetX + 18, 10, 62, 7, 10, true);
                        gotoxy(offsetX + 24, 13);
                        textcolor(14);
                        cout << "Cam on ban da su dung chuong trinh! Hen gap lai.";
                        textcolor(15);
                        Sleep(3000);
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
                system("cls");
                drawFrame();
                printStaticText();
                veKhungPhuMenuChinh();
            }
        }
    }
}
