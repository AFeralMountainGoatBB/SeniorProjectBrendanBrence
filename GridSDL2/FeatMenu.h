#pragma once
#include "GeneralHeaders.h"
#include "StaticFunctions.h"
#include "Feats.h"
#include "EntityClass.h"

class FeatMenu
{

public:
	FeatMenu();

	SDL_Renderer* renderer;
	//variables
	SDL_Event e;

	//widgets start
	kiss_array objects, a1;
	kiss_window MainWindow, DescriptionWindow;
	kiss_label FeatsTextBoxLabel = { 0 }, label_sel = { 0 }, label_res = { 0 }, Descript1 = { 0 }, Descript2 = { 0 }, Descript3 = { 0 };
	kiss_button ToggleFeatButton = { 0 }, IncreaseFeatButton = { 0 }, DecreaseFeatButton = { 0 }, button_cancel = { 0 }, FeatDescriptionButton = { 0 }, DescriptionOkButton = { 0 };
	kiss_textbox Feats = { 0 };
	kiss_vscrollbar vscrollbar1 = { 0 };
	kiss_entry entry = { 0 };
	int textbox_width, textbox_height, window2_width, window2_height, draw, quit;

	//events

	void FeatMenuRun(EntityClass &Source);
	void InventoryMenuUpdate(SDL_Renderer *& renderer);

	static void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e, kiss_textbox *textbox2, int *draw);
	static void textbox1_event(kiss_textbox *textbox, SDL_Event *e, kiss_vscrollbar *vscrollbar2, kiss_entry *entry, int *draw);
	static void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);

	static void button_cancel_event(kiss_button *button, SDL_Event *e, int *quit, int *draw);
	void CloseDescriptionEvent(kiss_button *button, SDL_Event *e, kiss_window *window1, kiss_label *label_sel,
		kiss_entry *entry, kiss_label *label_res, int *draw, EntityClass& Source);


	void IncreaseFeatEvent(kiss_button *button, SDL_Event *e, int *quit, int *draw, kiss_entry * entry, EntityClass& Source);
	void DecreaseFeatEvent(kiss_button *button, SDL_Event *e, int *quit, int *draw, kiss_entry * entry, EntityClass& Source);
	void ToggleFeatEvent(kiss_button *button, SDL_Event *e, int *quit, int *draw, kiss_entry * entry, EntityClass& Source);
	void ViewFeatDescriptionEvent(kiss_button *button, SDL_Event *e, int *quit, int *draw, kiss_entry* entry, EntityClass& Source);
	
	void RepopulateList(EntityClass& Source);

private:
	ObjectClass * SelectedItem = NULL;
};