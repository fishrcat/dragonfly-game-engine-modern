// display_manager.cpp — Manager of the graphics display

// Engine
#include "display_manager.h"

#include "config.h"
#include "log_manager.h"

namespace df {

DisplayManager::DisplayManager() {
    setType("DisplayManager");

    m_p_window = nullptr;
    m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
    m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
    m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
    m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;

    setBackgroundColor(df::Color::Black);
}

auto DisplayManager::getInstance() -> DisplayManager& {
    static DisplayManager instance;
    return instance;
}

auto DisplayManager::startUp() -> StartupResult {
    LM.writeLog(LogLevel::INFO, "DisplayManager: starting up");

    if (m_p_window == nullptr) {
        return StartupResult::Ok;
    }

    // Set up display window
    m_p_window = new sf::RenderWindow(
        sf::VideoMode(
            sf::Vector2u(m_window_horizontal_pixels, m_window_vertical_pixels)),
        WINDOW_TITLE_DEFAULT);
    m_p_window->setMouseCursorVisible(false);  // Disable cursor view
    m_p_window->setVerticalSyncEnabled(
        true);  // Sync refresh rate with hardware
    loadFont();

    return Manager::startUp();
}

void DisplayManager::shutDown() noexcept {
    LM.writeLog(LogLevel::INFO, "DisplayManager: shutting down");

    m_p_window->close();

    Manager::shutDown();
}

auto DisplayManager::getHorizontalChars() const -> int {
    return m_window_horizontal_chars;
}

auto DisplayManager::getVerticalChars() const -> int {
    return m_window_vertical_chars;
}

auto DisplayManager::getHorizontalPixels() const -> int {
    return m_window_horizontal_pixels;
}

auto DisplayManager::getVerticalPixels() const -> int {
    return m_window_vertical_pixels;
}

void DisplayManager::setBackgroundColor(const df::Color new_color) {
    m_background_color = new_color;
}

auto DisplayManager::loadFont(std::string_view font_path) -> int {
    if (!m_font.openFromFile(font_path)) {
        LM.writeLog(LogLevel::ERROR, "Font loading failed");
        return -1;
    }

    LM.writeLog(LogLevel::INFO, std::format("Loaded font: {}", font_path));
    return 0;
}

}  // namespace df
