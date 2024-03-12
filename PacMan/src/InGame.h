#pragma once

#include "zakengine/zak.h"
#include "pacman.h"
#include "pinkGhost.h"
#include "redGhost.h"
#include "cyanGhost.h"
#include "orangeGhost.h"
#include "level.h"

using namespace zak;

#define GAME_STATE_NONE			0
#define GAME_STATE_EXIT			1
#define GAME_STATE_NEXTLEVEL	2

#define HYPNOTIZED_TIME		10000.0f

#define LIVES_POS_X			-200
#define LIVES_POS_Y			-270

class InGame {
public:
	bool Initialize(int level);
	bool Shutdown();

	void SetState(int state) { _state = state; }
	int GetState() { return _state; }

	void Update(float dt);
	void Draw();

	InGame();
	~InGame();

private:
	int			_state;
	int			_currentLevel;
	
	Pacman		_pacman;

	RedGhost	_ghost;
	PinkGhost	_ghost2;
	CyanGhost	_ghost3;
	OrangeGhost	_ghost4;

	Sprite		_lives;
};