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
  if (!m_intro.Initialize())
    return false;

  // Inicializamos el menú
  if (!m_menu.Initialize())
    return false;

  // Inicializamos la pantalla de carga
  if (!m_loading.LoadIni("data/graphics/loading.spr")) 
    return false;

  // Inicializamos el estado del juego
  m_state = STATE_INTRO;

  m_level = 1;

  return true;
  }

void TestGame::OnFrame() {

  // Verificamos los estados
  switch(m_state) {
    // Estado = Introducción
    case STATE_INTRO:
      // Actualizamos la introducción
      m_intro.Update((float)_fpsMeter.GetDT());

      // Si terminó de correr por algún motivo
      // pasamos al estado menu
      if (m_intro.GetState() == INTRO_STATE_NONE) {
        m_state = STATE_MENU;
        }

      break;

      // Estado = Menu
    case STATE_MENU:
      // Actualizamos el menu
      m_menu.Update((float)_fpsMeter.GetDT());

      // Si el estado es de salida
      // salimos del juego
      if (m_menu.GetState() == MENU_STATE_EXIT) {
        PostQuitMessage(0);

        // Si el estado es de jugar
        // pasamos al estado de carga del juego
        } else if (m_menu.GetState() == MENU_STATE_PLAY) {
          m_state = STATE_LOADING;
        }
      break;

      // Estado = Cargando
    case STATE_LOADING:
      // Actualizamos la carga
      m_loading.Update((float)_fpsMeter.GetDT());

      // Comenzamos la carga del juego
      // si todo sale bien pasamos al estado
      // In-Game y sino salimos del juego
      if (m_inGame.Initialize(m_level))
        m_state = STATE_INGAME;
      else
        PostQuitMessage(0);

      break;

      // Estado = In-Game
    case STATE_INGAME:
      // Actualizamos el juego
      m_inGame.Update((float)_fpsMeter.GetDT());

      // Si el estado del juego es salir
      // volvemos al menu
      if (m_inGame.GetState() == GAME_STATE_EXIT) {
        // Si algo salió mal al apagar
        // el juego, salimos
        if (!m_inGame.Shutdown()) {
          PostQuitMessage(0);
          }
        // Cambiamos el estado a menu
        m_state = STATE_MENU;
        m_level = 1;
        // Inicializamos el estado del menu
        m_menu.SetState(MENU_STATE_NONE);
        } 
      else if(m_inGame.GetState() == GAME_STATE_NEXT_LEVEL) {
        if (!m_inGame.Shutdown()) {
          PostQuitMessage(0);
          }

        m_level++;
        m_state = STATE_LOADING;
        }
      break;
    }
  }

void TestGame::OnDraw() {

  // Dibujamos dependiendo del estado del juego
  switch(m_state){
    case STATE_INTRO:
      m_intro.Draw();
      break;
    case STATE_MENU:
      m_menu.Draw();
      break;
    case STATE_LOADING:
      m_loading.Draw();
      break;
    case STATE_INGAME:
      m_inGame.Draw();
      break;
    }

  if(_DEBUG)
    ShowInputDebug();
  }

bool TestGame::OnShutdown() {
  return true;
  }