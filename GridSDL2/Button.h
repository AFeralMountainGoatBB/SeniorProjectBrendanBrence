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
	void render(SDL_Renderer *& m_renderer);
	
	void SetName(std::string passedname) { m_name = passedname; }

	int GetXPos() { return m_Position.x; }
	int GetYPos() { return m_Position.y; }
	int GetHeight() {return m_Position.h;}
	int GetWidth() { return m_Position.w; }
	int GetYOffset() { return m_YOffset; }
	void SetYOffset(int y) { m_YOffset = y; }

private:
	std::string m_name = "button";
	std::string m_TexturePath = "button.png";
	LTexture* m_Texture;
	//Top left position
	SDL_Rect m_Position;
	int m_YOffset;
	int m_XOffset;

};