#ifndef _CPUINFO_H_
#define _CPUINFO_H_

#include "defines.h"

namespace zak {

/**
 *  Estructura que contiene la información del CPU.
 *	@author Juan Pablo "McKrackeN" Bettini
 */
struct ZAKENGINE_API STCPUInfo {
	bool m_bSSE;			// Streaming SIMD Extensions
	bool m_bSSE2;			// Streaming SIMD Extensions 2
	bool m_b3DNOW;			// 3DNow! (vendor independent)
	bool m_bMMX;			// MMX Support
	char m_szName[48];		// CPU Name
	bool m_bExt;			// Extended features available
	bool m_bMMXEX;			// MMX Extended (AMD specific extensions)
	bool m_b3DNOWEX;		// 3DNow! Extended (AMD specific extensions)
	char m_szVendor[13];	// Vendor Name
};

/**
 *  Clase que toma la información de las capacidades del procesador.
 *	@author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API CPUInfo 
{
public:
	/**
	 *  Llena y devuelve una estructura del tipo STCPUInfo con la información del CPU actual.
	 *	@see STCPUInfo
	 *	@return Una estructura del tipo STCPUInfo
	 */
	STCPUInfo	GetCPUInfo();

	/**
	 *  Método que devuelve si el CPU soporta las rutinas SSE.
	 *	@return Devuelve verdadero en caso de soportar SSE y falso en caso contrario.
	 */
	bool		OSSupportSSE();

	/**
	 *  Constructor
	 */
	CPUInfo();

	/**
	 *  Destructor
	 */
	~CPUInfo();
protected:
	
private:

};

}

#endif // _CPUINFO_H_