#include <SDL.h>

using namespace std;

int main(int args, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* mRender = NULL;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Main SDL window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	mRender = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				isRunning = false;
			else if (ev.type == SDL_KEYDOWN)
			{
				switch (ev.key.keysym.sym)
				{
				case SDLK_r:
					SDL_SetRenderDrawColor(mRender, 255, 0, 0, 255);
					break;
				case SDLK_g:
					SDL_SetRenderDrawColor(mRender, 0, 255, 0, 255);
					break;
				case SDLK_b:
					SDL_SetRenderDrawColor(mRender, 0, 0, 255, 255);
					break;
				default:
					SDL_SetRenderDrawColor(mRender, 0, 0, 0, 0);
				}


			}
		}

		SDL_RenderClear(mRender);
		SDL_RenderPresent(mRender);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(mRender);
	window = NULL;
	mRender = NULL;
	SDL_Quit();

	return 0;
}