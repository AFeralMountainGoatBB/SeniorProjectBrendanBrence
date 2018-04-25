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

		SDL_Renderer* renderer;
		//variables
		SDL_Event e;

		//widgets start
		kiss_array objects, a1;
		kiss_window MainWindow;
		kiss_label ItemsTextBoxLabel = { 0 }, label_sel = { 0 }, label_res = { 0 };
		kiss_button TwoHandButton = { 0 }, DropButton = { 0 }, button_cancel = { 0 }, SwapButton = { 0 }, EquipButton = { 0 };
		kiss_textbox Items = { 0 };
		kiss_vscrollbar vscrollbar1 = { 0 };
		kiss_entry entry = { 0 };
		int textbox_width, textbox_height, window2_width, window2_height, draw, quit;
		
		//events

		ObjectClass* InventoryMenuRun(EntityClass &Source, std::vector<std::vector<Tile>>&TileMap);
		void InventoryMenuUpdate(SDL_Renderer *& renderer);

		static void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e, kiss_textbox *textbox2, int *draw);
		static void textbox1_event(kiss_textbox *textbox, SDL_Event *e, kiss_vscrollbar *vscrollbar2, kiss_entry *entry, int *draw);
		static void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);
		
		static void button_cancel_event(kiss_button *button, SDL_Event *e, int *quit, int *draw);
		void button_ok1_event(kiss_button *button, SDL_Event *e, kiss_window *window1, kiss_label *label_sel,
			kiss_entry *entry, kiss_label *label_res, int *draw, EntityClass& Source);

		void SwapButtonEvent(kiss_button *button, SDL_Event *e, int *quit, int *draw, EntityClass& Source);
		void DropButtonEvent(kiss_button *button, SDL_Event *e, int *quit, int *draw, kiss_entry* entry, EntityClass& Source, std::vector<std::vector<Tile>>&TileMap);
		void TwoHandButtonEvent(kiss_button *button, SDL_Event *e, int *quit, int *draw, EntityClass& Source);
		void EquipButtonEvent(kiss_button *button, SDL_Event *e, int *quit, int *draw, kiss_entry* entry, EntityClass& Source);

		void RepopulateList(EntityClass& Source);

		ObjectClass* GetSelectedItem();
		void SetSelectedItem();
	private:
		ObjectClass * SelectedItem = NULL;
		bool ObjectEquipped;
};