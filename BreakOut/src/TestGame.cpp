#include "TestGame.h"

TestGame::TestGame(void)
{
}

TestGame::~TestGame(void)
{
}

bool TestGame::OnInit()
{
	_clearScreen = true;
	
	// Color de borrado en negro
	g_renderer.SetClearColor(0xFF000000);

	// Inicializamos la introducción
	if(!_intro.Initialize())
		return false;

	// Inicializamos pantalla de título
	if(!_title.Initialize())
		return false;

	// Inicializamos el menú
	if(!_menu.Initialize())
		return false;

	// Inicializamos pantalla de carga del juego
	if(!_loading.LoadIni("data/loading.spr"))
		return false;

	// Inicializamos el estado del juego
	_state = STATE_INTRO;

	return true;
}

void TestGame::OnFrame() 
{

	// Verificamos los estados
	switch(_state)
	{
		// Introducción
	case STATE_INTRO:
		// Actualizamos la introducción
		_intro.Update((float) _fpsMeter.GetDT());

		// Si terminó de correr por algú motivo
		// pasamos al estado menú
		if(_intro.GetState() == INTRO_STATE_NONE)
			_state = STATE_TITLE;
		break;

	// Título
	case STATE_TITLE:
		// Actualizamos la introducción
		_title.Update((float) _fpsMeter.GetDT());

		// Si terminó de correr por algú motivo
		// pasamos al estado menú
		if(_title.GetState() == TITLE_STATE_NONE)
			_state = STATE_MENU;
		break;

		// Menú
	case STATE_MENU:
		// Actualizamos el menú
		_menu.Update((float) _fpsMeter.GetDT());

		// Si el estado es de salida
		// salimos del juego
		if(_menu.GetState() == MENU_STATE_EXIT)
		{
			PostQuitMessage(0);
		}
		// Si el estado es de jugar
		// pasamos al estado de carga del juego
		else
		{
			if(_menu.GetState() == MENU_STATE_PLAY)
				_state = STATE_LOADING;
		}
		break;
	
	case STATE_LOADING:
		// Actualizamos la pantalla de carga
		_loading.Update((float)_fpsMeter.GetDT());

		/* Comenzamos la carga del juego
		   del juego, sí todo sale bien pasamos al estado
		   InGame y sino salimos del juego */
		if(_inGame.Initialize())
			_state = STATE_INGAME;
		else
			PostQuitMessage(0);

		break;

		// En el juego
	case STATE_INGAME:
		// Actualizamos el juego
		_inGame.Update((float) _fpsMeter.GetDT());

		// Si el estado del juego es salir
		// volvemos al menú
		if(_inGame.GetState() == GAME_STATE_EXIT)
		{		
			if(!_inGame.Shutdown())
				PostQuitMessage(0);

			_state = STATE_MENU;
			_menu.setState(MENU_STATE_NONE);
			_inGame.SetState(GAME_STATE_NONE);
		}
		break;
	}
}

void TestGame::OnDraw()
{
	switch(_state)
	{
	case STATE_INTRO:
		_intro.Draw();
		break;

	case STATE_TITLE:
		_title.Draw();
		break;

	case STATE_MENU:
		_menu.Draw();
		break;

	case STATE_LOADING:
		_loading.Draw();

	case STATE_INGAME:
		_inGame.Draw();
		break;

	}
}

bool TestGame::OnShutdown()
{
	return true;
}