#pragma once
#include "Game.h"

class GameObject
{
public:
	GameObject(const char* texturePath, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:
	int xpos;
	int ypos;

	SDL_Texture* objectTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};

