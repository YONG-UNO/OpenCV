// #include <opencv2/opencv.hpp>   // OpenCV核心功能（图像处理、轮廓检测等）
// #include <iostream>             // 标准输入输出库
// #include <chrono>               // 用于计算帧率的时间库
//
// using namespace cv;        // 简化OpenCV代码，避免重复写cv::前缀
// using namespace std;       // 简化标准库代码
// using namespace chrono;    // 简化时间计算代码，用于帧率统计
//
// int main(void) {
//     // 1. 摄像头初始化
//     const int camera_id = 0;         // 系统默认摄像头（0表示第一个摄像头）
//     VideoCapture cap;                // 视频捕获对象
//     const int backend = CAP_V4L2;    // Linux系统推荐V4L2后端（兼容性更好）
//
//     // 打开摄像头
//     if (!cap.open(camera_id, backend)) {
//         cerr << "can not open camera 0!" << endl;
//         return -1;
//     }
//
//     // 设置摄像头参数（分辨率、目标帧率，根据硬件性能调整）
//     cap.set(CAP_PROP_FRAME_WIDTH, 1080);  // 宽度1080px
//     cap.set(CAP_PROP_FRAME_HEIGHT, 720);  // 高度720px
//     cap.set(CAP_PROP_FPS, 30);            // 目标帧率30（过高可能导致卡顿，需匹配硬件）
//
//     cout << "Camera 0 is on! Press 'q' to quit." << endl;
//     cout << "Now detecting green objects with FPS display..." << endl;
//
//     // 图像存储变量
//     Mat frame;          // 摄像头原始帧
//     Mat hsv_frame;      // HSV颜色空间帧（颜色分割更稳定）
//     Mat mask;           // 颜色筛选后的掩码（白色=目标颜色，黑色=其他）
//
//     // 2. 关键修改：定义绿色的HSV阈值范围（替换原红色范围）
//     // HSV范围说明：H(色相)0-179，S(饱和度)0-255，V(亮度)0-255
//     // 绿色的HSV区间较集中（无需分两段），可根据环境光照微调S/V阈值
//     Scalar lower_green = Scalar(35, 120, 70);   // 绿色低阈值（H=35，S=120，V=70）
//     Scalar upper_green = Scalar(77, 255, 255);  // 绿色高阈值（H=77，S=255，V=255）
//
//     // 3. 帧率计算相关变量（新增）
//     double fps = 0.0;                          // 实时帧率
//     auto last_time = high_resolution_clock::now();  // 上一次计算帧率的时间戳
//     int frame_count = 0;                       // 帧计数器（避免每帧计算导致波动）
//     const int fps_update_interval = 10;         // 每10帧更新一次帧率（平衡实时性与稳定性）
//
//     while (true) {
//         // 记录当前帧时间（用于帧率计算）
//         auto current_time = high_resolution_clock::now();
//
//         // 4. 读取摄像头帧
//         cap >> frame;
//         if (frame.empty()) {  // 摄像头断开或无帧数据时退出
//             cerr << "Can't capture image, quitting..." << endl;
//             break;
//         }
//
//         // 5. 帧率计算逻辑（新增）
//         frame_count++;
//         if (frame_count >= fps_update_interval) {
//             // 计算10帧的时间差（毫秒）
//             auto duration = duration_cast<milliseconds>(current_time - last_time).count();
//             // 帧率公式：帧率 = 帧数 / 时间（秒）→ 转换为毫秒需×1000
//             fps = (frame_count * 1000.0) / duration;
//
//             // 重置计数器和时间戳，准备下一轮计算
//             frame_count = 0;
//             last_time = current_time;
//         }
//
//         // 6. 颜色空间转换：BGR→HSV（OpenCV默认存储为BGR，需转HSV）
//         cvtColor(frame, hsv_frame, COLOR_BGR2HSV);
//
//         // 7. 关键修改：筛选绿色区域（替换原红色筛选）
//         inRange(hsv_frame, lower_green, upper_green, mask);  // 无需分两段，直接生成绿色掩码
//
//         // 8. 优化掩码：去除小噪点（先腐蚀再膨胀=开运算，保留大目标）
//         Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));  // 5x5矩形结构元素
//         erode(mask, mask, kernel);  // 腐蚀：缩小小噪点
//         dilate(mask, mask, kernel); // 膨胀：恢复绿色目标区域大小
//
//         // 9. 轮廓检测：找到绿色物体的边缘
//         vector<vector<Point>> contours;  // 存储所有轮廓（每个轮廓是点的集合）
//         vector<Vec4i> hierarchy;         // 轮廓层级关系（暂用不到）
//         findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//         // 10. 遍历轮廓，标记绿色物体（修改标签文字为绿色）
//         for (size_t i = 0; i < contours.size(); i++) {
//             // 过滤小轮廓（避免误识别噪点，面积阈值根据物体大小调整）
//             double contour_area = contourArea(contours[i]);
//             if (contour_area < 500) {  // 面积<500px²视为噪点，跳过
//                 continue;
//             }
//
//             // 计算物体的外接矩形（包围物体的最小矩形）
//             Rect bounding_rect = boundingRect(contours[i]);
//             rectangle(frame, bounding_rect, Scalar(0, 255, 0), 2);  // 绿色矩形框（与物体颜色对应）
//
//             // 计算矩形中心点（标记物体中心）
//             Point center(bounding_rect.x + bounding_rect.width / 2,
//                         bounding_rect.y + bounding_rect.height / 2);
//             circle(frame, center, 4, Scalar(0, 0, 255), -1);  // 红色填充圆点（对比明显）
//
//             // 关键修改：标签改为“Green Object”（明确标记绿色物体）
//             string label = "Green Object (Area: " + to_string(int(contour_area)) + ")";
//             putText(frame, label, Point(bounding_rect.x, bounding_rect.y - 10),
//                     FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 1);  // 绿色标签文字
//         }
//
//         // 11. 新增：在画面左上角显示实时帧率（红色文字，避免与绿色物体冲突）
//         string fps_text = "FPS: " + to_string(int(fps * 10) / 10.0);  // 保留1位小数，避免波动
//         putText(frame, fps_text, Point(10, 60),  // 位置：左上角(10,60)，避开物体标签
//                 FONT_HERSHEY_SIMPLEX, 0.8,       // 字体大小0.8，清晰易读
//                 Scalar(0, 0, 255), 2);           // 红色文字，线宽2，对比度高
//
//         // 12. 显示结果（原始帧+绿色物体标记+帧率）
//         imshow("Camera 0 (Green Object Detection + FPS)", frame);
//         // 可选：显示掩码窗口（调试用，查看绿色区域筛选效果）
//         // imshow("Green Mask", mask);
//
//         // 按下「q」键退出循环（等待1ms，保证帧率流畅）
//         if (waitKey(1) == 'q') {
//             break;
//         }
//     }
//
//     // 13. 释放资源（关闭摄像头+销毁所有窗口）
//     cap.release();
//     destroyAllWindows();
//     return 0;
// }