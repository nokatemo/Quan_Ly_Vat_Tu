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
        if (isdigit(static_cast<unsigned char>(c))) return true;
    }
    return false;
}


// =========================================================
// PHAN 2: CAC HAM NHAP LIEU CHUAN HOA TRUC TIEP KHI GO (LIVE)
// =========================================================

string NhapMaID(size_t maxlen, bool* daHuy) {
    if (daHuy != nullptr) *daHuy = false;
    string result; 
    while (true) {
        int c = _getch(); 

        if (c == 27 && daHuy != nullptr) {
            *daHuy = true;
            cout << "\n";
            return "";
        }
        
        // 1. Bo qua phim dieu huong (Mui ten, F1-F12...)
        if (c == 0 || c == 224) { _getch(); continue; } 
        
        // 2. Xu ly Enter
        if (c == 13) { 
            if (!result.empty()) { // ID khong duoc bo trong
                cout << "\n";
                break;
            }
            continue;
        }
        
        // 3. Xu ly phim Backspace (Xoa)
        if (c == 8) { 
            if (!result.empty()) {
                result.pop_back(); // Xoa ky tu cuoi trong chuoi
                cout << "\b \b" << flush; // Xoa ky tu tren man hinh console
            }
            continue;
        }
        
        // 4. Chi cho phep nhap chu cai va chu so (Chan khoang trang, ky tu dac biet)
        if (!isalnum(static_cast<unsigned char>(c))) continue;
        
        // 5. Kiem tra do dai toi da
        if (result.size() >= maxlen) continue;
        
        // 6. Chuyen chu thuong thanh chu IN HOA ngay khi go va hien thi ra console
        char upper = static_cast<char>(toupper(static_cast<unsigned char>(c)));
        result += upper;
        cout << upper << flush;	
    } 	
    return result;
}

string nhapChuoiChuanHoa(size_t maxlen, bool* daHuy) {
    if (daHuy != nullptr) *daHuy = false;
    string result;
    while (true) {
        int c = _getch();
        if (c == 27 && daHuy != nullptr) {
            *daHuy = true;
            cout << "\n";
            return "";
        }
        if (c == 0 || c == 224) { _getch(); continue; } 
        
        // 1. Xu ly Enter
        if (c == 13) { 
            // Neu nguoi dung lo go khoang trang o cuoi -> Tu dong g?t bo truoc khi xong
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
        
        // 2. Xu ly Backspace
        if (c == 8) { 
            if (!result.empty()) {
                result.pop_back();
                cout << "\b \b" << flush;
            }
            continue;
        }
        
        // 3. Chi cho phep chu cai va khoang trang
        if (isalpha(static_cast<unsigned char>(c)) || c == ' ') {
            if (result.size() >= maxlen) continue;
            
            if (c == ' ') {
                // Chan khoang trang o dau va 2 khoang trang lien tiep
                if (result.empty() || result.back() == ' ') continue;
                result += ' ';
                cout << ' ' << flush;
            } else {
                char kytu;
                // Chu cai dau tien cua tu -> Viet hoa
                if (result.empty() || result.back() == ' ') {
                    kytu = static_cast<char>(toupper(static_cast<unsigned char>(c)));
                } else {
                    // Cac chu cai con lai -> Viet thuong
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
        
        // Cho phep chu cai, so va khoang trang (VD: "Xi Mang PC 40")
        if (isalnum(static_cast<unsigned char>(c)) || c == ' ') {
            if (result.size() >= maxlen) continue;
            
            if (c == ' ') {
                if (result.empty() || result.back() == ' ') continue;
                result += ' ';
                cout << ' ' << flush;
            } else {
                char kytu = static_cast<char>(c);
                // Chi in hoa/thuong ky tu chu cai, giu nguyen ky tu so
                if (isalpha(static_cast<unsigned char>(c))) {
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
                int n = stoi(s); // Ep chuoi sang so nguyen
                cout << "\n";
                return n;
            } catch (const out_of_range&) {
                cout << "\nLoi: So vuot qua kha nang luu tru! Nhap lai: " << flush;
                s.clear();
            }
            continue;
        }
        
        // Chi nhan ky tu so 0-9 (Chan dau '-' va ky tu chu)
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
                double n = stod(s); // Ep chuoi sang so thuc
                cout << "\n";
                return n;
            } catch (const out_of_range&) {
                cout << "\nLoi: So vuot qua kha nang luu tru! Nhap lai: " << flush;
                s.clear();
            }
            continue;
        }
        
        // Chi nhan ky tu so 0-9 va 1 dau cham (.). Chan dau '-' va nhieu dau cham
        if ((c >= '0' && c <= '9') || (c == '.' && s.find('.') == string::npos)) {
            char kytu = static_cast<char>(c);
            s += kytu;
            cout << kytu << flush; 
        }	 
    }
}
