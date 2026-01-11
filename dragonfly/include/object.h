// object.cpp — Base class for game engine objects

#pragma once

// Engine
#include "vector.h"

// System
#include <string>

namespace df {

class Object {
    public:
    Object() = default;
    virtual ~Object() = default;

    void setId(int new_id) noexcept;
    [[nodiscard]] auto getId() const noexcept -> int;

    void setType(std::string_view new_type);
    [[nodiscard]] auto getType() const noexcept -> const std::string&;

    void setPosition(const Vector& new_pos);
    [[nodiscard]] auto getPosition() const noexcept -> const Vector&;

    private:
    int m_id{};
    std::string m_type;
    Vector m_position;
};
}  // namespace df
