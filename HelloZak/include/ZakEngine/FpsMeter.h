#ifndef _FPSMeter_H_
#define _FPSMeter_H_

#include "Defines.h"

namespace zak {
/**
*	Clase que manipula el timer del sistema
*	@author Juan Pablo "McKrackeN" Bettini
*/
class ZAKENGINE_API FPSMeter {
	private:
		double		_fTimeBetweenFrames;
		double		_MeasureFpsSample;
		int			_iFPS;
		long int	_IFrameCounter;
		double		_lockFps;
		double		_accum;

		LARGE_INTEGER _performanceCount1;
		LARGE_INTEGER _performanceCount2;
		LARGE_INTEGER _frequency;

	public:

		/**
		*	Inicializa el timer
		*/
		void	FirstMeasure();

		/**
		*	Método invocado para medir el tiempo entre iteraciones
		*/
		void	Measure();

		/**
		*	Devuelve el tiempo transcurrido entre iteraciones.
		*	@return Número decimal (double) que indica el tiempo transcurrido (1000.0 equivale a 1 segundo).
		*/
		double	GetDT();

		/**
		*	Devuelve los cuadros por segundos a los que está corriendo la aplicación.
		*	@return Número entero que indica los cuadros por segundos a los que está corriendo la aplicación.
		*/
		int		GetFps();

		/**
		*	Método que permite indicar si deseamos 'trabar' los cuadros por segundo.
		*	@param Número decimal (double) que indica los cuadros por segundos a los que deseamos trabar.
		*/
		void	SetLockFPS(double fps);

		/**
		*	Constructor
		*/
		FPSMeter(){	_lockFps = 0; };

		/**
		*	Destructor
		*/
		~FPSMeter(){};
};

}

#endif //_FPSMeter_H_