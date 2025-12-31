#pragma once
#include "Event.h"
#include "ViewObject.h"

class GameOver : public df::ViewObject {

public:
  GameOver();
  ~GameOver() override;
  auto eventHandler(const df::Event *p_e) -> int override;

private:
  int time_to_live;
  void step();
  int draw() override;
};
