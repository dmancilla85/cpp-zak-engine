#ifndef _ZAKSOUND_H_
#define _ZAKSOUND_H_

#include "Defines.h"
#include "audiere.h"

#pragma comment(lib, "audiere.lib")

namespace zak {

/**
 *  Clase de manejo de sonido
 *	Ejemplo de uso:
 \code
bool TestGame::OnInit() {
	// Intentamos inicializar el 
	// dispositivo de sonido
	if (!SoundMgr::openDevice())
		return false;
	
	// Abrimos un archivo de música
	// en caso de error, el método
	// retornará NULL
	_music = SoundMgr::openSound("./data/machinae_supremacy_-_steves_quest.mp3", true);

	// Si hubo algún error, 
	// retornamos false
	if (!_music) {
		return false;
	}

	// Indicamos que deseamos que
	// se repita indefinidamente
	_music->setRepeat(true);

	// Corremos la música
	_music->play();
	
	// Abrimos un nuevo sonido
	_sound = SoundMgr::openSound("./data/Bubble.wav", false);

	// Verificamos si hubo algún error
	if (!_sound) {
		return false;
	}

	// Indicamos que no deseamos que
	// se repita
	_sound->setRepeat(false);

	// Indicamos el volumen al máximo
	// para todos los sonidos
	SoundMgr::setGlobalVolume(0.5f);

	return true;
}

void TestGame::OnFrame() {
	if (KeyDown(DIK_ESCAPE))
		PostQuitMessage(0);

	// Si mantenemos presionada la tecla S
	// y el sonido no se está reproduciendo
	// lo reproducimos de nuevo
	if (KeyPressed(DIK_S) && !_sound->isPlaying()) {
		_sound->stop();
		_sound->play();
	}

	// Si presionamos P pausaremos y
	// volveremos a reproducir la música
	if (KeyDown(DIK_P)) {
		if(_music->isPlaying()) {
			_music->pause();
		} else {
			_music->play();
		}
	}

	// Si presionamos la barra espaciadora
	// cortaremos la reproduccion de la música
	// y volveremos a iniciarla
	if (KeyDown(DIK_SPACE)) {
		if(_music->isPlaying()) {
			_music->stop();
		} else {
			_music->play();
		}
	}
}

bool TestGame::OnShutdown() {
	SoundMgr::closeSound(_music);
	SoundMgr::closeSound(_sound);

	return true;
}
 \endcode
 *
 *	@author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API Sound {
public:
	/**
	 *  Permite indicar un nombre para el sonido. Por defecto será la ruta y el nombre del archivo cargado
	 *	@param name cadena de caracteres terminada en \0 con el nombre del sonido
	 */
	void setName(char *name) { strcpy_s(_name, 256, name); }

	/**
	 *  Devuelve el nombre del sonido
	 *	@return cadena de caracteres terminada en \0 con el nombre del sonido
	 */
	char *getName() { return _name; }

	/**
	 *  Reproduce el sonido
	 */
	void play() {
		if (!_isPlaying && _active) {
			_pSound->play();
			_isPlaying = true;
			if (_paused)
				setPosition(_position);
			else
				setPosition(0);
			_paused = false;
		}
	}

	/**
	 *  Para el sonido
	 */
	void stop() { _pSound->stop(); _paused = false; _isPlaying = false; }

	/**
	 *  Pausa el sonido
	 */
	void pause() {
		if (!_paused && _active) {
			_position = _pSound->getPosition();
			stop();
			_paused = true;
		}
	}

	/**
	 *  Permite indicar el volumen del sonido entre 0.0f y 1.0f
	 *  @param volume volumen del sonido
	 */
	void setVolume(float volume) { _pSound->setVolume(volume); }
	
	/**
	 *  Retorna el volumen del sonido entre 0.0f y 1.0f
	 *  @return volumen del sonido
	 */
	float getVolume() { return _pSound->getVolume(); }

	/**
	 *  Permite indicar el tono del sonido entre 0.5f y 2.0f (por defecto 1.0f)
	 *  @param pitch tono del sonido 
	 */
	void setPitchShift(float pitch) { _pSound->setPitchShift(pitch); }

	/**
	 *  Devuelve el tono del sonido entre 0.5f y 2.0f (por defecto 1.0f)
	 *  @return devuelve el tono del sonido 
	 */
	float getPitchShift() { return _pSound->getPitchShift(); }

	/**
	 *  Permite indicar si deseamos que el sonido se reproduzca indefinidamente
	 *  @param repeat define si deseamos que se repita indefinidamente el sonido
	 */
	void setRepeat(bool repeat) { _pSound->setRepeat(repeat); }

	/**
	 *  Retorna si deseamos que el sonido se reproduzca indefinidamente
	 *  @return retorna si deseamos que se repita indefinidamente el sonido
	 */
	bool getRepeat() { return _pSound->getRepeat(); }

	/**
	 *  Devuelve la longitud del sonido
	 *  @return retorna la longitud del sonido
	 */
	int getLength() { return _pSound->getLength(); }

	/**
	 *  Devuelve la posición que se está reproduciendo del sonido
	 *  @return retorna la posición que se está reproduciendo del sonido
	 */
	int getPosition() { return _pSound->getPosition(); }

	/**
	 *  Indica la posición desde la cual se debe reproducir del sonido
	 *  @param pos la posición que a reproducir del sonido
	 */
	void setPosition(int pos) { _pSound->setPosition(pos); }

	/**
	 *  Permite indicar el balance entre los parlantes izquierdo y derecho. Debe ser un rango entre -1.0f y 1.0f (por defecto 0.0f)
	 *  @param pan balance entre los parlantes izquierdo y derecho (-1.0f y 1.0f)
	 */
	void setPan(float pan) { _pSound->setPan(pan); }

	/**
	 *  Devuelve el balance entre los parlantes izquierdo y derecho. Debe ser un rango entre -1.0f y 1.0f (por defecto 0.0f)
	 *  @return retorna el balance entre los parlantes izquierdo y derecho (-1.0f y 1.0f)
	 */
	float getPan() { return _pSound->getPan(); }

	/**
	 *  Inicializa el sonido a cero (puede tardar más en el caso de algunos sonidos)
	 */
	void reset() { _pSound->reset(); }

	/**
	 *  Devuelve si el sonido se está reproduciendo o no
	 *  @return devuelve true si el sonido se está reproduciendo y false en caso contrario.
	 */
	bool isPlaying() { return _pSound->isPlaying(); }

private:
	void setSoundActive(bool active) { _active = active; }

	Sound(audiere::OutputStreamPtr &pSound){ _pSound = pSound; _position = 0; _paused = false; _isPlaying = false; _pSound->ref(); _active = true; }
	~Sound(){  _name[0] = '\0'; }

	audiere::OutputStreamPtr _pSound;
	int _position;
	bool _paused;
	bool _isPlaying;
	static bool _active;
	
	char _name[256];

	friend class SoundMgr;
};

}

#endif // _ZAKSOUND_H_
