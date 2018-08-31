#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"
#include "Objects.h"
#include "EntityClass.h"

class EncounterInstance;
class InventoryMenu
{
	public:
		InventoryMenu();
		
		//events

		ObjectClass* InventoryMenuRun(EntityClass &Source, std::vector<std::vector<Tile>>&TileMap);
		void InventoryMenuUpdate(SDL_Renderer *& m_renderer);

		static void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *m_event, kiss_textbox *m_textbox2, int *m_draw);
		static void textbox1_event(kiss_textbox *textbox, SDL_Event *m_event, kiss_vscrollbar *vscrollbar2, kiss_entry *m_entry, int *m_draw);
		static void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);
		
		static void button_cancel_event(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw);
		void button_ok1_event(kiss_button *button, SDL_Event *m_event, kiss_window *window1, kiss_label *m_label_sel,
			kiss_entry *m_entry, kiss_label *m_label_res, int *m_draw, EntityClass& Source);

		void SwapButtonEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, EntityClass& Source);
		void DropButtonEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, kiss_entry* m_entry, EntityClass& Source, std::vector<std::vector<Tile>>&TileMap);
		void TwoHandButtonEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, EntityClass& Source);
		void EquipButtonEvent(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw, kiss_entry* m_entry, EntityClass& Source);

		void RepopulateList(EntityClass& Source);

		ObjectClass* GetSelectedItem();
		void SetSelectedItem();
	private:
		ObjectClass * m_SelectedItem = NULL;
		bool m_ObjectEquipped;

		SDL_Renderer* m_renderer;
		//variables
		SDL_Event m_event;

		//widgets start
		kiss_array m_objects, m_array1;
		kiss_window m_MainWindow;
		kiss_label m_ItemsTextBoxLabel = { 0 }, m_label_sel = { 0 }, m_label_res = { 0 };
		kiss_button m_TwoHandButton = { 0 }, m_DropButton = { 0 }, m_button_cancel = { 0 }, m_SwapButton = { 0 }, m_EquipButton = { 0 };
		kiss_textbox m_Items = { 0 };
		kiss_vscrollbar m_vscrollbar1 = { 0 };
		kiss_entry m_entry = { 0 };
		int m_textbox_width, m_textbox_height, m_window2_width, m_window2_height, m_draw, m_quit;
};