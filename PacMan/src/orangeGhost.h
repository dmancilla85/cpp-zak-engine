#pragma once

#include "ghost.h"

#define ORANGE_GHOST_SPEED	0.08f

class OrangeGhost : public Ghost {
public:
	bool Initialize();

	OrangeGhost():Ghost(){}
	~OrangeGhost(){}

private:


};