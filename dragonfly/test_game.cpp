// Engine
#include <chrono>
#include <thread>

#include "game_manager.h"
#include "log_manager.h"

auto main(int argc, char *argv[]) -> int {
    // Startup
    if (GM.startUp() != df::StartupResult::Ok) {
        GM.shutDown();
        return LM.writeLog(df::LogLevel::DEBUG, "Error starting manager");
    }

    LM.writeLog(df::LogLevel::DEBUG, "Started instance of test game");

    GM.run();

    GM.shutDown();

    return 0;
}
