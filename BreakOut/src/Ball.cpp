#include "Ball.h"

Ball::Ball(void)
{
	_vx = 0.0f;
	_vy = 0.0f;
	_vidas = 0;
  _speed = INITIAL_SPEED;
}

Ball::~Ball(void)
{
}

bool Ball::Initialize()
{
	if(!LoadIni("./data/ball.spr"))
		return false;
	
	SetDim(14, 14); // Tamaño
	SetPos(0, 0); // Posición inicial
	SetCheckCollision(true); // Deseamos chequear colisión

	// Defino colisión para bola
	SetCollisionType(Entity2D::eCollisionCircle);
  SetCollisionRadius(GetWidth() / 2);
  SetCollisionVisible(true);

	// Su velocidad inicial
	_vx = _vy = _speed;

	// Al inicio estará pegada al Pad
	_isSticky = true;

	return true;
}

void Ball::OnCollide(Entity2D *entity) 
{

	float puntoChoqueX, puntoChoqueY;

	// Obtengo las coordenadas de la colisión
	this->GetCollisionPos(puntoChoqueX, puntoChoqueY);

	// Coordenadas de la entidad
	float ejeY = entity->GetPosY();
	float ejeX = entity->GetPosX();

	float nvx;

	// Si no pega en los bordes hace el efecto de rebote
	if(puntoChoqueX != ejeX + entity->GetWidth() / 2 ||
		puntoChoqueX != ejeX - entity->GetWidth() / 2)
	{
		nvx = (ejeX - GetPosX()) / 100;
	}
	else
		nvx = _vx;

	// Volver a la posición anterior..
	SetToPreviousPosition();

	// Si no está en la posición inicial hace el efecto de rebote
	if(!_isSticky){
		this->SetVX(_vx - nvx);
	}

	// Invertir la velocidad
	BoundY();
	Update(_vx);
}

void Ball::Update(float dt)
{
	float x = GetPosX();
	float y = GetPosY();
	float w = (float) g_renderer.GetViewPortWidth();
	float h = (float) g_renderer.GetViewPortHeight();

	// Actualizo el shape
	Sprite::Update(dt);

	// Actualizamos la posición respecto
	// de la velocidad y el tiempo
	x += _vx * dt;
	y += _vy * dt;

	// Verifico si estoy fuera del margen derecho
	if( x > w/2 - GetWidth() / 2)
	{
		// Me posiciono sobre el borde
		x = w/2 - GetWidth() / 2;
		// Invierto la dirección
		BoundX();
	}
	else // Verifico si estoy fuera del margen izquierdo
		if(x < -w/2 + GetWidth() / 2)
		{
			x = -w/2 + GetWidth() / 2;
			BoundX();
		}

	// Verifico si estoy fuera del margen superior
	if( y > h/2 - GetHeight() / 2)
	{
		y = h/2 - GetHeight() / 2;
		BoundY();
	}
	else // Verifico si estoy fuera del margen inferior
		if(y < -h/2 + GetHeight() / 2){
			SetSticky(true);

			if(_vidas > 0)
				_vidas--;
		}

	// Defino nueva posición
	SetPos(x, y);

	// Mantener velocidad constante
	if(abs((int)this->_vx) != abs((int)this->_vy))
		_vx = _vy;

	if(_vx > _speed || _vy > _speed)
	{
		_vx = _speed;
		_vy = _speed;
	}
}
