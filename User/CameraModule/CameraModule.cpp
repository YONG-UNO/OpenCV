//
// Created by DingYong on 2025/10/11.
//

#include "CameraModule.h"

#include <opencv2/opencv.hpp>  // 引入opencv核心库

// 四个核心函数,构成操作摄像头的完整流程:
// 1. initCamera:initialize the camera
// 2. setCameraParams: set the camera params(参数)(resolution,rate)
// 3. readCameraFrame: read a frame of image