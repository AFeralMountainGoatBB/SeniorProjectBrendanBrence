#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"
#include "Tile.h"
#include "Objects.h"

class EncounterInstance;

class PickupItemsMenu {
public:
	PickupItemsMenu();

	//events
	
	ObjectClass* PickupItemsRun(Tile &tile);
	void PickupMenuUpdate(SDL_Renderer *& m_renderer);

	static void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *m_event, kiss_textbox *m_textbox2, int *m_draw);
	static void textbox1_event(kiss_textbox *textbox, SDL_Event *m_event, kiss_vscrollbar *vscrollbar2, kiss_entry *m_entry, int *m_draw);
	static void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);

	static void button_cancel_event(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw);
	void button_ok1_event(kiss_button *button, SDL_Event *m_event, kiss_window *window1, kiss_label *m_label_sel,
		kiss_entry *m_entry, kiss_label *m_label_res, int *m_draw, std::vector<ObjectClass*> ObjectVector);

	void RepopulateList(Tile SelectedTile);

	ObjectClass* GetSelectedItem();
	void SetSelectedItem();
private:
	ObjectClass* m_SelectedItem = NULL;


	SDL_Renderer* m_renderer;
	//variables
	SDL_Event m_event;

	//widgets start

	kiss_array m_objects, m_array1;
	kiss_window m_MainWindow;
	kiss_label m_ItemsTextBoxLabel = { 0 }, m_label_sel = { 0 }, m_label_res = { 0 };
	kiss_button m_Main_ok_button = { 0 }, m_Secondary_ok_button = { 0 }, m_button_cancel = { 0 };
	kiss_textbox m_textbox1 = { 0 };
	kiss_vscrollbar m_vscrollbar1 = { 0 };
	kiss_entry m_entry = { 0 };
	int m_textbox_width, m_textbox_height, m_window2_width, m_window2_height, m_draw, m_quit;
};