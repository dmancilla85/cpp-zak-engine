#ifndef _Engine_H_
#define _Engine_H_

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#pragma warning (disable : 4251)
#pragma warning (disable : 4996)

#ifdef ZAKENGINE_EXPORTS
#define ZAKENGINE_API __declspec(dllexport)		// Especifica clase para exportacion
#else
#define ZAKENGINE_API __declspec(dllimport)		// Especifica clase para importacion
#endif // ZAKENGINE_EXPORTS

#define ZAK_ENGINE_CLASS_NAME	L"ZakEngine"

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x800
#endif

#define ZAK_ENGINE_NAME			L"Zak Engine v1.0"
#define ZAK_ENGINE_LOGGER_HEADER "Zak Engine v1.0"

namespace zak {

extern HINSTANCE g_hInstance;

}

#endif // _ENGINE_H_
