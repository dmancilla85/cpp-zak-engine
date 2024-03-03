#include "game.h"

TestGame::TestGame() {

  }

TestGame::~TestGame() {

  }

void TestGame::InputDebug(){
  wstringstream ss;

  ss << ZAK_ENGINE_NAME << endl << "FPS: " << _fpsMeter.GetFps() << endl;
  ss << "JoyX: " << JoystickPosf(0, ZAK_INPUT_POS_X) << "JoyY: " << JoystickPosf(0, ZAK_INPUT_POS_Y) << endl;

  ss << "MouseAbsPosX: " << MouseAbsPosf(ZAK_INPUT_MOUSE_POS_X) << 
    " - MouseAbsPosY: " << MouseAbsPosf(ZAK_INPUT_MOUSE_POS_Y) << endl;

  ss << "MouseWorldPosX: " << MouseWorldPosf(ZAK_INPUT_MOUSE_POS_X) << 
    " - MouseWorldPosY: " << MouseWorldPosf(ZAK_INPUT_MOUSE_POS_Y) << endl;

  g_renderer.DrawString(ss.str(), 10, 10, 800-60, 600-60, ZAK_TEXT_LEFT);
  }


void TestGame::OnFrame() {
  if(KeyDown(DIK_ESCAPE))
    PostQuitMessage(0);
  }

bool TestGame::OnShutdown() {
  return true;
  }

bool TestGame::OnInit()  {
  return true;
  }

void TestGame::OnDraw() {
  
  if(_DEBUG)
    InputDebug();
 }