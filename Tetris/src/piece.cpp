#include "piece.h"

unsigned char pieceType[][1 + (MAX_PIECE_SIZE * MAX_PIECE_SIZE)] = {
  {2,
  1, 1,
  1, 1},
  {3,
  0, 1, 0,
  1, 1, 1,
  0, 0, 0},
  {3,
  1, 0, 0,
  1, 1, 0,
  0, 1, 0},
  {3,
  0, 1, 0,
  1, 1, 0,
  1, 0, 0},
  {3,
  0, 1, 0,
  0, 1, 0,
  0, 1, 1},
  {3,
  0, 1, 0,
  0, 1, 0,
  1, 1, 0},
  {4,
  0, 1, 0, 0,
  0, 1, 0, 0,
  0, 1, 0, 0,
  0, 1, 0, 0}
  };


Piece::Piece() {
  _size = 0;
  _color = 0xFF00FF00;
  _col = 0;
  _row = 0;
  _startPosX = 0;
  _startPosY = 0;
  }

Piece::~Piece() {
  // do nothing
  }

DWORD Piece::GetColorByType(int type) {
  
  DWORD color = 0xFF000000;

  switch(type) {
case 0:
  color = 0xFFFF0000;
  break;
case 1:
  color = 0xFF00FF00;
  break;
case 2:
  color = 0xFF0000FF;
  break;
case 3:
  color = 0xFFFFFF00;
  break;
case 4:
  color = 0xFF00FFFF;
  break;
case 5:
  color = 0xFFFF00FF;
  break;
case 6:
  color = 0xFF601060;
  break;
    }

  return color;
  }

void Piece::SetRandomType() {
  int rnd = rand()%MAX_PIECES;
  SetType(rnd, GetColorByType(rnd));
  }

void Piece::SetType(int type, DWORD color) {
  
  // Almaceno el tamaño de lado de la pieza
  _size = pieceType[type][0];

  _type = type;
  _color = color;

  for (int row=0; row<MAX_PIECE_SIZE; row++)
    for (int col=0; col<MAX_PIECE_SIZE; col++)
      _data[col+row*_size] = pieceType[type][(col+row*_size)+1]*_color;
        _col = 0;
        _row = 0;
        SetVisible(true);
  }

void Piece::RotateCW() {
  
  int ncol, nrow;
  DWORD newPiece[MAX_PIECE_SIZE*MAX_PIECE_SIZE];
  
  // Roto la pieza
  for (int row=0; row<_size; row++)
    for (int col=0; col<_size; col++)
      {
      ncol = _size-1-row;
      nrow = col;
      newPiece[ncol + nrow * _size] = _data[col + row * _size];
      }

    // Copio la pieza temporal a la definitiva
    memcpy((void *) _data, 
      (const void *) newPiece, _size * _size * sizeof(DWORD));
  }

void Piece::RotateCCW() {
  int ncol, nrow;
  
  DWORD newPiece[MAX_PIECE_SIZE*MAX_PIECE_SIZE];
  
  // Roto la pieza
  for (int row=0; row<_size; row++)
    for (int col=0; col<_size; col++)
      {
      ncol = row;
      nrow = _size-1-col;
      newPiece[ncol + nrow * _size] = _data[col + row * _size];
      }
    // Copio la pieza temporal a la definitiva
    memcpy((void *) _data, 
      (const void *) newPiece, _size * _size * sizeof(DWORD));
  }

void Piece::Update(float dt) {
  float x = GetPosX();
  float y = GetPosY();
  Sprite::Update(dt);
  SetPos(_startPosX+_col*GetWidth()*GetScaleX(), 
    _startPosY - _row*GetHeight()*GetScaleY());
  }

void Piece::Draw() {

  float x = GetPosX();
  float y = GetPosY();
  
  if (GetVisible()) {
    for (int row=0; row<_size; row++) {
      for (int col=0; col<_size; col++) {
        if (_data[col+row*_size] != 0) {
          
          g_renderer.EnableModulate();
          g_renderer.SetModulationColor(_data[col+row*_size]);
          
          SetPos(x+col*GetWidth()*GetScaleX(), 
            y-row*GetHeight()*GetScaleY());
          Sprite::Draw();
          g_renderer.DisableModulate();
          }
        }
      }
    }
  SetPos(x,y);
  }