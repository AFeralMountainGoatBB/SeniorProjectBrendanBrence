/**********************************************************************************************//**
 * @file	InventoryMenu.h.
 *
 * @brief	Declares the inventory menu class
 **************************************************************************************************/

#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"
#include "Objects.h"
#include "EntityClass.h"

//fwd declaation to prevent circular dependencies
class EncounterInstance;

class InventoryMenu
{
	public:

		/**********************************************************************************************//**
		 * @fn	InventoryMenu::InventoryMenu();
		 *
		 * @brief	Default constructor
		 *
		 * @author	Brendan B
		 * @date	9/4/2018
		 **************************************************************************************************/

		InventoryMenu();
		

		/**********************************************************************************************//**
		 * @fn	ObjectClass* InventoryMenu::InventoryMenuRun(EntityClass &Source, std::vector<std::vector<Tile>>&TileMap);
		 *
		 * @brief	Inventory menu run
		 *
		 * @author	Brendan B
		 * @date	9/4/2018
		 *
		 * @param [in,out]	Source 	Entity opening item menu
		 * @param [in,out]	TileMap	The tile map this is happening on
		 *
		 * @return	Null if it fails, else a pointer to the ObjectClass.
		 **************************************************************************************************/

		ObjectClass* InventoryMenuRun(EntityClass &Source, std::vector<std::vector<Tile>>&TileMap);

		/**********************************************************************************************//**
		 * @fn	static void InventoryMenu::vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *m_event, kiss_textbox *m_textbox2, int *m_draw);
		 *
		 * @brief	Vscrollbar 1 event to handle scrolling
		 *
		 * @author	Brendan B
		 * @date	9/4/2018
		 *
		 * @param [in,out]	vscrollbar	If non-null, the vscrollbar.
		 * @param [in,out]	m_event   	If non-null, the event.
		 * @param [in,out]	m_textbox2	If non-null, the second textbox.
		 * @param [in,out]	m_draw	  	If non-null, the draw.
		 **************************************************************************************************/

		static void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *m_event, kiss_textbox *m_textbox2, int *m_draw);

		/**********************************************************************************************//**
		 * @fn	static void InventoryMenu::textbox1_event(kiss_textbox *textbox, SDL_Event *m_event, kiss_vscrollbar *vscrollbar2, kiss_entry *m_entry, int *m_draw);
		 *
		 * @brief	Textbox 1 event
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
		 * @fn	static void InventoryMenu::text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);
		 *
		 * @brief	Text reset
		 *
		 * @author	Brendan B
		 * @date	9/4/2018
		 *
		 * @param [in,out]	textbox   	If non-null, the textbox.
		 * @param [in,out]	vscrollbar	If non-null, the vscrollbar.
		 **************************************************************************************************/

		static void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);

		/**********************************************************************************************//**
		 * @fn	static void InventoryMenu::button_cancel_event(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw);
		 *
		 * @brief	Button cancel event
		 *
		 * @author	Brendan B
		 * @date	9/4/2018
		 *
		 * @param [in,out]	button 	If non-null, the button.
		 * @param [in,out]	m_event	If non-null, the event.
		 * @param [in,out]	m_quit 	If non-null, the quit.
		 * @param [in,out]	m_draw 	If non-null, the draw.
		 **************************************************************************************************/

		static void button_cancel_event(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw);

		/**********************************************************************************************//**
		 * @fn	void InventoryMenu::button_ok1_event(kiss_button *button, SDL_Event *m_event, kiss_window *window1, kiss_label *m_label_sel, kiss_entry *m_entry, kiss_label *m_label_res, int *m_draw, EntityClass& Source);
		 *
		 * @brief	Button ok 1 event
		 *
		 * @author	Brendan B
		 * @date	9/4/2018
		 *
		 * @param [in,out]	button	   	If non-null, the button.
		 * @param [in,out]	m_event	   	If non-null, the event.
		 * @param [in,out]	window1	   	If non-null, the first window.
		 * @param [in,out]	m_label_sel	If non-null, the label selected.
		 * @param [in,out]	m_entry	   	If non-null, the entry.
		 * @param [in,out]	m_label_res	If non-null, the label resource.
		 * @param [in,out]	m_draw	   	If non-null, the draw.
		 * @param [in,out]	Source	   	Source entity whose inventory is being manipulated
		 **************************************************************************************************/

		void button_ok1_event(kiss_button *button, SDL_Event *m_event, kiss_window *window1, kiss_label *m_label_sel,
			kiss_entry *m_entry, kiss_label *m_label_res, int *m_draw, EntityClass& Source);

		/**********************************************************************************************//**
		 * @fn	void InventoryMenu::SwapButtonEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, EntityClass& Source);
		 *
		 * @brief	Swap button event
		 *
		 * @author	Brendan B
		 * @date	9/4/2018
		 *
		 * @param [in,out]	button 	If non-null, the button.
		 * @param [in,out]	m_event	If non-null, the event.
		 * @param [in,out]	m_quit 	If non-null, the quit.
		 * @param [in,out]	m_draw 	If non-null, the draw.
		 * @param [in,out]	Source 	Source entity whose inventory is being used
		 **************************************************************************************************/

		void SwapButtonEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, EntityClass& Source);

		/**********************************************************************************************//**
		 * @fn	void InventoryMenu::DropButtonEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, kiss_entry* m_entry, EntityClass& Source, std::vector<std::vector<Tile>>&TileMap);
		 *
		 * @brief	Drop button event
		 *
		 * @author	Brendan B
		 * @date	9/4/2018
		 *
		 * @param [in,out]	button 	If non-null, the button.
		 * @param [in,out]	m_event	If non-null, the event.
		 * @param [in,out]	m_quit 	If non-null, the quit.
		 * @param [in,out]	m_draw 	If non-null, the draw.
		 * @param [in,out]	m_entry	If non-null, the entry.
		 * @param [in,out]	Source 	Source entity for the inventory
		 * @param [in,out]	TileMap	The tile map.
		 **************************************************************************************************/

		void DropButtonEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, kiss_entry* m_entry, EntityClass& Source, std::vector<std::vector<Tile>>&TileMap);

		/**********************************************************************************************//**
		 * @fn	void InventoryMenu::TwoHandButtonEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, EntityClass& Source);
		 *
		 * @brief	Two hand button event
		 *
		 * @author	Brendan B
		 * @date	9/4/2018
		 *
		 * @param [in,out]	button 	If non-null, the button.
		 * @param [in,out]	m_event	If non-null, the event.
		 * @param [in,out]	m_quit 	If non-null, the quit.
		 * @param [in,out]	m_draw 	If non-null, the draw.
		 * @param [in,out]	Source 	Source entity for the inventory
		 **************************************************************************************************/

		void TwoHandButtonEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, EntityClass& Source);

		/**********************************************************************************************//**
		 * @fn	void InventoryMenu::EquipButtonEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, kiss_entry* m_entry, EntityClass& Source);
		 *
		 * @brief	Equip button event
		 *
		 * @author	Brendan B
		 * @date	9/4/2018
		 *
		 * @param [in,out]	button 	If non-null, the button.
		 * @param [in,out]	m_event	If non-null, the event.
		 * @param [in,out]	m_quit 	If non-null, the quit.
		 * @param [in,out]	m_draw 	If non-null, the draw.
		 * @param [in,out]	m_entry	If non-null, the entry.
		 * @param [in,out]	Source 	Source entity for the inventory
		 **************************************************************************************************/

		void EquipButtonEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, kiss_entry* m_entry, EntityClass& Source);

		/**********************************************************************************************//**
		 * @fn	void InventoryMenu::RepopulateList(EntityClass& Source);
		 *
		 * @brief	Repopulate list, populates the textbox, and attaches prefixes to where each item is located
		 *
		 * @author	Brendan B
		 * @date	9/4/2018
		 *
		 * @param [in,out]	Source	Source entity for the inventory being worked with
		 **************************************************************************************************/

		void RepopulateList(EntityClass& Source);

	private:
		/** @brief	The selected item */
		ObjectClass * m_SelectedItem = NULL;
		/** @brief	The object equipped */
		bool m_ObjectEquipped;
		/** @brief	The renderer */
		SDL_Renderer* m_renderer;
		/** @brief	the event being processed */
		SDL_Event m_event;

		 /** @brief	The arrays used by kiss_sdl */
		kiss_array m_objects, m_array1;
		/** @brief	The items */
		kiss_window m_MainWindow;
		/** @brief	The items */
		kiss_label m_ItemsTextBoxLabel = { 0 }, m_label_sel = { 0 }, m_label_res = { 0 };
		/** @brief	The two hand button, dropbutton, button cancel, swap button, equip button */
		kiss_button m_TwoHandButton = { 0 }, m_DropButton = { 0 }, m_button_cancel = { 0 }, m_SwapButton = { 0 }, m_EquipButton = { 0 };
		/** @brief	The items */
		kiss_textbox m_Items = { 0 };
		/** @brief	The first vscrollbar */
		kiss_vscrollbar m_vscrollbar1 = { 0 };
		/** @brief	The entry */
		kiss_entry m_entry = { 0 };

		/** @brief	The dimensions of textbox, window2, draw and quit */
		int m_textbox_width, m_textbox_height, m_window2_width, m_window2_height, m_draw, m_quit;
};