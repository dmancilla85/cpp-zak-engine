#pragma once

#include "zakengine/zak.h"
#include "level.h"

using namespace zak;

#define ACTOR_ACTION_NONE	0
#define ACTOR_ACTION_LEFT	1
#define ACTOR_ACTION_RIGHT	2
#define ACTOR_ACTION_UP		3
#define ACTOR_ACTION_DOWN	4

#define ACTION_ACTION_COUNT	5

#define ACTOR_EVENT_EAT		1
#define ACTOR_EVENT_TIME	2
#define ACTOR_EVENT_OUTHOME	3
#define ACTOR_EVENT_FOUND	4
#define ACTOR_EVENT_LOST	5
#define ACTOR_EVENT_PILL	6
#define ACTOR_EVENT_INHOME	7
#define ACTOR_EVENT_REINIT	8


#define GHOST_STATE_HOME		0
#define GHOST_STATE_GETOUTHOME	1
#define GHOST_STATE_SEARCH		2
#define GHOST_STATE_HYPNOTIZED	3
#define GHOST_STATE_CHASE		4
#define GHOST_STATE_GOHOME		5

#define PACMAN_STATE_ALIVE		0
#define PACMAN_STATE_DYING		1


class Actor : public Sprite {

public:
	virtual bool Initialize()=0;
	
	virtual void SetEvent(int event)=0;

	void SetState(int state);
	int GetState();
	
	bool SetAction(int action); 
	int GetAction() { return _action; } 

	int GetLastAction() { return _lastAction;}
	
	virtual void Update(float dt);

	void CenterOnRow(int col, int row);
	void CenterOnCol(int col, int row);

	void SetRange(float range) { _range = range; }
	float GetRange() { return _range; }

	bool IsInRange(Actor *actor) {
		static float x1;
		static float y1;
		static float x2;
		static float y2;

		GetPos(x1,y1);
		actor->GetPos(x2,y2);

		if ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1) <= (_range)*(_range)) {
			return true;
		}

		return false;
	}

	// Solo es usado por los fantasmas
	void SetPlayer(Actor *player) { _player = player; }
	Actor *GetPlayer() { return _player; }

	Actor() : _action(0), _state(0),_range(0.0f), _player(NULL) {}
	~Actor(){}

protected:
	int		_action;
	int		_lastAction;

	int		_state;

	float	_range;

	float		_homePosX;
	float		_homePosY;

	int			_homeCol;
	int			_homeRow;



	Actor	*_player;
};