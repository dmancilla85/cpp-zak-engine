#pragma once

#include "zakengine/zak.h"
#include "ship.h"
#include "asteroidmanager.h"
#include "checkcollision.h"

#define GAME_STATE_NONE		0
#define GAME_STATE_EXIT		1
#define GAME_STATE_NEXT_LEVEL		2

using namespace zak;

class InGame {
public:
	bool Initialize(int level);
	bool Shutdown();

	void SetState(int state) { m_state = state; }
	int GetState() { return m_state; }

	void Update(float dt);
	void Draw();

	InGame();
	~InGame();

private:
	int			m_state;
	Ship		*m_pShip;
};