#pragma once
#include "GeneralHeaders.h"

//#include "EncounterInstance.h"

class Tile;
class LTexture;
class EncounterInstance;
class Dot
{
public:
	//The dimensions of the dot
	int DOT_WIDTH = 20;
	int DOT_HEIGHT = 20;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 10;

	//Initializes the variables
	Dot();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot and check collision against tiles
	void move(EncounterInstance &Encounter);
	void SetLocation(int x, int y);

	std::pair<int, int> GetLocation();

	//Centers the camera over the dot
	void setCamera(SDL_Rect& camera);

	//Shows the dot on the screen
	void render(SDL_Rect& camera, LTexture &DotTexture, SDL_Renderer *& Renderer);

private:
	//Collision box of the dot
	SDL_Rect mBox;

	//The velocity of the dot
	int mVelX, mVelY;

	//The location on the map the object is in
	std::pair<int, int> mLocation; //first is x value, second is y value

};