// log_manager.h — Logging to file

#pragma once

// Project
#include "clock.h"
#include "config.h"
#include "manager.h"

// System
#include <cstdio>
#include <string>

#define LM df::LogManager::getInstance()

namespace df {

// Standard log levels
enum class LogLevel : std::uint8_t { TRACE, DEBUG, INFO, WARN, ERROR, FATAL };

// LogLevel to a string for readable log printing
inline auto levelToString(const LogLevel level) -> const char* {
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

class LogManager : public Manager {
    public:
    ~LogManager() override;
    LogManager(const LogManager&) = delete;  // Disable copy
    auto operator=(const LogManager&) -> LogManager& =
                                             delete;  // Disable assignment

    static auto getInstance() -> LogManager&;  // Singleton

    void setClock(const Clock& clock) { m_clock = &clock; }

    auto startUp() -> int override;
    void shutDown() override;

    void setLogLevel(LogLevel level);
    auto getLogLevel() const -> LogLevel;

    void setFlush(bool do_flush = true);

    auto writeLog(LogLevel level, const std::string& msg) const -> int;

    private:
    LogManager();

#ifdef DEBUG_MODE
    LogLevel log_level{LogLevel::DEBUG};
#else
    LogLevel log_level{LogLevel::ERROR};
#endif

    bool m_did_flush{true};
    FILE* m_log_file{nullptr};

    const Clock* m_clock = nullptr;
};

}  // namespace df
