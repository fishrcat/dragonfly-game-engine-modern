#pragma once
#include "Event.h"
#include "EventKeyboard.h"
#include "ViewObject.h"

class GameStart : public df::ViewObject {

private:
  void start();
  void kbd(const df::EventKeyboard *p_keyboard_event);

public:
  GameStart();
  int eventHandler(const df::Event *p_e) override;
  int draw() override;
};
