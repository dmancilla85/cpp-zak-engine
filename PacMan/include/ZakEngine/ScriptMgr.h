#ifndef _SCRIPTMGR_H_
#define _SCRIPTMGR_H_

#include <stdio.h>
#include <io.h>
#include <set>
// AngelScript
#include "ZakEngine/Messages.h"
#include "ZakEngine/FileLog.h"
#include "ZakEngine/defines.h"
#include "ZakEngine/MathUtil.h"
#include "ZakEngine/Input.h"
#include "ZakEngine/list.h"
#include "angelscript.h"
#include "Script.h"

#ifdef _DEBUG
#pragma comment(lib, "angelscriptd.lib")
#else
#pragma comment(lib, "angelscript.lib")
#endif 

namespace zak { 

class ZAKENGINE_API SupportScriptReferences {
public:

	SupportScriptReferences() { _ref = 1; }
	~SupportScriptReferences(){}

	int _ref;

	void AddRef() {
		++_ref;
	}

	void Release() {
		if (--_ref == 0)
			delete this;
	}
};

class Script;

/**
 *  Manager de scripts desarrollados en AngelScript
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
 \attention
 Para m�s informaci�n referirse a la ayuda de AngelScript
 *
 *  @author Juan Pablo "McKrackeN" Bettini
 */ 

class ZAKENGINE_API ScriptMgr
{ 
public:

	/**
	 *  Inicializa el motor de scripting
	 */
	static bool StartUp();

	/**
	 *  Apaga el motor de scripting
	 */
	static void Shutdown();

	/**
	 *  Registra una propiedad global
	 *  @param szDecl declaraci�n de la propiedad global
	 *  @param var puntero a la variable que se desea registrar
	 *  @return retorna un valor negativo en caso de error y 0 o positivo en caso contrario
	 */
	static int RegisterGlobalProperty(char *szDecl, void* var) 
	{ 
		return _asEngine->RegisterGlobalProperty(szDecl, var); 
	}

	/**
	 *  Registra una funci�n global
	 *  @param szDecl declaraci�n de la funci�n global
	 *  @param funcPointer puntero a la funci�n que se desea registrar 
	 *  @param callConv convenci�n de invocaci�n (recomiendo leer la documentaci�n de AngelScript para mayor informaci�n)
	 *  @return retorna un valor negativo en caso de error y 0 o positivo en caso contrario
	 */
	static int RegisterGlobalFunction(char *szDecl, asUPtr funcPointer, asDWORD callConv) 
	{ 
		return _asEngine->RegisterGlobalFunction(szDecl, funcPointer, callConv); 
	}

	/**
	 *  Registra un tipo de objeto para poder ser utilizado en el script
	 *  @param szClassName nombre de la clase como debe ser utilizado en el script
	 *  @param iSize tama�o en memoria (en bytes) del objeto 
	 *  @param flags debe ser uno de los valores soportados por el motor de script (leer documentaci�n de AngelScript)
	 *  @return retorna un valor negativo en caso de error y 0 o positivo en caso contrario
	 */
	static int RegisterObjectType (const char *szClassName, int iSize, asDWORD flags) 
	{ 
		return _asEngine->RegisterObjectType(szClassName, iSize, flags); 
	}

	/**
	 *  Registra un propiedad de un objeto ya registrado en el script para que pueda ser accedido desde el mismo
	 *  @param szClassName nombre de la clase como debe ser utilizada en el script
	 *  @param szPropertyDecl declaraci�n de la propiedad
	 *  @param byteOffset el offset desde el puntero del objeto donde se aloja la propiedad (para m�s informaci�n referirse a la documentaci�n de AngelScript)
	 *  @return retorna un valor negativo en caso de error y 0 o positivo en caso contrario
	 */
	static int RegisterObjectProperty (const char *szClassName, const char *szPropertyDecl, int byteOffset) 
	{ 
		return _asEngine->RegisterObjectProperty(szClassName, szPropertyDecl, byteOffset); 
	}

	/**
	 *  Registra un m�todo de un objeto ya registrado en el script para que pueda ser accedido desde el mismo
	 *  @param szClassName nombre de la clase como debe ser utilizada en el script
	 *  @param szDecl declaraci�n del m�todo
	 *  @param funcPointer puntero al m�todo
	 *  @param callConv convenci�n de invocaci�n del m�todo (referirse a la documentaci�n de AngelScript)
	 *  @return retorna un valor negativo en caso de error y 0 o positivo en caso contrario
	 */
	static int RegisterObjectMethod(const char *szClassName, const char *szDecl, asUPtr funcPointer, asDWORD callConv) 
	{
		return _asEngine->RegisterObjectMethod(szClassName, szDecl, funcPointer, callConv); 
	}

	/**
	 *  Registra el compotamiento de un objeto (invocaci�n de constructor, destructor, operadores, etc).
	 *  @param szClassName nombre de la clase como debe ser utilizada en el script
	 *  @param behaviour flags de comportamiento (referirse a la documentaci�n de AngelScript)
	 *  @param szDeclaration declaraci�n de la funci�n a invocar
	 *  @param funcPointer puntero a la funci�n
	 *  @param callConv convenci�n de invocaci�n del m�todo (referirse a la documentaci�n de AngelScript)
	 *  @return retorna un valor negativo en caso de error y 0 o positivo en caso contrario
	 */
	static int RegisterObjectBehaviour(const char *szClassName, asDWORD behaviour, const char *szDeclaration, asUPtr funcPointer, asDWORD callConv) 
	{
		return _asEngine->RegisterObjectBehaviour(szClassName, behaviour, szDeclaration, funcPointer, callConv);
	}

	/**
	 *  Agrega un nuevo script al motor
	 *  @param szModule nombre del m�dulo al que pertenece
	 *  @param szSection secci�n dentro del m�dulo (parecido a un namespace)
	 *  @return retorna el script creado. En caso de haber alg�n error, retornar� NULL.
	 */
	static Script*	AddScript(char *szModule, char *szSection);

	/**
	 *  Remueve un script del motor
	 *  @param script puntero al script a remover
	 *  @return retorna true si el script fue removido con �xito y false en caso contrario.
	 */
	static bool		RemoveScript(Script *script);

	/**
	 *  Elimina la lista de scripts
	 *  @return retorna true si la lista fue eliminada con �xito y false en caso contrario.
	 */
	static bool		ClearScriptList();

	/**
	 *  Compila el m�dulo pasado por par�metro
	 *  \attention Un modulo debe compilarse una vez que se agregaron y cargaron todos los Scripts en �l. Una vez compilado un m�dulo, no se podr�n agregar y compilar nuevos Scripts en �l.
	 *  @param szModule nombre del m�dulo a compilar
	 *  @return retorna true si el m�dulo pudo ser compilado correctamente y false en caso contrario
	 */
	static bool		CompileModule(char *szModule);

	/**
	 *  Ejecuta una sentencia pasada en una cadena de caracteres en un m�dulo determinado
	 *  @param szModule nombre del m�dulo en el cual ejecutar la sentencia
	 *  @param script la sentencia a ejecutar
	 *  @return retorna true si no hubo errores y false en caso contrario
	 */
	static bool		ExecuteString(char *szModule, char *script) { return ExecuteString(szModule, script, NULL); }

private: 
	static bool RegisterClasses();

	static void ConsoleTrace(string str) { Console::Trace(str); }
	static void ConsoleTrace(float var) { Console::Trace("%3.5f",var); }
	static void ConsoleTrace(double var) { Console::Trace("%3.5e",var); }
	static void ConsoleTrace(int var) { Console::Trace("%d",var); }
	static void ConsoleTrace(bool var) { (var?Console::Trace("true"):Console::Trace("false")); }
	static void ConsoleTrace(asUINT var) { Console::Trace("%u",var); }
	static void LogTrace(string str) { Log.Trace("%s\n", str.c_str()); }
	static void LogTrace(float var) { Log.Trace("%3.5f\n", var); }
	static void LogTrace(bool var) { (var?Log.Trace("true\n"):Log.Trace("false\n")); }
	static void LogTrace(double var) { Log.Trace("%3.5e\n", var); }
	static void LogTrace(int var) { Log.Trace("%d\n", var); }
	static void LogTrace(asUINT var) { Log.Trace("%u\n", var); }

	static float scriptRadToDegree(float angle);
	static float scriptDegreeToRad(float angle);

	static BYTE scriptKeyDown(BYTE key);
	static BYTE scriptKeyUp(BYTE key);
	static BYTE scriptKeyPressed(BYTE key);

	static BYTE scriptMousePress(BYTE btn);
	static bool scriptMouseClick(BYTE btn);
	static long scriptMouseRelPos(BYTE btn);
	static long scriptMouseAbsPos(BYTE btn);
	static long scriptMouseWorldPos(BYTE btn);
	static float scriptMouseRelPosf(BYTE btn);
	static float scriptMouseAbsPosf(BYTE btn);
	static float scriptMouseWorldPosf(BYTE btn);

	static long scriptJoystickPos(int devNum, int axis);
	static long scriptJoystickRot(int devNum, int axis);
	static float scriptJoystickPosf(int devNum, int axis); 
	static float scriptJoystickRotf(int devNum, int axis);
	static BYTE scriptJoystickButtons(int devNum, int button);
	static int scriptJoystickCount();

	static void ConsoleExecute(string arg);
	static void ConsoleExecuteM(string arg);
	static void ConsoleGet(string arg);

	static void ConstructIntArray(vector<int> *self);
	static void ConstructIntArray(int length, vector<int> *self);
	static void DestructIntArray(vector<int> *self);

	static void ConstructFloatArray(vector<float> *self);
	static void ConstructFloatArray(int length, vector<float> *self);
	static void DestructFloatArray(vector<float> *self);

	static bool LoadScript (char *szFilename, char *szModule, char *szSection);
	static bool LoadScript (char *szFilename, string &script, string &dir);

	static bool LoadByteCode (char *szFilename); // TODO
	static bool SaveByteCode (char *szFilename); // TODO

	static int  ProcessInclude (string &script, string &dir);

	static asIScriptContext* CreateContext() { return _asEngine->CreateContext(); }

	static int ReleaseContext(asIScriptContext *gsContext) { return gsContext->Release(); }
	static int Prepare(asIScriptContext *asContext, int iFunctionId) { return asContext->Prepare(iFunctionId); }
	static int Execute (asIScriptContext *asContext) { return asContext->Execute(); }
	static bool ExecuteString (char *szModule, char *script, asIScriptContext **asContext, asDWORD flags=0); 

	static int GetFuncIDByDecl(char *szModule, char *szFuncDecl) { return _asEngine->GetFunctionIDByDecl(szModule, szFuncDecl); }
	static const char *GetFuncDeclaration(int funcId) { return _asEngine->GetFunctionDeclaration(funcId);}

	static void MessageCallback(const asSMessageInfo *msg, void *param);

	static asIScriptEngine	*_asEngine;
	static List<Script*>	_list;
	static set<string>		_includedScripts;


	friend class Script;
};

} // end namespace 

#endif // _SCRIPTMGR_H_