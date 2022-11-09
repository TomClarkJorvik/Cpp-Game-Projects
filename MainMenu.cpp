#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* r)
{

	menuSrcRect.x = menuSrcRect.y = 0;
	menuDestRect.x = menuDestRect.y = 0;
	menuSrcRect.w = menuDestRect.w = 396;
	menuSrcRect.h = menuDestRect.h = 726;
	background = TextureManager::LoadTexture("assets/menuScreen.png");

	buttonSrcRect.x = buttonSrcRect.y = 0;
	buttonDestRect.x = 100;
	buttonDestRect.y = 430;
	buttonSrcRect.w = buttonDestRect.w = 198;
	buttonSrcRect.h = buttonDestRect.h = 165;

	buttonTexture = TextureManager::LoadTexture("assets/menuButton.png");

	renderer = r;

}

MainMenu::~MainMenu()
{
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(buttonTexture);
}

void MainMenu::Draw()
{
	SDL_RenderClear(renderer);

	TextureManager::Draw(background, menuSrcRect, menuDestRect);

	TextureManager::Draw(buttonTexture, buttonSrcRect, buttonDestRect);
	SDL_RenderPresent(renderer);


}

void MainMenu::Button()
{

}
