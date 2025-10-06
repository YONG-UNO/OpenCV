//
// Created by dingyong on 2025/10/4.
//

#ifndef OPENCV_FPSMODULE_H
#define OPENCV_FPSMODULE_H

#include <chrono>    // 时间库,提供高精度时间测量功能，是计算帧率的基础
using namespace std::chrono;   // 简化后续代码中时间相关类的使用

// 帧率计算器类（封装帧率相关变量和逻辑）
class FPSCalculator
{
private:
    double fps;                 // 实时帧率
    high_resolution_clock::time_point last_time;   // 上一次计算时间戳
    int frame_count;            // 帧计数器
    const int update_interval;  // 每N帧更新一次帧率（避免波动）

public:
    // 构造函数：初始化参数（默认每10帧更新一次）
    FPSCalculator(int interval = 10);

    // 每帧调用一次：更新帧计数并计算帧率
    void update();

    // 获取当前帧率（对外提供只读访问）
    double getFPS() const:
};


#endif //OPENCV_FPSMODULE_H