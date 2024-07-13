//
// Created by 杜建璋 on 2024/7/12.
//

#include <iostream>
#include "utils/Log.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <unistd.h>

const std::string Log::INFO = "INFO";
const std::string Log::DEBUG = "DEBUG";
const std::string Log::WARN = "WARN";
const std::string Log::ERROR = "ERROR";
std::string Log::HOSTNAME;

void Log::i(const std::string& msg) {
    print(INFO, msg);
}

void Log::d(const std::string& msg) {
    print(DEBUG, msg);
}

void Log::w(const std::string& msg) {
    print(WARN, msg);
}

void Log::e(const std::string& msg) {
    print(ERROR, msg);
}

std::string Log::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

void Log::print(const std::string& level, const std::string& msg) {
    if (HOSTNAME.empty()) {
        char hostName[128];
        gethostname(hostName, sizeof(hostName));
        HOSTNAME.append(std::string(hostName));
    }

    std::cout << "[" << std::setw(20) << HOSTNAME + ":" + std::to_string(getpid()) << "] "
              << "[" << getCurrentTimestamp() << "] "
              << "[" << std::setw(5) << level << "] "
              << msg << std::endl;
}
