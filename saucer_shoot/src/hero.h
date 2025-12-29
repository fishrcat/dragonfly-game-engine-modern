#pragma once
#include "EventKeyboard.h"
#include "Object.h"


class Hero : public df::Object {

    public:
        Hero();
        auto eventHandler(const df::Event *p_e) -> int override;

    private:
        int move_slowdown;
        int move_countdown;
        void kbd(const df::EventKeyboard *p_keyboard_event);
        void move(int delta_y);
        void step();
};
