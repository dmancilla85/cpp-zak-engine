#pragma once

#include "zakengine/zak.h"

using namespace zak;

#define GAME_STATE_NONE		0
#define GAME_STATE_EXIT		1

class InGame {
public:
	bool Initialize();
	bool Shutdown();

	void SetState(int state) { _state = state; }
	int GetState() { return _state; }

	void Update(float dt);
	void Draw();

	InGame();
	~InGame();

private:
	int			_state;
	Sprite		*_sprite;
	Animation	*_aniWalk;
	Animation	*_aniHit;

};