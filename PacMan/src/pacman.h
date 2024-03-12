#pragma once

#include "actor.h"
#include "CheckCollision.h"
#include "ActorMgr.h"
#include "level.h"

#define PACMAN_SPEED			0.1f

#define ROTATION_SPEED			1.0f
#define ROTATION_ACCEL			0.0005f

#define PACMAN_SMACHINE_STATES	2

#define PACMAN_LIVES			3


class Pacman : public Actor {

public:
	bool Initialize();
	void SetEvent(int event);
	int	 GetLives() { return _lives; } 

	void Update(float dt);

	void OnCollide(Entity2D *entity);

	Pacman();
	~Pacman();

private:
	int			_lives;
	Animation	_move;
	float		_rotationSpeed;
	int			_stateMachine[PACMAN_SMACHINE_STATES][PACMAN_SMACHINE_STATES];

};