#include "HoaDon.h"
#include <iostream>
#include <fstream> 
#include <sstream>
#include <conio.h>
#include <cctype>
#include <iomanip>

using namespace std;

// =========================================================
// PHAN 1: CAC HAM BO TRO XU LY DANH SACH CHI TIET HOA DON
// =========================================================

// Ham tao node chi tiet hoa don m?i
NodeCTHD* TaoNodeCTHD(ChiTietHoaDon ct) {
    NodeCTHD* p = new NodeCTHD;
    if (p == NULL) return NULL;
    p->data = ct;
    p->next = NULL;
    return p;
}

// Ham them chi tiet vat tu vao dau danh sach tam
void ThemCTHD(ListCTHD &dscthd, ChiTietHoaDon ct) {
    NodeCTHD* p = TaoNodeCTHD(ct);
    if (p == NULL) return;
    p->next = dscthd;
    dscthd = p;
}

// Ham xoa 1 vat tu khoi danh sach chi tiet tam theo MAVT
void XoaCTHDTrongDSTam(ListCTHD &dscthd, string maVT) {
    if (dscthd == NULL) {
        cout << "Danh sach dang rong!\n";
        return;
    }

    NodeCTHD* kieu = dscthd;
    NodeCTHD* bfkieu = NULL;

    while (kieu != NULL && kieu->data.MAVT != maVT) {
        bfkieu = kieu;
        kieu = kieu->next;
    }

    if (kieu == NULL) {
        cout << "Khong tim thay maVT da nhap trong hoa don!\n";
        return;
    }

    if (bfkieu == NULL) {
        dscthd = dscthd->next;
    } else {
        bfkieu->next = kieu->next;
    }

    delete kieu;
    cout << "Da xoa vat tu thanh cong!\n";
}

// Ham giai phong bo nho danh sach chi tiet hoa don tam
void GiaiPhongDSCTHD(ListCTHD &dscthd) {
    while (dscthd != NULL) {
        NodeCTHD *temp = dscthd;
        dscthd = dscthd->next;
        delete temp;
    }
    dscthd = NULL;
}

// Ham kiem tra trung ma vat tu trong gio hang tam
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

    if (!f.is_open()) {
        cout << "Loi: Khong the mo file HoaDon.txt de ghi!\n";
        return;
    }

    int demNVCoHD = 0;
    for (int i = 0; i < dsNV.soLuong; i++) {
        if (dsNV.ds[i]->dshd != NULL) {
            demNVCoHD++;
        }
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
    cout << "Ghi file HoaDon.txt thanh cong!\n";
}

void DocFileHoaDon(DanhSachNhanVien &dsNV) {
    ifstream f("HoaDon.txt", ios::in);

    if (!f.is_open()) {
        cout << "Thong bao: Khong tim thay file HoaDon.txt!\n";
        return;
    }

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
    cout << "Doc file HoaDon.txt va tai du lieu thanh cong!\n";
}

// =========================================================
// PHAN 3: HAM CHINH LAP HOA DON (CAU E)
// =========================================================

void LapHoaDon(DanhSachNhanVien &dsNV, TreeVatTu &root) {
    // ---------------------------------------------------------
    // GIAI DOAN 1: KHOI TAO PHIEU TAM VA KIEM TRA NHAN VIEN
    // ---------------------------------------------------------
    HoaDon hdTam;
    hdTam.dscthd = NULL;

    cout << "\n=== LAP HOA DON NHAP / XUAT ===\n";
    cout << "Nhap Ma Nhan Vien lap hoa don: ";
    string maNV = NhapMaID(10);

    int vtNV = TimkiemNhanVien(dsNV, maNV);
    if (vtNV == -1) {
        cout << "Loi: Ma nhan vien khong ton tai trong he thong!\n";
        return;
    }

    // ---------------------------------------------------------
    // GIAI DOAN 2: NHAP VA KIEM TRA THONG TIN CHUNG HOA DON
    // ---------------------------------------------------------

    // 1. Nhap va kiem tra trung So Hoa Don
    while (true) {
        cout << "Nhap So Hoa Don (Toi da 20 ky tu): ";
        string soHD = NhapMaID(20);

        bool trunghd = false;
        for (int i = 0; i < dsNV.soLuong; i++) {
            NodeHoaDon* pHD = dsNV.ds[i]->dshd;
            while (pHD != NULL) {
                if (pHD->data.soHD == soHD) {
                    trunghd = true;
                    break;
                }
                pHD = pHD->next;
            }
            if (trunghd) break;
        }

        if (trunghd) {
            cout << "Loi: So hoa don da ton tai! Vui long nhap so khac.\n";
        } else {
            hdTam.soHD = soHD;
            break;
        }
    }

    // 2. Nhap va kiem tra Ngay / Thang / Nam
    while (true) {
        cout << "Nhap Ngay lap: ";  int ngay = nhapsonguyen();
        cout << "Nhap Thang lap: "; int thang = nhapsonguyen();
        cout << "Nhap Nam lap: ";   int nam = nhapsonguyen();

        if (ngayhople(ngay, thang, nam)) {
            hdTam.ngayLap.ngay = ngay;
            hdTam.ngayLap.thang = thang;
            hdTam.ngayLap.nam = nam;
            break;
        } else {
            cout << "Loi: Ngay thang nam khong hop le trong thuc te! Nhap lai.\n";
        }
    }

    // 3. Nhap Loai Hoa Don ('N' hoac 'X')
    while (true) {
        cout << "Nhap Loai hoa don (N: Nhap, X: Xuat): ";
        char loai = _getch();
        loai = toupper(static_cast<unsigned char>(loai));

        if (loai == 'N' || loai == 'X') {
            cout << loai << endl;
            hdTam.loai = loai;
            break;
        }
    }

    // ---------------------------------------------------------
    // GIAI DOAN 3: MENU CHI TIET HOA DON (GIO HANG TAM)
    // ---------------------------------------------------------
    while (true) {
        cout << "\n--- CHON THAO TAC CHI TIET HOA DON ---\n";
        cout << "1. Them vat tu vao hoa don\n";
        cout << "2. Xoa vat tu vua nhap\n";
        cout << "3. Chot LUU hoa don\n";
        cout << "4. HUY lap hoa don\n";
        cout << "Chon thao tac (1-4): ";
        int luaChon = nhapsonguyen();

        if (luaChon == 1) {
            cout << "Nhap Ma Vat Tu: ";
            string maVT = NhapMaID(10);

            NodeVatTu* nodeVT = TimKiemVatTu(root, maVT);
            if (nodeVT == NULL) {
                cout << "Loi: Ma vat tu khong ton tai trong danh muc!\n";
                continue;
            }

            if (KiemTraTrungVatTuTrongGio(hdTam.dscthd, maVT)) {
                cout << "Loi: Vat tu nay da co trong hoa don! Vui long xoa di nhap lai.\n";
                continue;
            }

            cout << "Nhap So Luong: ";
            int soLuong = nhapsonguyen();
            if (soLuong <= 0) {
                cout << "Loi: So luong phai lon hon 0!\n";
                continue;
            }

            if (hdTam.loai == 'X' && soLuong > nodeVT->data.soLuongTon) {
                cout << "Loi: So luong xuat vuot qua ton kho! So luong ton hien co: " 
                     << nodeVT->data.soLuongTon << endl;
                continue;
            }

            cout << "Nhap Don Gia: ";
            double donGia = nhapsothuc();
            cout << "Nhap % VAT: ";
            double vat = nhapsothuc();

            ChiTietHoaDon ct;
            ct.MAVT = maVT;
            ct.soLuong = soLuong;
            ct.donGia = donGia;
            ct.VAT = vat;

            ThemCTHD(hdTam.dscthd, ct);
            cout << "Da them vat tu " << maVT << " vao hoa don tam!\n";
        }
        else if (luaChon == 2) {
            if (hdTam.dscthd == NULL) {
                cout << "Loi: Hoa don tam hien dang rong!\n";
                continue;
            }

            cout << "Nhap Ma Vat Tu can xoa: ";
            string maVT = NhapMaID(10);

            XoaCTHDTrongDSTam(hdTam.dscthd, maVT);
        }
        else if (luaChon == 3) {
            if (hdTam.dscthd == NULL) {
                cout << "Loi: Hoa don chua co vat tu nao! Khong the luu.\n";
                continue;
            }
            break;
        }
        else if (luaChon == 4) {
            GiaiPhongDSCTHD(hdTam.dscthd);
            cout << "Da huy lap hoa don!\n";
            return;
        }
        else {
            cout << "Lua chon khong hop le! Vui long chon tu 1 den 4.\n";
        }
    }

    // ---------------------------------------------------------
    // GIAI DOAN 4: CAP NHAT TON KHO, MOC NOI DS VA LUU FILE
    // ---------------------------------------------------------

    // 1. Cap nhat so luong ton tren Cay Vat Tu
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

    // 2. Moc NodeHoaDon vao dau DSLK dshd cua Nhan Vien
    NodeHoaDon* pHD = new NodeHoaDon();
    pHD->data = hdTam;
    pHD->next = dsNV.ds[vtNV]->dshd;
    dsNV.ds[vtNV]->dshd = pHD;

    // 3. Luu xuong file du lieu
    LuuFileHoaDon(dsNV);
    LuuFileVatTu(root);

    cout << "\nLap hoa don " << hdTam.soHD << " thanh cong va da luu he thong!\n";
}

// =========================================================
// CAU F: IN CHI TIET 1 HOA DON DUA VAO SO HOA DON
// =========================================================
void InHoaDon(DanhSachNhanVien dsNV, TreeVatTu root) {
    cout << "\n=== IN CHI TIET HOA DON ===\n";
    cout << "Nhap So Hoa Don can in: ";
    string soHD = NhapMaID(20);

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
        cout << "Loi: So hoa don '" << soHD << "' khong ton tai trong he thong!\n";
        return;
    }

    cout << "\n---------------------------------------------------------------\n";
    cout << "                     HOA DON " 
         << (hdTimThay->data.loai == 'N' ? "NHAP KHO" : "XUAT KHO") << endl;
    cout << "So Hoa Don : " << hdTimThay->data.soHD << endl;
    cout << "Ngay lap   : " << hdTimThay->data.ngayLap.ngay << "/"
                           << hdTimThay->data.ngayLap.thang << "/"
                           << hdTimThay->data.ngayLap.nam << endl;
    cout << "Nhan vien  : " << nvLap->HO << " " << nvLap->TEN 
         << " (Ma NV: " << nvLap->MANV << ")\n";
    cout << "---------------------------------------------------------------\n";

    cout << "STT | Ma VT     | Ten Vat Tu             | DVT     | So Luong | Don Gia     | VAT(%) | Thanh Tien\n";
    cout << "---------------------------------------------------------------------------------------------------\n";

    NodeCTHD* pCT = hdTimThay->data.dscthd;
    int stt = 1;
    double tongTriGia = 0;

    // Ep dinh dang so thuc khong in d?ng e+006 va khong lay so thap phan
    cout << fixed << setprecision(0);

    while (pCT != NULL) {
        string tenVT = "N/A";
        string dvt = "N/A";

        NodeVatTu* nodeVT = TimKiemVatTu(root, pCT->data.MAVT);
        if (nodeVT != NULL) {
            tenVT = nodeVT->data.TENVT;
            dvt = nodeVT->data.DVT;
        }

        double thanhTien = pCT->data.soLuong * pCT->data.donGia * (1.0 + pCT->data.VAT / 100.0);
        tongTriGia += thanhTien;

        cout << stt++ << "   | "
             << pCT->data.MAVT << " | "
             << tenVT << " | "
             << dvt << " | "
             << pCT->data.soLuong << " | "
             << pCT->data.donGia << " | "
             << pCT->data.VAT << "% | "
             << thanhTien << endl;

        pCT = pCT->next;
    }

    cout << "---------------------------------------------------------------------------------------------------\n";
    // Doi VNÐ -> VND de khong bi loi font console
    cout << "TONG TRI GIA HOA DON: " << tongTriGia << " VND\n"; 
    cout << "---------------------------------------------------------------------------------------------------\n";
}
