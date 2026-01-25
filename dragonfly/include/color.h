// color.h - Recognized SFML colors
#pragma once

// System
#include <SFML/Graphics.hpp>
#include <cstdint>

namespace df {

// Alias df::Color to sf::Color to avoid book switch statements
using Color = sf::Color;

inline constexpr Color COLOR_DEFAULT = Color::White;
}  // namespace df
