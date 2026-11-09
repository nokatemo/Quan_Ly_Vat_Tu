#pragma once
#include <iostream>
#include <string>

using namespace std;

// =========================================================
// 1. CAU TRUC NGAY THANG NAM
// =========================================================
struct Date {
    int ngay;           // Ngay lap (1-31)
    int thang;          // Thang lap (1-12)
    int nam;            // Nam lap
};

// =========================================================
// 2. CAU TRUC VAT TU (CAY NHI PHAN TIM KIEM)
// =========================================================
struct VatTu {
    string MAVT;        // Ma vat tu (Toi da 10 ky tu)
    string TENVT;       // Ten vat tu
    string DVT;         // Don vi tinh
    int soLuongTon;     // So luong ton kho
};

struct NodeVatTu {
    VatTu data;
    NodeVatTu* left;    // Con tro cay con trai
    NodeVatTu* right;   // Con tro cay con phai
};
typedef NodeVatTu* TreeVatTu;

// =========================================================
// 3. CAU TRUC CHI TIET HOA DON (DANH SACH LIEN KET DON)
// =========================================================
struct ChiTietHoaDon {
    string MAVT;        // Ma vat tu trong hoa don
    int soLuong;        // So luong mua hoac xuat
    double donGia;      // Don gia cua vat tu
    float VAT;          // Phan tram thue VAT
};

struct NodeCTHD {
    ChiTietHoaDon data;
    NodeCTHD* next;     // Con tro den chi tiet hoa don tiep theo
};
typedef NodeCTHD* ListCTHD;

// =========================================================
// 4. CAU TRUC HOA DON (DANH SACH LIEN KET DON)
// =========================================================
struct HoaDon {
    string soHD;        // So hoa don (Toi da 20 ky tu)
    Date ngayLap;       // Ngay thang nam lap hoa don
    char loai;          // Loai hoa don ('N': Nhap, 'X': Xuat)
    ListCTHD dscthd;    // Con tro quan ly danh sach chi tiet hoa don
};

struct NodeHoaDon {
    HoaDon data;
    NodeHoaDon* next;   // Con tro den hoa don tiep theo
};
typedef NodeHoaDon* ListHoaDon;

// =========================================================
// 5. CAU TRUC NHAN VIEN (DANH SACH TUYEN TINH MANG CON TRO)
// =========================================================
struct NhanVien {
    string MANV;        // Ma nhan vien
    string HO;          // Ho va ten dem
    string TEN;         // Ten nhan vien
    string PHAI;        // Gioi tinh ("Nam" / "Nu")
    ListHoaDon dshd;    // Con tro den danh sach hoa don do nhan vien nay lap
};

struct DanhSachNhanVien {
    NhanVien* ds[500];  // Mang con tro toi da 500 nhan vien
    int soLuong = 0;    // So luong nhan vien hien tai trong danh sach
};
