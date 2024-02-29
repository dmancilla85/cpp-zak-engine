#include "Menu.h"

Menu::Menu(void)
{
}

Menu::~Menu(void)
{
}

bool Menu::Initialize()
{
	// Inicializamo la opci�n actual
	// en la primera
	_optionSelected = 0;
	

	if(!_logo.LoadIni("data/logo.spr"))
		return false;
	else
	{
		_logo.SetPosX(20.0f);
		_logo.SetPosY(180.0f);
		_logo.SetWidth(300.0f);
		_logo.SetHeight(200.0f);
	}

	// Recorremos el arreglo de opciones
	// para inicializarlas
	for(int i = 0; i < MENU_OPTIONS_COUNT; i++)
	{
		//Cargamos el sprite de la opci�n
		if(!_option[i].LoadIni("data/menuButtons.spr"))
			return false;

		// Indicamos el cuadro de animaci�n
		// correspondiente a la opci�n
		// seg�n el bitmap creado
		_option[i].SetFrame(i * 2);

		// Verificamos si es la primera opci�n
		if(i > 0)
		{
			// Si no es la primera opci�n
			// indicamos que se posicione
			// por debajo de la anterior
			_option[i].SetPosX(_option[i - 1].GetPosX());
			_option[i].SetPosY(_option[i - 1].GetPosY() - 
				_option[i - 1].GetHeight() - 5);

		}
		else
		{
			// Si es la primera opci�n
			// indicamos que se posicione
			// seg�n las constantes
			_option[i].SetPos(MENU_START_POS_X, MENU_START_POS_Y);

		}
	}

	// Inicializamos el estado actual en NONE
	_state = MENU_STATE_NONE;
	return true;
}

void Menu::Update(float dt)
{
	_logo.Update(dt);

	// Si se presiona la tecla abajo
	if(KeyDown(DIK_DOWN))
	{
		// Seleccionamos la siguiente opci�n
		_optionSelected++;

		// En el caso de superar la cantidad
		// m�xima, volvemos a la primera opci�n
		if(_optionSelected >= MENU_OPTIONS_COUNT)
			_optionSelected = 0;
	}
	else
	{
		if(KeyDown(DIK_UP))
		{
			// Seleccionamos la opci�n anterior
			_optionSelected--;

			// Si la opci�n seleccionada es inferior
			// a la primera seleccionamos la �ltima
			if(_optionSelected < 0)
				_optionSelected = MENU_OPTIONS_COUNT - 1;
		}
	}
	
	// Si se presion� la tecla Enter
	if(KeyDown(DIK_RETURN))
		/*  Indicamos que  el estado actual es igual
			a la opci�n seleccionada. */
			_state = _optionSelected + 1;

	// Mostramos los botones en
	// su estado apagado
	for(int i = 0; i < MENU_OPTIONS_COUNT; i++)
	{
		_option[i].SetFrame(i * 2);
		_option[i].Update(dt);
	}

	// Resaltamos la opci�n seleccionada
	_option[_optionSelected].SetFrame(_optionSelected * 2 + 1);
}

void Menu::Draw()
{
	_logo.Draw();
	
	// Mostramos las opciones
	for(int i = 0; i < MENU_OPTIONS_COUNT; i++)
	{
		_option[i].Draw();
	}
}