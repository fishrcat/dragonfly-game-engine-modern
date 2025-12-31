#pragma once
#include "EventKeyboard.h"
#include "Object.h"
#include "reticle.h"

class Hero : public df::Object {

public:
  Hero();
  ~Hero() override;
  auto eventHandler(const df::Event *p_e) -> int override;

private:
  Reticle *p_reticle;
  int move_slowdown;
  int move_countdown;
  int fire_slowdown;
  int fire_countdown;
  int nuke_count;
  void kbd(const df::EventKeyboard *p_keyboard_event);
  void move(int delta_y);
  void step();
  void fire(df::Vector target);
  void mouse(const df::EventMouse *p_mouse_event);
  void nuke();
};
