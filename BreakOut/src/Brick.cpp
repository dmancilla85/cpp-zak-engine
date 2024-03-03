#include "Brick.h"

Brick::Brick(void)
  {
  _damage = 0;
  }

Brick::~Brick(void)
  {
  }

bool Brick::Initialize()
  {
  //SetShape(ZAK_SHAPE_QUAD);

  bool okLoad = LoadIni("./data/brick.spr");

  if(!okLoad)
    return false;

  _damage = 0;

  SetDim(65, 26);
  SetCollisionType(Entity2D::eCollisionBBox);
  SetCollisionSize(65, 26);
  SetCheckCollision(true);
  return true;
  }

void Brick::OnCollide(zak::Entity2D *entity)
  {
  _damage += HIT_DAMAGE;
 
  if(_damage > 0 && !_showBroken){
    //LoadIni("./data/broken_brick.spr");
      _showBroken = true;
    }

  if(_damage >= 100){
    SetVisible(false);
    SetCheckCollision(false);
    }
  }

int Brick::GetDamage(){
  return _damage;
  }