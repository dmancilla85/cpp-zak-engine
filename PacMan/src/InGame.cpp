#include "InGame.h"

InGame::InGame() {
	_currentLevel = 0;
}

InGame::~InGame() {
}

bool InGame::Initialize(int level) {

	// Inicializamos el estado
	_state = GAME_STATE_NONE;

	CheckCollision::Clear();
	ActorMgr::Clear();

	if (!Level::Initialize(level))
		return false;

	if (!_pacman.Initialize())
		return false;

	if (!_ghost.Initialize())
		return false;

	if (!_ghost2.Initialize())
		return false;

	if (!_ghost3.Initialize())
		return false;

	if (!_ghost4.Initialize())
		return false;


	if (!_lives.LoadIni("data/graphics/pacman.spr"))
		return false;

	_lives.SetFrame(1);
	
	ActorMgr::SetHypnotizedTotalTime(HYPNOTIZED_TIME);

	return true;
}

bool InGame::Shutdown() {
	CheckCollision::Clear();
	ActorMgr::Clear();

	return true;
}

void InGame::Update(float dt) {

	if (_pacman.GetState() == PACMAN_STATE_ALIVE) {
		if (KeyPressed(DIK_LEFT)) {
			_pacman.SetAction(ACTOR_ACTION_LEFT);
		} else if (KeyPressed(DIK_RIGHT)) {
			_pacman.SetAction(ACTOR_ACTION_RIGHT);
		}

		if (KeyPressed(DIK_UP)) {
			_pacman.SetAction(ACTOR_ACTION_UP);
		} else if (KeyPressed(DIK_DOWN)) {
			_pacman.SetAction(ACTOR_ACTION_DOWN);
		}
	}
	if (KeyDown(DIK_F12)) {
		g_window.SaveScreenshot("screenshot.bmp", 800,600,32);
	}
	Level::Update(dt);
	ActorMgr::Update(dt);
	CheckCollision::Check();

	if (Level::GetPointsRemaining() == 0) {
		_state = GAME_STATE_NEXTLEVEL;
	}

	// Si presionamos escape, salimos al menu
	if (KeyDown(DIK_ESCAPE))
		_state = GAME_STATE_EXIT;

	if (_pacman.GetLives() <= 0)
		_state = GAME_STATE_EXIT;

	_lives.Update(dt);
}

void InGame::Draw() {
	Level::Draw();
	ActorMgr::Draw();

	for (int i=0; i<_pacman.GetLives(); i++) {
		_lives.SetPos(LIVES_POS_X+i*_lives.GetWidth()*_lives.GetScale()+2, LIVES_POS_Y);
		_lives.Draw();
	}
}

