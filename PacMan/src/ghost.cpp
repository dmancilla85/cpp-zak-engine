#include "Ghost.h"

Ghost::Ghost() : Actor() {
	_state = 0;

	SetName("ghost");
}

Ghost::~Ghost(){

}

bool Ghost::Initialize() {

	if(!CheckCollision::Register(this,2)) {
		Log.Trace("No se pudo registrar un elemento en la lista de colisión\n");
		return false;
	}

	if(!ActorMgr::Register(this)) {
		Log.Trace("No se pudo registrar un elemento en la lista de colisión\n");
		return false;
	}

	if (!this->LoadIni("data/graphics/pacman.spr"))
		return false;

	if (!_hypnotized.Load("data/graphics/ghosthypnotized.ani"))
		return false;

	if (!_hypnotizedFinishing.Load("data/graphics/ghosthypfinish.ani"))
		return false;

	if (!_eyesUp.Load("data/graphics/ghosteyesup.ani"))
		return false;
	if (!_eyesDown.Load("data/graphics/ghosteyesdown.ani"))
		return false;
	if (!_eyesSide.Load("data/graphics/ghosteyesside.ani"))
		return false;

	_movingTime = GHOST_MOVING_INTERVAL;

	ZeroMemory(_stateMachine,GHOST_SMACHINE_STATES*GHOST_SMACHINE_STATES*sizeof(int));

	SetHomeTime((float)(MathUtil::Random()%(int)(GHOST_HOME_TIME/2)+(GHOST_HOME_TIME/2)));

	_maxSpeed = GHOST_SPEED;

	SetAction(ACTOR_ACTION_NONE);

	SetCheckCollision(true);

	return true;
}

void Ghost::SetHomePos(float x, float y) { 
	_homePosX = x; 
	_homePosY = y; 

	Level::_map.GetColRowFromWorldCoords(x,y,_homeCol, _homeRow);
}


void Ghost::SetEvent(int event) {
	for (int i=0; i < GHOST_SMACHINE_STATES; i++) {
		if (_stateMachine[GetState()][i] == event) {
			SetState(i);
			_movingTime = GHOST_MOVING_INTERVAL*GHOST_SPEED/GetSpeed();
			SetHomeTime((float)(MathUtil::Random()%(int)(GHOST_HOME_TIME/2)+(GHOST_HOME_TIME/2)));
			break;
		}
	}
}

void Ghost::SetRandomAction() {
	static int action;
	static bool result=false;

	do {
		result = false;
		action = (MathUtil::Random()%ACTION_ACTION_COUNT-1)+1;

		switch (GetLastAction()) {
			case ACTOR_ACTION_LEFT:
				if (action != ACTOR_ACTION_RIGHT)
					result = SetAction(action);
				break;
			case ACTOR_ACTION_RIGHT:
				if (action != ACTOR_ACTION_LEFT)
					result = SetAction(action);
				break;
			case ACTOR_ACTION_UP:
				if (action != ACTOR_ACTION_DOWN)
					result = SetAction(action);
				break;
			case ACTOR_ACTION_DOWN:
				if (action != ACTOR_ACTION_UP)
					result = SetAction(action);
				break;
			default:
				result =  SetAction(action);
		}
	} while (!result);

}

void Ghost::GetOutHome() {
	static int col,row;

	Chase(Level::_outPosX,Level::_outPosY);

	Level::_map.GetColRowFromWorldCoords(GetPosX(), GetPosY(), col, row);

	if (col == Level::_outCol && row == Level::_outRow) {
		SetEvent(ACTOR_EVENT_OUTHOME);
	} 
}

void Ghost::Search() {
	SetRandomAction();
}

void Ghost::Chase(float x, float y) {
	int x1;
	int y1;
	int x2;
	int y2;


	Level::_map.GetColRowFromWorldCoords(GetPosX(), GetPosY(), x1, y1);
	Level::_map.GetColRowFromWorldCoords(x, y, x2, y2);

	switch(GetAction()) {
		case ACTOR_ACTION_RIGHT:
		case ACTOR_ACTION_LEFT:
			if (y1 < y2)
				SetAction(ACTOR_ACTION_DOWN);
			else if (y1 > y2) 
				SetAction(ACTOR_ACTION_UP);
			
			break;
		case ACTOR_ACTION_UP:
		case ACTOR_ACTION_DOWN:
			if (x1 > x2) 
				SetAction(ACTOR_ACTION_LEFT);
			else if (x1 < x2) 
				SetAction(ACTOR_ACTION_RIGHT);
			
			break;
		default:
			if (y1 < y2)
				SetAction(ACTOR_ACTION_DOWN);
			else if (y1 > y2) 
				SetAction(ACTOR_ACTION_UP);
			else if (x1 > x2) 
				SetAction(ACTOR_ACTION_LEFT);
			else if (x1 < x2) 
				SetAction(ACTOR_ACTION_RIGHT);

			if (GetAction() == ACTOR_ACTION_NONE) {
				SetRandomAction();
			}
			break;
	}
}

void Ghost::Hypnotized() {
	SetRandomAction();
}

void Ghost::GoHome() {
	static int col, row;

	Chase(_homePosX,_homePosY);

	Level::_map.GetColRowFromWorldCoords(GetPosX(), GetPosY(), col, row);
	
	if (col == _homeCol && row == _homeRow) {
		SetEvent(ACTOR_EVENT_INHOME);
		SetCheckCollision(true);
	} 

}

void Ghost::UpdateEyesAnimation() {
	switch(GetAction()) {
		case ACTOR_ACTION_LEFT:
			if (GetAnimation() != &_eyesSide)
				SetAnimation(&_eyesSide);
			if (GetFlipHorizontal()) 
				FlipHorizontal();
			break;
		case ACTOR_ACTION_RIGHT:
			if (GetAnimation() != &_eyesSide)
				SetAnimation(&_eyesSide);
			if (!GetFlipHorizontal())
				FlipHorizontal();
			break;
		case ACTOR_ACTION_UP:
			if (GetAnimation() != &_eyesUp)
				SetAnimation(&_eyesUp);
			break;
		case ACTOR_ACTION_DOWN:
			if (GetAnimation() != &_eyesDown)
				SetAnimation(&_eyesDown);
			break;
	}
}

void Ghost::UpdateNormalAnimation() {
	switch(GetAction()) {
		case ACTOR_ACTION_LEFT:
			if (GetAnimation() != &_moveSide)
				SetAnimation(&_moveSide);
			if (GetFlipHorizontal()) 
				FlipHorizontal();
			break;
		case ACTOR_ACTION_RIGHT:
			if (GetAnimation() != &_moveSide)
				SetAnimation(&_moveSide);
			if (!GetFlipHorizontal())
				FlipHorizontal();
			break;
		case ACTOR_ACTION_UP:
			if (GetAnimation() != &_moveUp)
				SetAnimation(&_moveUp);
			break;
		case ACTOR_ACTION_DOWN:
			if (GetAnimation() != &_moveDown)
				SetAnimation(&_moveDown);
			break;
	}
}

void Ghost::Update(float dt) {
	static int tile = 0;
	static int col = 0;
	static int row = 0;

	Actor::Update(dt);

	switch(GetState()) {
		case GHOST_STATE_HOME:
			SetSpeed(GHOST_HOME_SPEED);

			_homeTime -= dt;

			if (_homeTime <= 0) {
				SetEvent(ACTOR_EVENT_TIME);
			} else if (GetAction() == ACTOR_ACTION_NONE) {
				if (GetLastAction() == ACTOR_ACTION_UP) {
					SetAction(ACTOR_ACTION_DOWN);
				} else {
					SetAction(ACTOR_ACTION_UP);
				}
			}

			UpdateNormalAnimation();

			break;
		case GHOST_STATE_GETOUTHOME:
			SetSpeed(GHOST_HOME_SPEED);

			_movingTime += dt;

			if (_movingTime >= GHOST_MOVING_INTERVAL*GHOST_SPEED/GetSpeed() || GetAction() == ACTOR_ACTION_NONE) {
				_movingTime = 0.0f;
				GetOutHome();
			}
			UpdateNormalAnimation();
			
			break;

		case GHOST_STATE_SEARCH:
			SetSpeed(_maxSpeed);

			_movingTime += dt;

			if (_movingTime >= GHOST_MOVING_INTERVAL*GHOST_SPEED/GetSpeed() || GetAction() == ACTOR_ACTION_NONE) {
				_movingTime = 0.0f;
				Search();
			}
			UpdateNormalAnimation();

			break;
		case GHOST_STATE_HYPNOTIZED:
			SetSpeed(GHOST_HYPNOTIZED_SPEED);

			_movingTime += dt;

			if (_movingTime >= GHOST_MOVING_INTERVAL*GHOST_SPEED/GetSpeed() || GetAction() == ACTOR_ACTION_NONE) {
				_movingTime = 0.0f;
				Hypnotized();
			}

			if (ActorMgr::GetHypnotizedTime() >= ActorMgr::GetHypnotizedTotalTime()-3000.0f) {
				if (GetAnimation() != &_hypnotizedFinishing)
					SetAnimation(&_hypnotizedFinishing);
			} else if (GetAnimation() != &_hypnotized) {
				SetAnimation(&_hypnotized);
			}
			

			break;
		case GHOST_STATE_CHASE:
			SetSpeed(_maxSpeed);

			_movingTime += dt;

			if (_movingTime >= GHOST_MOVING_INTERVAL*GHOST_SPEED/GetSpeed() || GetAction() == ACTOR_ACTION_NONE) {
				_movingTime = 0.0f;
				Chase(_player->GetPosX(), _player->GetPosY());
			}
			UpdateNormalAnimation();

			break;
		case GHOST_STATE_GOHOME:
			SetSpeed(_maxSpeed);

			_movingTime += dt;

			if (_movingTime >= GHOST_MOVING_INTERVAL*GHOST_SPEED/GetSpeed() || GetAction() == ACTOR_ACTION_NONE) {
				_movingTime = 0.0f;
				GoHome();
			}

			UpdateEyesAnimation();

			break;
	}

}

void Ghost::OnCollide(Entity2D *entity) {
	if (strcmp(entity->GetName(), "pacman")==0) {
		Actor *actor = (Actor*)entity;
		if (GetState() != GHOST_STATE_HYPNOTIZED && GetState() != GHOST_STATE_GOHOME) {
			actor->SetEvent(ACTOR_EVENT_EAT);
		} else {
			SetCheckCollision(false);
		}
	}
}
