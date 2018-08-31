#include "StaticFunctions.h"
#include "Texture.h"
#include "Tile.h"


bool checkCollision(SDL_Rect a_a, SDL_Rect a_b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a_a.x;
	rightA = a_a.x + a_a.w;
	topA = a_a.y;
	bottomA = a_a.y + a_a.h;

	//Calculate the sides of rect B
	leftB = a_b.x;
	rightB = a_b.x + a_b.w;
	topB = a_b.y;
	bottomB = a_b.y + a_b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

//
int DiceRoll(DiceType a_Dice)
{
	return 1 + rand() % a_Dice;
}

