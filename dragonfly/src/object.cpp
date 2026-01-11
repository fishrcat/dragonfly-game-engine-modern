// object.cpp — Base class for game engine objects

// Engine
#include "object.h"

#include "log_manager.h"

namespace df {

Object::Object() {
    static int last_obj_id = -1;

    // Increment the last object id and assign to the latest object
    last_obj_id++;
    setId(last_obj_id);

    LM.writeLog(LogLevel::DEBUG,
                std::format("Object: created object with id {}", getId()));
}

void Object::setId(const int new_id) { m_id = new_id; }

auto Object::getId() const noexcept -> int { return m_id; }

void Object::setType(const std::string_view new_type) { m_type = new_type; }

auto Object::getType() const noexcept -> const std::string& { return m_type; }

void Object::setPosition(const Vector& new_pos) { m_position = new_pos; }

auto Object::getPosition() const noexcept -> const Vector& {
    return m_position;
}

}  // namespace df
