#include "TestGame.h"

TestGame::TestGame(void)
  {
  _menu = NULL;
  _intro = NULL;
  _title = NULL;
  _inGame = NULL;
  _loading = NULL;
  }

TestGame::~TestGame(void)
  {
  if(_menu)
    delete _menu;

  if(_intro)
    delete _intro;

  if(_title)
    delete _title;

  if(_inGame)
    delete _inGame;

  if(_loading)
    delete _loading;
  }

void TestGame::InputDebug(){
  wstringstream ss;

  ss << ZAK_ENGINE_NAME << endl << "FPS: " << _fpsMeter.GetFps() << endl;
  ss << "JoyX: " << JoystickPosf(0, ZAK_INPUT_POS_X) << " - JoyY: " << JoystickPosf(0, ZAK_INPUT_POS_Y) << endl;

  ss << "MouseAbsPosX: " << MouseAbsPosf(ZAK_INPUT_MOUSE_POS_X) << 
    " - MouseAbsPosY: " << MouseAbsPosf(ZAK_INPUT_MOUSE_POS_Y) << endl;

  ss << "MouseWorldPosX: " << MouseWorldPosf(ZAK_INPUT_MOUSE_POS_X) << 
    " - MouseWorldPosY: " << MouseWorldPosf(ZAK_INPUT_MOUSE_POS_Y) << endl;

  g_renderer.DrawString(ss.str(), 10, 10, 800-60, 600-60, ZAK_TEXT_LEFT);
  }

bool TestGame::OnInit()
  {
  _menu = new Menu;
  _intro = new Intro;
  _title = new Title;
  _inGame = new InGame;
  _loading = new Loading;

  _clearScreen = true;

  // Color de borrado en negro
  g_renderer.SetClearColor(0xFF000000);

  // Inicializamos la introducción
  if(!_intro->Initialize())
    return false;

  // Inicializamos pantalla de título
  if(!_title->Initialize())
    return false;

  // Inicializamos el menú
  if(!_menu->Initialize())
    return false;

  // Inicializamos pantalla de carga del juego
  if(!_loading->Initialize())
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
      _intro->Update((float) _fpsMeter.GetDT());

      // Si terminó de correr por algú motivo
      // pasamos al estado menú
      if(_intro->GetState() == INTRO_STATE_NONE)
        _state = STATE_TITLE;
      break;

      // Título
    case STATE_TITLE:
      // Actualizamos la introducción
      _title->Update((float) _fpsMeter.GetDT());

      // Si terminó de correr por algú motivo
      // pasamos al estado menú
      if(_title->GetState() == TITLE_STATE_NONE)
        _state = STATE_MENU;
      break;

      // Menú
    case STATE_MENU:
      // Actualizamos el menú
      _menu->Update((float) _fpsMeter.GetDT());

      // Si el estado es de salida
      // salimos del juego
      if(_menu->GetState() == MENU_STATE_EXIT)
        {
        PostQuitMessage(0);
        }
      // Si el estado es de jugar
      // pasamos al estado de carga del juego
      else
        {
        if(_menu->GetState() == MENU_STATE_PLAY)
          _state = STATE_LOADING;
        }
      break;

    case STATE_LOADING:
      // Actualizamos la pantalla de carga
      _loading->Update((float)_fpsMeter.GetDT());

      if(_loading->GetState() == LOADING_STATE_NONE){
        if(_inGame->Initialize())
          _state = STATE_INGAME;
        else
          PostQuitMessage(0);
        }

      break;

      // En el juego
    case STATE_INGAME:
      // Actualizamos el juego
      _inGame->Update((float) _fpsMeter.GetDT());

      // Si el estado del juego es salir
      // volvemos al menú
      if(_inGame->GetState() == GAME_STATE_EXIT)
        {		
        if(!_inGame->Shutdown())
          PostQuitMessage(0);

        _state = STATE_MENU;
        _menu->setState(MENU_STATE_NONE);
        _inGame->SetState(GAME_STATE_NONE);
        }
      break;
    }
  }

void TestGame::OnDraw()
  {

  switch(_state)
    {
    case STATE_INTRO:
      _intro->Draw();
      break;

    case STATE_TITLE:
      _title->Draw();
      break;

    case STATE_MENU:
      _menu->Draw();
      break;

    case STATE_LOADING:
      _loading->Draw();

    case STATE_INGAME:
      _inGame->Draw();
      break;

    }

  if(_DEBUG) {
    InputDebug();
    }
  }

bool TestGame::OnShutdown()
  {
  return true;
  }