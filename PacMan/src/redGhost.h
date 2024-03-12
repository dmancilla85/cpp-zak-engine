#pragma once

#include "ghost.h"
#define RED_GHOST_SPEED 0.12f

class RedGhost : public Ghost {
public:
	bool Initialize();

	RedGhost():Ghost(){}
	~RedGhost(){}

private:


};