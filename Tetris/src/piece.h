#pragma once
#include "zakengine/zak.h"

using namespace zak;

#define MAX_PIECES 7
#define MAX_PIECE_SIZE 4

class Piece : public Sprite {

public:
  void SetRandomType();
  void SetType(int type, DWORD color);
  int GetType() { return _type; }
  void RotateCW();
  void RotateCCW();
  void MoveLeft() { _col--; }
  void MoveRight() { _col++; }
  void MoveUp() { _row--; }
  void MoveDown() { _row++; }
  DWORD GetColorByType(int type);
  void SetStartPos(float x, float y) { _startPosX = x; _startPosY = y;}
  void Update(float dt);
  void Draw();
  Piece();
  ~Piece();

private:
  int _size;
  DWORD _data[MAX_PIECE_SIZE*MAX_PIECE_SIZE];
  DWORD _color;
  int _row;
  int _col;
  float _startPosX;
  float _startPosY;
  int _type;
  friend class BoardMap;
  };