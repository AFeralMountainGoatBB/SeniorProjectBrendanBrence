#include "Button.h"
#include <functional>

button::button()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void button::setPosition(int x, int y, int width, int height)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.h = height;
	mPosition.w = width;
}

void button::setFunction(void funct())
{
	On_Click = funct;
}

void button::handleEvent(SDL_Event* e)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		//Check if mouse is in button
		bool inside = false;
		//check if mouse is inside the button 
		if (x > mPosition.x && x < mPosition.x + mPosition.w &&   y<mPosition.y+mPosition.h && y>mPosition.y)
		{
			inside = true;
			std::cout << "Button pressed" << std::endl;
			//do onclick!
			On_Click();
		}
	}
}

void button::render(SDL_Renderer*& renderer)
{
	mTexture->renderTile(mPosition.x, mPosition.y, renderer);
	//Show current button sprite
	//gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite]);
}