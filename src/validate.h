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

// So sanh 2 moc thoi gian
// Tra ve: -1 (d1 < d2), 0 (d1 == d2), 1 (d1 > d2)
int sosanhngay(int d1, int m1, int y1, int d2, int m2, int y2);

// Kiem tra xem chuoi co bi lan chu so vao khong (phuc vu kiem tra Ho Ten)
bool conso(const std::string& ten);

// Bo khoang trang thua va viet hoa chu cai dau moi tu.
// Ham nay chi xu ly chuoi co san, khong doc ban phim.
std::string ChuanHoaHoTen(const std::string& str);


// =========================================================
// PHAN 2: CAC HAM NHAP LIEU CHUAN HOA TRUC TIEP KHI GO (LIVE)
// =========================================================

// Nhap ID (Ma VT, Ma NV, So HD)
// - Chi nhan chu cai va so (A-Z, 0-9), tu dong IN HOA ngay khi go
// - Chan khoang trang va ky tu dac biet
// Truyen daHuy de cho phep nhan Esc huy nhap; daHuy se duoc dat thanh true.
std::string NhapMaID(std::size_t maxlen, bool* daHuy = nullptr);

// Nhap chuoi van ban (Ho, Ten)
// - Chi nhan chu cai va khoang trang
// - Tu dong in hoa chu cai dau moi tu, in thuong cac chu con lai ngay khi go
// - Chan khoang trang o dau, o cuoi, va 2 khoang trang lien tiep
std::string nhapChuoiChuanHoa(std::size_t maxlen, bool* daHuy = nullptr);

// Nhap Ten Vat Tu 
// - Chuan hoa hoa/thuong ngay khi go giong nhapChuoiChuanHoa
// - Cho phep nhap them chu so (VD: "Gach Ong 4 Lo")
std::string nhapTenVatTuChuanHoa(std::size_t maxlen);

// Nhap So Nguyen Duong (dung cho So Luong Ton)
// - Chi nhan cac so 0-9
// - Chan dau tru '-' va ky tu khong phai la so
int nhapsonguyen();

// Nhap So Thuc Duong (dung cho Don gia, % VAT)
// - Chi nhan cac so 0-9 va toi da 1 dau cham phay dong (.)
// - Chan dau tru '-' va nhieu dau cham cung luc
double nhapsothuc();


// =========================================================
// PHAN 3: HAM CHUAN HOA TUNG PHIM CHO FORM CO DI CHUYEN LEN/XUONG
// Tra ve: 1 (da them/xoa ky tu), -1 (day maxlen), 0 (bo qua phim)
// =========================================================
int XuLyPhimMaID(std::string& chuoi, int c, std::size_t maxlen);
int XuLyPhimChuoiChuanHoa(std::string& chuoi, int c, std::size_t maxlen);
void XoaKhoangTrangCuoi(std::string& chuoi);

#endif // VALIDATE_H
