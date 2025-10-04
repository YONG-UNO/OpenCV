```angular2html
your_project/          # 项目根目录
├── main.cpp           # 主函数（统筹调用各模块）
├── CameraModule.h     # 摄像头模块：声明初始化、读取帧等函数
├── CameraModule.cpp   # 摄像头模块：实现函数
├── DetectionModule.h  # 检测模块：声明HSV筛选、轮廓检测等函数
├── DetectionModule.cpp# 检测模块：实现函数
├── FPSModule.h        # 帧率模块：声明帧率计算函数
├── FPSModule.cpp      # 帧率模块：实现函数
└── CMakeLists.txt     # 编译配置（需包含所有cpp文件）
```