# CHƯƠNG TRÌNH QUẢN LÝ NHẬP XUẤT VẬT TƯ

## 1. Giới thiệu

Chương trình được xây dựng bằng ngôn ngữ C++, sử dụng **cây tìm kiếm nhị phân (Binary Search Tree – BST)** để quản lý danh sách vật tư.

Mỗi vật tư được xác định bằng mã vật tư duy nhất. Cây BST được tổ chức theo mã vật tư nhằm hỗ trợ tìm kiếm thông tin và xuất danh sách theo thứ tự mã tăng dần.

## 2. Chức năng chính

### 2.1. Nhập danh sách vật tư
- Nhập số lượng vật tư cần thêm, yêu cầu số nguyên dương.
- Nhập thông tin của từng vật tư, bao gồm:
  - Mã vật tư (`mavt`)
  - Tên vật tư (`tenvt`)
  - Số lượng (`soluong`)
  - Đơn giá (`dongia`)
- Không thêm vật tư nếu mã vật tư đã tồn tại trong cây BST.

### 2.2. Xuất danh sách vật tư
- Hiển thị thông tin của toàn bộ vật tư.
- Sử dụng phương pháp duyệt cây **Inorder (Left – Node – Right)**.
- Danh sách được xuất theo thứ tự mã vật tư tăng dần.

### 2.3. Tìm kiếm thông tin vật tư
- Nhập mã vật tư cần tìm.
- Tìm kiếm trên cây BST dựa vào mã vật tư.
- Nếu tìm thấy, hiển thị thông tin chi tiết của vật tư.
- Nếu không tìm thấy, thông báo cho người dùng.

### 2.4. Tính tổng giá trị tồn kho
- Tính thành tiền của từng vật tư theo công thức:

  `Thành tiền = Số lượng × Đơn giá`

- Tính tổng giá trị tồn kho theo công thức:

  `Tổng giá trị tồn kho = Tổng thành tiền của tất cả vật tư`

### 2.5. Quay lại menu và thoát chương trình
- Sau khi thực hiện chức năng, người dùng nhấn Enter để quay lại menu.
- Chọn `0` để thoát chương trình.
- Bộ nhớ được giải phóng trước khi chương trình kết thúc.

## 3. Cấu trúc dữ liệu

### 3.1. Cấu trúc vật tư

```cpp
struct vattu {
    string mavt;
    string tenvt;
    int soluong;
    double dongia;
};
```

Cấu trúc `vattu` lưu trữ thông tin của một vật tư.

### 3.2. Cấu trúc nút BST

```cpp
struct nodebst {
    vattu data;
    nodebst* left;
    nodebst* right;
};
```

Mỗi nút của cây gồm:
- `data`: Thông tin vật tư.
- `left`: Con trỏ đến cây con trái.
- `right`: Con trỏ đến cây con phải.

Cây được tổ chức dựa trên `mavt`:
- Mã vật tư nhỏ hơn nằm ở cây con trái.
- Mã vật tư lớn hơn nằm ở cây con phải.
- Mã vật tư trùng nhau không được thêm vào cây.

## 4. Các hàm xử lý chính

| Hàm | Chức năng |
|---|---|
| `create()` | Tạo nút BST mới. |
| `insert()` | Thêm vật tư vào cây BST. |
| `inorder()` | Duyệt cây và xuất danh sách theo mã tăng dần. |
| `search()` | Tìm vật tư theo mã. |
| `value()` | Tính tổng giá trị tồn kho. |
| `list()` | Hiển thị thông tin một vật tư. |
| `input()` | Nhập thông tin vật tư. |
| `freeroot()` | Giải phóng bộ nhớ của cây BST. |
| `xoaManHinh()` | Xóa nội dung màn hình console. |
| `quayLaiMenu()` | Chờ người dùng nhấn Enter để quay lại menu. |

## 5. Công nghệ sử dụng

- **Ngôn ngữ:** C++
- **Cấu trúc dữ liệu:** Binary Search Tree (BST)
- **Thư viện:** `iostream`, `string`, `limits`, `windows.h`
- **Môi trường chạy:** Windows Console
- **Quản lý bộ nhớ:** Cấp phát động bằng `new` và giải phóng bằng `delete`.

## 6. Hướng dẫn sử dụng

1. Chạy chương trình.
2. Nhập số lượng vật tư cần quản lý.
3. Nhập thông tin của từng vật tư.
4. Chọn chức năng trong menu:
   - `1`: Xuất danh sách vật tư.
   - `2`: Tìm kiếm thông tin vật tư.
   - `3`: Tính tổng giá trị tồn kho.
   - `0`: Thoát chương trình.
5. Sau khi thực hiện chức năng 1, 2 hoặc 3, nhấn Enter để quay lại menu.

## 7. Lưu ý

- Mã vật tư được sử dụng làm khóa để tổ chức cây BST.
- Việc so sánh mã vật tư là so sánh chuỗi, không phải so sánh số.
- Dữ liệu chỉ được lưu trong bộ nhớ khi chương trình đang chạy; chương trình chưa hỗ trợ lưu hoặc đọc dữ liệu từ tệp.
- Chương trình sử dụng `windows.h`, do đó phù hợp với môi trường Windows.

## 8. Kết luận

Chương trình áp dụng cây tìm kiếm nhị phân để quản lý vật tư, thực hiện các thao tác thêm, tìm kiếm, duyệt danh sách và tính tổng giá trị tồn kho. Qua đó, chương trình giúp vận dụng kiến thức về cấu trúc dữ liệu, đệ quy, con trỏ và quản lý bộ nhớ động trong C++.
