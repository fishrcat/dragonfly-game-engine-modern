// log_manager.h — Logging to file

#pragma once

// Project
#include "manager.h"

// System
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <ctime>
#include <string>

#define LM df::LogManager::getInstance()

namespace df {

// Standard log levels
enum class LogLevel : std::uint8_t { TRACE, DEBUG, INFO, WARN, ERROR, FATAL };

// LogLevel to a string for readable log printing
inline auto levelToString(LogLevel level) -> const char* {
    switch (level) {
        case LogLevel::TRACE:
            return "TRACE";
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARN:
            return "WARN";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::FATAL:
            return "FATAL";
        default:
            return "UNKNOWN";
    }
}

const std::string LOGFILE_NAME = "dragonfly.log";

class LogManager : public df::Manager {
    private:
    LogManager();
    LogManager(const LogManager&) = delete;             // Disable copy
    LogManager& operator=(const LogManager&) = delete;  // Disable assignment

    LogLevel log_level{LogLevel::INFO};
    bool m_did_flush{true};
    FILE* m_log_file{nullptr};

    public:
    ~LogManager() override;

    static auto getInstance() -> LogManager&;  // Singleton

    auto startUp() -> int override;
    void shutDown() override;

    void setLogLevel(LogLevel level);
    auto getLogLevel() const -> LogLevel;

    void setFlush(bool do_flush = true);

    auto writeLog(LogLevel level, const char* fmt, ...) -> int;
};

}  // namespace df
