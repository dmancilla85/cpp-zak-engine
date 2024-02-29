#pragma once

#include "zakengine/zak.h"

using namespace zak;

class Brick : public Sprite
{
public:
	Brick(void);
	~Brick(void);

	bool Initialize();
	void OnCollide(Entity2D *entity);
};
