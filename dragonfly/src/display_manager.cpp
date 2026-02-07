// display_manager.cpp — Manager of the graphics display

// Engine
#include "display_manager.h"

#include "config.h"
#include "default_font.h"
#include "log_manager.h"

namespace df {

auto charWidth() -> float {
    return static_cast<float>(DM.getHorizontalPixels()) /
           DM.getHorizontalChars();
}

auto charHeight() -> float {
    return static_cast<float>(DM.getVerticalPixels()) / DM.getVerticalChars();
}

auto spacesToPixels(const Vector spaces) -> Vector {
    return {spaces.x * charWidth(), spaces.y * charHeight()};
}

auto pixelsToSpaces(const Vector pixels) -> Vector {
    return {pixels.x / charWidth(), pixels.y / charHeight()};
}

DisplayManager::DisplayManager() {
    setType("DisplayManager");

    m_p_window = nullptr;
    m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
    m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
    m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
    m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;

    setBackgroundColor(Color::Black);
}

auto DisplayManager::getInstance() -> DisplayManager& {
    static DisplayManager instance;
    return instance;
}

auto DisplayManager::startUp() -> StartupResult {
    LM.writeLog(LogLevel::INFO, "DisplayManager: starting up");

    if (m_p_window != nullptr) {
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

    loadFont(FONT_FILE);

    return Manager::startUp();
}

void DisplayManager::shutDown() noexcept {
    LM.writeLog(LogLevel::INFO, "DisplayManager: shutting down");

    m_p_window->close();

    Manager::shutDown();
}

auto DisplayManager::drawCh(const Vector world_pos, const char ch,
                            const Color color) const -> int {
    // Ensure the display window is initialized
    if (m_p_window == nullptr) {
        LM.writeLog(LogLevel::ERROR,
                    "Attempting to draw before display window is initialized.");
        return -1;
    }

    const Vector pixel_pos = spacesToPixels(world_pos);

    // Draw background rectangle
    static sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(charWidth(), charHeight()));
    rect.setFillColor(m_background_color);
    rect.setPosition({pixel_pos.x - charWidth(), pixel_pos.y + charHeight()});
    m_p_window->draw(rect);

    // Draw the char
    static sf::Text text(m_font);
    text.setString(ch);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(color);
    text.setPosition(pixel_pos.toSF());
    m_p_window->draw(text);

    return 0;
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

auto DisplayManager::swapBuffers() const -> int {
    // Ensure the display window is initialized
    if (m_p_window == nullptr) {
        LM.writeLog(
            LogLevel::ERROR,
            "Attempting to display before display window is initialized.");
        return -1;
    }

    // Move buffer to display
    m_p_window->display();
    // Clear buffer for next draw
    m_p_window->clear();

    return 0;
}

auto DisplayManager::loadFont(std::optional<std::string_view> font_path)
    -> int {
    // Load from file if path provided
    if (font_path.has_value() && !font_path.value().empty()) {
        if (m_font.openFromFile(*font_path)) {
            LM.writeLog(LogLevel::INFO,
                        std::format("Loaded font from file: {}", *font_path));
            return 0;
        }
        LM.writeLog(
            LogLevel::ERROR,
            std::format("Font loading from file failed: {}", *font_path));
        return -1;
    }

    // Otherwise load the default font header
    if (!m_font.openFromMemory(df_font_ttf, df_font_ttf_len)) {
        LM.writeLog(LogLevel::ERROR, "Font loading from memory failed");
        return -1;
    }

    LM.writeLog(LogLevel::INFO, "Loaded default embedded font from memory");
    return 0;
}

}  // namespace df
