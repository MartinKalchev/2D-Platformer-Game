#ifndef _LEVEL_H
#define _LEVEL_H
#include "InputManager.h"
#include "PlaySideBar.h"
#include "Player.h"
using namespace QuickSDL;

class Level : public GameEntity
{
public:

	enum LEVEL_STATES { running, finished, gameOver };

private:
	Timer* mTimer;
	PlaySideBar* mSideBar;

	//Current stage
	int mStage;
	bool stageStarted;

	float labelTimer;

	Texture* stageLabel;
	Scoreboard* stageNumber;
	float stageLabelOnScreen;
	float stageLabelOffScreen;

	Player* mPlayer;
	bool PlayerHit;
	float PlayerRespawnDelay;
	float PlayerRespawnTimer;
	float RespawnLabelOnScreen;

	Texture* gameOverLabel;
	bool mGameOver;
	float gameOverDelay;
	float gameOverTimer;
	float gameOverLabelOnScreen;

	LEVEL_STATES currentState;

private:

	void StartStage();
	void HandleStartLabels();
	void HandleCollisions();
	void HandlePlayerDeath();

public:
	Level(int stage, PlaySideBar* sideBar, Player* player);
	~Level();

	//Returns the state of the level
	LEVEL_STATES State();

	void Update();
	void Render();
};


#endif

