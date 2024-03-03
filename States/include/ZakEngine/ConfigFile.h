#ifndef _ZAKCONFIGFILE_H_
#define _ZAKCONFIGFILE_H_

#include <fstream>
#include <string.h>
#include <stdlib.h>
//#include <iostream>
#include "defines.h"

using namespace std;

#define ZAK_CFG_MAX_CHARACTERS			256

#define ZAK_CFG_START_SECTION_NAME		'['
#define ZAK_CFG_END_SECTION_NAME		']'
#define ZAK_CFG_EQUAL					'='
#define ZAK_CFG_COMMENT					';'
#define ZAK_CFG_STRING					'"'

namespace zak {

/**
 * Esta clase analiza gramaticalmente archivos '.ini'.
 * Ejemplo de uso:
 * \code
	; Este es un archivo con extensión .ini
	[SECCION] ; Los comentarios se escriben anteponiendo un ';'
	ValorInt = 50
	ValorFloat = 10.0
	Cadena = "Hola, Mundo!"
 * \endcode
 *
 * Código:
 * \code
	ConfigFile *parser = new ConfigFile();
	
	if (!parser->Load("ruta/archivo.ini")) {
		delete parser;
		return false;
	}

	int	    valor1 = parser->ReadInteger("SECCION", "ValorInt", 0);
	float	valor2 = parser->ReadFloat("SECCION", "ValorFloat", 0.0f);
	char	*cadena = parser->ReadString("SECCION", "Cadena", "\0");
 * \endcode
 *
 *	@author Juan Pablo "McKrackeN" Bettini
 */

class ZAKENGINE_API ConfigFile 
{
public:

	/**
	* Abre el archivo a analizar.
	* @param szFilename Nombre del archivo a analizar.
	* @return Retorna verdadero si la operación fue exitosa
	*/
	bool Load(const char* szFilename);

	/**
	* Lee un número entero del archivo analizado.
	* @param Sección de la cual buscar la opción
	* @param Opción a buscar
	* @param Valor por defecto en el caso de no encontrar la opción buscada
	* @return Retorna el valor encontrado o el valor por defecto en caso de haber algún error.
	*/
	int ReadInteger(const char *pszSection,
					const char *pszOption,
					int iDefaultValue);

	/**
	* Lee un número entero largo del archivo analizado.
	* @param Sección de la cual buscar la opción
	* @param Opción a buscar
	* @param Valor por defecto en el caso de no encontrar la opción buscada
	* @return Retorna el valor encontrado o el valor por defecto en caso de haber algún error.
	*/
	long ReadLong (const char *pszSection,
					const char *pszOption,
					long lDefaultValue);

	/**
	* Lee un número DWORD del archivo analizado.
	* @param Sección de la cual buscar la opción
	* @param Opción a buscar
	* @param Valor por defecto en el caso de no encontrar la opción buscada
	* @return Retorna el valor encontrado o el valor por defecto en caso de haber algún error.
	*/
	DWORD ReadDWord (const char *pszSection,
					const char *pszOption,
					DWORD DefaultValue);

	/**
	* Lee un número booleano del archivo analizado.
	* @param Sección de la cual buscar la opción
	* @param Opción a buscar
	* @param Valor por defecto en el caso de no encontrar la opción buscada
	* @return Retorna el valor encontrado o el valor por defecto en caso de haber algún error.
	*/
	bool ReadBoolean(const char *pszSection,
						const char *pszOption,
						bool bDefaultValue);

	/**
	* Lee un número decimal del archivo analizado.
	* @param Sección de la cual buscar la opción
	* @param Opción a buscar
	* @param Valor por defecto en el caso de no encontrar la opción buscada
	* @return Retorna el valor encontrado o el valor por defecto en caso de haber algún error.
	*/
	float ReadFloat(const char *pszSection,
					const char *pszOption,
					float fDefaultValue);

	/**
	* Lee una cadena de caracteres del archivo analizado.
	* @param Sección de la cual buscar la opción
	* @param Opción a buscar
	* @param Cadena de caraceteres por defecto en el caso de no encontrar la opción buscada
	* @return Retorna la cadena encontrada encontrado o el valor por defecto en caso de haber algún error.
	*/
	char *ReadString(const char *pszSection,
				        const char *pszOption,
				 		const char *pszDefaultValue);

	/**
	* Constructor.
	*/
  	ConfigFile();

	/**
	* Constructor.
	* @param Nombre del archivo a abrir.
	*/
	ConfigFile(const char *Filename);

	/**
	* Destructor.
	*/
	~ConfigFile();

private:
	ifstream    _ifs;

	char _szString[ZAK_CFG_MAX_CHARACTERS]; 
	
	// Deletes all the unneeded chars
	void deleteUnneeded(char *szString);

	// Search in file for a specific section
	void searchSection(const char *szSection);

	// Search a specific value in the file
	void searchValue(char *pszString, const char *szOption);
};

} // end namespace 

#endif // _CONFIGFILE_H_
