//
// Created by 杜建璋 on 2024/7/26.
//

#include "utils/System.h"

int64_t System::currentTimeMillis()  {
    // 获取当前时间点
    auto now = std::chrono::system_clock::now();

    // 将时间点转换为时间戳（自纪元以来的毫秒数）
    auto duration = now.time_since_epoch();
    long millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    return millis;
}
