#include "VatTu.h"
#include <iostream>
#include <fstream>

using namespace std;

// Thuat toan tim kiem tren Cay Nhi Phan Tim Kiem (BST)
NodeVatTu* TimKiemVatTu(TreeVatTu root, string maVT) {
    NodeVatTu* p = root;
    while (p != NULL) {
        if (p->data.MAVT == maVT) return p; // Tim thay Node chua MAVT
        if (maVT < p->data.MAVT) {
            p = p->left;
        } else {
            p = p->right;
        }
    }
    return NULL; // Khong tim thay
}

// Ham phu tro chen 1 vat tu vao Cay Nhi Phan
void ThemVatTuVaoCay(TreeVatTu &root, VatTu vt) {
    if (root == NULL) {
        root = new NodeVatTu();
        root->data = vt;
        root->left = NULL;
        root->right = NULL;
    } else if (vt.MAVT < root->data.MAVT) {
        ThemVatTuVaoCay(root->left, vt);
    } else if (vt.MAVT > root->data.MAVT) {
        ThemVatTuVaoCay(root->right, vt);
    }
}

// Doc file VatTu.txt va nap vao Cay Nhi Phan
void DocFileVatTu(TreeVatTu &root) {
    ifstream f("VatTu.txt", ios::in);
    if (!f.is_open()) {
        cout << "Thong bao: Khong tim thay file VatTu.txt!\n";
        return;
    }

    int n;
    if (!(f >> n)) {
        f.close();
        return;
    }

    for (int i = 0; i < n; i++) {
        VatTu vt;
        f >> vt.MAVT;
        f.ignore();
        getline(f, vt.TENVT, '|');
        getline(f, vt.DVT, '|');
        f >> vt.soLuongTon;

        ThemVatTuVaoCay(root, vt);
    }

    f.close();
    cout << "Doc file VatTu.txt thanh cong!\n";
}

// Ham phu tro duyet LNR de ghi cay vat tu ra file
void GhiCayVatTuNha(TreeVatTu root, ofstream &f) {
    if (root != NULL) {
        GhiCayVatTuNha(root->left, f);
        f << root->data.MAVT << " "
          << root->data.TENVT << "|"
          << root->data.DVT << "|"
          << root->data.soLuongTon << endl;
        GhiCayVatTuNha(root->right, f);
    }
}

// Dem so nut tren cay
int DemSoVatTu(TreeVatTu root) {
    if (root == NULL) return 0;
    return 1 + DemSoVatTu(root->left) + DemSoVatTu(root->right);
}

// Ghi toan bo cay vat tu ra file VatTu.txt
void LuuFileVatTu(TreeVatTu root) {
    ofstream f("VatTu.txt", ios::out);
    if (!f.is_open()) {
        cout << "Loi: Khong the mo file VatTu.txt de ghi!\n";
        return;
    }

    int tongVT = DemSoVatTu(root);
    f << tongVT << endl;
    GhiCayVatTuNha(root, f);

    f.close();
    cout << "Ghi file VatTu.txt thanh cong!\n";
}

// Giai phong cay nhi phan
void GiaiPhongCayVatTu(TreeVatTu &root) {
    if (root != NULL) {
        GiaiPhongCayVatTu(root->left);
        GiaiPhongCayVatTu(root->right);
        delete root;
        root = NULL;
    }
}
