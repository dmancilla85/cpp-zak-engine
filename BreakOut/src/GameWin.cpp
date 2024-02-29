#include "GameWin.h"

GameWin::GameWin(void)
{
}

GameWin::~GameWin(void)
{
}

bool GameWin::Initialize()
{
	// Cargamos la introducción
	if(!Sprite::LoadIni("data/GameWin.spr"))
		return false;

	/* La introducción comienza con el estado
	   que incrementará el alpha*/
	_state = WIN_STATE_FADEIN;
	_currentColor = D3DCOLOR_ARGB(0, 0xFF, 0xFF, 0xFF);
	_accum = 0.0f;
	
	return true;
}

void GameWin::Update(float dt)
{
	Sprite::Update(dt);

	_accum += dt;

	if(KeyDown(DIK_ESCAPE) || KeyDown(DIK_RETURN))
		_state = WIN_STATE_FADEOUT;

	switch(_state)
	{
	case WIN_STATE_FADEIN:
		if(_accum > INTERVAL_TIME_X)
		{
			_currentColor += D3DCOLOR_ARGB(0x1, 0, 0, 0);
			
			if(_currentColor >= D3DCOLOR_ARGB(0xFF, 0xFF, 0xFF, 0xFF))
			{
				_currentColor = D3DCOLOR_ARGB(0xFF, 0xFF, 0xFF, 0xFF);
				_state = WIN_STATE_WAIT;
			}

			_accum -= INTERVAL_TIME_X;
		}
		break;

	case WIN_STATE_WAIT:
		if(_accum > WAIT_TIME)
		{
			_state = WIN_STATE_FADEOUT;
			_accum = WAIT_TIME;
		}
		break;

	case WIN_STATE_FADEOUT:
		if(_accum > INTERVAL_TIME_X)
		{
			_currentColor -= D3DCOLOR_ARGB(0x1, 0, 0, 0);

			if(_currentColor <= D3DCOLOR_ARGB(0, 0xFF, 0xFF, 0xFF))
			{
				_currentColor = D3DCOLOR_ARGB(0, 0xFF, 0xFF, 0xFF);
				_state = WIN_STATE_NONE;
			}

			_accum -= INTERVAL_TIME_X; 
		}
		break;
	}
}

void GameWin::Draw()
{
	g_renderer.EnableModulate();
	g_renderer.SetModulationColor(_currentColor);
	Sprite::Draw();
	g_renderer.DisableModulate();
}
