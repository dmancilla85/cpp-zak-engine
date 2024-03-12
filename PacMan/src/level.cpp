#include "level.h"

Map		Level::_map;
int		Level::_outCol = 0;
int		Level::_outRow = 0;
float	Level::_outPosX = 0;
float	Level::_outPosY = 0;
int		Level::_pacmanStartCol = 0;
int		Level::_pacmanStartRow = 0;
float	Level::_pacmanStartX = 0;
float	Level::_pacmanStartY = 0;
int		Level::_points = 0;


bool Level::Initialize(int level) {
	if (!_map.Load("data/graphics/tiles.png","data/graphics/level1.map",0))
		return false;

	_map.SetPos(-_map.GetWidth()*_map.GetMapWidth()*0.5f,_map.GetHeight()*_map.GetMapHeight()*0.5f);

	while(_map.GetWorldCoordsFromTile(TILE_EXIT, _outPosX, _outPosY)) {
		_map.GetColRowFromWorldCoords(_outPosX, _outPosY, _outCol, _outRow);
		_map.SetTile(_outCol,_outRow,TILE_EMPTY);
	}

	while(_map.GetWorldCoordsFromTile(TILE_PACMAN_START, _pacmanStartX, _pacmanStartY)) {
		_map.GetColRowFromWorldCoords(_pacmanStartX, _pacmanStartY, _pacmanStartCol, _pacmanStartRow);
		_map.SetTile(_pacmanStartCol,_pacmanStartRow,TILE_EMPTY);
	}

	_points = _map.GetTileNumCount(TILE_POINT);
	_points += _map.GetTileNumCount(TILE_PILL);

	return true;
}
