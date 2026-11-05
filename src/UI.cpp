#include "UI.h"
#include <conio.h> 

using namespace std;

// ==========================================================
// PHAN 1: CAI DAT THONG SO TOA DO VA KICH THUOC BANG
// ==========================================================

const int OFFSET_X = 15;  // Day bang sang phai de ra giua man hinh
const int OFFSET_Y = 0;   // Keo sat mep tren cung man hinh
const int WIDTH = 95;     // Do rong cua bang
const int HEIGHT = 28;    // Chieu cao an toan chong cuon (scroll) man hinh

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

// Ham 1: Di chuyen con tro den toa do (x, y)
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Ham 2: To mau chu va nen
void textcolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Ham 3: An hoac hien con tro chuot nhap nhay
void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; 
    SetConsoleCursorInfo(out, &cursorInfo);
}

// ==========================================================
// PHAN 3: CAC HAM VE KHUNG VA IN CHU CO DINH
// ==========================================================

// Ham 4: Ve khung vien cho menu
void drawFrame() {
    textcolor(6); // Mau vang toi de ve vien
    
    for (int i = 0; i <= WIDTH; i++) {
        gotoxy(OFFSET_X + i, OFFSET_Y);      cout << char(178); // Duong tren (Y=0)
        gotoxy(OFFSET_X + i, OFFSET_Y + 2);  cout << char(178); // Vach ngan Header (Y=2)
        gotoxy(OFFSET_X + i, OFFSET_Y + 24); cout << char(178); // Vach ngan Footer (Y=24)
        gotoxy(OFFSET_X + i, OFFSET_Y + 28); cout << char(178); // Duong duoi (Y=28)
    }

    for (int i = 0; i <= HEIGHT; i++) {
        gotoxy(OFFSET_X, OFFSET_Y + i);         cout << char(178); // Cot trai
        gotoxy(OFFSET_X + WIDTH, OFFSET_Y + i); cout << char(178); // Cot phai
    }
    
    gotoxy(0, 0); // Khoa con tro chong truot
}

// Ham 5: In thong tin co dinh
void printStaticText() {
    textcolor(14); // Mau vang sang
    
    gotoxy(OFFSET_X + 13, OFFSET_Y + 1); 
    cout << "HOC VIEN CONG NGHE BUU CHINH VIEN THONG PHAN HIEU THANH PHO HO CHI MINH";

    gotoxy(OFFSET_X + 15, OFFSET_Y + 25); 
    cout << ">> Bui Vu Nguyen Khoa -------- N25DECE097  -------- E25CQCE03-N <<";

    gotoxy(OFFSET_X + 15, OFFSET_Y + 26); 
    cout << ">> Ngo Minh Tien      -------- N25DECE121  -------- E25CQCE03-N <<";

    gotoxy(OFFSET_X + 15, OFFSET_Y + 27); 
    cout << ">> Tran Trung Nguyen  -------- N25DECE105  -------- E25CQCE03-N <<";
    
    gotoxy(0, 0); 
}

// Ham 6: In 10 muc menu va to mau (highlight) muc dang chon
void printMenuItems(int selectedIndex) {
    int startY = OFFSET_Y + 4; 

    for (int i = 0; i < NUM_ITEMS; i++) {
        gotoxy(OFFSET_X + 10, startY + (i * 2)); 

        if (i == selectedIndex) {
            textcolor(31); // To nen xanh duong, chu trang
            cout << menuItems[i]; 
        } else {
            textcolor(14); // Mau vang binh thuong
            cout << menuItems[i]; 
        }
    }
    textcolor(14); 
    gotoxy(0, 0);  
}

// ==========================================================
// PHAN 4: BO NAO TRUNG TAM DIEU KHIEN MENU & SWITCH CASE
// ==========================================================

void menuController(DanhSachNhanVien &dsNV, TreeVatTu &root) {
    system("mode con cols=120 lines=35");
    
    ShowConsoleCursor(false); // Giau con tro chuot
    system("cls");            
    
    drawFrame();
    printStaticText();
    
    int selectedIndex = 0; 
    bool isRunning = true; 

    while (isRunning) {
        printMenuItems(selectedIndex); 

        char key = _getch(); 
        
        if (key == -32 || key == 224) { 
            key = _getch(); 
            
            if (key == 72) { // Mui ten Len
                selectedIndex--; 
                if (selectedIndex < 0) selectedIndex = NUM_ITEMS - 1; 
            } else if (key == 80) { // Mui ten Xuong
                selectedIndex++; 
                if (selectedIndex >= NUM_ITEMS) selectedIndex = 0; 
            }
        } 
        else if (key == 13) { // Phim Enter
            system("cls");           
            ShowConsoleCursor(true); // Hien con tro chuot khi vao man hinh nhap lieu
            
            switch (selectedIndex) {
                case 0:
                    // Cap nhat vat tu (Tien)
                    break;
                case 1:
                    // In danh sach vat tu ton kho (Tien)
                    break;
                case 2:
                    // Cap nhat nhan vien (Khoa)
                    break;
                case 3:
                    // In danh sach nhan vien (Khoa)
                    break;
                case 4: // 5. Lap Hoa Don Nhap / Xuat (Cau E)
                    LapHoaDon(dsNV, root);
                    break;
                case 5: // 6. In Chi Tiet 1 Hoa Don (Cau F)
                    InHoaDon(dsNV, root);
                    break;
                case 6:
                    // Thong ke hoa don theo thoi gian (Cau G)
                    break;
                case 7:
                    // Top 10 vat tu doanh thu cao nhat (Cau I)
                    break;
                case 8:
                    // Thong ke doanh thu theo thang (Cau H)
                    break;
                case 9: // 0. Thoat
                    cout << "Chuong trinh ket thuc!\n";
                    isRunning = false;
                    break;
            }
            
            if (isRunning) {
                cout << "\nNhan phim bat ky de quay lai menu...";
                _getch(); 
                
                ShowConsoleCursor(false); 
                system("cls");            
                drawFrame();              
                printStaticText();        
            }
        }
    }
}
