#include "TextureManager.h"


SDL_Texture* TextureManager::LoadTexture(const char* filePath)
{
	return IMG_LoadTexture(Game::renderer, filePath);
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
