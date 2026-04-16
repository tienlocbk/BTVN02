# Result

1. Package build không có warning sau khi thêm dependencies
   
   ![](assets/2026-04-13-09-37-39-image.png)

2. distance_tf_broadcaster` broadcast đủ 2 frame lên `/tf`
   
   ![](assets/2026-04-13-10-46-52-image.png)

3. `sensor_link` x thay đổi theo giá trị `/distance_topic`<img title="" src="../assets/2026-04-15-09-27-02-image.png" alt="" width="722">

4. `distance_tf_listener` tính đúng khoảng cách từ TF
   
   ![](../assets/2026-04-15-09-39-05-image.png)

5. Khi sensor > `tf_threshold`, tự động gọi `/set_threshold`![](../assets/2026-04-15-09-47-00-image.png)

6. `/distance_reliable` publish đúng 1 Hz
   
   ![](../assets/2026-04-15-09-53-30-image.png)

7. `/distance_best_effort` publish đúng 10 Hz
   
   ![](../assets/2026-04-15-09-53-51-image.png)

8. Bảng stats in đúng số lượng sau 5 giây

9. QoS incompatible test → warning xuất hiện
   
   ![](../assets/2026-04-15-10-33-57-image.png)

10. Launch file full khởi động đủ 8 node
    
    ![](../assets/2026-04-15-10-32-53-image.png)
