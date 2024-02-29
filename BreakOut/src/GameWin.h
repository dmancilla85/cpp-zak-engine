#pragma once
#include "zakengine/zak.h"

using namespace zak;

#define WIN_STATE_NONE	0
#define WIN_STATE_FADEIN	1
#define WIN_STATE_WAIT	2
#define WIN_STATE_FADEOUT	3

#ifndef WAIT_TIME
#define WAIT_TIME	2000.0f
#endif

#ifndef INTERVAL_TIME_X
#define INTERVAL_TIME_X	 3.0f
#endif

class GameWin :
	public Sprite
{
public:
	GameWin(void);
	~GameWin(void);

	bool Initialize();
	int GetState(){return _state;}
	void SetState(int state) { _state = state;}
	void Update(float dt);
	void Draw();

private:
	int _state;
	DWORD _currentColor;
	float _accum;

};