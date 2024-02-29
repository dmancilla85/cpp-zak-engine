#include "game.h"

TestGame::TestGame() {

  }

TestGame::~TestGame() {

  }

void TestGame::OnDraw() {
  _sprite.Draw();
  }

void TestGame::OnFrame() {

  _sprite.Update((float)_fpsMeter.GetDT());

  if(KeyDown(DIK_ESCAPE))
    PostQuitMessage(0);
  }

bool TestGame::OnShutdown() {
  return true;
  }

bool TestGame::OnInit()  {

  if(!_sprite.LoadIni("./data/scorpion.spr")) {
    return false;
    }

  if(!_animation.Load("./data/scorpion.ani")) {
    return false;
    }

  _sprite.SetAnimation(&_animation);

  return true;
  }
