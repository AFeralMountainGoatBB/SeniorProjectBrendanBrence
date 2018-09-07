/**********************************************************************************************//**
 * @file	FeatMenu.h.
 *
 * @brief	Declares the feat menu class
 **************************************************************************************************/

#pragma once
#include "GeneralHeaders.h"
#include "StaticFunctions.h"
#include "Feats.h"
#include "EntityClass.h"

class FeatMenu
{

public:
	FeatMenu();

	/**********************************************************************************************//**
	 * @fn	void FeatMenu::FeatMenuRun(EntityClass &Source);
	 *
	 * @brief	Feat menu run, handles the running of the menu. Checks for events, exits updates to information and redraws the window every frame
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param [in,out]	Source	Source entity for the feats
	 **************************************************************************************************/

	void FeatMenuRun(EntityClass &Source);

	/**********************************************************************************************//**
	 * @fn	static void FeatMenu::vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *m_event, kiss_textbox *m_textbox2, int *m_draw);
	 *
	 * @brief	Vscrollbar 1 event, handles scrolling up and down
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param [in,out]	vscrollbar	If non-null, the vscrollbar.
	 * @param [in,out]	m_event   	If non-null, the event.
	 * @param [in,out]	m_textbox2	If non-null, the second textbox.
	 * @param [in,out]	m_draw	  	If non-null, the draw.
	 **************************************************************************************************/

	static void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *m_event, kiss_textbox *m_textbox2, int *m_draw);

	/**********************************************************************************************//**
	 * @fn	static void FeatMenu::textbox1_event(kiss_textbox *textbox, SDL_Event *m_event, kiss_vscrollbar *vscrollbar2, kiss_entry *m_entry, int *m_draw);
	 *
	 * @brief	Textbox 1 event, handles user clicking on the textbox to select feats
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param [in,out]	textbox	   	If non-null, the textbox.
	 * @param [in,out]	m_event	   	If non-null, the event.
	 * @param [in,out]	vscrollbar2	If non-null, the second vscrollbar.
	 * @param [in,out]	m_entry	   	If non-null, the entry.
	 * @param [in,out]	m_draw	   	If non-null, the draw.
	 **************************************************************************************************/

	static void textbox1_event(kiss_textbox *textbox, SDL_Event *m_event, kiss_vscrollbar *vscrollbar2, kiss_entry *m_entry, int *m_draw);

	/**********************************************************************************************//**
	 * @fn	static void FeatMenu::text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);
	 *
	 * @brief	Text reset, resets the textbox to be repopulated, deletes all entries before repopulating
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param [in,out]	textbox   	If non-null, the textbox.
	 * @param [in,out]	vscrollbar	If non-null, the vscrollbar.
	 **************************************************************************************************/

	static void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);

	/**********************************************************************************************//**
	 * @fn	static void FeatMenu::button_cancel_event(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw);
	 *
	 * @brief	Button cancel event, if user clicks set quitstate to true
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param [in,out]	button 	If non-null, the button.
	 * @param [in,out]	m_event	If non-null, the event.
	 * @param [in,out]	m_quit 	If non-null, the quit.
	 * @param [in,out]	m_draw 	If non-null, the draw.
	 **************************************************************************************************/

	static void button_cancel_event(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw);

	/**********************************************************************************************//**
	 * @fn	void FeatMenu::CloseDescriptionEvent(kiss_button *button, SDL_Event *m_event, kiss_window *window1, kiss_label *m_label_sel, kiss_entry *m_entry, kiss_label *m_label_res, int *m_draw, EntityClass& Source);
	 *
	 * @brief	Closes description event, if user clicks the button the description closes
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param [in,out]	button	   	If non-null, the button.
	 * @param [in,out]	m_event	   	If non-null, the event.
	 * @param [in,out]	window1	   	If non-null, the first window.
	 * @param [in,out]	m_label_sel	If non-null, the label selected.
	 * @param [in,out]	m_entry	   	If non-null, the entry.
	 * @param [in,out]	m_label_res	If non-null, the label resource.
	 * @param [in,out]	m_draw	   	If non-null, the draw.
	 * @param [in,out]	Source	   	Source for the.
	 **************************************************************************************************/

	void CloseDescriptionEvent(kiss_button *button, SDL_Event *m_event, kiss_window *window1, kiss_label *m_label_sel,
		kiss_entry *m_entry, kiss_label *m_label_res, int *m_draw, EntityClass& Source);

	/**********************************************************************************************//**
	 * @fn	void FeatMenu::IncreaseFeatEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, kiss_entry * m_entry, EntityClass& Source);
	 *
	 * @brief	Increase feat event, if button is clicked it calls the feat's inbuilt increase feat ability to up the range using feat
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param [in,out]	button 	If non-null, the button.
	 * @param [in,out]	m_event	If non-null, the event.
	 * @param [in,out]	m_quit 	If non-null, the quit.
	 * @param [in,out]	m_draw 	If non-null, the draw.
	 * @param [in,out]	m_entry	If non-null, the entry.
	 * @param [in,out]	Source 	Source entity for the feats
	 **************************************************************************************************/

	void IncreaseFeatEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, kiss_entry * m_entry, EntityClass& Source);

	/**********************************************************************************************//**
	 * @fn	void FeatMenu::DecreaseFeatEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, kiss_entry * m_entry, EntityClass& Source);
	 *
	 * @brief	Decrease feat event, if button is clicked it calls the feat's inbuilt increase feat ability to down the range using feat
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param [in,out]	button 	If non-null, the button.
	 * @param [in,out]	m_event	If non-null, the event.
	 * @param [in,out]	m_quit 	If non-null, the quit.
	 * @param [in,out]	m_draw 	If non-null, the draw.
	 * @param [in,out]	m_entry	If non-null, the entry.
	 * @param [in,out]	Source 	Source entity for the feats
	 **************************************************************************************************/

	void DecreaseFeatEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, kiss_entry * m_entry, EntityClass& Source);

	/**********************************************************************************************//**
	 * @fn	void FeatMenu::ToggleFeatEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, kiss_entry * m_entry, EntityClass& Source);
	 *
	 * @brief	Toggle feat event, calls the toggle ability for the feat
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param [in,out]	button 	If non-null, the button.
	 * @param [in,out]	m_event	If non-null, the event.
	 * @param [in,out]	m_quit 	If non-null, the quit.
	 * @param [in,out]	m_draw 	If non-null, the draw.
	 * @param [in,out]	m_entry	If non-null, the entry.
	 * @param [in,out]	Source 	Source entity for the feat
	 **************************************************************************************************/

	void ToggleFeatEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, kiss_entry * m_entry, EntityClass& Source);

	/**********************************************************************************************//**
	 * @fn	void FeatMenu::ViewFeatDescriptionEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, kiss_entry* m_entry, EntityClass& Source);
	 *
	 * @brief	View feat description event, calls getfeatdescription from feat and displays it
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param [in,out]	button 	If non-null, the button.
	 * @param [in,out]	m_event	If non-null, the event.
	 * @param [in,out]	m_quit 	If non-null, the quit.
	 * @param [in,out]	m_draw 	If non-null, the draw.
	 * @param [in,out]	m_entry	If non-null, the entry.
	 * @param [in,out]	Source 	Source for the feat
	 **************************************************************************************************/

	void ViewFeatDescriptionEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, kiss_entry* m_entry, EntityClass& Source);

	/**********************************************************************************************//**
	 * @fn	void FeatMenu::RepopulateList(EntityClass& Source);
	 *
	 * @brief	Repopulate list, iterates through source entity getting each feat, then displays each one in a textbox
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param [in,out]	Source	Source for the feat
	 **************************************************************************************************/

	void RepopulateList(EntityClass& Source);

private:
	/** @brief	The selected item */
	ObjectClass * m_SelectedItem = NULL;

	/** @brief	The active renderer */
	SDL_Renderer* m_renderer;
	
	/** @brief	The current event */
	SDL_Event m_event;

	/** @brief	The arrays used by kiss_sdl */
	kiss_array m_objects, m_array1;
	/** @brief	The windows used by this menu */
	kiss_window m_MainWindow, m_DescriptionWindow;
	/** @brief	The label variables used by this menu */
	kiss_label m_FeatsTextBoxLabel = { 0 }, m_label_sel = { 0 }, m_label_res = { 0 }, m_Descript1 = { 0 }, m_Descript2 = { 0 }, m_Descript3 = { 0 };
	/** @brief	The toggle feat button */
	kiss_button m_ToggleFeatButton = { 0 }, m_IncreaseFeatButton = { 0 }, m_DecreaseFeatButton = { 0 }, m_button_cancel = { 0 }, m_FeatDescriptionButton = { 0 }, m_DescriptionOkButton = { 0 };
	/** @brief	The feats */
	kiss_textbox m_Feats = { 0 };
	/** @brief	The first vscrollbar */
	kiss_vscrollbar m_vscrollbar1 = { 0 };
	/** @brief	The entry */
	kiss_entry m_entry = { 0 };

	/** @brief	variables for the constraints for the textboxes, windows and mdraw setting and m_quit*/
	int m_textbox_width, m_textbox_height, m_window2_width, m_window2_height, m_draw, m_quit;

};