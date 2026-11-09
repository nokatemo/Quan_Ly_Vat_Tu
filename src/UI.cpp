#include "UI.h"
#include <conio.h> 
#include <iomanip>
#include <iostream>

using namespace std;

// ==========================================================
// PHAN 1: THONG SO TOA DO VA DANH SACH MENU CHINH
// ==========================================================

// Toa do goc va kich thuoc khung ung dung chinh
const int OFFSET_X = 15;
const int OFFSET_Y = 0;
const int WIDTH = 95;
const int HEIGHT = 28;

// So luong phan tu va danh sach ten cac chuc nang Menu
const int NUM_ITEMS = 10;
string menuItems[NUM_ITEMS] = {
    "1.Cap Nhat Vat Tu",
    "2.In Danh Sach Vat Tu Ton Kho",
    "3.Cap Nhat Nhan Vien",
    "4.In Danh Sach Nhan Vien",
    "5.Lap Hoa Don Nhap / Xuat",
    "6.In Chi Tiet 1 Hoa Don",
    "7.Thong Ke Hoa Don Theo Thoi Gian",
    "8.Top 10 Vat Tu Doanh Thu Cao Nhat",
    "9.Thong Ke Doanh Thu Theo Thang",
    "0.Thoat Chuong Trinh"
};

// ==========================================================
// PHAN 2: CAC HAM HO TRO DIEU KHIEN CON TRO & MAU SAC CONSOLE
// ==========================================================

// Di chuyen con tro console den toa do (x, y)
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Thiet lap mau chu va mau nen console
void textcolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// An hoac hien con tro nhap nhay tren console (showFlag = true: hien, false: an)
void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; 
    SetConsoleCursorInfo(out, &cursorInfo);
}

// Ve khung hinh chu nhat voi vi tri (x,y), chieu rong w, chieu cao h va mau color
void drawBox(int x, int y, int w, int h, int color) {
    textcolor(color);
    // Ve hai duong ke ngang tren va duoi
    for (int i = 0; i <= w; i++) {
        gotoxy(x + i, y);     cout << char(178);
        gotoxy(x + i, y + h); cout << char(178);
    }
    // Ve hai duong ke doc trai va phai
    for (int i = 0; i <= h; i++) {
        gotoxy(x, y + i);     cout << char(178);
        gotoxy(x + w, y + i); cout << char(178);
    }
}

// Xoa mot dong tai toa do (x,y) voi chieu dai dinh truoc
void clearLine(int x, int y, int length) {
    gotoxy(x, y);
    for (int i = 0; i < length; i++) cout << " ";
    gotoxy(x, y);
}

// Ve khung vien tong the bao quanh toan giao dien ung dung
void drawFrame() {
    textcolor(6);
    // Ve cac duong ke ngang chia cac phan header, body va footer
    for (int i = 0; i <= WIDTH; i++) {
        gotoxy(OFFSET_X + i, OFFSET_Y);      cout << char(178);
        gotoxy(OFFSET_X + i, OFFSET_Y + 2);  cout << char(178);
        gotoxy(OFFSET_X + i, OFFSET_Y + 24); cout << char(178);
        gotoxy(OFFSET_X + i, OFFSET_Y + 28); cout << char(178);
    }

    // Ve hai bien doc hai ben
    for (int i = 0; i <= HEIGHT; i++) {
        gotoxy(OFFSET_X, OFFSET_Y + i);         cout << char(178);
        gotoxy(OFFSET_X + WIDTH, OFFSET_Y + i); cout << char(178);
    }
    gotoxy(0, 0);
}

// In phan chu tinh (Header & Footer): Ten truong hoc va danh sach thanh vien thuc hien
void printStaticText() {
    textcolor(14);
    // Header truong hoc
    gotoxy(OFFSET_X + 13, OFFSET_Y + 1); 
    cout << "HOC VIEN CONG NGHE BUU CHINH VIEN THONG PHAN HIEU THANH PHO HO CHI MINH";

    // Footer thong tin sinh vien thuc hien
    gotoxy(OFFSET_X + 15, OFFSET_Y + 25); 
    cout << ">> Bui Vu Nguyen Khoa -------- N25DECE097  -------- E25CQCE03-N <<";

    gotoxy(OFFSET_X + 15, OFFSET_Y + 26); 
    cout << ">> Ngo Minh Tien      -------- N25DECE121  -------- E25CQCE03-N <<";

    gotoxy(OFFSET_X + 15, OFFSET_Y + 27); 
    cout << ">> Tran Trung Nguyen  -------- N25DECE105  -------- E25CQCE03-N <<";
    gotoxy(0, 0); 
}

// In danh sach cac chuc nang Menu chinh, highlight muc dang duoc chon
void printMenuItems(int selectedIndex) {
    int startY = OFFSET_Y + 4; 
    for (int i = 0; i < NUM_ITEMS; i++) {
        gotoxy(OFFSET_X + 10, startY + (i * 2)); 
        if (i == selectedIndex) {
            textcolor(31); // Highlight mau nen trang/xanh chu noi bat
            cout << menuItems[i]; 
        } else {
            textcolor(14); // Mau vang tieu chuan
            cout << menuItems[i]; 
        }
    }
    textcolor(14); 
    gotoxy(0, 0);  
}

// ==========================================================
// PHAN 3: CAC HAM NOI BO DINH DANG BANG VA KHUNG NHAN VIEN
// ==========================================================

namespace {
    // Hang so dinh vi khung Nhan Vien
    const int KHUNG_NV_X = 12;
    const int KHUNG_NV_Y = 1;
    const int KHUNG_NV_RONG = 98;
    const int KHUNG_NV_CAO = 26;
    const int O_NHAP_NV_X = 58;
    const int RONG_O_NHAP = 24;

    // Xoa mot dong trong khung Nhan Vien
    void XoaDongNV(int dong, int chieuRong = KHUNG_NV_RONG - 4) {
        clearLine(KHUNG_NV_X + 2, dong, chieuRong);
    }

    // Can giua noi dung va them khoang trang hai ben cho o trong bang
    string CanCot(const string& text, int rong) {
        string noiDung = text.substr(0, max(0, rong - 2));
        return " " + noiDung + string(max(0, rong - 2 - (int)noiDung.size()), ' ') + " ";
    }

    // Tao chuoi mot dong du lieu hoan chinh cho bang danh sach
    string DongBang(const string cot[5]) {
        const int rong[] = {6, 10, 32, 16, 10};
        string dong = "|";
        for (int i = 0; i < 5; i++) dong += CanCot(cot[i], rong[i]) + "|";
        return dong;
    }

    // Tao chuoi duong vien ngan bang
    string VienBang() {
        const int rong[] = {6, 10, 32, 16, 10};
        string vien = "+";
        for (int i = 0; i < 5; i++) vien += string(rong[i], '-') + "+";
        return vien;
    }
}

// ==========================================================
// PHAN 4: CAC HAM GIAO DIEN NHAN VIEN (CAN GIUA CHU & CON TRO)
// ==========================================================

// Ve khung va tieu de chung cho chuc nang Nhan Vien
void VeKhungNhanVien(const string& tieuDe) {
    ShowConsoleCursor(false);
    drawBox(KHUNG_NV_X, KHUNG_NV_Y, KHUNG_NV_RONG, KHUNG_NV_CAO, 14);

    // Tinh toa do x de tieu de duoc can giua khung
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

// Hien thi so luong nhan vien hien co trong danh sach
void HienSoLuongNhanVien(int soLuong) {
    XoaDongNV(KHUNG_NV_Y + 5);
    gotoxy(KHUNG_NV_X + 4, KHUNG_NV_Y + 5);
    textcolor(10);
    cout << "Da co: " << soLuong << " nhan vien. Nhap thong tin de them nhan vien moi.";
    textcolor(11);
}

// Hien thong bao loi khi danh sach da dat gioi han 500 nhan vien
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

// Hien thi Form nhap thong tin Nhan Vien voi thuat toan can giua chuoi trong [ ] va tinh toa do con tro nhap nhay
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

    // In 4 o nhap thong tin nhan vien
    for (int i = 0; i < 4; i++) {
        XoaDongNV(dong[i]);
        gotoxy(KHUNG_NV_X + 4, dong[i]);
        textcolor(oDangChon == i ? 14 : 11);
        cout << (oDangChon == i ? "=> " : "   ") << nhan[i];

        gotoxy(O_NHAP_NV_X, dong[i]);
        textcolor(oDangChon == i ? 15 : 11);

        // THUAT TOAN CAN GIUA CHUOI TRONG KHUNG [ ]
        string txt = giaTri[i].substr(0, RONG_O_NHAP);
        int len = (int)txt.length();
        int padLeft = (RONG_O_NHAP - len) / 2;          // Khoang trang ben trai
        int padRight = RONG_O_NHAP - len - padLeft;     // Khoang trang ben phai

        if (oDangChon == i) {
            padLeftSelected = padLeft;
        }

        // In chuoi duoc chia deu khoang trang 2 ben -> Chuoi nam chinh giua [ ]
        cout << "[ " << string(padLeft, ' ') << txt << string(padRight, ' ') << " ]";
    }

    // In Nut Luu (Highlight neu dang duoc truyen focus)
    XoaDongNV(20);
    gotoxy(KHUNG_NV_X + 33, 20);
    if (oDangChon == 4) textcolor(31);
    else textcolor(14);
    cout << "[ LUU NHAN VIEN - ENTER / F2 ]";
    textcolor(11);

    // In dong thong bao loi validation (neu co)
    XoaDongNV(22);
    if (!thongBao.empty()) {
        gotoxy(KHUNG_NV_X + 4, 22);
        textcolor(12);
        cout << "=> LOI: " << thongBao;
        textcolor(11);
    }

    // Thanh huong dan thao tac o day khung
    XoaDongNV(24);
    gotoxy(KHUNG_NV_X + 4, 24);
    textcolor(10);
    cout << "[Len/Xuong/Tab: Chuyen o | Trai/Phai: Sua | Enter/F2: Luu | ESC: Huy & Ve Menu]";
    textcolor(11);

    // Thiet lap con tro console nhap nhay di theo vi tri ky tu trong o dang chon
    ShowConsoleCursor(oDangChon < 4);
    if (oDangChon < 4) {
        // Con tro nhap nhay chay theo vi tri chinh giua cua chuoi
        gotoxy(O_NHAP_NV_X + 2 + padLeftSelected + viTriConTro, dong[oDangChon]);
    }
}

// Hien thi bang danh sach nhan vien phan trang
void HienBangNhanVien(const NhanVien* const ds[], int soLuong, int trang) {
    VeKhungNhanVien("DANH SACH NHAN VIEN KHO");

    gotoxy(KHUNG_NV_X + 4, KHUNG_NV_Y + 5);
    textcolor(10);
    if (soLuong == 0) cout << "Chua co nhan vien trong he thong. Hay them nhan vien tu menu.";
    else cout << "Tong so: " << soLuong << " nhan vien | Sap xep theo Ten, Ho";

    const string tieuDe[] = {"STT", "MA NV", "HO VA TEN DEM", "TEN", "PHAI"};
    const int bangX = KHUNG_NV_X + 6;
    const string vien = VienBang();

    // In Header cua Bang
    textcolor(14);
    gotoxy(bangX, 7); cout << vien;
    textcolor(11);
    gotoxy(bangX, 8); cout << DongBang(tieuDe);
    textcolor(14);
    gotoxy(bangX, 9); cout << vien;

    // In cac dong du lieu theo trang
    int pageSize = SO_NHAN_VIEN_MOI_TRANG; // Su dung hang so dong bo (12 dong)
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

    // In duong vien duoi bang
    textcolor(14);
    gotoxy(bangX, 22); cout << vien;

    // In chi so phan trang
    int soTrang = soLuong == 0 ? 1 : (soLuong + pageSize - 1) / pageSize;
    string phanTrang = "[ Trang " + to_string(trang + 1) + " / " + to_string(soTrang) + " ]";
    gotoxy(KHUNG_NV_X + (KHUNG_NV_RONG - (int)phanTrang.size()) / 2, 23);
    textcolor(14);
    cout << phanTrang;

    // Thanh huong dan di chuyen trang
    gotoxy(KHUNG_NV_X + 4, 24);
    textcolor(10);
    cout << "[Trai/Phai, Up/Down: Chuyen trang | ESC/Enter: Quay ve Menu]";
    textcolor(11);
    ShowConsoleCursor(false);
}

// ==========================================================
// PHAN 5: THOAT CHUONG TRINH & CONTROLLER MENU CHINH
// ==========================================================

// Giao dien va hieu ung thoat ung dung
void GiaoDienThoatChuongTrinh() {
    system("cls");
    int boxX = 22, boxY = 5, boxW = 60, boxH = 12;
    drawBox(boxX, boxY, boxW, boxH, 14);

    textcolor(11);
    gotoxy(boxX + 18, boxY + 2);
    cout << "THONG BAO HE THONG";

    textcolor(14);
    gotoxy(boxX + 4, boxY + 3);
    for (int i = 0; i < boxW - 7; i++) cout << "~";

    textcolor(10);
    gotoxy(boxX + 11, boxY + 5);
    cout << "CAM ON BAN DA SU DUNG HE THONG!";
    
    textcolor(11);
    gotoxy(boxX + 15, boxY + 7);
    cout << "CHUC BAN MOT NGAY TOT LAM!";

    textcolor(14);
    gotoxy(boxX + 12, boxY + 9);
    cout << "Dang dong ung dung va luu du lieu";
    
    for (int i = 0; i < 4; i++) {
        Sleep(500);
        cout << ".";
    }

    textcolor(10);
    gotoxy(boxX + 17, boxY + 10);
    cout << "HOAN TAT! HEN GAP LAI.";
    
    Sleep(1500);
    system("cls");
    exit(0);
}

// Ham dieu khien menu chinh (Menu Controller)
void menuController(DanhSachNhanVien &dsNV, TreeVatTu &root) {
    system("mode con cols=120 lines=35");
    ShowConsoleCursor(false);
    system("cls");            
    
    drawFrame();
    printStaticText();
    
    int selectedIndex = 0; 
    bool isRunning = true; 

    // Vong lap dieu khien Menu bang phat hien phim Mui ten va Enter
    while (isRunning) {
        printMenuItems(selectedIndex); 
        char key = _getch(); 
        
        if (key == -32 || key == 224) { 
            key = _getch(); 
            if (key == 72) { // Mui ten Up
                selectedIndex--; 
                if (selectedIndex < 0) selectedIndex = NUM_ITEMS - 1; 
            } else if (key == 80) { // Mui ten Down
                selectedIndex++; 
                if (selectedIndex >= NUM_ITEMS) selectedIndex = 0; 
            }
        } 
        else if (key == 13) { // Enter -> Kich hoat chuc nang duoc chon
            system("cls");           
            ShowConsoleCursor(true); 
            
            switch (selectedIndex) {
                case 0: break;
                case 1: break;
                case 2: 
                    ThemNhanVien(dsNV);
                    break;
                case 3: 
                    InDanhSachNhanVien(dsNV);
                    break;
                case 4: 
                    giaodienLapHoaDon(dsNV, root);
                    break;
                case 5: 
                    giaodienInHoaDon(dsNV, root);
                    break;
                case 6: break;
                case 7: break;
                case 8: break;
                case 9:
                    GiaoDienThoatChuongTrinh();
                    break;
            }
            
            if (isRunning) {
                ShowConsoleCursor(false); 
                system("cls");            
                drawFrame();              
                printStaticText();        
            }
        }
    }
}
