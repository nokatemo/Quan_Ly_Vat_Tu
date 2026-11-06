#ifndef VATTU_H
#define VATTU_H
#include "UI.h"
#include "struct.h"
#include <string>
#include <vector>

using namespace std;

// ==========================================
// THAO TÁC CƠ BẢN TRÊN CÂY BST VẬT TƯ
// ==========================================
void initTreeVatTu(TreeVatTu &t);
NodeVatTu* searchVatTu(TreeVatTu t, string maVT);
bool insertVatTu(TreeVatTu &t, VatTu vt);
bool deleteVatTu(TreeVatTu &t, string maVT);
void freeTreeVatTu(TreeVatTu &t);

// ==========================================
// CHỨC NĂNG PHẦN TIẾN ĐẢM NHẬN (A & B)
// ==========================================
// Chức năng a: Cập nhật thông tin vật tư (Thêm / Xóa / Hiệu chỉnh)
void quanLyVatTu(TreeVatTu &t);

// Chức năng b: In danh sách vật tư tồn kho tăng dần theo TÊN
void inDSVatTuTheoTen(TreeVatTu t);

// ==========================================
// HÀM CẦU NỐI HỖ TRỢ KHOA & NGUYÊN
// ==========================================
// 1. Cập nhật số lượng tồn kho (soLuongThayDoi > 0: Nhập, < 0: Xuất)
bool CapNhatTonKho(TreeVatTu &root, string maVT, int soLuongThayDoi);

// 2. Lấy số lượng tồn hiện tại của 1 Vật tư
int getSoLuongTon(TreeVatTu t, string maVT);

// 3. Lấy tên vật tư dựa vào Mã VT (dùng cho Khoa khi in hóa đơn)
string getTenVatTu(TreeVatTu t, string maVT);

// --- HÀM ĐỌC VÀ LƯU FILE VẬT TƯ ---
void saveNodeToFile(TreeVatTu t, ofstream &fout);
bool SaveTreeVatTuToFile(TreeVatTu t, const string &filename = "VATTU.TXT");
bool LoadTreeVatTuFromFile(TreeVatTu &t, const string &filename = "VATTU.TXT");

#endif