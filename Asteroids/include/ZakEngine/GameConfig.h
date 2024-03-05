#pragma once

#include <string.h>

#include "defines.h"
#include "configfile.h"
#include "messages.h"
#include "FileLog.h"

namespace zak {

/**
 *  Clase que permite manejar la configuración del juego.
 *	@author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API GameConfig {
public:
	/**
	 *  Permite cargar la configuración a través de un archivo .ini. 
	 *  En caso de que el archivo no exista, intenta crear uno nuevo.
	 *	@param filename Nombre del archivo
	 *  @return Devuelve true si pudo ser cargado satisfactoriamente y false en caso contrario
	 */
	bool Load(char *filename);

	/**
	 *  Permite guardar la configuración en un archivo .ini
	 *	@param filename Nombre del archivo
	 *  @return Devuelve true si pudo ser guardado satisfactoriamente y false en caso contrario
	 */
	bool Save(char *filename);

	/**
	 *  Permite indicar el idioma
	 *	@param language Cadena de caracteres que indica el idioma con el que trabajaremos
	 */
	void SetLanguage(char *language);

	/**
	 *  Permite indicar el título de la ventana
	 *	@param caption Título de la ventana
	 */
	void SetCaption(char *caption);

	/**
	 *  Permite indicar el ancho de la ventana
	 *	@param width Ancho de la ventana
	 */
	void SetWidth(int width);

	/**
	 *  Permite indicar el alto de la ventana
	 *	@param height Alto de la ventana
	 */
	void SetHeight(int height);

	/**
	 *  Permite indicar los bits por píxel
	 *	@param bits Bits por píxel
	 */
	void SetBits(int bits);

	/**
	 *  Permite indicar la velocidad de refresco
	 *	@param refreshRate Velocidad de refresco 
	 */
	void SetRefreshRate(int refreshrate);

	/**
	 *  Permite indicar si deseamos congelar los cuadros por segundo
	 *	@param lockFPS Cantidad de cuadros por segundo a los que deseamos que corra la aplicación
	 */
	void SetLockFPS (int lockFPS);

	/**
	 *  Permite indicar si deseamos que el juego corra a pantalla completa o no
	 *	@param fullscreen Si indicamos true, el juego correrá a pantalla completa.
	 */
	void SetFullscren(bool fullscreen);

	/**
	 *  Permite indicar si deseamos activar la sincronización vertical 
	 *	@param vsync Si indicamos true, activaremos la sincronización vertical
	 */
	void SetVSync(bool vsync);

	/**
	 *  Permite indicar si deseamos que el cursor esté visible o no
	 *	@param cursorVisible Si indicamos true, veremos el cursor de windows en pantalla
	 */
	void SetCursorVisible(bool cursorVisible);

	/**
	 *  Permite indicar si deseamos activar el sonido
	 *	@param sound Si indicamos true, activaremos el sonido.
	 */
	void SetSound(bool sound);

	/**
	 *  Devuelve el idioma
	 *	@return Cadena de caracteres que indica el idioma con el que trabajaremos
	 */
	const char *GetLanguage()	{ return _language; }

	/**
	 *  Devuelve el título de la ventana
	 *	@return Título de la ventana
	 */
	const char *GetCaption()	{ return _caption; }

	/**
	 *  Devuelve el ancho de la ventana
	 *	@return Ancho de la ventana
	 */
	int GetWidth()				{ return _width; }

	/**
	 *  Devuelve el alto de la ventana
	 *	@return Alto de la ventana
	 */
	int GetHeight()				{ return _height; }

	/**
	 *  Devuelve los bits por píxel
	 *	@return Bits por píxel
	 */
	int	GetBits()				{ return _bits; }

	/**
	 *  Devuelve los cuadros por segundo a los que está bloqueado. 
	 *  En caso de devolver cero significa que no estará bloqueado.
	 *	@return Cantidad de cuadros por segundo a los que deseamos que corra la aplicación
	 */
	int	GetLockFPS()			{ return _lockFPS; }

	/**
	 *  Devuelve la velocidad de refresco
	 *	@return Velocidad de refresco 
	 */
	int GetRefreshRate()		{ return _refreshRate; }

	/**
	 *  Devuelve si la aplicación corre a pantalla completa o no.
	 *	@return Si devuelve true, el juego estará corriendo a pantalla completa.
	 */
	bool GetFullscreen()		{ return _fullscreen; }

	/**
	 *  Devuelve si está activada la sincronización vertical
	 *	@return Devuelve true en caso de que esté activada la sincronización vertical y false en caso contrario.
	 */
	bool GetVSync()				{ return _vsync; }

	/**
	 *  Devuelve si el cursor de windows está visible
	 *	@return Devuelve true en caso de que el cursor de windows esté visible y false en caso contrario.
	 */
	bool GetCursorVisible()		{ return _cursorVisible; }

	/**
	 *  Devuelve si el sonido está activado
	 *	@return Devuelve true en caso de que el sonido esté activado y false en caso contrario.
	 */
	bool GetSound()				{ return _sound; }

	GameConfig();
	~GameConfig();

private:
	char	_language[100];
	char	_caption[100];
	int		_width;
	int		_height;
	int		_bits;
	bool	_fullscreen;
	bool	_vsync;
	int		_refreshRate;
	int		_lockFPS;
	bool	_sound;
	bool	_cursorVisible;
};


} // end namespace

