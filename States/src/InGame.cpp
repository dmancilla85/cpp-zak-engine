#include "InGame.h"

InGame::InGame() {
	_sprite = NULL;
	_aniWalk = NULL;
	_aniHit = NULL;
}

InGame::~InGame() {
	// Destruimos los objetos
	if (_sprite)
		delete _sprite;

	if (_aniWalk)
		delete _aniWalk;

	if (_aniHit)
		delete _aniHit;
}

bool InGame::Initialize() {
	// Creamos el objeto sprite
	_sprite = new Sprite;

	if (!_sprite) {
		Shutdown();
		return false;
	}

	// Cargamos el sprite
	if (!_sprite->LoadIni("data/graphics/roxy.spr")) {
		Shutdown();
		return false;
	}
	
	// Creamos la animación de caminar
	_aniWalk = new Animation;

	if (!_aniWalk){
		Shutdown();
		return false;
	}

	// Cargamos la animación de caminar
	if (!_aniWalk->Load("data/graphics/walk.ani")) {
		Shutdown();
		return false;
	}

	// Creamos la animación de golpear
	_aniHit = new Animation;

	if (!_aniHit) {
		Shutdown();
		return false;
	}
	// Cargamos la animación de golpear
	if (!_aniHit->Load("data/graphics/hit.ani")) {
		Shutdown();
		return false;
	}

	// Iniciamos el sprite en el frame 22
	_sprite->SetFrame(22);

	// Inicializamos el estado
	_state = GAME_STATE_NONE;

	return true;
}

bool InGame::Shutdown() {
	// Destruimos los objetos
	if (_sprite)
		delete _sprite;

	if (_aniWalk)
		delete _aniWalk;

	if (_aniHit)
		delete _aniHit;

	_sprite = NULL;
	_aniWalk = NULL;
	_aniHit = NULL;

	return true;
}

void InGame::Update(float dt) {

	// Si presionamos escape, salimos al menu
	if (KeyDown(DIK_ESCAPE))
		_state = GAME_STATE_EXIT;

	// Si presionamos las teclas de movimiento
	// corremos la animación de caminar
	if (KeyDown(DIK_UP) || KeyDown(DIK_LEFT) || KeyDown(DIK_RIGHT) || KeyDown(DIK_DOWN))
		_sprite->SetAnimation(_aniWalk);
	
	// Si presionamos la tecla espacio
	// corremos la animación golpear
	if (KeyDown(DIK_SPACE))
		_sprite->SetAnimation(_aniHit);
	
	// Si ninguna tecla está presionada
	// dejamos de animar y mostramos el frame 22
	if (!KeyPressed(DIK_UP) && !KeyPressed(DIK_LEFT) && !KeyPressed(DIK_RIGHT) && !KeyPressed(DIK_DOWN) && !KeyPressed(DIK_SPACE)) {
		_sprite->SetAnimation(NULL);
		_sprite->SetFrame(22);
	}

	// Actualizamos el sprite
	_sprite->Update(dt);
}

void InGame::Draw() {
	// Dibujamos el sprite
	_sprite->Draw();
}

