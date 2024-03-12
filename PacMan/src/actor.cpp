#include "actor.h"


bool Actor::SetAction(int action) {
	static int col=0;
	static int row=0;
	static int tile=0;

	// Verifico de que acción se trata para determinar
	// si es una acción válida
	switch(action) {
		case ACTOR_ACTION_NONE:
			_action = action;
			return true;
			break;

		// Quiero ir hacia la izquierda
		case ACTOR_ACTION_LEFT:
			// Pido columna y fila en el mapa 
			// que corresponda a la posición 
			// en coordenadas de mundo del actor 
			Level::_map.GetColRowFromWorldCoords(GetPosX(), GetPosY(), col, row);

			// Dado que deseo ir hacia la izquierda,
			// verifico si se puede atravesar el tile 
			// izquierdo 
			tile = Level::_map.GetTileFromColRow(col-1, row);

			if (tile == TILE_EMPTY || tile == TILE_POINT || tile == TILE_PILL || tile == -1 ||
				(tile == TILE_DOOR1 || tile == TILE_DOOR2 || tile == TILE_DOOR3 || tile == TILE_DOOR4 || 
				tile == TILE_DOOR5 || tile == TILE_DOOR6 || tile == TILE_DOOR7 || tile == TILE_DOOR8) && 
				(_state == GHOST_STATE_GETOUTHOME || _state == GHOST_STATE_GOHOME)) {

				// en caso afirmativo, permito la acción...
				_action = action;

				// y centro el actor
				CenterOnRow(col,row);

				_lastAction = _action;

				return true;
			}
			break;

		// El resto de las acciones 
		// son análogas a la anterior

		case ACTOR_ACTION_RIGHT:
			Level::_map.GetColRowFromWorldCoords(GetPosX(), GetPosY(), col, row);
			tile = Level::_map.GetTileFromColRow(col+1, row);
			if (tile == TILE_EMPTY || tile == TILE_POINT || tile == TILE_PILL || tile == -1 ||
				(tile == TILE_DOOR1 || tile == TILE_DOOR2 || tile == TILE_DOOR3 || tile == TILE_DOOR4 || 
				tile == TILE_DOOR5 || tile == TILE_DOOR6 || tile == TILE_DOOR7 || tile == TILE_DOOR8) && 
				(_state == GHOST_STATE_GETOUTHOME || _state == GHOST_STATE_GOHOME)) {
				_action = action;
				CenterOnRow(col,row);

				_lastAction = _action;

				return true;
			}
			break;

		case ACTOR_ACTION_UP:
			Level::_map.GetColRowFromWorldCoords(GetPosX(), GetPosY(), col, row);
			tile = Level::_map.GetTileFromColRow(col, row-1);
			if (tile == TILE_EMPTY || tile == TILE_POINT || tile == TILE_PILL || tile == -1 ||
				(tile == TILE_DOOR1 || tile == TILE_DOOR2 || tile == TILE_DOOR3 || tile == TILE_DOOR4 || 
				tile == TILE_DOOR5 || tile == TILE_DOOR6 || tile == TILE_DOOR7 || tile == TILE_DOOR8) && 
				(_state == GHOST_STATE_GETOUTHOME || _state == GHOST_STATE_GOHOME)) {
				_action = action;
				CenterOnCol(col,row);

				_lastAction = _action;

				return true;
			}
			break;

		case ACTOR_ACTION_DOWN:
			Level::_map.GetColRowFromWorldCoords(GetPosX(), GetPosY(), col, row);
			tile = Level::_map.GetTileFromColRow(col, row+1);
			if (tile == TILE_EMPTY || tile == TILE_POINT || tile == TILE_PILL || tile == -1 ||
				(tile == TILE_DOOR1 || tile == TILE_DOOR2 || tile == TILE_DOOR3 || tile == TILE_DOOR4 || 
				tile == TILE_DOOR5 || tile == TILE_DOOR6 || tile == TILE_DOOR7 || tile == TILE_DOOR8) && 
				(_state == GHOST_STATE_GETOUTHOME || _state == GHOST_STATE_GOHOME)) {
				_action = action;
				CenterOnCol(col,row);

				_lastAction = _action;

				return true;
			}
			break;
	}

	return false;
}

void Actor::Update(float dt) {
	static float x = GetPosX();
	static float y = GetPosY();
	static int col=0;
	static int row=0;
	static int tile=0;

	x = GetPosX();
	y = GetPosY();
	

	// Verifico la acción actual y
	// según la misma, actualizo...
	switch(_action) {
		// Si estoy trasladándome hacia la izquierda
		case ACTOR_ACTION_LEFT:
			// Tomo la columna y fila en el mapa
			// correspondiente a la posición de
			// mundo del actor
			Level::_map.GetColRowFromWorldCoords(x, y, col, row);
			
			// Dado que estoy trasladándome hacia la izquierda,
			// verifico si se puede atravesar el tile 
			// izquierdo 
			tile = Level::_map.GetTileFromColRow(col-1, row);
			if (!(tile == TILE_EMPTY || tile == TILE_POINT || tile == TILE_PILL || tile == -1 ||
				(tile == TILE_DOOR1 || tile == TILE_DOOR2 || tile == TILE_DOOR3 || tile == TILE_DOOR4 || 
				tile == TILE_DOOR5 || tile == TILE_DOOR6 || tile == TILE_DOOR7 || tile == TILE_DOOR8) && 
				(_state == GHOST_STATE_GETOUTHOME || _state == GHOST_STATE_GOHOME))) {
				// si no puedo atravesarlo, desactivo la acción
				SetAction(ACTOR_ACTION_NONE);
			} else {
				// en caso de poder atravesar el tile, 
				// calculo la posición
				x -= GetSpeed()*dt;
			}
			break;

		// El resto de las acciones son análogas
		// a la anterior

		case ACTOR_ACTION_RIGHT:
			Level::_map.GetColRowFromWorldCoords(x, y, col, row);
			tile = Level::_map.GetTileFromColRow(col+1, row);
			if (!(tile == TILE_EMPTY || tile == TILE_POINT || tile == TILE_PILL || tile == -1 ||
				(tile == TILE_DOOR1 || tile == TILE_DOOR2 || tile == TILE_DOOR3 || tile == TILE_DOOR4 || 
				tile == TILE_DOOR5 || tile == TILE_DOOR6 || tile == TILE_DOOR7 || tile == TILE_DOOR8) && 
				(_state == GHOST_STATE_GETOUTHOME || _state == GHOST_STATE_GOHOME))) {
				SetAction(ACTOR_ACTION_NONE);
			} else {
				x += GetSpeed()*dt;
			}
			break;
		case ACTOR_ACTION_UP:
			Level::_map.GetColRowFromWorldCoords(x, y, col, row);
			tile = Level::_map.GetTileFromColRow(col, row-1);

			if (!(tile == TILE_EMPTY || tile == TILE_POINT || tile == TILE_PILL || tile == -1 ||
				(tile == TILE_DOOR1 || tile == TILE_DOOR2 || tile == TILE_DOOR3 || tile == TILE_DOOR4 || 
				tile == TILE_DOOR5 || tile == TILE_DOOR6 || tile == TILE_DOOR7 || tile == TILE_DOOR8) && 
				(_state == GHOST_STATE_GETOUTHOME || _state == GHOST_STATE_GOHOME))) {
				SetAction(ACTOR_ACTION_NONE);
			} else {
				y += GetSpeed()*dt;
			}
			break;
		case ACTOR_ACTION_DOWN:
			Level::_map.GetColRowFromWorldCoords(x, y, col, row);
			tile = Level::_map.GetTileFromColRow(col, row+1);
			if (!(tile == TILE_EMPTY || tile == TILE_POINT || tile == TILE_PILL || tile == -1 ||
				(tile == TILE_DOOR1 || tile == TILE_DOOR2 || tile == TILE_DOOR3 || tile == TILE_DOOR4 || 
				tile == TILE_DOOR5 || tile == TILE_DOOR6 || tile == TILE_DOOR7 || tile == TILE_DOOR8) && 
				(_state == GHOST_STATE_GETOUTHOME || _state == GHOST_STATE_GOHOME))) {
				SetAction(ACTOR_ACTION_NONE);
			} else {
				y -= GetSpeed()*dt;
			}

			break;
	}

	// Verifico si estoy fuera del mapa (tunel)
	// y fuerzo al actor a aparecer por el 
	// extremo contrario
	if (x <= Level::_map.GetPosX())
		x = Level::_map.GetPosX()+Level::_map.GetWidth()*Level::_map.GetMapWidth()-1;

	if (x >= Level::_map.GetPosX()+Level::_map.GetWidth()*Level::_map.GetMapWidth())
		x = Level::_map.GetPosX()+1;

	if (y >= Level::_map.GetPosY())
		y = Level::_map.GetPosY()-Level::_map.GetHeight()*Level::_map.GetMapHeight()+1;

	if (y <= Level::_map.GetPosY()-Level::_map.GetHeight()*Level::_map.GetMapHeight())
		y = Level::_map.GetPosY()-1;


	SetPos(x,y);

	Sprite::Update(dt);
}

void Actor::CenterOnRow(int col, int row) {
	static float x=0;
	static float y=0;

	Level::_map.GetWorldCoordsFromColRow(col, row, x, y);

	SetPosY(y);
}

void Actor::CenterOnCol(int col, int row) {
	static float x=0;
	static float y=0;

	// Convierto la columna y fila en el mapa
	// en coordenadas de mundo
	Level::_map.GetWorldCoordsFromColRow(col, row, x, y);

	SetPosX(x);
}

void Actor::SetState(int state) { 
	_state = state; 
}

int Actor::GetState(){ 
	return _state; 
}

