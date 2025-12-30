//Engine
#include "EventMouse.h"
#include "EventStep.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
// Project
#include "hero.h"
#include "bullet.h"

#include <algorithm>


Hero::Hero() {

    //Set up
    Object::setSprite("ship");
    Object::setType("Hero");

    // Input hooks
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::STEP_EVENT);
    registerInterest(df::MSE_EVENT);

    // Set starting position in world
    const float world_vert = WM.getBoundary().getVertical();
    const auto ship_height = getBox().getVertical();
    const df::Vector start_pos(ship_height + 3, world_vert / 2);
    Object::setPosition(start_pos);

    // Init motion controller
    move_slowdown = 2;
    move_countdown = move_slowdown;

    // Init fire controller
    fire_slowdown = 15;
    fire_countdown = fire_slowdown;
    p_reticle = new Reticle();
    p_reticle->draw();
}

Hero::~Hero() {
    // Create GameOver object.
    GM.setGameOver();
}

auto Hero::eventHandler(const df::Event *p_e) -> int {

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const auto *p_keyboard_event =
            dynamic_cast<const df::EventKeyboard *> (p_e);
        kbd(p_keyboard_event);
        return 1;
    }

    if (p_e->getType() == df::MSE_EVENT) {
        const df::EventMouse *p_mouse_event =
            dynamic_cast<const df::EventMouse *> (p_e);
        mouse(p_mouse_event);
        return 1;
    }

    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }

    return 0;
}

void Hero::kbd(const df::EventKeyboard *p_keyboard_event) {

    switch (p_keyboard_event->getKey()) {
    case df::Keyboard::Q:  // Quit
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            GM.setGameOver();
        }
        break;
    case df::Keyboard::W:  // Up
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            move(-1);
        }
        break;
    case df::Keyboard::S:  // Down
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            move(1);
        }
        break;
    }
}

void Hero::move(const int delta_y) {

    if (move_countdown > 0) {
        return;
    }
    move_countdown = move_slowdown;

    const df::Vector new_pos(
        getPosition().getX(),
        getPosition().getY() + static_cast<float>(delta_y)
    );

    const float current_y = new_pos.getY();
    const float min_y = getBox().getVertical();

    if (const float max_y = WM.getBoundary().getVertical() - 1; current_y > min_y && current_y < max_y) {
        WM.moveObject(this, new_pos);
    }
}

void Hero::step() {

    // Motion countdown.
    move_countdown--;
    move_countdown = std::max(move_countdown, 0);

    // Fire countdown
    fire_countdown --;
    fire_countdown = std::max(fire_countdown, 0);
}

void Hero::fire(df::Vector target) {
    if (fire_countdown > 0) {
        return;
    }
    fire_countdown = fire_slowdown;

    df::Vector v = target - getPosition();
    v.normalize();
    v.scale(1);
    const auto p = new Bullet(getPosition(), getBox().getHorizontal());
    p->setVelocity(v);
}

void Hero::mouse(const df::EventMouse *p_mouse_event) {
    if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
        (p_mouse_event->getMouseButton() == df::Mouse::LEFT)) {
        fire(p_mouse_event->getMousePosition());
    }
}
