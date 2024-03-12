#pragma once

#include "zakengine/zak.h"

using namespace zak;

#define TILE_EMPTY			0
#define TILE_POINT			1
#define TILE_PILL			2
#define TILE_DOOR1			40
#define TILE_DOOR2			41
#define TILE_DOOR3			42
#define TILE_DOOR4			43
#define TILE_DOOR5			44
#define TILE_DOOR6			45
#define TILE_DOOR7			46
#define TILE_DOOR8			47
#define TILE_RED_GHOST		49
#define TILE_PINK_GHOST		50
#define TILE_ORANGE_GHOST	51
#define TILE_CYAN_GHOST		52
#define TILE_EXIT			53
#define TILE_PACMAN_START	54

class Level  {
public:
	static bool Initialize(int level);
	static void Update(float dt) { _map.Update(dt); }
	static int GetOutCol() { return _outCol;}
	static int GetOutRow() { return _outRow;}
	static float GetOutPosX() { return _outPosX;}
	static float GetOutPosY() { return _outPosY;}

	static int	GetPointsRemaining() { return _points; }

	static void Draw() { _map.Draw(); }

private:
	static Map  _map;

	static int _outCol;
	static int _outRow;
	static float _outPosX;
	static float _outPosY;

	static float _pacmanStartX;
	static float _pacmanStartY;
	static int	 _pacmanStartCol;
	static int 	 _pacmanStartRow;

	static int	 _points;

	friend class Actor;
	friend class ActorMgr;
	friend class Pacman;
	friend class Ghost;
	friend class RedGhost;
	friend class PinkGhost;
	friend class OrangeGhost;
	friend class CyanGhost;
};