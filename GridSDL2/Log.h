/**********************************************************************************************//**
 * @file	Log.h.
 *
 * @brief	Declares the log class
 **************************************************************************************************/

#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"
#include "Texture.h"
#include "StaticFunctions.h"
#include "Button.h"

/**********************************************************************************************//**
 * @class	Log
 *
 * @brief	A log class contains messages generated by different actions to communicate gamestate changes to the user, 
 * 			will communicate the results of things like attack rolls
 *
 * @author	Brendan B
 * @date	9/4/2018
 **************************************************************************************************/

class Log {
public:
	//log functions

	/**********************************************************************************************//**
	 * @fn	Log::Log();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 **************************************************************************************************/

	Log();

	/**********************************************************************************************//**
	 * @fn	Log::Log(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_
	 * 		* Font);
	 *
	 * @brief	Constructor
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param 		  	TextureFolderPath	Full pathname of the texture folder file.
	 * @param [in,out]	TextureMap		 	[in,out] If non-null, the texture map.
	 * @param 		  	viewport		 	The viewport the log will render to
	 * @param [in,out]	Font			 	If non-null, the font being used
	 **************************************************************************************************/

	Log(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_Font* Font);

	/**********************************************************************************************//**
	 * @fn	void Log::Setup(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_Font* Font);
	 *
	 * @brief	Setup, sets log constraints to that of the viewport, sets font to passed value and sets up the buttons upbutton and downbutton
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param 		  	TextureFolderPath	Full pathname of the texture folder file.
	 * @param [in,out]	TextureMap		 	[in,out] If non-null, the texture map.
	 * @param 		  	viewport		 	The viewport.
	 * @param [in,out]	Font			 	If non-null, the font.
	 **************************************************************************************************/

	void Setup(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_Font* Font);

	/**********************************************************************************************//**
	 * @fn	void Log::AddLog(SDL_Renderer *& m_renderer, std::string LogEntry);
	 *
	 * @brief	Adds a log to 'LogEntry', passed in string format. creates texture from the text using renderer, 
	 * 			and loads the string into the the deque stringlog and deque texturelog
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	m_renderer	[in,out] If non-null, the renderer.
	 * @param 		  	LogEntry  	The log entry.
	 **************************************************************************************************/

	void AddLog(SDL_Renderer *& m_renderer, std::string LogEntry);

	/**********************************************************************************************//**
	 * @fn	void Log::AddStringLog(std::string LogEntry);
	 *
	 * @brief	Adds a string log to the string deque
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param	LogEntry	The log entry.
	 **************************************************************************************************/

	void AddStringLog(std::string LogEntry);

	/**********************************************************************************************//**
	 * @fn	void Log::AddTextureLog(SDL_Renderer*& m_renderer, std::string LogEntry);
	 *
	 * @brief	Adds a texture log to the texturelog deque
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	m_renderer	[in,out] If non-null, the renderer.
	 * @param 		  	LogEntry  	The log entry.
	 **************************************************************************************************/

	void AddTextureLog(SDL_Renderer*& m_renderer, std::string LogEntry);

	/**********************************************************************************************//**
	 * @fn	void Log::DeleteFromLog();
	 *
	 * @brief	Deletes from log
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 **************************************************************************************************/

	void DeleteFromLog();

	/**********************************************************************************************//**
	 * @fn	void Log::EventUpIndex(SDL_Event &m_event, button button);
	 *
	 * @brief	Event up index, shifts the current index upwards
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	m_event	The event.
	 * @param 		  	button 	The button control.
	 **************************************************************************************************/

	void EventUpIndex(SDL_Event &m_event, button button);

	/**********************************************************************************************//**
	 * @fn	void Log::EventDownIndex(SDL_Event &m_event, button button);
	 *
	 * @brief	Event down index, shifts the current index downwards
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	m_event	The event.
	 * @param 		  	button 	The button control.
	 **************************************************************************************************/

	void EventDownIndex(SDL_Event &m_event, button button);

	/**********************************************************************************************//**
	 * @fn	void Log::RenderLog(SDL_Renderer *& Renderer);
	 *
	 * @brief	Renders the log described by Renderer, iterates through starting at the index a number of lines equal to lines to render
	 * 			rendering the logs one after another
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Renderer	[in,out] If non-null, the renderer.
	 **************************************************************************************************/

	void RenderLog(SDL_Renderer *& Renderer);

	/**********************************************************************************************//**
	 * @fn	void Log::SetLogConstraints(int x, int y, int w, int h);
	 *
	 * @brief	Sets log constraints equal to the given constraints
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param	x	The x coordinate.
	 * @param	y	The y coordinate.
	 * @param	w	The width.
	 * @param	h	The height.
	 **************************************************************************************************/

	void SetLogConstraints(int x, int y, int w, int h);

	/**********************************************************************************************//**
	 * @fn	void Log::SetLogConstraints(SDL_Rect other);
	 *
	 * @brief	Sets log constraints equal to the given SDL_Rect
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param	other	The other SDL_Rect
	 **************************************************************************************************/

	void SetLogConstraints(SDL_Rect other);

	/**********************************************************************************************//**
	 * @fn	int Log::GetXPanelConstraint()
	 *
	 * @brief	Get x coordinate panel constraint
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @return	The x coordinate panel constraint.
	 **************************************************************************************************/

	int GetXPanelConstraint() { return m_LogConstraints.x; }

	/**********************************************************************************************//**
	 * @fn	int Log::GetYPanelConstraint()
	 *
	 * @brief	Get y coordinate panel constraint
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @return	The y coordinate panel constraint.
	 **************************************************************************************************/

	int GetYPanelConstraint() { return m_LogConstraints.y; }

	/**********************************************************************************************//**
	 * @fn	void Log::SetFont(TTF_Font* Font);
	 *
	 * @brief	Sets a font
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Font	If non-null, the font.
	 **************************************************************************************************/

	void SetFont(TTF_Font* Font);

	/**********************************************************************************************//**
	 * @fn	void Log::HandleEvents(SDL_Event& m_event);
	 *
	 * @brief	Handles the events described by m_event, possible of which are the clicking of the two buttons upindex and downindex
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	m_event	The event.
	 **************************************************************************************************/

	void HandleEvents(SDL_Event& m_event);

private:
	/** @brief	The log constraints */
	SDL_Rect m_LogConstraints;
	/** @brief	The up index control */
	button m_UpIndexButton;
	/** @brief	The down index control */
	button m_DownIndexButton;
	/** @brief	The log font */
	TTF_Font *m_LogFont;
	/** @brief	The log text color */
	SDL_Color m_LogTextColor = { 0, 0, 0 };

	/** @brief	The string representation of the log */
	std::deque<std::string>m_StringLog;
	/** @brief	The texture log */
	std::deque<LTexture*> m_TextureLog;
	/** @brief	Size of the log maximum */
	int m_LogMaximumSize = 100;
	/** @brief	Zero-based index of the location log */
	int m_LocationLogIndex = 0;
	/** @brief	The lines to render */
	int m_LinesToRender = 6;
	/** @brief	The lineheight */
	int m_LINEHEIGHT = 20;
	/** @brief	Full pathname of the texture file */
	std::string m_texturePath;

};