#include "Player.h"

Player::Player()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mVisible = false;
	mAnimating = true;

	mScore = 0;
	mLives = 3;

	mMario = new AnimatedTexture("Assets/mario_walking.png", 0, 0, 32, 64, 4, 0.7f, AnimatedTexture::horizontal);
	mMario->Parent(this);
	mMario->Pos(VEC2_ZERO);
	mMario->WrapMode(AnimatedTexture::loop);

	mMoveSpeed = 300.0f;
	mMoveBoundsX = Vector2(0.0f, Graphics::Instance()->SCREEN_WIDTH);


	marioDying = new AnimatedTexture("Assets/mario_walking.png", 194, 96, 32, 35, 1, 1.0f, AnimatedTexture::horizontal);
	marioDying->Parent(this);
	marioDying->Pos(VEC2_ZERO);
	marioDying->WrapMode(AnimatedTexture::once);

	isWalking = false;
	isJumping = false;

	/*marioJumping = new AnimatedTexture("Assets/mario_walking.png", 160, 0, 32, 64, 1, 1.0f, AnimatedTexture::horizontal);
	marioJumping->Parent(this);
	marioJumping->Pos(VEC2_ZERO);
	marioJumping->WrapMode(AnimatedTexture::loop);*/
	marioJumpingRight = new Texture("Assets/mario_walking.png", 160, 0, 32, 64);
	marioJumpingRight->Parent(this);
	marioJumpingRight->Pos(VEC2_ZERO);

	marioJumpingLeft = new Texture("Assets/mario_walking_reversed.png", 672 - 192, 0, 32, 64);
	marioJumpingLeft->Parent(this);
	marioJumpingLeft->Pos(VEC2_ZERO);

	marioIdleLeft = new Texture("Assets/mario_walking_reversed.png", 672 - 32, 0, 32, 64);
	marioIdleLeft->Parent(this);
	marioIdleLeft->Pos(VEC2_ZERO);

	marioIdleRight = new Texture("Assets/mario_walking.png", 0, 0, 32, 64);
	marioIdleRight->Parent(this);
	marioIdleRight->Pos(VEC2_ZERO);
}

Player::~Player()
{
	mTimer = NULL;
	mInput = NULL;

	delete mMario;
	mMario = NULL;

	delete marioDying;
	marioDying = NULL;

	delete marioJumpingLeft;
	marioJumpingLeft = NULL;

	delete marioJumpingRight;
	marioJumpingRight = NULL;

	delete marioIdleLeft;
	marioIdleLeft = NULL;

	delete marioIdleRight;
	marioIdleRight = NULL;

}


void Player::Movement()
{
	/*if (mInput->KeyDown(SDL_SCANCODE_RIGHT) && mInput->KeyDown(SDL_SCANCODE_UP)) {
		isJumping = true;
		Translate(VEC2_UP_RIGHT * mMoveSpeed * mTimer->DeltaTime());
		direction = "right";
		
	}*/
	if (!isJumping && mInput->KeyDown(SDL_SCANCODE_RIGHT))
	{
		isWalking = true;
		Translate(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime());
		mMario->Update();
		direction = "right";
	}
	else if (!isJumping && mInput->KeyDown(SDL_SCANCODE_LEFT))
	{
		isWalking = true;
		Translate(-VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime());
		mMario->Update();
		direction = "left";
	}
	else if (mInput->KeyReleased(SDL_SCANCODE_LEFT) || mInput->KeyReleased(SDL_SCANCODE_RIGHT))
	{
		isWalking = false;
	}
	//For jumping
	else if (mInput->KeyDown(SDL_SCANCODE_UP))
	{
		isJumping = true;
		Translate(-VEC2_UP * mMoveSpeed * mTimer->DeltaTime());
	}
	/*else if (mInput->KeyReleased(SDL_SCANCODE_UP) && mInput->KeyReleased(SDL_SCANCODE_RIGHT))
	{
		Vector2 pos = Pos(local);
		isJumping = false;

		while (pos.y < Graphics::Instance()->SCREEN_HEIGHT * 0.73f)
		{
			Vector2 tempvect = VEC2_UP * mMoveSpeed * mTimer->DeltaTime();
			pos += tempvect;
			this->mPos.y = Graphics::Instance()->SCREEN_HEIGHT * 0.73f;
			Pos(pos);
		}
	}*/
	else if (mInput->KeyReleased(SDL_SCANCODE_UP))
	{
		Vector2 pos = Pos(local);
		isJumping = false;
		
		while (pos.y < Graphics::Instance()->SCREEN_HEIGHT * 0.73f)
		{
			Vector2 tempvect = VEC2_UP * mMoveSpeed * mTimer->DeltaTime();
			pos += tempvect;
			this->mPos.y = Graphics::Instance()->SCREEN_HEIGHT * 0.73f;
			Pos(pos);
		}
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

void Player::Animating(bool animating)
{
	mAnimating = animating;
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
	mLives--;;
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
			if (isWalking == true)
			{
				mMario->Render();
			}
			else if (isJumping == true)
			{
				direction == "left" ? marioJumpingLeft->Render() : marioJumpingRight->Render();
			}
			else
			{
				direction == "left" ? marioIdleLeft->Render() : marioIdleRight->Render();
			}
		}
	}
}