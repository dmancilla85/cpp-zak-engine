#pragma once

#include <sstream>
#include "zakengine/zak.h"

#include "intro.h"
#include "menu.h"
#include "InGame.h"

using namespace zak;

#define STATE_MENU		1
#define STATE_INGAME	2
#define STATE_LOADING	3
#define STATE_INTRO		4

class TestGame : public Game {
public:

	void OnFrame();
	bool OnShutdown();
	bool OnInit();
	void OnDraw();

	TestGame();
	~TestGame();

private:
	int		m_state;
  int m_level;

	Intro	m_intro;
	Menu	m_menu;
	Sprite	m_loading;
	InGame	m_inGame;

  void ShowInputDebug();
};