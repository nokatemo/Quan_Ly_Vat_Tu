#include "HoaDon.h"
#include "UI.h"
#include "Validate.h"
#include "NhanVien.h"
#include "VatTu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// =========================================================
// PHAN 1: CAC HAM BO TRO XU LY DANH SACH CHI TIET HOA DON
// =========================================================

// Tao mot node chi tiet hoa don moi
NodeCTHD* TaoNodeCTHD(ChiTietHoaDon ct) {
    NodeCTHD* p = new NodeCTHD;
    if (p == NULL) return NULL;
    p->data = ct;
    p->next = NULL;
    return p;
}

// Them chi tiet hoa don vao dau danh sach lien ket
void ThemCTHD(ListCTHD &dscthd, ChiTietHoaDon ct) {
    NodeCTHD* p = TaoNodeCTHD(ct);
    if (p == NULL) return;
    p->next = dscthd;
    dscthd = p;
}

// Xoa mot chi tiet vat tu khoi danh sach hoa don tam theo ma vat tu
void XoaCTHDTrongDSTam(ListCTHD &dscthd, string maVT) {
    if (dscthd == NULL) return;

    NodeCTHD* kieu = dscthd;
    NodeCTHD* bfkieu = NULL;

    while (kieu != NULL && kieu->data.MAVT != maVT) {
        bfkieu = kieu;
        kieu = kieu->next;
    }

    if (kieu == NULL) return;

    if (bfkieu == NULL) {
        dscthd = dscthd->next;
    } else {
        bfkieu->next = kieu->next;
    }

    delete kieu;
}

// Giai phong bo nho danh sach lien ket chi tiet hoa don
void GiaiPhongDSCTHD(ListCTHD &dscthd) {
    while (dscthd != NULL) {
        NodeCTHD *temp = dscthd;
        dscthd = dscthd->next;
        delete temp;
    }
    dscthd = NULL;
}

// Kiem tra vat tu da ton tai trong gio hang/hoa don tam hay chua
bool KiemTraTrungVatTuTrongGio(ListCTHD head, const string& maVT) {
    NodeCTHD* p = head;
    while (p != NULL) {
        if (p->data.MAVT == maVT) return true;
        p = p->next;
    }
    return false;
}

// =========================================================
// PHAN 2: CAC HAM XU LY FILE (HOADON.TXT)
// =========================================================

// Luu tat ca hoa don cua nhan vien ra file HoaDon.txt
void LuuFileHoaDon(DanhSachNhanVien dsNV) {
    ofstream f("HoaDon.txt", ios::out);
    if (!f.is_open()) return;

    int demNVCoHD = 0;
    for (int i = 0; i < dsNV.soLuong; i++) {
        if (dsNV.ds[i]->dshd != NULL) demNVCoHD++;
    }

    f << demNVCoHD << endl;

    for (int i = 0; i < dsNV.soLuong; i++) {
        NhanVien* nv = dsNV.ds[i];
        if (nv->dshd == NULL) continue;

        int demHD = 0;
        NodeHoaDon* pHD = nv->dshd;
        while (pHD != NULL) {
            demHD++;
            pHD = pHD->next;
        }

        f << nv->MANV << "|" << demHD << endl;

        pHD = nv->dshd;
        while (pHD != NULL) {
            int demCTHD = 0;
            NodeCTHD* pCT = pHD->data.dscthd;
            while (pCT != NULL) {
                demCTHD++;
                pCT = pCT->next;
            }

            f << pHD->data.soHD << "|"
              << pHD->data.ngayLap.ngay << "|"
              << pHD->data.ngayLap.thang << "|"
              << pHD->data.ngayLap.nam << "|"
              << pHD->data.loai << "|"
              << demCTHD << endl;

            pCT = pHD->data.dscthd;
            while (pCT != NULL) {
                f << pCT->data.MAVT << "|"
                  << pCT->data.soLuong << "|"
                  << pCT->data.donGia << "|"
                  << pCT->data.VAT << endl;
                pCT = pCT->next;
            }
            pHD = pHD->next;
        }
    }
    f.close();
}

// Doc du lieu hoa don tu file HoaDon.txt vao danh sach nhan vien
void DocFileHoaDon(DanhSachNhanVien &dsNV) {
    ifstream f("HoaDon.txt", ios::in);
    if (!f.is_open()) return;

    string line;
    while (getline(f, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (!line.empty()) break;
    }

    if (line.empty()) {
        f.close();
        return;
    }

    int soLuongNVCoHD = 0;
    try {
        soLuongNVCoHD = stoi(line);
    } catch (...) {
        f.close();
        return;
    }

    for (int i = 0; i < soLuongNVCoHD; i++) {
        if (!getline(f, line)) break;
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;

        stringstream ssNV(line);
        string maNV, strSoHD;
        getline(ssNV, maNV, '|');
        getline(ssNV, strSoHD, '|');
        
        if (strSoHD.empty()) continue;
        int soLuongHD = 0;
        try { soLuongHD = stoi(strSoHD); } catch (...) { continue; }

        int vtNV = TimkiemNhanVien(dsNV, maNV);

        for (int j = 0; j < soLuongHD; j++) {
            if (!getline(f, line)) break;
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty()) continue;

            stringstream ssHD(line);
            string strNgay, strThang, strNam, strLoai, strSoCTHD;

            HoaDon hd;
            hd.dscthd = NULL;

            getline(ssHD, hd.soHD, '|');
            getline(ssHD, strNgay, '|');
            getline(ssHD, strThang, '|');
            getline(ssHD, strNam, '|');
            getline(ssHD, strLoai, '|');
            getline(ssHD, strSoCTHD, '|');

            if (strSoCTHD.empty()) continue;

            try {
                hd.ngayLap.ngay = stoi(strNgay);
                hd.ngayLap.thang = stoi(strThang);
                hd.ngayLap.nam = stoi(strNam);
            } catch (...) { continue; }

            hd.loai = strLoai.empty() ? 'N' : strLoai[0];
            int soLuongCTHD = 0;
            try { soLuongCTHD = stoi(strSoCTHD); } catch (...) { continue; }

            for (int k = 0; k < soLuongCTHD; k++) {
                if (!getline(f, line)) break;
                if (!line.empty() && line.back() == '\r') line.pop_back();
                if (line.empty()) continue;

                stringstream ssCT(line);
                string strSL, strDG, strVAT;
                ChiTietHoaDon ct;

                getline(ssCT, ct.MAVT, '|');
                getline(ssCT, strSL, '|');
                getline(ssCT, strDG, '|');
                getline(ssCT, strVAT, '|');

                try {
                    ct.soLuong = stoi(strSL);
                    ct.donGia = stod(strDG);
                    ct.VAT = stof(strVAT);
                } catch (...) { continue; }

                ThemCTHD(hd.dscthd, ct);
            }

            if (vtNV != -1) {
                NodeHoaDon* pHD = new NodeHoaDon();
                pHD->data = hd;
                pHD->next = dsNV.ds[vtNV]->dshd;
                dsNV.ds[vtNV]->dshd = pHD;
            }
        }
    }
    f.close();
}

// =========================================================
// PHAN 3: UI, HAM NHAP LINH HOAT VA BANG CHON VAT TU
// =========================================================

namespace {
    const int KHUNG_HD_X = 12;
    const int KHUNG_HD_Y = 1;
    const int KHUNG_HD_RONG = 98;
    const int KHUNG_HD_CAO = 26;

    // Xoa mot dong trong khung hoa don
    void XoaDongHD(int dong, int chieuRong = KHUNG_HD_RONG - 4) {
        clearLine(KHUNG_HD_X + 2, dong, chieuRong);
    }

    // In tieu de va duong ke ngang can giua khung
    void InIntroBanner(int boxX, int boxY, string titleText, int boxW) {
        int padLeft = (boxW - (int)titleText.length()) / 2;
        if (padLeft < 1) padLeft = 1;

        textcolor(14); 
        gotoxy(boxX + 2, boxY + 1); 
        for (int i = 0; i < boxW - 3; i++) cout << "=";

        gotoxy(boxX + padLeft, boxY + 2);
        textcolor(11); 
        cout << titleText;

        textcolor(14);
        gotoxy(boxX + 2, boxY + 3); 
        for (int i = 0; i < boxW - 3; i++) cout << "=";
        textcolor(11);
    }

    // Ham nhap chuoi linh hoat: ho tro ESC de huy va quay ve Menu bat ky luc nao
    bool NhapInputESC(int x, int y, string &outStr, size_t maxLen, bool inHoa = false, bool chiSo = false) {
        ShowConsoleCursor(true);
        gotoxy(x, y);
        cout << outStr << flush;
        size_t pos = outStr.length();

        while (true) {
            gotoxy(x + (int)pos, y);
            int c = _getch();

            if (c == 27) { // ESC -> Huy va thoat ngay ve Menu
                ShowConsoleCursor(false);
                return false;
            }
            if (c == 13) { // Enter -> Ket thuc nhap
                ShowConsoleCursor(false);
                return true;
            }
            if (c == 8) { // Backspace -> Xoa ky tu cuoi
                if (pos > 0) {
                    outStr.erase(pos - 1, 1);
                    pos--;
                    gotoxy(x + (int)pos, y);
                    cout << " " << flush;
                    gotoxy(x + (int)pos, y);
                }
                continue;
            }
            if (c == 0 || c == 224 || c == -32) {
                _getch(); // Bo qua cac phim mui ten hoac phim chuc nang
                continue;
            }

            if (outStr.length() < maxLen && c >= 32 && c <= 126) {
                char ch = (char)c;
                if (chiSo && !isdigit(ch)) continue;
                if (inHoa) ch = (char)toupper(ch);

                outStr.insert(pos, 1, ch);
                pos++;
                cout << ch << flush;
            }
        }
    }
}

// Chuyen cay nhi phan tim kiem vat tu sang mang de hien thi bang chon
void ChuyenCayThanhMang(TreeVatTu root, VatTu ds[], int &n) {
    if (root != NULL) {
        ChuyenCayThanhMang(root->left, ds, n);
        ds[n++] = root->data;
        ChuyenCayThanhMang(root->right, ds, n);
    }
}

// Giao dien bang chon vat tu tu danh sach kho
bool ChonVatTuTuBang(TreeVatTu root, VatTu &vtChon) {
    VatTu ds[500];
    int count = 0;
    ChuyenCayThanhMang(root, ds, count);

    if (count == 0) return false;

    system("cls");
    drawBox(KHUNG_HD_X, KHUNG_HD_Y, KHUNG_HD_RONG, KHUNG_HD_CAO, 14);

    InIntroBanner(KHUNG_HD_X, KHUNG_HD_Y, "DANH MUC VAT TU KHO", KHUNG_HD_RONG);

    gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 5);
    textcolor(11);
    cout << left << setw(5) << "STT" << "| "
         << setw(10) << "Ma VT" << "| "
         << setw(35) << "Ten Vat Tu" << "| "
         << setw(10) << "DVT" << "| "
         << "Ton Kho";

    gotoxy(KHUNG_HD_X + 2, KHUNG_HD_Y + 6);
    cout << "---------------------------------------------------------------------------------------------";

    int selectedIdx = 0;
    int topIdx = 0;
    int pageSize = 12;
    int rowWidthMax = KHUNG_HD_RONG - 5;

    ShowConsoleCursor(false);

    // In mot dong vat tu trong bang chon
    auto InDongVatTu = [&](int idx, int printY, bool isSelected) {
        stringstream ss;
        ss << left << setw(5) << (idx + 1) << "| "
           << setw(10) << ds[idx].MAVT << "| "
           << setw(35) << ds[idx].TENVT << "| "
           << setw(10) << ds[idx].DVT << "| "
           << left << setw(10) << ds[idx].soLuongTon;
           
        string text = ss.str();
        while (text.length() < (size_t)rowWidthMax) text += " ";

        gotoxy(KHUNG_HD_X + 3, printY);
        if (isSelected) textcolor(31); // Highlight dong dang chon
        else textcolor(11);
        cout << text;
        textcolor(11); 
    };

    // Ve lai toan bo trang danh sach vat tu
    auto VeTrang = [&]() {
        for (int i = 0; i < pageSize; i++) {
            int currIdx = topIdx + i;
            int printY = KHUNG_HD_Y + 7 + i;
            clearLine(KHUNG_HD_X + 3, printY, rowWidthMax);
            if (currIdx < count) {
                InDongVatTu(currIdx, printY, currIdx == selectedIdx);
            }
        }
        textcolor(14);
        gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 20);
        clearLine(KHUNG_HD_X + 3, KHUNG_HD_Y + 20, rowWidthMax);
        cout << "[Trang " << (topIdx / pageSize) + 1 << "/" << ((count - 1) / pageSize) + 1 << "]";
    };

    VeTrang();

    textcolor(10);
    gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 22);
    cout << "[Mui ten Len/Xuong]: Di Chuyen Dong | [Mui ten Trai/Phai]: Chuyen Trang";
    gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 23);
    cout << "[Enter]: Them Vat Tu Nay Vao Hoa Don | [ESC]: Huy Bo & Quay Lai";
    textcolor(11);

    // Vong lap dieu khien bang chon vat tu
    while (true) {
        char key = _getch();
        if (key == -32 || key == 224) {
            key = _getch();
            int prevIdx = selectedIdx;

            if (key == 72) { // Mui ten Len
                if (selectedIdx > 0) selectedIdx--;
            } else if (key == 80) { // Mui ten Xuong
                if (selectedIdx < count - 1) selectedIdx++;
            } else if (key == 75) { // Mui ten Trai (Lui trang)
                if (topIdx > 0) {
                    selectedIdx = max(0, selectedIdx - pageSize);
                    topIdx = max(0, topIdx - pageSize);
                    VeTrang();
                    continue;
                }
            } else if (key == 77) { // Mui ten Phai (Tien trang)
                if (topIdx + pageSize < count) {
                    selectedIdx = min(count - 1, selectedIdx + pageSize);
                    topIdx += pageSize;
                    VeTrang();
                    continue;
                }
            }

            if (prevIdx != selectedIdx) {
                if (selectedIdx < topIdx || selectedIdx >= topIdx + pageSize) {
                    if (selectedIdx < topIdx) topIdx = selectedIdx;
                    else topIdx = selectedIdx - pageSize + 1;
                    VeTrang();
                } else {
                    int prevY = KHUNG_HD_Y + 7 + (prevIdx - topIdx);
                    InDongVatTu(prevIdx, prevY, false);

                    int currY = KHUNG_HD_Y + 7 + (selectedIdx - topIdx);
                    InDongVatTu(selectedIdx, currY, true);
                }
            }
        } else if (key == 13) { // Enter -> Lay vat tu duoc chon
            vtChon = ds[selectedIdx];
            return true;
        } else if (key == 27) { // ESC -> Huy chon
            return false;
        }
    }
}

// =========================================================
// PHAN 4: GIAO DIEN CAU E - LAP HOA DON NHAP / XUAT KHO
// =========================================================

void giaodienLapHoaDon(DanhSachNhanVien &dsNV, TreeVatTu &root) {
    system("cls");
    HoaDon hdTam;
    hdTam.dscthd = NULL;

    drawBox(KHUNG_HD_X, KHUNG_HD_Y, KHUNG_HD_RONG, KHUNG_HD_CAO, 14);
    InIntroBanner(KHUNG_HD_X, KHUNG_HD_Y, "HE THONG LAP HOA DON NHAP / XUAT KHO", KHUNG_HD_RONG);

    textcolor(10);
    gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 24);
    cout << "[Luu y: Nhan ESC o bat ky o nhap nao de huy va thoat ve Menu]";

    // BUOC 1: NHAP MA NHAN VIEN LAP HOA DON
    int vtNV = -1;
    string maNV = "";
    while (true) {
        clearLine(KHUNG_HD_X + 3, KHUNG_HD_Y + 5, 88);
        clearLine(KHUNG_HD_X + 3, KHUNG_HD_Y + 6, 88);

        textcolor(11);
        gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 5);
        cout << "1. Nhap Ma Nhan Vien: ";

        maNV = "";
        if (!NhapInputESC(KHUNG_HD_X + 25, KHUNG_HD_Y + 5, maNV, 10, true)) {
            GiaiPhongDSCTHD(hdTam.dscthd);
            return;
        }

        vtNV = TimkiemNhanVien(dsNV, maNV);
        if (vtNV == -1) {
            textcolor(12);
            gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 6);
            cout << "=> LOI: Ma NV '" << maNV << "' khong ton tai! Nhan phim bat ky de nhap lai...";
            textcolor(11);
            _getch();
        } else {
            textcolor(10);
            gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 6);
            cout << "=> Nhan Vien: " << dsNV.ds[vtNV]->HO << " " << dsNV.ds[vtNV]->TEN;
            textcolor(11);
            break;
        }
    }

    // BUOC 2: NHAP SO HOA DON VA KIEM TRA TRUNG MA
    while (true) {
        clearLine(KHUNG_HD_X + 3, KHUNG_HD_Y + 8, 88);
        clearLine(KHUNG_HD_X + 3, KHUNG_HD_Y + 9, 88);

        textcolor(11);
        gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 8);
        cout << "2. Nhap So Hoa Don: ";

        string soHD = "";
        if (!NhapInputESC(KHUNG_HD_X + 23, KHUNG_HD_Y + 8, soHD, 20, true)) {
            GiaiPhongDSCTHD(hdTam.dscthd);
            return;
        }

        if (soHD.empty()) {
            textcolor(12);
            gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 9);
            cout << "=> LOI: So HD khong duoc de trong! Nhan phim bat ky de nhap lai...";
            textcolor(11);
            _getch();
            continue;
        }

        bool trunghd = false;
        for (int i = 0; i < dsNV.soLuong; i++) {
            NodeHoaDon* pHD = dsNV.ds[i]->dshd;
            while (pHD != NULL) {
                if (pHD->data.soHD == soHD) { trunghd = true; break; }
                pHD = pHD->next;
            }
            if (trunghd) break;
        }

        if (trunghd) {
            textcolor(12);
            gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 9);
            cout << "=> LOI: So HD '" << soHD << "' da ton tai! Nhan phim bat ky de nhap lai...";
            textcolor(11);
            _getch();
        } else {
            hdTam.soHD = soHD;
            textcolor(10);
            gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 9);
            cout << "=> So Hoa Don hop le!";
            textcolor(11);
            break;
        }
    }

    // BUOC 3: FORM NHAP NGAY, THANG, NAM LAP & LOAI HOA DON ('N' / 'X')
    string strNgay = "", strThang = "", strNam = "", strLoai = "N";
    int activeField = 0;

    textcolor(11);
    gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 11); cout << "3. Ngay Lap    : ";
    gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 12); cout << "4. Thang Lap   : ";
    gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 13); cout << "5. Nam Lap     : ";
    gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 14); cout << "6. Loai Hoa Don (N: Nhap kho / X: Xuat kho): ";

    textcolor(11);
    gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 16);
    cout << "[>>> ENTER DE XAC NHAN THONG TIN NGAY & LOAI HOA DON | ESC DE THOAT <<<]";

    while (true) {
        clearLine(KHUNG_HD_X + 20, KHUNG_HD_Y + 11, 10);
        clearLine(KHUNG_HD_X + 20, KHUNG_HD_Y + 12, 10);
        clearLine(KHUNG_HD_X + 20, KHUNG_HD_Y + 13, 10);
        clearLine(KHUNG_HD_X + 48, KHUNG_HD_Y + 14, 10);

        gotoxy(KHUNG_HD_X + 20, KHUNG_HD_Y + 11); cout << strNgay;
        gotoxy(KHUNG_HD_X + 20, KHUNG_HD_Y + 12); cout << strThang;
        gotoxy(KHUNG_HD_X + 20, KHUNG_HD_Y + 13); cout << strNam;
        gotoxy(KHUNG_HD_X + 48, KHUNG_HD_Y + 14); cout << strLoai;

        if (activeField == 4) {
            textcolor(31);
            gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 16);
            cout << "[>>> ENTER DE XAC NHAN THONG TIN NGAY & LOAI HOA DON | ESC DE THOAT <<<]";
            textcolor(11);
        } else {
            textcolor(11);
            gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 16);
            cout << "[>>> ENTER DE XAC NHAN THONG TIN NGAY & LOAI HOA DON | ESC DE THOAT <<<]";
        }

        ShowConsoleCursor(true);
        if (activeField == 0) gotoxy(KHUNG_HD_X + 20 + strNgay.length(), KHUNG_HD_Y + 11);
        else if (activeField == 1) gotoxy(KHUNG_HD_X + 20 + strThang.length(), KHUNG_HD_Y + 12);
        else if (activeField == 2) gotoxy(KHUNG_HD_X + 20 + strNam.length(), KHUNG_HD_Y + 13);
        else if (activeField == 3) gotoxy(KHUNG_HD_X + 48 + strLoai.length(), KHUNG_HD_Y + 14);
        else if (activeField == 4) gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 16);

        char c = _getch();

        if (c == 27) { // ESC -> Thoat ve Menu
            GiaiPhongDSCTHD(hdTam.dscthd);
            return;
        }

        if (c == -32 || c == 224) { // Chuyen o nhap bang phim mui ten Up/Down
            char key = _getch();
            if (key == 72) activeField = (activeField - 1 + 5) % 5;
            else if (key == 80) activeField = (activeField + 1) % 5;
            continue;
        }

        if (c == 8) { // Backspace -> Xoa ky tu trong field hien tai
            if (activeField == 0 && !strNgay.empty()) strNgay.pop_back();
            else if (activeField == 1 && !strThang.empty()) strThang.pop_back();
            else if (activeField == 2 && !strNam.empty()) strNam.pop_back();
            else if (activeField == 3 && !strLoai.empty()) strLoai.pop_back();
            continue;
        }

        if (c == 13) { // Enter -> Sang field tiep theo hoac xac nhan
            if (activeField < 4) {
                activeField++;
            } else {
                int ng = strNgay.empty() ? 0 : stoi(strNgay);
                int th = strThang.empty() ? 0 : stoi(strThang);
                int na = strNam.empty() ? 0 : stoi(strNam);

                if (!ngayhople(ng, th, na)) {
                    textcolor(12);
                    gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 18);
                    cout << "=> LOI: Ngay " << ng << "/" << th << "/" << na << " khong hop le! Nhan phim bat ky de nhap lai...";
                    textcolor(11);
                    _getch();
                    clearLine(KHUNG_HD_X + 3, KHUNG_HD_Y + 18, 88);
                    activeField = 0;
                } else if (strLoai != "N" && strLoai != "X") {
                    textcolor(12);
                    gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 18);
                    cout << "=> LOI: Loai hoa don phai la 'N' hoac 'X'! Nhan phim bat ky de nhap lai...";
                    textcolor(11);
                    _getch();
                    clearLine(KHUNG_HD_X + 3, KHUNG_HD_Y + 18, 88);
                    activeField = 3;
                } else {
                    hdTam.ngayLap.ngay = ng;
                    hdTam.ngayLap.thang = th;
                    hdTam.ngayLap.nam = na;
                    hdTam.loai = strLoai[0];
                    textcolor(10);
                    gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 18);
                    cout << "=> Ngay lap & Loai hoa don [" << (hdTam.loai == 'N' ? "NHAP KHO" : "XUAT KHO") << "] hop le!";
                    textcolor(11);
                    _getch();
                    break;
                }
            }
            continue;
        }

        if (activeField == 0 && isdigit(static_cast<unsigned char>(c)) && strNgay.length() < 2) strNgay += c;
        else if (activeField == 1 && isdigit(static_cast<unsigned char>(c)) && strThang.length() < 2) strThang += c;
        else if (activeField == 2 && isdigit(static_cast<unsigned char>(c)) && strNam.length() < 4) strNam += c;
        else if (activeField == 3) {
            char u = toupper(static_cast<unsigned char>(c));
            if (u == 'N' || u == 'X') strLoai = u;
            else strLoai = "";
        }
    }

    // BUOC 4: GIAO DIEN QUAN LY DANH SACH CHI TIET HOA DON TAM
    int menuSelected = 0;
    int currentPage = 1;
    int pageSize = 6;
    
    while (true) {
        int totalItems = 0;
        double tongTien = 0;
        NodeCTHD* pNode = hdTam.dscthd;
        while (pNode != NULL) {
            totalItems++;
            tongTien += pNode->data.soLuong * pNode->data.donGia * (1.0 + pNode->data.VAT / 100.0);
            pNode = pNode->next;
        }
        
        int totalPages = max(1, (totalItems + pageSize - 1) / pageSize);
        if (currentPage > totalPages) currentPage = totalPages;

        system("cls");
        drawBox(KHUNG_HD_X, KHUNG_HD_Y, KHUNG_HD_RONG, KHUNG_HD_CAO, 14);

        InIntroBanner(KHUNG_HD_X, KHUNG_HD_Y, "HOA DON: " + hdTam.soHD + " | NV: " + dsNV.ds[vtNV]->TEN + " | LOAI: " + (hdTam.loai == 'N' ? "NHAP KHO" : "XUAT KHO"), KHUNG_HD_RONG);

        gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 5);
        textcolor(11);
        cout << left << setw(4) << "STT" << "| "
             << setw(8) << "Ma VT" << "| "
             << setw(22) << "Ten Vat Tu" << "| "
             << setw(6) << "DVT" << "| "
             << setw(5) << "SL" << "| "
             << setw(11) << "Don Gia" << "| "
             << setw(6) << "VAT" << "| "
             << "Thanh Tien";

        gotoxy(KHUNG_HD_X + 2, KHUNG_HD_Y + 6);
        cout << "---------------------------------------------------------------------------------------------";

        // In danh sach cac mat hang trong hoa don tam theo phan trang
        auto VeTrangItems = [&]() {
            int startIndex = (currentPage - 1) * pageSize;
            
            NodeCTHD* pCurr = hdTam.dscthd;
            for (int k = 0; k < startIndex && pCurr != NULL; k++) {
                pCurr = pCurr->next;
            }

            int printY = KHUNG_HD_Y + 7;
            cout << fixed << setprecision(0);

            for (int i = 0; i < pageSize; i++) {
                gotoxy(KHUNG_HD_X + 3, printY + i);
                clearLine(KHUNG_HD_X + 3, printY + i, KHUNG_HD_RONG - 5);
                
                if (pCurr != NULL) {
                    int idx = startIndex + i;
                    string tenVT = "N/A", dvt = "N/A";
                    NodeVatTu* nodeVT = TimKiemVatTu(root, pCurr->data.MAVT);
                    if (nodeVT != NULL) { 
                        tenVT = nodeVT->data.TENVT; 
                        dvt = nodeVT->data.DVT; 
                    }
                    
                    double tt = pCurr->data.soLuong * pCurr->data.donGia * (1.0 + pCurr->data.VAT / 100.0);

                    textcolor(11);
                    cout << left << setw(4) << (idx + 1) << "| "
                         << setw(8) << pCurr->data.MAVT << "| "
                         << setw(22) << tenVT << "| "
                         << setw(6) << dvt << "| "
                         << setw(5) << pCurr->data.soLuong << "| "
                         << setw(11) << (long long)pCurr->data.donGia << "| "
                         << setw(6) << (to_string((int)pCurr->data.VAT) + "%") << "| "
                         << (long long)tt;

                    pCurr = pCurr->next;
                }
            }

            textcolor(14);
            gotoxy(KHUNG_HD_X + 75, KHUNG_HD_Y + 14);
            clearLine(KHUNG_HD_X + 75, KHUNG_HD_Y + 14, 20);
            cout << "[Trang " << currentPage << "/" << totalPages << "]";
        };

        VeTrangItems();

        gotoxy(KHUNG_HD_X + 2, KHUNG_HD_Y + 13);
        textcolor(11);
        cout << "=============================================================================================";
        gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 14);
        textcolor(10);
        cout << "TONG CONG TAM TINH: " << (long long)tongTien << " VND";
        
        string items[4] = {
            "1. Them Vat Tu Vao Hoa Don (Mo Bang Chon)",
            "2. Xoa Chi Tiet Vat Tu Trong Hoa Don",
            "3. CHOT LUU HOA DON XUONG HE THONG",
            "4. HUY LAP HOA DON (XOA DU LIEU TAM)"
        };

        // In menu lua chon chuc nang lap hoa don
        auto VeMenu = [&]() {
            for (int i = 0; i < 4; i++) {
                gotoxy(KHUNG_HD_X + 5, KHUNG_HD_Y + 16 + i);
                string text = (i == menuSelected ? "=> " : "   ") + items[i];
                while (text.length() < 60) text += " ";
                if (i == menuSelected) { textcolor(31); cout << text; }
                else { textcolor(11); cout << text; }
                textcolor(11);
            }
        };

        VeMenu();

        ShowConsoleCursor(false);
        int choice = 0;
        
        // Vong lap bat phim trong menu thao tac hoa don
        while (true) {
            char key = _getch();
            if (key == -32 || key == 224) {
                key = _getch();
                if (key == 72) { 
                    menuSelected = (menuSelected - 1 + 4) % 4;
                    VeMenu();
                } else if (key == 80) { 
                    menuSelected = (menuSelected + 1) % 4;
                    VeMenu();
                } else if (key == 75) { 
                    if (currentPage > 1) { currentPage--; VeTrangItems(); }
                } else if (key == 77) { 
                    if (currentPage < totalPages) { currentPage++; VeTrangItems(); }
                }
            } else if (key == 13) {
                choice = menuSelected + 1;
                break;
            }
        }

        // CHUC NANG 1: THEM VAT TU VAO HOA DON TAM
			if (choice == 1) {
			    VatTu vtChon;
			    if (ChonVatTuTuBang(root, vtChon)) {
			        if (KiemTraTrungVatTuTrongGio(hdTam.dscthd, vtChon.MAVT)) {
			            // Xoa sach dong huong dan cu o dong 22 va 23 truoc khi in thong bao loi
			            clearLine(KHUNG_HD_X + 3, KHUNG_HD_Y + 22, KHUNG_HD_RONG - 5);
			            clearLine(KHUNG_HD_X + 3, KHUNG_HD_Y + 23, KHUNG_HD_RONG - 5);
			            
			            gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 22);
			            textcolor(12);
			            cout << "=> LOI: Vat tu '" << vtChon.MAVT << "' da co trong hoa don!";
			            
			            gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 23);
			            textcolor(10);
			            cout << "[Nhan phim bat ky de tiep tuc...]";
			            textcolor(11);
			            
			            _getch();
			            continue;
			        }

                system("cls");
                drawBox(KHUNG_HD_X, KHUNG_HD_Y, KHUNG_HD_RONG, KHUNG_HD_CAO, 14);

                InIntroBanner(KHUNG_HD_X, KHUNG_HD_Y, "THEM VAT TU: [" + vtChon.MAVT + " - " + vtChon.TENVT + "]", KHUNG_HD_RONG);

                textcolor(11);
                gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 5);
                cout << "So luong ton hien co: " << vtChon.soLuongTon << " " << vtChon.DVT;

                textcolor(11);
                gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 7); cout << "Nhap So Luong: ";
                gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 9); cout << "Nhap Don Gia : ";
                gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 10); cout << "Nhap % VAT   : ";

                textcolor(11);
                gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 12);
                cout << "[>>> ENTER DE THEM VAT TU VAO HOA DON | ESC DE HUY <<<]";

                string strSL = "1", strDG = "100000", strVAT = "10";
                int subField = 0;

                while (true) {
                    gotoxy(KHUNG_HD_X + 18, KHUNG_HD_Y + 7);  cout << left << setw(15) << strSL;
                    gotoxy(KHUNG_HD_X + 18, KHUNG_HD_Y + 9);  cout << left << setw(15) << strDG;
                    gotoxy(KHUNG_HD_X + 18, KHUNG_HD_Y + 10); cout << left << setw(15) << strVAT;

                    if (subField == 3) {
                        textcolor(31);
                        gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 12);
                        cout << "[>>> ENTER DE THEM VAT TU VAO HOA DON | ESC DE HUY <<<]";
                        textcolor(11);
                    } else {
                        textcolor(11);
                        gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 12);
                        cout << "[>>> ENTER DE THEM VAT TU VAO HOA DON | ESC DE HUY <<<]";
                    }

                    ShowConsoleCursor(true);
                    if (subField == 0) gotoxy(KHUNG_HD_X + 18 + strSL.length(), KHUNG_HD_Y + 7);
                    else if (subField == 1) gotoxy(KHUNG_HD_X + 18 + strDG.length(), KHUNG_HD_Y + 9);
                    else if (subField == 2) gotoxy(KHUNG_HD_X + 18 + strVAT.length(), KHUNG_HD_Y + 10);
                    else if (subField == 3) gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 12);

                    char k = _getch();
                    if (k == 27) break; // ESC -> Huy them vat tu nay

                    if (k == -32 || k == 224) {
                        char subKey = _getch();
                        if (subKey == 72) subField = (subField - 1 + 4) % 4;
                        else if (subKey == 80) subField = (subField + 1) % 4;
                        continue;
                    }

                    if (k == 8) { // Backspace
                        if (subField == 0 && !strSL.empty()) strSL.pop_back();
                        else if (subField == 1 && !strDG.empty()) strDG.pop_back();
                        else if (subField == 2 && !strVAT.empty()) strVAT.pop_back();
                        continue;
                    }

                    if (k == 13) {
                        if (subField < 3) {
                            subField++;
                        } else {
                            int sl = strSL.empty() ? 0 : stoi(strSL);
                            double dg = strDG.empty() ? 0 : stod(strDG);
                            double v = strVAT.empty() ? 0 : stod(strVAT);

                            if (sl <= 0) {
                                textcolor(12);
                                gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 14);
                                cout << "=> LOI: So luong phai lon hon 0!";
                                textcolor(11);
                                _getch();
                                clearLine(KHUNG_HD_X + 3, KHUNG_HD_Y + 14, 75);
                                subField = 0;
                            } else if (hdTam.loai == 'X' && sl > vtChon.soLuongTon) {
                                textcolor(12);
                                gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 14);
                                cout << "=> LOI: Vuot qua ton kho (Hien co: " << vtChon.soLuongTon << ")!";
                                textcolor(11);
                                _getch();
                                clearLine(KHUNG_HD_X + 3, KHUNG_HD_Y + 14, 75);
                                subField = 0;
                            } else {
                                ChiTietHoaDon ct;
                                ct.MAVT = vtChon.MAVT;
                                ct.soLuong = sl;
                                ct.donGia = dg;
                                ct.VAT = (float)v;

                                ThemCTHD(hdTam.dscthd, ct);

                                textcolor(10);
                                gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 14);
                                cout << "=> DA THEM CHI TIET VAT TU VAO HOA DON!";
                                textcolor(11);
                                _getch();
                                break;
                            }
                        }
                        continue;
                    }

                    if (subField == 0 && isdigit(static_cast<unsigned char>(k))) strSL += k;
                    else if (subField == 1 && (isdigit(static_cast<unsigned char>(k)) || k == '.')) strDG += k;
                    else if (subField == 2 && (isdigit(static_cast<unsigned char>(k)) || k == '.')) strVAT += k;
                }
            }
        }
        // CHUC NANG 2: XOA CHI TIET VAT TU KHOI HOA DON TAM
        else if (choice == 2) {
            if (hdTam.dscthd == NULL) {
                textcolor(12);
                gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 22); cout << "=> LOI: Danh sach chi tiet hien dang rong!";
                textcolor(11);
                _getch();
                continue;
            }
            clearLine(KHUNG_HD_X + 3, KHUNG_HD_Y + 22, 80);
            gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 22); textcolor(11);
            cout << "Nhap Ma Vat Tu can xoa: ";
            string maXoa = "";
            if (NhapInputESC(KHUNG_HD_X + 27, KHUNG_HD_Y + 22, maXoa, 10, true)) {
                XoaCTHDTrongDSTam(hdTam.dscthd, maXoa);
            }
        }
        // CHUC NANG 3: CHOT LUU HOA DON
        else if (choice == 3) {
            if (hdTam.dscthd == NULL) {
                textcolor(12);
                gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 22); cout << "=> LOI: Hoa don rong! Khong the luu.";
                textcolor(11);
                _getch();
                continue;
            }
            break; 
        }
        // CHUC NANG 4: HUY LAP HOA DON
        else if (choice == 4) {
            GiaiPhongDSCTHD(hdTam.dscthd);
            return;
        }
    }

    // BUOC 5: CAP NHAT CAY VAT TU, CHEN HOA DON VAO NHAN VIEN VA GHI FILE
    NodeCTHD* pCT = hdTam.dscthd;
    while (pCT != NULL) {
        NodeVatTu* nodeVT = TimKiemVatTu(root, pCT->data.MAVT);
        if (nodeVT != NULL) {
            if (hdTam.loai == 'N') {
                nodeVT->data.soLuongTon += pCT->data.soLuong;
            } else if (hdTam.loai == 'X') {
                nodeVT->data.soLuongTon -= pCT->data.soLuong;
            }
        }
        pCT = pCT->next;
    }

    NodeHoaDon* pHD = new NodeHoaDon();
    pHD->data = hdTam;
    pHD->next = dsNV.ds[vtNV]->dshd;
    dsNV.ds[vtNV]->dshd = pHD;

    LuuFileHoaDon(dsNV);
    LuuFileVatTu(root);

    system("cls");
    drawBox(KHUNG_HD_X, KHUNG_HD_Y, KHUNG_HD_RONG, KHUNG_HD_CAO, 14);
    InIntroBanner(KHUNG_HD_X, KHUNG_HD_Y, "THONG BAO HE THONG", KHUNG_HD_RONG);
    textcolor(10);
    gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 6);
    cout << "=> LAP HOA DON " << hdTam.soHD << " THANH CONG VA DA LUU HE THONG!";
    textcolor(11);
    gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 8);
    cout << "Nhan phim bat ky de ve Menu...";
    _getch();
}

// =========================================================
// PHAN 5: GIAO DIEN CAU F - IN CHI TIET 1 HOA DON
// =========================================================

void giaodienInHoaDon(DanhSachNhanVien dsNV, TreeVatTu root) {
    NodeHoaDon* hdTimThay = NULL;
    NhanVien* nvLap = NULL;

    while (true) {
        system("cls");
        drawBox(KHUNG_HD_X, KHUNG_HD_Y, KHUNG_HD_RONG, KHUNG_HD_CAO, 14);

        InIntroBanner(KHUNG_HD_X, KHUNG_HD_Y, "TRA CUU & IN CHI TIET HOA DON", KHUNG_HD_RONG);

        textcolor(10);
        gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 24);
        cout << "[Luu y: Nhan ESC khi o nhap rong de thoat ve Menu]";

        textcolor(11);
        gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 5);
        cout << "Nhap So Hoa Don can in: ";
        
        string soHD = "";
        if (!NhapInputESC(KHUNG_HD_X + 27, KHUNG_HD_Y + 5, soHD, 20, true)) return; 

        if (soHD.empty()) return; 

        hdTimThay = NULL;
        nvLap = NULL;

        // Tim kiem hoa don trong danh sach nhan vien
        for (int i = 0; i < dsNV.soLuong; i++) {
            NodeHoaDon* pHD = dsNV.ds[i]->dshd;
            while (pHD != NULL) {
                if (pHD->data.soHD == soHD) {
                    hdTimThay = pHD;
                    nvLap = dsNV.ds[i];
                    break;
                }
                pHD = pHD->next;
            }
            if (hdTimThay != NULL) break;
        }

        if (hdTimThay == NULL) {
            textcolor(12);
            gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 7);
            cout << "=> LOI: So HD '" << soHD << "' khong ton tai trong he thong!";
            textcolor(11);
            gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 9);
            cout << "Nhan phim bat ky de nhap lai (hoac ESC de thoat ve Menu)...";
            ShowConsoleCursor(false);
            char k = _getch();
            if (k == 27) return;
        } else {
            break; 
        }
    }

    // Tinh tong tri gia va tong so chi tiet hoa don
    int totalItems = 0;
    double tongTriGia = 0;
    NodeCTHD* pCT = hdTimThay->data.dscthd;

    while (pCT != NULL) {
        totalItems++;
        double thanhTien = pCT->data.soLuong * pCT->data.donGia * (1.0 + pCT->data.VAT / 100.0);
        tongTriGia += thanhTien;
        pCT = pCT->next;
    }

    int pageSize = 9; 
    int totalPages = max(1, (totalItems + pageSize - 1) / pageSize);
    int currentPage = 1;

    ShowConsoleCursor(false);

    // Vong lap in va phan trang chi tiet hoa don
    while (true) {
        system("cls");
        drawBox(KHUNG_HD_X, KHUNG_HD_Y, KHUNG_HD_RONG, KHUNG_HD_CAO, 14);

        string titleHD = "HOA DON " + string(hdTimThay->data.loai == 'N' ? "NHAP KHO" : "XUAT KHO") + " [" + hdTimThay->data.soHD + "]";
        InIntroBanner(KHUNG_HD_X, KHUNG_HD_Y, titleHD, KHUNG_HD_RONG);

        textcolor(11);
        gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 5);
        cout << "So Hoa Don : " << left << setw(15) << hdTimThay->data.soHD;
        gotoxy(KHUNG_HD_X + 45, KHUNG_HD_Y + 5);
        cout << "Ngay Lap : " << hdTimThay->data.ngayLap.ngay << "/"
                             << hdTimThay->data.ngayLap.thang << "/"
                             << hdTimThay->data.ngayLap.nam;

        gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 6);
        cout << "Nhan Vien  : " << nvLap->HO << " " << nvLap->TEN 
             << " (Ma NV: " << nvLap->MANV << ")";

        gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 8);
        cout << left << setw(4) << "STT" << "| "
             << setw(8) << "Ma VT" << "| "
             << setw(22) << "Ten Vat Tu" << "| "
             << setw(6) << "DVT" << "| "
             << setw(5) << "SL" << "| "
             << setw(11) << "Don Gia" << "| "
             << setw(6) << "VAT" << "| "
             << "Thanh Tien";

        gotoxy(KHUNG_HD_X + 2, KHUNG_HD_Y + 9);
        cout << "---------------------------------------------------------------------------------------------";

        int startIndex = (currentPage - 1) * pageSize;
        int printY = KHUNG_HD_Y + 10;

        NodeCTHD* pCurr = hdTimThay->data.dscthd;
        for (int k = 0; k < startIndex && pCurr != NULL; k++) {
            pCurr = pCurr->next;
        }

        cout << fixed << setprecision(0);

        int countInPage = 0;
        while (pCurr != NULL && countInPage < pageSize) {
            int idx = startIndex + countInPage;
            string tenVT = "N/A", dvt = "N/A";

            NodeVatTu* nodeVT = TimKiemVatTu(root, pCurr->data.MAVT);
            if (nodeVT != NULL) {
                tenVT = nodeVT->data.TENVT;
                dvt = nodeVT->data.DVT;
            }

            double thanhTien = pCurr->data.soLuong * pCurr->data.donGia * (1.0 + pCurr->data.VAT / 100.0);

            gotoxy(KHUNG_HD_X + 3, printY);
            textcolor(11);
            cout << left << setw(4) << (idx + 1) << "| "
                 << setw(8) << pCurr->data.MAVT << "| "
                 << setw(22) << tenVT << "| "
                 << setw(6) << dvt << "| "
                 << setw(5) << pCurr->data.soLuong << "| "
                 << setw(11) << (long long)pCurr->data.donGia << "| "
                 << setw(6) << (to_string((int)pCurr->data.VAT) + "%") << "| "
                 << (long long)thanhTien;

            printY++;
            countInPage++;
            pCurr = pCurr->next;
        }

        gotoxy(KHUNG_HD_X + 2, KHUNG_HD_Y + 21);
        textcolor(11);
        cout << "=============================================================================================";

        gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 22);
        textcolor(10);
        cout << "TONG TRI GIA HOA DON: " << (long long)tongTriGia << " VND";

        textcolor(14);
        gotoxy(KHUNG_HD_X + 3, KHUNG_HD_Y + 24);
        cout << "[<- Trai / Phai ->]: Trang " << currentPage << "/" << totalPages 
             << "  |  [Enter/ESC]: Quay Lai Menu";

        char key = _getch();
        if (key == -32 || key == 224) {
            char navKey = _getch();
            if (navKey == 75) { // Mui ten Trai -> Lui trang
                if (currentPage > 1) currentPage--;
            } else if (navKey == 77) { // Mui ten Phai -> Tien trang
                if (currentPage < totalPages) currentPage++;
            }
        } else if (key == 13 || key == 27) { // Enter hoac ESC -> Quay ve Menu
            break;
        }
    }
}
