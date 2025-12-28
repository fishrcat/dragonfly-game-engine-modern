// Engine
#include "EventStep.h"
#include "WorldManager.h"
// Project
#include "explosion.h"

Explosion::Explosion() {

  // Set up
  if (Object::setSprite("explosion") == 0) {
    time_to_live = getAnimation().getSprite()->getFrameCount();
  } else {
    time_to_live = 0;
  }

  // Input hooks
  registerInterest(df::STEP_EVENT);

  // No collision
  Object::setSolidness(df::SPECTRAL);
}

auto Explosion::eventHandler(const df::Event *p_e) -> int {

  if (p_e->getType() == df::STEP_EVENT) {
    step();
    return 1;
  }

  return 0;
}

void Explosion::step() {

  time_to_live--;
  if (time_to_live <= 0) {
    WM.markForDelete(this);
  }
}
