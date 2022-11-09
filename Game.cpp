#include "Game.h"
#include "GameState.h"
#include "MainMenu.h"
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

void Game::mainMenu() {
	bool inMainMenu = true;
	MainMenu menu = MainMenu(renderer);

	while (inMainMenu) {

		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			inMainMenu = false;
			isRunning = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT &&
				event.button.x >= menu.buttonDestRect.x &&
				event.button.x <= (menu.buttonDestRect.x + menu.buttonDestRect.w) &&
				event.button.y >= menu.buttonDestRect.y &&
				event.button.y <= (menu.buttonDestRect.y + menu.buttonDestRect.h)) {

				inMainMenu = false;
			}
			break;
		}
		menu.Draw();
	}


}

void Game::showScoreScreen() {
	isRunning = false;
}



void Game::handleEvents()
{

	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (keystates[SDL_SCANCODE_LEFT]){
			gameState->TakeAction('l');

		}
		else if (keystates[SDL_SCANCODE_RIGHT])
			gameState->TakeAction('r');


	default:
		break;
	}
}

void Game::update()
{

	if (gameState->Update()) {
		showScoreScreen();
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
