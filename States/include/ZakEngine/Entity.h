#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Defines.h"
#include "Renderer.h"
#include "ScriptMgr.h"
#include <string.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace zak {

/**
 *  Clase que contiene las propiedades comunes a todas las entidades.
 *	@author Juan Pablo "McKrackeN" Bettini
 */
class ZAKENGINE_API ENTITY : protected SupportScriptReferences {
protected:
	char _pszNombre[256];
	bool _bVisible;

	virtual void Release(){}
	virtual void Reset(){}

	friend class Renderer;

public:
	/**
	 *  Fija la propiedad de visibilidad de la entidad
	 *	@param bVis Variable booleana que indica si la entidad es visible o no
	 */
	void SetVisible(bool bVis) 
	{
		_bVisible=bVis; 
	};
	
	/**
	 *  Devuelve si la entidad es visible o no
	 *	@return Retorna verdadero en caso de ser visible y falso en caso contrario
	 */
	bool GetVisible(void)  //protege _bVisible
	{
		return _bVisible; 
	};

	/**
	 *  Fija el nombre de la entidad
	 *	@param pszName Cadena de caracteres conteniendo el nombre de la entidad
	 */
	void SetName(char * pszName) 
	{
		strcpy(_pszNombre, pszName);
	}

	/**
	 *  Devuelve el nombre de la entidad
	 *	@return Retorna una cadena de caracteres conteniendo el nombre de la entidad
	 */
	char *GetName () 
	{
		return _pszNombre;
	}

	static bool RegisterEntity (char *className=NULL) {
		char _className[100];

		if (className != NULL) {
			strcpy_s(_className, 100, className);
		} else {
			strcpy_s(_className, 100, "Entity");
			if (ScriptMgr::RegisterObjectType(_className, 0, 0) < 0)
				return false;
		}

		if (ScriptMgr::RegisterObjectBehaviour(_className, asBEHAVE_ADDREF,"void f()", asMETHOD(SupportScriptReferences, AddRef), asCALL_GENERIC) < 0)
			return false;
		if (ScriptMgr::RegisterObjectBehaviour(_className, asBEHAVE_RELEASE,"void f()", asMETHOD(SupportScriptReferences, Release), asCALL_GENERIC) < 0)
			return false;
		if (ScriptMgr::RegisterObjectMethod(_className, "void SetVisible(bool)",asMETHODPR(ENTITY, SetVisible,(bool), void),asCALL_THISCALL) < 0)
			return false;
		if (ScriptMgr::RegisterObjectMethod(_className, "bool GetVisible()",asMETHODPR(ENTITY, GetVisible, (void), bool),asCALL_THISCALL) < 0)
			return false;

		return true;
	}

	/**
	 *  Constructor
	 */
	ENTITY(){ 
		_bVisible = true; 
		_pszNombre[0]='\0'; 
		g_renderer.Register(this);
	};

	/**
	 *  Destructor
	 */
	~ENTITY(){  
		g_renderer.Unregister(this);
	};
};

}

#endif // _ENTITY_H_
