#pragma once

#include "ZakEngine/defines.h"
#include "ScriptMgr.h"

namespace zak {

#define SCRIPT_MAX_CHARS_NAME	100

/**
 *  Clase que permite la comunicación con n script
 *  Ejemplo de uso:
 \code
// Codigo C++
bool TestGame::OnInit() {
	int ap = 10;

	if (!ScriptMgr::StartUp())
		return false;
	
	// Registro la variable ap en el sistema de script
	int result = ScriptMgr::RegisterGlobalProperty("int ap",&ap);

	// Pido un nuevo script en el módulo ZakEngine y la sección namespace
	_script = ScriptMgr::AddScript("ZakEngine", "namespace");

	// Cargo el script
	_script->LoadScript("data/scripts/script.as");

	// Compilo el módulo
	if (!ScriptMgr::CompileModule("ZakEngine"))
		return false;

	// Pido el id de la función
	_func = _script->GetFunctionIdByDecl("void DoSomething(int x)");
	
	// Preparo la función
	_script->Prepare(_func);

	// Paso al argumento 0 (el primero de tipo DWord) el valor 5
	_script->SetArgDWord(0,5);

	// Ejecuto el script
	_script->Execute();
}

bool TestGame::OnShutdown() {
	// Elimino la lista de scripts
	ScriptMgr::ClearScriptList();

	return true;
}
 \endcode
 \code
// Codigo en AngelScript

void DoSomething(int x) {
	ap = x;
}

 \endcode
 *  @author Juan Pablo "McKrackeN" Bettini
 */ 
class ZAKENGINE_API Script {
	friend class ScriptMgr;

public:

	/**
	 *  Devuelve el índice de la función según su prototipo
	 *  @param functionPrototype prototipo de la función
	 *	@return índice de la función
	 */ 
	int	 GetFunctionIdByDecl(char *functionPrototype);

	/**
	 *  Prepara la función para ser ejecutada. 
	 *	\attention Debe ser invocado SIEMPRE antes de ejecutar una función
	 *  @param functionPrototype prototipo de la función
	 *	@return retorna true si todo salió bien y false en caso contrario
	 */ 
	bool Prepare (char *functionPrototype);

	/**
	 *  Prepara la función para ser ejecutada. 
	 *	\attention Debe ser invocado SIEMPRE antes de ejecutar una función
	 *  @param funcId índice de la función obtenido por medio del método GetFunctionIdByDecl
	 *	@return retorna true si todo salió bien y false en caso contrario
	 */ 
	bool Prepare (int funcId);

	/**
	 *  Ejecuta la función preparada
	 */ 
	bool Execute();

	/**
	 *  Carga un script en texto
	 */ 
	bool LoadScript(char *filename);

	/**
	 *  Carga un script precompilado (binario)
	 *	\TODO Todavía no está desarrollado
	 */ 
	bool LoadByteCode(char *filename);

	/**
	 *  Ejecuta una sentencia pasada en una cadena de caracteres
	 *  @param script la sentencia a ejecutar
	 *  @return retorna true si no hubo errores y false en caso contrario
	 */
	bool ExecuteString(char *script);

	/**
	 *  Pasa un argumento del tipo DWord por parámetro a la función a ser ejecutada.
	 *	\attention Este método debe ser invocado luego de llamar a Prepare
	 *  @param iArg número de argumento donde el primero es 0 
	 *	@param value valor a pasar por parámetro
	 *  @return retorna un valor negativo si la función no pudo ser encontrada y 0 o positivo y todo salió bien.
	 */ 
	int  SetArgDWord(int iArg, asDWORD value) { return _context->SetArgDWord(iArg, value); }

	/**
	 *  Pasa un argumento del tipo QWord por parámetro a la función a ser ejecutada.
	 *	\attention Este método debe ser invocado luego de llamar a Prepare
	 *  @param iArg número de argumento donde el primero es 0 
	 *	@param value valor a pasar por parámetro
	 *  @return retorna un valor negativo si la función no pudo ser encontrada y 0 o positivo y todo salió bien.
	 */ 
	int  SetArgQWord(int iArg, asQWORD value) { return _context->SetArgQWord(iArg, value); }

	/**
	 *  Pasa un argumento del tipo float por parámetro a la función a ser ejecutada.
	 *	\attention Este método debe ser invocado luego de llamar a Prepare
	 *  @param iArg número de argumento donde el primero es 0 
	 *	@param value valor a pasar por parámetro
	 *  @return retorna un valor negativo si la función no pudo ser encontrada y 0 o positivo y todo salió bien.
	 */ 
	int  SetArgFloat(int iArg, float value) { return _context->SetArgFloat(iArg, value); }

	/**
	 *  Pasa un argumento del tipo double por parámetro a la función a ser ejecutada.
	 *	\attention Este método debe ser invocado luego de llamar a Prepare
	 *  @param iArg número de argumento donde el primero es 0 
	 *	@param value valor a pasar por parámetro
	 *  @return retorna un valor negativo si la función no pudo ser encontrada y 0 o positivo y todo salió bien.
	 */ 
	int  SetArgDouble(int iArg, double value){ return _context->SetArgDouble(iArg, value); }

	/**
	 *  Pasa un objeto por parámetro a la función a ser ejecutada.
	 *	\attention Este método debe ser invocado luego de llamar a Prepare
	 *  @param iArg número de argumento donde el primero es 0 
	 *	@param value valor a pasar por parámetro
	 *  @return retorna un valor negativo si la función no pudo ser encontrada y 0 o positivo y todo salió bien.
	 */ 
	int  SetArgObject(int iArg, void *object){ return _context->SetArgObject(iArg, object); }

	/**
	 *  Retorna un valor del tipo DWord de la función ejecutada anteriormente.
	 *  \attention Este valor es válido solo si la función fue ejecutada satisfactoriamente
	 *  @return retorna el valor de la función ejecutada.
	 */ 
	asDWORD GetReturnDWord() { return _context->GetReturnDWord(); }

	/**
	 *  Retorna un valor del tipo QWord de la función ejecutada anteriormente.
	 *  \attention Este valor es válido solo si la función fue ejecutada satisfactoriamente
	 *  @return retorna el valor de la función ejecutada.
	 */ 
	asQWORD GetReturnQWord() { return _context->GetReturnQWord(); }

	/**
	 *  Retorna un valor del tipo float de la función ejecutada anteriormente.
	 *  \attention Este valor es válido solo si la función fue ejecutada satisfactoriamente
	 *  @return retorna el valor de la función ejecutada.
	 */ 
	float GetReturnFloat() { return _context->GetReturnFloat(); }

	/**
	 *  Retorna un valor del tipo double de la función ejecutada anteriormente.
	 *  \attention Este valor es válido solo si la función fue ejecutada satisfactoriamente
	 *  @return retorna el valor de la función ejecutada.
	 */ 
	double GetReturnDouble() { return _context->GetReturnDouble(); }

	/**
	 *  Retorna un objeto de la función ejecutada anteriormente.
	 *  \attention Este valor es válido solo si la función fue ejecutada satisfactoriamente
	 *  @return retorna el valor de la función ejecutada.
	 */ 
	void *GetReturnObject() { return _context->GetReturnObject(); }

private:

	Script(char *moduleName, char *sectionName);
	~Script();

	char _moduleName[SCRIPT_MAX_CHARS_NAME];
	char _sectionName[SCRIPT_MAX_CHARS_NAME];

	asIScriptContext* _context;

	int	_currentFunc;


};

} // end namespace