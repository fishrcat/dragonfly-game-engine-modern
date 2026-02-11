// object.cpp — Base class for game engine objects

// Engine
#include "object.h"

#include "log_manager.h"
#include "world_manager.h"

namespace df {

Object::Object(const Vector& init_pos) : m_position(init_pos) {
    static int last_obj_id = -1;

    // Increment the last object id and assign to the latest object
    last_obj_id++;
    setId(last_obj_id);

    LM.writeLog(LogLevel::DEBUG,
                std::format("Object: created object with id {}", getId()));

    // All constructed objects should be added to the world
    WM.insertObject(this);
}

Object::~Object() {
    LM.writeLog(LogLevel::DEBUG,
                std::format("Object: removed object with id {}", getId()));
}

void Object::setVelocity(Vector new_velocity) {
    m_speed = new_velocity.magnitude();
    new_velocity.normalize();
    m_direction = new_velocity;
}

auto Object::getVelocity() const -> Vector {
    Vector velocity = m_direction;
    velocity.scale(m_speed);
    return velocity;
}

auto Object::predictPosition() const -> Vector {
    return m_position + getVelocity();
}

}  // namespace df
