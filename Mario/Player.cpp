#include "Player.h"

Player::Player()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mVisible = false;
	mAnimating = true;

	mScore = 0;
	mLives = 2;

	mMario = new AnimatedTexture("Assets/mario_walking.png", 0, 0, 32, 64, 4, 1.0f, AnimatedTexture::horizontal);

	mMario->Parent(this);
	mMario->Pos(VEC2_ZERO);
	mMario->WrapMode(AnimatedTexture::loop);

	mMoveSpeed = 150.0f;
	mMoveBoundsX = Vector2(0.0f, Graphics::Instance()->SCREEN_WIDTH);

	marioDying = new AnimatedTexture("Assets/mario_walking.png", 194, 96, 32, 35, 1, 1.0f, AnimatedTexture::horizontal);
	marioDying->Parent(this);
	marioDying->Pos(VEC2_ZERO);
	marioDying->WrapMode(AnimatedTexture::once);


}

Player::~Player()
{
	mTimer = NULL;
	mInput = NULL;

	delete mMario;
	mMario = NULL;

	delete marioDying;
	marioDying = NULL;

}


void Player::Movement()
{
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT))
	{
		Translate(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime());
		mMario->Update();
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT))
	{
		Translate(-VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime());
		mMario->Update();
	}
	else if (mInput->KeyDown(SDL_SCANCODE_UP))
	{
		Translate(-VEC2_UP * mMoveSpeed * mTimer->DeltaTime());
	}

	Vector2 pos = Pos(local);
	if (pos.x < mMoveBoundsX.x)
		pos.x = mMoveBoundsX.x;
	else if (pos.x > mMoveBoundsX.y)
		pos.x = mMoveBoundsX.y;

	Pos(pos);
}

void Player::Visible(bool visible)
{
	mVisible = visible;
}

bool Player::isAnimating()
{
	return mAnimating;
}

int Player::Score()
{
	return mScore;
}

int Player::Lives()
{
	return mLives;
}

void Player::AddScore(int change)
{
	mScore += change;
}

void Player::WasHit()
{
	mLives--;
	marioDying->ResetAnimation();
	mAnimating = true;
}

void Player::Update()
{
	if (mAnimating)
	{
		marioDying->Update();
		mAnimating = marioDying->isAnimating();
	}
	else
	{
		if (Active())
		{
			Movement();
		}
	}
}

void Player::Render()
{
	if (mVisible)
	{
		if (mAnimating)
		{
			marioDying->Render();
		}
		else
		{
			mMario->Render();
		}
	}
}