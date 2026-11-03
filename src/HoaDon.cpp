#include "HoaDon.h"
#include <iostream>
#include <fstream> 
#include <sstream>
using namespace std;

NodeCTHD* TaoNodeCTHD(ChiTietHoaDon ct) // Ham tra ve dia chi cua Node vua tao ( bao gom data va con tro next)
{
	NodeCTHD* p = new NodeCTHD; // Xin cap phat bo nho heap voi kieu du lieu la nodecthd
	p->data = ct;			
	p->next = NULL;		
	
	return p;	
}

void ThemCTHD(ListCTHD &dscthd, ChiTietHoaDon ct) 
{
    // 1. Tao node moi
    NodeCTHD* p = TaoNodeCTHD(ct); 
    if (p == NULL) return; // Phong truong hop tran RAM
    
    // 2. Cho node moi tro vao node dau hien tai
    p->next = dscthd; 
    
    // 3. Cap nhat node moi thanh node dau danh sach
    dscthd = p; 
}

void XoaCTHDTrongDSTam(ListCTHD &dscthd, string maVT) 
{
    if (dscthd == NULL) 
    {
        cout << "Danh sach dang rong!\n";
        return;
    }

    NodeCTHD* kieu = dscthd;
    NodeCTHD* bfkieu = NULL;

    // Duyet tim node co MAVT trung khop
    while (kieu != NULL && kieu->data.MAVT != maVT) 
    {
        bfkieu = kieu;        // Luu lai node hien tai lam node dung truoc
        kieu = kieu->next;    // Nhay sang node tiep theo
    }

    // Neu chay het danh sach ma khong tim thay maVT
    if (kieu == NULL) 
    {
        cout << "Khong tim thay maVT da nhap trong hoa don!\n";
        return;
    }

    // Neu node can xoa nam o DAU danh sach
    if (bfkieu == NULL) 
    {
        dscthd = dscthd->next;
    } 
    // Neu node can xoa nam o GIUA hoac CUOI danh sach
    else 
    {
        bfkieu->next = kieu->next;
    }

    delete kieu; // Giai phong RAM cua node bi xoa
    cout << "Da xoa vat tu thanh cong!\n";
}

void GiaiPhongDSCTHD(ListCTHD &dscthd)
{
	while (dscthd != NULL)
	{
		NodeCTHD *temp = dscthd;
		dscthd = dscthd->next;
		delete temp;
	}
	dscthd = NULL;
}

// ==========================
// HAM GHI FILE HOA DON 
// ==========================
void LuuFileHoaDon(DanhSachNhanVien dsNV) {
    ofstream f("HoaDon.txt", ios::out);

    if (!f.is_open()) {
        cout << "Loi: Khong the mo file HoaDon.txt de ghi!\n";
        return;
    }

    // 1. Dem so luong nhan vien thuc te co lap hoa don
    int demNVCoHD = 0;
    for (int i = 0; i < dsNV.soLuong; i++) {
        if (dsNV.ds[i]->dshd != NULL) {
            demNVCoHD++;
        }
    }

    f << demNVCoHD << endl;

    // 2. Duyet mang nhan vien
    for (int i = 0; i < dsNV.soLuong; i++) {
        NhanVien* nv = dsNV.ds[i];
        if (nv->dshd == NULL) continue;

        // Dem so luong hoa don cua NV
        int demHD = 0;
        NodeHoaDon* pHD = nv->dshd;
        while (pHD != NULL) {
            demHD++;
            pHD = pHD->next;
        }

        // Ghi dong NV: MANV|SoLuongHD
        f << nv->MANV << "|" << demHD << endl;

        // Duyet DSLK Hoa Don
        pHD = nv->dshd;
        while (pHD != NULL) {
            // Dem so chi tiet vat tu
            int demCTHD = 0;
            NodeCTHD* pCT = pHD->data.dscthd;
            while (pCT != NULL) {
                demCTHD++;
                pCT = pCT->next;
            }

            // Ghi dong Hoa Don: SoHD|Ngay|Thang|Nam|Loai|SoLuongCTHD
            f << pHD->data.soHD << "|"
              << pHD->data.ngayLap.ngay << "|"
              << pHD->data.ngayLap.thang << "|"
              << pHD->data.ngayLap.nam << "|"
              << pHD->data.loai << "|"
              << demCTHD << endl;

            // Duyet DSLK Chi Tiet Hoa Don
            pCT = pHD->data.dscthd;
            while (pCT != NULL) {
                // Ghi dong Chi Tiet: MAVT|SoLuong|DonGia|VAT
                f << pCT->data.MAVT << "|"
                  << pCT->data.soLuong << "|"
                  << pCT->data.donGia << "|"
                  << pCT->data.VAT << endl;
                pCT = pCT->next;
            }

            pHD = pHD->next;
        }
    }

    f.close();
    cout << "Ghi file HoaDon.txt thanh cong!\n";
}

// =======================
// HAM DOC FILE HOA DON 
// =======================
void DocFileHoaDon(DanhSachNhanVien &dsNV) {
    ifstream f("HoaDon.txt", ios::in);

    if (!f.is_open()) {
        cout << "Thong bao: Khong tim thay file HoaDon.txt!\n";
        return;
    }

    string line;
    if (!getline(f, line) || line.empty()) {
        f.close();
        return;
    }
    int soLuongNVCoHD = stoi(line);

    for (int i = 0; i < soLuongNVCoHD; i++) {
        if (!getline(f, line)) break;
        stringstream ssNV(line);
        string maNV, strSoHD;
        getline(ssNV, maNV, '|');
        getline(ssNV, strSoHD, '|');
        int soLuongHD = stoi(strSoHD);

        // Tim nhan vien trong mang
        int vtNV = -1;
        for (int k = 0; k < dsNV.soLuong; k++) {
            if (dsNV.ds[k]->MANV == maNV) {
                vtNV = k;
                break;
            }
        }

        // Doc danh sach hoa don cua NV nay
        for (int j = 0; j < soLuongHD; j++) {
            if (!getline(f, line)) break;
            stringstream ssHD(line);
            string strNgay, strThang, strNam, strLoai, strSoCTHD;

            HoaDon hd;
            hd.dscthd = NULL;

            getline(ssHD, hd.soHD, '|');
            getline(ssHD, strNgay, '|');
            getline(ssHD, strThang, '|');
            getline(ssHD, strNam, '|');
            getline(ssHD, strLoai, '|');
            getline(ssHD, strSoCTHD, '|');

            hd.ngayLap.ngay = stoi(strNgay);
            hd.ngayLap.thang = stoi(strThang);
            hd.ngayLap.nam = stoi(strNam);
            hd.loai = strLoai[0];
            int soLuongCTHD = stoi(strSoCTHD);

            // Doc danh sach chi tiet vat tu
            for (int k = 0; k < soLuongCTHD; k++) {
                if (!getline(f, line)) break;
                stringstream ssCT(line);
                string strSL, strDG, strVAT;
                ChiTietHoaDon ct;

                getline(ssCT, ct.MAVT, '|');
                getline(ssCT, strSL, '|');
                getline(ssCT, strDG, '|');
                getline(ssCT, strVAT, '|');

                ct.soLuong = stoi(strSL);
                ct.donGia = stod(strDG);
                ct.VAT = stof(strVAT);

                ThemCTHD(hd.dscthd, ct);
            }

            // Moc hoa don vao nhan vien
            if (vtNV != -1) {
                NodeHoaDon* pHD = new NodeHoaDon();
                pHD->data = hd;
                pHD->next = dsNV.ds[vtNV]->dshd;
                dsNV.ds[vtNV]->dshd = pHD;
            }
        }
    }

    f.close();
    cout << "Doc file HoaDon.txt va tai du lieu thanh cong!\n";
}
