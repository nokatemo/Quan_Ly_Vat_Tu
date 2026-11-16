#include "ThongKe.h"
#include "Validate.h"

#include <iomanip>
#include <iostream>

using namespace std;

namespace {
    const int NAM_NHO_NHAT = 1900;
    const int NAM_LON_NHAT = 9999;

    double TriGiaChiTiet(const ChiTietHoaDon& chiTiet) {
        return chiTiet.soLuong * chiTiet.donGia * (1.0 + chiTiet.VAT / 100.0);
    }

    int NhapNamThongKe() {
        while (true) {
            cout << "Nhap nam can thong ke (" << NAM_NHO_NHAT << " - "
                 << NAM_LON_NHAT << "): " << flush;
            int nam = nhapsonguyen();
            if (nam >= NAM_NHO_NHAT && nam <= NAM_LON_NHAT) return nam;

            cout << "Nam khong hop le. Vui long nhap lai.\n";
        }
    }

    void VeDongKe() {
        cout << "+----------+--------------------------+\n";
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
    const int nam = NhapNamThongKe();
    double doanhThu[12];
    TinhDoanhThuTheoThang(ds, nam, doanhThu);

    cout << "\nBANG THONG KE DOANH THU NAM " << nam << "\n";
    VeDongKe();
    cout << "| THANG    | DOANH THU (VND)         |\n";
    VeDongKe();

    cout << fixed << setprecision(2);
    for (int thang = 0; thang < 12; thang++) {
        cout << "| " << left << setw(9) << thang + 1
             << "| " << right << setw(23) << doanhThu[thang] << " |\n";
    }
    VeDongKe();
}
