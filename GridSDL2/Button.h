/**********************************************************************************************//**
 * @file	Button.h.
 *
 * @brief	Declares the button class
 **************************************************************************************************/

#pragma once

#include "GeneralHeaders.h"
#include "SharedEnums.h"
#include "Texture.h"
//fwd declaration to prevemt circular dependencies
class Log;

/**********************************************************************************************//**
 * @class	button
 *
 * @brief	A button class, holds information relating to its texture and its dimensions, 
 * 			as well as algorithms to determine if it was clicked
 *
 * @author	Brendan B
 * @date	9/7/2018
 **************************************************************************************************/

class button
{
public:
	/**********************************************************************************************//**
	 * @fn	button::button();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 **************************************************************************************************/

	button();

	/**********************************************************************************************//**
	 * @fn	void button::setPosition(int x, int y, int width, int height);
	 *
	 * @brief	Sets the position for the button
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	x	  	The x coordinate.
	 * @param	y	  	The y coordinate.
	 * @param	width 	The width.
	 * @param	height	The height.
	 **************************************************************************************************/

	void setPosition(int x, int y, int width, int height);

	/**********************************************************************************************//**
	 * @fn	void button::SetTexture(std::string textureName, std::map<std::string, LTexture*> &TextureMap, std::string Path);
	 *
	 * @brief	Sets the texture for the button
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param 		  	textureName	Name of the texture.
	 * @param [in,out]	TextureMap 	[in,out] If non-null, the texture map.
	 * @param 		  	Path	   	Full pathname of the file.
	 **************************************************************************************************/

	void SetTexture(std::string textureName, std::map<std::string, LTexture*> &TextureMap, std::string Path);
	//Shows button sprite

	/**********************************************************************************************//**
	 * @fn	void button::render(SDL_Renderer *& m_renderer);
	 *
	 * @brief	Renders the button on the screen using the passed renderer
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	m_renderer	[in,out] If non-null, the renderer.
	 **************************************************************************************************/

	void render(SDL_Renderer *& m_renderer);

	/**********************************************************************************************//**
	 * @fn	void button::SetName(std::string passedname)
	 *
	 * @brief	Sets a name
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	passedname	The new name value
	 **************************************************************************************************/

	void SetName(std::string passedname) { m_name = passedname; }

	/**********************************************************************************************//**
	 * @fn	int button::GetXPos()
	 *
	 * @brief	Get x coordinate position
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The x coordinate position.
	 **************************************************************************************************/

	int GetXPos() { return m_Position.x; }

	/**********************************************************************************************//**
	 * @fn	int button::GetYPos()
	 *
	 * @brief	Get y coordinate position
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The y coordinate position.
	 **************************************************************************************************/

	int GetYPos() { return m_Position.y; }

	/**********************************************************************************************//**
	 * @fn	int button::GetHeight()
	 *
	 * @brief	Gets the height
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The height.
	 **************************************************************************************************/

	int GetHeight() {return m_Position.h;}

	/**********************************************************************************************//**
	 * @fn	int button::GetWidth()
	 *
	 * @brief	Gets the width
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The width.
	 **************************************************************************************************/

	int GetWidth() { return m_Position.w; }

	/**********************************************************************************************//**
	 * @fn	int button::GetYOffset()
	 *
	 * @brief	Get y coordinate offset
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The y coordinate offset.
	 **************************************************************************************************/

	int GetYOffset() { return m_YOffset; }

	/**********************************************************************************************//**
	 * @fn	void button::SetYOffset(int y)
	 *
	 * @brief	Sets y coordinate offset
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	y	The y coordinate.
	 **************************************************************************************************/

	void SetYOffset(int y) { m_YOffset = y; }

private:
	/** @brief	The name */
	std::string m_name = "button";
	/** @brief	Full pathname of the texture file */
	std::string m_TexturePath = "button.png";
	/** @brief	The texture */
	LTexture* m_Texture;
	//Top left position
	/** @brief	The position */
	SDL_Rect m_Position;
	/** @brief	The offset */
	int m_YOffset;
	/** @brief	The offset */
	int m_XOffset;

};