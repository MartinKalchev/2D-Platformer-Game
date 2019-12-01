#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mBackgroundStage = new Texture("Assets/background.png", 0, 0, 1280, 720);
	mBackgroundStage->Parent(this);
	//mBackgroundStage->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mBackgroundStage->Pos(Vector2(0, 0));


	mSideBar = new PlaySideBar();
	mSideBar->Parent(this);
	mSideBar->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.05f));

	mStartLabel = new Texture("START", "Assets/nintendo.ttf", 38, { 150,120,0 });
	mStartLabel->Parent(this);
	mStartLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));


	mLevel = NULL;
	levelStartDelay = 1.0f;
	levelStarted = false;
	
	mPlayer = NULL;
	
}

PlayScreen::~PlayScreen()
{
	mTimer = NULL;
	mInput = NULL;

	delete mBackgroundStage;
	mBackgroundStage = NULL;

	delete mSideBar;
	mSideBar = NULL;

	//delete player;
	//player = NULL;

	delete mPlayer;
	mPlayer = NULL;

	delete mStartLabel;
	mStartLabel = NULL;

	delete mLevel;
	mLevel = NULL;

	delete mPlayer;
	mPlayer = NULL;
}

void PlayScreen::StartNextLevel()
{
	currentStage++;
	levelStartTimer = 0.0f;
	levelStarted = true;

	delete mLevel;
	mLevel = new Level(currentStage, mSideBar, mPlayer);
}

void PlayScreen::StartNewGame()
{
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.1f, Graphics::Instance()->SCREEN_HEIGHT * 0.73f));
	mPlayer->Active(false);

	mSideBar->SetHighScore(30000);
	mSideBar->setLives(mPlayer->Lives());
	mSideBar->SetPlayerScore(mPlayer->Score());

	gameStarted = false;
	levelStarted = false;
	levelStartTimer = 0.0f;
	currentStage = 0;
}


void PlayScreen::Update()
{
	if (gameStarted)
	{
		if (!levelStarted)
		{
			levelStartTimer += mTimer->DeltaTime();
			if (levelStartTimer >= levelStartDelay)
				StartNextLevel();
		}
	}
	else
	{
		gameStartTimer += mTimer->DeltaTime();
		if (gameStartTimer >= 3.0f)
			gameStarted = true;
	}

	if (gameStarted)
	{
		if(currentStage > 0)
			mSideBar->Update();

		if (levelStarted)
		{
			mLevel->Update();

			if (mLevel->State() == Level::finished)
				levelStarted = false;
		}

		mPlayer->Update();
	}
	
}

void PlayScreen::Render()
{
	mBackgroundStage->Render();
	mSideBar->Render();

	if (!gameStarted)
		mStartLabel->Render();

	if (gameStarted) 
	{
		if(levelStarted)
			mLevel->Render();

		mPlayer->Render();
	}
}