#pragma once
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

namespace plotx::time_utils {

// ----------------------
// 安全 localtime 封装
// ----------------------
inline bool safeLocalTime(std::time_t t, std::tm& out) {
#ifdef _WIN32
    return localtime_s(&out, &t) == 0;
#else
    return localtime_r(&t, &out) != nullptr;
#endif
}

// ----------------------
// 获取当前本地时间戳
// ----------------------
inline std::time_t getLocalTime() {
    return std::time(nullptr); // already system local time
}

// ----------------------
// 获取未来时间偏移 (单位: 秒)
// now + offsetSec
// ----------------------
inline std::time_t getFutureTime(std::time_t offsetSec) { return std::time(nullptr) + offsetSec; }

// ----------------------
// 时间戳 → yyyy-MM-dd HH:mm:ss
// ----------------------
inline std::string format(std::time_t ts) {
    std::tm tm{};
    if (!safeLocalTime(ts, tm)) {
        throw std::runtime_error("Failed to convert time to local time");
    }

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

// ----------------------
// yyyy-MM-dd HH:mm:ss → 时间戳
// ----------------------
inline std::time_t parse(const std::string& timeStr) {
    std::tm            tm{};
    std::istringstream iss(timeStr);
    iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

    if (iss.fail()) {
        throw std::runtime_error("Failed to parse time string: " + timeStr);
    }

    // std::mktime 认为 tm 是本地时间
    return std::mktime(&tm);
}

} // namespace plotx::time_utils
