#pragma once

// Engine
#include "event.h"

// System
#include <SFML/Window/Keyboard.hpp>
#include <cstdint>

namespace df::Input::Keyboard {

enum class Action : std::uint8_t {
    Undefined,
    Pressed,
    Held,
    Released,
};

// Alias df::Input::Keyboard::Key to sf::Keyboard::Key
using Key = sf::Keyboard::Key;

}  // namespace df::Input::Keyboard

namespace df {

inline constexpr auto KEYBOARD_EVENT = "df::keyboard";

class EventKeyboard : public Event {
    public:
    EventKeyboard()
        : EventKeyboard(Input::Keyboard::Key::Unknown,
                        Input::Keyboard::Action::Undefined) {}

    EventKeyboard(const Input::Keyboard::Key key,
                  const Input::Keyboard::Action action)
        : m_key(key), m_action(action) {
        setType(KEYBOARD_EVENT);
    }

    void setKey(const Input::Keyboard::Key new_key) { m_key = new_key; }
    auto getKey() const -> Input::Keyboard::Key { return m_key; }

    void setAction(const Input::Keyboard::Action new_action) {
        m_action = new_action;
    }
    auto getAction() const -> Input::Keyboard::Action { return m_action; }

    private:
    Input::Keyboard::Key m_key;
    Input::Keyboard::Action m_action;
};

}  // namespace df
