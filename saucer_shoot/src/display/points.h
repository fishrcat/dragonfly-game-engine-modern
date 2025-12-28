#pragma once
#include "Event.h"
#include "ViewObject.h"

#define POINTS_STRING "Points"

class PointsDisplay : public df::ViewObject {

public:
  PointsDisplay();
  auto eventHandler(const df::Event *p_e) -> int override;
};
