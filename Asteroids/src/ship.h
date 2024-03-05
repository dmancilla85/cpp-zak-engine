#pragma once

#include "zakengine/zak.h"

#include "mathutil.h"
#include "shot.h"
#include "checkcollision.h"

using namespace zak;

#define SHOTS_COUNT 20

#define SHIP_ANIM_FPS 15.0f
#define SHIP_ROT_SPEED 0.2f
#define SHIP_MAXSPEED 0.4f
#define SHIP_ACCEL 0.0003f

// states
#define SHIP_STATE_NONE 0
#define SHIP_STATE_INVISIBLE 1
#define SHIP_STATE_EXPLODING 2

// colors
#define SHIP_COLOR_INVISIBLE 0xA08080FF

#define INVISIBLE_TIME 2000.0f

class Ship : public Sprite {
public:
  bool Initialize();
  void Reset();
  void Update(float dt);
  void Draw();
  void OnCollide(Entity2D *entity);
  int GetLives() { return m_lives; }

  Ship();
  ~Ship();

private:
  void SwapLast(int which);

  float m_accumTime;
  float m_angle;
  float m_vx;
  float m_vy;

  int m_lives;
  int m_state;
  int m_lastShot;

  float m_invisibleTime;
  DWORD m_currentColor;

  Sprite *m_pSprExplosion;
  Animation *m_pAniExplosion;
  Shot *m_pShots[SHOTS_COUNT];
  };
