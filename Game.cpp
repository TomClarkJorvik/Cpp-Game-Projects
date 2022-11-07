#include "Game.h"
#include "GameState.h"
#include <iostream>


GameState* gameState;


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;


Game::Game()
{}
Game::~Game()
{}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems initialised." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created." << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			// sets to white
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created." << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}
	gameState = new GameState();


}
// todo : keybuffering
void Game::handleEvents()
{

	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_a:
			gameState->TakeAction('a');
			std::cout << "a\n";
			break;
		case SDLK_d:
			gameState->TakeAction('d');
			std::cout << "d\n";
			break;
		}
	default:
		break;
	}
}

void Game::update()
{

	if (gameState->Update()) {
		isRunning = false;
	}
	
}
void Game::render()
{
	SDL_RenderClear(renderer);

	gameState->Draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned." << std::endl;
}
