/**********************************************************************************************//**
 * @file	PickupItemsMenu.h.
 *
 * @brief	Declares the pickup items menu class
 **************************************************************************************************/

#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"
#include "Tile.h"
#include "Objects.h"

class EncounterInstance;

class PickupItemsMenu {
public:

	/**********************************************************************************************//**
	 * @fn	PickupItemsMenu::PickupItemsMenu();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 **************************************************************************************************/

	PickupItemsMenu();


	/**********************************************************************************************//**
	 * @fn	ObjectClass* PickupItemsMenu::PickupItemsRun(Tile &tile);
	 *
	 * @brief	Pickup items run, runs the main loop and handles rendering and events passed to the menu
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	tile	The tile being picked up from
	 *
	 * @return	Null if it fails, else a pointer to the ObjectClass to be picked up.
	 **************************************************************************************************/

	ObjectClass* PickupItemsRun(Tile &tile);

	/**********************************************************************************************//**
	 * @fn	static void PickupItemsMenu::vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *m_event, kiss_textbox *m_textbox2, int *m_draw);
	 *
	 * @brief	Vscrollbar 1 event, handles events on the scrollbar for the item list
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	vscrollbar	If non-null, the vscrollbar.
	 * @param [in,out]	m_event   	If non-null, the event.
	 * @param [in,out]	m_textbox2	If non-null, the second textbox.
	 * @param [in,out]	m_draw	  	If non-null, the draw, acts as a bool
	 **************************************************************************************************/

	static void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *m_event, kiss_textbox *m_textbox2, int *m_draw);

	/**********************************************************************************************//**
	 * @fn	static void PickupItemsMenu::textbox1_event(kiss_textbox *textbox, SDL_Event *m_event, kiss_vscrollbar *vscrollbar2, kiss_entry *m_entry, int *m_draw);
	 *
	 * @brief	Textbox 1 event, handles events in the textbox
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	textbox	   	If non-null, the textbox.
	 * @param [in,out]	m_event	   	If non-null, the event.
	 * @param [in,out]	vscrollbar2	If non-null, the second vscrollbar.
	 * @param [in,out]	m_entry	   	If non-null, the entry.
	 * @param [in,out]	m_draw	   	If non-null, the draw.
	 **************************************************************************************************/

	static void textbox1_event(kiss_textbox *textbox, SDL_Event *m_event, kiss_vscrollbar *vscrollbar2, kiss_entry *m_entry, int *m_draw);

	/**********************************************************************************************//**
	 * @fn	static void PickupItemsMenu::text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);
	 *
	 * @brief	Text reset, used to reset the textbox to properly update what is in it
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	textbox   	If non-null, the textbox.
	 * @param [in,out]	vscrollbar	If non-null, the vscrollbar.
	 **************************************************************************************************/

	static void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);

	/**********************************************************************************************//**
	 * @fn	static void PickupItemsMenu::button_cancel_event(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw);
	 *
	 * @brief	Button cancel event
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	button 	If non-null, the button.
	 * @param [in,out]	m_event	If non-null, the event.
	 * @param [in,out]	m_quit 	If non-null, the quit val
	 * @param [in,out]	m_draw 	If non-null, the draw val
	 **************************************************************************************************/

	static void button_cancel_event(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw);

	/**********************************************************************************************//**
	 * @fn	void PickupItemsMenu::button_ok1_event(kiss_button *button, SDL_Event *m_event, kiss_window *window1, kiss_label *m_label_sel, kiss_entry *m_entry, kiss_label *m_label_res, int *m_draw, std::vector<ObjectClass*> ObjectVector);
	 *
	 * @brief	Button ok 1 event
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	button			If non-null, the button.
	 * @param [in,out]	m_event			If non-null, the event.
	 * @param [in,out]	window1			If non-null, the first window.
	 * @param [in,out]	m_label_sel 	If non-null, the label selected.
	 * @param [in,out]	m_entry			If non-null, the entry.
	 * @param [in,out]	m_label_res 	If non-null, the label resource.
	 * @param [in,out]	m_draw			If non-null, the draw.
	 * @param [in,out]	ObjectVector	If non-null, the object vector of items present
	 **************************************************************************************************/

	void button_ok1_event(kiss_button *button, SDL_Event *m_event, kiss_window *window1, kiss_label *m_label_sel,
		kiss_entry *m_entry, kiss_label *m_label_res, int *m_draw, std::vector<ObjectClass*> ObjectVector);

	/**********************************************************************************************//**
	 * @fn	void PickupItemsMenu::RepopulateList(Tile SelectedTile);
	 *
	 * @brief	Repopulate list of items and place into textbox
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param	SelectedTile	The selected tile, where the list will populate from what items are in it
	 **************************************************************************************************/

	void RepopulateList(Tile SelectedTile);

private:
	/** @brief  pointer aiming to selected item*/
	ObjectClass* m_SelectedItem = NULL;

	/** @brief The renderer being used */
	SDL_Renderer* m_renderer;

	/** @brief the current even being processed */
	SDL_Event m_event;

	/** @brief The arrays used to store objects used by kiss_sdl */
	kiss_array m_objects, m_array1;
	/** @brief The mainWindow being used */
	kiss_window m_MainWindow;
	/** @brief The labels being used */
	kiss_label m_ItemsTextBoxLabel = { 0 }, m_label_sel = { 0 }, m_label_res = { 0 };
	/** @brief The main ok button, secondary ok button, button cancel */
	kiss_button m_Main_ok_button = { 0 }, m_Secondary_ok_button = { 0 }, m_button_cancel = { 0 };
	/** @brief	The first textbox */
	kiss_textbox m_textbox1 = { 0 };
	/** @brief	The first vscrollbar */
	kiss_vscrollbar m_vscrollbar1 = { 0 };
	/** @brief	The entry */
	kiss_entry m_entry = { 0 };

	/** @brief Dimensions for textbox and windows */
	int m_textbox_width, m_textbox_height, m_window2_width, m_window2_height, m_draw, m_quit;
};