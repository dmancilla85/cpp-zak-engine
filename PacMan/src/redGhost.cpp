#include "redGhost.h"

bool RedGhost::Initialize() {
	if (!Ghost::Initialize())
		return false;

	if (!_moveSide.Load("data/graphics/redghostside.ani"))
		return false;

	if (!_moveUp.Load("data/graphics/redghostup.ani"))
		return false;

	if (!_moveDown.Load("data/graphics/redghostdown.ani"))
		return false;

	SetAnimation(&_moveUp);

	_stateMachine[GHOST_STATE_HOME][GHOST_STATE_GETOUTHOME]		= ACTOR_EVENT_TIME;
	_stateMachine[GHOST_STATE_HOME][GHOST_STATE_SEARCH]			= ACTOR_EVENT_OUTHOME;
	_stateMachine[GHOST_STATE_GETOUTHOME][GHOST_STATE_SEARCH]	= ACTOR_EVENT_OUTHOME;
	_stateMachine[GHOST_STATE_SEARCH][GHOST_STATE_CHASE]		= ACTOR_EVENT_FOUND;
	_stateMachine[GHOST_STATE_SEARCH][GHOST_STATE_HYPNOTIZED]	= ACTOR_EVENT_PILL;
	_stateMachine[GHOST_STATE_CHASE][GHOST_STATE_HOME]			= ACTOR_EVENT_EAT;
	_stateMachine[GHOST_STATE_CHASE][GHOST_STATE_HYPNOTIZED]	= ACTOR_EVENT_PILL;
	_stateMachine[GHOST_STATE_CHASE][GHOST_STATE_SEARCH]		= ACTOR_EVENT_LOST;
	_stateMachine[GHOST_STATE_HYPNOTIZED][GHOST_STATE_SEARCH]	= ACTOR_EVENT_TIME;
	_stateMachine[GHOST_STATE_HYPNOTIZED][GHOST_STATE_GOHOME]	= ACTOR_EVENT_EAT;
	_stateMachine[GHOST_STATE_GOHOME][GHOST_STATE_HOME]			= ACTOR_EVENT_INHOME;

	SetRange(250);
	SetState(GHOST_STATE_HOME);

	SetMaxSpeed(RED_GHOST_SPEED);

	float x,y; 
	int col,row;

	if (!Level::_map.GetColRowFromTile(TILE_RED_GHOST,col,row))
		return false;
	
	if (!Level::_map.GetWorldCoordsFromColRow(col,row,x,y))
		return false;

	Level::_map.SetTile(col,row,TILE_EMPTY);

	SetPos(x, y);
	SetHomePos(x, y);


	return true;
}