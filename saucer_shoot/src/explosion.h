#pragma once
#include "Object.h"

class Explosion : public df::Object {

public:
  Explosion();
  auto eventHandler(const df::Event *p_e) -> int override;

private:
  int time_to_live;
  void step();
};
