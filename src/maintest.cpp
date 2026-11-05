#include <iostream>
#include "struct.h"
#include "UI.h"
#include "HoaDon.h"

using namespace std;

int main() {
    // 1. Khoi tao danh sach nhan vien va cay vat tu
    DanhSachNhanVien dsNV;
    dsNV.soLuong = 0;
    TreeVatTu root = NULL;

    // 2. Doc du lieu tu file len RAM khi bat chuong trinh
     DocFileVatTu(root);       // File VatTu cua Tien
     DocFileNhanVien(dsNV);    // File NhanVien cua Khoa
    DocFileHoaDon(dsNV);         // File HoaDon cua Khoa

    // 3. Khoi chay giao dien menu chinh
    menuController(dsNV, root);

    return 0;
}
