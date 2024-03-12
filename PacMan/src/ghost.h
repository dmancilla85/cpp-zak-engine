#pragma once

#include "actor.h"
#include "CheckCollision.h"
#include "ActorMgr.h"
#include "level.h"

#define GHOST_MOVING_INTERVAL	150.0f
#define GHOST_HOME_TIME			7000.0f

#define GHOST_SPEED				0.1f
#define GHOST_HYPNOTIZED_SPEED	0.05f
#define GHOST_HOME_SPEED		0.04f

#define GHOST_SMACHINE_STATES	6


class Ghost : public Actor {

public:
	virtual bool Initialize();
	void SetEvent(int event);

	void GetOutHome();
	void Search();
	void Chase(float x, float y);
	void Hypnotized();
	void GoHome();
	
	// Mostrará la animación correspondiente
	// cuando el fantasma está en estado
	// no-hipnotizado
	void UpdateNormalAnimation();

	// Mostrará la animación correspondiente
	// cuando el fantasma está en estado
	// hipnotizado
	void UpdateHypnotizedAnimation();

	// Mostrará la animación correspondiente
	// cuando el fantasma está en estado
	// muerto
	void UpdateEyesAnimation();

	void SetRandomAction();

	void Update(float dt);

	void OnCollide(Entity2D *entity);

	void SetHomePos(float x, float y);

	void SetHomeTime(float time) { _homeTime = time; }

	void SetMaxSpeed(float speed) { _maxSpeed = speed; }

	Ghost();
	~Ghost();

protected:
	Animation	_moveSide;
	Animation	_moveUp;
	Animation	_moveDown;
	Animation	_eyesSide;
	Animation	_eyesUp;
	Animation	_eyesDown;
	Animation	_hypnotized;
	Animation	_hypnotizedFinishing;

	float		_movingTime;

	float		_homeTime;

	float		_maxSpeed;

	int			_stateMachine[GHOST_SMACHINE_STATES][GHOST_SMACHINE_STATES];
};