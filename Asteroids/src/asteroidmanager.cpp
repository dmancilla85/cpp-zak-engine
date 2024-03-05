#include "asteroidmanager.h"

Asteroid*	AsteroidManager::m_pAsteroids = NULL;
int			AsteroidManager::m_asteroidCount = 0;

void AsteroidManager::Clear() {
	if (m_pAsteroids)
		delete [] m_pAsteroids;

	m_pAsteroids = NULL;

	m_asteroidCount = 0;
}

bool AsteroidManager::Initialize(int asteroidCount) {
	if (m_pAsteroids)
		delete [] m_pAsteroids;

	m_asteroidCount = asteroidCount;

	m_pAsteroids = new Asteroid[m_asteroidCount];

	if (!m_pAsteroids) {
		m_asteroidCount = 0;
		return false;
	}

	for (int i=0; i < m_asteroidCount; i++) {
		if (!m_pAsteroids[i].Initialize())
			return false;

		m_pAsteroids[i].SetVisible(true);
		m_pAsteroids[i].SetCheckCollision(true);
	}

	return true;
}

void AsteroidManager::Update(float dt) {
	for (int i=0; i < m_asteroidCount; i++) {
		m_pAsteroids[i].Update(dt);
	}
}
void AsteroidManager::Draw() {
	for (int i=0; i < m_asteroidCount; i++) {
		m_pAsteroids[i].Draw();
	}
}
