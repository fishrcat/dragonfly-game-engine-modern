#pragma once
#include "Event.h"
#include "EventKeyboard.h"
#include "Music.h"
#include "ViewObject.h"

class GameStart : public df::ViewObject {

private:
  void start();
  void kbd(const df::EventKeyboard *p_keyboard_event);
  df::Music *p_music;

public:
  GameStart();
  auto eventHandler(const df::Event *p_e) -> int override;
  auto draw() -> int override;
  void playMusic() const;
};
