#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H
#include "Timer.h"
//#include "AnimatedTexture.h"
#include "Level.h"

using namespace QuickSDL;

class PlayScreen : public GameEntity
{
private:

	Timer* mTimer;
	InputManager* mInput;
	std::vector<Texture*> mBackgroundTextures;
	PlaySideBar* mSideBar;
	GameEntity* mCanvas;
	GameEntity* mBackgroundCanvas;

	//AnimatedTexture* player;
	Texture* mStartLabel;

	float levelStartTimer;
	float levelStartDelay;
	bool gameStarted;
	float gameStartTimer;

	Level* mLevel;
	bool levelStarted;
	int currentStage;
	 
	Player* mPlayer;

private:
	//Loads the next level
	void StartNextLevel();
	void CreateBackgroundCanvas();

public:
	PlayScreen();
	~PlayScreen();

	//Called from the ScreenManager
	void StartNewGame();

	void Update();
	void Render();
};

#endif

