// Engine
#include <event_step.h>

#include <chrono>

#include "game_manager.h"
#include "log_manager.h"
#include "object.h"
#include "world_manager.h"

class Player : public df::Object {
    public:
    Player() { setType("Player"); }

    auto eventHandler(const df::Event* p_e) -> int override {
        // Try to cast event to EventStep
        if (const auto* step_event = dynamic_cast<const df::EventStep*>(p_e)) {
            // Increment X position by 1 every step
            auto pos = getPosition();
            pos.x += 1.0F;
            setPosition(pos);

            return 1;  // event handled
        }

        return 0;  // event not handled
    }
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

    new Player();
    new Enemy();

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

    for (const auto* obj : WM.getAllObjects()) {
        LM.writeLog(df::LogLevel::DEBUG, std::format("Player end position: {}",
                                                     obj->getPosition().x));
    }

    GM.shutDown();

    return 0;
}
