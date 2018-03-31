#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"
#include "Tile.h"
#include "Objects.h"

class EncounterInstance;

class PickupItemsMenu {
public:
	PickupItemsMenu();

	SDL_Renderer* renderer;
	//variables
	SDL_Event e;

	//widgets start
	
	kiss_array objects, a1;
	kiss_window MainWindow;
	kiss_label ItemsTextBoxLabel = { 0 }, label_sel = { 0 }, label_res = { 0 };
	kiss_button Main_ok_button = { 0 }, Secondary_ok_button = { 0 }, button_cancel = { 0 };
	kiss_textbox textbox1 = { 0 };
	kiss_vscrollbar vscrollbar1 = { 0 };
	kiss_entry entry = { 0 };
	int textbox_width, textbox_height, window2_width, window2_height, draw, quit;

	//events
	
	ObjectClass* PickupItemsRun(Tile &tile);
	void PickupMenuUpdate(SDL_Renderer *& renderer);

	static void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e, kiss_textbox *textbox2, int *draw);
	static void textbox1_event(kiss_textbox *textbox, SDL_Event *e, kiss_vscrollbar *vscrollbar2, kiss_entry *entry, int *draw);
	static void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);

	static void button_cancel_event(kiss_button *button, SDL_Event *e, int *quit, int *draw);
	void button_ok1_event(kiss_button *button, SDL_Event *e, kiss_window *window1, kiss_label *label_sel,
		kiss_entry *entry, kiss_label *label_res, int *draw, std::vector<ObjectClass*> ObjectVector);

	void RepopulateList(Tile SelectedTile);

	ObjectClass* GetSelectedItem();
	void SetSelectedItem();
private:
	ObjectClass* SelectedItem = NULL;
};