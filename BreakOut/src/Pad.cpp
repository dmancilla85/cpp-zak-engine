#include "Pad.h"

Pad::Pad(void)
{
	_currentAction = MOVE_NONE;
	_vx = 0.0f;
}

Pad::~Pad(void)
{
}

void Pad::OnCollide(Entity2D *entity)
{
	SetToPreviousPosition();
}

bool Pad::Initialize()
{
	if(!LoadIni("./data/pad.spr"))
		return false;
	
	//SetShape(ZAK_SHAPE_QUAD);
	//SetDim(100, 20);
	SetPos(0, -250);
	//SetColor(0xFFFF0000);
	SetCheckCollision(true);

	_vx = 0.0f;
	_currentAction = 0;

	return true;
}

void Pad::Update(float dt)
{
	float x = GetPosX();
	float w = (float) g_renderer.GetViewPortWidth() /2;
	float h = (float) g_renderer.GetViewPortHeight() /2;

	Sprite::Update(dt);

	// Verifico la posición actual
	if(_currentAction == MOVING)
	{
		x += _vx * dt;
	}

	// Verifico si estoy fuera de los margenes

	if(x > w - GetWidth()/2)
		x = w - GetWidth() / 2;

	if(x < -w + GetWidth() / 2)
		x = -w + GetWidth() / 2;

	SetPosX(x);
}

void Pad::SetInitialPos()
{
	SetPos(0, -250);
}