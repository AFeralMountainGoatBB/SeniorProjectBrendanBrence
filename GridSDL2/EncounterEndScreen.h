#pragma once
#include "GeneralHeaders.h"

//this class is for the m_objects that will be always present during the encounter, namely on the left side of the screen and the bottom
//will have labels for relevant information and a log on bottom
class EncounterEndScreen
{
public:
	/**********************************************************************************************//**
	 * @fn	EncounterEndScreen::EncounterEndScreen();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 **************************************************************************************************/

	EncounterEndScreen();

	/**********************************************************************************************//**
	 * @fn	void EncounterEndScreen::Show(bool playerWin, bool ComputerWin);
	 *
	 * @brief	Shows
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param	playerWin  	True to show player won label
	 * @param	ComputerWin	True to show AI won label
	 **************************************************************************************************/

	void Show(bool playerWin, bool ComputerWin);

	/**********************************************************************************************//**
	 * @fn	void EncounterEndScreen::quit_button_event(kiss_button *button, SDL_Event *m_event);
	 *
	 * @brief	Quit button event
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	button 	If non-null, the button.
	 * @param [in,out]	m_event	If non-null, the event.
	 **************************************************************************************************/

	void quit_button_event(kiss_button *button, SDL_Event *m_event);

	/**********************************************************************************************//**
	 * @fn	void EncounterEndScreen::EndScreenRun();
	 *
	 * @brief	Ends screen run, runs the whole menu, handles updating and 
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 **************************************************************************************************/

	void EndScreenRun();

private:
	/** @brief	The renderer */
	SDL_Renderer * m_renderer;
	/** @brief	The event */
	SDL_Event m_event;
	/** @brief	The objects */
	kiss_array m_objects;
	/** @brief	The window */
	kiss_window m_window;
	/** @brief	The label player winner, label for ai winner, label for no winner */
	kiss_label m_labelPWin = { 0 }, m_labelCWin = { 0 }, m_labelNoWin = { 0 };

	/** @brief	The quit button */
	kiss_button m_QuitButton = { 0 };
	/** @brief	The message[ kiss maximum length] */
	char m_message[KISS_MAX_LENGTH];

	/** @brief	The quit */
	int m_quit = 0;
	/** @brief	The draw */
	int m_draw;

	/** @brief	True to pwin */
	bool m_Pwin = false;
	/** @brief	True to cwin */
	bool m_Cwin = false;
};