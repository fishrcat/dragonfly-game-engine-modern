// Engine
#include "DisplayManager.h"
#include "EventMouse.h"
#include "WorldManager.h"
// Project
#include "reticle.h"

Reticle::Reticle() {

  // Set up
  Object::setType("Reticle");

  // Input hooks
  registerInterest(df::MSE_EVENT);

  // No collision and foreground
  Object::setSolidness(df::SPECTRAL);
  Object::setAltitude(df::MAX_ALTITUDE);
}

auto Reticle::eventHandler(const df::Event *p_e) -> int {

  // Map reticle to live mouse position
  if (p_e->getType() == df::MSE_EVENT) {
    if (const auto *const p_mouse_event =
            dynamic_cast<const df::EventMouse *>(p_e);
        p_mouse_event->getMouseAction() == df::MOVED) {
      setPosition(p_mouse_event->getMousePosition());
      return 1;
    }
  }

  return 0;
}

auto Reticle::draw() -> int {
  return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}
