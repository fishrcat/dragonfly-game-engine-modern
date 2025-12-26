#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

void loadResources(void) {
  RM.loadSprite("sprites-simple/saucer-spr.txt", "saucer");
}

auto main(int argc, char *argv[]) -> int {

  // Startup
  if (GM.startUp()) {
    LM.writeLog("Error starting game manager");
    GM.shutDown();
    return 1;
  }

  // Debug
  LM.setFlush(true);

  df::splash();

  GM.shutDown();

  return 0;
}
