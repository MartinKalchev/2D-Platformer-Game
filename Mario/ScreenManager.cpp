#include "ScreenManager.h"


ScreenManager* ScreenManager::sInstance = NULL;

ScreenManager* ScreenManager::Instance()
{
	if (sInstance == NULL)
		sInstance = new ScreenManager();

	return sInstance;
}


void ScreenManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

ScreenManager::ScreenManager()
{
	mInput = InputManager::Instance();
	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();
	mSettingsScreen = new SettingsScreen();

	mCurrentScreen = start;
}

ScreenManager::~ScreenManager()
{
	mInput = NULL;

	delete mStartScreen;
	mStartScreen = NULL;

	delete mPlayScreen;
	mPlayScreen = NULL;

	delete mSettingsScreen;
	mSettingsScreen = NULL;
}

void ScreenManager::Update()
{
	switch (mCurrentScreen)
	{
	case start:
		mStartScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN) && mStartScreen->SelectedOption() == 0)
		{
			mCurrentScreen = play;
			mPlayScreen->StartNewGame();
		}
		else if (mInput->KeyPressed(SDL_SCANCODE_RETURN) && mStartScreen->SelectedOption() == 1)
		{
			mCurrentScreen = settings;
		}
		break;

	case play:
		mPlayScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
		{
			mCurrentScreen = start;
		}
		break;

	case settings:
		mSettingsScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
		{
			mCurrentScreen = start;
		}
		break;
	}
}

void ScreenManager::Render()
{
	switch (mCurrentScreen)
	{
	case start:
		mStartScreen->Render();
		break;

	case play:
		mPlayScreen->Render();
		break;

	case settings:
		mSettingsScreen->Render();
		break;
	}
}