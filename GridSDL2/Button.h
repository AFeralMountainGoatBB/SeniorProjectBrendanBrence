#pragma once

#include "GeneralHeaders.h"
#include "SharedEnums.h"
#include "Texture.h"

class Log;

class button
{
public:
	//Initializes internal variables
	button();

	//Sets top left position
	void setPosition(int x, int y, int width, int height);
	void SetTexture(std::string textureName, std::map<std::string, LTexture*> &TextureMap, std::string Path);
	//Shows button sprite
	void render(SDL_Renderer *& renderer);
	
	void SetName(std::string passedname) { name = passedname; }

	int GetXPos() { return mPosition.x; }
	int GetYPos() { return mPosition.y; }
	int GetHeight() {return mPosition.h;}
	int GetWidth() { return mPosition.w; }
	int GetYOffset() { return YOffset; }
	void SetYOffset(int y) { YOffset = y; }

private:
	std::string name = "button";
	std::string TexturePath = "button.png";
	LTexture* mTexture;
	//Top left position
	SDL_Rect mPosition;
	int YOffset;
	int XOffset;

};