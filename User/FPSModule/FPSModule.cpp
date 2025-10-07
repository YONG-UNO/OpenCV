//
// Created by dingyong on 2025/10/4.
//

#include "FPSModule.h"

// constructor(构造函数)：initialize frame rate
// fps(0,0): initial frame rate is (0,0)
// frame_count: initial frame count
// update_interval(interval): initial refresh interval
// last_time: Get the current high-resolution clock ,
//            serves as a starting reference point for calculating frame rates
FPSCalculator::FPSCalculator(int interval)
    : fps(0.0), frame_count(0), update_interval(interval) {
        last_time = high_resolution_clock::now();  // 初始时间戳
    }

// update() function implementation
void FPSCalculator::update() {
    frame_count++;    // frame_count +1 for each call, called once per frame

    if (frame_count >= update_interval) {
        auto current_time = high_resolution_clock::now(); // get the current time

        // calculate the time difference from the last calculation
        // duration_cast<microseconds>: explicit(显式) converted to microseconds
        // .count(): extarct raw values from a time interval with units
        auto duration = duration_cast<microseconds>(current_time - last_time).count();

    // frame rate = frame count / time(s)
    // since duration is milliseconds, it needs to be divided by 1000 to
    // seconds, and the formula is transformed as(公式转换为) (frame count * 1000) / milliseconds
    fps = (frame_count * 1000.0) / duration;

    }
}
