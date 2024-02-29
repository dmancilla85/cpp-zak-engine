#pragma once

#include "zakengine/zak.h"

using namespace zak;

class TestGame : public Game {
public:
  void OnFrame();
  bool OnShutdown();
  bool OnInit();

  TestGame();
  ~TestGame();
private:

  };
