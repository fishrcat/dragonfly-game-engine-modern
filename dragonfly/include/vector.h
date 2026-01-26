// vector.h — 2D vector object and math overrides

#pragma once

#include "SFML/System/Vector2.hpp"

namespace df {

struct Vector {
    float x{0.F};
    float y{0.F};

    // SFML repr util
    [[nodiscard]] constexpr auto toSF() const noexcept -> sf::Vector2f {
        return {x, y};
    }

    constexpr Vector() = default;
    constexpr Vector(const float x_, const float y_) : x(x_), y(y_) {}

    [[nodiscard]] auto magnitude() const noexcept -> float;
    void normalize() noexcept;

    // Unary operators
    constexpr auto operator+() const noexcept -> Vector { return *this; }

    constexpr auto operator-() const noexcept -> Vector { return {-x, -y}; }

    // Binary operators
    constexpr auto operator+(const Vector& rhs) const noexcept -> Vector {
        return {x + rhs.x, y + rhs.y};
    }

    constexpr auto operator-(const Vector& rhs) const noexcept -> Vector {
        return {x - rhs.x, y - rhs.y};
    }

    // Scalar multiplication / division operators
    constexpr auto operator*(const float s) const noexcept -> Vector {
        return {x * s, y * s};
    }

    constexpr auto operator/(const float s) const noexcept -> Vector {
        return {x / s, y / s};
    }

    // Compound assignment operators
    auto operator+=(const Vector& rhs) noexcept -> Vector& {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    auto operator-=(const Vector& rhs) noexcept -> Vector& {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    auto operator*=(float s) noexcept -> Vector& {
        x *= s;
        y *= s;
        return *this;
    }

    auto operator/=(float s) noexcept -> Vector& {
        x /= s;
        y /= s;
        return *this;
    }

    // Comparison operators
    constexpr auto operator==(const Vector& rhs) const noexcept -> bool {
        return x == rhs.x && y == rhs.y;
    }

    constexpr auto operator!=(const Vector& rhs) const noexcept -> bool {
        return !(*this == rhs);
    }
};
}  // namespace df
