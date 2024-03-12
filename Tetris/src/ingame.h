#pragma once

#include "zakengine/zak.h"
#include "boardMap.h"
#include "piece.h"

using namespace zak;

#define GAME_STATE_NONE 0
#define GAME_STATE_EXIT 1
#define GAME_STATE_NEXTLEVEL 2
#define START_POS_X -100.0f
#define START_POS_Y 100.0f
#define NEXT_PIECE_POS_X -200.0f
#define NEXT_PIECE_POS_Y 100.0f
#define FALL_INTERVAL 1000.0f
#define MOVE_INTERVAL 80.0f

class InGame {

public:
  bool Initialize(int level);
  bool Shutdown();
  void SetState(int state) { _state = state; }
  int GetState() { return _state; }
  void Update(float dt);
  void Draw();
  InGame();
  ~InGame();

private:
  int _state;
  Piece _piece;
  Piece _nextPiece;
  BoardMap _boardMap;
  float _fallInterval;
  int _score;
  };