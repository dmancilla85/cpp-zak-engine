#ifndef _Particle_H_
#define _Particle_H_

#include "MathUtil.h"
#include "Sprite.h"
#include "Entity2D.h"

namespace zak {

class ZAKENGINE_API Particle : public Sprite {

	private:

	public:
		DWORD	_dwColor,_dwStartColor;
		char	*_pdwColor;
		char	*_pdwStartColor;
		char	*_pdwTemp;

		float	_rotSpeed;

		float	_windX;
		float	_windY;

		float	_fRedInterpolation;
		float	_fGreenInterpolation;
		float	_fBlueInterpolation;
		float	_fAlphaInterpolation;
		
		float	_startSizeX;
		float	_startSizeY;
		float	_sizeInterpolationX;
		float	_sizeInterpolationY;

		float	_fTimeAccum;

		float	_fLifeTime;

		bool	_bIsDead;

		float	_speedX;
		float	_speedY;

		float	_precalcSin;
		float	_precalcCos;

		void Update(float fTimeBetweenFrames);
//		void Draw(float fTimeBetweenFrames);

	Particle(){
		_rotSpeed = 0.0f;
		_fLifeTime = 0.0f;
		_bIsDead = false;
		_pdwColor = (char*)&_dwColor;
		_pdwStartColor = (char*)&_dwStartColor;
		
		_fRedInterpolation=0.0f;
		_fGreenInterpolation=0.0f;
		_fBlueInterpolation=0.0f;
		_fAlphaInterpolation=0.0f;

		_sizeInterpolationX=0.0f;
		_sizeInterpolationY=0.0f;
		
		_fTimeAccum = 0.0f;

		_speedX = 0.0f;
		_speedY = 0.0f;

		_windX = 0.0f;
		_windY = 0.0f;
	};
	~Particle(){};
};

/**
 *  Clase que define sistemas de partículas.
 *  Ejemplo de uso:
\code
;Archivo particleSystem.ini
[PARTICLESYSTEM]
Sprite = "data/graphics/particle.spr"
;Animation = "data/graphics/example.ani"
MaxParticles = 150
Frequency = 6.6
StartWidth = 10
StartHeight = 10
EndWidth = 50
EndHeight = 50
StartColor = 4294910207
EndColor = 16777215
LifeTime = 1000.0
LifeTimeNoise = 0.0
RotationSpeed = 0.0
RotationSpeedNoise = 0.02
Speed = 0.02
SpeedNoise = 0.001
Direction = 0.0
DirectionNoise = 360.0
Wind = 0.0
WindDirection = 90.0
\endcode

\code
bool TestGame::OnInit() {
 	if(!_particleSystem.Load("data/graphics/particleSystem.ini"))
		return false;
}
void TestGame::OnFrame() {
	_particleSystem.Update((float)_fpsMeter.GetDT());
}

void TestGame::OnDraw() {
	_particleSystem.Draw();
}
\endcode

 \attention 
 *  Cantidad total de Particulas = Tiempo de vida / Frecuencia
 *
 *	@author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API ParticleSystem : public Entity2D {
	private:
		Particle **_prtParticles;

		DWORD	_dwStartColor;
		DWORD	_dwEndColor;

		char	*_pdwStartColor;
		char	*_pdwEndColor;

		float	_fLifeTime;
		float	_fFrequency;
		float	_fAccum;

		float	_startSizeX;
		float	_startSizeY;
		float	_endSizeX;
		float	_endSizeY;

		float	_fParticlesSpeed;
		float	_fParticlesAngle;
		float	_rotSpeed;
		float	_fAngleNoise;
		float	_fSpeedNoise;
		float	_fLifeNoise;
		float	_rotSpeedNoise;
		float	_wind;
		float	_windDirection;

		int		_iMaxParticles;
		int		_lastParticle;

		bool	_bSystemEnabled;

		bool	_bIsAllDead;

		Animation *_animation;

		void SwapLast(int which);

	public:
		/**
		 *  Permite definir la dirección del viento
		 *	@param windDirection dirección en grados centígrados
		 */
		void SetWindDirection(float windDirection) {
			_windDirection = windDirection;
		}

		/**
		 *  Permite definir la fuerza del viento
		 *	@param wind velocidad del viento
		 */
		void SetWind(float wind) {
			_wind = wind;
		}

		/**
		 *  Define el tamaño inicial de la partícula
		 *	@param sizeX ancho inicial
		 *	@param sizeY alto inicial
		 */
		void SetStartDim(float sizeX, float sizeY) {
			_startSizeX = sizeX;
			_startSizeY = sizeY;
		}

		/**
		 *  Define el tamaño final de la partícula
		 *	@param sizeX ancho final
		 *	@param sizeY alto final
		 */
		void SetEndDim(float sizeX, float sizeY) {
			_endSizeX = sizeX;
			_endSizeY = sizeY;
		}

		/**
		 *  Define el color inicial de la partícula
		 *	@param dwColor color inicial
		 */
		void SetStartColor(DWORD dwColor) {
			_dwStartColor = dwColor;
		} 

		/**
		 *  Define el color final de la partícula
		 *	@param dwColor color final
		 */
		void SetEndColor(DWORD dwColor) {
			_dwEndColor = dwColor;
		} 

		/**
		 *  Define el tiempo de vida de la partícula
		 *	@param fLifeTime tiempo de vida de la partícula
		 */
		void SetLifeTime (float fLifeTime) {
			_fLifeTime = fLifeTime;
		}

		/**
		 *  Define la velocidad de rotación de la partícula
		 *	@param rotSpeed velocidad de rotación de la partícula
		 */
		void SetRotationSpeed(float rotSpeed) {
			_rotSpeed = rotSpeed;
		}

		/**
		 *  Define el ruido en la velocidad de rotación de la partícula
		 *	@param rotSpeedNoise ruido en la velocidad de rotación de la partícula
		 */
		void SetRotationSpeedNoise(float rotSpeedNoise) {
			_rotSpeedNoise = rotSpeedNoise;
		}

		/**
		 *  Define la velocidad de traslación de las partículas
		 *	@param fParticlesSpeed velocidad de traslación de las partículas
		 */
		void SetParticlesSpeed (float fParticlesSpeed) {
			_fParticlesSpeed = fParticlesSpeed;
		}

		/**
		 *  Define la dirección en la que serán disparadas las partículas
		 *	@param fParticlesAngle dirección en grados centígrados
		 */
		void SetParticlesAngle (float fParticlesAngle) {
			_fParticlesAngle = fParticlesAngle;
		}

		/**
		 *  Define el ruido en el tiempo de vida de la partícula
		 *	@param fLifeNoise ruido en el tiempo de vida de la partícula
		 */
		void SetLifeNoise (float fLifeNoise) {
			_fLifeNoise  = fLifeNoise;
		}

		/**
		 *  Define el ruido en la velocidad de traslación de la partícula
		 *	@param fSpeedNoise ruido en la velocidad de traslación de la partícula
		 */
		void SetSpeedNoise (float fSpeedNoise) {
			_fSpeedNoise = fSpeedNoise;
		}

		/**
		 *  Define el ruido en la dirección de la partícula
		 *	@param fAngleNoise ruido en la dirección de traslación de la partícula
		 */
		void SetAngleNoise (float fAngleNoise) {
			_fAngleNoise = fAngleNoise;
		}

		/**
		 *  Define a todas las partículas como muertas
		 */
		void SetAllDead() {
			for (int i=0; i<_iMaxParticles; i++) 
				_prtParticles[i]->_bIsDead = true;
		}

		/**
		 *  Devuelve si el sistema está activado o no
		 *	@return devuelve true si el sistema está activado o false en caso contrario.
		 */
		bool IsEnableSystem() {
			return _bSystemEnabled;
		}

		/**
		 *  Activa el sistema de partículas
		 */
		void SetEnableSystem() {
			_bSystemEnabled = true;
		}

		/**
		 *  Desactiva el sistema de partículas
		 */
		void SetDisableSystem() {
			_bSystemEnabled = false;
		}

		/**
		 *  Dibuja el sistema de partículas
		 */
		virtual void Draw ();

		/**
		 *  Actualiza el sistema de partículas
		 *	@param fTimeBetweenFrames tiempo transcurrido entre iteración e iteración del bucle principal
		 */
		virtual void Update (float fTimeBetweenFrames);

		/**
		 *  Método virtual que activa el efecto (blendig y modulate) de las partículas
		 */
		virtual void EnableEffect() {		
			g_renderer.EnableState(ZAK_RENDER_STATE_BLENDFUNCBRIGHT);
			g_renderer.EnableModulate();
		}

		/**
		 *  Método virtual que desactiva el efecto (blendig y modulate) de las partículas
		 */
		virtual void DisableEffect() {
			g_renderer.DisableState(ZAK_RENDER_STATE_BLENDFUNCBRIGHT);
			g_renderer.DisableModulate();
		}

		/**
		 *  Carga el sistema de partículas a partir de un archivo .ini
		 *  @param particleIniFilename ruta y nombre del archivo a cargar
		 */
		bool Load(char *particleIniFilename);

		/**
		 *  Carga un sprite en particular y permite definir la cantidad total de partículas y la frecuencia mínima de salida
		 *  @param iMaxParticles cantidad total de partículas
		 *  @param fFrequency frecuencia mínima de nacimiento de partículas
		 *	@spriteFilename ruta y nombre del sprite a cargar
		 */
		bool Load(int iMaxParticles, float fFrequency, char *spriteFilename) {
			_fFrequency = fFrequency;
			_fAccum = 0.0f;

			if (iMaxParticles>0) {
				_iMaxParticles = iMaxParticles;
				_prtParticles = new Particle* [iMaxParticles];
				if (_prtParticles) {
					for (int i=0; i<_iMaxParticles; i++) {
						_prtParticles[i] = new Particle;
						
						if (!_prtParticles[i]) {
							delete [] _prtParticles;
							return false;
						}
						
						_prtParticles[i]->_bIsDead = true;
						if (!_prtParticles[i]->LoadIni(spriteFilename)){
							return false;
						}
						_prtParticles[i]->_dwColor = 0;
						_prtParticles[i]->_fLifeTime = 0;
						_prtParticles[i]->SetVisible(false);
					}
					return true;
				} else {
					return false;
				}
			} else {
				_prtParticles = NULL;
				_iMaxParticles = 0;
				return false;
			}
			return false;
		}

		/**
		 *  Permite liberar la memoria RAM y de video de la textura cargada
		 *	@return retorna true si todo salió bien y false en caso contrario
		 */
		bool Unload();

	/**
	 *  Constructor
	 */
	ParticleSystem() {
		_rotSpeedNoise = 0.0f;
		_rotSpeed = 0.0f;
		_startSizeX = 0.0f;
		_startSizeY = 0.0f;
		_endSizeX = 0.0f;
		_endSizeY = 0.0f;
		_fParticlesSpeed = 0.0f;
		_fParticlesAngle = 0.0f;
		_fSpeedNoise = 0;
		_fAngleNoise = 0;
		_dwStartColor = 0;
		_dwEndColor = 0;
		_fLifeTime = 0.0f;
		_fLifeNoise = 0.0f;
		_wind = 0.0f;
		_windDirection = 0.0f;
		_pdwStartColor = (char*)&_dwStartColor;
		_pdwEndColor = (char*)&_dwEndColor;
		_prtParticles = NULL;
		_bSystemEnabled = true;
		_bIsAllDead = true;
		_animation = NULL;
		_lastParticle = 0;
	};

	/**
	 *  Destructor
	 */
	~ParticleSystem() {
		if (_prtParticles) {
			for (int i=0; i<_iMaxParticles; i++) {
				if (_prtParticles[i])
					delete _prtParticles[i];
			}

			delete [] _prtParticles;
		}
	};
};


}
#endif //_Particle_H_