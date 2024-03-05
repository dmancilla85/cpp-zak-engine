#include "asteroid.h"

int Asteroid::m_count = 0;

Asteroid::Asteroid() {
  m_vx = 0.0f;
  m_vy = 0.0f;
  m_rotSpeed = 0.0f;
  m_rotAngle = 0.0f;
  m_pChild = NULL;
  m_count++;
  }

Asteroid::~Asteroid() {
  if(m_pChild)
    delete [] m_pChild;

  m_count = 0;
  }

bool Asteroid::Initialize(int type) {
  m_pSprExplosion = new Sprite;
  m_pAniExplosion = new Animation;

  if(!LoadIni("data/graphics/asteroid.spr")) {
    return false;
    }

  if(!m_pSprExplosion->LoadIni("data/graphics/explosion.spr")) {
    return false;
    }

  if(!m_pAniExplosion->Load("data/graphics/explosion.ani")) {
    return false;
    }

  SetPos(ASTEROID_START_POS_X, ASTEROID_START_POS_Y);

  SetPos(ASTEROID_START_POS_X, ASTEROID_START_POS_Y);
	
	m_angle = (float)(rand()%360);
	m_rotSpeed = ((rand()%(ASTEROID_MAX_ROTSPEED-ASTEROID_MIN_ROTSPEED))+ASTEROID_MIN_ROTSPEED)*0.01f;
	m_speed	  = ((rand()%(ASTEROID_MAX_SPEED-ASTEROID_MIN_SPEED))+ASTEROID_MIN_SPEED)*0.01f;

	m_vx = m_speed*cosf((float)(DegreeToRad(m_angle)));
	m_vy = m_speed*sinf((float)(DegreeToRad(m_angle)));


  SetAngleZ(m_rotAngle);

  // collision properties
  SetName("asteroid");
  SetCheckCollision(false);
  SetVisible(false);

  m_type = type;

  switch(m_type) {
    case 1:
      m_pChild = new Asteroid[2];
      m_pChild[0].Initialize(2);
      m_pChild[1].Initialize(2);
      SetScale(0.7f);
      m_pSprExplosion->SetScale(1.2f);
      break;

    case 2:
      SetScale(0.4f);
      m_pSprExplosion->SetScale(0.9f);
      break;

    default:
      m_pChild = new Asteroid[2];
      m_pChild[0].Initialize(1);
      m_pChild[1].Initialize(1);
      SetScale(1.0f);
      m_pSprExplosion->SetScale(1.5f);
      break;
    }

  SetCollisionRadius( ASTEROID_COLLISION_RADIUS * GetScale() );

  if(!CheckCollision::Register(this, 2))
      return false;

  return true;
  }

void Asteroid::Update(float dt){
  float x = GetPosX();
  float y = GetPosY();
  static int w = (int) g_renderer.GetViewPortWidth() / 2;
  static int h = (int) g_renderer.GetViewPortHeight() / 2;

  Sprite::Update(dt);

  x += m_vx * dt;
  y += m_vy * dt;

  if(abs(x) > w) {
    x = w * ( x / (- abs(x)));
    }

  if(abs(y) > h) {
    y = h * ( y / (- abs(y)));
    }

  m_rotAngle += m_rotSpeed * dt;
  SetAngleZ(m_rotAngle);

  SetPos(x,y);

  if(m_pChild) {
    m_pChild[0].Update(dt);
    m_pChild[1].Update(dt);
    }

  if(m_pSprExplosion->GetVisible()) {
    m_pSprExplosion->Update(dt);

    if(!m_pSprExplosion->IsAnimationRunning()) {
      m_pSprExplosion->SetVisible(false);
      m_count--;
      }
    }
  }

void Asteroid::Draw() {
  Sprite::Draw();

  if(m_pChild) {
    m_pChild[0].Draw();
    m_pChild[1].Draw();
    }

  m_pSprExplosion->Draw();

  }

void Asteroid::Explode() {
  this->SetCheckCollision(false);
  this->SetVisible(false);

  m_pSprExplosion->SetAnimation(m_pAniExplosion);
  m_pSprExplosion->SetVisible(true);
  m_pSprExplosion->SetPos(GetPosX(), GetPosY());

  if(m_pChild) {
    m_pChild[0].SetPos(GetPosX(), GetPosY());
    m_pChild[0].SetVisible(true);
    m_pChild[0].SetCheckCollision(true);

    m_pChild[1].SetPos(GetPosX(), GetPosY());
    m_pChild[1].SetVisible(true);
    m_pChild[1].SetCheckCollision(true);
    }
  }

void Asteroid::OnCollide(Entity2D *pEntity){
  if(strcmp(pEntity->GetName(), "shot") == 0) {
    Explode();
    }
  }