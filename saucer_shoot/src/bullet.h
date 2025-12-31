#pragma once
#include "EventCollision.h"
#include "Object.h"

class Bullet : public df::Object {

public:
  Bullet(df::Vector hero_pos, float hero_width);
  auto eventHandler(const df::Event *p_e) -> int override;

private:
  void out();
  static void hit(const df::EventCollision *p_collision_event);
};
