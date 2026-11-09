#include <iostream>
#include <windows.h>
#include "struct.h"
#include "VatTu.h"
#include "NhanVien.h"
#include "HoaDon.h"
#include "UI.h"

using namespace std;

int main() {
    

    // 2. Khai bao va khoi tao cac cau truc du lieu chinh cua he thong
    TreeVatTu root = NULL;             // Cay Nhi Phan Tim Kiem quan ly Vat Tu
    DanhSachNhanVien dsNV;            // Mang con tro quan ly Nhan Vien
    dsNV.soLuong = 0;

    // 3. Doc toan bo du lieu tu cac File text vao bo nho RAM khi khoi dong
    DocFileVatTu(root);
    DocFileNhanVien(dsNV);
    DocFileHoaDon(dsNV);               // Nap danh sach hoa don vao tung nhan vien tuong ung

    // 4. Kich hoat giao dien va luong dieu khien Menu chinh
    menuController(dsNV, root);

    // 5. Giai phong bo nho truoc khi thoat (neu can)
    GiaiPhongDSNhanVien(dsNV);
    // GiaiPhongCayVatTu(root);

    return 0;
}
