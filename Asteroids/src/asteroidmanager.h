#pragma once

#include "zakengine/zak.h"
#include "asteroid.h"

using namespace zak;

class AsteroidManager {
public:

	static void Clear();
	static bool Initialize(int asteroidCount);
	static void Update(float dt);
	static void Draw();
	static int GetCount() { return m_pAsteroids[0].GetCount(); }

private:

	static Asteroid *m_pAsteroids;
	static int m_asteroidCount;
};