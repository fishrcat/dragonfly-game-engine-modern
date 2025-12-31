// Engine
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
// Project
#include "src/hero.h"
#include "src/nuke.h"
#include "src/points.h"
#include "src/saucer.h"
#include "src/star.h"

void loadResources();

void populateWorld();

auto main(int argc, char *argv[]) -> int {
  // Startup
  if (GM.startUp()) {
    GM.shutDown();
    return LM.writeLog("Error starting game manager");
  }
  df::splash();

  // Debug
  LM.setFlush(true);

  // Set up world
  loadResources();
  populateWorld();

  // Run game loop
  GM.run();

  GM.shutDown();

  return 0;
}

void loadResources() {
  RM.loadSprite("assets/sprites-simple/saucer-spr.txt", "saucer");
  RM.loadSprite("assets/sprites-simple/ship-spr.txt", "ship");
  RM.loadSprite("assets/sprites-simple/bullet-spr.txt", "bullet");
  RM.loadSprite("assets/sprites-simple/explosion-spr.txt", "explosion");
}

void populateWorld() {

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
}
