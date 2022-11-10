#include "Block.h"

Block::Block(int colourInput, int* stateInput)
{
	rotation = 0;
	blockColour = colourInput;
	state = stateInput;
	switch (blockColour) {

	case 1: // yellow square
		coords[0][0] = 4;
		coords[0][1] = 0;
		coords[1][0] = 4;
		coords[1][1] = 1;
		coords[2][0] = 5;
		coords[2][1] = 0;
		coords[3][0] = 5;
		coords[3][1] = 1;
		pivotPoint[0] = 4;
		pivotPoint[1] = 0;
		break;
	case 2:// red --__
		coords[0][0] = 4;
		coords[0][1] = 0;
		coords[1][0] = 5;
		coords[1][1] = 0;
		coords[2][0] = 5;
		coords[2][1] = 1;
		coords[3][0] = 6;
		coords[3][1] = 1;
		pivotPoint[0] = 5;
		pivotPoint[1] = 1;
		break;
	case 3: // orange __|
		coords[0][0] = 5;
		coords[0][1] = 1;
		coords[1][0] = 6;
		coords[1][1] = 1;
		coords[2][0] = 7;
		coords[2][1] = 1;
		coords[3][0] = 7;
		coords[3][1] = 0;
		pivotPoint[0] = 6;
		pivotPoint[1] = 1;
		break;
	case 4:// green _|-
		coords[0][0] = 5;
		coords[0][1] = 1;
		coords[1][0] = 6;
		coords[1][1] = 1;
		coords[2][0] = 6;
		coords[2][1] = 0;
		coords[3][0] = 7;
		coords[3][1] = 0;
		pivotPoint[0] = 6;
		pivotPoint[1] = 1;
		break;
	case 5: // blue ____
		coords[0][0] = 4;
		coords[0][1] = 0;
		coords[1][0] = 5;
		coords[1][1] = 0;
		coords[2][0] = 6;
		coords[2][1] = 0;
		coords[3][0] = 7;
		coords[3][1] = 0;
		pivotPoint[0] = 5;
		pivotPoint[1] = 0;
		break;
	case 6: // pink _|_
		coords[0][0] = 5;
		coords[0][1] = 1;
		coords[1][0] = 6;
		coords[1][1] = 1;
		coords[2][0] = 6;
		coords[2][1] = 0;
		coords[3][0] = 7;
		coords[3][1] = 1;
		pivotPoint[0] = 6;
		pivotPoint[1] = 1;
		break;
	case 7:// dark blue |__
		coords[0][0] = 4;
		coords[0][1] = 0;
		coords[1][0] = 4;
		coords[1][1] = 1;
		coords[2][0] = 5;
		coords[2][1] = 1;
		coords[3][0] = 6;
		coords[3][1] = 1;
		pivotPoint[0] = 5;
		pivotPoint[1] = 1;
		break;
	case 8:// purple |_
		//           |
		coords[0][0] = 4;
		coords[0][1] = 0;
		coords[1][0] = 4;
		coords[1][1] = 1;
		coords[2][0] = 5;
		coords[2][1] = 1;
		coords[3][0] = 5;
		coords[3][1] = 2;
		pivotPoint[0] = 4;
		pivotPoint[1] = 1;
		break;
	}
}
