#include "game.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#ifdef _DEBUG
#pragma comment (lib, "zakengined.lib")
#else
#pragma comment (lib, "zakengine.lib")
#endif

int main() {
  TestGame game;

  if(game.StartUp()) {
    game.Loop();
    }

  if(!game.Shutdown()) {
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
  }