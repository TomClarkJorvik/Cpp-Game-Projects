#include "Game.h"
#include <iostream>

Game* game = nullptr;
int main(int argc, char* argv[]) {

	const int FPS = 5; 
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	

	game = new Game();

	game->init("BoiEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 396, 726, false);

	while (game->running()) {
		frameStart = SDL_GetTicks();


		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}