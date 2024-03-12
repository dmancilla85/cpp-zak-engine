#pragma once

#include "actor.h"

#define MAX_ACTORS			20


class ActorMgr {

public:
	static bool Register (Actor *actor);
	static bool Unregister (Actor *actor);

	static void SetHypnotizedTotalTime(float time) { _hypnotizedTotalTime = time; }
	static float GetHypnotizedTime() { return _hypnotizedTime; }
	static float GetHypnotizedTotalTime() { return _hypnotizedTotalTime; }

	static void Clear() { _lastElement = 0; _lastPlayer = 0;}

	static void SendEvent(int event, Actor *sender);

	static void Draw();
	static void Update(float dt);
	
private:
	static Actor *_list[MAX_ACTORS];
	static int _lastElement;
	static int _lastPlayer;

	static float _hypnotizedTotalTime;
	static float _hypnotizedTime;

};