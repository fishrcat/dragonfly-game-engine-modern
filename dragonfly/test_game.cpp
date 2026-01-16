// Engine
#include <chrono>

#include "game_manager.h"
#include "log_manager.h"
#include "object.h"
#include "world_manager.h"

class Player : public df::Object {
    public:
    Player() { setType("Player"); }
};

class Enemy : public df::Object {
    public:
    Enemy() { setType("Enemy"); }
};

auto main(int argc, char* argv[]) -> int {
    // Startup
    if (GM.startUp() != df::StartupResult::Ok) {
        GM.shutDown();
        return LM.writeLog(df::LogLevel::DEBUG, "Error starting manager");
    }

    LM.writeLog(df::LogLevel::DEBUG, "Started instance of test game");

    WM.insertObject(new Player());
    WM.insertObject(new Enemy());

    for (const auto* obj : WM.getAllObjects()) {
        LM.writeLog(df::LogLevel::DEBUG,
                    std::format("Object type: {}", obj->getType()));
    }
    for (const auto* player : WM.objectsOfType("Player")) {
        LM.writeLog(df::LogLevel::DEBUG,
                    std::format("Found Player with ID {}", player->getId()));
    }

    for (df::Object* enemy : WM.objectsOfType("Enemy")) {
        WM.markForDelete(enemy);
    }

    GM.run();

    GM.shutDown();

    return 0;
}
