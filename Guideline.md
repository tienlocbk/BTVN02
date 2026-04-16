# Result

1. Package build không có warning sau khi thêm dependencies
  
  ![](file:///mnt/18F8AE7953C53855/SecondBrain/Project/MARS/BTVN02/assets/2026-04-13-09-37-39-image.png?msec=1776320220477)
  
2. distance_tf_broadcaster` broadcast đủ 2 frame lên `/tf`
  
  ![](file:///mnt/18F8AE7953C53855/SecondBrain/Project/MARS/BTVN02/assets/2026-04-13-10-46-52-image.png?msec=1776320220477)
  
3. `sensor_link` x thay đổi theo giá trị `/distance_topic`![](file:///mnt/18F8AE7953C53855/SecondBrain/Project/MARS/assets/2026-04-15-09-27-02-image.png?msec=1776320220478)
  
4. `distance_tf_listener` tính đúng khoảng cách từ TF
  
  ![](file:///mnt/18F8AE7953C53855/SecondBrain/Project/MARS/assets/2026-04-15-09-39-05-image.png?msec=1776320220479)
  
5. Khi sensor > `tf_threshold`, tự động gọi `/set_threshold`![](file:///mnt/18F8AE7953C53855/SecondBrain/Project/MARS/assets/2026-04-15-09-47-00-image.png?msec=1776320220479)
  
6. `/distance_reliable` publish đúng 1 Hz
  
  ![](file:///mnt/18F8AE7953C53855/SecondBrain/Project/MARS/assets/2026-04-15-09-53-30-image.png?msec=1776320220478)
  
7. `/distance_best_effort` publish đúng 10 Hz
  
  ![](file:///mnt/18F8AE7953C53855/SecondBrain/Project/MARS/assets/2026-04-15-09-53-51-image.png?msec=1776320220477)
  
8. Bảng stats in đúng số lượng sau 5 giây
  
9. QoS incompatible test → warning xuất hiện
  
  ![](file:///mnt/18F8AE7953C53855/SecondBrain/Project/MARS/assets/2026-04-15-10-33-57-image.png?msec=1776320220478)
  
10. Launch file full khởi động đủ 8 node