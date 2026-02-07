#pragma once

// Engine
#include "event.h"
#include "vector.h"

// System
#include <SFML/Window/Mouse.hpp>
#include <cstdint>
#include <optional>

namespace df::Input::Mouse {

enum class Action : std::uint8_t {
    Undefined,
    Clicked,
    Held,
    Moved,
};

// Alias df::Input::Mouse::Button to sf::Mouse::Button
using Button = sf::Mouse::Button;

}  // namespace df::Input::Mouse

namespace df {

inline constexpr auto MOUSE_EVENT = "df::mouse";

class EventMouse : public Event {
    public:
    // Default (undefined event)
    EventMouse()
        : EventMouse(std::nullopt, Input::Mouse::Action::Undefined, Vector{}) {}

    // Fully-initialized event
    EventMouse(const std::optional<Input::Mouse::Button> button,
               const Input::Mouse::Action action, const Vector pos)
        : m_button(button), m_action(action), m_pos(pos) {
        setType(MOUSE_EVENT);
    }

    void setButton(const std::optional<Input::Mouse::Button> new_button) {
        m_button = new_button;
    }
    auto getButton() const -> std::optional<Input::Mouse::Button> {
        return m_button;
    }

    void setAction(const Input::Mouse::Action new_action) {
        m_action = new_action;
    }
    auto getAction() const -> Input::Mouse::Action { return m_action; }

    void setPos(const Vector new_pos) { m_pos = new_pos; }
    auto getPos() const -> Vector { return m_pos; }

    private:
    std::optional<Input::Mouse::Button> m_button;
    Input::Mouse::Action m_action;
    Vector m_pos;
};

}  // namespace df
