#include "ship.h"


Ship::Ship() {
  m_pSprExplosion = NULL;
  m_pAniExplosion = NULL;
  *m_pShots = NULL;
  }


Ship::~Ship(){
  if(m_pAniExplosion)
    delete m_pAniExplosion;

  if(m_pSprExplosion)
    delete m_pSprExplosion;

  if(m_pShots)
    delete [] *m_pShots;
  }

void Ship::SwapLast(int which){
  Shot *shot;
  if (which >= 0 && which < m_lastShot)  {
    shot = m_pShots[which];
    m_lastShot--;
    m_pShots[which] = m_pShots[m_lastShot];
    m_pShots[m_lastShot] = shot;
    }
  }

  bool Ship::Initialize() {
    m_pSprExplosion = new Sprite;
    m_pAniExplosion = new Animation;

    if(!LoadIni("data/graphics/uridium.spr"))
      return false;

    if(!m_pSprExplosion->LoadIni("data/graphics/explosion.spr"))
      return false;

    if(!m_pAniExplosion->Load("data/graphics/explosionNave.ani"))
      return false;

    Reset();

    SetName("ship");
    SetCheckCollision(false);
    SetCollisionRadius(15);

    m_lives = 5;
    m_state = SHIP_STATE_INVISIBLE;
    m_invisibleTime = 0;
    m_currentColor = SHIP_COLOR_INVISIBLE;

    for(int i = 0; i < SHOTS_COUNT; i++){
      m_pShots[i] = new Shot;

      if(!m_pShots[i])
        return false;

      if(!m_pShots[i]->Initialize())
        return false;
      }

    m_lastShot = 0;

    if(!CheckCollision::Register(this, 1))
      return false;

    return true;
    }

  void Ship::Reset(){
    this->SetPos(0, 0);
    m_accumTime = 0;
    m_angle = 0;

    SetFrame(3);
    SetAngleZ(m_angle);
    SetVisible(true);

    m_vx = 0;
    m_vy = 0;
    }

  void Ship::Update(float dt){
    static float x;
    static float y;
    static int w = (int) g_renderer.GetViewPortWidth() / 2;
    static int h = (int) g_renderer.GetViewPortHeight() / 2;

    switch(m_state) {
    case SHIP_STATE_EXPLODING:
      m_pSprExplosion->Update(dt);

      if(!m_pSprExplosion->IsAnimationRunning()) {
        Reset();
        m_state = SHIP_STATE_INVISIBLE;
        m_lives--;
        m_pSprExplosion->SetVisible(false);
        }
      break;

    case SHIP_STATE_INVISIBLE:
      m_invisibleTime += dt;

      if(m_invisibleTime >= INVISIBLE_TIME) {
        m_state = SHIP_STATE_NONE;
        m_invisibleTime = 0.0f;
        this->SetCheckCollision(true);
        }

    default:
      Sprite::Update(dt);

      // time for animation
      m_accumTime += dt;

      // change animation frames so ship seem to be spinning
      if(m_accumTime > 1.0f / SHIP_ANIM_FPS * 1000.0f) {

        if(KeyPressed(DIK_LEFT)) {
          Sprite::_iActualFrame--;
          } 
        else if(KeyPressed(DIK_RIGHT)) {
          Sprite::_iActualFrame++;
          } 
        else {
          // no key pressed then return
          // to frame 3 (top view)
          if (Sprite::_iActualFrame > 3)
            Sprite::_iActualFrame--;
          else if(Sprite::_iActualFrame < 3)
            Sprite::_iActualFrame++;
          }

        // check to no exceed frame limits
        if(_iActualFrame < 0)
          _iActualFrame = 11;
        else 
          if(_iActualFrame > 11)
            _iActualFrame = 0;

        SetFrame(Sprite::_iActualFrame);
        m_accumTime -= 1.0f / SHIP_ANIM_FPS * 1000.0f;
        }

      // keys to rotate
      if(KeyPressed(DIK_LEFT)) {
        m_angle += SHIP_ROT_SPEED * dt;
        SetAngleZ(m_angle);
        } 
      else if(KeyPressed(DIK_RIGHT)) {
        m_angle -= SHIP_ROT_SPEED * dt;
        SetAngleZ(m_angle);
        }

      // key to accelerate
      if(KeyPressed(DIK_UP) && abs(m_vx) <= SHIP_MAXSPEED && abs(m_vy) <= SHIP_MAXSPEED) {
        m_vx += SHIP_ACCEL * (float)(cosf((float)(DEGREE_TO_RAD((double) m_angle))) * dt); 
        m_vy += SHIP_ACCEL * (float)(sinf((float)(DEGREE_TO_RAD((double) m_angle))) * dt); 
        }

      // check max speed
      if(abs(m_vx) > SHIP_MAXSPEED){
        m_vx = SHIP_MAXSPEED * (m_vx / abs(m_vx));
        }

      if(abs(m_vy) > SHIP_MAXSPEED){
        m_vy = SHIP_MAXSPEED * (m_vy / abs(m_vy));
        }

      // get actual position
      x = GetPosX();
      y = GetPosY();

      // move element
      x += m_vx * dt;
      y += m_vy * dt;

      // check to no exceed screen borders
      if(x > w)
        x = (float) (-w);
      else if( x < -w)
        x = (float) w;

      if(y > h)
        y = (float) (-h);
      else if( y < -h)
        y = (float) h;

      // verify if the space key is pressed
      if(KeyDown(DIK_SPACE) && m_lastShot < SHOTS_COUNT - 1){
        m_pShots[m_lastShot]->Shoot(GetPosX(), GetPosY(), m_angle);
        m_lastShot++;
        }

      // set new position
      SetPos(x, y);
      break;
      }

    // update active shots
    int i = 0;
    while(i < m_lastShot) {

      if(!m_pShots[i]->GetVisible()) {
        SwapLast(i);
        }
      else {
        m_pShots[i]->Update(dt);
        }
      i++;
      }
    }

  void Ship::Draw() {

    for(int i = 0; i < SHOTS_COUNT; i++) {
      m_pShots[i]->Draw();
      }

    switch(m_state){
    case SHIP_STATE_EXPLODING:
      m_pSprExplosion->Draw();
      break;

    case SHIP_STATE_INVISIBLE:
      g_renderer.EnableModulate();
      g_renderer.SetModulationColor(m_currentColor);
      Sprite::Draw();
      g_renderer.DisableModulate();
      break;

    default:
      Sprite::Draw();
      break;
      }
    }

  void Ship::OnCollide(Entity2D *entity){
    if(strcmp(entity->GetName(), "asteroid") == 0) {
      this->SetCheckCollision(false);
      m_pSprExplosion->SetVisible(true);
      m_pSprExplosion->SetPos(GetPosX(), GetPosY());
      m_pSprExplosion->SetAnimation(m_pAniExplosion);

      this->SetVisible(false);
      m_state = SHIP_STATE_EXPLODING;
      }
    }
