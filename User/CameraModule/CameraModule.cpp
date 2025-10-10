//
// Created by DingYong on 2025/10/11.
//

#include "CameraModule.h"


bool initCamera(VideoCapture& cap, int camera_id, int backend) {
    // 打开摄像头:参数为设备id和后端API (默认V4L2,适用于Linux)
    if (!cap.open(cmaera))
}