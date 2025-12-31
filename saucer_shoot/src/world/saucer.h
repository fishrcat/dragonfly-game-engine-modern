#pragma once
#include "EventCollision.h"
#include "Object.h"

class Saucer : public df::Object {

public:
  Saucer();
  ~Saucer() override;
  auto eventHandler(const df::Event *p_e) -> int override;

private:
  // TODO: Move to game engine config loader
  const int saucer_points = 10;
  void moveToStart();
  void out();
  void hit(const df::EventCollision *p_c) const;
  void destroy();
};
