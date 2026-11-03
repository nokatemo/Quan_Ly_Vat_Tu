#include "Validate.h"
#include <iostream> 
#include <string>
#include <cctype>    
#include <conio.h>   
#include <stdexcept> 

using namespace std;

// =========================================================
// PHAN 1: CAC HAM KIEM TRA LOGIC
// =========================================================

bool chuoirong(const string& str) {
    for (char c : str) {
        if (c != ' ') return false; // Co chua ky tu khac khoang trang
    }
    return true; // Chuoi hoan toan rong
}

bool namnhuan(int nam) {
    // Nam nhuan la nam chia het cho 400, hoac chia het cho 4 nhung khong chia het cho 100
    return (nam % 400 == 0) || (nam % 4 == 0 && nam % 100 != 0);
}

int kiemtrangay(int thang, int nam) {
    switch (thang) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
            return 31;
        case 4: case 6: case 9: case 11: 
            return 30;
        case 2: 
            return namnhuan(nam) ? 29 : 28;
        default: 
            return 0; // Thang nhap vao bi sai
    }
}

bool ngayhople(int ngay, int thang, int nam) {
    if (nam < 1900) return false;
    if (thang < 1 || thang > 12) return false;
    if (ngay < 1 || ngay > kiemtrangay(thang, nam)) return false;
    return true;
}

int sosanhngay(int d1, int m1, int y1, int d2, int m2, int y2) {
    if (y1 > y2) return 1;
    if (y1 < y2) return -1;
    
    if (m1 > m2) return 1;
    if (m1 < m2) return -1;
    
    if (d1 > d2) return 1;
    if (d1 < d2) return -1;
    
    return 0; // Bang nhau
}

bool conso(const string& ten) {
    for (char c : ten) {
        if (isdigit(c)) return true;
    }
    return false;
}


// =========================================================
// PHAN 2: CAC HAM NHAP LIEU CHUAN HOA TRUC TIEP (LIVE)
// 
// Bang ma ASCII can nho cho _getch():
// - 13     : Phim Enter
// - 8      : Phim Backspace (Xoa)
// - 0, 224 : Phim dieu huong (Mui ten, F1-F12...)
// =========================================================

string NhapMaID(size_t maxlen) {
    string result; 
    while (true) {
        int c = _getch(); 
        
        // 1. Bo qua phim dieu huong, _getch() lan 2 de nuot phim ranh
        if (c == 0 || c == 224) { _getch(); continue; } 
        
        // 2. Xu ly Enter
        if (c == 13) { 
            if (!result.empty()) { // ID khong duoc bo trong
                cout << "\n";
                break;
            }
            continue;
        }
        
        // 3. Xu ly xoa (Backspace)
        if (c == 8) { 
            if (!result.empty()) {
                result.pop_back(); // Xoa trong bien
                cout << "\b \b" << flush; // Xoa tren man hinh hien thi
            }
            continue;
        }
        
        // 4. Chi cho phep nhap chu cai va so (Chan ky tu dac biet, khoang trang)
        if (!isalnum(c)) continue;
        
        // 5. Kiem tra kich thuoc toi da
        if (result.size() >= maxlen) continue;
        
        // 6. Chuyen chu thuong thanh chu In Hoa
        char upper = static_cast<char>(toupper(static_cast<unsigned char>(c)));
        result += upper;
        cout << upper << flush;	
    } 	
    return result;
}

string nhapChuoiChuanHoa(size_t maxlen) {
    string result;
    while (true) {
        int c = _getch();
        if (c == 0 || c == 224) { _getch(); continue; } 
        
        if (c == 13) { 
            // Neu user lo go 1 khoang trang o cuoi roi an Enter -> Tu dong xoa
            if (!result.empty() && result.back() == ' ') {
                result.pop_back(); 
                cout << "\b \b" << flush;
            }
            if (!result.empty()) { // Bat buoc phai co du lieu
                cout << "\n";
                break;
            }
            continue;
        }
        
        if (c == 8) { 
            if (!result.empty()) {
                result.pop_back();
                cout << "\b \b" << flush;
            }
            continue;
        }
        
        // 4. CHI CHO PHEP CHU CAI VA KHOANG TRANG (a-z, A-Z, space)
        if (isalpha(c) || c == ' ') {
            if (result.size() >= maxlen) continue;
            
            if (c == ' ') {
                // Chan khoang trang o dau hoac 2 khoang trang dinh vao nhau
                if (result.empty() || result.back() == ' ') continue;
                result += ' ';
                cout << ' ' << flush;
            } else {
                char kytu;
                // Chu cai dau tien cua moi tu se tu dong viet hoa
                if (result.empty() || result.back() == ' ') {
                    kytu = static_cast<char>(toupper(static_cast<unsigned char>(c)));
                } else {
                    // Nhung chu cai con lai tu dong viet thuong
                    kytu = static_cast<char>(tolower(static_cast<unsigned char>(c)));
                }
                result += kytu;
                cout << kytu << flush;
            }
        }
    }
    return result;
}

string nhapTenVatTuChuanHoa(size_t maxlen) {
    string result;
    while (true) {
        int c = _getch();
        if (c == 0 || c == 224) { _getch(); continue; } 
        
        if (c == 13) { 
            if (!result.empty() && result.back() == ' ') {
                result.pop_back(); 
                cout << "\b \b" << flush;
            }
            if (!result.empty()) { 
                cout << "\n";
                break;
            }
            continue;
        }
        
        if (c == 8) { 
            if (!result.empty()) {
                result.pop_back();
                cout << "\b \b" << flush;
            }
            continue;
        }
        
        // 4. CHO PHEP CHU CAI, SO VA KHOANG TRANG (VD: "Gach Ong 4 Lo")
        if (isalnum(c) || c == ' ') {
            if (result.size() >= maxlen) continue;
            
            if (c == ' ') {
                if (result.empty() || result.back() == ' ') continue;
                result += ' ';
                cout << ' ' << flush;
            } else {
                char kytu = static_cast<char>(c);
                // Giong nhapChuoiChuanHoa, chi format chu cai, khong the format so
                if (isalpha(c)) {
                    if (result.empty() || result.back() == ' ') {
                        kytu = static_cast<char>(toupper(static_cast<unsigned char>(c)));
                    } else {
                        kytu = static_cast<char>(tolower(static_cast<unsigned char>(c)));
                    }
                }
                result += kytu;
                cout << kytu << flush;
            }
        }
    }
    return result;
}

int nhapsonguyen() {
    string s;
    while (true) {
        int c = _getch();
        if (c == 0 || c == 224) { _getch(); continue; }
        
        if (c == 8) {
            if (!s.empty()) {
                s.pop_back();
                cout << "\b \b" << flush;
            }
            continue;
        }
        
        if (c == 13) {
            if (s.empty()) continue;
            try {
                int n = stoi(s); // Ep chuoi sang nguyen
                cout << "\n";
                return n;
            } catch (const out_of_range&) {
                cout << "\nLoi: So vuot qua kha nang luu tru! Nhap lai: " << flush;
                s.clear();
            }
            continue;
        }
        
        // CHI NHAN SO 0-9. Chan luon dau am (-) de buoc nguoi dung nhap so nguyen DUONG
        if (c >= '0' && c <= '9') {
            char kytu = static_cast<char>(c);
            s += kytu;
            cout << kytu << flush; 
        }
    }
}

double nhapsothuc() {
    string s;
    while (true) {
        char c = _getch();
        if (c == 0 || c == 224) { _getch(); continue; }
        
        if (c == 8) {
            if (!s.empty()) {
                s.pop_back();
                cout << "\b \b" << flush;
            }
            continue;
        }
        
        if (c == 13) {
            if (s.empty()) continue;
            try {
                double n = stod(s); // Ep chuoi sang thuc
                cout << "\n";
                return n;
            } catch (const out_of_range&) {
                cout << "\nLoi: So vuot qua kha nang luu tru! Nhap lai: " << flush;
                s.clear();
            }
            continue;
        }
        
        // CHI NHAN SO 0-9 VA 1 DAU CHAM(.). Chan nhap so am va nhieu dau cham cung luc
        if ((c >= '0' && c <= '9') || (c == '.' && s.find('.') == string::npos)) {
            char kytu = static_cast<char>(c);
            s += kytu;
            cout << kytu << flush; 
        }	 
    }
}
