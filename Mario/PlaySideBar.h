#ifndef _PLAYSIDEBAR_H
#define _PLAYSIDEBAR_H
#include "Timer.h"
#include "Scoreboard.h"

using namespace QuickSDL;

class PlaySideBar : public GameEntity
{
private:
	Timer* mTimer;
	Texture* mBackground;

	Texture* mHighScoreLabel;
	Scoreboard* mHighScoreBoard;

	Texture* mPlayerOneLabel;
	Scoreboard* mPlayerOneScore;

	static const int MAX_MARIO_LIVES = 3;
	GameEntity* mMarios;
	Texture* mLivesLabel;
	Texture* mMarioTextures[MAX_MARIO_LIVES];
	Scoreboard* mTotalLivesLabel;
	int totalLives;


public:
	PlaySideBar();
	~PlaySideBar();

	void SetHighScore(int score);
	void SetPlayerScore(int score);
	void setLives(int lives);

	void Update();
	void Render();
};

#endif

