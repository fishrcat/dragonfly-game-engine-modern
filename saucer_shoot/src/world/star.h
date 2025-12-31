#pragma once
#include "Object.h"

#define STAR_CHAR '.'

class Star : public df::Object {

public:
  Star();
  auto draw() -> int override;
  auto eventHandler(const df::Event *p_e) -> int override;
  void out();
};
