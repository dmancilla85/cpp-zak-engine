#include "checkcollision.h"

Entity2D* CheckCollision::m_pList1[COLLISION_MAX_ENTITIES];
Entity2D* CheckCollision::m_pList2[COLLISION_MAX_ENTITIES];
int CheckCollision::m_lastList1 = 0;
int CheckCollision::m_lastList2 = 0;

bool CheckCollision::Register(Entity2D *entity, int list) {
  switch(list) {
    case 1: 
      if(m_lastList1 < COLLISION_MAX_ENTITIES){
        m_pList1[m_lastList1] = entity;
        m_lastList1++;
        return true;
        }
      break;

    case 2:
      if(m_lastList2 < COLLISION_MAX_ENTITIES){
        m_pList2[m_lastList2] = entity;
        m_lastList2++;
        return true;
        }
      break;
    }

  return false;
  }

void CheckCollision::Clear() {
  m_lastList1 = 0;
  m_lastList2 = 0;
  }

void CheckCollision::Check() {
  static float x1;
  static float y1;
  static float r1;
  static float x2;
  static float y2;
  static float r2;

  for (int i=0; i < m_lastList1; i++) {
		x1 = m_pList1[i]->GetPosX();
		y1 = m_pList1[i]->GetPosY();
		r1 = m_pList1[i]->GetCollisionRadius();

		for (int j=0; j < m_lastList2; j++) {
			x2 = m_pList2[j]->GetPosX();
			y2 = m_pList2[j]->GetPosY();
			r2 = m_pList2[j]->GetCollisionRadius();
			if (m_pList1[i]->GetCheckCollision() && m_pList2[j]->GetCheckCollision()) {
				if ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1) <= (r1+r2)*(r1+r2)) {
					m_pList1[i]->OnCollide(m_pList2[j]);
					m_pList2[j]->OnCollide(m_pList1[i]);
				}
			}
		}
	}
  }