#include "UI.h"
#include "NhanVien.h"
#include <conio.h> 

using namespace std;

// ==========================================================
// PHAN 1: CAI DAT THONG SO TOA DO VA KICH THUOC BANG
// ==========================================================

const int OFFSET_X = 15;  // Day bang sang phai de ra giua man hinh
const int OFFSET_Y = 0;   // Keo sat mep tren cung man hinh de tiet kiem khong gian
const int WIDTH = 95;     // Do rong cua bang
// CHIEU CAO 28: Day la kich thuoc an toan tuyet doi. Toan bo bang chi 
// nam trong 29 dong (tu 0 den 28), dam bao 100% man hinh khong bi cuon (scroll) 
// lam de chu len vien o bat ky may tinh nao.
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

// ==========================================================
// KHU VUC GIAO DIEN DANH RIENG CHO PHAN NHAN VIEN
// ==========================================================

const int KHUNG_NV_X = 10;     // Toa do X mep trai cua khung Nhan Vien
const int KHUNG_NV_Y = 1;      // Toa do Y mep tren cua khung Nhan Vien
const int KHUNG_NV_RONG = 100; // Chieu rong cua khung Nhan Vien
const int KHUNG_NV_CAO = 31;   // Chieu cao cua khung Nhan Vien (tu dong 1 den dong 32)
const int O_NHAP_NV_X = 75;    // Toa do X bat dau ve cac o nhap [ ... ]

// Xoa trang 1 dong ben trong khung Nhan Vien bang cach in ри khoang trang
void XoaDong(int dong) {
    gotoxy(KHUNG_NV_X + 1, dong);
    cout << string(KHUNG_NV_RONG - 1, ' ') << flush;
}

// Can le trai noi dung nam trong 1 o cua bang voi do rong co dinh
string CanCot(const string& text, int rong) {
    string noiDung = text.substr(0, rong - 2); // Cat bot neu chuoi dai hon o
    int soKhoangTrangBu = (rong - 2) - (int)noiDung.length();
    return " " + noiDung + string(soKhoangTrangBu, ' ') + " ";
}

// Ghep 5 cot (STT, MA NV, HO, TEN, PHAI) thanh 1 dong trong bang
string DongBang(const string cot[5]) {
    const int rong[5] = {6, 10, 30, 25, 15}; // Do rong cua tung cot
    string dong = "|";
    for (int i = 0; i < 5; i++) {
        dong += CanCot(cot[i], rong[i]) + "|";
    }
    return dong;
}

// Tao duong ke ngang cua bang: +------+----------+...+
string VienBang() {
    const int rong[5] = {6, 10, 30, 25, 15};
    string vien = "+";
    for (int i = 0; i < 5; i++) {
        vien += string(rong[i], '-') + "+";
    }
    return vien;
}

// Hien thi tong so nhan vien hien co o dong Y = 5
void HienSoLuongNhanVien(int soLuong) {
    XoaDong(5);
    gotoxy(KHUNG_NV_X + 3, 5);
    textcolor(10);
    cout << "Tong so: " << soLuong << " / 500 nhan vien" << flush;
    textcolor(11);
}

// Hien thong bao khi mang da day 500 nhan vien
void HienThongBaoDayNhanVien() {
    XoaDong(11);
    gotoxy(KHUNG_NV_X + 3, 11);
    textcolor(12);
    cout << "Danh sach da du 500 nhan vien.";
    XoaDong(30);
    gotoxy(KHUNG_NV_X + 3, 30);
    textcolor(10);
    cout << "[PgUp/PgDn: chuyen trang DS | Nhan Esc hoac Enter de quay ve menu chinh]" << flush;
    textcolor(11);
    ShowConsoleCursor(false);
}

// Ve khung vien lon bao quanh man hinh Nhan Vien va tieu de o tren cung
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
    gotoxy(KHUNG_NV_X + (KHUNG_NV_RONG - (int)ten.length()) / 2, 3);
    textcolor(11);
    cout << ten << flush;
}

// Hien thi 4 o nhap lieu o nua tren man hinh (tu dong 6 den dong 11)
void HienFormNhanVien(const NhanVien& nv, int oDangChon, int viTriConTro,
                     const string& thongBao) {
    const string nhan[4] = {
        "1. Ma nhan vien (toi da 5 ky tu)",
        "2. Ho va ten dem",
        "3. Ten",
        "4. Phai (Nam / Nu)"
    };
    const string giaTri[4] = {nv.MANV, nv.ho, nv.ten, nv.phai};
    const int dong[4] = {6, 7, 8, 9}; // Toa do Y cua 4 o nhap

    for (int i = 0; i < 4; i++) {
        XoaDong(dong[i]);
        gotoxy(KHUNG_NV_X + 3, dong[i]);
        textcolor(oDangChon == i ? 14 : 11);
        cout << (oDangChon == i ? "> " : "  ") << nhan[i] << flush;
        gotoxy(O_NHAP_NV_X, dong[i]);
        textcolor(oDangChon == i ? 15 : 11);
        string noiDung = giaTri[i].substr(0, 20);
        cout << "[ " << noiDung << string(20 - noiDung.length(), ' ') << " ]" << flush;
    }

    // In nut Luu o dong Y = 10
    XoaDong(10);
    gotoxy(43, 10);
    textcolor(oDangChon == 4 ? 224 : 14);
    cout << "[ LUU NHAN VIEN - ENTER / F2 ]" << flush;
    textcolor(11);

    // In dong thong bao loi (neu co) o dong Y = 11
    XoaDong(11);
    if (!thongBao.empty()) {
        gotoxy(KHUNG_NV_X + 3, 11);
        textcolor(12);
        cout << thongBao.substr(0, KHUNG_NV_RONG - 6) << flush;
    }

    // In huong dan phim tat o cuoi khung (dong 29, 30)
    textcolor(11);
    XoaDong(29);
    gotoxy(KHUNG_NV_X + 3, 29);
    cout << "Len/Xuong/Tab: chuyen o | Trai/Phai: sua | Enter: tiep/Luu | F2: luu | PgUp/PgDn: trang DS";
    XoaDong(30);
    gotoxy(KHUNG_NV_X + 3, 30);
    textcolor(10);
    cout << "[Nhan Esc de huy thong tin dang nhap va quay ve menu chinh]" << flush;
    textcolor(11);

    ShowConsoleCursor(oDangChon < 4);
    if (oDangChon < 4) {
        gotoxy(O_NHAP_NV_X + 2 + viTriConTro, dong[oDangChon]);
    }
}

// Hien thi bang danh sach nhan vien (sap xep tang dan theo MNV) ngay ben duoi Form nhap
void HienBangNhanVienTheoMaKhiNhap(const NhanVien* const ds[], int soLuong,
                                   int trang, int viTriVuaThem) {
    // Ve vach ngan ngang o dong Y = 12 giua khung Nhap (o tren) va khung Danh sach (o duoi)
    textcolor(14);
    gotoxy(KHUNG_NV_X, 12);
    cout << string(KHUNG_NV_RONG + 1, char(178));

    // In tieu de cua bang ben duoi o dong Y = 13
    XoaDong(13);
    string tieuDeDS = "DANH SACH NHAN VIEN (SAP XEP TANG DAN THEO MNV)";
    gotoxy(KHUNG_NV_X + (KHUNG_NV_RONG - (int)tieuDeDS.length()) / 2, 13);
    textcolor(14);
    cout << tieuDeDS;

    const string tieuDeCot[5] = {"STT", "MA NV", "HO VA TEN DEM", "TEN", "PHAI"};
    const int bangX = KHUNG_NV_X + 4;
    const string vien = VienBang();

    textcolor(14);
    gotoxy(bangX, 14);
    cout << vien;
    textcolor(11);
    gotoxy(bangX, 15);
    cout << DongBang(tieuDeCot);
    textcolor(14);
    gotoxy(bangX, 16);
    cout << vien;

    // In 10 dong du lieu nhan vien (tu dong 17 den dong 26)
    for (int i = 0; i < SO_NV_MOI_TRANG_NHAP; i++) {
        int viTri = trang * SO_NV_MOI_TRANG_NHAP + i;
        string cot[5] = {"", "", "", "", ""};
        if (viTri < soLuong) {
            const NhanVien& nv = *ds[viTri];
            cot[0] = to_string(viTri + 1);
            cot[1] = nv.MANV;
            cot[2] = nv.ho;
            cot[3] = nv.ten;
            cot[4] = nv.phai;
        }
        gotoxy(bangX, 17 + i);
        // To mau xanh la (10) cho nhan vien vua moi them
        textcolor((viTri < soLuong && viTri == viTriVuaThem) ? 10 : 11);
        cout << DongBang(cot);
    }

    textcolor(14);
    gotoxy(bangX, 27);
    cout << vien;

    XoaDong(28);
    int soTrang = (soLuong == 0) ? 1 : (soLuong + SO_NV_MOI_TRANG_NHAP - 1) / SO_NV_MOI_TRANG_NHAP;
    string phanTrang = (soLuong == 0)
        ? "Chua co nhan vien trong danh sach"
        : ("Trang " + to_string(trang + 1) + " / " + to_string(soTrang) +
           " (PgUp/PgDn: chuyen trang)");
    gotoxy(KHUNG_NV_X + (KHUNG_NV_RONG - (int)phanTrang.length()) / 2, 28);
    textcolor(10);
    cout << phanTrang << flush;
    textcolor(11);
}

// Hien thi bang danh sach nhan vien toan man hinh (dung cho chuc nang 4 tren Menu)
void HienBangNhanVien(const NhanVien* const ds[], int soLuong, int trang) {
    VeKhungNhanVien("DANH SACH NHAN VIEN");
    gotoxy(KHUNG_NV_X + 3, 6);
    textcolor(10);
    if (soLuong == 0) cout << "Chua co nhan vien. Hay them nhan vien tu menu.";
    else cout << "Tong so: " << soLuong << " nhan vien | Sap xep theo ten, ho";

    const string tieuDe[5] = {"STT", "MA NV", "HO VA TEN DEM", "TEN", "PHAI"};
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
        string cot[5] = {"", "", "", "", ""};
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
    gotoxy(KHUNG_NV_X + (KHUNG_NV_RONG - (int)phanTrang.length()) / 2, 27);
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
    textcolor(6); // Mau vang toi de ve vien
    
    // Ve 4 duong ke ngang da duoc can chinh lai cuc ky an toan va khop y
    for (int i = 0; i <= WIDTH; i++) {
        gotoxy(OFFSET_X + i, OFFSET_Y);      cout << char(178); // Duong tren cung (Y=0)
        gotoxy(OFFSET_X + i, OFFSET_Y + 2);  cout << char(178); // Vach ngan Header (Y=2)
        gotoxy(OFFSET_X + i, OFFSET_Y + 24); cout << char(178); // Vach ngan Footer (Y=24)
        gotoxy(OFFSET_X + i, OFFSET_Y + 28); cout << char(178); // Duong duoi cung (Y=28) - An toan 100%
    }

    // Ve 2 cot doc o 2 ben
    for (int i = 0; i <= HEIGHT; i++) {
        gotoxy(OFFSET_X, OFFSET_Y + i);         cout << char(178); // Cot doc trai
        gotoxy(OFFSET_X + WIDTH, OFFSET_Y + i); cout << char(178); // Cot doc phai
    }
    
    // Dua con tro ve goc trai tren cung (0,0) de khoa man hinh, chong truot
    gotoxy(0, 0); 
}

// Ham 5: In cac dong chu co dinh 
void printStaticText() {
    textcolor(14); // Mau vang sang
    
    // In Header o giua vung chong tren cung (Y=1)
    gotoxy(OFFSET_X + 13, OFFSET_Y + 1); 
    cout << "HOC VIEN CONG NGHE BUU CHINH VIEN THONG CO SO THANH PHO HO CHI MINH";

    // In thong tin cua 3 thanh vien o cac toa do 25, 26, 27 
    // Tat ca deu nho hon 28 nen hoan toan khong bao gio bi de len vien nua
    gotoxy(OFFSET_X + 15, OFFSET_Y + 25); 
    cout << ">> Bui Vu Nguyen Khoa -------- N25DECE097  -------- E25CQCE03-N <<";

    gotoxy(OFFSET_X + 15, OFFSET_Y + 26); 
    cout << ">> Ngo Minh Tien      -------- N25DECE121  -------- E25CQCE03-N <<";

    gotoxy(OFFSET_X + 15, OFFSET_Y + 27); 
    cout << ">> Tran Trung Nguyen  -------- N25DECE105  -------- E25CQCE03-N <<";
    
    gotoxy(0, 0); // Khoa con tro chong cuon
}

// Ham 6: In danh sach 10 chuc nang va to mau (highlight)
void printMenuItems(int selectedIndex) {
    // Bat dau in tu Y = 4. 
    // Vach ngan la Y = 2, nen Y = 3 se tu dong tro thanh KHOANG TRONG (PADDING) phia tren.
    int startY = OFFSET_Y + 4; 

    for (int i = 0; i < NUM_ITEMS; i++) {
        // Moi chuc nang cach nhau 2 dong (i * 2). 
        // Muc so 9 se o Y = 22. Vach ngan duoi la Y = 24. -> Y = 23 tu dong thanh KHOANG TRONG phia duoi.
        gotoxy(OFFSET_X + 10, startY + (i * 2)); 

        if (i == selectedIndex) {
            textcolor(31); // To nen xanh duong, chu trang
            cout << menuItems[i]; 
        } else {
            textcolor(14); // Tra lai mau vang binh thuong
            cout << menuItems[i]; 
        }
    }
    textcolor(14); // Reset mau ve mac dinh
    gotoxy(0, 0);  // Khoa con tro chong cuon
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
