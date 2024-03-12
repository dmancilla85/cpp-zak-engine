#pragma once

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "defines.h"


#define PI				3.1415926535897932384626433832795
#define DegreeToRad(n)	n*0.017453292519943295769236907684886
#define RadToDegree(n)	n*57.295779513082320876798154814105
#define ZAK_MAX_RAND	180000

namespace zak {

/**
 *  Clase que contiene m�todos para distintos c�lculos como
 *  por ejemplo senos y cosenos a partir de tablas o el c�lculo
 *  de la distancia entre dos puntos.
 *	@author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API MathUtil {

public:
	/**
	 *  Devuelve el arcotangente del �ngulo pasado por par�mtro
	 *	@param tan tangente del �ngulo
	 *	@return valor del arcotangente
	 */
	static float ATan(float tan);

	/**
	 *  Devuelve el arcocoseno del �ngulo pasado por par�mtro
	 *	@param cos coseno del �ngulo
	 *	@return valor del arcocoseno 
	 */
	static float ACos(float cos);

	/**
	 *  Devuelve el arcoseno del �ngulo pasado por par�mtro
	 *	@param sin seno del �ngulo
	 *	@return valor del arcoseno 
	 */
	static float ASin(float sin);

	/**
	 *  Devuelve el seno del �ngulo pasado por par�mtro
	 *	@param degree �ngulo en grados 
	 *	@return valor del seno del �ngulo dado
	 */
	static float Sin(float degree);

	/**
	 *  Devuelve el coseno del �ngulo pasado por par�mtro
	 *	@param degree �ngulo en grados 
	 *	@return valor del coseno del �ngulo dado
	 */
	static float Cos(float degree);

	/**
	 *  Devuelve la tangente del �ngulo pasado por par�mtro
	 *	@param degree �ngulo en grados 
	 *	@return valor de la tangente del �ngulo dado
	 */
	static float Tan(float degree);

	/**
	 *  Devuelve el seno y el coseno del �ngulo pasado por par�mtro
	 *	@param degree �ngulo en grados cent�grados
	 *	@param sine devuelve el seno del �ngulo
	 *	@param cosine devuelve el coseno del �ngulo
	 */
	static void SinCos(float degree, float *sine, float *cosine);

	/**
	 *  Devuelve un n�mero aleatorio
	 *	Ejemplo de uso:
	 \code
		// Devuelve un n�mero del 0 al 9
		int rnd = MathUtil::Random()%10;

		// Devuelve un n�mero del 1 al 10
		int rnd1 = MathUtil::Random()%10+1;

		// Devuelve un n�mero del 10 al 19
		int rnd2 = MathUtil::Random()%10+10;
	 \endcode
	 *	@return devuelve un n�mero aleatorio
	 */
	static int Random() {
		_randIndex++;

		if (_randIndex >= ZAK_MAX_RAND) {
			_randIndex = 0;
		}

		return _rand[_randIndex];
	}

	/**
	 *  Devuelve la distancia al cuadrado (m�s r�pida) entre dos puntos
	 *	@param x1 Coordenada x de la posici�n del punto 1
	 *	@param y1 Coordenada y de la posici�n del punto 1
	 *	@param x2 Coordenada x de la posici�n del punto 2
	 *	@param y2 Coordenada y de la posici�n del punto 2
	 *	@return Distancia al cuadrado entre los dos puntos
	 */
	static float DistanceQuad (float x1, float y1, float x2, float y2) { return ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)); }

	/**
	 *  Devuelve la distancia entre dos puntos
	 *	@param x1 Coordenada x de la posici�n del punto 1
	 *	@param y1 Coordenada y de la posici�n del punto 1
	 *	@param x2 Coordenada x de la posici�n del punto 2
	 *	@param y2 Coordenada y de la posici�n del punto 2
	 *	@return Distancia entre los dos puntos
	 */
	static float Distance	  (float x1, float y1, float x2, float y2) { return sqrt(((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))); }

	/**
	 *  Redondea un n�mero flotante
	 *	@param num N�mero que se desea redondear
	 *	@return Redondeo del n�mero
	 */
	static float Round (float num);

private:
	static bool Initialize();
	static void Shutdown() {
		if (_rand)
			delete [] _rand;
	}

	static void SinCosCalc(float degree, float *sine, float *cosine);
	static float _sin[360];
	static float _cos[360];
	static float _tan[360];
	static int *_rand;
	static int _randIndex;

	friend class Game;
};

};