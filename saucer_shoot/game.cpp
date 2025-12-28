// Engine
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
// Project
#include "src/saucer.h"


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
  RM.loadSprite("sprites-simple/saucer-spr.txt", "saucer");
}

void populateWorld() {
  new Saucer;
}
