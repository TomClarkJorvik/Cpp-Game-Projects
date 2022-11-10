#pragma once
class Block
{
public :
	Block(int colourInput, int* stateInput);


	int coords[4][2];
	int pivotPoint[2];
	int blockColour;
private:
	int rotation;
	int* state;




};

