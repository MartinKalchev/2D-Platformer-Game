#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include "Scoreboard.h"

using namespace QuickSDL;

class StartScreen : public GameEntity
{
private:

	Timer* mTimer;
	InputManager* mInput;

	// Top Bar Entities
	GameEntity* mTopBar;
	Texture* mPlayer1;
	Texture* mHighScore;
	Texture* mPlayer2;
	Scoreboard* mPlayerOneScore;
	Scoreboard* mTopScore;
	Scoreboard* mPlayerTwoScore;

	// Logo Entities
	Texture* mLogo;
	Texture* mNintendo;

	//Player Entities
	GameEntity* mOptions;
	Texture* mPlay;
	Texture* mSettings;
	Texture* mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffset;
	int mSelectedOption;

	// Bottom Bar
	GameEntity* mBotBar;
	Texture* mRights;

public:

	StartScreen();
	~StartScreen();

	int SelectedOption();

	void SelectOption(int change);
	void Update();
	void Render();
};

#endif

