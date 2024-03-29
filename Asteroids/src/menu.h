#pragma once

#include "zakengine/zak.h"

using namespace zak;

#define MENU_START_POS_X	0
#define MENU_START_POS_Y	0

#define MENU_OPTIONS_COUNT	2

#define MENU_STATE_NONE		0
#define MENU_STATE_PLAY		1
#define MENU_STATE_EXIT		2


class Menu { 
public:
	bool Initialize();

	int  GetState() { return _state; }
	void SetState(int state) { _state = state; }

	void Update(float dt);
	void Draw();

	Menu();
	~Menu();

private:
	int		_state;
	int		_optionSelected;
	Sprite	_option[MENU_OPTIONS_COUNT];
};