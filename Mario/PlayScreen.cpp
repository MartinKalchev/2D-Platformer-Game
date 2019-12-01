#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mCanvas = new GameEntity();
	mCanvas->Parent(this);
	mCanvas->Pos(Vector2(0, 0));

	CreateBackgroundCanvas();

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

	for (int i = 0; i < mBackgroundTextures.size(); i++)
	{
		delete mBackgroundTextures[i];
		mBackgroundTextures[i] = NULL;
	}

	delete mSideBar;
	mSideBar = NULL;

	//delete player;
	//player = NULL;

	delete mStartLabel;
	mStartLabel = NULL;

	delete mLevel;
	mLevel = NULL;

	delete mPlayer;
	mPlayer = NULL;

	delete mCanvas;
	mCanvas = NULL;
}

void PlayScreen::StartNextLevel()
{
	currentStage++;
	levelStartTimer = 0.0f;
	levelStarted = true;

	delete mLevel;
	mLevel = new Level(currentStage, mSideBar, mPlayer);
}

void PlayScreen::CreateBackgroundCanvas()
{
	mBackgroundCanvas = new GameEntity();
	mBackgroundCanvas->Parent(mCanvas);
	mBackgroundCanvas->Pos(Vector2(0, 0));

	const int nOfBackgrounds = 10; // TODO: Fix magic number
	for (int i = 0; i < nOfBackgrounds; i++)
	{
		Texture* currentTexture = new Texture("Assets/background.png", 0, 0, 1280, 720);
		currentTexture->Parent(mBackgroundCanvas);
		const float offset = (Graphics::Instance()->SCREEN_WIDTH) * i;
		currentTexture->Pos(Vector2((Graphics::Instance()->SCREEN_WIDTH * 0.5f) + offset, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

		mBackgroundTextures.push_back(currentTexture);
	}
}

void PlayScreen::StartNewGame()
{
	if (mPlayer != NULL)
	{
		delete mPlayer;
	}

	mPlayer = new Player();
	mPlayer->Parent(mCanvas);
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

		if (mPlayer->Pos().x >= Graphics::Instance()->SCREEN_WIDTH * 0.5f)
		{
			const float canvasX = -(mPlayer->Pos(local).x - (Graphics::Instance()->SCREEN_WIDTH * 0.5f));
			mCanvas->Pos(Vector2(canvasX, mCanvas->Pos(local).y));
			mPlayer->mMoveBoundsX = Vector2(abs(canvasX), Graphics::Instance()->SCREEN_WIDTH + abs(canvasX));
		}
	}
	
}

void PlayScreen::Render()
{
	mCanvas->Render();
	for (Texture* t : mBackgroundTextures)
	{
		t->Render();
	}
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