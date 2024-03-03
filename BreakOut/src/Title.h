#pragma once

#include "zakengine/zak.h"

using namespace zak;

#define TITLE_STATE_NONE		0
#define TITLE_STATE_FADEIN		1
#define TITLE_STATE_WAIT		2
#define TITLE_STATE_FADEOUT		3

#define TITLE_WAIT_TIME				4000.0f
#define TITLE_INTERVAL_TIME			5.0f

class Title : public Sprite
{
public:
	Title(void);
	~Title(void);

  int	 GetState() { return _state; }
	void SetState(int state) { _state = state; }
	bool Initialize();
  void Draw();
  void Update(float dt);

private:
  int		_state;
	DWORD	_currentColor;
	float	_accum;
};
