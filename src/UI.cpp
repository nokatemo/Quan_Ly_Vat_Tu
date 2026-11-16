#include "UI.h"
#include "NhanVien.h"
#include "ThongKe.h"
#include <conio.h> 

using namespace std;

// ==========================================================
// PHAN 1: CAI DAT THONG SO TOA DO VA KICH THUOC BANG
// ==========================================================

const int OFFSET_X = 15;
const int OFFSET_Y = 0;
const int WIDTH = 95;
const int HEIGHT = 28;

// Danh sach cac chuc nang (gom 10 muc)
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
// PHAN 2: CAC HAM HO TRO GIAO DIEN (CON TRO & MAU SAC)
// ==========================================================

// Ham 1: Di chuyen con tro chuot den toa do (x, y) tren man hinh
void gotoxy(int x, int y) {
    cout << flush;
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Ham 2: To mau cho chu
// Ma mau 14 la vang sang, 6 la vang toi, 31 la nen xanh chu trang
void textcolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Ham 3: Giau (an) con tro chuot nhap nhay di cho dep mat
void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; 
    SetConsoleCursorInfo(out, &cursorInfo);
}

namespace {
    const int KHUNG_NV_X = 10;
    const int KHUNG_NV_Y = 1;
    const int KHUNG_NV_RONG = 100;
    const int KHUNG_NV_CAO = 31;
    const int O_NHAP_NV_X = 75;

    void XoaDong(int dong) {
        cout << flush;
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (GetConsoleScreenBufferInfo(out, &info)) {
            COORD viTri = {KHUNG_NV_X + 1, static_cast<short>(dong)};
            DWORD daXoa = 0;
            FillConsoleOutputCharacterA(out, ' ', KHUNG_NV_RONG - 1, viTri, &daXoa);
        } else {
            gotoxy(KHUNG_NV_X + 1, dong);
            cout << string(KHUNG_NV_RONG - 1, ' ') << flush;
        }
    }

    string CanCot(const string& text, int rong) {
        string noiDung = text.substr(0, rong - 2);
        return " " + noiDung + string(rong - 2 - noiDung.size(), ' ') + " ";
    }

    string DongBang(const string cot[5]) {
        const int rong[] = {6, 10, 30, 25, 15};
        string dong = "|";
        for (int i = 0; i < 5; i++) dong += CanCot(cot[i], rong[i]) + "|";
        return dong;
    }

    string VienBang() {
        const int rong[] = {6, 10, 30, 25, 15};
        string vien = "+";
        for (int i = 0; i < 5; i++) vien += string(rong[i], '-') + "+";
        return vien;
    }

    void HienBangNhanVienTrongForm(const DanhSachNhanVien& ds, int trang) {
        const string tieuDe[] = {"STT", "MA NV", "HO VA TEN DEM", "TEN", "PHAI"};
        const int bangX = KHUNG_NV_X + 4;
        const string vien = VienBang();
        const int soTrang = ds.soLuong == 0 ? 1 :
            (ds.soLuong + SO_NHAN_VIEN_TREN_FORM - 1) / SO_NHAN_VIEN_TREN_FORM;

        XoaDong(16);
        gotoxy(KHUNG_NV_X + 3, 16);
        textcolor(10);
        cout << "DANH SACH NHAN VIEN (SAP XEP THEO MA)";

        textcolor(14);
        gotoxy(bangX, 17);
        cout << vien;
        textcolor(11);
        gotoxy(bangX, 18);
        cout << DongBang(tieuDe);
        textcolor(14);
        gotoxy(bangX, 19);
        cout << vien;

        for (int i = 0; i < SO_NHAN_VIEN_TREN_FORM; i++) {
            const int viTri = trang * SO_NHAN_VIEN_TREN_FORM + i;
            string cot[5];
            if (viTri < ds.soLuong && ds.ds[viTri] != nullptr) {
                const NhanVien& nhanVien = *ds.ds[viTri];
                cot[0] = to_string(viTri + 1);
                cot[1] = nhanVien.MANV;
                cot[2] = nhanVien.ho;
                cot[3] = nhanVien.ten;
                cot[4] = nhanVien.phai;
            }
            gotoxy(bangX, 20 + i);
            textcolor(11);
            cout << DongBang(cot);
        }
        textcolor(14);
        gotoxy(bangX, 27);
        cout << vien;

        XoaDong(28);
        string phanTrang = "Trang " + to_string(trang + 1) + " / " + to_string(soTrang)
                         + " | PgUp/PgDn: chuyen trang";
        gotoxy(KHUNG_NV_X + (KHUNG_NV_RONG - static_cast<int>(phanTrang.size())) / 2, 28);
        textcolor(11);
        cout << phanTrang;
    }
}

void HienSoLuongNhanVien(int soLuong) {
    XoaDong(5);
    gotoxy(KHUNG_NV_X + 3, 5);
    textcolor(10);
    cout << "Tong so: " << soLuong << " / 500 nhan vien" << flush;
    textcolor(11);
}

void HienThongBaoDayNhanVien() {
    XoaDong(15);
    gotoxy(KHUNG_NV_X + 3, 15);
    textcolor(12);
    cout << "Danh sach da du 500 nhan vien.";
    XoaDong(30);
    gotoxy(KHUNG_NV_X + 3, 30);
    textcolor(10);
    cout << "[Nhan Esc hoac Enter de quay ve menu chinh]" << flush;
    textcolor(11);
    ShowConsoleCursor(false);
}

void VeKhungNhanVien(const string& tieuDe) {
    ShowConsoleCursor(false);
    textcolor(14);
    gotoxy(KHUNG_NV_X, KHUNG_NV_Y);
    cout << string(KHUNG_NV_RONG + 1, char(178));
    for (int y = KHUNG_NV_Y + 1; y < KHUNG_NV_Y + KHUNG_NV_CAO; y++) {
        gotoxy(KHUNG_NV_X, y);
        cout << char(178);
        textcolor(11);
        cout << string(KHUNG_NV_RONG - 1, ' ');
        textcolor(14);
        cout << char(178);
    }
    gotoxy(KHUNG_NV_X, KHUNG_NV_Y + KHUNG_NV_CAO);
    cout << string(KHUNG_NV_RONG + 1, char(178));
    gotoxy(KHUNG_NV_X + 2, 2);
    cout << string(KHUNG_NV_RONG - 3, '=');
    gotoxy(KHUNG_NV_X + 2, 4);
    cout << string(KHUNG_NV_RONG - 3, '=');
    string ten = tieuDe.substr(0, KHUNG_NV_RONG - 8);
    gotoxy(KHUNG_NV_X + (KHUNG_NV_RONG - static_cast<int>(ten.size())) / 2, 3);
    textcolor(11);
    cout << ten << flush;
}

void HienFormNhanVien(const NhanVien& nv, const DanhSachNhanVien& ds, int trang,
                     int oDangChon, int viTriConTro,
                     const string& thongBao) {
    const string nhan[] = {"1. Ma nhan vien (toi da 5 ky tu)", "2. Ho va ten dem", "3. Ten", "4. Phai (Nam / Nu)"};
    const string giaTri[] = {nv.MANV, nv.ho, nv.ten, nv.phai};
    const int dong[] = {6, 8, 10, 12};
    for (int i = 0; i < 4; i++) {
        XoaDong(dong[i]);
        gotoxy(KHUNG_NV_X + 3, dong[i]);
        textcolor(oDangChon == i ? 14 : 11);
        cout << (oDangChon == i ? "> " : "  ") << nhan[i] << flush;
        gotoxy(O_NHAP_NV_X, dong[i]);
        textcolor(oDangChon == i ? 15 : 11);
        string noiDung = giaTri[i].substr(0, 20);
        cout << "[ " << noiDung << string(20 - noiDung.size(), ' ') << " ]" << flush;
    }
    XoaDong(14);
    gotoxy(43, 14);
    textcolor(oDangChon == 4 ? 224 : 14);
    cout << "[ LUU NHAN VIEN - ENTER / F2 ]" << flush;
    textcolor(11);
    XoaDong(15);
    if (!thongBao.empty()) {
        gotoxy(KHUNG_NV_X + 3, 15);
        textcolor(12);
        cout << thongBao.substr(0, KHUNG_NV_RONG - 6) << flush;
    }

    HienBangNhanVienTrongForm(ds, trang);
    textcolor(11);
    XoaDong(30);
    gotoxy(KHUNG_NV_X + 3, 30);
    textcolor(10);
    cout << "Len/Xuong/Tab: chuyen o | Trai/Phai: sua | F2: luu | Esc: huy va quay menu" << flush;
    textcolor(11);
    ShowConsoleCursor(oDangChon < 4);
    if (oDangChon < 4) {
        gotoxy(O_NHAP_NV_X + 2 + viTriConTro, dong[oDangChon]);
    }
}

void HienBangNhanVien(const NhanVien* const ds[], int soLuong, int trang) {
    VeKhungNhanVien("DANH SACH NHAN VIEN");
    gotoxy(KHUNG_NV_X + 3, 6);
    textcolor(10);
    if (soLuong == 0) cout << "Chua co nhan vien. Hay them nhan vien tu menu.";
    else cout << "Tong so: " << soLuong << " nhan vien | Sap xep theo ten, ho";

    const string tieuDe[] = {"STT", "MA NV", "HO VA TEN DEM", "TEN", "PHAI"};
    const int bangX = KHUNG_NV_X + 4;
    const string vien = VienBang();
    textcolor(14);
    gotoxy(bangX, 7);
    cout << vien;
    textcolor(11);
    gotoxy(bangX, 8);
    cout << DongBang(tieuDe);
    textcolor(14);
    gotoxy(bangX, 9);
    cout << vien;
    for (int i = 0; i < SO_NHAN_VIEN_MOI_TRANG; i++) {
        int viTri = trang * SO_NHAN_VIEN_MOI_TRANG + i;
        string cot[5];
        if (viTri < soLuong) {
            const NhanVien& nv = *ds[viTri];
            cot[0] = to_string(viTri + 1);
            cot[1] = nv.MANV;
            cot[2] = nv.ho;
            cot[3] = nv.ten;
            cot[4] = nv.phai;
        }
        gotoxy(bangX, 10 + i);
        textcolor(11);
        cout << DongBang(cot);
    }
    textcolor(14);
    gotoxy(bangX, 25);
    cout << vien;
    int soTrang = soLuong == 0 ? 1 : (soLuong + SO_NHAN_VIEN_MOI_TRANG - 1) / SO_NHAN_VIEN_MOI_TRANG;
    string phanTrang = "Trang " + to_string(trang + 1) + " / " + to_string(soTrang);
    gotoxy(KHUNG_NV_X + (KHUNG_NV_RONG - static_cast<int>(phanTrang.size())) / 2, 27);
    textcolor(11);
    cout << phanTrang;
    gotoxy(KHUNG_NV_X + 3, 30);
    textcolor(10);
    cout << "[Trai/Phai, PgUp/PgDn: chuyen trang | Esc hoac Enter: ve menu]" << flush;
    textcolor(11);
    ShowConsoleCursor(false);
}


// ==========================================================
// PHAN 3: CAC HAM VE KHUNG VA IN CHU
// ==========================================================

// Ham 4: Ve khung vien mau vang cho bang
void drawFrame() {
    textcolor(6);
    for (int i = 0; i <= WIDTH; i++) {
        gotoxy(OFFSET_X + i, OFFSET_Y);      cout << char(178);
        gotoxy(OFFSET_X + i, OFFSET_Y + 2);  cout << char(178);
        gotoxy(OFFSET_X + i, OFFSET_Y + 24); cout << char(178);
        gotoxy(OFFSET_X + i, OFFSET_Y + 28); cout << char(178);
    }

    for (int i = 0; i <= HEIGHT; i++) {
        gotoxy(OFFSET_X, OFFSET_Y + i);         cout << char(178);
        gotoxy(OFFSET_X + WIDTH, OFFSET_Y + i); cout << char(178);
    }

    gotoxy(0, 0);
}

// Ham 5: In cac dong chu co dinh 
void printStaticText() {
    textcolor(14);
    gotoxy(OFFSET_X + 13, OFFSET_Y + 1);
    cout << "HOC VIEN CONG NGHE BUU CHINH VIEN THONG CO SO THANH PHO HO CHI MINH";

    gotoxy(OFFSET_X + 15, OFFSET_Y + 25);
    cout << ">> Bui Vu Nguyen Khoa -------- N25DECE097  -------- E25CQCE03-N <<";

    gotoxy(OFFSET_X + 15, OFFSET_Y + 26);
    cout << ">> Ngo Minh Tien      -------- N25DECE121  -------- E25CQCE03-N <<";

    gotoxy(OFFSET_X + 15, OFFSET_Y + 27);
    cout << ">> Tran Trung Nguyen  -------- N25DECE105  -------- E25CQCE03-N <<";

    gotoxy(0, 0);
}

// Ham 6: In danh sach 10 chuc nang va to mau (highlight)
void printMenuItems(int selectedIndex) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        gotoxy(OFFSET_X + 10, OFFSET_Y + 4 + i * 2);
        if (i == selectedIndex) {
            textcolor(31);
            cout << menuItems[i];
        } else {
            textcolor(14);
            cout << menuItems[i];
        }
    }
    textcolor(14);
    gotoxy(0, 0);
}


// ==========================================================
// PHAN 4: BO NAO TRUNG TAM DIEU KHIEN MENU & SWITCH CASE
// ==========================================================

// Ham 7: Quan ly vong lap chinh va doc tin hieu tu ban phim
void menuController() {
	DanhSachNhanVien ds;
    system("mode con cols=120 lines=35"); // Setup khung nhin mac dinh cho console
    if (!DocFileNhanVien(ds)) {
        system("cls");
        ShowConsoleCursor(true);
        textcolor(12);
        cout << "Khong doc duoc NhanVien.txt. Kiem tra dinh dang va quyen truy cap.\n"
             << "Nhan phim bat ky de thoat; file hien tai se khong bi ghi de." << flush;
        _getch();
        return;
    }
    
    ShowConsoleCursor(false); // Giau con tro chuot di
    system("cls");            // Xoa sach man hinh 
    
    // Ve khung va in chu 1 lan duy nhat 
    drawFrame();
    printStaticText();
    
    int selectedIndex = 0; // Vi tri dang chon (Bat dau la muc 1)
    bool isRunning = true; 

    while (isRunning) {
        printMenuItems(selectedIndex); // Cap nhat mau menu lien tuc

        int key = _getch(); // Cho bam 1 phim bat ky
        
        // Bat su kien khi bam mui ten len/xuong
        if (key == 0 || key == 224) { 
            key = _getch(); // Doc ma thu 2 de xac dinh huong
            
            if (key == 72) { // Mui ten Len
                selectedIndex--; 
                if (selectedIndex < 0) selectedIndex = NUM_ITEMS - 1; // Nhay xuong cuoi neu cham noc
            } else if (key == 80) { // Mui ten Xuong
                selectedIndex++; 
                if (selectedIndex >= NUM_ITEMS) selectedIndex = 0; // Nhay len dau neu cham day
            }
        }
        // Ma 13 la phim Enter
        else if (key == 13) { 
            system("cls");           
            ShowConsoleCursor(true); // Hien lai con tro de cho nhap lieu
            bool quayVeMenuNgay = false;
            
            // DAY CHINH LA NOI BO CODE CHUC NANG DO AN VAO 
            switch (selectedIndex) {
                case 0:
                    // Code Quan li vat tu
                    break;
                case 1:
                    // Code Danh sach vat tu
                    break;
                case 2:
                    ThemNhanVien(ds);
                    quayVeMenuNgay = true;
                    break;
                case 3:
                	InDanhSachNhanVien(ds);
                    quayVeMenuNgay = true;
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    ThongKeDoanhThuTheoThang(ds);
                    quayVeMenuNgay = true;
                    break;
                case 9: // Chon chuc nang 0. Thoat
                    cout << "Chuong trinh ket thuc!\n";
                    isRunning = false; // Dap vo vong lap while -> Thoat
                    break;
            }
            
            // Chay xong code chuc nang, tam dung man hinh de xem
            if (isRunning) {
                if (!quayVeMenuNgay) {
                    cout << "\nNhan phim bat ky de quay lai menu...";
                    _getch();
                }
                
                // Khoi phuc lai giao dien bang menu
                ShowConsoleCursor(false); 
                system("cls");            
                drawFrame();              
                printStaticText();        
            }
        }
    }
}
