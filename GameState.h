#pragma once
#include "Game.h"
#include "TextureManager.h"
#include <random>

const int mapHeight = 20;
const int mapWidth = 10;

class GameState
{
public:
	GameState();
	~GameState();
	void TakeAction(char action);
	bool Update();
	void Draw();
	bool AddNewBlock();
	void GameOver();


	int* firstStatePtr;
	int rows = 20;
	int cols = 10;

	int score = 0;

private:

	SDL_Rect src, dest;
	SDL_Rect bgSrc, bgDest;

	SDL_Texture* yellow;
	SDL_Texture* red;
	SDL_Texture* orange;
	SDL_Texture* green;
	SDL_Texture* blue;
	SDL_Texture* pink;
	SDL_Texture* darkblue;
	SDL_Texture* purple;

	SDL_Texture* background;


	int currentBlock[4][2];
	int currentBlockColour;
	int state[20][10] = {
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0}
};
};

