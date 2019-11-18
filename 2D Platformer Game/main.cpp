#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int screenWIDTH = 1280;
const int screenHEIGHT = 640;

SDL_Texture* LoadTexture(string filePath, SDL_Renderer* renderTarget) {

	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == NULL) {
		cout << "Error: " << SDL_GetError() << endl;
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	}
	SDL_FreeSurface(surface);

	return texture;
}

int main(int argc, char* argv[])
{
	int prevTime = 0;
	int currentTime = 0;
	float deltaTime = 0;
	float frameCounter = 0;
	float frameLimit = 0.20f;
	float moveSpeed = 300.f;
	int sizeOnScreen = 48;
	int textureWidth;
	int textureHeight;

	SDL_Window* window = nullptr;
	SDL_Renderer* mRender = nullptr;
	SDL_Texture* playerTex = nullptr;
	SDL_Rect positionRect;
	SDL_Rect cropRect;

	SDL_Init(SDL_INIT_VIDEO);
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		cout << "Error: " << IMG_GetError() << endl;
	}

	window = SDL_CreateWindow("Main SDL window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWIDTH, screenHEIGHT, SDL_WINDOW_SHOWN);
	mRender = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	playerTex = LoadTexture("assets/small_mario_walking.png", mRender);
	SDL_QueryTexture(playerTex, NULL, NULL, &textureWidth, &textureHeight);
	int framesX = 8, framesY = 1;
	int frameWidth = textureWidth / framesX;
	int frameHeight = textureHeight / framesY;
	
	positionRect.h = cropRect.h = frameHeight;
	positionRect.w = cropRect.w = frameWidth;
	positionRect.h = positionRect.w = 40;
	positionRect.x = 0;
	positionRect.y = 640 - positionRect.h;
	cropRect.y = 0;
	cropRect.x = frameWidth * 5;

	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;

		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				isRunning = false;
			else if (ev.type == SDL_KEYDOWN)
			{
				switch (ev.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					isRunning = false;
					SDL_Quit();
					break;

				case SDLK_RIGHT:
					positionRect.x += moveSpeed * deltaTime;
					cropRect.x = frameWidth * 5;
					if (frameCounter >= frameLimit * 3) {
						frameCounter = 0;
						cropRect.x = frameWidth * 5;
					}
					else if (frameCounter >= frameLimit * 2) {
						cropRect.x = frameWidth * 7;
					}
					else if (frameCounter >= frameLimit) {
						cropRect.x = frameWidth * 6;
					}
					break;

				case SDLK_LEFT:
					positionRect.x -= moveSpeed * deltaTime;
					cropRect.x = frameWidth * 2;
					if (frameCounter >= frameLimit * 3) {
						cropRect.x = frameWidth * 2;
						frameCounter = 0;
					}
					else if (frameCounter >= frameLimit * 2) {
						cropRect.x = 0;
					}
					else if (frameCounter >= frameLimit) {
						cropRect.x = frameWidth;
					}
					break;

				case SDLK_UP:					
					cropRect.x = frameWidth * 3;
					positionRect.y -= moveSpeed * deltaTime;
					break;
				}
			}
			else if (ev.type == SDL_KEYUP) {
				switch (ev.key.keysym.sym) {
				case SDLK_UP:
					positionRect.y = 640 - positionRect.h;
					cropRect.x = frameWidth * 4;
					break;
				case SDLK_LEFT:
					cropRect.x = frameWidth * 2;
					break;
				case SDLK_RIGHT:
					cropRect.x = frameWidth * 5;
					break;
				}
			}
		}

		frameCounter += deltaTime;

		SDL_RenderClear(mRender);
		SDL_RenderCopy(mRender, playerTex, &cropRect, &positionRect);
		SDL_RenderPresent(mRender);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(mRender);
	SDL_DestroyTexture(playerTex);
	window = nullptr;
	mRender = nullptr;
	playerTex = nullptr;
	IMG_Quit();
	SDL_Quit();

	return 0;
}
