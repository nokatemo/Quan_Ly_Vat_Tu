#include "ThongKe_DoanhThu.h"
#include "UI.h"

#include <cctype>
#include <conio.h>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

namespace {
    const int NAM_NHO_NHAT = 1900;
    const int NAM_LON_NHAT = 9999;

    double TriGiaChiTiet(const ChiTietHoaDon& chiTiet) {
        return chiTiet.soLuong * chiTiet.donGia * (1.0 + chiTiet.VAT / 100.0);
    }

    void VeKhungThongKeChung() {
        int offsetX = getDynamicOffsetX();
        clearContentArea();
        ShowConsoleCursor(false);
        veTieuDeChucNang("9. THONG KE DOANH THU THEO THANG");

        // 1. Khung ben trai: Nhap nam & Thong so (X: offsetX + 3, rong 34, cao 15)
        int leftX = offsetX + 3;
        int boxY  = OFFSET_Y + 5;
        drawBox(leftX, boxY, 34, 15, 3, false);
        gotoxy(leftX + 2, boxY);
        textcolor(14); cout << " NHAP NAM CAN THONG KE ";

        gotoxy(leftX + 3, boxY + 3);
        textcolor(11); cout << "NAM: [      ]";

        gotoxy(leftX + 3, boxY + 6);
        textcolor(8);  cout << string(28, char(196));

        gotoxy(leftX + 3, boxY + 8);
        textcolor(10); cout << "GHI CHU TINH TOAN:";
        gotoxy(leftX + 3, boxY + 10);
        textcolor(7);  cout << "- Chi tinh hoa don XUAT";
        gotoxy(leftX + 3, boxY + 11);
        textcolor(7);  cout << "- Doanh thu da gom VAT";
        gotoxy(leftX + 3, boxY + 12);
        textcolor(7);  cout << "- Don vi tinh: VND";

        // 2. Khung ben phai: Bang doanh thu 12 thang (X: offsetX + 39, rong 53, cao 17)
        int rightX = offsetX + 39;
        drawBox(rightX, boxY, 53, 17, 3, false);
        gotoxy(rightX + 3, boxY);
        textcolor(11); cout << " BANG THONG KE DOANH THU ";

        // Header bang 12 thang
        gotoxy(rightX + 2, boxY + 1);
        textcolor(14);
        cout << " THANG " << char(179) << "            DOANH THU (VND)        ";

        gotoxy(rightX + 2, boxY + 2);
        textcolor(3);
        cout << string(7, char(196)) << char(197) << string(41, char(196));

        // 12 dong thang mac dinh 0.00
        for (int t = 0; t < 12; t++) {
            gotoxy(rightX + 2, boxY + 3 + t);
            textcolor(15); cout << "  " << left << setw(5) << (t + 1);
            textcolor(3);  cout << char(179);
            textcolor(8);  cout << right << setw(39) << "0.00" << "  ";
        }

        // Dong TONG NAM o day bang
        gotoxy(rightX + 2, boxY + 15);
        textcolor(10); cout << " TONG  ";
        textcolor(3);  cout << char(179);
        textcolor(14); cout << right << setw(39) << "0.00" << "  ";

        veThanhHuongDan(offsetX + 12, OFFSET_Y + 23, "Nhap nam (4 so) + ENTER: Xem | ESC: Ve Menu Chinh");
    }

    void CapNhatBangDoanhThu(int nam, const double doanhThu[12]) {
        int offsetX = getDynamicOffsetX();
        int rightX = offsetX + 39;
        int boxY   = OFFSET_Y + 5;

        // Cap nhat tieu de khung phai kem nam dang xem
        gotoxy(rightX + 3, boxY);
        textcolor(10);
        cout << " BANG DOANH THU NAM " << nam << " ";

        cout << fixed << setprecision(2);
        double tongNam = 0.0;

        for (int t = 0; t < 12; t++) {
            gotoxy(rightX + 2, boxY + 3 + t);
            textcolor(11); cout << "  " << left << setw(5) << (t + 1);
            textcolor(3);  cout << char(179);
            textcolor(doanhThu[t] > 0 ? 15 : 7);
            cout << right << setw(39) << doanhThu[t] << "  ";
            tongNam += doanhThu[t];
        }

        gotoxy(rightX + 2, boxY + 15);
        textcolor(10); cout << " TONG  ";
        textcolor(3);  cout << char(179);
        textcolor(14); cout << right << setw(39) << tongNam << "  ";
        textcolor(15);
    }

    bool NhapNamTrongKhung(int& nam) {
        int offsetX = getDynamicOffsetX();
        int leftX = offsetX + 3;
        int boxY  = OFFSET_Y + 5;

        // Xoa thong bao loi cu (neu co)
        gotoxy(leftX + 2, boxY + 14);
        cout << string(30, ' ');

        gotoxy(leftX + 3, boxY + 3);
        textcolor(14); cout << "NAM: [      ]";
        gotoxy(leftX + 10, boxY + 3);
        ShowConsoleCursor(true);

        string duLieu = "";
        while (true) {
            int phim = _getch();
            if (phim == 27) { // ESC
                ShowConsoleCursor(false);
                return false;
            }
            if (phim == 0 || phim == 224 || phim == -32) {
                _getch();
                continue;
            }
            if (phim == 8) { // Backspace
                if (!duLieu.empty()) {
                    duLieu.pop_back();
                    cout << "\b \b" << flush;
                }
                continue;
            }
            if (phim == 13 && !duLieu.empty()) { // Enter
                int giaTri = stoi(duLieu);
                if (giaTri >= NAM_NHO_NHAT && giaTri <= NAM_LON_NHAT) {
                    nam = giaTri;
                    ShowConsoleCursor(false);
                    return true;
                } else {
                    gotoxy(leftX + 2, boxY + 14);
                    textcolor(12);
                    cout << "Nam tu 1900 - 9999!";
                    gotoxy(leftX + 10 + (int)duLieu.length(), boxY + 3);
                }
                continue;
            }
            if (isdigit(static_cast<unsigned char>(phim)) && duLieu.size() < 4) {
                duLieu += static_cast<char>(phim);
                textcolor(15);
                cout << static_cast<char>(phim) << flush;
            }
        }
    }
}

void TinhDoanhThuTheoThang(const DanhSachNhanVien& ds, int nam,
                            double doanhThu[12]) {
    for (int i = 0; i < 12; i++) doanhThu[i] = 0.0;

    for (int i = 0; i < ds.soLuong; i++) {
        if (ds.ds[i] == nullptr) continue;

        for (ListHoaDon hoaDon = ds.ds[i]->dshd; hoaDon != nullptr;
             hoaDon = hoaDon->next) {
            const HoaDon& hd = hoaDon->data;
            if (hd.loai != 'X' || hd.ngayLap.nam != nam ||
                hd.ngayLap.thang < 1 || hd.ngayLap.thang > 12) {
                continue;
            }

            double& tongThang = doanhThu[hd.ngayLap.thang - 1];
            for (ListCTHD chiTiet = hd.dscthd; chiTiet != nullptr;
                 chiTiet = chiTiet->next) {
                tongThang += TriGiaChiTiet(chiTiet->data);
            }
        }
    }
}

void ThongKeDoanhThuTheoThang(const DanhSachNhanVien& ds) {
    VeKhungThongKeChung();
    int offsetX = getDynamicOffsetX();

    while (true) {
        int nam;
        if (!NhapNamTrongKhung(nam)) return;

        double doanhThu[12];
        TinhDoanhThuTheoThang(ds, nam, doanhThu);
        CapNhatBangDoanhThu(nam, doanhThu);

        veThanhHuongDan(offsetX + 10, OFFSET_Y + 23, "ENTER: Xem nam khac | ESC: Quay lai Menu Chinh");
        int phim = _getch();
        if (phim == 27) return;
        if (phim == 0 || phim == 224 || phim == -32) _getch();

        veThanhHuongDan(offsetX + 12, OFFSET_Y + 23, "Nhap nam (4 so) + ENTER: Xem | ESC: Ve Menu Chinh");
    }
}
