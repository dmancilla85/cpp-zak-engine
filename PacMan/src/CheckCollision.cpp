#include "CheckCollision.h"

Entity2D *CheckCollision::_list1[COLLISION_MAX_ENTITIES];
Entity2D *CheckCollision::_list2[COLLISION_MAX_ENTITIES];

int CheckCollision::_lastList1 = 0;
int CheckCollision::_lastList2 = 0;

bool CheckCollision::Register(Entity2D *entity, int list){
	switch (list) {
		case 1:
			if (_lastList1 < COLLISION_MAX_ENTITIES) {
				_list1[_lastList1] = entity;
				_lastList1++;
				return true;
			}
			break;
		case 2:
			if (_lastList2 < COLLISION_MAX_ENTITIES) {
				_list2[_lastList2] = entity;
				_lastList2++;
				return true;
			}
			break;
	}

	return false;
}

bool CheckCollision::Unregister(Entity2D *entity, int list) {
	int i=0;

	switch (list) {
		case 1:
			while (i<_lastList1 && _list1[i] != entity)
				i++;

			if (_list1[i] == entity) {
				_lastList1--;
				_list1[i] = _list1[_lastList1];
				_list1[_lastList1] = NULL;
				return true;
			}
			break;
		case 2:
			while (i<_lastList2 && _list2[i] != entity)
				i++;

			if (_list2[i] == entity) {
				_lastList2--;
				_list2[i] = _list2[_lastList2];
				_list2[_lastList2] = NULL;
				return true;
			}
			break;
	}
	return false;
}

void CheckCollision::Clear() {
	_lastList1 = 0;
	_lastList2 = 0;
}

void CheckCollision::Check() {
	static float x1;
	static float y1;
	static float r1;
	static float x2;
	static float y2;
	static float r2;

	for (int i=0; i < _lastList1; i++) {
		x1 = _list1[i]->GetPosX();
		y1 = _list1[i]->GetPosY();
		r1 = _list1[i]->GetCollisionRadius();

		for (int j=0; j < _lastList2; j++) {
			x2 = _list2[j]->GetPosX();
			y2 = _list2[j]->GetPosY();
			r2 = _list2[j]->GetCollisionRadius();
			if (_list1[i]->GetCheckCollision() && _list2[j]->GetCheckCollision()) {
				if ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1) <= (r1+r2)*(r1+r2)) {
					_list1[i]->OnCollide(_list2[j]);
					_list2[j]->OnCollide(_list1[i]);
				}
			}
		}
	}
}
