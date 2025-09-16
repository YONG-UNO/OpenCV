#include <opencv2/opencv.hpp>   // 包含opencv核心功能
#include <iostream>             // 标准输入输出库

using namespace cv;        // 使用opencv命名空间，避免重复写cv::前缀
using namespace std;       // 使用标准库命名空间

int main(void) {
    // 摄像头初始化
    const int camera_id = 0;         // 指定使用第0个摄像头（系统默认摄像头）
    VideoCapture cap;                // 视频捕获对象，用于操作摄像头
    const int backend = CAP_V4L2;    // 指定使用V4L2后端（适用于Linux的视频设备接口）

    // 打开摄像头
    // cap.open(camera_id, backend) 这是VideoCapture类的open方法，用于打开摄像头
    // 第一个参数camera_id:摄像头的编号（0表示默认摄像头，1表示第二个摄像头）
    // 第二个参数backend：指定视频捕获后端（如前面提到的CAP_V4L2,用于Linux系统）
    if (!cap.open(camera_id, backend)) {
        cerr << "can not open camera 0!" << endl;          // 通过标准错误流输出错误
        return -1;                                         // 退出程序并返回-1（非0返回值表示程序异常退出）
    }

    // 设置摄像头参数
    cap.set(CAP_PROP_FRAME_WIDTH, 1080);    // 宽度
    cap.set(CAP_PROP_FRAME_HEIGHT, 720);    // 高度
    cap.set(CAP_PROP_FPS, 1);

    cout << "the camera0 has been turn on, enter ‘p’ to quit" << endl;

    Mat frame;
    while (true) {
        cap >> frame;

        if (frame.empty()) {
            cerr << "can't capture the image, programming quit" << endl;
            break;
        }

        // 在画面上添加“Camera0”文字标识（绿色，位置左上角）
        putText(frame, "Camera 0", Point(10, 30),
            FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0,255,0), 2);

        imshow("camera0", frame);          // 显示画面，窗口标题为“camera0”

        // 等待1ms，若按下‘q’则退出循环
        if (waitKey(1) == 'q') {
            break;
        }
    }

    cap.release();
    destroyAllWindows();
    return 0;
}



// #include <iostream>
// using namespace std;
// int main() {
//     cout << "HELLO" << endl;
//     cout << 'a' << endl;
// }