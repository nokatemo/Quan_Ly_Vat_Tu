#include "UI.h"
#include <conio.h> 

using namespace std;

const int OFFSET_X = 15;
const int OFFSET_Y = 0;
const int WIDTH = 95;
const int HEIGHT = 28;

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

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
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

void drawBox(int x, int y, int w, int h, int color) {
    textcolor(color);
    for (int i = 0; i <= w; i++) {
        gotoxy(x + i, y);     cout << char(178);
        gotoxy(x + i, y + h); cout << char(178);
    }
    for (int i = 0; i <= h; i++) {
        gotoxy(x, y + i);     cout << char(178);
        gotoxy(x + w, y + i); cout << char(178);
    }
}

void clearLine(int x, int y, int length) {
    gotoxy(x, y);
    for (int i = 0; i < length; i++) cout << " ";
    gotoxy(x, y);
}

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

void printStaticText() {
    textcolor(14);
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

void printMenuItems(int selectedIndex) {
    int startY = OFFSET_Y + 4; 
    for (int i = 0; i < NUM_ITEMS; i++) {
        gotoxy(OFFSET_X + 10, startY + (i * 2)); 
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

// Giao dien hop thoai tam biet khi thoat chuong trinh (Hien thi trong 10 giay)
void GiaoDienThoatChuongTrinh() {
    system("cls");
    int boxX = 22, boxY = 5, boxW = 60, boxH = 12;
    drawBox(boxX, boxY, boxW, boxH, 14); // Ve khung mau vang sang trong

    // Tieu de chinh can giua trong khung
    textcolor(11); // Mau Cyan
    gotoxy(boxX + 18, boxY + 2);
    cout << "THONG BAO HE THONG";

    // Duong ke ngang trang tri
    textcolor(14);
    gotoxy(boxX + 4, boxY + 3);
    for (int i = 0; i < boxW - 7; i++) cout << "~";

    // Loi chao va cam on duoc can le chinh chu
    textcolor(10); // Mau xanh la noi bat
    gotoxy(boxX + 11, boxY + 5);
    cout << "CAM ON BAN DA SU DUNG HE THONG!";
    
    textcolor(11); // Mau Cyan diu mat
    gotoxy(boxX + 15, boxY + 7);
    cout << "CHUC BAN MOT NGAY TOT LAM!";

    // Hieu ung thong bao tien trinh
    textcolor(14); // Mau vang
    gotoxy(boxX + 12, boxY + 9);
    cout << "Dang dong ung dung va luu du lieu";
    
    // Vong lap chay dau cham loading (chay trong khoang 2 giay dau)
    for (int i = 0; i < 4; i++) {
        Sleep(500); // Dung 0.5 giay moi cham (tong 2 giay)
        cout << ".";
    }

    // Hien thi them thong bao hoan tat va dung them 8 giay nua (Tong cong dung tron 10 giay)
    textcolor(10);
    gotoxy(boxX + 17, boxY + 10);
    cout << "HOAN TAT! HEN GAP LAI.";
    
    Sleep(3000); // Dung tiep 8 giay

    system("cls");
    exit(0); // Thoat han chuong trinh an toan
}

void menuController(DanhSachNhanVien &dsNV, TreeVatTu &root) {
    system("mode con cols=120 lines=35");
    ShowConsoleCursor(false);
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
            if (key == 72) { 
                selectedIndex--; 
                if (selectedIndex < 0) selectedIndex = NUM_ITEMS - 1; 
            } else if (key == 80) { 
                selectedIndex++; 
                if (selectedIndex >= NUM_ITEMS) selectedIndex = 0; 
            }
        } 
        else if (key == 13) { 
            system("cls");           
            ShowConsoleCursor(true); 
            
            switch (selectedIndex) {
                case 0: break;
                case 1: break;
                case 2: break;
                case 3: break;
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
