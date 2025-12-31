// Engine
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
// Project
#include "display/game_start.h"

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

  // Sprites
  RM.loadSprite("assets/sprites-simple/saucer-spr.txt", "saucer");
  RM.loadSprite("assets/sprites-simple/ship-spr.txt", "ship");
  RM.loadSprite("assets/sprites-simple/bullet-spr.txt", "bullet");
  RM.loadSprite("assets/sprites-simple/explosion-spr.txt", "explosion");
  RM.loadSprite("assets/sprites-simple/gameover-spr.txt", "gameover");
  RM.loadSprite("assets/sprites-simple/gamestart-spr.txt", "gamestart");

  // Sound effects
  RM.loadSound("assets/sounds/fire.wav", "fire");
  RM.loadSound("assets/sounds/explode.wav", "explode");
  RM.loadSound("assets/sounds/nuke.wav", "nuke");
  RM.loadSound("assets/sounds/game-over.wav", "game over");

  // Music
  RM.loadMusic("assets/sounds/start-music.wav", "start music");
}

void populateWorld() { new GameStart; }
