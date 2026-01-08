#include "log_manager.h"

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>

#include "manager.h"

class TestLogManager : public df::LogManager {
    public:
    using df::LogManager::setFlush;
    using df::LogManager::writeLog;
};

class LogManagerFileTest : public ::testing::Test {
    protected:
    TestLogManager &log =
        static_cast<TestLogManager &>(df::LogManager::getInstance());
    const std::string logFileName = df::LOGFILE_NAME;

    void SetUp() override {
        log.startUp();
        log.setFlush(true);
        std::ofstream ofs(logFileName, std::ios::trunc);
    }

    void TearDown() override { log.shutDown(); }

    // Helper
    std::string readLogFile() {
        std::ifstream ifs(logFileName);
        std::stringstream sstream;
        sstream << ifs.rdbuf();
        return sstream.str();
    }
};

TEST_F(LogManagerFileTest, LogFileContainsMessages) {
    log.writeLog(df::LogLevel::INFO, "Game started with %d players", 4);
    log.writeLog(df::LogLevel::WARN, "Memory usage is high: %.1f MB", 512.5);
    log.writeLog(df::LogLevel::ERROR, "Failed to load resource: %s",
                 "texture.png");

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
    log.writeLog(df::LogLevel::INFO, "Flush off message");

    log.setFlush(true);
    log.writeLog(df::LogLevel::INFO, "Flush on message");

    std::string contents = readLogFile();
    EXPECT_NE(contents.find("Flush off message"), std::string::npos);
    EXPECT_NE(contents.find("Flush on message"), std::string::npos);
}
