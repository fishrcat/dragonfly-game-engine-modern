// config.h — Engine level config
// TODO: Research post-compile settings manager best practices

#pragma once

#include <chrono>

#define DEBUG_MODE

namespace df {

inline constexpr std::chrono::milliseconds TARGET_TIME{33};

}
