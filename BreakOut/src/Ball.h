#pragma once

#include "zakengine/zak.h"
#include <cmath>

using namespace zak;

class Ball : public Sprite
{
public:
	Ball(void);
	~Ball(void);
	bool Initialize();
	void OnCollide(Entity2D *entity);
	void Update(float dt);

	void SetSticky(bool isSticky) {_isSticky = isSticky;}
	bool GetSticky() {return _isSticky;}
	int GetVidas() {return _vidas;}
	void SetVX(float vx) {_vx = vx;}
	void SetVY(float vy) {_vy = vy;}
	void SetVidas(int vidas) {_vidas = vidas;}

private:
	void BoundX(){_vx *= -1;}
	void BoundY(){_vy *= -1;}

	float _vx;
	float _vy;
	bool _isSticky;
	int _vidas;

};
