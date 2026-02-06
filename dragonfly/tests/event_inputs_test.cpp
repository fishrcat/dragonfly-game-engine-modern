#include <gtest/gtest.h>

#include <SFML/Window/Keyboard.hpp>

#include "event_keyboard.h"
#include "event_mouse.h"

using namespace df;
using namespace df::Input::Keyboard;
using namespace df::Input::Mouse;

class EventKeyboardTest : public ::testing::Test {
    protected:
    EventKeyboard event;
};

TEST_F(EventKeyboardTest, ConstructorSetsEventType) {
    EXPECT_EQ(event.getType(), KEYBOARD_EVENT);
}

// Namespace aliasing
TEST_F(EventKeyboardTest, SetAndGetKey) {
    event.setKey(Key::A);
    EXPECT_EQ(event.getKey(), sf::Keyboard::Key::A);
}

class EventMouseTest : public ::testing::Test {
    protected:
    EventMouse event;
};

TEST_F(EventMouseTest, ConstructorSetsEventType) {
    EXPECT_EQ(event.getType(), MOUSE_EVENT);
}

// Namespace aliasing
TEST_F(EventMouseTest, SetAndGetButton) {
    event.setButton(Button::Left);
    EXPECT_EQ(event.getButton(), sf::Mouse::Button::Left);
}
