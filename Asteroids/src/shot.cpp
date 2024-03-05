#include "shot.h"

Shot::Shot() {
  //do nothing
  }
  
Shot::~Shot(){
  //do nothing
  }

bool Shot::Initialize() {
  if(!LoadIni("data/graphics/shot.spr"))
    return false;

  m_vx = 0;
  m_vy = 0;

  SetVisible(false);
  SetName("shot");
  SetCheckCollision(false);
  SetCollisionRadius(5);

  if(!CheckCollision::Register(this, 1))
      return false;

  return true;
 }

void Shot::Shoot(float fromX, float fromY, float angle){
 SetPos(fromX, fromY);
 SetAngleZ(angle);

 m_vx = SHOT_SPEED * cosf(DEGREE_TO_RAD(angle));
 m_vy = SHOT_SPEED * sinf(DEGREE_TO_RAD(angle));
 SetVisible(true);
 SetCheckCollision(true);
  }

void Shot::Update(float dt) {
  float x = GetPosX();
  float y = GetPosY();

  static int w = (int) g_renderer.GetViewPortWidth() / 2;
  static int h = (int) g_renderer.GetViewPortHeight() / 2;

  x += m_vx * dt;
  y += m_vy * dt;

  if(abs(x) > w || abs(y) > h) {
    SetVisible(false);
    this->SetCheckCollision(false);
    }

  SetPos(x, y);
 }

void Shot::OnCollide(Entity2D *entity) {
  this->SetVisible(false);
  this->SetCheckCollision(false);
 }