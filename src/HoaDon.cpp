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
// PHAN 1: MODULE LOGIC XU LY DANH SACH LIEN KET & NGHIEP VU
// =========================================================

// Tao mot node chi tiet hoa don moi
NodeCTHD* TaoNodeCTHD(ChiTietHoaDon ct) {
    NodeCTHD* p = new NodeCTHD;
    if (p == NULL) return NULL;
    p->data = ct;
    p->next = NULL;
    return p;
}

// Them chi tiet hoa don vao dau danh sach lien ket don
void ThemCTHD(ListCTHD &dscthd, ChiTietHoaDon ct) {
    NodeCTHD* p = TaoNodeCTHD(ct);
    if (p == NULL) return;
    p->next = dscthd;
    dscthd = p;
}

// Xoa mot chi tiet vat tu khoi danh sach hoa don tam theo ma vat tu
void XoaCTHDTrongDSTam(ListCTHD &dscthd, string maVT) {
    if (dscthd == NULL) return;

    NodeCTHD* hienTai = dscthd;
    NodeCTHD* truocDo = NULL;

    while (hienTai != NULL && hienTai->data.MAVT != maVT) {
        truocDo = hienTai;
        hienTai = hienTai->next;
    }

    if (hienTai == NULL) return;

    if (truocDo == NULL) {
        dscthd = dscthd->next;
    } else {
        truocDo->next = hienTai->next;
    }

    delete hienTai;
}

// Giai phong toan bo bo nho danh sach chi tiet hoa don
void GiaiPhongDSCTHD(ListCTHD &dscthd) {
    while (dscthd != NULL) {
        NodeCTHD* tam = dscthd;
        dscthd = dscthd->next;
        delete tam;
    }
    dscthd = NULL;
}

// Kiem tra vat tu da co trong hoa don tam hay chua
bool KiemTraTrungVatTuTrongGio(ListCTHD head, const string& maVT) {
    NodeCTHD* p = head;
    while (p != NULL) {
        if (p->data.MAVT == maVT) return true;
        p = p->next;
    }
    return false;
}

// Kiem tra so hoa don da ton tai trong toan bo he thong hay chua
bool KiemTraTrungSoHoaDon(const DanhSachNhanVien &dsNV, const string &soHD) {
    for (int i = 0; i < dsNV.soLuong; i++) {
        NodeHoaDon* pHD = dsNV.ds[i]->dshd;
        while (pHD != NULL) {
            if (pHD->data.soHD == soHD) return true;
            pHD = pHD->next;
        }
    }
    return false;
}

// Tinh tong so mat hang va tong thanh tien (da bao gom VAT) cua mot hoa don
void TinhTongHoaDon(ListCTHD dscthd, int &tongSoMatHang, double &tongTien) {
    tongSoMatHang = 0;
    tongTien = 0;
    NodeCTHD* p = dscthd;
    while (p != NULL) {
        tongSoMatHang++;
        tongTien += p->data.soLuong * p->data.donGia * (1.0 + p->data.VAT / 100.0);
        p = p->next;
    }
}

// Cap nhat so luong ton kho tren cay BST sau khi chot luu hoa don
void CapNhatTonKhoSauKhiLuuHD(TreeVatTu &root, const HoaDon &hd) {
    NodeCTHD* pCT = hd.dscthd;
    while (pCT != NULL) {
        NodeVatTu* nodeVT = TimKiemVatTu(root, pCT->data.MAVT);
        if (nodeVT != NULL) {
            if (hd.loai == 'N') {
                nodeVT->data.soLuongTon += pCT->data.soLuong;
            } else if (hd.loai == 'X') {
                nodeVT->data.soLuongTon -= pCT->data.soLuong;
            }
        }
        pCT = pCT->next;
    }
}

// =========================================================
// PHAN 2: MODULE XU LY DOC / GHI FILE (HOADON.TXT)
// =========================================================

// Ghi toan bo danh sach hoa don cua nhan vien ra file HoaDon.txt
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
// PHAN 3: MODULE GIAO DIEN DUNG CHUNG & O NHAP CAN GIUA
// =========================================================

namespace {
    // Do rong ben trong cua cac o nhap don (dong nhat de tham my)
    const int RONG_O_NHAP_DON = 22;
    // Do rong ben trong cua cac o ngay / thang / nam / loai hoa don
    const int RONG_O_NHAP_NGAY = 10;

    // Dinh dang so tien co dau phay ngan cach hang nghin (VD: 11,000,000)
    string DinhDangTienHD(double soTien) {
        long long giaTri = (long long)(soTien + 0.5);
        string s = to_string(giaTri);
        string ketQua = "";
        int dem = 0;
        for (int i = (int)s.length() - 1; i >= 0; i--) {
            ketQua = s[i] + ketQua;
            dem++;
            if (dem % 3 == 0 && i > 0) {
                ketQua = "," + ketQua;
            }
        }
        return ketQua;
    }

    // Dinh dang ngay thang nam dd/mm/yyyy doc lap voi co cout (tranh loi dao so)
    string DinhDangNgayHD(int ngay, int thang, int nam) {
        string sNgay  = (ngay < 10 ? "0" : "") + to_string(ngay);
        string sThang = (thang < 10 ? "0" : "") + to_string(thang);
        return sNgay + "/" + sThang + "/" + to_string(nam);
    }

    // Ve khung vien doi gon gang cho cac chuc nang chi tiet
    void VeKhungChucNangHD(const string &tieuDeChinh, int chieuCao = 24) {
        int offsetX = getDynamicOffsetX();
        system("cls");
        drawBox(offsetX, OFFSET_Y, WIDTH + 1, chieuCao, 6, true);

        int tieuDeX = offsetX + (WIDTH - (int)tieuDeChinh.length()) / 2;
        gotoxy(tieuDeX, OFFSET_Y + 1);
        textcolor(14);
        cout << tieuDeChinh;

        textcolor(6);
        gotoxy(offsetX, OFFSET_Y + 2);
        cout << char(204) << string(WIDTH - 1, char(205)) << char(185);
        textcolor(15);
    }

    // In thanh huong dan phim tat o day khung
    void InThanhHuongDanHD(int x, int y, const string &noiDung) {
        clearLine(x, y, 93);
        gotoxy(x, y);
        textcolor(11); cout << "Dieu khien: ";
        textcolor(7);  cout << noiDung;
        textcolor(15);
    }

    // Hien thong bao loi hoac thanh cong tai dong chi dinh
    void InThongBaoHD(int x, int y, const string &thongBao, int mauChu = 12) {
        clearLine(x, y, 92);
        gotoxy(x, y);
        textcolor(mauChu);
        cout << thongBao;
        textcolor(15);
    }

    // Ve mot o nhap [ ... ] voi noi dung can giua, an con tro va chi to xanh phan chu da nhap
    void VeONhapCanGiua(int boxStartX, int y, int innerWidth, const string &noiDung, bool dangChon) {
        string txt = noiDung.substr(0, innerWidth);
        int len = (int)txt.length();
        int padLeft = (innerWidth - len) / 2;
        int padRight = innerWidth - len - padLeft;

        gotoxy(boxStartX, y);
        textcolor(dangChon ? 14 : 11);
        cout << "[";

        if (dangChon) {
            if (len == 0) {
                int leftEmpty = (innerWidth - 1) / 2;
                int rightEmpty = innerWidth - 1 - leftEmpty;
                textcolor(15); cout << string(leftEmpty, ' ');
                textcolor(31); cout << " ";
                textcolor(15); cout << string(rightEmpty, ' ');
            } else {
                textcolor(15); cout << string(padLeft, ' ');
                textcolor(31); cout << txt;
                textcolor(15); cout << string(padRight, ' ');
            }
        } else {
            textcolor(15);
            cout << string(padLeft, ' ') << txt << string(padRight, ' ');
        }

        textcolor(dangChon ? 14 : 11);
        cout << "]";
        textcolor(15);
        ShowConsoleCursor(false);
    }

    // Nhap chuoi trong o ngoac vuong can giua, ho tro ESC va Backspace
    bool NhapChuoiCanGiua(int boxStartX, int y, int innerWidth, string &ketQua,
                          size_t doDaiToiDa, bool vietHoa = false,
                          bool chiNhapSo = false, bool choPhepDauCham = false) {
        while (true) {
            VeONhapCanGiua(boxStartX, y, innerWidth, ketQua, true);
            int phim = _getch();

            if (phim == 27) { // ESC -> Huy nhap
                VeONhapCanGiua(boxStartX, y, innerWidth, ketQua, false);
                ShowConsoleCursor(false);
                return false;
            }
            if (phim == 13) { // ENTER -> Xac nhan
                VeONhapCanGiua(boxStartX, y, innerWidth, ketQua, false);
                ShowConsoleCursor(false);
                return true;
            }
            if (phim == 8) { // Backspace -> Xoa ky tu cuoi va tu dong can giua lai
                if (!ketQua.empty()) {
                    ketQua.pop_back();
                }
                continue;
            }
            if (phim == 0 || phim == 224 || phim == -32) {
                _getch(); // Bo qua phim mui ten
                continue;
            }

            if (ketQua.length() < doDaiToiDa && phim >= 32 && phim <= 126) {
                char kyTu = (char)phim;
                if (chiNhapSo && !isdigit((unsigned char)kyTu) && !(choPhepDauCham && kyTu == '.')) {
                    continue;
                }
                if (vietHoa) kyTu = (char)toupper((unsigned char)kyTu);
                ketQua += kyTu;
            }
        }
    }

    // Ve khung bang 8 cot chi tiet hoa don (Tong rong = 93 ky tu)
    // Cot: STT(4) | Ma VT(9) | Ten Vat Tu(24) | DVT(7) | SL(6) | Don Gia(12) | VAT(6) | Thanh Tien(16)
    void VeKhungBangChiTietHD(int boxX, int tableY, int soDongHienThi) {
        textcolor(3);
        gotoxy(boxX, tableY);
        cout << char(218) << string(4, char(196))  << char(194)
             << string(9, char(196))  << char(194)
             << string(24, char(196)) << char(194)
             << string(7, char(196))  << char(194)
             << string(6, char(196))  << char(194)
             << string(12, char(196)) << char(194)
             << string(6, char(196))  << char(194)
             << string(16, char(196)) << char(191);

        gotoxy(boxX, tableY + 1);
        textcolor(3);  cout << char(179);
        textcolor(14); cout << left  << setw(4)  << " STT";
        textcolor(3);  cout << char(179);
        textcolor(14); cout << left  << setw(9)  << " Ma VT";
        textcolor(3);  cout << char(179);
        textcolor(14); cout << left  << setw(24) << " Ten Vat Tu";
        textcolor(3);  cout << char(179);
        textcolor(14); cout << left  << setw(7)  << " DVT";
        textcolor(3);  cout << char(179);
        textcolor(14); cout << right << setw(5)  << "SL" << " ";
        textcolor(3);  cout << char(179);
        textcolor(14); cout << right << setw(11) << "Don Gia" << " ";
        textcolor(3);  cout << char(179);
        textcolor(14); cout << right << setw(5)  << "VAT" << " ";
        textcolor(3);  cout << char(179);
        textcolor(14); cout << right << setw(15) << "Thanh Tien" << " ";
        textcolor(3);  cout << char(179);

        gotoxy(boxX, tableY + 2);
        textcolor(3);
        cout << char(195) << string(4, char(196))  << char(197)
             << string(9, char(196))  << char(197)
             << string(24, char(196)) << char(197)
             << string(7, char(196))  << char(197)
             << string(6, char(196))  << char(197)
             << string(12, char(196)) << char(197)
             << string(6, char(196))  << char(197)
             << string(16, char(196)) << char(180);

        for (int i = 0; i < soDongHienThi; i++) {
            gotoxy(boxX, tableY + 3 + i);
            textcolor(3);
            cout << char(179) << string(4, ' ')  << char(179)
                 << string(9, ' ')  << char(179)
                 << string(24, ' ') << char(179)
                 << string(7, ' ')  << char(179)
                 << string(6, ' ')  << char(179)
                 << string(12, ' ') << char(179)
                 << string(6, ' ')  << char(179)
                 << string(16, ' ') << char(179);
        }

        gotoxy(boxX, tableY + 3 + soDongHienThi);
        textcolor(3);
        cout << char(192) << string(4, char(196))  << char(193)
             << string(9, char(196))  << char(193)
             << string(24, char(196)) << char(193)
             << string(7, char(196))  << char(193)
             << string(6, char(196))  << char(193)
             << string(12, char(196)) << char(193)
             << string(6, char(196))  << char(193)
             << string(16, char(196)) << char(217);
        textcolor(15);
    }

    // Do du lieu mot trang chi tiet hoa don vao khung bang 8 cot
    void DoDuLieuBangChiTietHD(int boxX, int tableY, int soDongHienThi, ListCTHD dscthd,
                               TreeVatTu root, int trangHienTai) {
        int viTriBatDau = (trangHienTai - 1) * soDongHienThi;
        NodeCTHD* pCurr = dscthd;
        for (int k = 0; k < viTriBatDau && pCurr != NULL; k++) {
            pCurr = pCurr->next;
        }

        for (int i = 0; i < soDongHienThi; i++) {
            int rowY = tableY + 3 + i;
            gotoxy(boxX, rowY);

            if (pCurr != NULL) {
                int stt = viTriBatDau + i + 1;
                string tenVT = "N/A", dvt = "N/A";
                NodeVatTu* nodeVT = TimKiemVatTu(root, pCurr->data.MAVT);
                if (nodeVT != NULL) {
                    tenVT = nodeVT->data.TENVT.substr(0, 22);
                    dvt = nodeVT->data.DVT.substr(0, 5);
                }

                double thanhTien = pCurr->data.soLuong * pCurr->data.donGia * (1.0 + pCurr->data.VAT / 100.0);
                string strDonGia = DinhDangTienHD(pCurr->data.donGia);
                string strThanhTien = DinhDangTienHD(thanhTien);
                string strVAT = to_string((int)pCurr->data.VAT) + "%";

                textcolor(3);  cout << char(179);
                textcolor(7);  cout << " " << left << setw(3) << stt;
                textcolor(3);  cout << char(179);
                textcolor(11); cout << " " << left << setw(8) << pCurr->data.MAVT;
                textcolor(3);  cout << char(179);
                textcolor(15); cout << " " << left << setw(23) << tenVT;
                textcolor(3);  cout << char(179);
                textcolor(7);  cout << " " << left << setw(6) << dvt;
                textcolor(3);  cout << char(179);
                textcolor(14); cout << right << setw(5) << pCurr->data.soLuong << " ";
                textcolor(3);  cout << char(179);
                textcolor(15); cout << right << setw(11) << strDonGia << " ";
                textcolor(3);  cout << char(179);
                textcolor(7);  cout << right << setw(5) << strVAT << " ";
                textcolor(3);  cout << char(179);
                textcolor(10); cout << right << setw(15) << strThanhTien << " ";
                textcolor(3);  cout << char(179);

                pCurr = pCurr->next;
            } else {
                textcolor(3);
                cout << char(179) << string(4, ' ')  << char(179)
                     << string(9, ' ')  << char(179)
                     << string(24, ' ') << char(179)
                     << string(7, ' ')  << char(179)
                     << string(6, ' ')  << char(179)
                     << string(12, ' ') << char(179)
                     << string(6, ' ')  << char(179)
                     << string(16, ' ') << char(179);
            }
        }
        textcolor(15);
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

// Giao dien bang chon vat tu tu kho (Ke khung ASCII 5 cot chuan dep)
bool ChonVatTuTuBang(TreeVatTu root, VatTu &vtChon) {
    VatTu ds[500];
    int tongVatTu = 0;
    ChuyenCayThanhMang(root, ds, tongVatTu);

    if (tongVatTu == 0) return false;

    int offsetX = getDynamicOffsetX();
    int boxX = offsetX + 3;
    int tableY = OFFSET_Y + 4;

    VeKhungChucNangHD("DANH MUC VAT TU TRONG KHO", 24);
    ShowConsoleCursor(false);

    // Ve khung bang 5 cot (Tong rong = 93 ky tu: 6 + 12 + 41 + 12 + 16 + 6 vien = 93)
    textcolor(3);
    gotoxy(boxX, tableY);
    cout << char(218) << string(6, char(196))  << char(194)
         << string(12, char(196)) << char(194)
         << string(41, char(196)) << char(194)
         << string(12, char(196)) << char(194)
         << string(16, char(196)) << char(191);

    gotoxy(boxX, tableY + 1);
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left  << setw(6)  << " STT";
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left  << setw(12) << " Ma VT";
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left  << setw(41) << " Ten Vat Tu";
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left  << setw(12) << " DVT";
    textcolor(3);  cout << char(179);
    textcolor(14); cout << right << setw(15) << "Ton Kho" << " ";
    textcolor(3);  cout << char(179);

    gotoxy(boxX, tableY + 2);
    textcolor(3);
    cout << char(195) << string(6, char(196))  << char(197)
         << string(12, char(196)) << char(197)
         << string(41, char(196)) << char(197)
         << string(12, char(196)) << char(197)
         << string(16, char(196)) << char(180);

    int pageSize = 12;
    gotoxy(boxX, tableY + 3 + pageSize);
    textcolor(3);
    cout << char(192) << string(6, char(196))  << char(193)
         << string(12, char(196)) << char(193)
         << string(41, char(196)) << char(193)
         << string(12, char(196)) << char(193)
         << string(16, char(196)) << char(217);

    int selectedIdx = 0;
    int topIdx = 0;

    // In mot dong vat tu trong bang
    auto InDongVatTu = [&](int idx, int rowY, bool dangChon) {
        gotoxy(boxX, rowY);
        if (idx < tongVatTu) {
            string tenVT = ds[idx].TENVT.substr(0, 39);
            if (dangChon) {
                textcolor(3);  cout << char(179);
                textcolor(31);
                cout << " " << left << setw(5)  << (idx + 1)
                     << " " << left << setw(12) << ds[idx].MAVT
                     << " " << left << setw(41) << tenVT
                     << " " << left << setw(12) << ds[idx].DVT
                     << right << setw(15) << ds[idx].soLuongTon << " ";
                textcolor(3);  cout << char(179);
            } else {
                textcolor(3);  cout << char(179);
                textcolor(7);  cout << " " << left << setw(5)  << (idx + 1);
                textcolor(3);  cout << char(179);
                textcolor(11); cout << " " << left << setw(11) << ds[idx].MAVT;
                textcolor(3);  cout << char(179);
                textcolor(15); cout << " " << left << setw(40) << tenVT;
                textcolor(3);  cout << char(179);
                textcolor(7);  cout << " " << left << setw(11) << ds[idx].DVT;
                textcolor(3);  cout << char(179);
                textcolor(ds[idx].soLuongTon > 0 ? 10 : 12);
                cout << right << setw(15) << ds[idx].soLuongTon << " ";
                textcolor(3);  cout << char(179);
            }
        } else {
            textcolor(3);
            cout << char(179) << string(6, ' ')  << char(179)
                 << string(12, ' ') << char(179)
                 << string(41, ' ') << char(179)
                 << string(12, ' ') << char(179)
                 << string(16, ' ') << char(179);
        }
        textcolor(15);
    };

    // Ve lai ca trang vat tu
    auto VeTrang = [&]() {
        for (int i = 0; i < pageSize; i++) {
            int currIdx = topIdx + i;
            InDongVatTu(currIdx, tableY + 3 + i, currIdx == selectedIdx);
        }
        int tongTrang = (tongVatTu - 1) / pageSize + 1;
        int trangHienTai = (topIdx / pageSize) + 1;
        gotoxy(boxX + 75, tableY + 4 + pageSize);
        textcolor(14);
        cout << "[Trang " << trangHienTai << "/" << tongTrang << "]   ";
        textcolor(15);
    };

    VeTrang();
    InThanhHuongDanHD(boxX, OFFSET_Y + 22, "Len/Xuong: Chon VT | Trai/Phai: Chuyen trang | ENTER: Chon | ESC: Quay lai");

    while (true) {
        int key = _getch();
        if (key == -32 || key == 224 || key == 0) {
            key = _getch();
            int prevIdx = selectedIdx;

            if (key == 72 && selectedIdx > 0) {
                selectedIdx--;
            } else if (key == 80 && selectedIdx < tongVatTu - 1) {
                selectedIdx++;
            } else if (key == 75 && topIdx > 0) {
                selectedIdx = max(0, selectedIdx - pageSize);
                topIdx = max(0, topIdx - pageSize);
                VeTrang();
                continue;
            } else if (key == 77 && topIdx + pageSize < tongVatTu) {
                selectedIdx = min(tongVatTu - 1, selectedIdx + pageSize);
                topIdx += pageSize;
                VeTrang();
                continue;
            }

            if (prevIdx != selectedIdx) {
                if (selectedIdx < topIdx || selectedIdx >= topIdx + pageSize) {
                    topIdx = (selectedIdx < topIdx) ? selectedIdx : (selectedIdx - pageSize + 1);
                    VeTrang();
                } else {
                    InDongVatTu(prevIdx, tableY + 3 + (prevIdx - topIdx), false);
                    InDongVatTu(selectedIdx, tableY + 3 + (selectedIdx - topIdx), true);
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
// PHAN 4: MODULE GIAO DIEN CAU E - LAP HOA DON NHAP / XUAT
// =========================================================

void giaodienLapHoaDon(DanhSachNhanVien &dsNV, TreeVatTu &root) {
    int offsetX = getDynamicOffsetX();
    int boxX = offsetX + 3;

    HoaDon hdTam;
    hdTam.dscthd = NULL;

    VeKhungChucNangHD("LAP HOA DON NHAP / XUAT KHO", 24);
    InThanhHuongDanHD(boxX, OFFSET_Y + 22, "ENTER: Xac nhan nhap | ESC: Huy lap hoa don & quay ve Menu chinh");

    // ---------------------------------------------------------
    // BUOC 1: NHAP MA NHAN VIEN & SO HOA DON (CON TRO CAN GIUA)
    // ---------------------------------------------------------
    drawBox(boxX, OFFSET_Y + 4, 93, 6, 3, false);
    gotoxy(boxX + 3, OFFSET_Y + 4);
    textcolor(14); cout << " BUOC 1: THONG TIN NHAN VIEN & SO HOA DON ";

    int oNhapBuoc1X = boxX + 29; // Toa do bat dau dau '[' cho ca 2 o nhap Buoc 1

    gotoxy(boxX + 4, OFFSET_Y + 6);
    textcolor(11); cout << "Ma Nhan Vien lap phieu : ";
    VeONhapCanGiua(oNhapBuoc1X, OFFSET_Y + 6, RONG_O_NHAP_DON, "", false);

    gotoxy(boxX + 4, OFFSET_Y + 8);
    textcolor(11); cout << "So Hoa Don moi         : ";
    VeONhapCanGiua(oNhapBuoc1X, OFFSET_Y + 8, RONG_O_NHAP_DON, "", false);

    int vtNV = -1;
    string maNV = "";
    while (true) {
        clearLine(oNhapBuoc1X + RONG_O_NHAP_DON + 3, OFFSET_Y + 6, 35);
        maNV = "";
        if (!NhapChuoiCanGiua(oNhapBuoc1X, OFFSET_Y + 6, RONG_O_NHAP_DON, maNV, 10, true)) {
            GiaiPhongDSCTHD(hdTam.dscthd);
            return;
        }

        vtNV = TimkiemNhanVien(dsNV, maNV);
        if (vtNV == -1) {
            InThongBaoHD(boxX + 4, OFFSET_Y + 18, "(!) Ma nhan vien '" + maNV + "' khong ton tai! Nhan phim bat ky de nhap lai...", 12);
            _getch();
            clearLine(boxX + 4, OFFSET_Y + 18, 88);
        } else {
            gotoxy(oNhapBuoc1X + RONG_O_NHAP_DON + 4, OFFSET_Y + 6);
            textcolor(10); cout << "-> NV: " << dsNV.ds[vtNV]->HO << " " << dsNV.ds[vtNV]->TEN;
            textcolor(15);
            break;
        }
    }

    while (true) {
        clearLine(oNhapBuoc1X + RONG_O_NHAP_DON + 3, OFFSET_Y + 8, 35);
        string soHD = "";
        if (!NhapChuoiCanGiua(oNhapBuoc1X, OFFSET_Y + 8, RONG_O_NHAP_DON, soHD, 20, true)) {
            GiaiPhongDSCTHD(hdTam.dscthd);
            return;
        }

        if (soHD.empty()) {
            InThongBaoHD(boxX + 4, OFFSET_Y + 18, "(!) So hoa don khong duoc de trong! Nhan phim bat ky de nhap lai...", 12);
            _getch();
            clearLine(boxX + 4, OFFSET_Y + 18, 88);
            continue;
        }

        if (KiemTraTrungSoHoaDon(dsNV, soHD)) {
            InThongBaoHD(boxX + 4, OFFSET_Y + 18, "(!) So hoa don '" + soHD + "' da ton tai! Vui long nhap ma khac...", 12);
            _getch();
            clearLine(boxX + 4, OFFSET_Y + 18, 88);
        } else {
            hdTam.soHD = soHD;
            gotoxy(oNhapBuoc1X + RONG_O_NHAP_DON + 4, OFFSET_Y + 8);
            textcolor(10); cout << "-> Hop le";
            textcolor(15);
            break;
        }
    }

    // ---------------------------------------------------------
    // BUOC 2: NHAP NGAY LAP & LOAI HOA DON (4 O RONG BANG NHAU)
    // ---------------------------------------------------------
    drawBox(boxX, OFFSET_Y + 11, 93, 6, 3, false);
    gotoxy(boxX + 3, OFFSET_Y + 11);
    textcolor(14); cout << " BUOC 2: NGAY LAP & LOAI PHIEU ";

    int oNgayX  = boxX + 32;
    int oThangX = boxX + 47;
    int oNamX   = boxX + 62;

    gotoxy(boxX + 4, OFFSET_Y + 13);
    textcolor(11); cout << "Ngay lap (dd / mm / yyyy) : ";
    gotoxy(oNgayX + RONG_O_NHAP_NGAY + 2, OFFSET_Y + 13);  textcolor(15); cout << " / ";
    gotoxy(oThangX + RONG_O_NHAP_NGAY + 2, OFFSET_Y + 13); textcolor(15); cout << " / ";

    gotoxy(boxX + 4, OFFSET_Y + 15);
    textcolor(11); cout << "Loai hoa don (N / X)      : ";
    gotoxy(oNgayX + RONG_O_NHAP_NGAY + 5, OFFSET_Y + 15);
    textcolor(8); cout << "(N: Nhap kho  |  X: Xuat kho)";

    InThanhHuongDanHD(boxX, OFFSET_Y + 22, "Mui ten: Chuyen o | Backspace: Xoa | ENTER: Tiep tuc | ESC: Huy ve Menu");

    string oNgayThangLoai[4] = { "", "", "", "N" };
    const int gioiHanO[4] = { 2, 2, 4, 1 };
    const int toaDoX[4]   = { oNgayX, oThangX, oNamX, oNgayX };
    const int toaDoY[4]   = { OFFSET_Y + 13, OFFSET_Y + 13, OFFSET_Y + 13, OFFSET_Y + 15 };
    int oDangChon = 0;

    while (true) {
        // Ve ca 4 o voi do rong trong bang nhau (RONG_O_NHAP_NGAY = 10) va to xanh phan chu da nhap
        for (int i = 0; i < 4; i++) {
            VeONhapCanGiua(toaDoX[i], toaDoY[i], RONG_O_NHAP_NGAY, oNgayThangLoai[i], i == oDangChon);
        }

        int phim = _getch();
        if (phim == 27) {
            ShowConsoleCursor(false);
            GiaiPhongDSCTHD(hdTam.dscthd);
            return;
        }
        if (phim == -32 || phim == 224 || phim == 0) {
            phim = _getch();
            if (phim == 75 || phim == 72) oDangChon = (oDangChon + 3) % 4;
            else if (phim == 77 || phim == 80) oDangChon = (oDangChon + 1) % 4;
            continue;
        }
        if (phim == 8) {
            if (!oNgayThangLoai[oDangChon].empty()) oNgayThangLoai[oDangChon].pop_back();
            continue;
        }
        if (oDangChon < 3 && phim >= '0' && phim <= '9') {
            if ((int)oNgayThangLoai[oDangChon].length() < gioiHanO[oDangChon]) {
                oNgayThangLoai[oDangChon] += (char)phim;
                if ((int)oNgayThangLoai[oDangChon].length() == gioiHanO[oDangChon]) oDangChon++;
            }
            continue;
        }
        if (oDangChon == 3) {
            char u = (char)toupper((unsigned char)phim);
            if (u == 'N' || u == 'X') {
                oNgayThangLoai[3] = string(1, u);
                continue;
            }
        }
        if (phim == 13) {
            if (oNgayThangLoai[0].empty() || oNgayThangLoai[1].empty() || oNgayThangLoai[2].empty()) {
                InThongBaoHD(boxX + 4, OFFSET_Y + 18, "(!) Vui long nhap day du ngay, thang, nam truoc khi tiep tuc!", 12);
                continue;
            }
            int ng = stoi(oNgayThangLoai[0]);
            int th = stoi(oNgayThangLoai[1]);
            int na = stoi(oNgayThangLoai[2]);

            if (!ngayhople(ng, th, na)) {
                InThongBaoHD(boxX + 4, OFFSET_Y + 18, "(!) Ngay " + DinhDangNgayHD(ng, th, na) + " khong ton tai!", 12);
                continue;
            }
            if (oNgayThangLoai[3] != "N" && oNgayThangLoai[3] != "X") {
                InThongBaoHD(boxX + 4, OFFSET_Y + 18, "(!) Loai hoa don chi duoc nhap N (Nhap) hoac X (Xuat)!", 12);
                oDangChon = 3;
                continue;
            }

            hdTam.ngayLap.ngay = ng;
            hdTam.ngayLap.thang = th;
            hdTam.ngayLap.nam = na;
            hdTam.loai = oNgayThangLoai[3][0];
            ShowConsoleCursor(false);
            break;
        }
    }

    // ---------------------------------------------------------
    // BUOC 3: MAN HINH GIO HANG CHI TIET HOA DON & CHOT LUU
    // ---------------------------------------------------------
    int menuSelected = 0;
    int currentPage = 1;
    const int pageSize = 6;
    int tableY = OFFSET_Y + 5;

    while (true) {
        int totalItems = 0;
        double tongTien = 0;
        TinhTongHoaDon(hdTam.dscthd, totalItems, tongTien);

        int totalPages = max(1, (totalItems + pageSize - 1) / pageSize);
        if (currentPage > totalPages) currentPage = totalPages;

        string loaiPhieuText = (hdTam.loai == 'N' ? "NHAP KHO" : "XUAT KHO");
        VeKhungChucNangHD("CHI TIET HOA DON [" + hdTam.soHD + "] - " + loaiPhieuText, 24);

        gotoxy(boxX, OFFSET_Y + 3);
        textcolor(11); cout << "Nhan vien: ";
        textcolor(15); cout << dsNV.ds[vtNV]->HO << " " << dsNV.ds[vtNV]->TEN << " (" << dsNV.ds[vtNV]->MANV << ")";

        gotoxy(boxX + 55, OFFSET_Y + 3);
        textcolor(11); cout << "Ngay lap: ";
        textcolor(14); cout << DinhDangNgayHD(hdTam.ngayLap.ngay, hdTam.ngayLap.thang, hdTam.ngayLap.nam);

        VeKhungBangChiTietHD(boxX, tableY, pageSize);
        DoDuLieuBangChiTietHD(boxX, tableY, pageSize, hdTam.dscthd, root, currentPage);

        int footerTableY = tableY + 3 + pageSize + 1;
        gotoxy(boxX, footerTableY);
        textcolor(11); cout << "TONG CONG TAM TINH: ";
        textcolor(10); cout << DinhDangTienHD(tongTien) << " VND";

        gotoxy(boxX + 78, footerTableY);
        textcolor(14); cout << "[Trang " << currentPage << "/" << totalPages << "]";

        int actionY = footerTableY + 2;
        drawBox(boxX, actionY, 93, 4, 3, false);
        gotoxy(boxX + 3, actionY);
        textcolor(14); cout << " THAO TAC HOA DON ";

        string tenNut[4] = {
            "[+] Them Vat Tu Vao Phieu",
            "[-] Xoa Vat Tu Khoi Phieu",
            "[V] CHOT LUU HOA DON",
            "[X] HUY BO HOA DON"
        };
        int nutX[4] = { boxX + 4, boxX + 48, boxX + 4, boxX + 48 };
        int nutY[4] = { actionY + 1, actionY + 1, actionY + 2, actionY + 2 };

        auto VeCacNutThaoTac = [&]() {
            for (int i = 0; i < 4; i++) {
                gotoxy(nutX[i], nutY[i]);
                if (i == menuSelected) {
                    textcolor(31);
                    cout << " > " << left << setw(34) << tenNut[i];
                } else {
                    int mau = (i == 0 ? 10 : (i == 1 ? 14 : (i == 2 ? 11 : 12)));
                    textcolor(15); cout << "   ";
                    textcolor(mau); cout << left << setw(34) << tenNut[i];
                }
            }
            textcolor(15);
        };

        VeCacNutThaoTac();
        InThanhHuongDanHD(boxX, OFFSET_Y + 22, "Mui ten: Chon thao tac / Chuyen trang | ENTER: Thuc hien");

        int choice = 0;
        while (true) {
            int key = _getch();
            if (key == -32 || key == 224 || key == 0) {
                key = _getch();
                if (key == 72 || key == 80) {
                    menuSelected = (menuSelected + 2) % 4;
                    VeCacNutThaoTac();
                } else if (key == 75) {
                    if (menuSelected % 2 == 1) { menuSelected--; VeCacNutThaoTac(); }
                    else if (currentPage > 1) {
                        currentPage--;
                        DoDuLieuBangChiTietHD(boxX, tableY, pageSize, hdTam.dscthd, root, currentPage);
                        gotoxy(boxX + 78, footerTableY); textcolor(14);
                        cout << "[Trang " << currentPage << "/" << totalPages << "]";
                    }
                } else if (key == 77) {
                    if (menuSelected % 2 == 0) { menuSelected++; VeCacNutThaoTac(); }
                    else if (currentPage < totalPages) {
                        currentPage++;
                        DoDuLieuBangChiTietHD(boxX, tableY, pageSize, hdTam.dscthd, root, currentPage);
                        gotoxy(boxX + 78, footerTableY); textcolor(14);
                        cout << "[Trang " << currentPage << "/" << totalPages << "]";
                    }
                }
            } else if (key == 13) {
                choice = menuSelected + 1;
                break;
            }
        }

        // Xu ly 4 thao tac gio hang
        if (choice == 1) { // Them vat tu
            VatTu vtChon;
            if (ChonVatTuTuBang(root, vtChon)) {
                if (KiemTraTrungVatTuTrongGio(hdTam.dscthd, vtChon.MAVT)) {
                    InThongBaoHD(boxX, OFFSET_Y + 21, "(!) Vat tu '" + vtChon.MAVT + "' da ton tai trong phieu! Hay xoa neu muon nhap lai.", 12);
                    _getch();
                    continue;
                }

                VeKhungChucNangHD("NHAP CHI TIET VAT TU: " + vtChon.MAVT + " - " + vtChon.TENVT, 24);
                drawBox(boxX, OFFSET_Y + 4, 93, 10, 3, false);
                gotoxy(boxX + 3, OFFSET_Y + 4);
                textcolor(14); cout << " THONG SO XUAT / NHAP ";

                gotoxy(boxX + 4, OFFSET_Y + 6);
                textcolor(11); cout << "Ton kho hien tai       : ";
                textcolor(10); cout << vtChon.soLuongTon << " " << vtChon.DVT;

                int oThongSoX = boxX + 29; // Thang hang voi cac o o Buoc 1
                gotoxy(boxX + 4, OFFSET_Y + 8);  textcolor(11); cout << "So luong               : ";
                gotoxy(boxX + 4, OFFSET_Y + 10); textcolor(11); cout << "Don gia (VND)          : ";
                gotoxy(boxX + 4, OFFSET_Y + 12); textcolor(11); cout << "Thue VAT (%)           : ";

                InThanhHuongDanHD(boxX, OFFSET_Y + 22, "Len/Xuong: Chuyen o | Backspace: Xoa | ENTER: Them vao phieu | ESC: Huy");

                string oChiTiet[3] = { "1", "100000", "10" };
                const int subY[3]  = { OFFSET_Y + 8, OFFSET_Y + 10, OFFSET_Y + 12 };
                const size_t maxKyTu[3] = { 8, 12, 5 };
                int subField = 0;

                while (true) {
                    // Ve 3 o thong so cung do rong RONG_O_NHAP_DON (22) va to xanh phan chu da nhap
                    for (int i = 0; i < 3; i++) {
                        VeONhapCanGiua(oThongSoX, subY[i], RONG_O_NHAP_DON, oChiTiet[i], i == subField);
                    }

                    int k = _getch();
                    if (k == 27) { ShowConsoleCursor(false); break; }
                    if (k == -32 || k == 224 || k == 0) {
                        k = _getch();
                        if (k == 72) subField = (subField + 2) % 3;
                        else if (k == 80) subField = (subField + 1) % 3;
                        continue;
                    }
                    if (k == 8) {
                        if (!oChiTiet[subField].empty()) oChiTiet[subField].pop_back();
                        continue;
                    }
                    if ((k >= '0' && k <= '9') || (subField > 0 && k == '.')) {
                        if (oChiTiet[subField].length() < maxKyTu[subField]) {
                            oChiTiet[subField] += (char)k;
                        }
                        continue;
                    }
                    if (k == 13) {
                        if (subField < 2) {
                            subField++;
                            continue;
                        }
                        int sl = oChiTiet[0].empty() ? 0 : stoi(oChiTiet[0]);
                        double dg = oChiTiet[1].empty() ? 0 : stod(oChiTiet[1]);
                        float vat = oChiTiet[2].empty() ? 0.0f : stof(oChiTiet[2]);

                        if (sl <= 0) {
                            InThongBaoHD(boxX + 4, OFFSET_Y + 15, "(!) So luong phai lon hon 0!", 12);
                            subField = 0;
                            continue;
                        }
                        if (hdTam.loai == 'X' && sl > vtChon.soLuongTon) {
                            InThongBaoHD(boxX + 4, OFFSET_Y + 15, "(!) Khong du ton kho de xuat (Hien con: " + to_string(vtChon.soLuongTon) + ")!", 12);
                            subField = 0;
                            continue;
                        }

                        ChiTietHoaDon ct;
                        ct.MAVT = vtChon.MAVT;
                        ct.soLuong = sl;
                        ct.donGia = dg;
                        ct.VAT = vat;
                        ThemCTHD(hdTam.dscthd, ct);

                        ShowConsoleCursor(false);
                        break;
                    }
                }
            }
        } else if (choice == 2) { // Xoa vat tu
            if (hdTam.dscthd == NULL) {
                InThongBaoHD(boxX, OFFSET_Y + 21, "(!) Phieu hien dang rong, khong co vat tu de xoa!", 12);
                _getch();
                continue;
            }
            clearLine(boxX, OFFSET_Y + 21, 90);
            gotoxy(boxX, OFFSET_Y + 21);
            textcolor(14); cout << "Nhap Ma VT can xoa     : ";
            string maXoa = "";
            if (NhapChuoiCanGiua(boxX + 25, OFFSET_Y + 21, RONG_O_NHAP_DON, maXoa, 10, true)) {
                XoaCTHDTrongDSTam(hdTam.dscthd, maXoa);
            }
        } else if (choice == 3) { // Chot luu hoa don
            if (hdTam.dscthd == NULL) {
                InThongBaoHD(boxX, OFFSET_Y + 21, "(!) Khong the luu hoa don rong! Vui long them it nhat 1 vat tu.", 12);
                _getch();
                continue;
            }
            break;
        } else if (choice == 4) { // Huy bo
            GiaiPhongDSCTHD(hdTam.dscthd);
            return;
        }
    }

    // Cap nhat ton kho, them hoa don vao nhan vien va luu xuong file
    CapNhatTonKhoSauKhiLuuHD(root, hdTam);

    NodeHoaDon* pHD = new NodeHoaDon();
    pHD->data = hdTam;
    pHD->next = dsNV.ds[vtNV]->dshd;
    dsNV.ds[vtNV]->dshd = pHD;

    LuuFileHoaDon(dsNV);
    LuuFileVatTu(root);

    VeKhungChucNangHD("HOAN TAT LAP HOA DON", 24);
    drawBox(offsetX + 18, OFFSET_Y + 8, 62, 7, 10, false);
    gotoxy(offsetX + 24, OFFSET_Y + 10);
    textcolor(10); cout << "DA LUU HOA DON [" << hdTam.soHD << "] THANH CONG!";
    gotoxy(offsetX + 24, OFFSET_Y + 12);
    textcolor(7);  cout << "Du lieu ton kho va hoa don da duoc cap nhat.";
    InThanhHuongDanHD(boxX, OFFSET_Y + 22, "Nhan phim bat ky de quay ve Menu chinh...");
    _getch();
}

// =========================================================
// PHAN 5: MODULE GIAO DIEN CAU F - IN CHI TIET 1 HOA DON
// =========================================================

void giaodienInHoaDon(DanhSachNhanVien dsNV, TreeVatTu root) {
    int offsetX = getDynamicOffsetX();
    int boxX = offsetX + 3;

    while (true) {
        NodeHoaDon* hdTimThay = NULL;
        NhanVien* nvLap = NULL;

        // Buoc 1: Nhap so hoa don can tra cuu (con tro o giua o vuong)
        while (true) {
            VeKhungChucNangHD("TRA CUU & IN CHI TIET HOA DON", 24);
            drawBox(boxX, OFFSET_Y + 4, 93, 5, 3, false);
            gotoxy(boxX + 3, OFFSET_Y + 4);
            textcolor(14); cout << " TIM KIEM HOA DON ";

            int oTimKiemX = boxX + 29;
            gotoxy(boxX + 4, OFFSET_Y + 6);
            textcolor(11); cout << "Nhap So Hoa Don        : ";

            InThanhHuongDanHD(boxX, OFFSET_Y + 22, "ENTER: Tim kiem hoa don | ESC: Quay ve Menu chinh");

            string soHD = "";
            if (!NhapChuoiCanGiua(oTimKiemX, OFFSET_Y + 6, RONG_O_NHAP_DON, soHD, 20, true)) return;
            if (soHD.empty()) return;

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
                InThongBaoHD(boxX + 4, OFFSET_Y + 11, "(!) Khong tim thay hoa don mang ma '" + soHD + "' trong he thong!", 12);
                gotoxy(boxX + 4, OFFSET_Y + 12);
                textcolor(7); cout << "Nhan phim bat ky de nhap lai hoac nhan ESC de thoat...";
                int k = _getch();
                if (k == 27) return;
            } else {
                break;
            }
        }

        // Buoc 2: Tinh tong tri gia hoa don va hien thi phieu chi tiet
        int totalItems = 0;
        double tongTriGia = 0;
        TinhTongHoaDon(hdTimThay->data.dscthd, totalItems, tongTriGia);

        const int pageSize = 8;
        int totalPages = max(1, (totalItems + pageSize - 1) / pageSize);
        int currentPage = 1;
        int tableY = OFFSET_Y + 8;
        bool traCuuTiep = false;

        ShowConsoleCursor(false);

        while (true) {
            string loaiText = (hdTimThay->data.loai == 'N' ? "PHIEU NHAP KHO" : "PHIEU XUAT KHO");
            VeKhungChucNangHD("CHI TIET " + loaiText + " [" + hdTimThay->data.soHD + "]", 24);

            // Khung thong tin chung bo tri 2 cot x 2 dong thoang mat, tham my
            drawBox(boxX, OFFSET_Y + 3, 93, 5, 3, false);
            gotoxy(boxX + 3, OFFSET_Y + 3);
            textcolor(14); cout << " THONG TIN CHUNG HOA DON ";

            // Dong 1: So Hoa Don (trai) & Ngay Lap (phai)
            gotoxy(boxX + 4, OFFSET_Y + 4);
            textcolor(11); cout << "So Hoa Don   : ";
            textcolor(14); cout << hdTimThay->data.soHD;

            gotoxy(boxX + 52, OFFSET_Y + 4);
            textcolor(11); cout << "Ngay Lap     : ";
            textcolor(15); cout << DinhDangNgayHD(hdTimThay->data.ngayLap.ngay,
                                                hdTimThay->data.ngayLap.thang,
                                                hdTimThay->data.ngayLap.nam);

            // Dong 2 (cach 1 dong cho thoang): Nhan Vien (trai) & Loai Phieu (phai)
            gotoxy(boxX + 4, OFFSET_Y + 6);
            textcolor(11); cout << "Nhan Vien    : ";
            textcolor(15); cout << nvLap->HO << " " << nvLap->TEN << " (" << nvLap->MANV << ")";

            gotoxy(boxX + 52, OFFSET_Y + 6);
            textcolor(11); cout << "Loai Phieu   : ";
            textcolor(hdTimThay->data.loai == 'N' ? 10 : 13);
            cout << (hdTimThay->data.loai == 'N' ? "NHAP KHO (N)" : "XUAT KHO (X)");

            // Ve bang 8 cot chi tiet hoa don
            VeKhungBangChiTietHD(boxX, tableY, pageSize);
            DoDuLieuBangChiTietHD(boxX, tableY, pageSize, hdTimThay->data.dscthd, root, currentPage);

            // Tong tri gia va chi so trang
            int footerY = tableY + 3 + pageSize + 1;
            gotoxy(boxX, footerY);
            textcolor(11); cout << "TONG TRI GIA HOA DON: ";
            textcolor(10); cout << DinhDangTienHD(tongTriGia) << " VND";

            gotoxy(boxX + 78, footerY);
            textcolor(14); cout << "[Trang " << currentPage << "/" << totalPages << "]";

            InThanhHuongDanHD(boxX, OFFSET_Y + 22, "Trai/Phai: Chuyen trang | ENTER: Tra cuu HD khac | ESC: Ve Menu");

            int key = _getch();
            if (key == -32 || key == 224 || key == 0) {
                int navKey = _getch();
                if (navKey == 75 && currentPage > 1) currentPage--;
                else if (navKey == 77 && currentPage < totalPages) currentPage++;
            } else if (key == 13) {
                traCuuTiep = true;
                break;
            } else if (key == 27) {
                return;
            }
        }

        if (!traCuuTiep) break;
    }
}
