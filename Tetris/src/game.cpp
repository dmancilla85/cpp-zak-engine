#include "game.h"

TestGame::TestGame() {

  }

TestGame::~TestGame() { 

  }

void TestGame::ShowInputDebug(){
  wstringstream ss;

  ss << ZAK_ENGINE_NAME << endl << "FPS: " << _fpsMeter.GetFps() << endl;
  ss << "JoyX: " << JoystickPosf(0, ZAK_INPUT_POS_X) << "JoyY: " << JoystickPosf(0, ZAK_INPUT_POS_Y) << endl;

  ss << "MouseAbsPosX: " << MouseAbsPosf(ZAK_INPUT_MOUSE_POS_X) << 
    " - MouseAbsPosY: " << MouseAbsPosf(ZAK_INPUT_MOUSE_POS_Y) << endl;

  ss << "MouseWorldPosX: " << MouseWorldPosf(ZAK_INPUT_MOUSE_POS_X) << 
    " - MouseWorldPosY: " << MouseWorldPosf(ZAK_INPUT_MOUSE_POS_Y) << endl;

  g_renderer.DrawString(ss.str(), 10, 10, 800-60, 600-60, ZAK_TEXT_LEFT);
  }

bool TestGame::OnInit() {
  // Activamos el borrado de pantalla
  _clearScreen = true;

  // Color de borrado en negro
  g_renderer.SetClearColor(0xFF000000);

  // Inicializamos la introducción
  if (!_intro.Initialize())
    return false;

  // Inicializamos el menú
  if (!_menu.Initialize())
    return false;

  // Inicializamos la pantalla de carga
  if (!_loading.LoadIni("data/graphics/loading.spr")) 
    return false;

  // Inicializamos el estado del juego
  _state = STATE_INTRO;

  return true;
  }

void TestGame::OnFrame() {

  // Verificamos los estados
  switch(_state) {
    // Estado = Introducción
    case STATE_INTRO:
      // Actualizamos la introducción
      _intro.Update((float)_fpsMeter.GetDT());

      // Si terminó de correr por algún motivo
      // pasamos al estado menu
      if (_intro.GetState() == INTRO_STATE_NONE) {
        _state = STATE_MENU;
        }

      break;

      // Estado = Menu
    case STATE_MENU:
      // Actualizamos el menu
      _menu.Update((float)_fpsMeter.GetDT());

      // Si el estado es de salida
      // salimos del juego
      if (_menu.GetState() == MENU_STATE_EXIT) {
        PostQuitMessage(0);

        // Si el estado es de jugar
        // pasamos al estado de carga del juego
        } else if (_menu.GetState() == MENU_STATE_PLAY) {
          _state = STATE_LOADING;
        }
      break;

      // Estado = Cargando
    case STATE_LOADING:
      // Actualizamos la carga
      _loading.Update((float)_fpsMeter.GetDT());

      // Comenzamos la carga del juego
      // si todo sale bien pasamos al estado
      // In-Game y sino salimos del juego
      if (_inGame.Initialize(0))
        _state = STATE_INGAME;
      else
        PostQuitMessage(0);

      break;

      // Estado = In-Game
    case STATE_INGAME:
      // Actualizamos el juego
      _inGame.Update((float)_fpsMeter.GetDT());

      // Si el estado del juego es salir
      // volvemos al menu
      if (_inGame.GetState() == GAME_STATE_EXIT) {
        // Si algo salió mal al apagar
        // el juego, salimos
        if (!_inGame.Shutdown()) {
          PostQuitMessage(0);
          }
        // Cambiamos el estado a menu
        _state = STATE_MENU;

        // Inicializamos el estado del menu
        _menu.SetState(MENU_STATE_NONE);
        }
      break;
    }
  }

void TestGame::OnDraw() {

  // Dibujamos dependiendo del estado del juego
  switch(_state){
    case STATE_INTRO:
      _intro.Draw();
      break;
    case STATE_MENU:
      _menu.Draw();
      break;
    case STATE_LOADING:
      _loading.Draw();
      break;
    case STATE_INGAME:
      _inGame.Draw();
      break;
    }

  if(_DEBUG)
    ShowInputDebug();
  }

bool TestGame::OnShutdown() {
  return true;
  }