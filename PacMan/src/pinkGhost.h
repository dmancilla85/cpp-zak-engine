#pragma once

#include "ghost.h"

#define PINK_GHOST_SPEED	0.13f

class PinkGhost : public Ghost {
public:
	bool Initialize();

	PinkGhost():Ghost(){}
	~PinkGhost(){}

private:


};