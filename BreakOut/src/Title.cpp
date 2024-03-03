#include "Title.h"

Title::Title(void)
{
}

Title::~Title(void)
{
}

bool Title::Initialize()
{
	// Cargamos la introducción
	if(!Sprite::LoadIni("data/title.spr"))
		return false;

	/* La introducción comienza con el estado
	   que incrementará el alpha*/
	_state = TITLE_STATE_FADEIN;
	_currentColor = D3DCOLOR_ARGB(0, 0xFF, 0xFF, 0xFF);
	_accum = 0.0f;
	
	return true;
}

void Title::Update(float dt)
{
	Sprite::Update(dt);

	_accum += dt;

	if(KeyDown(DIK_ESCAPE) || KeyDown(DIK_RETURN))
		_state = TITLE_STATE_FADEOUT;

	switch(_state)
	{
	case TITLE_STATE_FADEIN:
		if(_accum > TITLE_INTERVAL_TIME)
		{
			_currentColor += D3DCOLOR_ARGB(0x1, 0, 0, 0);
			
			if(_currentColor >= D3DCOLOR_ARGB(0xFF, 0xFF, 0xFF, 0xFF))
			{
				_currentColor = D3DCOLOR_ARGB(0xFF, 0xFF, 0xFF, 0xFF);
				_state = TITLE_STATE_WAIT;
			}

			_accum -= TITLE_INTERVAL_TIME;
		}
		break;

	case TITLE_STATE_WAIT:
		if(_accum > TITLE_WAIT_TIME)
		{
			_state = TITLE_STATE_FADEOUT;
			_accum = TITLE_WAIT_TIME;
		}
		break;

	case TITLE_STATE_FADEOUT:
		if(_accum > TITLE_INTERVAL_TIME)
		{
			_currentColor -= D3DCOLOR_ARGB(0x1, 0, 0, 0);

			if(_currentColor <= D3DCOLOR_ARGB(0, 0xFF, 0xFF, 0xFF))
			{
				_currentColor = D3DCOLOR_ARGB(0, 0xFF, 0xFF, 0xFF);
				_state = TITLE_STATE_NONE;
			}

			_accum -= TITLE_INTERVAL_TIME; 
		}
		break;
	}
}

void Title::Draw()
{
	g_renderer.EnableModulate();
	g_renderer.SetModulationColor(_currentColor);
	Sprite::Draw();
	g_renderer.DisableModulate();
}
