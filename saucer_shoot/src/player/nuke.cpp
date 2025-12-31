// Project
#include "nuke.h"

EventNuke::EventNuke() { setType(NUKE_EVENT); };

NukesDisplay::NukesDisplay() {

  // Set up
  ViewObject::setLocation(df::TOP_LEFT);
  ViewObject::setViewString(NUKE_STRING);
  ViewObject::setValue(1);
  ViewObject::setColor(df::YELLOW);
};
