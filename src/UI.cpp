#include "UI.h"
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
    system("mode con cols=120 lines=35"); // Setup khung nhin mac dinh cho console
    
    ShowConsoleCursor(false); // Giau con tro chuot di
    system("cls");            // Xoa sach man hinh 
    
    // Ve khung va in chu 1 lan duy nhat 
    drawFrame();
    printStaticText();
    
    int selectedIndex = 0; // Vi tri dang chon (Bat dau la muc 1)
    bool isRunning = true; 

    while (isRunning) {
        printMenuItems(selectedIndex); // Cap nhat mau menu lien tuc

        char key = _getch(); // Cho bam 1 phim bat ky
        
        // Bat su kien khi bam mui ten len/xuong
        if (key == -32 || key == 224) { 
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
            
            // DAY CHINH LA NOI BO CODE CHUC NANG DO AN VAO 
            switch (selectedIndex) {
                case 0:
                    // Code Quan li vat tu
                    break;
                case 1:
                    // Code Danh sach vat tu
                    break;
                case 2:
                    break;
                case 3:
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
                cout << "\nNhan phim bat ky de quay lai menu...";
                _getch(); 
                
                // Khoi phuc lai giao dien bang menu
                ShowConsoleCursor(false); 
                system("cls");            
                drawFrame();              
                printStaticText();        
            }
        }
    }
}
