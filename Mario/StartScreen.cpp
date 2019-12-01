#include "StartScreen.h"


StartScreen::StartScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	// Top Bar Entities
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 80.0f));
	mPlayer1 = new Texture("PLAYER 1", "Assets/mario.ttf", 32, { 200, 0, 0 });
	mHighScore = new Texture("HIGHSCORE", "Assets/mario.ttf", 32, { 200, 0 ,0 });
	mPlayer2 = new Texture("PLAYER 2", "Assets/mario.ttf", 32, { 200, 0, 0 });

	mPlayerOneScore = new Scoreboard();
	mTopScore = new Scoreboard();
	mPlayerTwoScore = new Scoreboard();


	mPlayer1->Parent(mTopBar);
	mHighScore->Parent(mTopBar);
	mPlayer2->Parent(mTopBar);
	mPlayerOneScore->Parent(mTopBar);
	mTopScore->Parent(mTopBar);
	mPlayerTwoScore->Parent(mTopBar);


	mPlayer1->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.4f, 0.0f));
	mHighScore->Pos(Vector2(-4.0f, 0.0f));
	mPlayer2->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.4f, 0.0f));

	mPlayerOneScore->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.39f, 40.0f));
	mTopScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.05f, 40.0f));
	mPlayerTwoScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.4f, 40.0f));


	mTopBar->Parent(this);

	// Logo Entities
	mLogo = new Texture("Assets/mario_logo.png", 0, 0, 500, 200);
	mNintendo = new Texture("@ 1985 Nintendo", "Assets/nintendo.ttf", 24, { 200, 0, 0 });

	mNintendo->Parent(mLogo);

	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.34f));
	mNintendo->Pos(Vector2(130.0f, 120.0f));

	mLogo->Parent(this);

	// Player entities
	mOptions = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.55f));
	mPlay = new Texture("PLAY", "Assets/mario.ttf", 32, { 230, 230, 230 });
	mSettings = new Texture("SETTINGS", "Assets/mario.ttf", 32, { 230, 230, 230 });
	mCursor = new Texture("Assets/mario_cursor.png");


	mPlay->Parent(mOptions);
	mSettings->Parent(mOptions);
	mCursor->Parent(mPlay);


	mPlay->Pos(Vector2(0.0f, 25.0f));
	mSettings->Pos(Vector2(0.0f, 70.0f));
	mCursor->Pos(Vector2(100.0f, -5.0f));

	mOptions->Parent(this);

	mCursorStartPos = mCursor->Pos(local);
	mCursorOffset = Vector2(0.0f, 43.0f);
	mSelectedOption = 0;

	//Bottom Bar Entities
	mBotBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.7f));
	mRights = new Texture("ALL RIGHTS RESERVED", "Assets/mario.ttf", 32, { 230,230,230 });
	mRights->Parent(mBotBar);
	mRights->Pos(Vector2(0.0f, 140.0f));

	mBotBar->Parent(this);
}

StartScreen::~StartScreen()
{
	// Freeing top bar entities
	delete mTopBar;
	mTopBar = NULL;
	delete mPlayer1;
	mPlayer1 = NULL;
	delete mHighScore;
	mHighScore = NULL;
	delete mPlayer2;
	mPlayer2 = NULL;
	delete mPlayerOneScore;
	mPlayerOneScore = NULL;
	delete mTopScore;
	mTopScore = NULL;
	delete mPlayerTwoScore;
	mPlayerTwoScore = NULL;


	// Freeing Logo Entity
	delete mLogo;
	mLogo = NULL;
	delete mNintendo;
	mNintendo = NULL;

	// Freeing Player Entities
	delete mOptions;
	mOptions = NULL;
	delete mPlay;
	mPlay = NULL;
	delete mSettings;
	mSettings = NULL;
	delete mCursor;
	mCursor = NULL;

	//Freeing Bottom Bar Entities
	delete mBotBar;
	mBotBar = NULL;
	delete mRights;
	mRights = NULL;
}


int StartScreen::SelectedOption()
{
	return mSelectedOption;
}

void StartScreen::SelectOption(int change)
{
	mSelectedOption += change;

	if (mSelectedOption < 0)
		mSelectedOption = 1;
	else if (mSelectedOption > 1)
		mSelectedOption = 0;

	mCursor->Pos(mCursorStartPos + mCursorOffset * mSelectedOption);
}

void StartScreen::Update()
{
	if (mInput->KeyPressed(SDL_SCANCODE_DOWN))
		SelectOption(1);
	else if (mInput->KeyPressed(SDL_SCANCODE_UP))
		SelectOption(-1);
	else if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
		SDL_Quit();
}

void StartScreen::Render()
{
	mPlayer1->Render();
	mHighScore->Render();
	mPlayer2->Render();
	mPlayerOneScore->Render();
	mTopScore->Render();
	mPlayerTwoScore->Render();

	mLogo->Render();
	mNintendo->Render();

	mPlay->Render();
	mSettings->Render();
	mCursor->Render();

	mRights->Render();
}