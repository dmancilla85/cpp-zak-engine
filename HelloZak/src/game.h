#pragma once

#include <sstream>
#include "zakengine/zak.h"

using namespace zak;

class TestGame : public Game {
public:
  void OnFrame();
  bool OnShutdown();
  bool OnInit();
  void OnDraw();

  TestGame();
  ~TestGame();
private:
  void ShowInputDebug();
  };
