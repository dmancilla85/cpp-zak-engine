#pragma once

#include "zakengine/zak.h"
#include "mathutil.h"
#include "checkcollision.h"

using namespace zak;

#define ASTEROID_START_POS_X (float) (g_renderer.GetViewPortWidth() / 2)
#define ASTEROID_START_POS_Y (float) (g_renderer.GetViewPortHeight() / 2)

#define ASTEROID_MIN_ROTSPEED 5
#define ASTEROID_MAX_ROTSPEED 12

#define ASTEROID_MIN_SPEED 5
#define ASTEROID_MAX_SPEED 10

#define ASTEROID_COLLISION_RADIUS 24

class Asteroid : public Sprite {
public:
  bool Initialize(int type = 0);
  void Update(float dt);
  void Draw();
  void Explode();
  void OnCollide(Entity2D *pEntity);
  void ResetCounter() { m_count = 0; }
  int GetCount() { return m_count; }

  Asteroid();
	~Asteroid();

private:
  float m_vx;
  float m_vy;
  float m_rotSpeed;
  float m_rotAngle;
  float m_angle;
  float m_speed;
  int m_type;
  
  static int m_count;

  Asteroid *m_pChild;
  Sprite *m_pSprExplosion;
  Animation *m_pAniExplosion;
  };