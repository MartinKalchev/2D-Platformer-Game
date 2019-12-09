#ifndef _PLAYER_H
#define _PLAYER_H
#include "AnimatedTexture.h"
#include "InputManager.h"
using namespace QuickSDL;

class Player : public GameEntity
{
private:

	Timer* mTimer;
	InputManager* mInput;

	// if player is visible on screen
	bool mVisible;
	// if is animating
	bool mAnimating;


	int mScore;
	int mLives;

	AnimatedTexture* mMario;

	float mMoveSpeed;

	bool isWalking;
	bool isJumping;

	AnimatedTexture* marioDying;
	AnimatedTexture* marioJumping;
	Texture* marioIdle;

private:

	void Movement();

public:

	// min and max X the player can move between on the screen
	Vector2 mMoveBoundsX;

	Player();
	~Player();

	void Visible(bool visible);
	bool isAnimating();
	void Animating(bool animating);

	int Score();
	int Lives();

	void AddScore(int change);

	void WasHit();

	void Update();
	void Render();
};


#endif

