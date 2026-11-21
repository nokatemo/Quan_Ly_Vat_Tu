#include "NhanVien.h"
#include "Validate.h"
#include "UI.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// ==========================================================
// 1. HAM TIM KIEM NHI PHAN (BINARY SEARCH) THEO MA NHAN VIEN
// Mang ds.ds[] luon duoc sap xep tang dan theo MANV
// ==========================================================
int TimKiemNhanVien(const DanhSachNhanVien& ds, const string& maNV) {
    int Left = 0;                
    int Right = ds.soLuong - 1;  

    while (Left <= Right) {
        int Mid = (Left + Right) / 2; 

        if (ds.ds[Mid]->MANV == maNV) {
            return Mid; 
        }
        if (maNV < ds.ds[Mid]->MANV) {
            Right = Mid - 1; 
        } else {
            Left = Mid + 1;  
        }
    }
    return -1;
}

// ==========================================================
// 2. HAM CHEN NHAN VIEN VAO MANG THEO THU TU TANG DAN MA NV
// ==========================================================
int ChenNhanVienTheoMa(DanhSachNhanVien& ds, NhanVien* nvMoi) {
    int i = ds.soLuong; // Mac dinh chen o cuoi mang

    // Doi cac nhan vien co MANV lon hon sang phai 1 o de nhuong cho
    while (i > 0 && ds.ds[i - 1]->MANV > nvMoi->MANV) {
        ds.ds[i] = ds.ds[i - 1];
        i--;
    }

    ds.ds[i] = nvMoi; 
    ds.soLuong++;            
    return i;
}

// ==========================================================
// 3. DOC VA GHI FILE CO BAN (DUNG IFSTREAM / OFSTREAM)
// Moi dong trong NhanVien.txt co dang: MANV|Ho|Ten|Phai
// ==========================================================

bool GhiFileNhanVien(const DanhSachNhanVien& ds, const string& tenFile) {
    ofstream fileOut(tenFile.c_str()); // Mo file de ghi
    if (!fileOut.is_open()) {
        return false;
    }

    for (int i = 0; i < ds.soLuong; i++) {
        fileOut << ds.ds[i]->MANV << "|"
                << ds.ds[i]->ho   << "|"
                << ds.ds[i]->ten  << "|"
                << ds.ds[i]->phai << "\n";
    }

    fileOut.close();
    return true;
}

bool DocFileNhanVien(DanhSachNhanVien& ds, const string& tenFile) {
    ifstream fileIn(tenFile.c_str()); // Mo file de doc
    if (!fileIn.is_open()) {
        return true; // Chua co file thi coi nhu danh sach ban dau rong (0 NV)
    }

    string maNV, ho, ten, phai;

    // Doc tung dong theo dau ngan cach '|'
    while (getline(fileIn, maNV, '|')) {
        getline(fileIn, ho, '|');
        getline(fileIn, ten, '|');
        getline(fileIn, phai);

        // Xoa ky tu xuong dong '\r' o cuoi dong (neu co tren Windows)
        if (!phai.empty() && phai.back() == '\r') {
            phai.pop_back();
        }

        // Bo qua dong trong hoac khi mang da day 500 nguoi
        if (maNV.empty() || ds.soLuong >= 500) {
            continue;
        }

        // Neu ma NV chua ton tai thi tao node moi va chen vao mang
        if (TimKiemNhanVien(ds, maNV) == -1) {
            NhanVien* nvMoi = new NhanVien;
            nvMoi->MANV = maNV;
            nvMoi->ho   = ho;
            nvMoi->ten  = ten;
            nvMoi->phai = phai;
            nvMoi->dshd = NULL; // Chua co hoa don nao

            ChenNhanVienTheoMa(ds, nvMoi);
        }
    }

    fileIn.close();
    return true;
}

// ==========================================================
// 4. HAM NHAP NHAN VIEN TREN FORM & CAP NHAT BANG BEN DUOI
// Moi viec chuan hoa ky tu deu goi tu Validate.cpp
// ==========================================================
bool NhapMotNhanVien(DanhSachNhanVien& ds, const string& tenFile,
                     int& trangDS, int& viTriVuaThem) {
    if (ds.soLuong >= 500) {
        return false;
    }

    NhanVien nv = {"", "", "", "", NULL};                  // Luu du lieu 4 o dang nhap
    string* oNhap[4] = {&nv.MANV, &nv.ho, &nv.ten, &nv.phai}; // Con tro tro vao 4 o
    const int gioiHan[4] = {5, 20, 10, 3};                 // So ky tu toi da cua tung o
    int oDangChon = 0;                                     // 0:MANV, 1:Ho, 2:Ten, 3:Phai, 4:Nut Luu
    string thongBaoLoi = "";

    while (true) {
        int doDaiChuoi = (oDangChon < 4) ? (int)oNhap[oDangChon]->length() : 0;
        HienFormNhanVien(nv, oDangChon, doDaiChuoi, thongBaoLoi);

        int c = _getch();
        if (c == 27) return false; // Phim Esc: thoat ve menu chinh

        bool bamNutLuu = false;

        // 1. Xu ly phim mui ten Len/Xuong, F2, PgUp/PgDn
        if (c == 0 || c == 224) {
            int phim = _getch();
            int soTrang = (ds.soLuong == 0) ? 1 : (ds.soLuong + SO_NV_MOI_TRANG_NHAP - 1) / SO_NV_MOI_TRANG_NHAP;

            if (phim == 72 || phim == 80) { // 72: Mui ten Len, 80: Mui ten Xuong
                if (oDangChon < 4) XoaKhoangTrangCuoi(*oNhap[oDangChon]);
                oDangChon = (phim == 72) ? (oDangChon + 4) % 5 : (oDangChon + 1) % 5;
                thongBaoLoi = "";
            } else if (phim == 60) { // F2: Luu
                bamNutLuu = true;
            } else if (phim == 73 && trangDS > 0) { // PgUp: Trang truoc
                trangDS--;
                HienBangNhanVienTheoMaKhiNhap(ds.ds, ds.soLuong, trangDS, viTriVuaThem);
            } else if (phim == 81 && trangDS < soTrang - 1) { // PgDn: Trang sau
                trangDS++;
                HienBangNhanVienTheoMaKhiNhap(ds.ds, ds.soLuong, trangDS, viTriVuaThem);
            }
            if (!bamNutLuu) continue;
        }
        // 2. Xu ly phim Enter va Tab
        else if (c == 13 && oDangChon == 4) {
            bamNutLuu = true; // Enter tai nut Luu
        } else if (c == 13 || c == 9) { // Enter hoac Tab tai o nhap -> sang o tiep theo
            if (oDangChon < 4) XoaKhoangTrangCuoi(*oNhap[oDangChon]);
            oDangChon = (oDangChon + 1) % 5;
            thongBaoLoi = "";
            continue;
        }

        // 3. Kiem tra du lieu va Luu nhan vien
        if (bamNutLuu) {
            for (int i = 1; i < 4; i++) XoaKhoangTrangCuoi(*oNhap[i]);

            int oBiLoi = -1;
            if (chuoirong(nv.MANV)) {
                oBiLoi = 0;
                thongBaoLoi = "Ma nhan vien khong duoc de trong.";
            } else if (TimKiemNhanVien(ds, nv.MANV) != -1) {
                oBiLoi = 0;
                thongBaoLoi = "Ma da ton tai. Vui long nhap ma khac.";
            } else if (chuoirong(nv.ho)) {
                oBiLoi = 1;
                thongBaoLoi = "Ho va ten dem khong duoc de trong.";
            } else if (chuoirong(nv.ten)) {
                oBiLoi = 2;
                thongBaoLoi = "Ten khong duoc de trong.";
            } else if (nv.phai != "Nam" && nv.phai != "Nu") {
                oBiLoi = 3;
                thongBaoLoi = "Phai chi nhan Nam hoac Nu.";
            }

            if (oBiLoi == -1) {
                NhanVien* nvMoi = new NhanVien(nv);
                int viTriMoi = ChenNhanVienTheoMa(ds, nvMoi);
                GhiFileNhanVien(ds, tenFile);

                viTriVuaThem = viTriMoi;
                trangDS = viTriMoi / SO_NV_MOI_TRANG_NHAP;
                return true;
            }
            oDangChon = oBiLoi;
            continue;
        }

        // 4. Goi ham chuan hoa ky tu ben Validate.cpp cho o dang chon
        if (oDangChon == 4) continue;

        int ketQua = (oDangChon == 0)
            ? XuLyPhimMaID(nv.MANV, c, gioiHan[0])
            : XuLyPhimChuoiChuanHoa(*oNhap[oDangChon], c, gioiHan[oDangChon]);

        if (ketQua == 1) {
            thongBaoLoi = "";
        } else if (ketQua == -1) {
            thongBaoLoi = "O nay toi da " + to_string(gioiHan[oDangChon]) + " ky tu.";
        }
    }
}

bool ThemNhanVien(DanhSachNhanVien& ds, const string& tenFile) {
    int soLuongBanDau = ds.soLuong;
    int trangDS = 0;
    int viTriVuaThem = -1;

    VeKhungNhanVien("THEM VA CAP NHAT NHAN VIEN");
    HienSoLuongNhanVien(ds.soLuong);
    HienBangNhanVienTheoMaKhiNhap(ds.ds, ds.soLuong, trangDS, viTriVuaThem);

    while (ds.soLuong < 500 && NhapMotNhanVien(ds, tenFile, trangDS, viTriVuaThem)) {
        HienSoLuongNhanVien(ds.soLuong);
        HienBangNhanVienTheoMaKhiNhap(ds.ds, ds.soLuong, trangDS, viTriVuaThem);
    }

    if (ds.soLuong >= 500) {
        HienThongBaoDayNhanVien();
        while (true) {
            int c = _getch();
            if (c == 27 || c == 13) break;
            if (c == 0 || c == 224) {
                int phim = _getch();
                int soTrang = (ds.soLuong == 0) ? 1 : (ds.soLuong + SO_NV_MOI_TRANG_NHAP - 1) / SO_NV_MOI_TRANG_NHAP;
                if (phim == 73 && trangDS > 0) {
                    trangDS--;
                    HienBangNhanVienTheoMaKhiNhap(ds.ds, ds.soLuong, trangDS, viTriVuaThem);
                } else if (phim == 81 && trangDS < soTrang - 1) {
                    trangDS++;
                    HienBangNhanVienTheoMaKhiNhap(ds.ds, ds.soLuong, trangDS, viTriVuaThem);
                }
            }
        }
    }
    return ds.soLuong > soLuongBanDau;
}

// ==========================================================
// 5. IN DANH SACH NHAN VIEN SAP XEP THEO TEN, HO (BUBBLE SORT)
// ==========================================================
void InDanhSachNhanVien(const DanhSachNhanVien& ds) {
    const NhanVien* thutu[500];
    for (int i = 0; i < ds.soLuong; i++) {
        thutu[i] = ds.ds[i];
    }

    // Bubble Sort (Sap xep noi bot) theo Ten, neu trung Ten thi xep theo Ho
    for (int i = 0; i < ds.soLuong - 1; i++) {
        for (int j = 0; j < ds.soLuong - 1 - i; j++) {
            if (thutu[j]->ten > thutu[j + 1]->ten ||
                (thutu[j]->ten == thutu[j + 1]->ten && thutu[j]->ho > thutu[j + 1]->ho)) {
                const NhanVien* tam = thutu[j];
                thutu[j] = thutu[j + 1];
                thutu[j + 1] = tam;
            }
        }
    }

    int trang = 0;
    int soTrang = (ds.soLuong == 0) ? 1 : (ds.soLuong + SO_NHAN_VIEN_MOI_TRANG - 1) / SO_NHAN_VIEN_MOI_TRANG;
    HienBangNhanVien(thutu, ds.soLuong, trang);

    while (true) {
        int c = _getch();
        if (c == 27 || c == 13) return;
        if (c != 0 && c != 224) continue;

        int phim = _getch();
        int trangCu = trang;
        if ((phim == 75 || phim == 72 || phim == 73) && trang > 0) trang--;
        else if ((phim == 77 || phim == 80 || phim == 81) && trang < soTrang - 1) trang++;
        else if (phim == 71) trang = 0;
        else if (phim == 79) trang = soTrang - 1;

        if (trang != trangCu) {
            HienBangNhanVien(thutu, ds.soLuong, trang);
        }
    }
}
