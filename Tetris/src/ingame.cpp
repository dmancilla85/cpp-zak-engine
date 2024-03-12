#include "ingame.h"

InGame::InGame() {
  }

InGame::~InGame() {
  }

bool InGame::Initialize(int level) {
 
  if (!_piece.LoadIni("data/graphics/piece.spr"))
    return false;
  
  if (!_nextPiece.LoadIni("data/graphics/piece.spr"))
    return false;
  
  if (!_boardMap.LoadIni("data/graphics/piece.spr"))
    return false;

  _boardMap.Reset();
  _piece.SetRandomType();
  _piece.SetStartPos(START_POS_X,START_POS_Y);
  _nextPiece.SetStartPos(NEXT_PIECE_POS_X,NEXT_PIECE_POS_Y);
  _boardMap.SetPos(START_POS_X,START_POS_Y);
  _nextPiece.SetRandomType();
  _score = 0;

  // Inicializamos el estado
  _state = GAME_STATE_NONE;

  return true;
  }

bool InGame::Shutdown() {
  return true;
  }

void InGame::Update(float dt) {
  static float fallAccumTime = 0;
  static float moveAccumTime = 0;
  _fallInterval = FALL_INTERVAL;
  
  if (KeyDown(DIK_UP)) {
    _piece.RotateCCW();
    
    if (_boardMap.CollideWith(_piece))
      _piece.RotateCW();
    }
  if (KeyPressed(DIK_DOWN)) {
    _fallInterval = MOVE_INTERVAL;
    }
  
  moveAccumTime += dt;
  
  if (moveAccumTime >= MOVE_INTERVAL) {
    moveAccumTime = MOVE_INTERVAL;
    
    if (KeyPressed(DIK_LEFT)) {
      moveAccumTime -= MOVE_INTERVAL;
      _piece.MoveLeft();
      
      if (_boardMap.CollideWith(_piece))
        _piece.MoveRight();
      }
    
    if (KeyPressed(DIK_RIGHT)) {
      moveAccumTime -= MOVE_INTERVAL;
      _piece.MoveRight();
      
      if (_boardMap.CollideWith(_piece))
        _piece.MoveLeft();
      }
    }
  fallAccumTime += dt;
  
  if (fallAccumTime >= _fallInterval) {
    fallAccumTime = 0;
    _piece.MoveDown();
    
    if (_boardMap.CollideWith(_piece)) {
      int lines=0;
      _piece.MoveUp();
      _boardMap.StampPiece(_piece);
      lines = _boardMap.CheckForLines();
      
      if (lines == 1) {
        _score += 100;
        } else if (lines == 2) {
          _score += 300;
        } else if (lines == 3) {
          _score += 600;
          } else if (lines == 4) {
            _score += 1000;
          }

        _piece.SetType(_nextPiece.GetType(), _piece.GetColorByType
          (_nextPiece.GetType()));
        
        if (_boardMap.CollideWith(_piece)) {
          _state = GAME_STATE_EXIT;
          }
        _nextPiece.SetRandomType();
      }
    }
  // Si presionamos escape, salimos al menu
  if (KeyDown(DIK_ESCAPE))
    _state = GAME_STATE_EXIT;
  
  _piece.Update(dt);
  _nextPiece.Update(dt);
  _boardMap.Update(dt);
  }

void InGame::Draw() {
  wstringstream ss;
  _boardMap.Draw();
  _piece.Draw();
  _nextPiece.Draw();

  ss << "Score: " << _score;
  g_renderer.DrawString(ss.str(),10,10,780,580,ZAK_TEXT_RIGHT);
  }