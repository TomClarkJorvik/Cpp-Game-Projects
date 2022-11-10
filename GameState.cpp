#include "GameState.h"
#include <iostream>

GameState::GameState() {
	firstStatePtr = *state;
	yellow = TextureManager::LoadTexture("assets/yellow.png"); //1
	red = TextureManager::LoadTexture("assets/red.png"); //2
	orange = TextureManager::LoadTexture("assets/orange.png"); //3
	green = TextureManager::LoadTexture("assets/green.png"); //4
	blue = TextureManager::LoadTexture("assets/blue.png"); //5
	pink = TextureManager::LoadTexture("assets/pink.png"); //6
	darkblue = TextureManager::LoadTexture("assets/darkblue.png"); //7
	purple = TextureManager::LoadTexture("assets/purple.png"); //8

	src.x = src.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;
	dest.x = dest.y = 0;

	background = TextureManager::LoadTexture("assets/background.png");

	bgSrc.x = bgSrc.y = 0;
	bgDest.x = bgDest.y = 0;
	bgSrc.w = bgDest.w = 396;
	bgSrc.h = bgDest.h = 726;

	AddNewBlock();
}

GameState::~GameState() {
	SDL_DestroyTexture(yellow);
	SDL_DestroyTexture(red);
	SDL_DestroyTexture(orange);
	SDL_DestroyTexture(green);
	SDL_DestroyTexture(blue);
	SDL_DestroyTexture(pink);
	SDL_DestroyTexture(darkblue);
	SDL_DestroyTexture(purple);
	SDL_DestroyTexture(background);
}

// a or d to move left or right
void GameState::TakeAction(char action) {
	bool canMove = true;

	switch (action) {
	// move block left
	case 'l':
		for (int i = 0; i < 4; i++) {
			if (state[currentBlock->coords[i][1]][currentBlock->coords[i][0]-1] != 0 || currentBlock->coords[i][0] == 0) {
				canMove = false;
			}
		}
		if (canMove) {
			currentBlock->pivotPoint[0] -= 1;
			for (int i = 0; i < 4; i++) {
				currentBlock->coords[i][0] -= 1;
			}
		}
		break;
	case 'r':
		for (int i = 0; i < 4; i++) {
			if (state[currentBlock->coords[i][1]][currentBlock->coords[i][0] + 1] != 0 || currentBlock->coords[i][0] == (cols - 1)) {
				canMove = false;
			}
		}
		if (canMove) {
			currentBlock->pivotPoint[0] += 1;
			for (int i = 0; i < 4; i++) {
				currentBlock->coords[i][0] += 1;
			}
		}
		break;
	case 'e':
		// clockwise rotation
		if (currentBlock->blockColour != 1) {
			bool canRotate = true;
			int targetXs[4] = { 0,0,0,0 };
			int targetYs[4] = { 0,0,0,0 };
			for (int i = 0; i < 4; i++) {
				// x
				targetXs[i] = currentBlock->pivotPoint[0] + currentBlock->pivotPoint[1] - currentBlock->coords[i][1];
				// y
				targetYs[i] = currentBlock->pivotPoint[1] - currentBlock->pivotPoint[0] + currentBlock->coords[i][0];

				if (state[targetYs[i]][targetXs[i]] != 0 || targetXs[i] <0 || targetYs[i] < 0 || targetXs[i] > (cols -1) || targetYs[i] > (rows-1)) {
					canRotate = false;
				}
			}
			if (canRotate) {
				for (int i = 0; i < 4; i++) {
					// x
					currentBlock->coords[i][0] = targetXs[i];
					// y
					currentBlock->coords[i][1] = targetYs[i];
				}
			}
		}

		break;

	case 'q':
		// counter clockwise rotation
		if (currentBlock->blockColour != 1) {
			bool canRotate = true;
			int targetXs[4] = { 0,0,0,0 };
			int targetYs[4] = { 0,0,0,0 };
			for (int i = 0; i < 4; i++) {
				// x
				targetXs[i] = currentBlock->pivotPoint[0] - currentBlock->pivotPoint[1] + currentBlock->coords[i][1];
				// y
				targetYs[i] = currentBlock->pivotPoint[1] + currentBlock->pivotPoint[0] - currentBlock->coords[i][0];

				if (state[targetYs[i]][targetXs[i]] != 0 || targetXs[i] <0 || targetYs[i] < 0 || targetXs[i] > (cols - 1) || targetYs[i] > (rows - 1)) {
					canRotate = false;
				}
			}
			if (canRotate) {
				for (int i = 0; i < 4; i++) {
					// x
					currentBlock->coords[i][0] = targetXs[i];
					// y
					currentBlock->coords[i][1] = targetYs[i];
				}
			}
		}

		break;


	}

}

// returns true if the block cant be placed (game over)
// if block can be moved down, move it down by 1
// else, make it a part of the game state.
//			check if a row is made.
bool GameState::Update() {

	bool canMove = true;
	// moves the current block down by 1 row. If there is a block underneath it, then it stops.
	for (int i = 0; i < 4; i++) {
		if (state[currentBlock->coords[i][1]+1][currentBlock->coords[i][0]] != 0 || currentBlock->coords[i][1]== (rows - 1)) {
			canMove = false;
		}
	}
	if (canMove) {
		currentBlock->pivotPoint[1] += 1;
		for (int i = 0; i < 4; i++) {
			currentBlock->coords[i][1] += 1;
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			state[currentBlock->coords[i][1]][currentBlock->coords[i][0]] = currentBlock->blockColour;
		}



		if (AddNewBlock()) {
			return true;
		}
	}
	bool rowMade;
	for (int i = 0; i < rows; i++) {
		rowMade = true;
		for (int j = 0; j < cols; j++) {
			if (state[i][j] == 0) {
				rowMade = false;
				break;
			}
		}
		if (rowMade) {
			// move all rows above down by one, make top row empty.
			if (i != 0) {
				for (int row = i; row > 1; row--) {
					for (int col = 0; col < cols; col++) {
						state[row][col] = state[row - 1][col];
					}
				}
			}
			for (int col = 0; col < cols; col++) {
				state[0][col] = 0;
			}
			score++;
		}
	}

	return false;
}


// draws the game state
void GameState::Draw() {

	TextureManager::Draw(background, bgSrc, bgDest);

	int type = 0;
	for (int row = 0; row < mapHeight; row++) {
		for (int col = 0; col < mapWidth; col++) {
			type = *(firstStatePtr + (10 * row) + col);


			dest.x = col * 33 + 33;
			dest.y = row * 33 + 33;

			switch (type) {
			case 0:
				break;
			case 1:
				TextureManager::Draw(yellow, src, dest);
				break;
			case 2:
				TextureManager::Draw(red, src, dest);
				break;
			case 3:
				TextureManager::Draw(orange, src, dest);
				break;
			case 4:
				TextureManager::Draw(green, src, dest);
				break;
			case 5:
				TextureManager::Draw(blue, src, dest);
				break;
			case 6:
				TextureManager::Draw(pink, src, dest);
				break;
			case 7:
				TextureManager::Draw(darkblue, src, dest);
				break;
			case 8:
				TextureManager::Draw(purple, src, dest);
				break;
			}

		}
	}
	for (int i = 0; i < 4; i++) {
		dest.x = currentBlock->coords[i][0] * 33 + 33;
		dest.y = currentBlock->coords[i][1] * 33 + 33;
		switch (currentBlock->blockColour) {
		case 0:
			break;
		case 1:
			TextureManager::Draw(yellow, src, dest);
			break;
		case 2:
			TextureManager::Draw(red, src, dest);
			break;
		case 3:
			TextureManager::Draw(orange, src, dest);
			break;
		case 4:
			TextureManager::Draw(green, src, dest);
			break;
		case 5:
			TextureManager::Draw(blue, src, dest);
			break;
		case 6:
			TextureManager::Draw(pink, src, dest);
			break;
		case 7:
			TextureManager::Draw(darkblue, src, dest);
			break;
		case 8:
			TextureManager::Draw(purple, src, dest);
			break;
		}
		
	}

}

// returns true if the block cant be placed (game over)
bool GameState::AddNewBlock() {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(1, 8);
	currentBlock->~Block();
	currentBlock = new Block(distr(gen),*state);


	for (int i = 0; i < 4; i++) {
		if (state[currentBlock->coords[i][1]][currentBlock->coords[i][0]] != 0) {
			return true;
		}
	}


	return false;
}

void GameState::GameOver()
{
}
