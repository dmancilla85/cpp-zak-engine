#pragma once

#include "zakengine/zak.h"
#include "piece.h"

using namespace zak;

class BoardMap : public Sprite {

public:
  static const int COLS = 10;
  static const int ROWS = 20;
  
  BoardMap(void);
  ~BoardMap(void);
  
  // Dibuja el mapa
  void Draw();
  // Actualiza
  void Update(float dt);
  // Verifica si la pieza colisiona contra el tablero
  bool CollideWith(Piece & piece);
  // Copia la pieza en el tablero
  void StampPiece(Piece & piece);
  // Limpia una línea específica del tablero
  void ClearLine(int row);
  // Busca líneas formadas en el tablero
  int CheckForLines();
  // Reseteo el tablero
  void Reset();

private:
  DWORD _map[COLS][ROWS];
  };