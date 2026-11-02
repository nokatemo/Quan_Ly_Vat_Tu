# Đồ án DSA - Quản lý nhập xuất vật tư

## Tổng quan đồ án
Đồ án xây dựng chương trình quản lý nhập xuất vật tư cho một cửa hàng, cho phép quản lý danh mục hàng hóa, nhân viên và các hóa đơn nhập/xuất kho. Chương trình tự động cập nhật số lượng tồn kho dựa trên loại hóa đơn, hỗ trợ in ấn, thống kê doanh thu và lưu trữ dữ liệu vào file.

**Cấu trúc dữ liệu sử dụng:**
- **Cây nhị phân tìm kiếm (BST):** Quản lý danh sách Vật tư (khóa là MAVT).
- **Mảng con trỏ:** Quản lý danh sách Nhân viên (tối đa 500 người, luôn tăng dần theo MANV).
- **Danh sách liên kết đơn (DSLK):** Quản lý Hóa đơn và Chi tiết hóa đơn.

**Các chức năng chính:**
- Quản lý vật tư (thêm, xóa, sửa, in danh sách theo tên).
- Quản lý nhân viên (thêm, xóa, sửa, in danh sách theo tên/họ).
- Lập hóa đơn nhập/xuất, tự động cập nhật số lượng tồn kho.
- In hóa đơn, tính tổng trị giá (có VAT).
- Thống kê hóa đơn theo khoảng thời gian, thống kê doanh thu theo tháng.
- Lưu trữ và đọc dữ liệu từ file text.

**Công nghệ sử dụng:**
- Ngôn ngữ: C++ (Dev-C++ 5.9.2)
- Giao diện: Console (dòng lệnh)
- File I/O: Đọc/ghi file text (dấu `|` phân cách)

---

## Thành viên
- [Trần Trung Nguyên - N25DECE105] - Module Nhân viên
- [Ngô Minh Tiến - N25DECE121] - Module Vật tư
- [Bùi Vũ Nguyên Khoa - N25DECE097] - Module Hóa đơn

## Phân công
| Người | Module | Câu |
|---|---|---|
| Trần Trung Nguyên - N25DECE105 | Nhân viên + Menu | c, d, i |
| Ngô Minh Tiến - N25DECE121 | Vật tư | a, b, h |
| Bùi Vũ Nguyên Khoa - N25DECE097 | Hóa đơn + Tích hợp | e, f, g |
