## Tiêu chí chấp nhận

| #   | Tiêu chí                                                   | Kiểm tra bằng                   |
| --- | ---------------------------------------------------------- | ------------------------------- |
| 1   | Package build không có warning                             | `colcon build`                  |
| 2   | `distance_publisher` publish đúng 1 Hz                     | `ros2 topic hz /distance_topic` |
| 3   | `distance_listener` in cảnh báo khi `distance < threshold` | Quan sát log                    |
| 4   | Service thay đổi được `threshold` runtime                  | `ros2 service call ...`         |
| 5   | Sau khi gọi service, listener dùng threshold mới           | Quan sát log                    |
| 6   | Action server gửi đủ 5 bước feedback                       | Chạy action client              |
| 7   | Action trả về `is_safe` đúng theo threshold hiện tại       | Test nhiều giá trị              |
| 8   | Launch file khởi động toàn bộ hệ thống một lệnh            | `ros2 launch ...`               |
| 9   | `rqt_graph` hiển thị đủ node và topic                      | `rqt_graph`                     |

#### 1. Package build không có warning

![](/home/loc/.config/marktext/images/2026-04-06-09-13-16-image.png)

#### 2.  `distance_publisher` publish đúng 1 Hz

![](/home/loc/.config/marktext/images/2026-04-06-09-19-08-image.png)

#### 3. `distance_listener`in cảnh báo khi`distance < threshold`

![](/home/loc/.config/marktext/images/2026-04-06-09-21-10-image.png)

#### 4. Service thay đổi được `threshold` runtime

![](/home/loc/.config/marktext/images/2026-04-06-09-30-48-image.png)

#### 5. Sau khi gọi service, listener dùng threshold mới

![](/home/loc/.config/marktext/images/2026-04-06-10-17-47-image.png)

#### 6.Action server gửi đủ 5 bước feedback

![](/home/loc/.config/marktext/images/2026-04-06-11-06-43-image.png)

#### 7. Action trả về `is_safe` đúng theo threshold hiện tại

![](/home/loc/.config/marktext/images/2026-04-06-11-20-30-image.png)

#### 8. Launch file khởi động toàn bộ hệ thống một lệnh

![](/home/loc/.config/marktext/images/2026-04-06-11-26-40-image.png)

#### 9.`rqt_graph` hiển thị đủ node và topic

![](/home/loc/.config/marktext/images/2026-04-06-11-27-22-image.png)
