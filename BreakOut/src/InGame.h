#pragma once

#include "zakengine/zak.h"
#include "Ball.h"
#include "Pad.h"
#include "Brick.h"
#include "GameOver.h"
#include "GameWin.h"

// Estados del juego
#define GAME_STATE_NONE		0
#define GAME_STATE_EXIT		1
#define GAME_STATE_LOADING	2
#define GAME_STATE_LOSE		3
#define GAME_STATE_WIN		4

// Constantes para los ladrillos
#define BRICKS_PER_SIDE		10 // Bloques x Lado
#define BRICKS_FILES		6 // Filas de ladrillos
#define START_POS_X 		-250
#define START_POS_Y 		280
#define SPACE_BETWEEN_X		7
#define SPACE_BETWEEN_Y		5

// Vidas disponibles
#define VIDAS				6
// Niveles disponibles
#define NIVELES				2

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

	InGame(void);
	~InGame(void);
	
private:
	Ball _ball;
	Pad _pad;
	Brick _bricks[BRICKS_PER_SIDE * BRICKS_FILES];

	int _nivel; // Indicador de nivel
	int _puntaje; // Acumulador de puntaje

	bool CheckCollision(Entity2D &entity1, Entity2D &entity2);
	
	// Variables para el control de los ladrillos
	int _ladrillosRotos;
	int _totalLadrillos;

	bool regenerarMuro(unsigned short _bricksActivos[BRICKS_FILES][BRICKS_PER_SIDE]);
	bool regenerarMuro(string nivel);

	// Capitulo 5 - Descriptor de estado
	int _state;
	Sprite _loading; // Pantalla de carga
	GameOver _loseGame;  // Pantalla de juego terminado
	GameWin _winGame; // Pantalla de victoria
};
