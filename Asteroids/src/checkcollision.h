#pragma once

#include "zakengine/zak.h"

using namespace zak;

#define COLLISION_MAX_ENTITIES 200

class CheckCollision {
public:
  static bool Register(Entity2D *entity, int list);
  static bool Unregister(Entity2D *entity, int list);
  static void Clear();
  static void Check();

private:
  static Entity2D *m_pList1[COLLISION_MAX_ENTITIES];
  static Entity2D *m_pList2[COLLISION_MAX_ENTITIES];
  static int m_lastList1;
  static int m_lastList2;
  };
