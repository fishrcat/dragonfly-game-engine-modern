// object.h — Base class for game engine objects

#pragma once

// Engine
#include "vector.h"

// System
#include <string>

namespace df {

class Object {
    public:
    Object();
    virtual ~Object() = default;

    void setId(int new_id);
    auto getId() const noexcept -> int;

    void setType(std::string_view new_type);
    auto getType() const noexcept -> const std::string&;

    void setPosition(const Vector& new_pos);
    [[nodiscard]] auto getPosition() const noexcept
        -> const Vector&;  // Using nodiscard for heavy gets only

    private:
    int m_id{-1};
    std::string m_type;
    Vector m_position;
};
}  // namespace df
