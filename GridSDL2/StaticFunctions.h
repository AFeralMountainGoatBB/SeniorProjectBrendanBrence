#pragma once

#include "GeneralHeaders.h"
#include "SharedEnums.h"

class Tile;
class LTexture;

//Box collision detector
bool checkCollision(SDL_Rect a, SDL_Rect b);

int DiceRoll(DiceType Dice);