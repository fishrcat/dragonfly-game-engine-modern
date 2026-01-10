// log_manager.cpp — Manager of logging to file

// Project
#include "log_manager.h"

#include "clock.h"

// System
#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <format>
#include <string>

namespace df {

LogManager::LogManager() { setType("LogManager"); }

LogManager::~LogManager() {
    if (m_log_file != nullptr) {
        fclose(m_log_file);
        m_log_file = nullptr;
    }
}

auto LogManager::getInstance() -> LogManager& {
    static LogManager instance;
    return instance;
}

// Open file on startup
auto LogManager::startUp() -> int {
    m_log_file = fopen(LOGFILE_NAME.c_str(), "w+");

    if (m_log_file == nullptr) {
        writeLog(LogLevel::ERROR, "Error opening log file");
        return -1;
    }

    writeLog(LogLevel::INFO, "LogManager started");
    return Manager::startUp();
}

// Close file on shutdown
void LogManager::shutDown() {
    if (m_log_file != nullptr) {
        fclose(m_log_file);
        m_log_file = nullptr;
    }
    Manager::shutDown();
}

void LogManager::setLogLevel(const LogLevel level) {
    if (level == log_level) return;

    writeLog(LogLevel::INFO,
             std::format("Log level changed from {} to {}",
                         levelToString(log_level), levelToString(level)));

    log_level = level;
}

auto LogManager::getLogLevel() const -> LogLevel { return log_level; }

// Debug Mode: flush to file on every write in case of crash
void LogManager::setFlush(const bool do_flush) { m_do_flush = do_flush; }

auto LogManager::writeLog(const LogLevel level,
                          const std::string& msg) const -> int {
    if (level < log_level || m_log_file == nullptr) return 0;

    const std::string time_str =
        (m_clock != nullptr) ? df::Clock::getSystemTimeString() : "NoClock";
    const int frame = (m_clock != nullptr) ? m_clock->getFrame() : -1;

    // Format final log string
    const auto formatted = std::format("[{}][Frame {}] {} : {}", time_str,
                                       frame, levelToString(level), msg);

    if (log_level == LogLevel::TRACE || log_level == LogLevel::DEBUG) {
        std::fprintf(stderr, "%s\n", formatted.c_str());
    }

    std::fprintf(m_log_file, "%s\n", formatted.c_str());

    if (m_do_flush) {
        std::fflush(m_log_file);
        if (log_level == LogLevel::TRACE || log_level == LogLevel::DEBUG) {
            std::fflush(stderr);
        }
    }

    return 1;
}

}  // namespace df
