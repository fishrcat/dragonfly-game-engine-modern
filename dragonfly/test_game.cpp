// Engine
#include "log_manager.h"
#include "manager.h"

auto main(int argc, char *argv[]) -> int {
    // Debug
    LM.startUp();
    LM.setFlush(true);
    LM.setLogLevel(df::LogLevel::DEBUG);

    // Startup
    df::Manager manager;
    if (manager.startUp()) {
        manager.shutDown();
        return LM.writeLog(df::LogLevel::DEBUG, "Error starting manager");
    }

    LM.writeLog(df::LogLevel::DEBUG, "Started %d instance of test game", 1);

    manager.shutDown();

    return 0;
}
