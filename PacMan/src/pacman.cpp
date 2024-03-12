#include "pacman.h"

Pacman::Pacman(){
	_state = 0;

	SetName("pacman");
}

Pacman::~Pacman(){
}


bool Pacman::Initialize() {
	if (!this->LoadIni("data/graphics/pacman.spr"))
		return false;

	if (!_move.Load("data/graphics/pacman.ani"))
		return false;

	SetAnimation(&_move);

	_homePosX = Level::_pacmanStartX;
	_homePosY = Level::_pacmanStartY;

	this->SetPos(_homePosX,_homePosY);

	if(!CheckCollision::Register(this,1)) {
		Log.Trace("No se pudo registrar un elemento en la lista de colisión\n");
		return false;
	}

	if(!ActorMgr::Register(this)) {
		Log.Trace("No se pudo registrar un elemento en la lista de colisión\n");
		return false;
	}

	Actor::SetAction(ACTOR_ACTION_RIGHT);
	Actor::SetSpeed(PACMAN_SPEED);

	ZeroMemory(_stateMachine,PACMAN_SMACHINE_STATES*PACMAN_SMACHINE_STATES*sizeof(int));

	_stateMachine[PACMAN_STATE_ALIVE][PACMAN_STATE_DYING]		= ACTOR_EVENT_EAT;
	_stateMachine[PACMAN_STATE_DYING][PACMAN_STATE_ALIVE]		= ACTOR_EVENT_REINIT;

	SetState(PACMAN_STATE_ALIVE);
	SetCheckCollision(true);
	
	_lives = PACMAN_LIVES;

	return true;
}

void Pacman::SetEvent(int event) {

	for (int i=0; i < PACMAN_SMACHINE_STATES; i++) {
		if (_stateMachine[GetState()][i] == event) {
			SetState(i);

			if (event == ACTOR_EVENT_EAT) {
				_lives--;
				SetAnimation(NULL);
				SetFrame(1);
				_rotationSpeed = ROTATION_SPEED;
				Actor::SetAction(ACTOR_ACTION_NONE);
				SetCheckCollision(false);
			} else if (event == ACTOR_EVENT_REINIT) {
				SetAngleZ(0);
				this->SetPos(_homePosX,_homePosY);
				Actor::SetAction(ACTOR_ACTION_RIGHT);
				SetAnimation(&_move);
				SetCheckCollision(true);
			}

			break;
		}
	}
}


void Pacman::Update(float dt) {
	static int tile = 0;
	static int col = 0;
	static int row = 0;

	Actor::Update(dt);

	switch(_state) {
		case PACMAN_STATE_DYING:
			if (_rotationSpeed > 0) {
				_rotationSpeed -= dt*ROTATION_ACCEL;
				SetAngleZ(GetAngleZ()+dt*_rotationSpeed);
			} else {
				SetEvent(ACTOR_EVENT_REINIT);
			}
			break;
		case PACMAN_STATE_ALIVE:
			switch(GetAction()) {
				case ACTOR_ACTION_LEFT:
					SetAngleZ(0);
					if (!GetFlipHorizontal())
						FlipHorizontal();
					break;
				case ACTOR_ACTION_RIGHT:
					SetAngleZ(0);
					if (GetFlipHorizontal())
						FlipHorizontal();
					break;
				case ACTOR_ACTION_UP:
					SetAngleZ(90);
					if (GetFlipHorizontal())
						FlipHorizontal();
					break;
				case ACTOR_ACTION_DOWN:
					SetAngleZ(90);
					if (!GetFlipHorizontal())
						FlipHorizontal();
					break;
			}

			Level::_map.GetColRowFromWorldCoords(GetPosX(), GetPosY(), col, row);
			tile = Level::_map.GetTileFromColRow(col, row);

			if (tile == TILE_PILL) {
				ActorMgr::SendEvent(ACTOR_EVENT_PILL,this);
				Level::_points--;
			} else if (tile == TILE_POINT) {
				Level::_points--;
			}

			Level::_map.SetTile(col,row,TILE_EMPTY);

			break;
	}
}


void Pacman::OnCollide(Entity2D *entity) {
	if (strcmp(entity->GetName(), "ghost") == 0) {
		Actor *actor = (Actor*)entity;
		if (actor->GetState() == GHOST_STATE_HYPNOTIZED) {
			actor->SetEvent(ACTOR_EVENT_EAT);
		} 
	}
}
