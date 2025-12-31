// Engine
#include "EventStep.h"
#include "GameManager.h"
#include "WorldManager.h"
// Project
#include "game_start.h"

#include "player/hero.h"
#include "player/nuke.h"
#include "points.h"
#include "utility.h"
#include "world/saucer.h"
#include "world/star.h"

GameStart::GameStart() {

  // Set up
  Object::setType("GameStart");
  Object::setSprite("gamestart");
  ViewObject::setLocation(df::CENTER_CENTER);

  // Input hooks
  registerInterest(df::KEYBOARD_EVENT);
}

auto GameStart::eventHandler(const df::Event *p_e) -> int {

  if (p_e->getType() == df::KEYBOARD_EVENT) {
    const auto *p_keyboard_event = dynamic_cast<const df::EventKeyboard *>(p_e);
    kbd(p_keyboard_event);
    return 1;
  }

  return 0;
}

void GameStart::kbd(const df::EventKeyboard *p_keyboard_event) {

  switch (p_keyboard_event->getKey()) {
  case df::Keyboard::P: // Play
    start();
    break;
  case df::Keyboard::Q: // Quit
    GM.setGameOver();
    break;
  default:
    break;
  }
}

auto GameStart::draw() -> int { return df::Object::draw(); }

void GameStart::start() {

  // TODO: Move to game engine config loader
  constexpr int num_stars = 16;
  constexpr int num_saucers = 16;

  for (int i = 0; i < num_stars; i++) {
    new Star;
  }

  for (int i = 0; i < num_saucers; i++) {
    new Saucer;
  }
  new Hero;

  // Displays
  new PointsDisplay;
  new NukesDisplay;

  ViewObject::setActive(false);
}
