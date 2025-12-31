#pragma once
#include "Event.h"
#include "ViewObject.h"

const std::string NUKE_EVENT = "nuke";

class EventNuke : public df::Event {

public:
  EventNuke();
};

#define NUKE_STRING "Nukes"

class NukesDisplay : public df::ViewObject {

public:
  NukesDisplay();
};
