# 🎓 C++ Student Management System

## 📌 Giới thiệu

Bài tập thực hành C++: **Quản lý danh sách sinh viên bằng mảng con trỏ cấp phát động**.

Mục tiêu của bài tập là vận dụng các kiến thức:

- `struct` trong C++
- Con trỏ và con trỏ cấp hai (`SinhVien**`)
- Cấp phát và giải phóng bộ nhớ động
- Thuật toán Bubble Sort
- Tham chiếu và hoán đổi con trỏ
- Hàm và xử lý dữ liệu
- Kiểm tra dữ liệu đầu vào

## 📋 Yêu cầu bài toán

Xây dựng chương trình quản lý danh sách `n` sinh viên với các chức năng nhập, xuất, sắp xếp và tìm kiếm.

### 1. Khai báo cấu trúc (1 điểm)

Tạo cấu trúc `SinhVien` gồm các thuộc tính:

| Thuộc tính | Kiểu dữ liệu | Mô tả |
|---|---|---|
| `MASV` | `char[11]` | Mã sinh viên, tối đa 10 ký tự |
| `HO` | `string` | Họ sinh viên |
| `TEN` | `string` | Tên sinh viên |
| `DTB` | `float` | Điểm trung bình |

### 2. Nhập danh sách sinh viên (2 điểm)

- Nhập số lượng sinh viên `n > 0`.
- Kiểm tra dữ liệu đầu vào, yêu cầu nhập lại nếu không hợp lệ.
- Sử dụng `SinhVien **ds` để quản lý danh sách.
- Cấp phát động bộ nhớ bằng `new`.
- Nhập đầy đủ thông tin từng sinh viên.
- Điểm trung bình phải nằm trong khoảng `[0, 10]`.
- Mã sinh viên không vượt quá 10 ký tự.

### 3. Xuất danh sách (1 điểm)

Viết hàm `xuatDS()` để hiển thị toàn bộ danh sách sinh viên, bao gồm:

- Mã sinh viên
- Họ
- Tên
- Điểm trung bình

### 4. Sắp xếp danh sách – Bubble Sort (2 điểm)

Viết hàm `sortTheoTen()` với yêu cầu:

- Sắp xếp tên sinh viên tăng dần theo bảng chữ cái.
- Nếu trùng tên, tiếp tục sắp xếp theo họ tăng dần.
- Bắt buộc sử dụng thuật toán **Bubble Sort**.
- Tự xây dựng hàm hoán đổi hai con trỏ sinh viên.
- Không hoán đổi dữ liệu trực tiếp của các đối tượng sinh viên.

### 5. Tìm sinh viên có điểm cao nhất (2 điểm)

Viết hàm tìm và xuất sinh viên có điểm trung bình cao nhất.

Nếu nhiều sinh viên cùng đạt điểm cao nhất, chương trình phải hiển thị tất cả sinh viên đó.

### 6. Giải phóng bộ nhớ (2 điểm)

- Giải phóng bộ nhớ từng sinh viên bằng `delete`.
- Giải phóng mảng con trỏ bằng `delete[]`.
- Đảm bảo không gây rò rỉ bộ nhớ.

---

## 🧪 Dữ liệu kiểm thử

### Input mẫu

| MASV | HO | TEN | DTB |
|---|---|---|---|
| SV01 | Nguyen | An | 8.5 |
| SV02 | Tran | Binh | 9.0 |
| SV03 | Le | An | 7.5 |
| SV04 | Pham | Dung | 9.0 |

### Kết quả sau khi sắp xếp

| MASV | HO | TEN | DTB |
|---|---|---|---|
| SV03 | Le | An | 7.5 |
| SV01 | Nguyen | An | 8.5 |
| SV02 | Tran | Binh | 9.0 |
| SV04 | Pham | Dung | 9.0 |

### Sinh viên có điểm trung bình cao nhất

| MASV | HO | TEN | DTB |
|---|---|---|---|
| SV02 | Tran | Binh | 9.0 |
| SV04 | Pham | Dung | 9.0 |

---

## ⚙️ Quy định kỹ thuật

1. Sử dụng ngôn ngữ C++.
2. Không sử dụng `vector` hoặc `std::sort()`.
3. Bắt buộc sử dụng mảng con trỏ cấp phát động `SinhVien**`.
4. Tách chương trình thành các hàm riêng biệt.
5. Sử dụng Bubble Sort để sắp xếp danh sách.
6. Kiểm tra dữ liệu nhập không hợp lệ.
7. Giải phóng toàn bộ bộ nhớ đã cấp phát.

## 📊 Thang điểm

| Nội dung | Điểm |
|---|---:|
| Khai báo cấu trúc | 1 |
| Nhập và cấp phát động | 2 |
| Xuất danh sách | 1 |
| Bubble Sort | 2 |
| Tìm điểm cao nhất | 2 |
| Giải phóng bộ nhớ | 2 |
| **Tổng cộng** | **10** |

---

## 🛠️ Công nghệ sử dụng

- **Ngôn ngữ:** C++
- **Kiến thức:** Struct, Pointers, Dynamic Memory Allocation, Bubble Sort
- **Môi trường:** Windows Console (nếu sử dụng Windows API)

## 🎯 Mục tiêu học tập

Sau khi hoàn thành bài tập, người học có thể tự xây dựng chương trình quản lý dữ liệu đơn giản bằng C++, thao tác với mảng con trỏ, thực hiện thuật toán sắp xếp và quản lý bộ nhớ động đúng cách.
