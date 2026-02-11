// object.h — Base class for game engine objects

#pragma once

// Engine
#include "event.h"
#include "vector.h"

// System
#include <string>

namespace df {

class Object {
    public:
    explicit Object(const Vector& init_pos = {});
    virtual ~Object();

    void setId(const int new_id) { m_id = new_id; }
    auto getId() const noexcept -> int { return m_id; }

    void setType(const std::string_view new_type) { m_type = new_type; }
    auto getType() const noexcept -> const std::string& { return m_type; }

    void setPosition(const Vector new_pos) { m_position = new_pos; }
    auto getPosition() const noexcept -> const Vector& { return m_position; }

    void setSpeed(const float new_speed) { m_speed = new_speed; }
    auto getSpeed() const noexcept -> float { return m_speed; }

    void setDirection(const Vector new_direction) {
        m_direction = new_direction;
    }
    auto getDirection() const noexcept -> Vector { return m_direction; }

    void setVelocity(Vector new_velocity);
    auto getVelocity() const -> Vector;
    [[nodiscard]] auto predictPosition() const -> Vector;

    virtual auto eventHandler([[maybe_unused]] const Event* p_e) -> int {
        return 0;
    }

    virtual auto draw() -> int = 0;

    auto setAltitude(int new_altitude) -> int;
    auto getAltitude() const -> int { return m_altitude; }

    private:
    int m_id{-1};
    std::string m_type;

    int m_altitude{0};

    Vector m_position;
    Vector m_direction;
    float m_speed{0.0};
};
}  // namespace df
