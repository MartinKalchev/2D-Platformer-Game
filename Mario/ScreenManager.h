#ifndef _SCREENMANAGER_H
#define _SCREENMANAGER_H
#include "StartScreen.h"
#include "PlayScreen.h"
#include "SettingsScreen.h"

class ScreenManager
{
private:
	//Enum to switch between the screens
	enum SCREENS { start, play, settings };

	static ScreenManager* sInstance;

	InputManager* mInput;
	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;
	SettingsScreen* mSettingsScreen;

	SCREENS mCurrentScreen;
public:

	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();
};
#endif


