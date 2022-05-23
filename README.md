# Mystic Woods

## I, Hướng dẫn cài đặt và chạy game
  ### B1: Tải project về
  Cách 1: Trên Github, chọn Code => Download ZIP  
  Cách 2: Mở terminal tại thư mục muốn lưu project, sử dụng lệnh `git init` để khởi tạo Git, sau đó dùng lệnh `git clone https://github.com/kiu-chan/Mystic-Woods.git` để clone project về máy  
  ### B2: Cài đặt Make
  Tải và cài đặt Make từ đường link sau: [link](https://drive.google.com/drive/folders/1CgQUSdYFO1bWSrRLxRyvqQ8womtRUbri?usp=sharing)  
  Thêm đường dẫn đến thư mục bin vào `environment variable`  
  VD: C:\Program Files (x86)\GnuWin32\bin 
  ### B3: Chạy game
  Mở terminal tại thư mục chứa project, sử dụng lệnh `mingw32-make` và `.\main` để chạy game
## II, Mô tả chung về trò chơi
  **Thể loại:** `Sinh tồn`, `phiêu lưu`
  
  Game sinh tồn trong thế giới 2D có thể di chuyển đánh quái.
  


### III, Các chức năng của trò chơi
  - Điều khiển nhân vật di chuyển bằng các phím mũi tên và tấn công bằng phím `space`
  - Hệ thống HP, đánh quái và quái tự tấn công người chơi
  - Quái vật tự đuổi theo người chơi khi vào phạm vi và tấn công, quái vật có thể hồi sinh theo một thời gian nhất định
    
### IV, Các kỹ thuật lập trình được sử dụng
  - Sử dụng thư viện đồ họa SDL
  - Lập trình hướng đối tượng (class)
  - Con trỏ, cấp phát động
  - Sử dụng thuật toán xử lý va chạm
  - Hệ thống tile-map nhiều lớp xếp chồng lên nhau và có những chức năng riêng (collision, monster, map)
### V, Hỗ trợ
- Sử dụng Photoshop để edit ảnh
- Sử dụng pyxelEdit để làm map
### VI, Kết luận
  Do là game đầu tay nên còn nhiều thiếu sót, game cần được cải tiến và fix vài lỗi nhỏ
  
  Dự kiến phát triển:
  - Sửa lỗi va chạm sao cho tự nhiên hết có thể
  - Thêm menu khi vào game và khi chết có thể chơi lại 
  - Lưu lại điểm và tiến trình
  - Thêm nhiều màn chơi và hệ thống level
  - Thêm boss và item
 

