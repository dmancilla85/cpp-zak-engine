#include "TestGame.h"

using namespace zak;

//#define USING_DIRECTX81

#ifdef USING_DIRECTX81

#ifdef _DEBUG
#pragma comment (lib, "zakengine81d.lib")
#else
#pragma comment (lib, "zakengine81.lib")
#endif

#else

#ifdef _DEBUG
#pragma comment (lib, "zakengined.lib")
#else
#pragma comment (lib, "zakengine.lib")
#endif

#endif

int main () {
	string desc;
	TestGame game;
	GameConfig config;

	if (!config.Load("config.ini"))
		return false;

	if (game.StartUp(&config)) {
		game.Loop();
	} else {
		game.Shutdown();

		MessageBoxA(g_window.GetHWnd(),Log.GetLastMessage(),"Error",MB_ICONERROR|MB_OK);

		return 1;
	}

	if (!game.Shutdown()) {

		MessageBoxA(g_window.GetHWnd(),Log.GetLastMessage(),"Error",MB_ICONERROR|MB_OK);
		return 1;
	}
	
	return 0;
}