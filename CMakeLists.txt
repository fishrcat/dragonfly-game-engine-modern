cmake_minimum_required(VERSION 3.15)
project(DragonflyGames LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform detection
if(APPLE)
    set(LIB_NAME "dragonfly-arm64-mac")
    set(PLATFORM_LINK_LIBS "")
elseif(UNIX)
    set(PLATFORM_LINK_LIBS rt)
    add_compile_options(-Wall)
    if(EXISTS "/proc/version")
        file(READ "/proc/version" PROC_VERSION)
        if(PROC_VERSION MATCHES "microsoft|WSL")
            set(LIB_NAME "dragonfly-x64-wsl")
        else()
            set(LIB_NAME "dragonfly-x64-linux")
        endif()
    else()
        set(LIB_NAME "dragonfly-x64-linux")
    endif()
endif()

# Find SFML
find_package(SFML 3.0 QUIET COMPONENTS Graphics Window System Audio)
if(NOT SFML_FOUND)
    set(SFML_ROOT "$ENV{HOME}/src/SFML-3.0.0")
    find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Window System Audio)
endif()

# Dragonfly library
set(DRAGONFLY_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/dragonfly/include")
set(DRAGONFLY_LIBRARY "${CMAKE_SOURCE_DIR}/dragonfly/lib/lib${LIB_NAME}.a")

# Discover executable projects
file(GLOB PROJECT_DIRS RELATIVE ${CMAKE_SOURCE_DIR} "*")
foreach(PROJECT_DIR ${PROJECT_DIRS})
    if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${PROJECT_DIR}" AND
       NOT PROJECT_DIR STREQUAL "dragonfly" AND
       NOT PROJECT_DIR STREQUAL "build" AND
       NOT PROJECT_DIR STREQUAL ".git" AND
       EXISTS "${CMAKE_SOURCE_DIR}/${PROJECT_DIR}/CMakeLists.txt")
        add_subdirectory(${PROJECT_DIR})
    endif()
endforeach()

