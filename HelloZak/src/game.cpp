#include "game.h"

TestGame::TestGame() {

  }

TestGame::~TestGame() {

  }

void TestGame::OnFrame() {
  if(KeyDown(DIK_ESCAPE))
    PostQuitMessage(0);
  }

bool TestGame::OnShutdown() {
  return true;
  }

bool TestGame::OnInit()  {
  return true;
  }
