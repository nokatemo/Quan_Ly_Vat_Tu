# LỘ TRÌNH PHÁT TRIỂN ĐỒ ÁN DSA
## Đề tài: Quản lý nhập xuất vật tư

---

## 1. TỔNG QUAN ĐỒ ÁN

### 1.1. Mục tiêu
Xây dựng chương trình console quản lý nhập xuất vật tư của một cửa hàng, sử dụng các cấu trúc dữ liệu:
- Cây nhị phân tìm kiếm (BST) cho danh sách Vật tư.
- Mảng con trỏ cho danh sách Nhân viên.
- Danh sách liên kết đơn (DSLK) cho Hóa đơn và Chi tiết hóa đơn.

### 1.2. Công nghệ sử dụng
| Thành phần | Công nghệ |
|---|---|
| Ngôn ngữ | C++ (Dev-C++ 5.9.2) |
| Chuỗi mô tả (HO, TEN, TENVT, DVT) | std::string |
| Mã định danh (MAVT, MANV, SoHD) | char[] |
| Cấu trúc dữ liệu | Tự code (BST, DSLK, mảng con trỏ) |
| File I/O | fstream + file text (dấu |) |
| Giao diện | iostream, iomanip (console) |
| Quản lý mã nguồn | Git + GitHub |

### 1.3. Thành viên và phân công
| Thành viên | MSSV | Module chính | Câu phụ trách | Branch |
|---|---|---|---|---|
| Trần Trung Nguyên | N25DECE105 | Nhân viên + Menu + Validate | c, d, i | module-nhan-vien |
| Ngô Minh Tiến | N25DECE121 | Vật tư | a, b, h | module-vat-tu |
| Bùi Vũ Nguyên Khoa | N25DECE097 | Hóa đơn + CT_HĐ + Tích hợp | e, f, g | module-hoa-don |

---

## 2. KIẾN TRÚC HỆ THỐNG

### 2.1. Sơ đồ quan hệ dữ liệu
Nhanvien (mảng con trỏ, tối đa 500)
  - MANV, HO, TEN, PHAI
  - dshd --> Hoadon (DSLK đơn)
              - SoHD, NgayLap, Loai, MANV
              - dscthd --> CT_Hoadon (DSLK đơn)
                            - MAVT --> Vattu (BST)
                            - Soluong, Dongia, VAT

### 2.2. Cấu trúc thư mục
quan-ly-vat-tu/
├── README.md              <- Giới thiệu đồ án, thành viên
├── THIET_KE.md            <- Thiết kế struct, quan hệ dữ liệu
├── NHAT_KY.md             <- Nhật ký tiến độ từng ngày
├── .gitignore             <- File không up lên GitHub
├── src/                   <- Code nguồn
├── data/                  <- File dữ liệu mẫu
└── docs/                  <- Báo cáo, slide, roadmap

### 2.3. Các module chính
| Module | File | Người phụ trách |
|---|---|---|
| Menu + Validate | menu.cpp/.h, validate.cpp/.h | Nguyên |
| Vật tư (BST) | vattu.cpp/.h | Tiến |
| Nhân viên (mảng con trỏ) | nhanvien.cpp/.h | Nguyên |
| Hóa đơn + CT_HĐ (DSLK) | hoadon.cpp/.h, cthd.cpp/.h | Khoa |
| Tích hợp | main.cpp | Khoa |

---

## 3. LỘ TRÌNH 8 TUẦN

### TUẦN 1: NỀN TẢNG C++ + MẢNG CON TRỎ + GIT
Mục tiêu: Cả 3 nắm pointer, struct, mảng con trỏ, tách file, Git.

| Người | Học | Bài tập |
|---|---|---|
| Cả 3 | Pointer, Reference, new/delete, std::string, struct | Mảng động số nguyên |
| Nguyên | Validate, menu console | Menu + validate cơ bản |
| Tiến | Struct + sort | Sort struct theo tên |
| Khoa | DSLK đơn | DSLK quản lý sinh viên |

Sản phẩm: Menu chạy được, BST số nguyên, DSLK đơn, repo GitHub có cấu trúc.

---

### TUẦN 2: BST + FILE I/O + NGÀY THÁNG
Mục tiêu: Cả 3 nắm BST, file I/O, ngày tháng. Chốt struct chung.

| Người | Học | Bài tập |
|---|---|---|
| Cả 3 | BST insert/search/delete, file I/O, Date | BST vật tư mini |
| Nguyên | File I/O + validate ngày | Đọc/ghi file nhân viên |
| Tiến | BST delete + sort theo tên | BST vật tư đầy đủ |
| Khoa | DSLK nâng cao + thiết kế | DSLK hóa đơn + CTHD |

Sản phẩm: Struct chung đã chốt, BST Vattu, DSLK Hoadon, file I/O mẫu.

---

### TUẦN 3: CHỐT THIẾT KẾ + BẮT ĐẦU CODE
Mục tiêu: Chốt toàn bộ thiết kế, viết header chung, menu chính, bắt đầu code.

| Người | Công việc | Deliverable |
|---|---|---|
| Nguyên | menu.cpp, validate.cpp, nhanvien.cpp (core) | Menu + Nhân viên thêm/xóa/sửa |
| Tiến | vattu.cpp (BST insert/search/delete) | BST Vật tư core |
| Khoa | main.cpp, hoadon.cpp, cthd.cpp (core) | Main + Hoadon core |

Sản phẩm: main.cpp chạy được menu, validate hoàn chỉnh, BST Vattu core, Hoadon core.

---

### TUẦN 4: CODE MODULE CHÍNH (PHẦN 1)
Mục tiêu: Hoàn thiện phần core của từng module.

| Người | Công việc | Câu |
|---|---|---|
| Nguyên | In NV theo tên/họ + file NV | c, d |
| Tiến | In VT theo tên + file VT | a, b |
| Khoa | Lập + in hóa đơn + file HĐ | e, f |

Sản phẩm: Câu a, b, c, d, e, f hoàn chỉnh, file I/O hoạt động.

---

### TUẦN 5: CODE MODULE CHÍNH (PHẦN 2) + SỬA LỖI
Mục tiêu: Hoàn thiện các câu còn lại, sửa lỗi, test biên.

| Người | Công việc | Câu |
|---|---|---|
| Nguyên | Doanh thu từng tháng trong năm | i |
| Tiến | Top 10 vật tư doanh thu | h |
| Khoa | Thống kê HĐ theo khoảng thời gian | g |

Sản phẩm: Đủ 9 chức năng a-i, test tích hợp.

---

### TUẦN 6: HOÀN THIỆN + TEST BIÊN + TÍCH HỢP
Mục tiêu: Tích hợp toàn bộ, test biên, sửa lỗi, hoàn thiện file I/O.

| Người | Công việc |
|---|---|
| Nguyên | Test biên Nhân viên + Menu + Validate |
| Tiến | Test biên Vật tư + Top 10 |
| Khoa | Test biên Hoadon + Thống kê |

Test biên cần làm: mã trùng, tên rỗng, số âm, ngày sai, xuất quá tồn, file lỗi, 500 nhân viên, BST 1 nút.

Sản phẩm: Tất cả chức năng chạy được, file I/O hoạt động, danh sách test case.

---

### TUẦN 7: MOCK VẤN ĐÁP + SỬA LỖI + HOÀN THIỆN
Mục tiêu: Mock vấn đáp, sửa lỗi cuối, hoàn thiện báo cáo.

| Ngày | Công việc |
|---|---|
| 1-2 | Mock vấn đáp chéo (15 phút/người) |
| 3-4 | Sửa lỗi, hoàn thiện validate |
| 5-6 | Viết báo cáo, vẽ sơ đồ, chuẩn bị slide |
| 7 | Chạy demo lần cuối, backup |

Sản phẩm: Báo cáo hoàn chỉnh, slide demo, code đã sửa lỗi.

---

### TUẦN 8: BÁO CÁO + DEMO + DỰ PHÒNG
Mục tiêu: Hoàn thiện báo cáo, demo, dự phòng sửa lỗi.

| Ngày | Công việc |
|---|---|
| 1-2 | Hoàn thiện báo cáo, slide |
| 3-4 | Ôn vấn đáp |
| 5-6 | Dự phòng sửa lỗi |
| 7 | Nộp bài, demo chính thức |

Sản phẩm: Báo cáo nộp, slide, code backup, file dữ liệu mẫu.

---

## 4. QUY TRÌNH LÀM VIỆC NHÓM

### 4.1. Git Workflow
1. Mỗi người làm việc trên branch riêng (module-nhan-vien, module-vat-tu, module-hoa-don).
2. Không commit trực tiếp vào main.
3. Commit message rõ ràng: "Ngay X: lam gi".
4. Push ít nhất 1 lần/ngày.
5. Pull trước khi push để tránh conflict.
6. Merge vào main vào cuối tuần, sau khi cả nhóm review.

### 4.2. Lịch họp nhóm
- Đầu tuần: Phân việc, giải đáp thắc mắc.
- Cuối tuần: Review, merge, test, đánh giá chéo.

### 4.3. Definition of Done
Một chức năng được coi là xong khi:
- Chạy không crash.
- Có validate nhập liệu.
- Có test case biên.
- Đã merge vào main.
- Cả nhóm đọc hiểu code.

### 4.4. Quy tắc code
- Dùng typedef cho con trỏ: typedef Hoadon* PTR_HOADON;
- Dùng NULL thay vì nullptr.
- Comment tiếng Việt không dấu.
- Tách file .h/.cpp rõ ràng.
- Mỗi hàm chỉ làm 1 việc.

---

## 5. RỦI RO & DỰ PHÒNG

| Rủi ro | Dự phòng |
|---|---|
| Nguyên không theo kịp | Tiến/Khoa kèm, giao phần dễ hơn |
| BST delete khó | Tiến học trước tuần 2 |
| Câu e phức tạp | Khoa làm sớm từ tuần 3 |
| File I/O lỗi | Làm từ tuần 2-3, test nhiều lần |
| Tích hợp lỗi | Merge sớm từ tuần 3 |
| Vấn đáp yếu | Mock từ tuần 7 |
| Hết thời gian | Ưu tiên a-g trước, h-i sau |

---

## 6. TIÊU CHÍ ĐÁNH GIÁ

| Tiêu chí | Trọng số |
|---|---|
| Đúng cấu trúc dữ liệu (BST, DSLK, mảng con trỏ) | 30% |
| Đủ 9 chức năng a-i | 25% |
| Validate + xử lý lỗi | 15% |
| File I/O hoạt động | 10% |
| Giao diện console rõ ràng | 10% |
| Vấn đáp + báo cáo | 10% |

---

*Cập nhật lần cuối: [12/10/2026]*
