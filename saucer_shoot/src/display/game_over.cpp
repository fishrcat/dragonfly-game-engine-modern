// Engine
#include "EventStep.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "WorldManager.h"
#include "utility.h"
// Project
#include "game_over.h"
#include "game_start.h"

GameOver::GameOver() {

  // Set up
  Object::setType("GameOver");
  Object::setSprite("gameover");
  ViewObject::setLocation(df::CENTER_CENTER);

  // Explosion effect
  df::addParticles(df::SPARKS, getPosition(), 4, df::RED);
  df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);

  // Sound effect
  if (df::Sound *p_sound = RM.getSound("game over")) {
    p_sound->play();
  }

  if (Object::setSprite("gameover") == 0) {
    time_to_live = getAnimation().getSprite()->getFrameCount() *
                   getAnimation().getSprite()->getSlowdown();
  } else {
    time_to_live = 0;
  }

  // Input hooks
  registerInterest(df::STEP_EVENT);
}

GameOver::~GameOver() {

  // Remove Saucers and ViewObjects, re-activate GameStart.
  df::ObjectList object_list = WM.getAllObjects(true);
  for (int i = 0; i < object_list.getCount(); i++) {
    Object *p_o = object_list[i];
    if (p_o->getType() == "Saucer" || p_o->getType() == "ViewObject") {
      WM.markForDelete(p_o);
    }
    if (p_o->getType() == "GameStart") {
      p_o->setActive(true);
      dynamic_cast<GameStart *>(p_o)->playMusic();
    }
  }
}

auto GameOver::eventHandler(const df::Event *p_e) -> int {

  if (p_e->getType() == df::STEP_EVENT) {
    step();
    return 1;
  }

  return 0;
}

void GameOver::step() {
  time_to_live--;
  if (time_to_live <= 0)
    WM.markForDelete(this);
}

auto GameOver::draw() -> int { return df::Object::draw(); }

void GameStart::playMusic() const { p_music->play(); }
