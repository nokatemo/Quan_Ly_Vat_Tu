#pragma once
#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. CAU TRUC THOI GIAN
// ==========================================
struct Date {
    int ngay;
    int thang;
    int nam;
};

// ==========================================
// 2. CAU TRUC VAT TU & CAY NHI PHAN 
// ==========================================
struct VatTu {
    string MAVT;
    string tenVatTu;
    string donViTinh;
    int soLuongTon;
};

struct NodeVatTu {
    VatTu data;
    NodeVatTu* left;
    NodeVatTu* right;
};
typedef NodeVatTu* TreeVatTu; // Con tro goc cua Cay nhi phan tim kiem

// ==========================================
// 3. CAU TRUC CHI TIET HOA DON & DSLK 
// ==========================================
struct ChiTietHoaDon {
    string MAVT;
    int soLuong;
    double donGia;
    float VAT;
};

struct NodeCTHD {
    ChiTietHoaDon data;
    NodeCTHD* next;
};
typedef NodeCTHD* ListCTHD; // Con tro dau cua danh sach chi tiet vat tu

// ==========================================
// 4. CAU TRUC HOA DON & DSLK 
// ==========================================
struct HoaDon {
    string soHD;
    Date ngayLap;
    char loai; // 'N' (Nhap) hoac 'X' (Xuat)
    ListCTHD dscthd; // Diem neo quan ly cac chi tiet vat tu ben trong
};

struct NodeHoaDon {
    HoaDon data;
    NodeHoaDon* next;
};
typedef NodeHoaDon* ListHoaDon; // Con tro dau danh sach hoa don

// ==========================================
// 5. CAU TRUC NHAN VIEN & MANG CON TRO 
// ==========================================
struct NhanVien {
    string MANV;
    string ho;
    string ten;
    string phai;
    ListHoaDon dshd; // Diem neo moc vao chuoi hoa don do nhan vien nay lap
};

struct DanhSachNhanVien {
    NhanVien* ds[500]; // Mang con tro chua toi da 500 nhan vien
    int soLuong = 0;   // So luong nhan vien thuc te dang quan ly
};
