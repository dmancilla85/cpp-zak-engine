#ifndef _ZAKSOUNDMGR_H_
#define _ZAKSOUNDMGR_H_

#include <vector>
#include "FileLog.h"
#include "Messages.h"
#include "Defines.h"
#include "Sound.h"
#include "audiere.h"
#include "list.h"
#include "console.h"

#pragma comment(lib, "audiere.lib")

using namespace std;

namespace zak {

enum SOUND_TYPE {
	SNDTYPE_SOUND=0,
	SNDTYPE_MUSIC=1
};

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
class ZAKENGINE_API SoundMgr {
public:

	/**
	 *  Inicializa el controlador de sonido
	 *	@return retorna true si todo salió bien y false en caso contrario.
	 */
	static bool openDevice();

	/**
	 *  Abre un nuevo sonido
	 *	@param filename nombre del archivo a abrir
	 *	@param stream si deseamos que se reproduzca por streaming o no
	 *  @param type Tipo del sonido (efecto sonoro y música).
	 *	@return retorna un puntero al sonido cargado. En caso de error devuelve NULL.
	 */
	static Sound *openSound(char *filename, bool stream,SOUND_TYPE type=SNDTYPE_SOUND);

	/**
	 *  Destruye el sonido pasado por parámetro
	 *  @param sound sonido que se desea destruir
	 */
	static void closeSound(Sound *sound);

	/**
	 *  Permite indicar si el sonido está activo o no
	 *  @param active indicar si el sonido está activo o no
	 */
	static void setSoundActive(bool active) { _active = active; Sound::_active = active; }

	/**
	 *  Devuelve si el sonido está activo o no
	 *  @return devuelve true si el sonido está activo o false en caso contrario
	 */
	static bool getSoundActive() { return _active; }

	/**
	 *  Permite indicar el volumen global para todos los sonidos
	 *  @param volume volumen global de los sonidos (entre 0.0f y 1.0f)
	 */
	static void	setGlobalVolume(float volume);

	/**
	 *  Devuelve el volumen global para todos los sonidos
	 *  @return devuelve el volumen global de los sonidos (entre 0.0f y 1.0f)
	 */
	static float getGlobalVolume() { return _globalVolume; }

	/**
	 *  Permite indicar el volumen para los efectos sonoros
	 *  @param volume volumen de los sonidos (entre 0.0f y 1.0f)
	 */
	static void	setSoundVolume(float volume);

	/**
	 *  Devuelve el volumen de los efectos sonoros
	 *  @return devuelve el volumen de los efectos sonoros (entre 0.0f y 1.0f)
	 */
	static float getSoundVolume() { return _soundVolume; }

	/**
	 *  Permite indicar el volumen para la música
	 *  @param volume volumen de la música (entre 0.0f y 1.0f)
	 */
	static void	setMusicVolume(float volume);

	/**
	 *  Devuelve el volumen de la música
	 *  @return devuelve el volumen de la música (entre 0.0f y 1.0f)
	 */
	static float getMusicVolume() { return _musicVolume; }

private:
	static void logAudioDevices();

	static bool _active;
	static audiere::AudioDevicePtr *_pDevice;
	static List<Sound*> _musicList;
	static List<Sound*> _sndList;
	static float _soundVolume;
	static float _musicVolume;
	static float _globalVolume;

	friend class Game;
};


}

#endif // _ZAKSOUND_H_
