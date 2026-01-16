// log_manager.h — Manager of logging to file

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

    // Read only game clock in LogManager context
    void setClock(const Clock& clock) { m_clock = &clock; }

    [[nodiscard]] auto startUp()
        -> StartupResult override;  // Enforce startup checks
    void shutDown() noexcept override;

    void setLogLevel(LogLevel level);
    auto getLogLevel() const -> LogLevel;

    void setFlush(bool do_flush = true);

    auto writeLog(LogLevel level, const std::string& msg) const -> int;

    private:
    LogManager();

    // TODO: change config.h to a post-compile settings manager
#ifdef DEBUG_MODE
    LogLevel log_level{LogLevel::DEBUG};
    bool m_do_flush{true};
#else
    LogLevel log_level{LogLevel::ERROR};
    bool m_do_flush{false};
#endif

    FILE* m_log_file{nullptr};

    const Clock* m_clock = nullptr;
};

}  // namespace df
