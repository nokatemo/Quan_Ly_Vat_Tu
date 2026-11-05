#ifndef VATTU_H
#define VATTU_H

#include "struct.h"

// Tim kiem vat tu tren Cay Nhi Phan theo MAVT
NodeVatTu* TimKiemVatTu(TreeVatTu root, string maVT);

// Doc file danh sach vat tu tu VatTu.txt
void DocFileVatTu(TreeVatTu &root);

// Ghi file danh sach vat tu ra VatTu.txt
void LuuFileVatTu(TreeVatTu root);

// Giai phong bo nho cay vat tu
void GiaiPhongCayVatTu(TreeVatTu &root);

#endif
