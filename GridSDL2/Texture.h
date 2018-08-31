#pragma once

#ifndef Texture_h
#define Texture_h

#include "GeneralHeaders.h"
#include <string>

class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer *&Renderer);

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer *& Renderer, TTF_Font *gFont);
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void renderTile(int x, int y, SDL_Renderer*& Renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

	void renderEntity(int x, int y, SDL_Renderer*& Renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);


	//Gets image dimensions
	int getWidth();
	int getHeight();
	void setWidth(int width);
	void setHeight(int height);

	void setTexture(SDL_Texture* Texture);

private:
	//The actual hardware texture
	SDL_Texture* m_Texture;

	//Image dimensions
	int m_Width;
	int m_Height;
};


#endif Texture_h 