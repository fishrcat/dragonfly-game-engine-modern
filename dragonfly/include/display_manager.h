// display_manager.h — Manager of the graphics display

#pragma once

// Project
#include "color.h"
#include "config.h"
#include "manager.h"
#include "vector.h"

#define DM df::DisplayManager::getInstance()

namespace df {

class DisplayManager : public Manager {
    private:
    DisplayManager();

    sf::Font m_font;
    sf::RenderWindow *m_p_window;
    int m_window_horizontal_pixels;
    int m_window_vertical_pixels;
    int m_window_horizontal_chars;
    int m_window_vertical_chars;
    df::Color m_background_color{WINDOW_BACKGROUND_COLOR_DEFAULT};

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

    auto swapBuffers() -> int;

    auto getWindow() const -> sf::RenderWindow *;

    void setBackgroundColor(df::Color new_color);
    auto loadFont(std::string_view font_path = FONT_FILE_DEFAULT) -> int;
};

}  // namespace df
