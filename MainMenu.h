#pragma once
#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.h"

class MainMenu
{
public:
	MainMenu(SDL_Renderer* r);
	~MainMenu();
	void Draw();

	SDL_Rect buttonSrcRect, buttonDestRect;

private:
	SDL_Rect menuSrcRect, menuDestRect;
	SDL_Texture* background;
	SDL_Texture* buttonTexture;
	SDL_Renderer* renderer;
};

