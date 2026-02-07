// config.h — Engine level config
// TODO: Research post-compile settings manager best practices

#pragma once

// Engine
#include "color.h"

// System
#include <clock.h>

#include <SFML/Graphics.hpp>
#include <chrono>

#define DEBUG_MODE

namespace df {

// Frame time min (ms)
inline constexpr std::chrono::milliseconds TARGET_TIME{33};

// SFML Defaults
constexpr int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
constexpr int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
constexpr int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
constexpr int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
constexpr int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar;
constexpr Color WINDOW_BACKGROUND_COLOR_DEFAULT = Color::Black;
constexpr std::string WINDOW_TITLE_DEFAULT = "Dragonfly";

// Graphics Settings
inline constexpr std::string FONT_FILE;

// Debug Mode Settings

constexpr auto dev_runtime = Clock::duration_t(6000);

}  // namespace df
