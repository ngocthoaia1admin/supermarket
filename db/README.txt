Tạo tài khoản người dùng cho project
CREATE USER 'supermarket'@'localhost' IDENTIFIED BY '123';
Đăng nhập với người dùng này rồi chạy script.sql hoặc chạy script.sql với root rồi grand cho tài khoản này
GRANT ALL ON supermarket TO 'supermarket'@'localhost';