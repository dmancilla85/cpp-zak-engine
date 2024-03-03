#pragma once
#include "zakengine/zak.h"

using namespace zak;

#define LOADING_STATE_NONE	0
#define LOADING_STATE_FADEIN	1
#define LOADING_STATE_WAIT	2
#define LOADING_STATE_FADEOUT	3

#define LOADING_WAIT_TIME	1000.0f

#ifndef INTERVAL_TIME_X
#define INTERVAL_TIME_X	 3.0f
#endif

class Loading :
	public Sprite
{
public:
	Loading(void);
	~Loading(void);

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