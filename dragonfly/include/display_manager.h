// display_manager.h — Manager of the graphics display

#pragma once

// Engine
#include "color.h"
#include "config.h"
#include "manager.h"
#include "vector.h"

#define DM df::DisplayManager::getInstance()

namespace df {

// ASCII char <-> window pixel utils
auto charHeight() -> float;
auto charWidth() -> float;
auto spacesToPixels(Vector spaces) -> Vector;
auto pixelsToSpaces(Vector pixels) -> Vector;

class DisplayManager : public Manager {
    private:
    DisplayManager();

    sf::Font m_font;
    sf::RenderWindow *m_p_window;
    int m_window_horizontal_pixels;
    int m_window_vertical_pixels;
    int m_window_horizontal_chars;
    int m_window_vertical_chars;
    Color m_background_color{WINDOW_BACKGROUND_COLOR_DEFAULT};

    public:
    DisplayManager(const DisplayManager &) = delete;  // Disable copy
    auto operator=(const DisplayManager &) -> DisplayManager & =
                                                  delete;  // Disable assignment
    static auto getInstance() -> DisplayManager &;         // Singleton

    [[nodiscard]] auto startUp()
        -> StartupResult override;  // Enforce startup checks
    void shutDown() noexcept override;

    auto drawCh(Vector world_pos, char ch, Color color) const -> int;

    auto getHorizontalChars() const -> int;
    auto getVerticalChars() const -> int;
    auto getHorizontalPixels() const -> int;
    auto getVerticalPixels() const -> int;

    auto swapBuffers() const -> int;

    auto getWindow() const -> sf::RenderWindow * { return m_p_window; };

    void setBackgroundColor(Color new_color);
    auto loadFont(std::optional<std::string_view> font_path = std::nullopt)
        -> int;
};

}  // namespace df
