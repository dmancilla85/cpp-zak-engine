#include "boardmap.h"

BoardMap::BoardMap(void) {
  Reset();
  }

BoardMap::~BoardMap(void) {
  }

// Dibuja el mapa
void BoardMap::Draw() {
  
  float x = GetPosX();
  float y = GetPosY();
  g_renderer.EnableModulate();
  
  for (int i=0; i<COLS; i++) {
    for (int j=0; j<ROWS; j++) {
      if (_map[i][j] != 0) {
        g_renderer.SetModulationColor(_map[i][j]);
        } else {
          g_renderer.SetModulationColor(0xFF606060);
        }
      
      SetPos(x+i*GetWidth()*GetScaleX(),y-j*GetHeight()
        *GetScaleY());
      
      Sprite::Draw();
      }
    }
  g_renderer.DisableModulate();
  SetPos(x,y);
  }

void BoardMap::Update(float dt) {
  Sprite::Update(dt);
  }

// Verifica si la pieza colisiona contra el tablero
bool BoardMap::CollideWith(Piece & piece) {
  
  for (int row=0; row<piece._size; row++)
    for (int col=0; col<piece._size; col++)
      {
      // Verifico que la pos. del mapa por afectar esté dentro de él
        if (piece._col+col >= COLS || piece._col+col < 0)
          {
          // Me estoy yendo del mapa por la derecha o por la izquierda
            if (piece._data[col + row * piece._size] != 0)
              return true;
          }
        else if (piece._row + row >= ROWS || piece._row+row < 0)
          {
          // Estoy tocando el piso del mapa o
          // estoy por encima del mapa -> ¿Éste es un caso posible?
            if (piece._data[col + row * piece._size] != 0)
              return true;
          }
        else if (_map[piece._col + col][piece._row + row] != 0 &&
          piece._data[col + row * piece._size] != 0)
          // Una parte de la pieza toca otra pieza del mapa
          return true;
      }
    return false;
  }

// Copia la pieza en el tablero
void BoardMap::StampPiece(Piece & piece) {
  
  for (int row = 0; row < piece._size; row++)
    for (int col = 0; col < piece._size; col++)
      {
      if (piece._col + col >= 0 && piece._col + col < COLS &&
        piece._row + row >= 0 && piece._row + row < ROWS &&
        piece._data[col + row * piece._size] != 0)
        _map[piece._col + col][piece._row + row] = piece.
        _data[col + row * piece._size];
      }
    piece.SetVisible(false);
  }

// Limpia una línea específica del tablero
void BoardMap::ClearLine(int row) {
  // Copio las lineas hacia abajo
  for (int i = row; i > 0; i--)
    for (int col = 0; col < COLS; col++)
      _map[col][i] = _map[col][i-1];
  // Elimino la primera línea
  for (int col = 0; col < COLS; col++)
    _map[col][0] = 0;
  }

// Busca líneas formadas en el tablero
int BoardMap::CheckForLines() {
  bool isALine;
  int lines=0;

  for (int row = ROWS; row >= 0; row--)
    {
    isALine = true;

    for (int col=0; col < COLS; col++)
      {
      if (_map[col][row] == 0)
        {
        isALine = false;
        break;
        }
      }
    if (isALine)
      {
      lines++;
      ClearLine(row);
      row++;
      }
    }
  return lines;
  }

// Reseteo el tablero
void BoardMap::Reset() {
  for (int i = 0; i < COLS; i++)
    for (int j = 0; j < ROWS; j++)
      _map[i][j] = 0;
  }