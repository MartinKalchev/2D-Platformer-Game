#ifndef _PLAYER_H
#define _PLAYER_H
#include "AnimatedTexture.h"
#include "InputManager.h"
using namespace QuickSDL;
using namespace std;

class Player : public GameEntity
{
private:

	Timer* mTimer;
	InputManager* mInput;

	// if player is visible on screen
	bool mVisible;
	// if is animating
	bool mAnimating;
	bool isWalking;
	bool isJumping;

	string direction = "right";

	int mScore;
	int mLives;

	float mMoveSpeed;

	AnimatedTexture* mMario;
	AnimatedTexture* marioDying;
	//AnimatedTexture* marioJumping;
	Texture* marioJumpingLeft;
	Texture* marioJumpingRight;
	Texture* marioIdleLeft;
	Texture* marioIdleRight;

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

