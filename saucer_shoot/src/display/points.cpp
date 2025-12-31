// Engine
#include "EventStep.h"
// Project
#include "points.h"

PointsDisplay::PointsDisplay() {

  // Set up
  ViewObject::setLocation(df::TOP_RIGHT);
  ViewObject::setViewString(POINTS_STRING);
  ViewObject::setColor(df::YELLOW);

  // Input hooks
  registerInterest(df::STEP_EVENT);
};

auto PointsDisplay::eventHandler(const df::Event *p_e) -> int {

  if (ViewObject::eventHandler(p_e) != 0) {
    return 1;
  }

  if (p_e->getType() == df::STEP_EVENT) {
    if (dynamic_cast<const df::EventStep *>(p_e)->getStepCount() % 30 == 0) {
      setValue(getValue() + 1);
    }

    return 1;
  }

  return 0;
}
