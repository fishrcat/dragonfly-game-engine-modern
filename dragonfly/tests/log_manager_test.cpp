// log_manager_test.cpp — Unit tests for df::LogManager

#include "log_manager.h"

#include <gtest/gtest.h>

#include <format>  // C++20 for std::format
#include <fstream>
#include <sstream>
#include <string>

#include "clock.h"
#include "manager.h"

class TestLogManager : public df::LogManager {
    public:
    using LogManager::setFlush;
    using LogManager::writeLog;
};

class LogManagerFileTest : public ::testing::Test {
    protected:
    TestLogManager &log =
        static_cast<TestLogManager &>(df::LogManager::getInstance());
    const std::string logFileName = df::LOGFILE_NAME;

    void SetUp() override {
        log.startUp();
        const df::Clock gameClock;
        log.setClock(gameClock);
        log.setFlush(true);
        std::ofstream ofs(logFileName, std::ios::trunc);  // clear file
    }

    void TearDown() override { log.shutDown(); }

    // Helper to read the log file contents
    auto readLogFile() const -> std::string {
        std::ifstream ifs(logFileName);
        std::stringstream sstream;
        sstream << ifs.rdbuf();
        return sstream.str();
    }
};

TEST_F(LogManagerFileTest, LogFileContainsMessages) {
    log.writeLog(df::LogLevel::INFO,
                 std::format("Game started with {} players", 4));
    log.writeLog(df::LogLevel::WARN,
                 std::format("Memory usage is high: {:.1f} MB", 512.5));
    log.writeLog(df::LogLevel::ERROR,
                 std::format("Failed to load resource: {}", "texture.png"));

    std::string contents = readLogFile();

    EXPECT_NE(contents.find("INFO"), std::string::npos);
    EXPECT_NE(contents.find("Game started with 4 players"), std::string::npos);

    EXPECT_NE(contents.find("WARN"), std::string::npos);
    EXPECT_NE(contents.find("Memory usage is high: 512.5 MB"),
              std::string::npos);

    EXPECT_NE(contents.find("ERROR"), std::string::npos);
    EXPECT_NE(contents.find("Failed to load resource: texture.png"),
              std::string::npos);
}

TEST_F(LogManagerFileTest, FlushToggleDoesNotLoseMessages) {
    log.setFlush(false);
    log.writeLog(df::LogLevel::INFO, std::string("Flush off message"));

    log.setFlush(true);
    log.writeLog(df::LogLevel::INFO, std::string("Flush on message"));

    std::string contents = readLogFile();
    EXPECT_NE(contents.find("Flush off message"), std::string::npos);
    EXPECT_NE(contents.find("Flush on message"), std::string::npos);
}
