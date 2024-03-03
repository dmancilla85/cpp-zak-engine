#pragma once

#include "zakengine/zak.h"

using namespace zak;

#define HIT_DAMAGE 100

class Brick : public Sprite
{
public:
	Brick(void);
	~Brick(void);

	bool Initialize();
	void OnCollide(Entity2D *entity);
  int GetDamage();

private:
  int _damage;
  bool _showBroken;
};
