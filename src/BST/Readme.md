# 📦 C++ Inventory Management System

## 📌 Giới thiệu

Bài tập thực hành C++: **Quản lý danh sách vật tư bằng cây tìm kiếm nhị phân (Binary Search Tree – BST)**.

Mục tiêu của bài tập là vận dụng các kiến thức:

- `struct` trong C++
- Con trỏ và con trỏ cấu trúc
- Cấp phát và giải phóng bộ nhớ động (`new`, `delete`)
- Cấu trúc dữ liệu cây tìm kiếm nhị phân (BST)
- Thuật toán đệ quy
- Thao tác thêm và tìm kiếm dữ liệu trên BST
- Duyệt cây Inorder
- Tính tổng giá trị tồn kho
- Xử lý dữ liệu đầu vào và xây dựng menu chức năng

## 📋 Yêu cầu bài toán

Xây dựng chương trình quản lý danh sách vật tư bằng cây tìm kiếm nhị phân, sử dụng mã vật tư làm khóa để thực hiện các chức năng nhập, xuất, tìm kiếm và tính tổng giá trị tồn kho.

### 1. Khai báo cấu trúc dữ liệu

Tạo cấu trúc `vattu` gồm các thuộc tính:

| Thuộc tính | Kiểu dữ liệu | Mô tả |
|---|---|---|
| `mavt` | `string` | Mã vật tư |
| `tenvt` | `string` | Tên vật tư |
| `soluong` | `int` | Số lượng vật tư |
| `dongia` | `double` | Đơn giá vật tư |

Tạo cấu trúc `nodebst` gồm các thành phần:

| Thành phần | Kiểu dữ liệu | Mô tả |
|---|---|---|
| `data` | `vattu` | Thông tin vật tư được lưu trong nút |
| `left` | `nodebst*` | Con trỏ đến cây con trái |
| `right` | `nodebst*` | Con trỏ đến cây con phải |

Quy tắc tổ chức cây BST:

- Mã vật tư nhỏ hơn mã tại nút hiện tại được đưa vào cây con trái.
- Mã vật tư lớn hơn mã tại nút hiện tại được đưa vào cây con phải.
- Không thêm vật tư nếu mã vật tư đã tồn tại trong cây.

### 2. Nhập danh sách vật tư

- Nhập số lượng vật tư cần quản lý, yêu cầu `n > 0`.
- Nhập đầy đủ mã vật tư, tên vật tư, số lượng và đơn giá.
- Sử dụng hàm `input()` để nhập thông tin từng vật tư.
- Sử dụng hàm `create()` để tạo nút mới và cấp phát bộ nhớ động.
- Sử dụng hàm `insert()` để đưa vật tư vào cây BST.
- Kiểm tra mã vật tư trùng lặp trước khi thêm vào cây.

### 3. Xuất danh sách vật tư

Viết hàm `inorder()` để duyệt và xuất toàn bộ danh sách vật tư.

Thông tin hiển thị bao gồm:

- Mã vật tư
- Tên vật tư
- Số lượng
- Đơn giá
- Thành tiền

Sử dụng phương pháp duyệt cây **Inorder (Left – Node – Right)** để xuất danh sách theo thứ tự mã vật tư tăng dần.

### 4. Tìm kiếm thông tin vật tư

Viết hàm `search()` để tìm vật tư theo mã.

- Nhập mã vật tư cần tìm.
- So sánh mã tìm kiếm với mã tại nút hiện tại.
- Nếu mã nhỏ hơn, tiếp tục tìm trong cây con trái.
- Nếu mã lớn hơn, tiếp tục tìm trong cây con phải.
- Nếu tìm thấy, xuất thông tin vật tư.
- Nếu không tìm thấy, hiển thị thông báo phù hợp.

### 5. Tính tổng giá trị tồn kho

Viết hàm `value()` để tính tổng giá trị tồn kho của toàn bộ vật tư.

Công thức tính thành tiền của từng vật tư:

`Thành tiền = Số lượng × Đơn giá`

Công thức tính tổng giá trị tồn kho:

`Tổng giá trị tồn kho = Tổng thành tiền của tất cả vật tư`

Sử dụng đệ quy để tính tổng giá trị tại nút hiện tại và hai cây con trái, phải.

### 6. Xây dựng menu chức năng

Chương trình cung cấp các chức năng:

| Lựa chọn | Chức năng |
|---|---|
| `1` | Xuất danh sách vật tư |
| `2` | Tìm kiếm thông tin vật tư theo mã |
| `3` | Tính tổng giá trị tồn kho |
| `0` | Thoát chương trình |

Sau khi thực hiện chức năng, người dùng có thể nhấn Enter để quay lại menu.

### 7. Giải phóng bộ nhớ

Viết hàm `freeroot()` để giải phóng toàn bộ bộ nhớ đã cấp phát cho cây BST.

- Duyệt và giải phóng cây con trái.
- Duyệt và giải phóng cây con phải.
- Xóa nút hiện tại bằng `delete`.
- Đảm bảo toàn bộ cây được giải phóng trước khi chương trình kết thúc.

---

## 🧪 Dữ liệu kiểm thử

### Input mẫu

Nhập số lượng vật tư:

```text
4
```

Nhập lần lượt thông tin vật tư:

| Mã vật tư | Tên vật tư | Số lượng | Đơn giá |
|---|---|---:|---:|
| VT03 | Ban phim | 10 | 250000 |
| VT01 | Chuot may tinh | 20 | 150000 |
| VT04 | Man hinh | 5 | 2500000 |
| VT02 | Tai nghe | 15 | 300000 |

### Kết quả xuất danh sách

Chọn chức năng `1`.

```text
=== DANH SACH VAT TU ===
Ma vat tu: VT01
Ten vat tu: Chuot may tinh
So luong: 20
Don gia: 150000
Thanh tien: 3000000
-------------------------
Ma vat tu: VT02
Ten vat tu: Tai nghe
So luong: 15
Don gia: 300000
Thanh tien: 4500000
-------------------------
Ma vat tu: VT03
Ten vat tu: Ban phim
So luong: 10
Don gia: 250000
Thanh tien: 2500000
-------------------------
Ma vat tu: VT04
Ten vat tu: Man hinh
So luong: 5
Don gia: 2500000
Thanh tien: 12500000
-------------------------
```

Danh sách được xuất theo thứ tự mã vật tư tăng dần, không phụ thuộc vào thứ tự nhập ban đầu.

### Kết quả tìm kiếm

Chọn chức năng `2`, nhập mã vật tư `VT02`.

```text
Nhap ma vat tu: VT02

=== THONG TIN VAT TU ===
Ma vat tu: VT02
Ten vat tu: Tai nghe
So luong: 15
Don gia: 300000
Thanh tien: 4500000
-------------------------
```

Nếu nhập mã không tồn tại, ví dụ `VT99`:

```text
Nhap ma vat tu: VT99
Khong tim thay vat tu!
```

### Kết quả tính tổng giá trị tồn kho

Chọn chức năng `3`.

| Mã vật tư | Thành tiền (VNĐ) |
|---|---:|
| VT01 | 3.000.000 |
| VT02 | 4.500.000 |
| VT03 | 2.500.000 |
| VT04 | 12.500.000 |
| **Tổng cộng** | **22.500.000** |

Kết quả:

```text
Tong gia tri ton kho: 22500000
```

*Lưu ý: Kết quả trên minh họa giá trị tính toán. Để chương trình hiển thị dấu chấm phân cách hàng nghìn như `22.500.000`, cần bổ sung hàm định dạng số vào mã nguồn.*

---

## ⚙️ Quy định kỹ thuật

1. Sử dụng ngôn ngữ C++.
2. Sử dụng `struct` để lưu trữ thông tin vật tư và cấu trúc nút cây.
3. Bắt buộc sử dụng cây tìm kiếm nhị phân (BST).
4. Sử dụng mã vật tư làm khóa của cây.
5. Tách chương trình thành các hàm riêng biệt.
6. Sử dụng đệ quy cho thao tác tìm kiếm, duyệt cây và tính tổng giá trị tồn kho.
7. Sử dụng cấp phát động bằng `new` và giải phóng bộ nhớ bằng `delete`.
8. Không sử dụng `vector` hoặc cấu trúc dữ liệu thay thế BST để quản lý danh sách.
9. Xây dựng menu cho phép thực hiện nhiều chức năng trong một lần chạy.
10. Chương trình sử dụng `windows.h` cho thao tác xóa màn hình và tạm dừng trên Windows.

## 📊 Thang điểm tham khảo

| Nội dung | Điểm |
|---|---:|
| Khai báo cấu trúc vật tư và nút BST | 1 |
| Nhập dữ liệu và tạo cây BST | 2 |
| Xuất danh sách bằng Inorder | 1.5 |
| Tìm kiếm vật tư theo mã | 1.5 |
| Tính tổng giá trị tồn kho | 1.5 |
| Menu và xử lý dữ liệu đầu vào | 1 |
| Giải phóng bộ nhớ | 1.5 |
| **Tổng cộng** | **10** |

*Thang điểm trên chỉ mang tính tham khảo, không phải thang điểm chính thức của đề bài.*

---

## 🛠️ Công nghệ sử dụng

- **Ngôn ngữ:** C++
- **Cấu trúc dữ liệu:** Binary Search Tree (BST)
- **Kiến thức:** Struct, Pointers, Recursion, Dynamic Memory Allocation
- **Thư viện:** `iostream`, `string`, `limits`, `windows.h`
- **Môi trường:** Windows Console

## 🎯 Mục tiêu học tập

Sau khi hoàn thành bài tập, người học có thể vận dụng cấu trúc dữ liệu cây tìm kiếm nhị phân để quản lý thông tin vật tư, hiểu cách tổ chức dữ liệu bằng con trỏ, triển khai thuật toán đệ quy và thực hiện cấp phát, giải phóng bộ nhớ động trong C++.
