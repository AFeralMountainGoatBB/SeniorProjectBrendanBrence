/**********************************************************************************************//**
 * @file	Texture.h.
 *
 * @brief	Declares the texture class
 **************************************************************************************************/

#pragma once

#ifndef Texture_h
#define Texture_h

#include "GeneralHeaders.h"
#include <string>

/**********************************************************************************************//**
 * @class	LTexture
 *
 * @brief	
 *
 * @author	Brendan B
 * @date	9/1/2018
 **************************************************************************************************/

class LTexture
{
public:

	/**********************************************************************************************//**
	 * @fn	LTexture::LTexture();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/

	LTexture();


	/**********************************************************************************************//**
	 * @fn	LTexture::~LTexture();
	 *
	 * @brief	Destructor
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/

	~LTexture();


	/**********************************************************************************************//**
	 * @fn	bool LTexture::loadFromFile(std::string path, SDL_Renderer *&Renderer);
	 *
	 * @brief	Loads from file, Loads image at specified path
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param 		  	path		Full pathname of the file being loaded from
	 * @param [in,out]	Renderer	[in,out] If non-null, the renderer being used
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool loadFromFile(std::string path, SDL_Renderer *&Renderer);

#ifdef _SDL_TTF_H
	//Creates image from font string

	/**********************************************************************************************//**
	 * @fn	bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer *& Renderer, TTF_Font *Font);
	 *
	 * @brief	Loads from rendered text, effectively creates an image from a string in a given font
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param 		  	textureText	The text that will be rendered to text
	 * @param 		  	textColor  	The text color being rendered to 
	 * @param [in,out]	Renderer   	[in,out] If non-null, the renderer being used
	 * @param [in,out]	Font	   	If non-null, the font the text will be in
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer *& Renderer, TTF_Font *Font);
#endif

	/**********************************************************************************************//**
	 * @fn	void LTexture::free();
	 *
	 * @brief	Frees this object, deallocates the mem for it
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/

	void free();

	/**********************************************************************************************//**
	 * @fn	void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue);
	 *
	 * @brief	Sets a color value
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	red  	The red value
	 * @param	green	The green value
	 * @param	blue 	The blue value
	 **************************************************************************************************/

	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	/**********************************************************************************************//**
	 * @fn	void LTexture::setBlendMode(SDL_BlendMode blending);
	 *
	 * @brief	Sets blend mode
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	blending	The new blending mode
	 **************************************************************************************************/

	void setBlendMode(SDL_BlendMode blending);

	/**********************************************************************************************//**
	 * @fn	void LTexture::setAlpha(Uint8 alpha);
	 *
	 * @brief	Sets an alpha value
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	alpha	The alpha value that 
	 **************************************************************************************************/

	void setAlpha(Uint8 alpha);


	/**********************************************************************************************//**
	 * @fn	void LTexture::renderTile(int x, int y, SDL_Renderer*& Renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
	 *
	 * @brief	Renders the texture given, most often used for tile textures
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param 		  	x			The x coordinate value of where tile will be rendered
	 * @param 		  	y			The y coordinate value of where tile will be rendered
	 * @param [in,out]	Renderer	[in,out] If non-null, the active renderer
	 * @param [in,out]	clip		(Optional) If non-null, the clip coords on the texture
	 * @param 		  	angle   	(Optional) The angle the texture will be rotated at before rendering
	 * @param [in,out]	center  	(Optional) If non-null, the center of the texture
	 * @param 		  	flip		(Optional) The flip setting, when rendered SDL determines what kind of flip is used with this val
	 **************************************************************************************************/

	void renderTile(int x, int y, SDL_Renderer*& Renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

	/**********************************************************************************************//**
	 * @fn	void LTexture::renderEntity(int x, int y, SDL_Renderer*& Renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	 *
	 * @brief	Renders the entity passed to it
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param 		  	x			The x coordinate where is being rendered to
	 * @param 		  	y			The y coordinate where is being rendered to
	 * @param [in,out]	Renderer	[in,out] If non-null, the renderer that will be used
	 * @param [in,out]	clip		(Optional) If non-null, the clip value
	 * @param 		  	angle   	(Optional) The angle.
	 * @param [in,out]	center  	(Optional) If non-null, the center of the text
	 * @param 		  	flip		(Optional) The flip.
	 **************************************************************************************************/

	void renderEntity(int x, int y, SDL_Renderer*& Renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	/**********************************************************************************************//**
	 * @fn	int LTexture::getWidth();
	 *
	 * @brief	Gets the width of image
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The width of image dimensions
	 **************************************************************************************************/

	int getWidth();

	/**********************************************************************************************//**
	 * @fn	int LTexture::getHeight();
	 *
	 * @brief	Gets the height of image
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The height of image dimensions
	 **************************************************************************************************/

	int getHeight();

	/**********************************************************************************************//**
	 * @fn	void LTexture::setWidth(int width);
	 *
	 * @brief	Sets a width of the texture
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	width	The width of the image
	 **************************************************************************************************/

	void setWidth(int width);

	/**********************************************************************************************//**
	 * @fn	void LTexture::setHeight(int height);
	 *
	 * @brief	Sets a height for the texture
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	height	The height of the image
	 **************************************************************************************************/

	void setHeight(int height);

	/**********************************************************************************************//**
	 * @fn	void LTexture::setTexture(SDL_Texture* Texture);
	 *
	 * @brief	Sets a texture into this class
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param [in,out]	Texture	If non-null, the texture being stored
	 **************************************************************************************************/

	void setTexture(SDL_Texture* Texture);

private:
	/** @brief	The texture */
	SDL_Texture* m_Texture;

	//Image dimensions
	/** @brief	The width */
	int m_Width;
	/** @brief	The height */
	int m_Height;
};

#endif Texture_h 