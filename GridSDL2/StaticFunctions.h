#pragma once

#include "GeneralHeaders.h"
#include "SharedEnums.h"

class Tile;
class LTexture;

//Starts up SDL and creates window
bool init(SDL_Renderer* &gRenderer, SDL_Window* &gWindow);

//Loads media
bool loadMedia(Tile* tiles[], LTexture &gDotTexture, LTexture &gTileTexture, SDL_Renderer *&gRenderer, SDL_Rect &gTileClips);

//Frees media and shuts down SDL
void close(Tile* tiles[], LTexture &gDotTexture, LTexture &gTileTexture, SDL_Renderer*& gRenderer, SDL_Window*& gWindow);

//Box collision detector
bool checkCollision(SDL_Rect a, SDL_Rect b);

//Checks collision box against set of tiles
bool touchesWall(SDL_Rect box, Tile* tiles[]);

//Sets tiles from tile map
bool setTiles(Tile *tiles[], SDL_Rect gTileClips[]);

int DiceRoll(DiceType Dice);