add_library(dragonfly)
add_library(dragonfly::dragonfly ALIAS dragonfly)

target_sources(dragonfly
    PRIVATE
    src/manager.cpp
    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
    include/manager.h
)

target_compile_features(dragonfly PUBLIC cxx_std_20)

target_include_directories(dragonfly
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(dragonfly PRIVATE -Wall -Wextra -Wpedantic)
elseif (MSVC)
  target_compile_options(dragonfly PRIVATE /W4 /permissive- /WX)
endif()

option(DRAGONFLY_BUILD_TESTS "Build Dragonfly tests" ON)

if (DRAGONFLY_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
