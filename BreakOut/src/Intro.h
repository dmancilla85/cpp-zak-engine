#pragma once
#include "zakengine/zak.h"

using namespace zak;

#define INTRO_STATE_NONE	0
#define INTRO_STATE_FADEIN	1
#define INTRO_STATE_WAIT	2
#define INTRO_STATE_FADEOUT	3

#ifndef WAIT_TIME
#define WAIT_TIME	2000.0f
#endif

#ifndef INTERVAL_TIME
#define INTERVAL_TIME	5.0f
#endif

class Intro :
	public Sprite
{
public:
	Intro(void);
	~Intro(void);

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
