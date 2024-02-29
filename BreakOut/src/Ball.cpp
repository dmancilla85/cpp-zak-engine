#include "Ball.h"

Ball::Ball(void)
{
	_vx = 0.0f;
	_vy = 0.0f;
	_vidas = 0;
}

Ball::~Ball(void)
{
}

bool Ball::Initialize()
{
	if(!LoadIni("./data/ball.spr"))
		return false;
	
	//SetShape(ZAK_SHAPE_QUAD); // Forma
	SetDim(0.5, 0.5); // Tama�o
	SetPos(0, 0); // Posici�n inicial
	//SetColor(0xFF0000FF); // Color
	SetCheckCollision(true); // Deseamos chequear colisi�n

	// Defino colisi�n para bola
	//SetCollisionType(Entity2D::eCollisionBBox);
	//this->SetCollisionSize(GetWidth(), GetHeight());

	// Su velocidad inicial
	_vx = 0.03f;
	_vy = 0.03f;

	// Al inicio estar� pegada al Pad
	_isSticky = true;

	return true;
}

void Ball::OnCollide(Entity2D *entity) 
{

	float puntoChoqueX, puntoChoqueY;

	// Obtengo las coordenadas de la colisi�n
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

	// Volver a la posici�n anterior..
	SetToPreviousPosition();

	// Si no est� en la posici�n inicial hace el efecto de rebote
	if(!_isSticky){
		this->SetVX(_vx - nvx);
	}

	// Invertir la velocidad
	BoundY();
	Update(0.01f);
}

void Ball::Update(float dt)
{
	float x = GetPosX();
	float y = GetPosY();
	float w = (float) g_renderer.GetViewPortWidth();
	float h = (float) g_renderer.GetViewPortHeight();

	// Actualizo el shape
	Sprite::Update(dt);

	// Actualizamos la posici�n respecto
	// de la velocidad y el tiempo
	x += _vx * dt;
	y += _vy * dt;

	// Verifico si estoy fuera del margen derecho
	if( x > w/2 - GetWidth() / 2)
	{
		// Me posiciono sobre el borde
		x = w/2 - GetWidth() / 2;
		// Invierto la direcci�n
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

	// Defino nueva posici�n
	SetPos(x, y);

	// Mantener velocidad constante
	if(abs((int)this->_vx) != abs((int)this->_vy))
		_vx = _vy;

	if(_vx > 0.5f || _vy > 0.5f)
	{// Su velocidad inicial
		_vx = 0.5f;
		_vy = 0.5f;
	}
}
