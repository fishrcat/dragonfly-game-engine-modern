// log_manager.cpp — Logging to file

// Project
#include "log_manager.h"

// System
#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <ctime>

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

void LogManager::setLogLevel(LogLevel level) {
    if (level == log_level) return;

    writeLog(LogLevel::INFO, "Log level changed from %s to %s",
             levelToString(log_level), levelToString(level));

    log_level = level;
}

auto LogManager::getLogLevel() const -> LogLevel { return log_level; }

// Debug Mode: flush to file on every write in case of crash
void LogManager::setFlush(bool do_flush) { m_did_flush = do_flush; }

auto LogManager::writeLog(LogLevel level, const char* fmt, ...) -> int {
    if (level < log_level || m_log_file == nullptr) return 0;

    // Timestamp
    // TODO: Replace with std::format chrono or engine clock impelementation
    constexpr int kTimeBufferSize = 48;
    constexpr int kMillisecondsInSecond = 1000;

    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto t = std::chrono::system_clock::to_time_t(now);
    auto ms = now_ms.time_since_epoch().count() % kMillisecondsInSecond;

    std::tm local_tm{};
    localtime_r(&t, &local_tm);

    char time_buf[kTimeBufferSize];
    std::snprintf(time_buf, sizeof(time_buf),
                  "%04d-%02d-%02d %02d:%02d:%02d.%03d", local_tm.tm_year + 1900,
                  local_tm.tm_mon + 1, local_tm.tm_mday, local_tm.tm_hour,
                  local_tm.tm_min, local_tm.tm_sec, static_cast<int>(ms));

    // Format varargs
    constexpr std::size_t kMessageBufferSize = 1024;
    char message_buf[kMessageBufferSize];

    va_list args;
    va_start(args, fmt);
    const int msg_len =
        std::vsnprintf(message_buf, sizeof(message_buf), fmt, args);
    va_end(args);

    if (msg_len < 0) return 0;

    // Print to stderr DEBUG or lower
    if (level == LogLevel::TRACE || level == LogLevel::DEBUG) {
        std::fprintf(stderr, "%s : %s : %s\n", time_buf, levelToString(level),
                     message_buf);
    }

    // Print to log file
    std::fprintf(m_log_file, "%s : %s : %s\n", time_buf, levelToString(level),
                 message_buf);

    // Flush if enabled
    if (m_did_flush) {
        if (level == LogLevel::TRACE || level == LogLevel::DEBUG)
            std::fflush(stderr);
        std::fflush(m_log_file);
    }

    return 1;
}

}  // namespace df
