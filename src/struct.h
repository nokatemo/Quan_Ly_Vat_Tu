#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Date {
    int ngay;
    int thang;
    int nam;
};

struct VatTu {
    string MAVT;
    string TENVT;
    string DVT;
    int soLuongTon;
};

struct NodeVatTu {
    VatTu data;
    NodeVatTu* left;
    NodeVatTu* right;
};
typedef NodeVatTu* TreeVatTu;

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
typedef NodeCTHD* ListCTHD;

struct HoaDon {
    string soHD;
    Date ngayLap;
    char loai;
    ListCTHD dscthd;
};

struct NodeHoaDon {
    HoaDon data;
    NodeHoaDon* next;
};
typedef NodeHoaDon* ListHoaDon;

struct NhanVien {
    string MANV;
    string HO;
    string TEN;
    string PHAI;
    ListHoaDon dshd;
};

struct DanhSachNhanVien {
    NhanVien* ds[500];
    int soLuong = 0;
};
