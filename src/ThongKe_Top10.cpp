#include "ThongKe_Top10.h"
#include "UI.h"
#include "Validate.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>

using namespace std;

// ==========================================================
// PHAN 1: CAU TRUC DU LIEU VA CAC HAM TIEN ICH CO BAN
// ==========================================================

struct ThongKeVatTu {
    string MAVT;
    string TENVT;
    string DVT;
    int soLuongTon;
    double doanhThu;
};

// Do rong ben trong cua 6 o nhap ngay / thang / nam (dong nhat de tham my)
const int RONG_O_NGAY_TK = 6;

// Chuyen chuoi ky tu so thanh so nguyen (an toan cho moi trinh bien dich)
int chuyenChuoiSangSo(const string &chuoi) {
    if (chuoi.empty()) return 0;
    int ketQua = 0;
    for (int i = 0; i < (int)chuoi.length(); i++) {
        ketQua = ketQua * 10 + (chuoi[i] - '0');
    }
    return ketQua;
}

// Dinh dang so tien co dau phay ngan cach hang nghin (VD: 11,000,000)
string dinhDangTien(double soTien) {
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

// ==========================================================
// PHAN 2: MODULE XU LY LOGIC THONG KE (THUAN THUAT TOAN)
// ==========================================================

// Buoc 1: Duyet cay vat tu (LNR) va dua du lieu vao mang thong ke
void chuyenCayVatTuSangMang(TreeVatTu root, ThongKeVatTu dsTK[], int &soLuongVT) {
    if (root != NULL) {
        chuyenCayVatTuSangMang(root->left, dsTK, soLuongVT);

        dsTK[soLuongVT].MAVT = root->data.MAVT;
        dsTK[soLuongVT].TENVT = root->data.TENVT;
        dsTK[soLuongVT].DVT = root->data.DVT;
        dsTK[soLuongVT].soLuongTon = root->data.soLuongTon;
        dsTK[soLuongVT].doanhThu = 0;
        soLuongVT++;

        chuyenCayVatTuSangMang(root->right, dsTK, soLuongVT);
    }
}

// Buoc 2: Duyet toan bo hoa don Xuat trong khoang ngay va cong don doanh thu
void tinhDoanhThuVatTu(DanhSachNhanVien dsNV, ThongKeVatTu dsTK[], int soLuongVT,
                       int tuNgay, int tuThang, int tuNam,
                       int denNgay, int denThang, int denNam) {
    // Reset doanh thu ve 0 truoc moi lan thong ke
    for (int k = 0; k < soLuongVT; k++) {
        dsTK[k].doanhThu = 0;
    }

    // Duyet qua tung nhan vien
    for (int i = 0; i < dsNV.soLuong; i++) {
        NodeHoaDon* hoaDon = dsNV.ds[i]->dshd;

        // Duyet danh sach lien ket hoa don cua nhan vien thu i
        while (hoaDon != NULL) {
            int ngay = hoaDon->data.ngayLap.ngay;
            int thang = hoaDon->data.ngayLap.thang;
            int nam = hoaDon->data.ngayLap.nam;

            bool laHoaDonXuat = (hoaDon->data.loai == 'X');
            bool namTrongKhoangNgay = (sosanhngay(ngay, thang, nam, tuNgay, tuThang, tuNam) >= 0 &&
                                       sosanhngay(ngay, thang, nam, denNgay, denThang, denNam) <= 0);

            if (laHoaDonXuat && namTrongKhoangNgay) {
                NodeCTHD* chiTiet = hoaDon->data.dscthd;

                // Duyet danh sach chi tiet vat tu trong hoa don hop le
                while (chiTiet != NULL) {
                    double thanhTien = chiTiet->data.soLuong * chiTiet->data.donGia * (1.0 + chiTiet->data.VAT / 100.0);

                    // Tim ma vat tu tuong ung trong mang de cong don doanh thu
                    for (int k = 0; k < soLuongVT; k++) {
                        if (dsTK[k].MAVT == chiTiet->data.MAVT) {
                            dsTK[k].doanhThu += thanhTien;
                            break;
                        }
                    }
                    chiTiet = chiTiet->next;
                }
            }
            hoaDon = hoaDon->next;
        }
    }
}

// Buoc 3: Sap xep mang vat tu giam dan theo doanh thu
void sapXepDoanhThuGiamDan(ThongKeVatTu dsTK[], int soLuongVT) {
    for (int i = 0; i < soLuongVT - 1; i++) {
        bool coHoanDoi = false;
        for (int j = 0; j < soLuongVT - i - 1; j++) {
            if (dsTK[j].doanhThu < dsTK[j + 1].doanhThu) {
                ThongKeVatTu tam = dsTK[j];
                dsTK[j] = dsTK[j + 1];
                dsTK[j + 1] = tam;
                coHoanDoi = true;
            }
        }
        if (!coHoanDoi) break;
    }
}

// ==========================================================
// PHAN 3: MODULE GIAO DIEN VA TUONG TAC NGUOI DUNG (UI)
// ==========================================================

// Ve khung bao ngoai gon gang cho chuc nang chi tiet (khong co ten thanh vien & header truong)
void veKhungChucNangGon(int offsetX) {
    system("cls");
    drawBox(offsetX, OFFSET_Y, WIDTH + 1, 24, 6, true);

    string tieuDe = "THONG KE TOP 10 VAT TU CO DOANH THU CAO NHAT";
    int tieuDeX = offsetX + (WIDTH - (int)tieuDe.length()) / 2;
    gotoxy(tieuDeX, OFFSET_Y + 1);
    textcolor(14);
    cout << tieuDe;

    textcolor(6);
    gotoxy(offsetX, OFFSET_Y + 2);
    cout << char(204) << string(WIDTH - 1, char(205)) << char(185);
    textcolor(15);
}

// Ve mot o nhap [ ... ] can giua, an con tro va chi to xanh phan chu da nhap
void veONhapNgayCanGiua(int boxStartX, int y, int innerWidth, const string &noiDung, bool dangChon) {
    string txt = noiDung.substr(0, innerWidth);
    int len = (int)txt.length();
    int padLeft = (innerWidth - len) / 2;
    int padRight = innerWidth - len - padLeft;

    gotoxy(boxStartX, y);
    textcolor(dangChon ? 14 : 11);
    cout << "[";

    if (dangChon) {
        if (len == 0) {
            // Khi o trong: hien 1 diem xanh nho o giua de biet dang chon o nao
            int leftEmpty = (innerWidth - 1) / 2;
            int rightEmpty = innerWidth - 1 - leftEmpty;
            textcolor(15); cout << string(leftEmpty, ' ');
            textcolor(31); cout << " ";
            textcolor(15); cout << string(rightEmpty, ' ');
        } else {
            // Khi co chu: to xanh dung bang do dai chu da nhap
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

// Hien thi 6 o nhap ngay thang nam va highlight o dang chon
void veCacONhapNgay(int boxX, int boxY, const string oNhap[6], int oDangChon) {
    int oNgayX  = boxX + 32;
    int oThangX = boxX + 43;
    int oNamX   = boxX + 54;

    const int toaDoX[6] = { oNgayX, oThangX, oNamX, oNgayX, oThangX, oNamX };
    const int toaDoY[6] = { boxY + 1, boxY + 1, boxY + 1, boxY + 2, boxY + 2, boxY + 2 };

    for (int i = 0; i < 6; i++) {
        veONhapNgayCanGiua(toaDoX[i], toaDoY[i], RONG_O_NGAY_TK, oNhap[i], i == oDangChon);
    }
}

// Xu ly nhap khoang ngay bang phim mui ten, Backspace, Enter, ESC
// Tra ve true neu ngay hop le, tra ve false neu nguoi dung bam ESC de thoat
bool nhapKhoangNgayThongKe(int boxX, int boxY,
                            int &tuNgay, int &tuThang, int &tuNam,
                            int &denNgay, int &denThang, int &denNam) {
    drawBox(boxX, boxY, 92, 5, 3, false);
    gotoxy(boxX + 3, boxY);
    textcolor(14);
    cout << " NHAP KHOANG THOI GIAN THONG KE ";

    int oNgayX  = boxX + 32;
    int oThangX = boxX + 43;

    gotoxy(boxX + 4, boxY + 1);
    textcolor(11); cout << "Tu ngay  (dd / mm / yyyy) : ";
    gotoxy(oNgayX + RONG_O_NGAY_TK + 2, boxY + 1);  textcolor(15); cout << " / ";
    gotoxy(oThangX + RONG_O_NGAY_TK + 2, boxY + 1); textcolor(15); cout << " / ";

    gotoxy(boxX + 4, boxY + 2);
    textcolor(11); cout << "Den ngay (dd / mm / yyyy) : ";
    gotoxy(oNgayX + RONG_O_NGAY_TK + 2, boxY + 2);  textcolor(15); cout << " / ";
    gotoxy(oThangX + RONG_O_NGAY_TK + 2, boxY + 2); textcolor(15); cout << " / ";

    gotoxy(boxX + 2, boxY + 19);
    textcolor(11); cout << "Dieu khien: ";
    textcolor(7);  cout << "Mui ten: Di chuyen o | Backspace: Xoa | ENTER: Thong ke | ESC: Ve Menu";

    string oNhap[6] = { "", "", "", "", "", "" };
    const int gioiHanKyTu[6] = { 2, 2, 4, 2, 2, 4 };
    int oDangChon = 0;

    ShowConsoleCursor(false);

    while (true) {
        veCacONhapNgay(boxX, boxY, oNhap, oDangChon);
        int phim = _getch();

        // Xu ly phim dieu huong (Mui ten Trai, Phai, Len, Xuong)
        if (phim == -32 || phim == 224 || phim == 0) {
            phim = _getch();
            if (phim == 75) {        // Mui ten Trai
                oDangChon = (oDangChon + 5) % 6;
            } else if (phim == 77) { // Mui ten Phai
                oDangChon = (oDangChon + 1) % 6;
            } else if (phim == 72 || phim == 80) { // Mui ten Len / Xuong
                oDangChon = (oDangChon + 3) % 6;
            }
            continue;
        }

        // Phim ESC: Thoat chuc nang ve Menu Chinh
        if (phim == 27) {
            ShowConsoleCursor(false);
            return false;
        }

        // Phim Backspace: Xoa 1 ky tu o o hien tai
        if (phim == 8) {
            if (!oNhap[oDangChon].empty()) {
                oNhap[oDangChon].pop_back();
            }
            continue;
        }

        // Phim so 0-9: Nhap du lieu vao o hien tai
        if (phim >= '0' && phim <= '9') {
            if ((int)oNhap[oDangChon].length() < gioiHanKyTu[oDangChon]) {
                oNhap[oDangChon] += (char)phim;
                // Tu dong chuyen sang o ke tiep khi go du so ky tu
                if ((int)oNhap[oDangChon].length() == gioiHanKyTu[oDangChon] && oDangChon < 5) {
                    oDangChon++;
                }
            }
            continue;
        }

        // Phim ENTER: Kiem tra hop le va thuc hien thong ke
        if (phim == 13) {
            // Kiem tra xem co o nao bi de trong khong
            int oBiTrong = -1;
            for (int i = 0; i < 6; i++) {
                if (oNhap[i].empty()) {
                    oBiTrong = i;
                    break;
                }
            }

            if (oBiTrong != -1) {
                gotoxy(boxX + 4, boxY + 3);
                textcolor(12);
                cout << "(!) Vui long nhap day du ngay, thang, nam truoc khi nhan ENTER!        ";
                oDangChon = oBiTrong; // Dua o chon den dung o dang thieu
                continue;
            }

            tuNgay   = chuyenChuoiSangSo(oNhap[0]);
            tuThang  = chuyenChuoiSangSo(oNhap[1]);
            tuNam    = chuyenChuoiSangSo(oNhap[2]);
            denNgay  = chuyenChuoiSangSo(oNhap[3]);
            denThang = chuyenChuoiSangSo(oNhap[4]);
            denNam   = chuyenChuoiSangSo(oNhap[5]);

            if (!ngayhople(tuNgay, tuThang, tuNam) || !ngayhople(denNgay, denThang, denNam)) {
                gotoxy(boxX + 4, boxY + 3);
                textcolor(12);
                cout << "(!) Ngay thang nam khong ton tai! Vui long kiem tra lai.                ";
                continue;
            }

            if (sosanhngay(tuNgay, tuThang, tuNam, denNgay, denThang, denNam) > 0) {
                gotoxy(boxX + 4, boxY + 3);
                textcolor(12);
                cout << "(!) Tu ngay phai nho hon hoac bang Den ngay! Vui long sua lai.          ";
                continue;
            }

            // Bo highlight tat ca cac o va hien thi thong bao xac nhan
            veCacONhapNgay(boxX, boxY, oNhap, -1);
            ShowConsoleCursor(false);

            string sTuNgay  = (tuNgay < 10 ? "0" : "") + to_string(tuNgay) + "/"
                            + (tuThang < 10 ? "0" : "") + to_string(tuThang) + "/" + to_string(tuNam);
            string sDenNgay = (denNgay < 10 ? "0" : "") + to_string(denNgay) + "/"
                            + (denThang < 10 ? "0" : "") + to_string(denThang) + "/" + to_string(denNam);

            gotoxy(boxX + 4, boxY + 3);
            textcolor(10);
            cout << "Ket qua thong ke tu " << sTuNgay << " den " << sDenNgay << string(25, ' ');
            return true;
        }
    }
}

// Ve bang ket qua Top 10 (Tong chieu rong = 92 ky tu: 6 + 12 + 34 + 12 + 22 + 6 vien = 92)
void veBangKetQuaTop10(int boxX, int tableY, const ThongKeVatTu dsTK[], int soLuongVT) {
    // 1. Duong vien tren cung
    textcolor(3);
    gotoxy(boxX, tableY);
    cout << char(218) << string(6, char(196))  << char(194)
         << string(12, char(196)) << char(194)
         << string(34, char(196)) << char(194)
         << string(12, char(196)) << char(194)
         << string(22, char(196)) << char(191);

    // 2. Dong tieu de cac cot
    gotoxy(boxX, tableY + 1);
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left << setw(6)  << " TOP";
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left << setw(12) << " Ma VT";
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left << setw(34) << " Ten Vat Tu";
    textcolor(3);  cout << char(179);
    textcolor(14); cout << left << setw(12) << " DVT";
    textcolor(3);  cout << char(179);
    textcolor(14); cout << right << setw(21) << "Doanh Thu (VND)" << " ";
    textcolor(3);  cout << char(179);

    // 3. Duong ke ngan giua tieu de va du lieu
    gotoxy(boxX, tableY + 2);
    textcolor(3);
    cout << char(195) << string(6, char(196))  << char(197)
         << string(12, char(196)) << char(197)
         << string(34, char(196)) << char(197)
         << string(12, char(196)) << char(197)
         << string(22, char(196)) << char(180);

    // 4. In 10 dong du lieu Top 10 (Vua khit 1 khung bang tren 1 trang man hinh)
    int soDongCoDoanhThu = 0;
    for (int i = 0; i < 10; i++) {
        int rowY = tableY + 3 + i;
        gotoxy(boxX, rowY);

        if (i < soLuongVT && dsTK[i].doanhThu > 0) {
            soDongCoDoanhThu++;
            string tenRutGon = dsTK[i].TENVT.substr(0, 32);
            string chuoiTien = dinhDangTien(dsTK[i].doanhThu);

            textcolor(3);  cout << char(179);
            textcolor(i < 3 ? 14 : 7);
            cout << " " << left << setw(5) << (i + 1);
            textcolor(3);  cout << char(179);
            textcolor(11); cout << " " << left << setw(11) << dsTK[i].MAVT;
            textcolor(3);  cout << char(179);
            textcolor(15); cout << " " << left << setw(33) << tenRutGon;
            textcolor(3);  cout << char(179);
            textcolor(7);  cout << " " << left << setw(11) << dsTK[i].DVT;
            textcolor(3);  cout << char(179);
            textcolor(10); cout << right << setw(21) << chuoiTien << " ";
            textcolor(3);  cout << char(179);
        } else {
            textcolor(3);
            cout << char(179) << string(6, ' ')  << char(179)
                 << string(12, ' ') << char(179)
                 << string(34, ' ') << char(179)
                 << string(12, ' ') << char(179)
                 << string(22, ' ') << char(179);
        }
    }

    // 5. Duong vien day bang
    gotoxy(boxX, tableY + 13);
    textcolor(3);
    cout << char(192) << string(6, char(196))  << char(193)
         << string(12, char(196)) << char(193)
         << string(34, char(196)) << char(193)
         << string(12, char(196)) << char(193)
         << string(22, char(196)) << char(217);

    // Thong bao neu khong co vat tu nao ban duoc
    if (soDongCoDoanhThu == 0) {
        gotoxy(boxX + 18, tableY + 7);
        textcolor(12);
        cout << "-> Khong co vat tu nao co doanh thu trong khoang thoi gian nay!";
    }

    // Thanh huong dan o day khung
    gotoxy(boxX + 2, tableY + 14);
    textcolor(11); cout << "Dieu khien: ";
    textcolor(7);  cout << "[ENTER]: Thong ke khoang ngay khac  |  [ESC]: Quay lai Menu chinh     ";
    textcolor(15);
}

// ==========================================================
// PHAN 4: HAM DIEU KHIEN CHINH (KET NOI LOGIC VA GIAO DIEN)
// ==========================================================

void giaodienTop10VatTu(DanhSachNhanVien dsNV, TreeVatTu root) {
    // Buoc 1: Chuan bi danh sach vat tu tu cay BST
    ThongKeVatTu dsTK[501];
    int soLuongVT = 0;
    chuyenCayVatTuSangMang(root, dsTK, soLuongVT);

    int offsetX = getDynamicOffsetX();
    int boxX = offsetX + 3;
    int boxY = OFFSET_Y + 3;
    int tableY = boxY + 5;

    while (true) {
        // Buoc 2: Ve khung gon va nhan khoang ngay tu nguoi dung
        veKhungChucNangGon(offsetX);

        int tuNgay, tuThang, tuNam, denNgay, denThang, denNam;
        bool daXacNhan = nhapKhoangNgayThongKe(boxX, boxY, tuNgay, tuThang, tuNam, denNgay, denThang, denNam);

        // Neu nguoi dung bam ESC -> thoat ve Menu Chinh
        if (!daXacNhan) {
            return;
        }

        // Buoc 3: Goi Module Logic de tinh doanh thu va sap xep Top 10
        tinhDoanhThuVatTu(dsNV, dsTK, soLuongVT, tuNgay, tuThang, tuNam, denNgay, denThang, denNam);
        sapXepDoanhThuGiamDan(dsTK, soLuongVT);

        // Buoc 4: Hien thi ket qua ra bang
        veBangKetQuaTop10(boxX, tableY, dsTK, soLuongVT);

        // Cho nguoi dung bam ENTER de nhap lai hoac ESC de ve Menu
        while (true) {
            int phim = _getch();
            if (phim == 27) return; // ESC -> Ve Menu Chinh
            if (phim == 13) break;  // ENTER -> Lap lai thong ke moi
        }
    }
}
