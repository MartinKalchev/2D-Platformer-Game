// AnimatedTexture.cpp                                             //
// Extends the Texture class' functionality to handle animations   //
// Uses the Texture class' spritesheet constructor                 //
//                                                                 //
#include "AnimatedTexture.h"

namespace QuickSDL
{

	AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir)
		: Texture(filename, x, y, w, h)
	{
		mTimer = Timer::Instance();
		mInput = InputManager::Instance();

		mStartX = x;
		mStartY = y;

		mFrameCount = frameCount;
		mAnimationSpeed = animationSpeed;
		mTimePerFrame = mAnimationSpeed / mFrameCount;
		mAnimationTimer = 0.0f;

		mAnimationDirection = animationDir;

		mAnimationDone = false;

		mWrapMode = loop;


		flipType = SDL_FLIP_NONE;

	}

	AnimatedTexture::~AnimatedTexture()
	{
		mInput = NULL;
	}

	void AnimatedTexture::WrapMode(WRAP_MODE mode)
	{
		mWrapMode = mode;
	}


	void AnimatedTexture::ResetAnimation()
	{
		mAnimationTimer = 0.0f;
		mAnimationDone = false;
	}

	bool AnimatedTexture::isAnimating()
	{
		return !mAnimationDone;
	}

	void AnimatedTexture::Update()
	{
		if (!mAnimationDone)
		{
			mAnimationTimer += mTimer->DeltaTime();

			if (mAnimationTimer >= mAnimationSpeed)
			{
				//Only loop if the wrap mode is loop
				if (mWrapMode == loop)
					mAnimationTimer -= mAnimationSpeed;
				else
				{
					mAnimationDone = true;
					mAnimationTimer = mAnimationSpeed - mTimePerFrame;
				}
			}

			if (mAnimationDirection == horizontal)
				mClipRect.x = mStartX + (int)(mAnimationTimer / mTimePerFrame) * mWidth;
			else
				mClipRect.y = mStartY + (int)(mAnimationTimer / mTimePerFrame) * mHeight;
		}
	}


	void AnimatedTexture::Render()
	{
		Vector2 pos = Pos(world);
		Vector2 scale = Scale(world);

		//Centers the texture on the texture's world position so that its position is not the top left corner
		mRenderRect.x = (int)(pos.x - mWidth * scale.x * 0.5f);
		mRenderRect.y = (int)(pos.y - mHeight * scale.y * 0.5f);

		//Scales the width and height according to the scale of the GameEntity
		mRenderRect.w = (int)(mWidth * scale.x);
		mRenderRect.h = (int)(mHeight * scale.y);


		if (mInput->KeyDown(SDL_SCANCODE_LEFT))
		{
			flipType = SDL_FLIP_HORIZONTAL;
		}
		else if (mInput->KeyDown(SDL_SCANCODE_RIGHT))
		{
			flipType = SDL_FLIP_NONE;
		}

		mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(world), flipType);

	}
}