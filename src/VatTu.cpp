#include "VatTu.h"
#include "UI.h"
#include "Validate.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// ==========================================================
// 0. HÀM BỔ TRỢ CHUẨN HÓA & HIỂN THỊ (CHỐNG VỠ KHUNG & GIẬT MÀN HÌNH)
// ==========================================================

// Cắt ngắn chuỗi nếu dài quá giới hạn cho phép của cột và thêm dấu ...
string formatColString(string str, size_t maxLen) {
    if (str.length() > maxLen) {
        return str.substr(0, maxLen - 3) + "...";
    }
    return str;
}

// Chuyển chuỗi về dạng chữ thường để tìm kiếm không phân biệt hoa thường
string toLowerStr(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

// Hàm xóa riêng khu vực bảng dữ liệu để in lại (giúp màn hình không bị nhấp nháy/giật)
void clearDataArea(int startX, int startY, int rowCount, int colWidth) {
    string emptyLine(colWidth, ' ');
    for (int i = 0; i < rowCount; i++) {
        gotoxy(startX, startY + i);
        cout << emptyLine;
    }
}

// ==========================================================
// 1. CÁC THAO TÁC CƠ BẢN TRÊN CÂY BST
// ==========================================================

void initTreeVatTu(TreeVatTu &t) {
    t = nullptr;
}

NodeVatTu* searchVatTu(TreeVatTu t, string maVT) {
    if (t == nullptr || t->data.MAVT == maVT) return t;
    if (maVT < t->data.MAVT) return searchVatTu(t->left, maVT);
    return searchVatTu(t->right, maVT);
}

bool insertVatTu(TreeVatTu &t, VatTu vt) {
    if (t == nullptr) {
        NodeVatTu* p = new NodeVatTu;
        p->data = vt;
        p->left = nullptr;
        p->right = nullptr;
        t = p;
        return true;
    }
    if (vt.MAVT == t->data.MAVT) return false;
    if (vt.MAVT < t->data.MAVT) return insertVatTu(t->left, vt);
    return insertVatTu(t->right, vt);
}

void nodeTheMang(TreeVatTu &X, TreeVatTu &Y) {
    if (Y->left != nullptr) {
        nodeTheMang(X, Y->left);
    } else {
        X->data = Y->data;
        X = Y;
        Y = Y->right;
    }
}

bool deleteVatTu(TreeVatTu &t, string maVT) {
    if (t == nullptr) return false;

    if (maVT < t->data.MAVT) {
        return deleteVatTu(t->left, maVT);
    } else if (maVT > t->data.MAVT) {
        return deleteVatTu(t->right, maVT);
    } else {
        NodeVatTu* nodeXoa = t;
        if (t->left == nullptr) {
            t = t->right;
        } else if (t->right == nullptr) {
            t = t->left;
        } else {
            nodeTheMang(nodeXoa, t->right);
        }
        delete nodeXoa;
        return true;
    }
}

void freeTreeVatTu(TreeVatTu &t) {
    if (t != nullptr) {
        freeTreeVatTu(t->left);
        freeTreeVatTu(t->right);
        delete t;
        t = nullptr;
    }
}

// ==========================================================
// 2. CÁC HÀM CẦU NỐI THEO CHUẨN ĐỀ XUẤT
// ==========================================================

bool CapNhatTonKho(TreeVatTu &root, string maVT, int soLuongThayDoi) {
    NodeVatTu* node = searchVatTu(root, maVT);
    if (node == nullptr) return false; 

    node->data.soLuongTon += soLuongThayDoi;
    return true; 
}

int getSoLuongTon(TreeVatTu t, string maVT) {
    NodeVatTu* node = searchVatTu(t, maVT);
    return (node != nullptr) ? node->data.soLuongTon : -1;
}

string getTenVatTu(TreeVatTu t, string maVT) {
    NodeVatTu* node = searchVatTu(t, maVT);
    return (node != nullptr) ? node->data.tenVatTu : "Khong tim thay";
}

// ==========================================================
// 3. CHỨC NĂNG A: CẬP NHẬT VẬT TƯ (THÊM / XÓA / HIỆU CHỈNH INTERACTIVE)
// ==========================================================

void quanLyVatTu(TreeVatTu &t) {
    system("cls");
    drawFrame();

    gotoxy(OFFSET_X + 32, OFFSET_Y + 1);
    textcolor(14);
    cout << "=== CAP NHAT THONG TIN VAT TU ===";

    gotoxy(OFFSET_X + 10, OFFSET_Y + 5);  cout << "1. Them Vat Tu Moi";
    gotoxy(OFFSET_X + 10, OFFSET_Y + 7);  cout << "2. Xoa Vat Tu";
    gotoxy(OFFSET_X + 10, OFFSET_Y + 9);  cout << "3. Hieu Chinh Thong Tin Vat Tu";
    gotoxy(OFFSET_X + 10, OFFSET_Y + 11); cout << "0. Quay lai Menu Chinh";

    gotoxy(OFFSET_X + 10, OFFSET_Y + 14);
    cout << "Nhap lua chon [0-3]: ";
    int luaChon = nhapsonguyen();

    if (luaChon == 0) {
        return;
    }
    else if (luaChon == 1) { // THÊM VẬT TƯ MỚI
        VatTu vt;
        gotoxy(OFFSET_X + 10, OFFSET_Y + 16);
        cout << "Nhap Ma VT (toi da 10 ky tu): ";
        vt.MAVT = NhapMaID(10);

        if (searchVatTu(t, vt.MAVT) != nullptr) {
            gotoxy(OFFSET_X + 10, OFFSET_Y + 18);
            textcolor(12); cout << "Loi: Ma vat tu da ton tai!";
            _getch(); return;
        }

        gotoxy(OFFSET_X + 10, OFFSET_Y + 17);
        cout << "Nhap Ten Vat Tu: ";
        vt.tenVatTu = nhapTenVatTuChuanHoa(35);

        gotoxy(OFFSET_X + 10, OFFSET_Y + 18);
        cout << "Nhap Don Vi Tinh: ";
        vt.donViTinh = nhapChuoiChuanHoa(15);

        gotoxy(OFFSET_X + 10, OFFSET_Y + 19);
        cout << "Nhap So Luong Ton Ban Dau: ";
        vt.soLuongTon = nhapsonguyen();

        if (insertVatTu(t, vt)) {
            gotoxy(OFFSET_X + 10, OFFSET_Y + 21);
            textcolor(10); cout << "=> Them vat tu thanh cong!";
        }
        _getch();
    } 
    else if (luaChon == 2) { // XÓA VẬT TƯ
        gotoxy(OFFSET_X + 10, OFFSET_Y + 16);
        cout << "Nhap Ma VT can xoa: ";
        string maVT = NhapMaID(10);

        if (deleteVatTu(t, maVT)) {
            gotoxy(OFFSET_X + 10, OFFSET_Y + 18);
            textcolor(10); cout << "=> Xoa vat tu thanh cong!";
        } else {
            gotoxy(OFFSET_X + 10, OFFSET_Y + 18);
            textcolor(12); cout << "Loi: Khong tim thay ma vat tu!";
        }
        _getch();
    } 
    else if (luaChon == 3) { // HIỆU CHỈNH VẬT TƯ
        gotoxy(OFFSET_X + 10, OFFSET_Y + 16);
        cout << "Nhap Ma VT can hieu chinh: ";
        string maVT = NhapMaID(10);

        NodeVatTu* node = searchVatTu(t, maVT);
        if (node == nullptr) {
            gotoxy(OFFSET_X + 10, OFFSET_Y + 18);
            textcolor(12); cout << "Loi: Khong tim thay ma vat tu!";
            _getch();
            return;
        }

        system("cls");
        drawFrame();
        gotoxy(OFFSET_X + 30, OFFSET_Y + 1);
        textcolor(14);
        cout << "=== HIEU CHINH CHITIET VAT TU ===";

        int selectedOption = 0;
        bool isEditing = true;

        while (isEditing) {
            gotoxy(OFFSET_X + 10, OFFSET_Y + 5);
            textcolor(14); cout << "Ma Vat Tu (Khoa): " << node->data.MAVT;

            gotoxy(OFFSET_X + 10, OFFSET_Y + 8);
            if (selectedOption == 0) textcolor(31); else textcolor(14);
            cout << "1. Ten Vat Tu : " << node->data.tenVatTu;
            for (int i = 0; i < 20; i++) cout << " ";

            gotoxy(OFFSET_X + 10, OFFSET_Y + 10);
            if (selectedOption == 1) textcolor(31); else textcolor(14);
            cout << "2. Don Vi Tinh: " << node->data.donViTinh;
            for (int i = 0; i < 20; i++) cout << " ";

            gotoxy(OFFSET_X + 10, OFFSET_Y + 12);
            textcolor(8);
            cout << "3. So Luong Ton: " << node->data.soLuongTon << " (Khong duoc phep sua)";

            gotoxy(OFFSET_X + 10, OFFSET_Y + 15);
            if (selectedOption == 2) textcolor(31); else textcolor(14);
            cout << "[ LUU & HOAN THANH ]";

            gotoxy(OFFSET_X + 10, OFFSET_Y + 19);
            textcolor(11);
            cout << "Dung mui ten UP/DOWN de di chuyen | Enter de sua | Esc de huy";

            char key = _getch();
            if (key == -32 || key == 224) {
                key = _getch();
                if (key == 72) {
                    selectedOption--;
                    if (selectedOption < 0) selectedOption = 2;
                } else if (key == 80) {
                    selectedOption++;
                    if (selectedOption > 2) selectedOption = 0;
                }
            } 
            else if (key == 13) {
                ShowConsoleCursor(true);
                if (selectedOption == 0) {
                    gotoxy(OFFSET_X + 10, OFFSET_Y + 21);
                    textcolor(14); cout << "Nhap Ten VT moi: ";
                    string tenMoi = nhapTenVatTuChuanHoa(35);
                    if (!tenMoi.empty()) node->data.tenVatTu = tenMoi;
                    gotoxy(OFFSET_X + 10, OFFSET_Y + 21); cout << string(60, ' ');
                } 
                else if (selectedOption == 1) {
                    gotoxy(OFFSET_X + 10, OFFSET_Y + 21);
                    textcolor(14); cout << "Nhap DVT moi: ";
                    string dvtMoi = nhapChuoiChuanHoa(15);
                    if (!dvtMoi.empty()) node->data.donViTinh = dvtMoi;
                    gotoxy(OFFSET_X + 10, OFFSET_Y + 21); cout << string(60, ' ');
                } 
                else if (selectedOption == 2) {
                    isEditing = false;
                }
                ShowConsoleCursor(false);
            } 
            else if (key == 27) {
                isEditing = false;
            }
        }

        gotoxy(OFFSET_X + 10, OFFSET_Y + 21);
        textcolor(10); cout << "=> Cap nhat thong tin thanh cong!";
        _getch();
    }

    textcolor(14);
}

// ==========================================================
// 4. CHỨC NĂNG B: IN DS VẬT TƯ (TÌM KIẾM REAL-TIME DECOR CAO CẤP)
// ==========================================================

void storeTreeToVector(TreeVatTu t, vector<VatTu> &list) {
    if (t != nullptr) {
        storeTreeToVector(t->left, list);
        list.push_back(t->data);
        storeTreeToVector(t->right, list);
    }
}

void inDSVatTuTheoTen(TreeVatTu t) {
    vector<VatTu> listAll;
    storeTreeToVector(t, listAll);

    if (listAll.empty()) {
        system("cls");
        drawFrame();
        gotoxy(OFFSET_X + 10, OFFSET_Y + 5);
        textcolor(12); cout << "Danh sach vat tu hien dang rong!";
        _getch(); return;
    }

    // Sắp xếp tăng dần theo tên vật tư
    sort(listAll.begin(), listAll.end(), [](const VatTu &a, const VatTu &b) {
        return a.tenVatTu < b.tenVatTu;
    });

    vector<VatTu> listCurrent = listAll;
    string keyword = "";

    int ITEMS_PER_PAGE = 14;
    int currentPage = 1;
    bool isSearchingMode = false;
    bool isRunning = true;

    // CHỈ VẼ KHUNG CỐ ĐỊNH 1 LẦN ĐẦU TIÊN
    system("cls");
    drawFrame();

    int posX = OFFSET_X + 3;
    int startY = OFFSET_Y + 4;

    // In tiêu đề các cột cố định
    gotoxy(posX, startY + 1);
    textcolor(14);
    cout << left << setw(15) << "Ma VT" 
         << setw(38) << "Ten Vat Tu" 
         << setw(14) << "Don Vi Tinh" 
         << right << setw(12) << "So Luong Ton";

    gotoxy(posX, startY + 2);
    cout << string(79, '-');

    while (isRunning) {
        // 1. Lọc dữ liệu theo từ khóa real-time
        listCurrent.clear();
        if (keyword.empty()) {
            listCurrent = listAll;
        } else {
            string kwLower = toLowerStr(keyword);
            for (const auto &vt : listAll) {
                if (toLowerStr(vt.MAVT).find(kwLower) != string::npos || 
                    toLowerStr(vt.tenVatTu).find(kwLower) != string::npos) {
                    listCurrent.push_back(vt);
                }
            }
        }

        // Tính toán số trang
        int totalItems = listCurrent.size();
        int totalPages = (totalItems == 0) ? 1 : (totalItems + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
        if (currentPage > totalPages) currentPage = totalPages;
        if (currentPage < 1) currentPage = 1;

        // 2. CẬP NHẬT HEADER & SỐ TRANG
        gotoxy(OFFSET_X + 18, OFFSET_Y + 1);
        textcolor(14);
        cout << "=== DANH SACH VAT TU TON KHO (Trang " << currentPage << "/" << totalPages << ") ===";
        cout << string(10, ' ');

        // 3. DECOR THANH SEARCH BAR NỔI BẬT NƠI DÒNG (startY - 1)
        gotoxy(posX, startY - 1);
        if (isSearchingMode) {
            textcolor(30); // Nền Vàng chữ Đen nổi bật khi gõ
            cout << " [ SEARCH ] ";
            textcolor(11);
            cout << " > ";
            textcolor(14);
            cout << keyword;
            textcolor(10); cout << "_"; // Con trỏ nhấp nháy
            textcolor(15);
            cout << string(25 - keyword.length(), ' ');
        } else {
            textcolor(11);
            cout << "[ TIM KIEM ]: ";
            if (keyword.empty()) {
                textcolor(8); // Màu xám chìm
                cout << "(Nhan [F] de tim kiem real-time...)         ";
            } else {
                textcolor(14);
                cout << "\"" << keyword << "\"                         ";
            }
        }

        // Hiển thị Badge số lượng quả tìm được ở góc phải
        gotoxy(posX + 61, startY - 1);
        textcolor(11);
        cout << "[ Tim thay: ";
        textcolor(14);
        cout << setw(3) << totalItems;
        textcolor(11);
        cout << " ]";

        // 4. IN DANH SÁCH BẢNG DỮ LIỆU
        clearDataArea(posX, startY + 3, ITEMS_PER_PAGE + 1, 79);

        int startIndex = (currentPage - 1) * ITEMS_PER_PAGE;
        int endIndex = min(startIndex + ITEMS_PER_PAGE, totalItems);
        int currentY = startY + 3;

        if (totalItems == 0) {
            gotoxy(posX + 20, currentY + 3);
            textcolor(12);
            cout << "-> Khong tim thay vat tu nao phu hop!";
        } else {
            for (int i = startIndex; i < endIndex; i++) {
                gotoxy(posX, currentY);
                textcolor(15);
                cout << left << setw(15) << listCurrent[i].MAVT 
                     << setw(38) << formatColString(listCurrent[i].tenVatTu, 35) 
                     << setw(14) << formatColString(listCurrent[i].donViTinh, 11) 
                     << right << setw(12) << listCurrent[i].soLuongTon;
                currentY++;
            }
        }

        // 5. FOOTER HƯỚNG DẪN THAO TÁC
        gotoxy(posX, OFFSET_Y + 23);
        if (isSearchingMode) {
            textcolor(14);
            cout << ">> Dang go tu khoa... | Enter: Hoan thanh | Esc: Huy tim kiem          ";
        } else {
            textcolor(11);
            cout << "<-/->: Trang Truoc/Sau | [F]: Tim Kiem | [R]: Reset | [ESC]: Thoat";
        }

        // 6. BẮT PHÍM THAO TÁC
        char key = _getch();

        if (isSearchingMode) {
            if (key == 13) { // Enter -> Kết thúc gõ
                isSearchingMode = false;
            } 
            else if (key == 27) { // Esc -> Hủy từ khóa
                keyword = "";
                isSearchingMode = false;
                currentPage = 1;
            } 
            else if (key == 8) { // Backspace -> Xóa ký tự
                if (!keyword.empty()) {
                    keyword.pop_back();
                    currentPage = 1;
                }
            } 
            else if (keyword.length() < 22 && (isalnum(key) || key == ' ')) {
                if (key == ' ' && keyword.empty()) continue;
                keyword += key;
                currentPage = 1;
            }
        } 
        else {
            if (key == -32 || key == 224) {
                key = _getch();
                if (key == 77 || key == 81) { // Mũi tên Phải / PageDown
                    if (currentPage < totalPages) currentPage++;
                } else if (key == 75 || key == 73) { // Mũi tên Trái / PageUp
                    if (currentPage > 1) currentPage--;
                }
            } 
            else if (key == 'f' || key == 'F') { // Bật chế độ gõ tìm kiếm
                isSearchingMode = true;
            } 
            else if (key == 'r' || key == 'R') { // Reset tìm kiếm
                keyword = "";
                currentPage = 1;
            } 
            else if (key == 27) { // Escape -> Thoát
                isRunning = false;
            }
        }
    }
}

// ==========================================================
// 5. ĐỌC / GHI FILE VATTU.TXT
// ==========================================================

void saveNodeToFile(TreeVatTu t, ofstream &fout) {
    if (t != nullptr) {
        fout << t->data.MAVT << "|"
             << t->data.tenVatTu << "|"
             << t->data.donViTinh << "|"
             << t->data.soLuongTon << "\n";
        
        saveNodeToFile(t->left, fout);
        saveNodeToFile(t->right, fout);
    }
}

bool SaveTreeVatTuToFile(TreeVatTu t, const string &filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        return false;
    }

    saveNodeToFile(t, fout);
    fout.close();
    return true;
}

bool LoadTreeVatTuFromFile(TreeVatTu &t, const string &filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        return false;
    }

    freeTreeVatTu(t);
    initTreeVatTu(t);

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        VatTu vt;
        string soLuongStr;

        getline(ss, vt.MAVT, '|');
        getline(ss, vt.tenVatTu, '|');
        getline(ss, vt.donViTinh, '|');
        getline(ss, soLuongStr, '|');

        if (!vt.MAVT.empty() && !soLuongStr.empty()) {
            vt.soLuongTon = stoi(soLuongStr);
            insertVatTu(t, vt);
        }
    }

    fin.close();
    return true;
}