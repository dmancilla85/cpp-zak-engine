#include "game.h"

TestGame::TestGame() {
  // do nothing
  }

TestGame::~TestGame() {
  // do nothing
  }

float UniformRectilinearMotion(float x, float v, float dt) {
  return x += v*dt; 
  }

float UniformlyAcceleratedRectilinearMotion(float x, float v, float a, float dt) {
  return x += v*dt + a/2 * dt * dt; 
  }

bool TestGame::CheckCollisionBoundedBox(Entity2D *entity1, Entity2D *entity2) {
  float x1 = entity1->GetPosX();
  float y1 = entity1->GetPosY();
  float w1 = entity1->GetWidth();
  float h1 = entity1->GetHeight();

  float x2 = entity2->GetPosX();
  float y2 = entity2->GetPosY();
  float w2 = entity2->GetWidth();
  float h2 = entity2->GetHeight();

  return ((x2 >x1 && x2 < x1 + w1) || (x1 > x2 && x1 < x2 + w2)) && 
    ((y2 > y1 && y2 < y1 + h1) || (y1 > y2 && y1 <y2 +h2));
  }

bool TestGame::CheckCollisionBoundedCircle(Entity2D *entity1, Entity2D *entity2) {
  float x1 = entity1->GetPosX();
  float y1 = entity1->GetPosY();
  float r1 = entity1->GetWidth() / 2;

  float x2 = entity2->GetPosX();
  float y2 = entity2->GetPosY();
  float r2 = entity2->GetWidth() / 2;

  float d = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);

  return d < (r1 + r2) * (r1 + r2); 
  }



void TestGame::OnDraw() {
  _shapeQuad.Draw();
  _shapeTriangle.Draw();
  _shapeTranslated.Draw();
  _shapeRotated.Draw();
  _shapeScaled.Draw();
  }

void TestGame::OnFrame() {

  float dt = (float)_fpsMeter.GetDT();

  _shapeQuad.SetPosX(
    UniformRectilinearMotion(_shapeQuad.GetPosX(), 0.05f, dt));

  _shapeTriangle.SetPosX(
    UniformlyAcceleratedRectilinearMotion(_shapeTriangle.GetPosX(),0, 0.02f, dt)
    );

  // update
  _shapeTriangle.Update(dt);
  _shapeQuad.Update(dt);
  _shapeTranslated.Update(dt);
  _shapeRotated.Update(dt);
  _shapeScaled.Update(dt);

  if(CheckCollisionBoundedBox(&_shapeQuad, &_shapeTranslated)) {
    _shapeQuad.SetPos(0, 0);
    _shapeTranslated.SetPos(-100, -100);

    }

  if(_shapeTriangle.IsColliding(&_shapeScaled)) {
      _shapeTriangle.SetPos(-100, 100);
    }

  if(KeyDown(DIK_ESCAPE))
    PostQuitMessage(0);
  }

bool TestGame::OnShutdown() {
  return true;
  }

bool TestGame::OnInit()  {

  _shapeQuad.SetShape(ZAK_SHAPE_QUAD);
  _shapeQuad.SetDim(100, 100);
  _shapeQuad.SetPos(0, 0);
  _shapeQuad.SetColor(0xFF00FF00);

  _shapeTriangle.SetShape(ZAK_SHAPE_TRIANGLE);
  _shapeTriangle.SetDim(60, 60);
  _shapeTriangle.SetPos(-100, 100);
  _shapeTriangle.SetColor(0xFFD49CB4);
  _shapeTriangle.SetCollisionType(Entity2D::eCollisionBBox);
  _shapeTriangle.SetCollisionSize(60, 60);
  _shapeTriangle.SetCollisionPos(0, 0);
  _shapeTriangle.SetCheckCollision(true);

  _shapeTranslated.SetShape(ZAK_SHAPE_QUAD);
  _shapeTranslated.SetDim(120, 120);
  _shapeTranslated.SetPos(-200, -100);
  _shapeTranslated.SetColor(0xFFFF0000);
  _shapeTranslated.SetSpeed(0.1f);
  _shapeTranslated.SetMovDirection(90.0f);
  _shapeTranslated.SetMoving(true);

  _shapeRotated.SetShape(ZAK_SHAPE_TRIANGLE);
  _shapeRotated.SetDim(60, 60);
  _shapeRotated.SetPos(0, -100);
  _shapeRotated.SetColor(0xFFF58B57);
  _shapeRotated.SetRotationSpeed(0.08f);
  _shapeRotated.SetRotating(true);

  _shapeScaled.SetShape(ZAK_SHAPE_QUAD);
  _shapeScaled.SetPos(200, 150);
  _shapeScaled.SetDim(80, 80);
  _shapeScaled.SetScale(2.0f, 2.0f);
  _shapeScaled.SetColor(0xFF999999);
  _shapeScaled.SetCollisionType(Entity2D::eCollisionBBox);
  _shapeScaled.SetCollisionSize(160, 160);
  _shapeScaled.SetCollisionPos(0, 0);
  _shapeScaled.SetCheckCollision(true);

  return true;
  }