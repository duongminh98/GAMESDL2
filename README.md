# SPACEWAR
# **GIỚI THIỆU**
- Họ và tên: Dương Tuấn Minh
- MSSV: 23021937
# **VỀ GAME**
## Luật chơi
- Người chơi điều khiển máy bay tiêu diệt máy bay địch và các chướng ngại vật.
- Máy bay địch bị tiêu diệt sẽ rơi ra 1 point, di chuyển máy bay người chơi đến point để tăng 1 điểm trên score.
- Né tránh đạn của máy bay địch và các chướng ngại, người chơi chỉ có 1 mạng.
- Khi score>=5 sẽ xuất hiện thiên thạch bay về phía người chơi, điều khiển máy bay để bắn phá trúng.
- Khi score>=10 sẽ xuất hiện tên lửa định hướng ghim vào người chơi, sống sót bằng cách di chuyển máy bay để tên lửa lao vào máy bay địch.
- Score càng cao thì tốc độ spawn của địch càng giảm bớt tăng thêm độ khó.
## Điều khiển
|**PHÍM**|**CHỨC NĂNG**|
|-------|-------|
|**W**|**LÊN**|
|**A**|**TRÁI**|
|**S**|**XUỐNG**| 
|**D**|**PHẢI**| 
|**SPACE**|**BẮN**| 
# **NGƯỠNG ĐIỂM MONG MUỐN: 8-8.5**
## Lý do
- Game viết có bố cục rõ ràng, tách file, dễ debug khi cần.
- Sử dụng đầy đủ các component của SDL: SDL_image, SDL_Mixer, SDL_Font.
- Có đầy đủ cấu trúc:
  
  - MENU gồm chơi, xem bảng điểm và thoát.
  
  - Tính điểm và đánh dấu điểm số kỷ lục.
  - Lưu lại điểm vào file.
  - Có thể tắt mở nhạc nền.
 
- Custom lại con trỏ chuột trong cửa sổ game.
- Tính đường đi, góc bắn định hướng cho kẻ địch.
- Kiểm tra collision giữa 2 texture.
- Cắt ghép các texture từ texture gốc.
- Các hàm dọn dẹp được sử dụng xuyên suốt quá trình chơi, giúp tối ưu bộ nhớ sử dụng.
- Dùng mã hoá RSA khi lưu bảng điểm giúp tránh gian lận sửa điểm bằng file trong trò chơi.
# **HƯỚNG PHÁT TRIỂN**
- Thêm các boss vào trong trò chơi.
- Xây dựng thêm các chướng ngại vật tĩnh để người chơi né khi di chuyển.
- Có thể sử dụng các thuật toán để spawn AI không bị đè lên nhau.
- Thêm animation cho game.
- Thêm các loại đạn và các chế độ chơi khác nhau.
