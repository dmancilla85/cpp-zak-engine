#pragma once

#include "ZakEngine/defines.h"
#include "ScriptMgr.h"

namespace zak {

#define SCRIPT_MAX_CHARS_NAME	100

/**
 *  Clase que permite la comunicaci�n con n script
 *  Ejemplo de uso:
 \code
// Codigo C++
bool TestGame::OnInit() {
	int ap = 10;

	if (!ScriptMgr::StartUp())
		return false;
	
	// Registro la variable ap en el sistema de script
	int result = ScriptMgr::RegisterGlobalProperty("int ap",&ap);

	// Pido un nuevo script en el m�dulo ZakEngine y la secci�n namespace
	_script = ScriptMgr::AddScript("ZakEngine", "namespace");

	// Cargo el script
	_script->LoadScript("data/scripts/script.as");

	// Compilo el m�dulo
	if (!ScriptMgr::CompileModule("ZakEngine"))
		return false;

	// Pido el id de la funci�n
	_func = _script->GetFunctionIdByDecl("void DoSomething(int x)");
	
	// Preparo la funci�n
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
	 *  Devuelve el �ndice de la funci�n seg�n su prototipo
	 *  @param functionPrototype prototipo de la funci�n
	 *	@return �ndice de la funci�n
	 */ 
	int	 GetFunctionIdByDecl(char *functionPrototype);

	/**
	 *  Prepara la funci�n para ser ejecutada. 
	 *	\attention Debe ser invocado SIEMPRE antes de ejecutar una funci�n
	 *  @param functionPrototype prototipo de la funci�n
	 *	@return retorna true si todo sali� bien y false en caso contrario
	 */ 
	bool Prepare (char *functionPrototype);

	/**
	 *  Prepara la funci�n para ser ejecutada. 
	 *	\attention Debe ser invocado SIEMPRE antes de ejecutar una funci�n
	 *  @param funcId �ndice de la funci�n obtenido por medio del m�todo GetFunctionIdByDecl
	 *	@return retorna true si todo sali� bien y false en caso contrario
	 */ 
	bool Prepare (int funcId);

	/**
	 *  Ejecuta la funci�n preparada
	 */ 
	bool Execute();

	/**
	 *  Carga un script en texto
	 */ 
	bool LoadScript(char *filename);

	/**
	 *  Carga un script precompilado (binario)
	 *	\TODO Todav�a no est� desarrollado
	 */ 
	bool LoadByteCode(char *filename);

	/**
	 *  Ejecuta una sentencia pasada en una cadena de caracteres
	 *  @param script la sentencia a ejecutar
	 *  @return retorna true si no hubo errores y false en caso contrario
	 */
	bool ExecuteString(char *script);

	/**
	 *  Pasa un argumento del tipo DWord por par�metro a la funci�n a ser ejecutada.
	 *	\attention Este m�todo debe ser invocado luego de llamar a Prepare
	 *  @param iArg n�mero de argumento donde el primero es 0 
	 *	@param value valor a pasar por par�metro
	 *  @return retorna un valor negativo si la funci�n no pudo ser encontrada y 0 o positivo y todo sali� bien.
	 */ 
	int  SetArgDWord(int iArg, asDWORD value) { return _context->SetArgDWord(iArg, value); }

	/**
	 *  Pasa un argumento del tipo QWord por par�metro a la funci�n a ser ejecutada.
	 *	\attention Este m�todo debe ser invocado luego de llamar a Prepare
	 *  @param iArg n�mero de argumento donde el primero es 0 
	 *	@param value valor a pasar por par�metro
	 *  @return retorna un valor negativo si la funci�n no pudo ser encontrada y 0 o positivo y todo sali� bien.
	 */ 
	int  SetArgQWord(int iArg, asQWORD value) { return _context->SetArgQWord(iArg, value); }

	/**
	 *  Pasa un argumento del tipo float por par�metro a la funci�n a ser ejecutada.
	 *	\attention Este m�todo debe ser invocado luego de llamar a Prepare
	 *  @param iArg n�mero de argumento donde el primero es 0 
	 *	@param value valor a pasar por par�metro
	 *  @return retorna un valor negativo si la funci�n no pudo ser encontrada y 0 o positivo y todo sali� bien.
	 */ 
	int  SetArgFloat(int iArg, float value) { return _context->SetArgFloat(iArg, value); }

	/**
	 *  Pasa un argumento del tipo double por par�metro a la funci�n a ser ejecutada.
	 *	\attention Este m�todo debe ser invocado luego de llamar a Prepare
	 *  @param iArg n�mero de argumento donde el primero es 0 
	 *	@param value valor a pasar por par�metro
	 *  @return retorna un valor negativo si la funci�n no pudo ser encontrada y 0 o positivo y todo sali� bien.
	 */ 
	int  SetArgDouble(int iArg, double value){ return _context->SetArgDouble(iArg, value); }

	/**
	 *  Pasa un objeto por par�metro a la funci�n a ser ejecutada.
	 *	\attention Este m�todo debe ser invocado luego de llamar a Prepare
	 *  @param iArg n�mero de argumento donde el primero es 0 
	 *	@param value valor a pasar por par�metro
	 *  @return retorna un valor negativo si la funci�n no pudo ser encontrada y 0 o positivo y todo sali� bien.
	 */ 
	int  SetArgObject(int iArg, void *object){ return _context->SetArgObject(iArg, object); }

	/**
	 *  Retorna un valor del tipo DWord de la funci�n ejecutada anteriormente.
	 *  \attention Este valor es v�lido solo si la funci�n fue ejecutada satisfactoriamente
	 *  @return retorna el valor de la funci�n ejecutada.
	 */ 
	asDWORD GetReturnDWord() { return _context->GetReturnDWord(); }

	/**
	 *  Retorna un valor del tipo QWord de la funci�n ejecutada anteriormente.
	 *  \attention Este valor es v�lido solo si la funci�n fue ejecutada satisfactoriamente
	 *  @return retorna el valor de la funci�n ejecutada.
	 */ 
	asQWORD GetReturnQWord() { return _context->GetReturnQWord(); }

	/**
	 *  Retorna un valor del tipo float de la funci�n ejecutada anteriormente.
	 *  \attention Este valor es v�lido solo si la funci�n fue ejecutada satisfactoriamente
	 *  @return retorna el valor de la funci�n ejecutada.
	 */ 
	float GetReturnFloat() { return _context->GetReturnFloat(); }

	/**
	 *  Retorna un valor del tipo double de la funci�n ejecutada anteriormente.
	 *  \attention Este valor es v�lido solo si la funci�n fue ejecutada satisfactoriamente
	 *  @return retorna el valor de la funci�n ejecutada.
	 */ 
	double GetReturnDouble() { return _context->GetReturnDouble(); }

	/**
	 *  Retorna un objeto de la funci�n ejecutada anteriormente.
	 *  \attention Este valor es v�lido solo si la funci�n fue ejecutada satisfactoriamente
	 *  @return retorna el valor de la funci�n ejecutada.
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