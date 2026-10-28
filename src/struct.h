#pragma once
#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. CẤU TRÚC THỜI GIAN
// ==========================================
struct Date {
    int ngay;
    int thang;
    int nam;
};

// ==========================================
// 2. CẤU TRÚC VẬT TƯ & CÂY NHỊ PHÂN 
// (Dành cho phần việc của Minh Tiến)
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
typedef NodeVatTu* TreeVatTu; // Con trỏ gốc của Cây nhị phân tìm kiếm

// ==========================================
// 3. CẤU TRÚC CHI TIẾT HÓA ĐƠN & DSLK 
// (Dành cho phần việc của Nguyên Khoa)
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
typedef NodeCTHD* ListCTHD; // Con trỏ đầu của danh sách chi tiết vật tư

// ==========================================
// 4. CẤU TRÚC HÓA ĐƠN & DSLK 
// (Dành cho phần việc của Nguyên Khoa)
// ==========================================
struct HoaDon {
    string soHD;
    Date ngayLap;
    char loai; // 'N' (Nhập) hoặc 'X' (Xuất)
    ListCTHD dscthd; // Điểm neo quản lý các chi tiết vật tư bên trong
};

struct NodeHoaDon {
    HoaDon data;
    NodeHoaDon* next;
};
typedef NodeHoaDon* ListHoaDon; // Con trỏ đầu danh sách hóa đơn

// ==========================================
// 5. CẤU TRÚC NHÂN VIÊN & MẢNG CON TRỞ 
// (Dành cho phần việc của Trung Nguyên)
// ==========================================
struct NhanVien {
    string MANV;
    string ho;
    string ten;
    string phai;
    ListHoaDon dshd; // Điểm neo móc vào chuỗi hóa đơn do nhân viên này lập
};

struct DanhSachNhanVien {
    NhanVien* ds[500]; // Mảng con trỏ chứa tối đa 500 nhân viên
    int soLuong = 0;   // Số lượng nhân viên thực tế đang quản lý
};
