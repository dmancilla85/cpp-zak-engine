#include "GameOver.h"

GameOver::GameOver(void)
{
}

GameOver::~GameOver(void)
{
}

bool GameOver::Initialize()
{
	// Cargamos la introducción
	if(!Sprite::LoadIni("data/GameOver.spr"))
		return false;

	/* La introducción comienza con el estado
	   que incrementará el alpha*/
	_state = LOSE_STATE_FADEIN;
	_currentColor = D3DCOLOR_ARGB(0, 0xFF, 0xFF, 0xFF);
	_accum = 0.0f;
	
	return true;
}

void GameOver::Update(float dt)
{
	Sprite::Update(dt);

	_accum += dt;

	if(KeyDown(DIK_ESCAPE) || KeyDown(DIK_RETURN))
		_state = LOSE_STATE_FADEOUT;

	switch(_state)
	{
	case LOSE_STATE_FADEIN:
		if(_accum > INTERVAL_TIME_X)
		{
			_currentColor += D3DCOLOR_ARGB(0x1, 0, 0, 0);
			
			if(_currentColor >= D3DCOLOR_ARGB(0xFF, 0xFF, 0xFF, 0xFF))
			{
				_currentColor = D3DCOLOR_ARGB(0xFF, 0xFF, 0xFF, 0xFF);
				_state = LOSE_STATE_WAIT;
			}

			_accum -= INTERVAL_TIME_X;
		}
		break;

	case LOSE_STATE_WAIT:
		if(_accum > WAIT_TIME)
		{
			_state = LOSE_STATE_FADEOUT;
			_accum = WAIT_TIME;
		}
		break;

	case LOSE_STATE_FADEOUT:
		if(_accum > INTERVAL_TIME_X)
		{
			_currentColor -= D3DCOLOR_ARGB(0x1, 0, 0, 0);

			if(_currentColor <= D3DCOLOR_ARGB(0, 0xFF, 0xFF, 0xFF))
			{
				_currentColor = D3DCOLOR_ARGB(0, 0xFF, 0xFF, 0xFF);
				_state = LOSE_STATE_NONE;
			}

			_accum -= INTERVAL_TIME_X; 
		}
		break;
	}
}

void GameOver::Draw()
{
	g_renderer.EnableModulate();
	g_renderer.SetModulationColor(_currentColor);
	Sprite::Draw();
	g_renderer.DisableModulate();
}
