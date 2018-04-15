#pragma once

#include "GeneralHeaders.h"
#include "SharedEnums.h"
#include "Texture.h"


const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

class button
{
public:
	//Initializes internal variables
	button();

	//Sets top left position
	void setPosition(int x, int y, int width, int height);

	void setFunction(void (*funcptr)());

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	//Shows button sprite
	void render(SDL_Renderer*& renderer);

private:
	std::string name;
	LTexture* mTexture;
	//Top left position
	SDL_Rect mPosition;

	void(*On_Click)();

	//Currently used global sprite
	LButtonSprite mCurrentSprite;

};