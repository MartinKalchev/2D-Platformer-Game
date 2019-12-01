#ifndef _SETTINGSSCREEN_H
#define _SETTINGSSCREEN_H
#include "InputManager.h"
#include "GameEntity.h"

using namespace QuickSDL;

class SettingsScreen : public GameEntity
{
private:


public:
	SettingsScreen();
	~SettingsScreen();

	void Update();
	void Render();
};

#endif


