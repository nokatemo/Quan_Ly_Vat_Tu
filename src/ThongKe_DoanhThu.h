#ifndef THONGKE_DOANHTHU_H
#define THONGKE_DOANHTHU_H

#include "struct.h"

// Tinh doanh thu cua 12 thang trong nam. Chi tinh hoa don xuat (loai 'X').
// Doanh thu cua moi chi tiet = so luong * don gia * (1 + VAT / 100).
void TinhDoanhThuTheoThang(const DanhSachNhanVien& ds, int nam,
                            double doanhThu[12]);

// Nhap nam va hien bang thong ke doanh thu theo yeu cau cua de bai.
void ThongKeDoanhThuTheoThang(const DanhSachNhanVien& ds);

#endif
