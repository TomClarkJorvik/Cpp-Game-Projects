#include "GameState.h"

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
}

// a or d to move left or right
void GameState::TakeAction(char action) {
	bool canMove = true;

	switch (action) {
	// move block left
	case 'l':
		for (int i = 0; i < 4; i++) {
			if (state[currentBlock[i][1]][currentBlock[i][0]-1] != 0 || currentBlock[i][0] == 0) {
				canMove = false;
			}
		}
		if (canMove) {
			for (int i = 0; i < 4; i++) {
				currentBlock[i][0] -= 1;
			}
		}
		break;
	case 'r':
		for (int i = 0; i < 4; i++) {
			if (state[currentBlock[i][1]][currentBlock[i][0] + 1] != 0 || currentBlock[i][0] == 9) {
				canMove = false;
			}
		}
		if (canMove) {
			for (int i = 0; i < 4; i++) {
				currentBlock[i][0] += 1;
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
		if (state[currentBlock[i][1]+1][currentBlock[i][0]] != 0 || currentBlock[i][1]==19) {
			canMove = false;
		}
	}
	if (canMove) {
		for (int i = 0; i < 4; i++) {
			currentBlock[i][1] += 1;
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			state[currentBlock[i][1]][currentBlock[i][0]] = currentBlockColour;
		}



		if (AddNewBlock()) {
			return true;
		}
	}
	bool rowMade;
	for (int i = 0; i < rows; i++) {
		rowMade = true;
		for (int j = 0; j < rows; j++) {
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
		dest.x = currentBlock[i][0] * 33 + 33;
		dest.y = currentBlock[i][1] * 33 + 33;
		switch (currentBlockColour) {
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
	currentBlockColour = distr(gen);
	switch (currentBlockColour) {

	case 1: // yellow square
		currentBlock[0][0] = 4;
		currentBlock[0][1] = 0;
		currentBlock[1][0] = 4;
		currentBlock[1][1] = 1;
		currentBlock[2][0] = 5;
		currentBlock[2][1] = 0;
		currentBlock[3][0] = 5;
		currentBlock[3][1] = 1; 
		break;
	case 2:// red --__
		currentBlock[0][0] = 4;
		currentBlock[0][1] = 0;
		currentBlock[1][0] = 4;
		currentBlock[1][1] = 1;
		currentBlock[2][0] = 5;
		currentBlock[2][1] = 1;
		currentBlock[3][0] = 5;
		currentBlock[3][1] = 2;
		break;
	case 3: // orange __|
		currentBlock[0][0] = 5;
		currentBlock[0][1] = 0;
		currentBlock[1][0] = 5;
		currentBlock[1][1] = 1;
		currentBlock[2][0] = 5;
		currentBlock[2][1] = 2;
		currentBlock[3][0] = 4;
		currentBlock[3][1] = 2;
		break;
	case 4:// green _|-
		currentBlock[0][0] = 5;
		currentBlock[0][1] = 0;
		currentBlock[1][0] = 5;
		currentBlock[1][1] = 1;
		currentBlock[2][0] = 4;
		currentBlock[2][1] = 1;
		currentBlock[3][0] = 4;
		currentBlock[3][1] = 2;
		break;
	case 5: // blue ____
		currentBlock[0][0] = 4;
		currentBlock[0][1] = 0;
		currentBlock[1][0] = 4;
		currentBlock[1][1] = 1;
		currentBlock[2][0] = 4;
		currentBlock[2][1] = 2;
		currentBlock[3][0] = 4;
		currentBlock[3][1] = 3;
		break;
	case 6: // pink _|_
		currentBlock[0][0] = 5;
		currentBlock[0][1] = 0;
		currentBlock[1][0] = 5;
		currentBlock[1][1] = 1;
		currentBlock[2][0] = 4;
		currentBlock[2][1] = 1;
		currentBlock[3][0] = 5;
		currentBlock[3][1] = 2;
		break;
	case 7:// dark blue |__
		currentBlock[0][0] = 4;
		currentBlock[0][1] = 0;
		currentBlock[1][0] = 5;
		currentBlock[1][1] = 0;
		currentBlock[2][0] = 5;
		currentBlock[2][1] = 1;
		currentBlock[3][0] = 5;
		currentBlock[3][1] = 2; 
		break;
	case 8:// purple -|_
		currentBlock[0][0] = 4;
		currentBlock[0][1] = 0;
		currentBlock[1][0] = 4;
		currentBlock[1][1] = 1;
		currentBlock[2][0] = 5;
		currentBlock[2][1] = 1;
		currentBlock[3][0] = 5;
		currentBlock[3][1] = 2;
		break;
	}

	for (int i = 0; i < 4; i++) {
		if (state[currentBlock[i][1]][currentBlock[i][0]] != 0) {
			return true;
		}
	}


	return false;
}

void GameState::GameOver()
{
}
