#pragma once

#include <sstream>
#include "zakengine/zak.h"

#include "Intro.h"
#include "Title.h"
#include "Menu.h"
#include "Loading.h"
#include "InGame.h"

using namespace zak;

#define STATE_MENU		1
#define STATE_INGAME	2
#define STATE_LOADING	3
#define STATE_INTRO		4
#define STATE_TITLE		5

class TestGame :
	public Game
{
public:

	void OnFrame();
	bool OnShutdown();
	bool OnInit();
	void OnDraw();

	TestGame(void);
	~TestGame(void);

private:
	int _state;
	Intro *_intro;
	Title *_title;
	Menu *_menu;
	InGame *_inGame;
	Loading *_loading;

  void InputDebug();
};
