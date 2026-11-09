#include "NhanVien.h"
#include "UI.h"
#include "Validate.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <conio.h>
#include <cstdio>

using namespace std;

// =========================================================
// PHAN 1: CAC HAM TIM KIEM NHAN VIEN
// =========================================================

// Tim kiem nhi phan (Binary Search) theo MANV tren mang con tro da sap xep
int TimkiemNhanVien(const DanhSachNhanVien& ds, const string& maNV) {
    int Left = 0;
    int Right = ds.soLuong - 1;

    while (Left <= Right) {
        int Mid = Left + ((Right - Left) / 2);
        if (ds.ds[Mid]->MANV == maNV) return Mid; // Tim thay, tra ve vi tri index
        if (maNV < ds.ds[Mid]->MANV) Right = Mid - 1; // Tim ben trai
        else Left = Mid + 1;                          // Tim ben phai
    }
    return -1; // Khong tim thay
}

// Ham boc (wrapper) ho tro goi ten ham theo chuan CamelCase
int TimKiemNhanVien(const DanhSachNhanVien& ds, const string& maNV) {
    return TimkiemNhanVien(ds, maNV);
}

// =========================================================
// PHAN 2: CAC HAM NOI BO (ANONYMOUS NAMESPACE) HO TRO NHAP LIEU & CHUAN HOA
// =========================================================

namespace {
    // Viet hoa chu cai dau tien cua moi tu trong chuoi (VD: "nguyen van" -> "Nguyen Van")
    void VietHoaDauTu(string& chuoi) {
        bool dauTu = true;
        for (char& kyTu : chuoi) {
            if (kyTu == ' ') {
                dauTu = true;
            } else {
                unsigned char c = static_cast<unsigned char>(kyTu);
                kyTu = static_cast<char>(dauTu ? toupper(c) : tolower(c));
                dauTu = false;
            }
        }
    }

    // Chuan hoa chuoi: xoa khoang trang thua o dau, cuoi va giua cac tu, sau do viet hoa chu cai dau
    string ChuanHoaThongTinNhanVien(const string& chuoi) {
        string ketQua;
        for (char c : chuoi) {
            if (c == ' ') {
                if (!ketQua.empty() && ketQua.back() != ' ') ketQua += ' ';
            } else {
                ketQua += c;
            }
        }
        if (!ketQua.empty() && ketQua.back() == ' ') ketQua.pop_back();
        VietHoaDauTu(ketQua);
        return ketQua;
    }

    // Kiem tra tinh hop le cua thong tin nhan vien theo quy dinh
    bool ThongTinNhanVienHopLe(const NhanVien& nv) {
        // Kiem tra do dai va rong
        if (nv.MANV.empty() || nv.MANV.size() > 5 || chuoirong(nv.HO) || nv.HO.size() > 20 ||
            chuoirong(nv.TEN) || nv.TEN.size() > 10 || (nv.PHAI != "Nam" && nv.PHAI != "Nu")) return false;
        
        // MANV chi chua chu va so, in hoa
        for (unsigned char c : nv.MANV) if (!isalnum(c) || islower(c)) return false;
        
        // HO va TEN chi chua chu cai va khoang trang
        for (unsigned char c : nv.HO) if (!isalpha(c) && c != ' ') return false;
        for (unsigned char c : nv.TEN) if (!isalpha(c) && c != ' ') return false;
        
        return true;
    }

    // Chen nhan vien moi vao mang con tro sao cho danh sach luon tang dan theo MANV
    int ChenNhanVienTheoMa(DanhSachNhanVien& ds, NhanVien* nv) {
        int i = ds.soLuong;
        // Dich cac phan tu co MANV lon hon sang phai
        while (i > 0 && ds.ds[i - 1]->MANV > nv->MANV) {
            ds.ds[i] = ds.ds[i - 1];
            i--;
        }
        ds.ds[i] = nv;
        ds.soLuong++;
        return i; // Tra ve vi tri chen moi
    }

    // Form nhap lieu tuong tac va kiem tra thong tin mot nhan vien
    bool NhapMotNhanVien(DanhSachNhanVien& ds, const string& tenFile) {
        if (ds.soLuong >= 500) return false; // Danh sach da day (toi da 500)

        NhanVien nv = {"", "", "", "", NULL};
        string* oNhap[] = {&nv.MANV, &nv.HO, &nv.TEN, &nv.PHAI};
        const size_t gioiHan[] = {5, 20, 10, 3}; // Gioi han ky tu cho tung field
        int oDangChon = 0; // 0: MANV, 1: HO, 2: TEN, 3: PHAI, 4: Nut Luu
        size_t viTri = 0;  // Vi tri con tro trong o nhap
        string thongBao;

        // Lambda ho tro chuyen doi giua cac o nhap
        auto chuyenO = [&](int oMoi) {
            if (oDangChon > 0 && oDangChon < 4) {
                *oNhap[oDangChon] = ChuanHoaThongTinNhanVien(*oNhap[oDangChon]);
            }
            oDangChon = oMoi;
            viTri = oMoi < 4 ? oNhap[oMoi]->size() : 0;
            thongBao.clear();
        };

        // Vong lap nhap va xu ly phim real-time
        while (true) {
            HienFormNhanVien(nv, oDangChon, static_cast<int>(viTri), thongBao);
            int c = _getch();
            if (c == 27) return false; // Phim ESC -> Huy nhap va quay lai

            bool luu = false;

            // Phim chuc nang / Mui ten
            if (c == 0 || c == 224) {
                int phim = _getch();
                if (phim == 72) chuyenO((oDangChon + 4) % 5);      // Mui ten Up
                else if (phim == 80) chuyenO((oDangChon + 1) % 5); // Mui ten Down
                else if (phim == 60) luu = true;                   // Phim F2 (Luu)
                else if (oDangChon < 4) {
                    string& giaTri = *oNhap[oDangChon];
                    if (phim == 75 && viTri > 0) viTri--;                // Left
                    else if (phim == 77 && viTri < giaTri.size()) viTri++; // Right
                    else if (phim == 71) viTri = 0;                       // Home
                    else if (phim == 79) viTri = giaTri.size();            // End
                    else if (phim == 83 && viTri < giaTri.size()) {       // Delete
                        giaTri.erase(viTri, 1);
                        if (oDangChon > 0) VietHoaDauTu(giaTri);
                        thongBao.clear();
                    }
                }
                if (!luu) continue;
            } else if (c == 13 && oDangChon == 4) { // Enter tai Nut Luu
                luu = true;
            } else if (c == 13 || c == 9) { // Enter hoac TAB -> Chuyen sang o tiep theo
                chuyenO((oDangChon + 1) % 5);
                continue;
            }

            // Thao tac Luu va kiem tra loi validation
            if (luu) {
                nv.HO = ChuanHoaThongTinNhanVien(nv.HO);
                nv.TEN = ChuanHoaThongTinNhanVien(nv.TEN);
                nv.PHAI = ChuanHoaThongTinNhanVien(nv.PHAI);
                int oLoi = -1;

                if (chuoirong(nv.MANV)) {
                    oLoi = 0;
                    thongBao = "Ma nhan vien khong duoc de trong.";
                } else if (TimkiemNhanVien(ds, nv.MANV) != -1) {
                    oLoi = 0;
                    thongBao = "Ma da ton tai. Vui long nhap ma khac.";
                } else if (chuoirong(nv.HO)) {
                    oLoi = 1;
                    thongBao = "Ho va ten dem khong duoc de trong.";
                } else if (chuoirong(nv.TEN)) {
                    oLoi = 2;
                    thongBao = "Ten khong duoc de trong.";
                } else if (nv.PHAI != "Nam" && nv.PHAI != "Nu") {
                    oLoi = 3;
                    thongBao = "Phai chi nhan Nam hoac Nu.";
                }

                // Neu khong co loi -> Chen vao danh sach va ghi file
                if (oLoi == -1) {
                    NhanVien* moi = new NhanVien(nv);
                    int viTriMoi = ChenNhanVienTheoMa(ds, moi);
                    if (GhiFileNhanVien(ds, tenFile)) return true;

                    // Neu ghi file loi -> Rollback (xoa khoi danh sach)
                    for (int i = viTriMoi; i < ds.soLuong - 1; i++) ds.ds[i] = ds.ds[i + 1];
                    ds.soLuong--;
                    ds.ds[ds.soLuong] = nullptr;
                    delete moi;
                    thongBao = "Khong ghi duoc NhanVien.txt. Nhan F2 de thu lai, Esc de huy.";
                    viTri = oDangChon < 4 ? oNhap[oDangChon]->size() : 0;
                    continue;
                }
                oDangChon = oLoi;
                viTri = oNhap[oLoi]->size();
                continue;
            }

            // Xoa ky tu (Backspace)
            if (oDangChon == 4) continue;
            string& giaTri = *oNhap[oDangChon];
            if (c == 8) {
                if (viTri > 0) {
                    giaTri.erase(viTri - 1, 1);
                    viTri--;
                    if (oDangChon > 0) VietHoaDauTu(giaTri);
                    thongBao.clear();
                }
                continue;
            }

            // Nhap ky tu thuong
            if (c < 32 || c > 255) continue;
            unsigned char kyTu = static_cast<unsigned char>(c);
            bool hopLe = oDangChon == 0 ? isalnum(kyTu) : (isalpha(kyTu) || c == ' ');
            if (!hopLe) continue;

            if (giaTri.size() >= gioiHan[oDangChon]) {
                thongBao = "O nay toi da " + to_string(gioiHan[oDangChon]) + " ky tu.";
                continue;
            }

            char moi = oDangChon == 0 ? static_cast<char>(toupper(kyTu)) : static_cast<char>(c);
            giaTri.insert(viTri, 1, moi);
            viTri++;
            if (oDangChon > 0) VietHoaDauTu(giaTri);
            thongBao.clear();
        }
    }
} // namespace

// =========================================================
// PHAN 3: CAC HAM THAO TAC FILE NHAN VIEN (DOC / GHI FILE)
// =========================================================

// Lay duong dan file an toan (tuyet doi) cung thu muc voi file exe
string DuongDanFileNhanVien(const string& tenFile) {
    if (tenFile.find_first_of("/\\") != string::npos || tenFile.find(':') != string::npos) return tenFile;
    char duongDan[MAX_PATH];
    DWORD doDai = GetModuleFileNameA(nullptr, duongDan, MAX_PATH);
    if (doDai == 0 || doDai >= MAX_PATH) return tenFile;
    string chuongTrinh(duongDan, doDai);
    size_t viTri = chuongTrinh.find_last_of("/\\");
    return viTri == string::npos ? tenFile : chuongTrinh.substr(0, viTri + 1) + tenFile;
}

// Ghi danh sach nhan vien an toan qua file tam (.tmp) truoc khi ghi de
bool GhiFileNhanVien(const DanhSachNhanVien& ds, const string& tenFile) {
    if (ds.soLuong < 0 || ds.soLuong > 500) return false;
    for (int i = 0; i < ds.soLuong; i++) {
        if (ds.ds[i] == nullptr || !ThongTinNhanVienHopLe(*ds.ds[i])) return false;
        for (int j = 0; j < i; j++) if (ds.ds[j]->MANV == ds.ds[i]->MANV) return false;
    }

    string duongDan = DuongDanFileNhanVien(tenFile);
    string fileTam = duongDan + ".tmp";
    ofstream file(fileTam.c_str(), ios::out | ios::trunc);
    if (!file.is_open()) return false;

    for (int i = 0; i < ds.soLuong; i++) {
        const NhanVien& nv = *ds.ds[i];
        file << nv.MANV << '|' << nv.HO << '|' << nv.TEN << '|' << nv.PHAI << '\n';
    }
    file.close();

    // Thay the file goc bang file tam
    if (!file || !MoveFileExA(fileTam.c_str(), duongDan.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
        remove(fileTam.c_str());
        return false;
    }
    return true;
}

// Ham luu file ho tro giao dien cu
void LuuFileNhanVien(const DanhSachNhanVien& dsNV) {
    GhiFileNhanVien(dsNV, "NhanVien.txt");
}

// Doc danh sach nhan vien tu file text vao mang con tro
bool DocFileNhanVien(DanhSachNhanVien& ds, const string& tenFile) {
    if (ds.soLuong != 0) return false;
    string duongDan = DuongDanFileNhanVien(tenFile);

    if (GetFileAttributesA(duongDan.c_str()) == INVALID_FILE_ATTRIBUTES) {
        DWORD loi = GetLastError();
        return loi == ERROR_FILE_NOT_FOUND || loi == ERROR_PATH_NOT_FOUND;
    }

    ifstream file(duongDan.c_str());
    if (!file.is_open()) return false;

    DanhSachNhanVien tam;
    string dong;
    bool hopLe = true;
    bool dongDau = true;

    while (getline(file, dong)) {
        // Xoa BOM UTF-8 neu co o dong dau
        if (dongDau && dong.compare(0, 3, "\xEF\xBB\xBF") == 0) dong.erase(0, 3);
        dongDau = false;

        if (!dong.empty() && dong.back() == '\r') dong.pop_back();
        if (dong.find_first_not_of(" \t") == string::npos) continue; // Dong trong
        if (tam.soLuong >= 500) { hopLe = false; break; }

        NhanVien nv = {"", "", "", "", NULL};
        istringstream tach(dong);
        if (!getline(tach, nv.MANV, '|') || !getline(tach, nv.HO, '|') ||
            !getline(tach, nv.TEN, '|') || !getline(tach, nv.PHAI)) { hopLe = false; break; }

        for (char& c : nv.MANV) c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
        nv.HO = ChuanHoaThongTinNhanVien(nv.HO);
        nv.TEN = ChuanHoaThongTinNhanVien(nv.TEN);
        nv.PHAI = ChuanHoaThongTinNhanVien(nv.PHAI);

        if (!ThongTinNhanVienHopLe(nv) || TimkiemNhanVien(tam, nv.MANV) != -1) { hopLe = false; break; }
        ChenNhanVienTheoMa(tam, new NhanVien(nv));
    }

    if (file.bad() || (file.fail() && !file.eof())) hopLe = false;

    if (!hopLe) {
        for (int i = 0; i < tam.soLuong; i++) delete tam.ds[i];
        return false;
    }

    for (int i = 0; i < tam.soLuong; i++) ds.ds[i] = tam.ds[i];
    ds.soLuong = tam.soLuong;
    return true;
}

// =========================================================
// PHAN 4: CAC HAM GIAO DIEN CHUC NANG QUAN LY NHAN VIEN
// =========================================================

// Giao dien chuc nang Them nhan vien
bool ThemNhanVien(DanhSachNhanVien& ds, const string& tenFile) {
    int soLuongBanDau = ds.soLuong;
    VeKhungNhanVien("THEM VA CAP NHAT NHAN VIEN");
    HienSoLuongNhanVien(ds.soLuong);

    while (ds.soLuong < 500 && NhapMotNhanVien(ds, tenFile)) {
        HienSoLuongNhanVien(ds.soLuong);
    }

    if (ds.soLuong >= 500) {
        HienThongBaoDayNhanVien();
        while (true) {
            int c = _getch();
            if (c == 27 || c == 13) break;
            if (c == 0 || c == 224) _getch();
        }
    }
    return ds.soLuong > soLuongBanDau;
}

// In danh sach nhan vien sap xep theo Ten tang dan (trung Ten thi sap theo Ho), ho tro phan trang
void InDanhSachNhanVien(const DanhSachNhanVien& ds) {
    const NhanVien* thutu[500];
    for (int i = 0; i < ds.soLuong; i++) {
        thutu[i] = ds.ds[i];
    }

    // Sap xep danh sach in theo Ten tang dan, neu trung Ten thi sap xep theo Ho (Insertion Sort)
    for (int i = 1; i < ds.soLuong; i++) {
        const NhanVien* dangxet = thutu[i];
        int j = i;
        while (j > 0 &&
               (thutu[j-1]->TEN > dangxet->TEN ||
                (thutu[j-1]->TEN == dangxet->TEN &&
                 thutu[j-1]->HO > dangxet->HO))) {
            thutu[j] = thutu[j-1];
            j--;
        }
        thutu[j] = dangxet;
    }

    int trang = 0;
    int pageSize = 12; // Co dinh 12 dong/trang dong bo 100% voi UI.cpp
    int soTrang = ds.soLuong == 0 ? 1 : (ds.soLuong + pageSize - 1) / pageSize;

    HienBangNhanVien(thutu, ds.soLuong, trang);

    // Vong lap dieu khien phan trang danh sach nhan vien
    while (true) {
        int c = _getch();
        if (c == 27 || c == 13) return; // Phim ESC hoac Enter de quay ve Menu
        
        if (c == 0 || c == 224 || c == -32) {
            int phim = _getch();
            int trangCu = trang;
            if ((phim == 75 || phim == 72 || phim == 73) && trang > 0) { // Mui ten Trai, Up, PgUp -> Trang truoc
                trang--;
            }
            else if ((phim == 77 || phim == 80 || phim == 81) && trang < soTrang - 1) { // Mui ten Phai, Down, PgDn -> Trang sau
                trang++;
            }
            else if (phim == 71) { // Phim Home -> Trang dau
                trang = 0;
            }
            else if (phim == 79) { // Phim End -> Trang cuoi
                trang = soTrang - 1;
            }

            if (trang != trangCu) {
                HienBangNhanVien(thutu, ds.soLuong, trang);
            }
        }
    }
}

// Giai phong tat ca con tro nhan vien va dua so luong ve 0
void GiaiPhongDSNhanVien(DanhSachNhanVien &dsNV) {
    for (int i = 0; i < dsNV.soLuong; i++) {
        delete dsNV.ds[i];
        dsNV.ds[i] = nullptr;
    }
    dsNV.soLuong = 0;
}
