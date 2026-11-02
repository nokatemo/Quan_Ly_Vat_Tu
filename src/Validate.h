#ifndef VALIDATE_H
#define VALIDATE_H

#include <string>
#include <cstddef>

// =========================================================
// PHAN 1: CAC HAM KIEM TRA LOGIC (VALIDATION)
// =========================================================

// Kiem tra xem chuoi co bi rong hoac chi toan khoang trang hay khong
bool chuoirong(const std::string& str);

// Kiem tra nam nhuan (phuc vu cho ham kiemtrangay)
bool namnhuan(int nam);

// Tra ve so ngay toi da trong 1 thang (xet ca thang 2 cua nam nhuan)
int kiemtrangay(int thang, int nam);

// Kiem tra bo 3 Ngay/Thang/Nam co ton tai trong thuc te khong
bool ngayhople(int ngay, int thang, int nam);

// So sanh 2 moc thoi gian (phuc vu tinh nang thong ke doanh thu tu ngay... den ngay...)
// Tra ve: -1 (d1 < d2), 0 (d1 == d2), 1 (d1 > d2)
int sosanhngay(int d1, int m1, int y1, int d2, int m2, int y2);

// Kiem tra xem chuoi co bi lan chu so vao khong (vi du kiem tra Ho Ten)
bool conso(const std::string& ten);


// =========================================================
// PHAN 2: CAC HAM NHAP LIEU CHUAN HOA TRUC TIEP KHI GO
// =========================================================

// Nhap ID (Ma VT, Ma NV, So HD)
// - Chi nhan chu cai va so (A-Z, 0-9), tu dong in hoa tat ca
// - Chan khoang trang va ky tu dac biet
std::string NhapMaID(std::size_t maxlen);

// Nhap chuoi van ban (Ho, Ten)
// - Chi nhan chu cai va khoang trang
// - Tu dong in hoa chu cai dau, in thuong chu cai con lai
// - Chan khoang trang o dau, o cuoi, hoac 2 khoang trang lien tiep
std::string nhapChuoiChuanHoa(std::size_t maxlen);

// Nhap Ten Vat Tu 
// - Chuan hoa in hoa/in thuong giong nhapChuoiChuanHoa
// - NHUNG cho phep nhap them chu so (VD: "Xi mang PC 40")
std::string nhapTenVatTuChuanHoa(std::size_t maxlen);

// Nhap So Nguyen Duong (dung cho So Luong Ton)
// - Chi nhan cac so 0-9
// - Chan dau tru '-' nen khong the nhap so am
int nhapsonguyen();

// Nhap So Thuc Duong (dung cho Don gia, % VAT)
// - Chi nhan cac so 0-9 va toi da 1 dau cham phay dong (.)
// - Chan dau tru '-' nen khong the nhap so am
double nhapsothuc();

#endif
