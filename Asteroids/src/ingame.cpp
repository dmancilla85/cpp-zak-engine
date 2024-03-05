#include "ingame.h"

InGame::InGame() {
	m_pShip = NULL;
}

InGame::~InGame() {
	// Destruimos los objetos
	if (m_pShip)
		delete m_pShip;
}

bool InGame::Initialize(int level) {
	
  CheckCollision::Clear();
  AsteroidManager::Clear();

  m_pShip = new Ship;

  m_state = GAME_STATE_NONE;

  if(!m_pShip->Initialize())
    return false;

  if(!AsteroidManager::Initialize(level))
    return false;

	return true;
}

bool InGame::Shutdown() {
	CheckCollision::Clear();
  AsteroidManager::Clear();

  return true;
}

void InGame::Update(float dt) {
  m_pShip->Update(dt);
  AsteroidManager::Update(dt);

  if(KeyDown(DIK_ESCAPE))
    m_state = GAME_STATE_EXIT;

  if(m_pShip->GetLives() <= 0) {
    m_state = GAME_STATE_EXIT;
    } 

  if(AsteroidManager::GetCount <= 0) {
    m_state = GAME_STATE_NEXT_LEVEL;
    }

  CheckCollision::Check();
}

void InGame::Draw() {
  AsteroidManager::Draw();
  m_pShip->Draw();

  wstringstream ss;

  ss << "Asteroids: " << AsteroidManager::GetCount();
  g_renderer.SetFontColor(0xFFFF0000);
  g_renderer.DrawString(ss.str(), 10, 10, 780, 580, ZAK_TEXT_RIGHT);
}

