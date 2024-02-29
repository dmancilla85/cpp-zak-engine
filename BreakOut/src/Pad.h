#pragma once

#include "zakengine/zak.h"

using namespace zak;

#define MOVE_NONE	0
#define MOVING		1

class Pad : public Sprite
{
public:
	Pad(void);
	~Pad(void);

	bool Initialize();
	void OnCollide(Entity2D *entity);
	void SetAction(int action, float speed = 0.0f) 
		{_currentAction = action; _vx = speed;}
	void Update(float dt);
	void SetInitialPos();

private:
	int _currentAction;
	float _vx;

};
