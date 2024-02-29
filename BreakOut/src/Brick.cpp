#include "Brick.h"

Brick::Brick(void)
{
}

Brick::~Brick(void)
{
}

bool Brick::Initialize()
{
	//SetShape(ZAK_SHAPE_QUAD);
	if(!LoadIni("./data/brick.spr"))
		return false;
	SetDim(50, 20);
	SetCollisionType(Entity2D::eCollisionBBox);
	SetCollisionSize(50, 20);
	SetCheckCollision(true);
	return true;
}

void Brick::OnCollide(zak::Entity2D *entity)
{
	SetVisible(false);
	SetCheckCollision(false);
}