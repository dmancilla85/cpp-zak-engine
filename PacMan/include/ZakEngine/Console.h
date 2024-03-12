#pragma once

#include <string>
#include <map>
#include <vector>
#include "defines.h"
#include "messages.h"

#define MAX_CIRCULAR_LIST_SIZE	100

using namespace std;

typedef void(*pointerToFunc)(string);

namespace zak {

/**
 *  Clase que maneja los datos de la consola estilo Quake.
 *	@author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API Console {
public:
	static void Initialize();

	/**
	 *  Método que elimina los elementos de la consola
	 */
	static void Clear();

	/**
	 *  Método que permite logear texto en la consola.
	 *  @param str Cadena de caracteres a ser agregada a la consola.
	 */
	static void Trace(string str);

	/**
	 *  Método que permite logear texto en la consola.
	 *  @param str Cadena de caracteres a ser agregada a la consola con formato estilo printf.
	 */
	static void Trace(const char *str, ...);

	/**
	 *  Método que permite leer una línea de la consola. 
	 *  Al tratarse de una lista circular, la línea será eliminada. 
	 *  El método deberá ser invocado si la lista no está vacía.
	 *  @see IsEmpty()
	 *  @return Cadena de caracteres de la línea.
	 */
	static string ReadLine();

	/**
	 *  Devuelve si la lista está vacía o no.
	 *  @return Devuelve true si la lista está vacía y false en caso contrario.
	 */
	static bool IsEmpty() { return (_writeCursor == _readCursor); }

	/**
	 *  Permite ejecutar un comando pasado por parámetro.
	 *  @param input Línea de comandos a ser ejecutada.
	 *  @return Devuelve true si el comando fue ejecutado con éxito y false en caso contrario.
	 */
	static bool ExecuteCommand(string input);

	/**
	 *  Permite regisrar un nuevo comando con la función que deberá ejecutarse.
	 *  Esta función deberá cumplir con el prototipo: 
	 \code
	 void Funcion (string cadena);
	 \endcode
	 *  @param cmd Comando asignado para ejecutar la función
	 *  @param func Puntero a la función que deberá ser ejecutada al invocarse el comando
	 *  @return Devuelve true si el comando fue registrado con éxito y false en caso contrario.
	 */
	static bool RegisterCommand(string cmd, pointerToFunc func);

	static vector<string>	_lastCommands;
	static int				_lastCmdCursor;

private:
	static map<string, pointerToFunc>	_commands;
	static vector<string>				_vector;
	static string						_buffer[MAX_CIRCULAR_LIST_SIZE];
	static int							_readCursor;
	static int							_writeCursor;

	static void Help(string help);
	static void InsertString (string str);
};

} // end namespace
