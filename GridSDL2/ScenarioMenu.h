/**********************************************************************************************//**
 * @file	ScenarioMenu.h.
 *
 * @brief	Declares the scenario menu class
 **************************************************************************************************/

#pragma once
#include "GeneralHeaders.h"
#include <string>
#include <iostream>
#include <filesystem>
#include "GameInstance.h"

/**********************************************************************************************//**
 * @class	ScenarioMenu
 *
 * @brief	A scenario menu, handles selecting 
 *
 * @author	Brendan B
 * @date	9/7/2018
 **************************************************************************************************/

class ScenarioMenu
{
public:

	/**********************************************************************************************//**
	 * @fn	ScenarioMenu::ScenarioMenu();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 **************************************************************************************************/

	ScenarioMenu();

	/**********************************************************************************************//**
	 * @fn	static void ScenarioMenu::PrintFile(std::string filepath);
	 *
	 * @brief	Print file, outputs file to console line by line
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	filepath	The filepath.
	 **************************************************************************************************/

	static void PrintFile(std::string filepath);

	/**********************************************************************************************//**
	 * @fn	static void ScenarioMenu::vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *m_event, kiss_textbox *m_textbox2, int *m_draw);
	 *
	 * @brief	Vscrollbar 1 event
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	vscrollbar	If non-null, the vscrollbar.
	 * @param [in,out]	m_event   	If non-null, the event.
	 * @param [in,out]	m_textbox2	If non-null, the second textbox.
	 * @param [in,out]	m_draw	  	If non-null, the draw.
	 **************************************************************************************************/

	static void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *m_event, kiss_textbox *m_textbox2, int *m_draw);

	/**********************************************************************************************//**
	 * @fn	static void ScenarioMenu::textbox2_event(kiss_textbox *textbox, SDL_Event *m_event, kiss_vscrollbar *vscrollbar2, kiss_entry *m_entry, int *m_draw);
	 *
	 * @brief	Textbox 2 event, handles when user clicks on files to select them
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	textbox	   	If non-null, the textbox.
	 * @param [in,out]	m_event	   	If non-null, the event.
	 * @param [in,out]	vscrollbar2	If non-null, the second vscrollbar.
	 * @param [in,out]	m_entry	   	If non-null, the entry.
	 * @param [in,out]	m_draw	   	If non-null, the draw.
	 **************************************************************************************************/

	static void textbox2_event(kiss_textbox *textbox, SDL_Event *m_event, kiss_vscrollbar *vscrollbar2, kiss_entry *m_entry, int *m_draw);

	/**********************************************************************************************//**
	 * @fn	static void ScenarioMenu::text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);
	 *
	 * @brief	Text reset
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	textbox   	If non-null, the textbox.
	 * @param [in,out]	vscrollbar	If non-null, the vscrollbar.
	 **************************************************************************************************/

	static void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);

	/**********************************************************************************************//**
	 * @fn	static void ScenarioMenu::button_ok2_event(kiss_button *button, SDL_Event *m_event, kiss_window *window1, kiss_window *window2, kiss_progressbar *m_progressbar, int *m_draw);
	 *
	 * @brief	Button ok 2 event
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	button		 	If non-null, the button.
	 * @param [in,out]	m_event		 	If non-null, the event.
	 * @param [in,out]	window1		 	If non-null, the first window.
	 * @param [in,out]	window2		 	If non-null, the second window.
	 * @param [in,out]	m_progressbar	If non-null, the progressbar.
	 * @param [in,out]	m_draw		 	If non-null, the draw.
	 **************************************************************************************************/

	static void button_ok2_event(kiss_button *button, SDL_Event *m_event, kiss_window *window1, kiss_window *window2, kiss_progressbar *m_progressbar, int *m_draw);

	/**********************************************************************************************//**
	 * @fn	static void ScenarioMenu::button_cancel_event(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw);
	 *
	 * @brief	Button cancel event
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	button 	If non-null, the button.
	 * @param [in,out]	m_event	If non-null, the event.
	 * @param [in,out]	m_quit 	If non-null, the quit.
	 * @param [in,out]	m_draw 	If non-null, the draw.
	 **************************************************************************************************/

	static void button_cancel_event(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw);

	/**********************************************************************************************//**
	 * @fn	void ScenarioMenu::button_ok1_event(kiss_button *button, SDL_Event *m_event, kiss_window *window1, kiss_window *window2, kiss_label *m_label_sel, kiss_entry *m_entry, kiss_label *m_label_res, kiss_progressbar *m_progressbar, int *m_draw, GameInstance &GInst);
	 *
	 * @brief	Button ok 1 event, handles when user has a file selected
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	button		 	If non-null, the button.
	 * @param [in,out]	m_event		 	If non-null, the event.
	 * @param [in,out]	window1		 	If non-null, the first window.
	 * @param [in,out]	window2		 	If non-null, the second window.
	 * @param [in,out]	m_label_sel  	If non-null, the label selected.
	 * @param [in,out]	m_entry		 	If non-null, the entry.
	 * @param [in,out]	m_label_res  	If non-null, the label resource.
	 * @param [in,out]	m_progressbar	If non-null, the progressbar.
	 * @param [in,out]	m_draw		 	If non-null, the draw.
	 * @param [in,out]	GInst		 	The instance.
	 **************************************************************************************************/

	void button_ok1_event(kiss_button *button, SDL_Event *m_event, kiss_window *window1, kiss_window *window2, kiss_label *m_label_sel,
		kiss_entry *m_entry, kiss_label *m_label_res, kiss_progressbar *m_progressbar, int *m_draw, GameInstance &GInst);

	/**********************************************************************************************//**
	 * @fn	int ScenarioMenu::ScenarioMenuRun(GameInstance &GInst);
	 *
	 * @brief	Scenario menu run
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	GInst	The instance.
	 *
	 * @return	An int.
	 **************************************************************************************************/

	int ScenarioMenuRun(GameInstance &GInst);

private:
	/** @brief	Full pathname of the directory file */
	std::string m_DirectoryPath = "Data\\Scenarios";
	/** @brief	Full pathname of the scenario file */
	std::string m_ScenarioPath = "";

	/** @brief	The renderer */
	SDL_Renderer* m_renderer;
	
	/** @brief	The event */
	SDL_Event m_event;

	/** @brief	Kiss array objects used in kiss examples **/
	kiss_array m_objects, m_array1, m_array2;

	/** @brief	The two kiss windows used by the class **/
	kiss_window m_MainWindow, m_SecondaryWindow;
	/** @brief	The left text box label */
	kiss_label m_LeftTextBoxLabel = { 0 }, m_FileTextBoxLabel = { 0 }, m_label_sel = { 0 }, m_label_res = { 0 };
	/** @brief	The main ok button */
	kiss_button m_Main_ok_button = { 0 }, m_Secondary_ok_button = { 0 }, m_button_cancel = { 0 };
	/** @brief	The first textbox */
	kiss_textbox m_textbox1 = { 0 }, m_textbox2 = { 0 };
	/** @brief	The first vscrollbar */
	kiss_vscrollbar m_vscrollbar1 = { 0 };
	/** @brief	The progressbar */
	kiss_progressbar m_progressbar = { 0 };
	/** @brief	The entry */
	kiss_entry m_entry = { 0 };

	/** @brief	The textbox width, textbox height, windowheight, draw, quit values*/
	int m_textbox_width, m_textbox_height, m_window2_width, m_window2_height, m_draw, m_quit;

};