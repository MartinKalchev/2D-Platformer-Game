#include "PlaySideBar.h"


PlaySideBar::PlaySideBar()
{
	mTimer = Timer::Instance();

	mBackground = new Texture("Assets/sidebar.png");
	mBackground->Parent(this);
	mBackground->Pos(Vector2(45.0f, 10.0f));
	mBackground->Scale(Vector2(3.0f, 1.5f));

	mHighScoreLabel = new Texture("HIGHSCORE", "Assets/mario.ttf", 32, { 150, 120 , 0 });
	mHighScoreLabel->Parent(this);
	mHighScoreLabel->Pos(Vector2(-20.0f, 0.0f));

	mHighScoreBoard = new Scoreboard();
	mHighScoreBoard->Parent(this);
	mHighScoreBoard->Pos(Vector2(40.0f, 32.0f));

	mPlayerOneLabel = new Texture("PLAYER 1", "Assets/mario.ttf", 32, { 150, 120, 0 });
	mPlayerOneLabel->Parent(this);
	mPlayerOneLabel->Pos(Vector2(-500.0f, 0.0f));

	mPlayerOneScore = new Scoreboard();
	mPlayerOneScore->Parent(this);
	mPlayerOneScore->Pos(Vector2(-430.0f, 32.0f));


	mMarios = new GameEntity();
	mMarios->Parent(this);
	mMarios->Pos(Vector2(400.0f, 80.0f));

	mLivesLabel = new Texture("PLAYER LIVES: ", "Assets/mario.ttf", 32, { 150, 120, 0 });
	mLivesLabel->Parent(this);
	mLivesLabel->Pos(Vector2(300.0f, 0.0f));

	for (int i = 0; i < MAX_MARIO_LIVES; i++)
	{
		mMarioTextures[i] = new Texture("Assets/super-mario.png");
		mMarioTextures[i]->Parent(mMarios);
		mMarioTextures[i]->Pos(Vector2(35.0f * (i % 4), -80.0f));
	}

	mTotalLivesLabel = new Scoreboard();
	mTotalLivesLabel->Parent(mMarios);
	mTotalLivesLabel->Pos(Vector2(125.0f, -80.0f));

}

PlaySideBar::~PlaySideBar()
{
	mTimer = NULL;

	delete mBackground;
	mBackground = NULL;

	delete mHighScoreLabel;
	mHighScoreLabel = NULL;

	delete mHighScoreBoard;
	mHighScoreBoard = NULL;

	delete mPlayerOneLabel;
	mPlayerOneLabel = NULL;

	delete mPlayerOneScore;
	mPlayerOneScore = NULL;

	delete mMarios;
	mMarios = NULL;

	delete mLivesLabel;
	mLivesLabel = NULL;

	for (int i = 0; i < MAX_MARIO_LIVES; i++)
	{
		delete mMarioTextures[i];
		mMarioTextures[i] = NULL;
	}

	delete mTotalLivesLabel;
	mTotalLivesLabel = NULL;
}

// Access function for the score from the playSideBar class
void PlaySideBar::SetHighScore(int score)
{
	mHighScoreBoard->Score(score);
}

void PlaySideBar::SetPlayerScore(int score)
{
	mPlayerOneScore->Score(score);
}

void PlaySideBar::setLives(int lives)
{
	totalLives = lives;

	mTotalLivesLabel->Score(totalLives);
}

void PlaySideBar::Update()
{

}

void PlaySideBar::Render()
{
	mBackground->Render();

	mHighScoreLabel->Render();
	mHighScoreBoard->Render();

	mPlayerOneLabel->Render();
	mPlayerOneScore->Render();

	mLivesLabel->Render();

	for (int i = 0; i < MAX_MARIO_LIVES && i < totalLives; i++)
	{
		mMarioTextures[i]->Render();
	}

	mTotalLivesLabel->Render();
}


Vector2 PlaySideBar::GetDimensions()
{
	return mBackground->GetDimensions();
}

