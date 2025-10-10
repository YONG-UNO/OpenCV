cmake_minimum_required(VERSION 4.0)
project(opencv)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 寻找 OpenCV 库
find_package(OpenCV REQUIRED)

# 打印找到的 OpenCV 版本信息（可选，用于调试）
message(STATUS "Found OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include directories: ${OpenCV_INCLUDE_DIRS}")

# 添加可执行文件
add_executable(opencv main.cpp
        User/FPSModule/FPSModule.cpp
        User/FPSModule/FPSModule.h
        User/CameraModule/CameraModule.cpp
        User/CameraModule/CameraModule.h)

# 链接 OpenCV 库到可执行文件
target_link_libraries(opencv PRIVATE ${OpenCV_LIBS})

# 包含 OpenCV 的头文件目录
target_include_directories(opencv PRIVATE ${OpenCV_INCLUDE_DIRS})
