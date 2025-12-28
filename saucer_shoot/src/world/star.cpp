// Engine
#include "DisplayManager.h"
#include "EventMouse.h"
#include "EventOut.h"
#include "WorldManager.h"
// Project
#include "star.h"

#include <random>

Star::Star() {

  // Set up
  Object::setType("Star");
  Object::setSolidness(df::SPECTRAL);
  Object::setAltitude(0);

  // Add parallax
  std::mt19937 rng{std::random_device{}()};
  std::uniform_int_distribution<int> dist(0, RAND_MAX);
  Object::setVelocity(df::Vector(
      static_cast<float>(-1.0) / static_cast<float>((dist(rng) % 10) + 1), 0));

  // Scatter over window view
  const df::Vector pos(
      static_cast<float>(rand() %
                         static_cast<int>(WM.getBoundary().getHorizontal())),
      static_cast<float>(rand() %
                         static_cast<int>(WM.getBoundary().getVertical())));
  Object::setPosition(pos);
}

auto Star::eventHandler(const df::Event *p_e) -> int {

  if (p_e->getType() == df::OUT_EVENT) {
    out();
    return 1;
  }

  return 0;
}

void Star::out() {

  std::mt19937 rng{std::random_device{}()};
  std::uniform_int_distribution<int> dist(0, RAND_MAX);

  const df::Vector pos(
      WM.getBoundary().getHorizontal() + static_cast<float>((dist(rng) % 20)),
      static_cast<float>(rand() %
                         static_cast<int>(WM.getBoundary().getVertical())));
  setPosition(pos);
  setVelocity(df::Vector(-1.0 / (rand() % 10 + 1), 0));
}

auto Star::draw() -> int {
  return DM.drawCh(getPosition(), STAR_CHAR, df::WHITE);
}
