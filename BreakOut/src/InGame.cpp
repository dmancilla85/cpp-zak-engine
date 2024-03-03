#include "Ingame.h"

void InGame::Reset(){
  _puntaje = 0;
  _ladrillosRotos = 0;
  _nivel = 0;
  }

InGame::InGame(void)
  {
  Reset();
  _state = GAME_STATE_LOADING;
  }

InGame::~InGame(void)
  {
  }

bool InGame::CheckCollision(zak::Entity2D &entity1, zak::Entity2D &entity2)
  {
  // Si están activadas las colisiones de ambas entidades, 
  // entonces chequeamos colisión
  if (entity1.GetCheckCollision() && entity2.GetCheckCollision()) {
    float x1 = entity1.GetPosX() - (entity1.GetWidth() / 2);
    float w1 = entity1.GetWidth();
    float y1 = entity1.GetPosY() - (entity1.GetHeight() / 2);
    float h1 = entity1.GetHeight();

    float x2 = entity2.GetPosX() - (entity2.GetWidth() / 2);
    float w2 = entity2.GetWidth();
    float y2 = entity2.GetPosY() - (entity2.GetHeight() / 2);
    float h2 = entity2.GetHeight();

    // Si ((x1 esta entre x2 y x2+w2) o (x2 esta entre x1 y x1+w1))
    // y ((y1 esta entre y2 y y2+h2) o (y2 esta entre y1 y y1+h1))
    if (((x1 < x2+w2 && x1 > x2) || (x2 < x1+w1 && x2 > x1)) &&
      ((y1 < y2+h2 && y1 > y2) || (y2 < y1+h1 && y2 > y1)))

      // entonces hubo colisión
      return true;
    }

  // No hubo colisión
  return false;
  }


bool InGame::BuildWall(unsigned short _bricksActivos[BRICKS_FILES][BRICKS_PER_SIDE])
  {
  _totalLadrillos = 0;
  _ladrillosRotos = 0;

  // Recorro el array e inicializo los ladrillos
  for(int y = 0; y < BRICKS_FILES; y++){
    for(int x = 0; x < BRICKS_PER_SIDE; x++)
      {
      // Inicializo el ladrillo
      if(!_bricks[y * BRICKS_PER_SIDE + x].Initialize())
        return false;

      // Tomo el ancho y alto del ladrillo
      float w = _bricks[y * BRICKS_PER_SIDE + x].GetWidth();
      float h = _bricks[y * BRICKS_PER_SIDE + x].GetHeight();

      // Seteo la posición del ladrilo
      _bricks[y*BRICKS_PER_SIDE+x].SetPos(START_POS_X + x * (w + SPACE_BETWEEN_X), 
        START_POS_Y - y *(h + SPACE_BETWEEN_Y));

      if(_bricksActivos[y][x] == 1)
        {
        _bricks[y * BRICKS_PER_SIDE + x].SetVisible(true);
        _totalLadrillos++;
        }	
      else 
        {
        _bricks[y * BRICKS_PER_SIDE + x].SetVisible(false);
        _bricks[y * BRICKS_PER_SIDE + x].SetCheckCollision(false);
        }
      }
    }

  return true;
  }

bool InGame::BuildWall(string nivel)
  {
  ifstream estructuraMuro(nivel.c_str());
  string linea;

  unsigned short murosVisibles[BRICKS_FILES][BRICKS_PER_SIDE];

  if (estructuraMuro.is_open())
    {
    int i = 0;
    //Mientras que no sea fin de archivo
    while (! estructuraMuro.eof() )
      {
      getline (estructuraMuro, linea);

      for(unsigned j = 0; j < linea.length(); j++)
        murosVisibles[i][j] = linea[j] - 48;
      i++;

      }
    estructuraMuro.close();

    BuildWall(murosVisibles);
    }
  else cout << "No se pudo abrir el archivo.";

  return true;
  }

bool InGame::Initialize()
  {
  // Inicializar la bola
  if(!_ball.Initialize())
    return false;

  // Vidas
  _ball.SetVidas(VIDAS);

  // Inicializar el pad
  if(!_pad.Initialize())
    return false;

  if(!_loading.Initialize())
    return false;

  if(!_loseGame.Initialize())
    return false;

  if(!_winGame.Initialize())
    return false;

  // Fabrico el muro correspondiente
  _nivel = 0;
  string caso1 = "data/0.txt";
  BuildWall(caso1);

  return true;
  }

void InGame::Update(float dt)
  {
  string aux = "data/1.txt";	

  switch(_state)
    {
    case GAME_STATE_LOADING:
      // Actualizamos la pantalla de carga
      _loading.Update(dt);		
      BuildWall(aux);
      _state = GAME_STATE_NONE;
      break;

    case GAME_STATE_LOSE:
      // Actualizamos la pantalla de carga
      _loseGame.Update(dt);

      if(_loseGame.GetState() == LOSE_STATE_NONE)
        {
        _state = GAME_STATE_EXIT;
        }
      break;

    case GAME_STATE_WIN:
      // Actualizamos la pantalla de carga
      _winGame.Update(dt);

      if(_winGame.GetState() == WIN_STATE_NONE)
        {
        _state = GAME_STATE_EXIT;
        }
      break;

    case GAME_STATE_NONE:
      // Si presionamos escape salimos al menú
      if(KeyDown(DIK_ESCAPE))
        _state = GAME_STATE_EXIT;

      _pad.SetAction(MOVE_NONE);

      // Si presione cursor izquierda
      if(KeyPressed(DIK_LEFT))
        // Muevo el pad hacia la izquierda
        _pad.SetAction(MOVING, -0.8f);

      else if(KeyPressed(DIK_RIGHT)){
        // Muevo el pad hacia la derecha
        _pad.SetAction(MOVING, 0.8f);
        }
      // Si muevo el mouse
      else if(MouseRelPosf(ZAK_INPUT_MOUSE_POS_X) != 0.0f)
        {
        // Muevo el pad respecto del movimiento del mouse
        _pad.SetPosX(_pad.GetPosX() + MouseRelPosf(ZAK_INPUT_MOUSE_POS_X));
        } // Sí hay algún joystick conectado..
      else if(JoystickCount() > 0)
        {
        // Verifico si la posición del joystick es diferente del centro
        if(JoystickPosf(0, ZAK_INPUT_POS_X) != 0)
          // Muevo el pad respecto de la posición del joystick
          _pad.SetAction(MOVING, (JoystickPosf(0, ZAK_INPUT_POS_X) / 1024) * 0.4f);
        }

      if((KeyDown(DIK_SPACE) || MouseClick(ZAK_INPUT_MOUSE_BTN_1) ||
        JoystickButtons(0, 1)) && _ball.GetSticky())
        {
        _ball.SetSticky(false);
        _ball.SetVX(0.4f);
        _ball.SetVY(-0.4f);
        }

      // Si la bola está pegajosa la trasladamos junto con el pad
      if(_ball.GetSticky())
        {
        _ball.SetPos(_pad.GetPosX(), _pad.GetPosY() + _pad.GetHeight() / 2 + 
          _ball.GetHeight()/2 + 2);
        _ball.SetVX(0);
        _ball.SetVY(0);
        }

      // Actualizo las entidades
      _pad.Update(dt);
      _ball.Update(dt);

      // Recorro el array de ladrillos para actualizarlos y chequear la colisión
      for(int y = 0; y < BRICKS_FILES; y++)
        for(int x = 0; x < BRICKS_PER_SIDE; x++)
          {
          //Actualizo el ladrillo
          _bricks[y * BRICKS_PER_SIDE + x].Update(dt);

          // Chequeo la colisión del ladrillo
          if(CheckCollision(_ball, _bricks[y * BRICKS_PER_SIDE + x]))
            {
            // En el caso de haber colisión..
            _ball.OnCollide(&_bricks[y * BRICKS_PER_SIDE + x]);
            _bricks[y * BRICKS_PER_SIDE + x].OnCollide(&_ball);

            // Aumento el puntaje
            _puntaje += _bricks[y * BRICKS_PER_SIDE + x].GetDamage();
            // Aumento la cantidad de ladrillos rotos
            _ladrillosRotos += _bricks[y * BRICKS_PER_SIDE + x].GetDamage() / 100;
            }
          }

        // Chequeo la colisión entre la bola y el pad
        if(CheckCollision(_ball, _pad))
          {
          // En el caso de haber colisión
          // llamo a los métodos OnCollide de las 2 entidades
          _ball.OnCollide(&_pad);
          _pad.OnCollide(&_ball);
          }

        // Si se acaban las vidas el puntaje es 0
        if(_ball.GetVidas() == 0)
          {
          Reset();
          _pad.SetInitialPos();
          _state = GAME_STATE_LOSE;
          Initialize();
          }

        // Si se rompen todos los ladrillos vuelve a generarse el muro
        if(_ladrillosRotos >= _totalLadrillos)
          {
          _nivel++;

          if(_nivel < NIVELES)
            {
            _ladrillosRotos = 0;
            _state = GAME_STATE_LOADING;
            _ball.SetSticky(true);
            _ball.IncreaseSpeed();
            BuildWall(aux);
            }
          else{
            Reset();
            _state = GAME_STATE_WIN;
            }
          }

        break;
    }
  }

void InGame::Draw()
  {
  // Mostrar información en pantalla
  wstringstream msg_vida, msg_puntaje, msg_nivel;

  switch(_state)
    {
    case GAME_STATE_NONE:
      msg_vida << "VIDAS : " << _ball.GetVidas();
      msg_puntaje << "PUNTAJE: " << _puntaje;
      msg_nivel << "NIVEL:" << _nivel + 1; 

      g_renderer.SetFont(FT_TAHOMA, 20);
      g_renderer.SetFontColor(0xFF0FF000);
      // Vidas
      g_renderer.DrawString(msg_vida.str(), 60, 600  - 20, 10, 10, ZAK_TEXT_CENTER);
      // Puntaje
      g_renderer.DrawString(msg_puntaje.str(), 800 - 100, 600 -20, 10, 10, ZAK_TEXT_CENTER);
      // Nivel
      g_renderer.DrawString(msg_nivel.str(), 400, 600 - 20, 10, 10, ZAK_TEXT_CENTER);

      // Dibujamos las entidades
      _ball.Draw();
      _pad.Draw();

      // REcorremos el array para dibujar los ladrillos
      for(int y = 0; y < BRICKS_FILES; y++)
        for(int x = 0; x < BRICKS_PER_SIDE; x++)
          _bricks[y * BRICKS_PER_SIDE + x].Draw();
      break;

    case GAME_STATE_LOADING:
      _loading.Draw();
      break;

    case GAME_STATE_LOSE:
      _loseGame.Draw();
      break;

    case GAME_STATE_WIN:
      _winGame.Draw();
      break;
    }
  }


bool InGame::Shutdown()
  {
  return true;
  }
