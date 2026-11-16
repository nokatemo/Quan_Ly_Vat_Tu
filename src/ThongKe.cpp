#include "ThongKe.h"
#include "UI.h"

#include <cctype>
#include <conio.h>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

namespace {
    const int NAM_NHO_NHAT = 1900;
    const int NAM_LON_NHAT = 9999;
    const int KHUNG_TK_X = 10;
    const int KHUNG_TK_Y = 1;
    const int KHUNG_TK_RONG = 100;
    const int KHUNG_TK_CAO = 31;
    const int BANG_TK_X = KHUNG_TK_X + 29;

    double TriGiaChiTiet(const ChiTietHoaDon& chiTiet) {
        return chiTiet.soLuong * chiTiet.donGia * (1.0 + chiTiet.VAT / 100.0);
    }

    void InGiuaThongKe(const string& noiDung, int dong, int mau) {
        gotoxy(KHUNG_TK_X + (KHUNG_TK_RONG - static_cast<int>(noiDung.size())) / 2, dong);
        textcolor(mau);
        cout << noiDung;
    }

    void VeKhungThongKe(const string& tieuDe) {
        ShowConsoleCursor(false);
        textcolor(14);
        gotoxy(KHUNG_TK_X, KHUNG_TK_Y);
        cout << string(KHUNG_TK_RONG + 1, char(178));
        for (int dong = KHUNG_TK_Y + 1; dong < KHUNG_TK_Y + KHUNG_TK_CAO; dong++) {
            gotoxy(KHUNG_TK_X, dong);
            cout << char(178);
            textcolor(11);
            cout << string(KHUNG_TK_RONG - 1, ' ');
            textcolor(14);
            cout << char(178);
        }
        gotoxy(KHUNG_TK_X, KHUNG_TK_Y + KHUNG_TK_CAO);
        cout << string(KHUNG_TK_RONG + 1, char(178));
        gotoxy(KHUNG_TK_X + 2, KHUNG_TK_Y + 1);
        cout << string(KHUNG_TK_RONG - 3, '=');
        gotoxy(KHUNG_TK_X + 2, KHUNG_TK_Y + 3);
        cout << string(KHUNG_TK_RONG - 3, '=');
        InGiuaThongKe(tieuDe, KHUNG_TK_Y + 2, 11);
    }

    void VeDongBang(int dong) {
        gotoxy(BANG_TK_X, dong);
        textcolor(14);
        cout << "+----------+------------------------------+";
    }

    bool NhapNamThongKe(int& nam) {
        while (true) {
            system("cls");
            VeKhungThongKe("THONG KE DOANH THU THEO NAM");
            InGiuaThongKe("NHAP NAM CAN THONG KE", KHUNG_TK_Y + 6, 14);
            gotoxy(KHUNG_TK_X + 25, KHUNG_TK_Y + 9);
            textcolor(11);
            cout << "NAM: [    ]";
            gotoxy(KHUNG_TK_X + 31, KHUNG_TK_Y + 9);
            ShowConsoleCursor(true);

            string duLieu;
            while (true) {
                int phim = _getch();
                if (phim == 27) {
                    ShowConsoleCursor(false);
                    return false;
                }
                if (phim == 0 || phim == 224) {
                    _getch();
                    continue;
                }
                if (phim == 8) {
                    if (!duLieu.empty()) {
                        duLieu.pop_back();
                        cout << "\b \b" << flush;
                    }
                    continue;
                }
                if (phim == 13 && !duLieu.empty()) {
                    nam = stoi(duLieu);
                    break;
                }
                if (isdigit(static_cast<unsigned char>(phim)) && duLieu.size() < 4) {
                    duLieu += static_cast<char>(phim);
                    cout << static_cast<char>(phim) << flush;
                }
            }

            if (nam >= NAM_NHO_NHAT && nam <= NAM_LON_NHAT) {
                ShowConsoleCursor(false);
                return true;
            }

            gotoxy(KHUNG_TK_X + 26, KHUNG_TK_Y + 14);
            textcolor(12);
            cout << "Nam phai nam trong khoang 1900 - 9999.";
            InGiuaThongKe("Nhan phim bat ky de nhap lai, Esc de quay ve menu.",
                         KHUNG_TK_Y + 16, 10);
            int phim = _getch();
            if (phim == 27) {
                ShowConsoleCursor(false);
                return false;
            }
        }
    }

    void HienBangDoanhThu(int nam, const double doanhThu[12]) {
        system("cls");
        VeKhungThongKe("BANG THONG KE DOANH THU");
        InGiuaThongKe("NAM THONG KE: " + to_string(nam), KHUNG_TK_Y + 5, 10);
        InGiuaThongKe("CHI TINH HOA DON XUAT - GIA TRI BAO GOM VAT",
                      KHUNG_TK_Y + 6, 8);

        VeDongBang(KHUNG_TK_Y + 8);
        gotoxy(BANG_TK_X, KHUNG_TK_Y + 9);
        textcolor(11);
        cout << "| " << left << setw(7) << "THANG"
             << "| " << right << setw(27) << "DOANH THU (VND)" << " |";
        VeDongBang(KHUNG_TK_Y + 10);

        cout << fixed << setprecision(2);
        double tongNam = 0.0;
        for (int thang = 0; thang < 12; thang++) {
            gotoxy(BANG_TK_X, KHUNG_TK_Y + 11 + thang);
            textcolor(11);
            cout << "| " << left << setw(7) << thang + 1
                 << "| " << right << setw(27) << doanhThu[thang] << " |";
            tongNam += doanhThu[thang];
        }
        VeDongBang(KHUNG_TK_Y + 23);
        gotoxy(BANG_TK_X, KHUNG_TK_Y + 24);
        textcolor(10);
        cout << "| " << left << setw(7) << "TONG NAM"
             << "| " << right << setw(27) << tongNam << " |";
        VeDongBang(KHUNG_TK_Y + 25);

        InGiuaThongKe("Nhan phim bat ky de thong ke nam khac", KHUNG_TK_Y + 28, 11);
        InGiuaThongKe("Nhan Esc de quay lai menu chinh", KHUNG_TK_Y + 29, 10);
        textcolor(11);
        ShowConsoleCursor(false);
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
    while (true) {
        int nam;
        if (!NhapNamThongKe(nam)) return;

        double doanhThu[12];
        TinhDoanhThuTheoThang(ds, nam, doanhThu);

        HienBangDoanhThu(nam, doanhThu);
        int phim = _getch();
        if (phim == 27) return;
        if (phim == 0 || phim == 224) _getch();
    }
}
