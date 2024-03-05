#pragma once

#include "zakengine/zak.h"
#include "mathutil.h"
#include "checkcollision.h"

#define SHOT_SPEED 0.6f

using namespace zak;

class Shot : public Sprite {
public:
  bool Initialize();
  void Shoot(float fromX, float fromY, float angle);
  void Update(float dt);
  void OnCollide(Entity2D *entity);

  Shot();
  ~Shot();

private:
  float m_vx;
  float m_vy;
  };