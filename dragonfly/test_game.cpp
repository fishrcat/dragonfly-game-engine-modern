// Engine
#include <chrono>

#include "game_manager.h"
#include "log_manager.h"
#include "object.h"
#include "object_list.h"

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

    df::ObjectList players;
    players.append(new Player());

    df::ObjectList enemies;
    enemies.append(new Enemy());

    df::ObjectList world_objects;
    world_objects.append(players);
    world_objects.append(enemies);

    for (const auto& obj_ptr : world_objects) {
        LM.writeLog(df::LogLevel::DEBUG,
                    std::format("Object type: {}", obj_ptr->getType()));
    }

    GM.run();

    GM.shutDown();

    return 0;
}
