#pragma once

#include "zakengine/zak.h"
#include "Ball.h"
#include "Pad.h"
#include "Brick.h"
#include "GameOver.h"
#include "GameWin.h"
#include "Loading.h"

// Estados del juego
#define GAME_STATE_NONE		0
#define GAME_STATE_EXIT		1
#define GAME_STATE_LOADING	2
#define GAME_STATE_LOSE		3
#define GAME_STATE_WIN		4

// Constantes para los ladrillos
#define BRICKS_PER_SIDE		10 // Bloques x Lado
#define BRICKS_FILES		6 // Filas de ladrillos
#define START_POS_X 		-260
#define START_POS_Y 		280
#define SPACE_BETWEEN_X		1
#define SPACE_BETWEEN_Y		1

// Vidas disponibles
#define VIDAS				5
// Niveles disponibles
#define NIVELES				10

using namespace zak;

class InGame
{
public:

	// Manipulación de estados
	bool Initialize();
	bool Shutdown();
	void SetState(int state) { _state = state;}
	int GetState() {return _state;}
	void Update(float dt);
	void Draw();
  void Reset();

	InGame(void);
	~InGame(void);
	
private:
	int _state;
	int _nivel; // Indicador de nivel
	int _puntaje; // Acumulador de puntaje
	float _ladrillosRotos;
	int _totalLadrillos;
  
  Ball _ball;
	Pad _pad;
	Brick _bricks[BRICKS_PER_SIDE * BRICKS_FILES];
  Loading _loading; 
	GameOver _loseGame;  
	GameWin _winGame; 

	bool CheckCollision(Entity2D &entity1, Entity2D &entity2);
	bool BuildWall(unsigned short _bricksActivos[BRICKS_FILES][BRICKS_PER_SIDE]);
	bool BuildWall(string nivel);
	
};
