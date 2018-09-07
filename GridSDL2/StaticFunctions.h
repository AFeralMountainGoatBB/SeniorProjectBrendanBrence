#pragma once

#include "GeneralHeaders.h"
#include "SharedEnums.h"

class Tile;
class LTexture;

//Box collision detector

/**********************************************************************************************//**
 * @fn	bool checkCollision(SDL_Rect a, SDL_Rect b);
 *
 * @brief	Check collision between the two rectangles a and b
 *
 * @author	Brendan B
 * @date	9/1/2018
 *
 * @param	a	A SDL_Rect to process 
 * @param	b	A SDL_Rect to process 
 *
 * @return	True if they collide, false if they do not.
 **************************************************************************************************/

bool checkCollision(SDL_Rect a, SDL_Rect b);

/**********************************************************************************************//**
 * @fn	int DiceRoll(DiceType Dice);
 *
 * @brief	Dice roll, takes enum val equal to dice size, generates a number between 1 and the number passed
 *
 * @author	Brendan B
 * @date	9/1/2018
 *
 * @param	Dice	The type of dice being rolled, only allows 1 dice at a time.
 *
 * @return	the generated number.
 **************************************************************************************************/

int DiceRoll(DiceType Dice);