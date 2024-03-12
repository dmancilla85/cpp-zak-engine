#pragma once

#include "ghost.h"

#define CYAN_GHOST_SPEED	0.07f

class CyanGhost : public Ghost {
public:
	bool Initialize();

	CyanGhost():Ghost(){}
	~CyanGhost(){}

private:


};