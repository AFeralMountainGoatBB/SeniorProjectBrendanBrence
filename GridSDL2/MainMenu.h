/**********************************************************************************************//**
 * @file	MainMenu.h.
 *
 * @brief	Declares the main menu class
 **************************************************************************************************/

#pragma once
#include "GeneralHeaders.h"

/**********************************************************************************************//**
 * @class	MainMenu
 *
 * @brief	A main menu class holding information to run the main menu to interact with users
 *
 * @author	Brendan B
 * @date	9/4/2018
 **************************************************************************************************/

class MainMenu
{
public:

	/**********************************************************************************************//**
	 * @fn	MainMenu::MainMenu();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 **************************************************************************************************/

	MainMenu();

	/**********************************************************************************************//**
	 * @fn	void MainMenu::quit_button_event(kiss_button *button, SDL_Event *m_event, int *m_draw);
	 *
	 * @brief	Quit button event
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	button 	If non-null, the button.
	 * @param [in,out]	m_event	If non-null, the event.
	 * @param [in,out]	m_draw 	If non-null, the draw.
	 **************************************************************************************************/

	void quit_button_event(kiss_button *button, SDL_Event *m_event, int *m_draw);

	/**********************************************************************************************//**
	 * @fn	void MainMenu::scenario_button_event(kiss_button *button, SDL_Event *m_event, int *m_draw);
	 *
	 * @brief	Scenario button event
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	button 	If non-null, the button.
	 * @param [in,out]	m_event	If non-null, the event.
	 * @param [in,out]	m_draw 	If non-null, the draw.
	 **************************************************************************************************/

	void scenario_button_event(kiss_button *button, SDL_Event *m_event, int *m_draw);

	/**********************************************************************************************//**
	 * @fn	void MainMenu::MainMenUUpdate(SDL_Renderer *& m_renderer);
	 *
	 * @brief	Main menu update
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	m_renderer	[in,out] If non-null, the active renderer
	 **************************************************************************************************/

	void MainMenUUpdate(SDL_Renderer *& m_renderer);

	/**********************************************************************************************//**
	 * @fn	int MainMenu::MainMenuRun();
	 *
	 * @brief	Main menu run
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @return	An int return value to communicate what the user requests
	 **************************************************************************************************/

	int MainMenuRun();

private:
	//variables
	/** @brief	The renderer */
	SDL_Renderer * m_renderer;
	/** @brief	The event */
	SDL_Event m_event;
	/** @brief	The objects */
	kiss_array m_objects;
	/** @brief	The window */
	kiss_window m_window;
	/** @brief	The label */
	kiss_label m_label = { 0 };
	/** @brief	The scenario button */
	kiss_button m_ScenarioButton = { 0 };
	/** @brief	The quit button */
	kiss_button m_QuitButton = { 0 };
	/** @brief	The message[ kiss maximum length] */
	char m_message[KISS_MAX_LENGTH];

	/**********************************************************************************************//**
	 * @enum	option
	 *
	 * @brief	Values that represent options the user selects
	 **************************************************************************************************/

	enum option { CONTINUE = 0, QUIT = -1, SCENARIOMENU = 1 };
	/** @brief	The retval */
	option m_retval = CONTINUE;

};