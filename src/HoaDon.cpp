#include "HoaDon.h"
#include "UI.h"
#include <iostream>
#include <fstream> 
#include <sstream>
#include <conio.h>
#include <cctype>
#include <iomanip>
#include <vector>

using namespace std;

// =========================================================
// PHAN 1: CAC HAM BO TRO XU LY DANH SACH CHI TIET HOA DON
// =========================================================

NodeCTHD* TaoNodeCTHD(ChiTietHoaDon ct) {
    NodeCTHD* p = new NodeCTHD;
    if (p == NULL) return NULL;
    p->data = ct;
    p->next = NULL;
    return p;
}

void ThemCTHD(ListCTHD &dscthd, ChiTietHoaDon ct) {
    NodeCTHD* p = TaoNodeCTHD(ct);
    if (p == NULL) return;
    p->next = dscthd;
    dscthd = p;
}

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

void GiaiPhongDSCTHD(ListCTHD &dscthd) {
    while (dscthd != NULL) {
        NodeCTHD *temp = dscthd;
        dscthd = dscthd->next;
        delete temp;
    }
    dscthd = NULL;
}

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

void DocFileHoaDon(DanhSachNhanVien &dsNV) {
    ifstream f("HoaDon.txt", ios::in);
    if (!f.is_open()) return;

    string line;
    if (!getline(f, line) || line.empty()) {
        f.close();
        return;
    }
    int soLuongNVCoHD = stoi(line);

    for (int i = 0; i < soLuongNVCoHD; i++) {
        if (!getline(f, line)) break;
        stringstream ssNV(line);
        string maNV, strSoHD;
        getline(ssNV, maNV, '|');
        getline(ssNV, strSoHD, '|');
        int soLuongHD = stoi(strSoHD);

        int vtNV = -1;
        for (int k = 0; k < dsNV.soLuong; k++) {
            if (dsNV.ds[k]->MANV == maNV) {
                vtNV = k;
                break;
            }
        }

        for (int j = 0; j < soLuongHD; j++) {
            if (!getline(f, line)) break;
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

            hd.ngayLap.ngay = stoi(strNgay);
            hd.ngayLap.thang = stoi(strThang);
            hd.ngayLap.nam = stoi(strNam);
            hd.loai = strLoai[0];
            int soLuongCTHD = stoi(strSoCTHD);

            for (int k = 0; k < soLuongCTHD; k++) {
                if (!getline(f, line)) break;
                stringstream ssCT(line);
                string strSL, strDG, strVAT;
                ChiTietHoaDon ct;

                getline(ssCT, ct.MAVT, '|');
                getline(ssCT, strSL, '|');
                getline(ssCT, strDG, '|');
                getline(ssCT, strVAT, '|');

                ct.soLuong = stoi(strSL);
                ct.donGia = stod(strDG);
                ct.VAT = stof(strVAT);

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
// PHAN 3: UI, D?NH D?NG B?NG & TÍNH NANG CH?N V?T TU
// =========================================================

void ChuyenCayThanhMang(TreeVatTu root, VatTu ds[], int &n) {
    if (root != NULL) {
        ChuyenCayThanhMang(root->left, ds, n);
        ds[n++] = root->data;
        ChuyenCayThanhMang(root->right, ds, n);
    }
}

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

bool ChonVatTuTuBang(TreeVatTu root, VatTu &vtChon) {
    VatTu ds[500];
    int count = 0;
    ChuyenCayThanhMang(root, ds, count);

    if (count == 0) return false;

    system("cls");
    int boxX = 12, boxY = 1, boxW = 98, boxH = 25;
    drawBox(boxX, boxY, boxW, boxH, 14);

    InIntroBanner(boxX, boxY, "DANH MUC VAT TU KHO", boxW);

    gotoxy(boxX + 3, boxY + 5);
    textcolor(11);
    cout << left << setw(5) << "STT" << "| "
         << setw(10) << "Ma VT" << "| "
         << setw(35) << "Ten Vat Tu" << "| "
         << setw(10) << "DVT" << "| "
         << "Ton Kho";

    gotoxy(boxX + 2, boxY + 6);
    cout << "---------------------------------------------------------------------------------------------";

    int selectedIdx = 0;
    int topIdx = 0;
    int pageSize = 12;
    int rowWidthMax = boxW - 5;

    ShowConsoleCursor(false);

    auto InDongVatTu = [&](int idx, int printY, bool isSelected) {
        stringstream ss;
        ss << left << setw(5) << (idx + 1) << "| "
           << setw(10) << ds[idx].MAVT << "| "
           << setw(35) << ds[idx].TENVT << "| "
           << setw(10) << ds[idx].DVT << "| "
           << left << setw(10) << ds[idx].soLuongTon;
           
        string text = ss.str();
        while (text.length() < rowWidthMax) text += " ";

        gotoxy(boxX + 3, printY);
        if (isSelected) textcolor(31); 
        else textcolor(11);
        cout << text;
        textcolor(11); 
    };

    auto VeTrang = [&]() {
        for (int i = 0; i < pageSize; i++) {
            int currIdx = topIdx + i;
            int printY = boxY + 7 + i;
            clearLine(boxX + 3, printY, rowWidthMax);
            if (currIdx < count) {
                InDongVatTu(currIdx, printY, currIdx == selectedIdx);
            }
        }
        textcolor(14);
        gotoxy(boxX + 3, boxY + 20);
        clearLine(boxX + 3, boxY + 20, rowWidthMax);
        cout << "[Trang " << (topIdx / pageSize) + 1 << "/" << ((count - 1) / pageSize) + 1 << "]";
    };

    VeTrang();

    textcolor(10);
    gotoxy(boxX + 3, boxY + 22);
    cout << "[Mui ten Len/Xuong]: Di Chuyen Dong | [Mui ten Trai/Phai]: Chuyen Trang";
    gotoxy(boxX + 3, boxY + 23);
    cout << "[Enter]: Them Vat Tu Nay Vao Hoa Don | [ESC]: Huy Bo & Quay Lai";
    textcolor(11);

    while (true) {
        char key = _getch();
        if (key == -32 || key == 224) {
            key = _getch();
            int prevIdx = selectedIdx;

            if (key == 72) { 
                if (selectedIdx > 0) selectedIdx--;
            } else if (key == 80) { 
                if (selectedIdx < count - 1) selectedIdx++;
            } else if (key == 75) { 
                if (topIdx > 0) {
                    selectedIdx = max(0, selectedIdx - pageSize);
                    topIdx = max(0, topIdx - pageSize);
                    VeTrang();
                    continue;
                }
            } else if (key == 77) { 
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
                    int prevY = boxY + 7 + (prevIdx - topIdx);
                    InDongVatTu(prevIdx, prevY, false);

                    int currY = boxY + 7 + (selectedIdx - topIdx);
                    InDongVatTu(selectedIdx, currY, true);
                }
            }
        } else if (key == 13) {
            vtChon = ds[selectedIdx];
            return true;
        } else if (key == 27) {
            return false;
        }
    }
}

// =========================================================
// PHAN 4: GIAO DIEN CHINH LAP HOA DON (CAU E - H? TR? PHÍM ESC THOÁT)
// =========================================================

void giaodienLapHoaDon(DanhSachNhanVien &dsNV, TreeVatTu &root) {
    system("cls");
    HoaDon hdTam;
    hdTam.dscthd = NULL;

    int boxX = 12, boxY = 1, boxW = 98, boxH = 26;
    drawBox(boxX, boxY, boxW, boxH, 14);

    InIntroBanner(boxX, boxY, "HE THONG LAP HOA DON NHAP / XUAT KHO", boxW);

    // Dòng hu?ng d?n thoát chung ? du?i khung
    textcolor(10);
    gotoxy(boxX + 3, boxY + 24);
    cout << "[Luu y: Bam phim ESC bat c? luc nao de huy va thoat ve Menu]";

    // BUOC 1: NHAP MA NHAN VIEN (H? TR? ESC)
    int vtNV = -1;
    string maNV = "";
    while (true) {
        clearLine(boxX + 3, boxY + 5, 80);
        clearLine(boxX + 3, boxY + 6, 80);

        textcolor(11);
        gotoxy(boxX + 3, boxY + 5);
        cout << "1. Nhap Ma Nhan Vien: ";

        ShowConsoleCursor(true);
        // Ki?m tra phím ESC khi nh?p ID nhân viên
        char chFirst = _getch();
        if (chFirst == 27) { GiaiPhongDSCTHD(hdTam.dscthd); return; }
        
        string restID = NhapMaID(10); // Hàm Nh?p mã nh?n chu?i ti?p theo
        maNV = chFirst + restID;

        vtNV = TimkiemNhanVien(dsNV, maNV);
        if (vtNV == -1) {
            textcolor(12);
            gotoxy(boxX + 3, boxY + 6);
            cout << "=> LOI: Ma nhan vien '" << maNV << "' khong ton tai! Nhan phim bat ky nhap lai (ESC de thoat).";
            textcolor(11);
            char k = _getch();
            if (k == 27) { GiaiPhongDSCTHD(hdTam.dscthd); return; }
        } else {
            textcolor(10);
            gotoxy(boxX + 3, boxY + 6);
            cout << "=> Nhan Vien: " << dsNV.ds[vtNV]->HO << " " << dsNV.ds[vtNV]->TEN;
            textcolor(11);
            break;
        }
    }

    // BUOC 2: NHAP SO HOA DON (H? TR? ESC)
    while (true) {
        clearLine(boxX + 3, boxY + 8, 80);
        clearLine(boxX + 3, boxY + 9, 80);

        textcolor(11);
        gotoxy(boxX + 3, boxY + 8);
        cout << "2. Nhap So Hoa Don: ";

        ShowConsoleCursor(true);
        char chFirst = _getch();
        if (chFirst == 27) { GiaiPhongDSCTHD(hdTam.dscthd); return; }

        string restHD = NhapMaID(20);
        string soHD = chFirst + restHD;

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
            gotoxy(boxX + 3, boxY + 9);
            cout << "=> LOI: So hoa don '" << soHD << "' da ton tai! Nhan phim bat ky de nhap lai (ESC de thoat).";
            textcolor(11);
            char k = _getch();
            if (k == 27) { GiaiPhongDSCTHD(hdTam.dscthd); return; }
        } else {
            hdTam.soHD = soHD;
            textcolor(10);
            gotoxy(boxX + 3, boxY + 9);
            cout << "=> So Hoa Don hop le!";
            textcolor(11);
            break;
        }
    }

    // BUOC 3: FORM NHAP NGAY, THANG, NAM & LOAI HD (H? TR? ESC)
    string strNgay = "", strThang = "", strNam = "", strLoai = "N";
    int activeField = 0;

    textcolor(11);
    gotoxy(boxX + 3, boxY + 11); cout << "3. Ngay Lap    : ";
    gotoxy(boxX + 3, boxY + 12); cout << "4. Thang Lap   : ";
    gotoxy(boxX + 3, boxY + 13); cout << "5. Nam Lap     : ";
    gotoxy(boxX + 3, boxY + 14); cout << "6. Loai Hoa Don (N: Nhap kho / X: Xuat kho): ";

    textcolor(11);
    gotoxy(boxX + 3, boxY + 16);
    cout << "[>>> ENTER DE XAC NHAN THONG TIN NGAY & LOAI HOA DON | ESC DE THOAT <<<]";

    while (true) {
        gotoxy(boxX + 20, boxY + 11); cout << left << setw(10) << strNgay;
        gotoxy(boxX + 20, boxY + 12); cout << left << setw(10) << strThang;
        gotoxy(boxX + 20, boxY + 13); cout << left << setw(10) << strNam;
        gotoxy(boxX + 48, boxY + 14); cout << left << setw(5) << strLoai;

        if (activeField == 4) {
            textcolor(31);
            gotoxy(boxX + 3, boxY + 16);
            cout << "[>>> ENTER DE XAC NHAN THONG TIN NGAY & LOAI HOA DON | ESC DE THOAT <<<]";
            textcolor(11);
        } else {
            textcolor(11);
            gotoxy(boxX + 3, boxY + 16);
            cout << "[>>> ENTER DE XAC NHAN THONG TIN NGAY & LOAI HOA DON | ESC DE THOAT <<<]";
        }

        ShowConsoleCursor(true);
        if (activeField == 0) gotoxy(boxX + 20 + strNgay.length(), boxY + 11);
        else if (activeField == 1) gotoxy(boxX + 20 + strThang.length(), boxY + 12);
        else if (activeField == 2) gotoxy(boxX + 20 + strNam.length(), boxY + 13);
        else if (activeField == 3) gotoxy(boxX + 48 + strLoai.length(), boxY + 14);
        else if (activeField == 4) gotoxy(boxX + 3, boxY + 16);

        char c = _getch();

        if (c == 27) { // B?m ESC b?t c? lúc nào ? bu?c này d? thoát
            GiaiPhongDSCTHD(hdTam.dscthd);
            return;
        }

        if (c == -32 || c == 224) {
            char key = _getch();
            if (key == 72) activeField = (activeField - 1 + 5) % 5;
            else if (key == 80) activeField = (activeField + 1) % 5;
            continue;
        }

        if (c == 8) {
            if (activeField == 0 && !strNgay.empty()) strNgay.pop_back();
            else if (activeField == 1 && !strThang.empty()) strThang.pop_back();
            else if (activeField == 2 && !strNam.empty()) strNam.pop_back();
            continue;
        }

        if (c == 13) {
            if (activeField < 4) {
                activeField++;
            } else {
                int ng = strNgay.empty() ? 0 : stoi(strNgay);
                int th = strThang.empty() ? 0 : stoi(strThang);
                int na = strNam.empty() ? 0 : stoi(strNam);

                if (!ngayhople(ng, th, na)) {
                    textcolor(12);
                    gotoxy(boxX + 3, boxY + 18);
                    cout << "=> LOI: Ngay " << ng << "/" << th << "/" << na << " khong hop le!";
                    textcolor(11);
                    _getch();
                    clearLine(boxX + 3, boxY + 18, 75);
                    activeField = 0;
                } else {
                    hdTam.ngayLap.ngay = ng;
                    hdTam.ngayLap.thang = th;
                    hdTam.ngayLap.nam = na;
                    hdTam.loai = strLoai[0];
                    textcolor(10);
                    gotoxy(boxX + 3, boxY + 18);
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
        }
    }

    // BUOC 4: CHI TIET HOA DON TAM VA THAO TAC MENU (TÍCH H?P PHÂN TRANG UI)
    int menuSelected = 0;
    int currentPage = 1;
    int pageSize = 6;
    
    while (true) {
        vector<ChiTietHoaDon> dsCT;
        NodeCTHD* pNode = hdTam.dscthd;
        double tongTien = 0;
        while (pNode != NULL) {
            dsCT.push_back(pNode->data);
            tongTien += pNode->data.soLuong * pNode->data.donGia * (1.0 + pNode->data.VAT / 100.0);
            pNode = pNode->next;
        }
        
        int totalItems = (int)dsCT.size();
        int totalPages = max(1, (totalItems + pageSize - 1) / pageSize);
        if (currentPage > totalPages) currentPage = totalPages;

        system("cls");
        drawBox(boxX, boxY, boxW, boxH, 14);

        InIntroBanner(boxX, boxY, "HOA DON: " + hdTam.soHD + " | NV: " + dsNV.ds[vtNV]->TEN + " | LOAI: " + (hdTam.loai == 'N' ? "NHAP KHO" : "XUAT KHO"), boxW);

        gotoxy(boxX + 3, boxY + 5);
        textcolor(11);
        cout << left << setw(4) << "STT" << "| "
             << setw(8) << "Ma VT" << "| "
             << setw(22) << "Ten Vat Tu" << "| "
             << setw(6) << "DVT" << "| "
             << setw(5) << "SL" << "| "
             << setw(11) << "Don Gia" << "| "
             << setw(6) << "VAT" << "| "
             << "Thanh Tien";

        gotoxy(boxX + 2, boxY + 6);
        cout << "---------------------------------------------------------------------------------------------";

        auto VeTrangItems = [&]() {
            int startIndex = (currentPage - 1) * pageSize;
            int endIndex = min(startIndex + pageSize, totalItems);
            int printY = boxY + 7;
            cout << fixed << setprecision(0);

            for (int i = 0; i < pageSize; i++) {
                gotoxy(boxX + 3, printY + i);
                clearLine(boxX + 3, printY + i, boxW - 5);
                if (startIndex + i < totalItems) {
                    int idx = startIndex + i;
                    string tenVT = "N/A", dvt = "N/A";
                    NodeVatTu* nodeVT = TimKiemVatTu(root, dsCT[idx].MAVT);
                    if (nodeVT != NULL) { tenVT = nodeVT->data.TENVT; dvt = nodeVT->data.DVT; }
                    
                    double tt = dsCT[idx].soLuong * dsCT[idx].donGia * (1.0 + dsCT[idx].VAT / 100.0);

                    textcolor(11);
                    cout << left << setw(4) << (idx + 1) << "| "
                         << setw(8) << dsCT[idx].MAVT << "| "
                         << setw(22) << tenVT << "| "
                         << setw(6) << dvt << "| "
                         << setw(5) << dsCT[idx].soLuong << "| "
                         << setw(11) << (long long)dsCT[idx].donGia << "| "
                         << setw(6) << (to_string((int)dsCT[idx].VAT) + "%") << "| "
                         << (long long)tt;
                }
            }

            textcolor(14);
            gotoxy(boxX + 75, boxY + 14);
            clearLine(boxX + 75, boxY + 14, 20);
            cout << "[Trang " << currentPage << "/" << totalPages << "]";
        };

        VeTrangItems();

        gotoxy(boxX + 2, boxY + 13);
        textcolor(11);
        cout << "=============================================================================================";
        gotoxy(boxX + 3, boxY + 14);
        textcolor(10);
        cout << "TONG CONG TAM TINH: " << (long long)tongTien << " VND";
        
        string items[4] = {
            "1. Them Vat Tu Vao Hoa Don (Mo Bang Chon)",
            "2. Xoa Chi Tiet Vat Tu Trong Hoa Don",
            "3. CHOT LUU HOA DON XUONG HE THONG",
            "4. HUY LAP HOA DON (XOA DU LIEU TAM)"
        };

        auto VeMenu = [&]() {
            for (int i = 0; i < 4; i++) {
                gotoxy(boxX + 5, boxY + 16 + i);
                string text = (i == menuSelected ? "=> " : "   ") + items[i];
                while(text.length() < 60) text += " ";
                if (i == menuSelected) { textcolor(31); cout << text; }
                else { textcolor(11); cout << text; }
                textcolor(11);
            }
        };

        VeMenu();

        ShowConsoleCursor(false);
        int choice = 0;
        
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

        if (choice == 1) {
            VatTu vtChon;
            if (ChonVatTuTuBang(root, vtChon)) {
                if (KiemTraTrungVatTuTrongGio(hdTam.dscthd, vtChon.MAVT)) {
                    textcolor(12);
                    gotoxy(boxX + 3, boxY + 22);
                    cout << "=> LOI: Vat tu '" << vtChon.MAVT << "' da co trong hoa don!";
                    textcolor(11);
                    _getch();
                    continue;
                }

                system("cls");
                drawBox(boxX, boxY, boxW, boxH, 14);

                InIntroBanner(boxX, boxY, "THEM VAT TU: [" + vtChon.MAVT + " - " + vtChon.TENVT + "]", boxW);

                textcolor(11);
                gotoxy(boxX + 3, boxY + 5);
                cout << "So luong ton hien co: " << vtChon.soLuongTon << " " << vtChon.DVT;

                textcolor(11);
                gotoxy(boxX + 3, boxY + 7); cout << "Nhap So Luong: ";
                gotoxy(boxX + 3, boxY + 9); cout << "Nhap Don Gia : ";
                gotoxy(boxX + 3, boxY + 10); cout << "Nhap % VAT   : ";

                textcolor(11);
                gotoxy(boxX + 3, boxY + 12);
                cout << "[>>> ENTER DE THEM VAT TU VAO HOA DON | ESC DE HUY <<<]";

                string strSL = "1", strDG = "100000", strVAT = "10";
                int subField = 0;

                while (true) {
                    gotoxy(boxX + 18, boxY + 7);  cout << left << setw(15) << strSL;
                    gotoxy(boxX + 18, boxY + 9);  cout << left << setw(15) << strDG;
                    gotoxy(boxX + 18, boxY + 10); cout << left << setw(15) << strVAT;

                    if (subField == 3) {
                        textcolor(31);
                        gotoxy(boxX + 3, boxY + 12);
                        cout << "[>>> ENTER DE THEM VAT TU VAO HOA DON | ESC DE HUY <<<]";
                        textcolor(11);
                    } else {
                        textcolor(11);
                        gotoxy(boxX + 3, boxY + 12);
                        cout << "[>>> ENTER DE THEM VAT TU VAO HOA DON | ESC DE HUY <<<]";
                    }

                    ShowConsoleCursor(true);
                    if (subField == 0) gotoxy(boxX + 18 + strSL.length(), boxY + 7);
                    else if (subField == 1) gotoxy(boxX + 18 + strDG.length(), boxY + 9);
                    else if (subField == 2) gotoxy(boxX + 18 + strVAT.length(), boxY + 10);
                    else if (subField == 3) gotoxy(boxX + 3, boxY + 12);

                    char k = _getch();
                    if (k == 27) break; // Thoát form nh?p v?t tu con

                    if (k == -32 || k == 224) {
                        char subKey = _getch();
                        if (subKey == 72) subField = (subField - 1 + 4) % 4;
                        else if (subKey == 80) subField = (subField + 1) % 4;
                        continue;
                    }

                    if (k == 8) {
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
                                gotoxy(boxX + 3, boxY + 14);
                                cout << "=> LOI: So luong phai lon hon 0!";
                                textcolor(11);
                                _getch();
                                clearLine(boxX + 3, boxY + 14, 75);
                                subField = 0;
                            } else if (hdTam.loai == 'X' && sl > vtChon.soLuongTon) {
                                textcolor(12);
                                gotoxy(boxX + 3, boxY + 14);
                                cout << "=> LOI: Vuot qua ton kho (Hien co: " << vtChon.soLuongTon << ")!";
                                textcolor(11);
                                _getch();
                                clearLine(boxX + 3, boxY + 14, 75);
                                subField = 0;
                            } else {
                                ChiTietHoaDon ct;
                                ct.MAVT = vtChon.MAVT;
                                ct.soLuong = sl;
                                ct.donGia = dg;
                                ct.VAT = v;

                                ThemCTHD(hdTam.dscthd, ct);

                                textcolor(10);
                                gotoxy(boxX + 3, boxY + 14);
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
        else if (choice == 2) {
            if (hdTam.dscthd == NULL) {
                textcolor(12);
                gotoxy(boxX + 3, boxY + 22); cout << "=> LOI: Danh sach chi tiet hien dang rong!";
                textcolor(11);
                _getch();
                continue;
            }
            ShowConsoleCursor(true);
            clearLine(boxX + 3, boxY + 22, 70);
            gotoxy(boxX + 3, boxY + 22); textcolor(11);
            cout << "Nhap Ma Vat Tu can xoa: ";
            string maXoa = NhapMaID(10);
            XoaCTHDTrongDSTam(hdTam.dscthd, maXoa);
        }
        else if (choice == 3) {
            if (hdTam.dscthd == NULL) {
                textcolor(12);
                gotoxy(boxX + 3, boxY + 22); cout << "=> LOI: Hoa don rong! Khong the luu.";
                textcolor(11);
                _getch();
                continue;
            }
            break; 
        }
        else if (choice == 4) {
            GiaiPhongDSCTHD(hdTam.dscthd);
            return;
        }
    }

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
    drawBox(boxX, boxY, boxW, boxH, 14);
    InIntroBanner(boxX, boxY, "THONG BAO HE THONG", boxW);
    textcolor(10);
    gotoxy(boxX + 3, boxY + 6);
    cout << "=> LAP HOA DON " << hdTam.soHD << " THANH CONG VA DA LUU HE THONG!";
    textcolor(11);
    gotoxy(boxX + 3, boxY + 8);
    cout << "Nhan phim bat ky de ve Menu...";
    _getch();
}

// =========================================================
// PHAN 5: GIAO DIEN CAU F - IN CHI TIET 1 HOA DON
// =========================================================

void giaodienInHoaDon(DanhSachNhanVien dsNV, TreeVatTu root) {
    system("cls");
    int boxX = 12, boxY = 1, boxW = 98, boxH = 26;
    drawBox(boxX, boxY, boxW, boxH, 14);

    InIntroBanner(boxX, boxY, "TRA CUU & IN CHI TIET HOA DON", boxW);

    textcolor(11);
    gotoxy(boxX + 3, boxY + 5);
    cout << "Nhap So Hoa Don can in (ESC de thoat): ";
    
    ShowConsoleCursor(true);
    // H? tr? thoát ESC ? ph?n tra c?u hóa don
    char chFirst = _getch();
    if (chFirst == 27) return;
    string restHD = NhapMaID(20);
    string soHD = chFirst + restHD;

    NodeHoaDon* hdTimThay = NULL;
    NhanVien* nvLap = NULL;

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
        gotoxy(boxX + 3, boxY + 7);
        cout << "=> LOI: So hoa don '" << soHD << "' khong ton tai trong he thong!";
        textcolor(11);
        gotoxy(boxX + 3, boxY + 9);
        cout << "Nhan phim bat ky de quay lai menu...";
        ShowConsoleCursor(false);
        _getch();
        return;
    }

    vector<ChiTietHoaDon> dsCT;
    double tongTriGia = 0;
    NodeCTHD* pCT = hdTimThay->data.dscthd;

    while (pCT != NULL) {
        dsCT.push_back(pCT->data);
        double thanhTien = pCT->data.soLuong * pCT->data.donGia * (1.0 + pCT->data.VAT / 100.0);
        tongTriGia += thanhTien;
        pCT = pCT->next;
    }

    int totalItems = (int)dsCT.size();
    int pageSize = 9; 
    int totalPages = max(1, (totalItems + pageSize - 1) / pageSize);

    int currentPage = 1;
    ShowConsoleCursor(false);

    while (true) {
        system("cls");
        drawBox(boxX, boxY, boxW, boxH, 14);

        string titleHD = "HOA DON " + string(hdTimThay->data.loai == 'N' ? "NHAP KHO" : "XUAT KHO") + " [" + hdTimThay->data.soHD + "]";
        InIntroBanner(boxX, boxY, titleHD, boxW);

        textcolor(11);
        gotoxy(boxX + 3, boxY + 5);
        cout << "So Hoa Don : " << left << setw(15) << hdTimThay->data.soHD;
        gotoxy(boxX + 45, boxY + 5);
        cout << "Ngay Lap : " << hdTimThay->data.ngayLap.ngay << "/"
                             << hdTimThay->data.ngayLap.thang << "/"
                             << hdTimThay->data.ngayLap.nam;

        gotoxy(boxX + 3, boxY + 6);
        cout << "Nhan Vien  : " << nvLap->HO << " " << nvLap->TEN 
             << " (Ma NV: " << nvLap->MANV << ")";

        gotoxy(boxX + 3, boxY + 8);
        cout << left << setw(4) << "STT" << "| "
             << setw(8) << "Ma VT" << "| "
             << setw(22) << "Ten Vat Tu" << "| "
             << setw(6) << "DVT" << "| "
             << setw(5) << "SL" << "| "
             << setw(11) << "Don Gia" << "| "
             << setw(6) << "VAT" << "| "
             << "Thanh Tien";

        gotoxy(boxX + 2, boxY + 9);
        cout << "---------------------------------------------------------------------------------------------";

        int startIndex = (currentPage - 1) * pageSize;
        int endIndex = min(startIndex + pageSize, totalItems);
        int printY = boxY + 10;

        cout << fixed << setprecision(0);

        for (int i = startIndex; i < endIndex; i++) {
            string tenVT = "N/A";
            string dvt = "N/A";

            NodeVatTu* nodeVT = TimKiemVatTu(root, dsCT[i].MAVT);
            if (nodeVT != NULL) {
                tenVT = nodeVT->data.TENVT;
                dvt = nodeVT->data.DVT;
            }

            double thanhTien = dsCT[i].soLuong * dsCT[i].donGia * (1.0 + dsCT[i].VAT / 100.0);

            gotoxy(boxX + 3, printY);
            textcolor(11);
            cout << left << setw(4) << (i + 1) << "| "
                 << setw(8) << dsCT[i].MAVT << "| "
                 << setw(22) << tenVT << "| "
                 << setw(6) << dvt << "| "
                 << setw(5) << dsCT[i].soLuong << "| "
                 << setw(11) << (long long)dsCT[i].donGia << "| "
                 << setw(6) << (to_string((int)dsCT[i].VAT) + "%") << "| "
                 << (long long)thanhTien;

            printY++;
        }

        gotoxy(boxX + 2, boxY + 21);
        textcolor(11);
        cout << "=============================================================================================";

        gotoxy(boxX + 3, boxY + 22);
        textcolor(10);
        cout << "TONG TRI GIA HOA DON: " << (long long)tongTriGia << " VND";

        textcolor(14);
        gotoxy(boxX + 3, boxY + 24);
        cout << "[<- Trai / Phai ->]: Trang " << currentPage << "/" << totalPages 
             << "  |  [Enter/ESC]: Quay Lai Menu";

        char key = _getch();
        if (key == -32 || key == 224) {
            char navKey = _getch();
            if (navKey == 75) { 
                if (currentPage > 1) currentPage--;
            } else if (navKey == 77) { 
                if (currentPage < totalPages) currentPage++;
            }
        } else if (key == 13 || key == 27) { 
            break;
        }
    }
}
