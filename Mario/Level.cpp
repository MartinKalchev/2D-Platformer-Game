#include "Level.h"

Level::Level(int stage, PlaySideBar* sideBar, Player* player)
{
	mTimer = Timer::Instance();
	mSideBar = sideBar;

	mStage = stage;
	stageStarted = false;

	labelTimer = 0.0f;
	stageLabel = new Texture("LEVEL", "Assets/nintendo.ttf", 38, { 150,120,0 });
	stageLabel->Parent(this);
	stageLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	stageNumber = new Scoreboard({ 150,120,0 });
	stageNumber->Score(mStage);
	stageNumber->Parent(this);
	stageNumber->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.58f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	stageLabelOnScreen = 0.0f;
	stageLabelOffScreen = 1.5f;

	mPlayer = player;
	PlayerHit = false;
	PlayerRespawnDelay = 1.0f;
	PlayerRespawnTimer = 0.0f;
	RespawnLabelOnScreen = 2.0f;

	gameOverLabel = new Texture("GAME OVER", "Assets/nintendo.ttf", 38, { 150,120,0 });
	gameOverLabel->Parent(this);
	gameOverLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mGameOver = false;
	gameOverDelay = 5.0f;
	gameOverTimer = 0.0f;
	gameOverLabelOnScreen = 1.0f;

	currentState = running;
}

Level::~Level()
{
	mTimer = NULL;
	mSideBar = NULL;


	delete stageLabel;
	stageLabel = NULL;

	delete stageNumber;
	stageNumber = NULL;

	mPlayer = NULL;

	delete gameOverLabel;
	gameOverLabel = NULL;
}

void Level::StartStage()
{
	stageStarted = true;
}

void Level::HandleStartLabels()
{
	labelTimer += mTimer->DeltaTime();
	if (labelTimer >= stageLabelOffScreen)
	{
		if (mStage > 1)
			StartStage();
		else
		{
			StartStage();
			mPlayer->Active(true);
			mPlayer->Visible(true);
		}
	}
}

void Level::HandleCollisions()
{
	if (!PlayerHit)
	{
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_X))
		{
			mPlayer->WasHit();
			mSideBar->setLives(mPlayer->Lives());

			PlayerHit = true;
			PlayerRespawnTimer = 0.0f;
			mPlayer->Active(false);
		}
	}
}

void Level::HandlePlayerDeath()
{
	if (!mPlayer->isAnimating())
	{
		if (mPlayer->Lives() > 0)
		{
			if (PlayerRespawnTimer == 0.0f)
				mPlayer->Visible(false);

			PlayerRespawnTimer += mTimer->DeltaTime();

			if (PlayerRespawnTimer >= PlayerRespawnDelay)
			{
				mPlayer->Visible(true);
				mPlayer->Active(true);
				PlayerHit = false;
			}
		}
		else
		{
			if (gameOverTimer == 0.0f)
				mPlayer->Visible(false);

			gameOverTimer += mTimer->DeltaTime();
			if (gameOverTimer >= gameOverDelay)
			{
				currentState = gameOver;
			}
		}
	}
}

Level::LEVEL_STATES Level::State()
{
	return currentState;
}

void Level::Update()
{
	if (!stageStarted)
	{
		HandleStartLabels();
	}
	else
	{
		HandleCollisions();

		if (PlayerHit)
		{
			HandlePlayerDeath();
		}
		else
		{
			if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_N))
			{
				currentState = finished;
			}
		}
	}
}

void Level::Render()
{
	if (!stageStarted)
	{
		if (labelTimer > stageLabelOnScreen&& labelTimer < stageLabelOffScreen)
		{
			stageLabel->Render();
			stageNumber->Render();
		}
	}
	else
	{
		if (PlayerHit)
		{
			if (gameOverTimer >= gameOverLabelOnScreen)
				gameOverLabel->Render();
		}
	}

	
}