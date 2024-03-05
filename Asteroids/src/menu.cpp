#include "menu.h"

Menu::Menu() {

}
Menu::~Menu() {

}

bool Menu::Initialize() {

	// Inicializamos la opción actual 
	// en la primera
	_optionSelected = 0;

	// Recorremos el arreglo de opciones
	// para inicializarlas
	for (int i=0; i < MENU_OPTIONS_COUNT; i++) {

		// Cargamos el sprite de la opción
		if (!_option[i].LoadIni("data/graphics/menu.spr"))
			return false;
		
		// Indicamos el cuadro de animación
		// correspondiente a la opción
		// según el bitmap creado
		_option[i].SetFrame(i*2);

		// Verificamos si es la primera opción
		if (i>0) {	
			// Si no es la primera opción
			// indicamos que se posicione
			// por debajo de la anterior
			_option[i].SetPosX(_option[i-1].GetPosX());
			_option[i].SetPosY(_option[i-1].GetPosY() - _option[i-1].GetHeight() - 5);
		} else {
			// Si es la primera opción
			// indicamos que se posicione
			// según las constantes
			_option[i].SetPos(MENU_START_POS_X,MENU_START_POS_Y);
		}
	}
	
	// Inicializamos el estado
	// actual en NONE
	_state = MENU_STATE_NONE;

	return true;
}

void Menu::Update(float dt) {

	// Si se presionó la tecla abajo
	if (KeyDown(DIK_DOWN)) {
		// Seleccionamos la siguiente opción
		_optionSelected++;

		// En el caso de superar la cantidad
		// máxima, volvemos a la primera
		// opción
		if (_optionSelected >= MENU_OPTIONS_COUNT) {
			_optionSelected = 0;
		}

	// Si se presionó la tecla arriba
	} else if (KeyDown(DIK_UP)) {
		// Seleccionamos la opción anterior
		_optionSelected--;

		// Si la opción seleccionada
		// es inferior a la primera
		// seleccionamos la última
		if (_optionSelected < 0) {
			_optionSelected = MENU_OPTIONS_COUNT-1;
		}
	}

	// Si se presionó la tecla Enter
	if (KeyDown(DIK_RETURN))
		// Indicamos que el estado actual
		// es igual a la opción 
		// seleccionada
		_state = _optionSelected+1;

	// Mostramos los botones en 
	// su estado "apagado"
	for (int i=0; i < MENU_OPTIONS_COUNT; i++) {
		_option[i].SetFrame(i*2);

		_option[i].Update(dt);
	}

	// Resaltamos la opción seleccionada
	_option[_optionSelected].SetFrame(_optionSelected*2+1);
}

void Menu::Draw() {
	// Mostramos las opciones
	for (int i=0; i < MENU_OPTIONS_COUNT; i++) {
		_option[i].Draw();
	}
}

