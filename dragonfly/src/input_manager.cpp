// input_manager.cpp — Manager of player input (keyboard and mouse)

// Engine
#include "input_manager.h"

#include "display_manager.h"
#include "event_keyboard.h"
#include "event_mouse.h"
#include "log_manager.h"
#include "world_manager.h"

// System
#include <SFML/Graphics.hpp>

namespace df {

InputManager::InputManager() { setType("InputManager"); }

auto InputManager::getInstance() -> InputManager& {
    static InputManager instance;
    return instance;
}

auto InputManager::startUp() -> StartupResult {
    LM.writeLog(LogLevel::INFO, "InputManager: starting up");

    if (!DM.isStarted()) {
        LM.writeLog(LogLevel::INFO,
                    "InputManager dependency DisplayManager not started");
        return StartupResult::Failed;
    }

    sf::RenderWindow* window = DM.getWindow();
    window->setKeyRepeatEnabled(false);

    return Manager::startUp();
}

void InputManager::shutDown() noexcept {
    LM.writeLog(LogLevel::INFO, "InputManager: shutting down");

    sf::RenderWindow* window = DM.getWindow();
    window->setKeyRepeatEnabled(false);

    Manager::shutDown();
}

void InputManager::getInput() {
    auto* window = DM.getWindow();
    while (const auto event = window->pollEvent()) {
        event->visit([&]<typename T0>(const T0& e) -> auto {
            using T = std::decay_t<T0>;

            // Key press
            if constexpr (std::is_same_v<T, sf::Event::KeyPressed>) {
                const EventKeyboard key{e.code,
                                        Input::Keyboard::Action::Pressed};
                WM.onEvent(&key);
            }

            // Key release
            else if constexpr (std::is_same_v<T, sf::Event::KeyReleased>) {
                const EventKeyboard key{e.code,
                                        Input::Keyboard::Action::Released};
                WM.onEvent(&key);
            }

            // Mouse position change
            else if constexpr (std::is_same_v<T, sf::Event::MouseMoved>) {
                const EventMouse mouse{
                    std::nullopt, Input::Mouse::Action::Moved,
                    pixelsToSpaces(Vector(e.position.x, e.position.y))};
                WM.onEvent(&mouse);
            }

            // Mouse button
            else if constexpr (std::is_same_v<T,
                                              sf::Event::MouseButtonPressed>) {
                const EventMouse mouse{
                    e.button, Input::Mouse::Action::Clicked,
                    pixelsToSpaces(Vector(e.position.x, e.position.y))};
                WM.onEvent(&mouse);
            }
        });
    }

    // Continuous press
    for (int k = 0; std::cmp_less(k, sf::Keyboard::KeyCount); ++k) {
        if (const auto keyCode = static_cast<sf::Keyboard::Key>(k);
            sf::Keyboard::isKeyPressed(keyCode)) {
            EventKeyboard key{keyCode, Input::Keyboard::Action::Held};
            WM.onEvent(&key);
        }
    }

    // Continuous press
    for (int b = 0; std::cmp_less(b, sf::Mouse::ButtonCount); ++b) {
        if (const auto button = static_cast<sf::Mouse::Button>(b);
            sf::Mouse::isButtonPressed(button)) {
            const auto pos = sf::Mouse::getPosition(*window);
            EventMouse mouse{button, Input::Mouse::Action::Held,
                             pixelsToSpaces(Vector(static_cast<float>(pos.x),
                                                   static_cast<float>(pos.y)))};
            WM.onEvent(&mouse);
        }
    }
}

}  // namespace df
