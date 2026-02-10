// System
#include <chrono>
#include <format>

// Engine
#include <event_keyboard.h>

#include "display_manager.h"
#include "game_manager.h"
#include "log_manager.h"
#include "object.h"
#include "world_manager.h"

class Marker : public df::Object {
    public:
    explicit Marker(const df::Vector& init_pos = {}) : df::Object(init_pos) {
        setType("Marker");
    }

    auto draw() -> int override {
        DM.drawCh(getPosition(), *"B", df::Color::Yellow);
        return 0;
    }
};

class Player : public df::Object {
    public:
    Player() {
        setType("Player");
        setPosition({5.0F, 5.0F});
    }

    auto draw() -> int override {
        DM.drawCh(getPosition(), *"X", df::Color::Green);
        return 0;
    }

    auto eventHandler(const df::Event* p_e) -> int override {
        if (const auto* key_event =
                dynamic_cast<const df::EventKeyboard*>(p_e)) {
            if (key_event->getKey() == df::Input::Keyboard::Key::Enter &&
                key_event->getAction() ==
                    df::Input::Keyboard::Action::Pressed) {
                auto pos = getPosition();
                pos.x += 1.0F;
                setPosition(pos);
            }

            return 1;
        }

        return 0;
    }
};

class Enemy : public df::Object {
    public:
    Enemy() { setType("Enemy"); }
    auto draw() -> int override { return 0; };
};

auto main(int argc, char* argv[]) -> int {
    // Startup
    if (GM.startUp() != df::StartupResult::Ok) {
        GM.shutDown();
        return LM.writeLog(df::LogLevel::DEBUG, "Error starting manager");
    }

    LM.writeLog(df::LogLevel::DEBUG, "Started instance of test game");

    // Test WorldManager object management
    new Player();
    new Enemy();
    for (const auto* player : WM.objectsOfType("Player")) {
        LM.writeLog(df::LogLevel::DEBUG,
                    std::format("Found Player with ID {}", player->getId()));
    }
    for (df::Object* enemy : WM.objectsOfType("Enemy")) {
        WM.markForDelete(enemy);
    }

    // Place markers at the four window corners for alignment check
    const int h_chars = DM.getHorizontalChars();
    const int v_chars = DM.getVerticalChars();

    new Marker({0.0F, 0.0F});                             // Top-left
    new Marker({static_cast<float>(h_chars - 1), 0.0F});  // Top-right
    new Marker({0.0F, static_cast<float>(v_chars - 1)});  // Bottom-left
    new Marker({static_cast<float>(h_chars - 1),
                static_cast<float>(v_chars - 1)});  // Bottom-right

    // Run test game
    GM.run();

    // Test WorldManager end state
    for (const auto* obj : WM.objectsOfType("Player")) {
        LM.writeLog(df::LogLevel::DEBUG, std::format("Player end position: {}",
                                                     obj->getPosition().x));
    }

    GM.shutDown();

    return 0;
}
