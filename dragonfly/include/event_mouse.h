#pragma once

// Engine
#include "event.h"
#include "vector.h"

// System
#include <SFML/Window/Mouse.hpp>
#include <cstdint>

namespace df::Input::Mouse {

enum class Action : std::uint8_t {
    Undefined,
    Clicked,
    Moved,
};

// Alias df::Input::Mouse::Button to sf::Mouse::Button
using Button = sf::Mouse::Button;

}  // namespace df::Input::Mouse

namespace df {

inline constexpr auto MOUSE_EVENT = "df::mouse";

class EventMouse : public Event {
    public:
    EventMouse() { setType(MOUSE_EVENT); }

    void setButton(Input::Mouse::Button new_button) { m_button = new_button; }
    auto getButton() const -> Input::Mouse::Button { return m_button; }

    void setAction(Input::Mouse::Action new_action) { m_action = new_action; }
    auto getAction() const -> Input::Mouse::Action { return m_action; }

    void setPos(Vector new_pos) { m_pos = new_pos; }
    auto getPos() const -> Vector { return m_pos; }

    private:
    Input::Mouse::Button m_button;
    Input::Mouse::Action m_action;
    Vector m_pos;
};

}  // namespace df
