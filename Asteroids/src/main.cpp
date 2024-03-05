#include "game.h"

#ifdef _DEBUG
#pragma comment (lib, "zakengined.lib")
#else
#pragma comment (lib, "zakengine.lib")
#endif

int main () {
	string desc;
	TestGame game;

	zak::Message::setLanguaje("Español");

	if (game.StartUp()) {
		game.Loop();
		if (!game.Shutdown()) {
			desc = zak::Message::getLastMessage();
			zak::Log.Trace(desc.c_str());
			return 1;
		}
	} else {
		desc = zak::Message::getLastMessage();
		zak::Log.Trace(desc.c_str());
		return 1;
	}
	
	return 0;
}