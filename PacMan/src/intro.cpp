#include "intro.h"

Intro::Intro() {

}

Intro::~Intro() {

}

bool Intro::Initialize() {
	// Cargamos la introducción
	if (!Sprite::LoadIni("data/graphics/intro.spr"))
		return false;

	_state = INTRO_STATE_FADEIN;

	_currentColor = D3DCOLOR_ARGB(0,0xFF,0xFF,0xFF);

	_accum = 0.0f;

	return true;
}

void Intro::Update(float dt) {
	Sprite::Update(dt);

	_accum += dt;

	if (KeyDown(DIK_ESCAPE) || KeyDown(DIK_RETURN)) {
		_state = INTRO_STATE_FADEOUT;
	}

	switch(_state) {
		case INTRO_STATE_FADEIN:
			if (_accum > INTERVAL_TIME) {
				_currentColor += D3DCOLOR_ARGB(0x1,0,0,0);
				if (_currentColor >= D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0xFF)) {
					_currentColor = D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0xFF);
					_state = INTRO_STATE_WAIT;
				}
				_accum -= INTERVAL_TIME;
			}
			break;

		case INTRO_STATE_WAIT:
			if (_accum > WAIT_TIME) {
				_state = INTRO_STATE_FADEOUT;
				_accum -= WAIT_TIME;
			}
			break;

		case INTRO_STATE_FADEOUT:
			if (_accum > INTERVAL_TIME) {
				_currentColor -= D3DCOLOR_ARGB(0x1,0,0,0);

				if (_currentColor <= D3DCOLOR_ARGB(0,0xFF,0xFF,0xFF)) {
					_currentColor = D3DCOLOR_ARGB(0,0xFF,0xFF,0xFF);
					_state = INTRO_STATE_NONE;
				}
				_accum -= INTERVAL_TIME;
			}
			break;
	}
}

void Intro::Draw() {
	g_renderer.EnableModulate();
	g_renderer.SetModulationColor(_currentColor);

	Sprite::Draw();
	
	g_renderer.DisableModulate();
}


