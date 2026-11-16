#include "Validate.h"
#include<iostream>
#include<string>
#include "NhanVien.h"
#include "UI.h"
#include <cctype>
#include <fstream>
#include <sstream>
#include <cstdio>



using namespace std;

int TimKiemNhanVien(const DanhSachNhanVien& ds, const string& maNV){
 int Left = 0;
 int Right = ds.soLuong - 1;
 
 while (Left <= Right){
 	int Mid = Left + ((Right - Left ) / 2);
 	
 	if (ds.ds[Mid]->MANV == maNV){
 		return Mid;
	 }
	if (maNV < ds.ds[Mid]->MANV) {
		Right = Mid - 1;
	}
	else {
		Left = Mid + 1;
	}
 }
 return -1;
}

namespace {
    // Chi doi hoa/thuong, giu nguyen do dai de con tro khong bi nhay khi dang sua.
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

    bool ThongTinNhanVienHopLe(const NhanVien& nv) {
        if (nv.MANV.empty() || nv.MANV.size() > 5 || chuoirong(nv.ho) || nv.ho.size() > 20 ||
            chuoirong(nv.ten) || nv.ten.size() > 10 || (nv.phai != "Nam" && nv.phai != "Nu")) return false;
        for (unsigned char c : nv.MANV) if (!isalnum(c) || islower(c)) return false;
        for (unsigned char c : nv.ho) if (!isalpha(c) && c != ' ') return false;
        for (unsigned char c : nv.ten) if (!isalpha(c) && c != ' ') return false;
        return true;
    }

    int ChenNhanVienTheoMa(DanhSachNhanVien& ds, NhanVien* nv) {
        int i = ds.soLuong;
        while (i > 0 && ds.ds[i - 1]->MANV > nv->MANV) {
            ds.ds[i] = ds.ds[i - 1];
            i--;
        }
        ds.ds[i] = nv;
        ds.soLuong++;
        return i;
    }

bool NhapMotNhanVien(DanhSachNhanVien& ds, const string& tenFile) {
    if (ds.soLuong >= 500) {
        return false;
    }

    NhanVien nv = {"", "", "", "", NULL};
    string* oNhap[] = {&nv.MANV, &nv.ho, &nv.ten, &nv.phai};
    const size_t gioiHan[] = {5, 20, 10, 3};
    int oDangChon = 0;
    size_t viTri = 0;
    string thongBao;

    auto chuyenO = [&](int oMoi) {
        if (oDangChon > 0 && oDangChon < 4) {
            *oNhap[oDangChon] = ChuanHoaThongTinNhanVien(*oNhap[oDangChon]);
        }
        oDangChon = oMoi;
        viTri = oMoi < 4 ? oNhap[oMoi]->size() : 0;
        thongBao.clear();
    };

    while (true) {
        HienFormNhanVien(nv, oDangChon, static_cast<int>(viTri), thongBao);
        int c = _getch();
        if (c == 27) return false;
        bool luu = false;

        if (c == 0 || c == 224) {
            int phim = _getch();
            if (phim == 72) chuyenO((oDangChon + 4) % 5);
            else if (phim == 80) chuyenO((oDangChon + 1) % 5);
            else if (phim == 60) luu = true; // F2
            else if (oDangChon < 4) {
                string& giaTri = *oNhap[oDangChon];
                if (phim == 75 && viTri > 0) viTri--;
                else if (phim == 77 && viTri < giaTri.size()) viTri++;
                else if (phim == 71) viTri = 0;
                else if (phim == 79) viTri = giaTri.size();
                else if (phim == 83 && viTri < giaTri.size()) {
                    giaTri.erase(viTri, 1);
                    if (oDangChon > 0) VietHoaDauTu(giaTri);
                    thongBao.clear();
                }
            }
            if (!luu) continue;
        } else if (c == 13 && oDangChon == 4) {
            luu = true;
        } else if (c == 13 || c == 9) {
            chuyenO((oDangChon + 1) % 5);
            continue;
        }

        if (luu) {
            nv.ho = ChuanHoaThongTinNhanVien(nv.ho);
            nv.ten = ChuanHoaThongTinNhanVien(nv.ten);
            nv.phai = ChuanHoaThongTinNhanVien(nv.phai);
            int oLoi = -1;
            if (chuoirong(nv.MANV)) {
                oLoi = 0;
                thongBao = "Ma nhan vien khong duoc de trong.";
            } else if (TimKiemNhanVien(ds, nv.MANV) != -1) {
                oLoi = 0;
                thongBao = "Ma da ton tai. Vui long nhap ma khac.";
            } else if (chuoirong(nv.ho)) {
                oLoi = 1;
                thongBao = "Ho va ten dem khong duoc de trong.";
            } else if (chuoirong(nv.ten)) {
                oLoi = 2;
                thongBao = "Ten khong duoc de trong.";
            } else if (nv.phai != "Nam" && nv.phai != "Nu") {
                oLoi = 3;
                thongBao = "Phai chi nhan Nam hoac Nu.";
            }
            if (oLoi == -1) {
                NhanVien* moi = new NhanVien(nv);
                int viTriMoi = ChenNhanVienTheoMa(ds, moi);
                if (GhiFileNhanVien(ds, tenFile)) return true;

                // Ghi that bai thi giu lai form de thu lai, khong bao da luu.
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

string DuongDanFileNhanVien(const string& tenFile) {
    if (tenFile.find_first_of("/\\") != string::npos || tenFile.find(':') != string::npos) return tenFile;
    char duongDan[MAX_PATH];
    DWORD doDai = GetModuleFileNameA(nullptr, duongDan, MAX_PATH);
    if (doDai == 0 || doDai >= MAX_PATH) return tenFile;
    string chuongTrinh(duongDan, doDai);
    size_t viTri = chuongTrinh.find_last_of("/\\");
    return viTri == string::npos ? tenFile : chuongTrinh.substr(0, viTri + 1) + tenFile;
}

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
        file << nv.MANV << '|' << nv.ho << '|' << nv.ten << '|' << nv.phai << '\n';
    }
    file.close();
    if (!file || !MoveFileExA(fileTam.c_str(), duongDan.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
        remove(fileTam.c_str());
        return false;
    }
    return true;
}

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
        if (dongDau && dong.compare(0, 3, "\xEF\xBB\xBF") == 0) dong.erase(0, 3);
        dongDau = false;
        if (!dong.empty() && dong.back() == '\r') dong.pop_back();
        if (dong.find_first_not_of(" \t") == string::npos) continue;
        if (tam.soLuong >= 500) { hopLe = false; break; }
        NhanVien nv = {"", "", "", "", NULL};
        istringstream tach(dong);
        if (!getline(tach, nv.MANV, '|') || !getline(tach, nv.ho, '|') ||
            !getline(tach, nv.ten, '|') || !getline(tach, nv.phai)) { hopLe = false; break; }
        for (char& c : nv.MANV) c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
        nv.ho = ChuanHoaThongTinNhanVien(nv.ho);
        nv.ten = ChuanHoaThongTinNhanVien(nv.ten);
        nv.phai = ChuanHoaThongTinNhanVien(nv.phai);
        if (!ThongTinNhanVienHopLe(nv) || TimKiemNhanVien(tam, nv.MANV) != -1) { hopLe = false; break; }
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
  
  
void InDanhSachNhanVien(const DanhSachNhanVien& ds) {
    const NhanVien* thutu[500];
    for (int i = 0; i < ds.soLuong; i++) {
        thutu[i] = ds.ds[i];
    }

    for (int i = 1; i < ds.soLuong; i++) {
        const NhanVien* dangxet = thutu[i];
        int j = i;
        while (j > 0 &&
               (thutu[j-1]->ten > dangxet->ten ||
                (thutu[j-1]->ten == dangxet->ten &&
                 thutu[j-1]->ho > dangxet->ho))) {
            thutu[j] = thutu[j-1];
            j--;
        }
        thutu[j] = dangxet;
    }

    int trang = 0;
    int soTrang = ds.soLuong == 0 ? 1 : (ds.soLuong + SO_NHAN_VIEN_MOI_TRANG - 1) / SO_NHAN_VIEN_MOI_TRANG;
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
        if (trang != trangCu) HienBangNhanVien(thutu, ds.soLuong, trang);
    }
}
  
     
   
     
     
     
     
     
  
  
  
   
   
   
   
   

