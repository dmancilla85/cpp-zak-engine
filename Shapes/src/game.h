#pragma once

#include "zakengine/zak.h"

using namespace zak;

class TestGame : public Game {

public:
  void OnFrame();
  bool OnShutdown();
  bool OnInit();
  void OnDraw();
  bool CheckCollisionBoundedBox(Entity2D *entity1, Entity2D *entity2);
  bool CheckCollisionBoundedCircle(Entity2D *entity1, Entity2D *entity2);

  TestGame();
  ~TestGame();
  
private:
  Shape _shapeQuad;
  Shape _shapeTriangle;
  Shape _shapeTranslated;
  Shape _shapeRotated;
  Shape _shapeScaled;
  };
