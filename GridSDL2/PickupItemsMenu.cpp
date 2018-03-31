#include "PickupItemsMenu.h"

PickupItemsMenu::PickupItemsMenu()
{
	quit = 0;
	draw = 1;
	textbox_width = 250;
	textbox_height = 250;
	renderer = kiss_init("PickupItemsMenu", &objects, 640, 480);
	if (!renderer)
	{
		std::cout << "Renderer wrong" << std::endl;
		return;
	}
	kiss_array_new(&a1);
	kiss_array_append(&objects, ARRAY_TYPE, &a1);

	
	/* Arrange the widgets nicely relative to each other */
	kiss_window_new(&MainWindow, NULL, 1, 0, 0, kiss_screen_width, kiss_screen_height);

	kiss_textbox_new(&textbox1, &MainWindow, 1, &a1, kiss_screen_width / 3, 3 * kiss_normal.h - kiss_screen_height / 15, textbox_width, textbox_height);
	kiss_vscrollbar_new(&vscrollbar1, &MainWindow, textbox1.rect.x + textbox_width, textbox1.rect.y, textbox_height);
	kiss_label_new(&ItemsTextBoxLabel, &MainWindow, "Items", textbox1.rect.x + kiss_edge, textbox1.rect.y - kiss_textfont.lineheight);
	kiss_entry_new(&entry, &MainWindow, 1, "Select Item to pickup", kiss_screen_width / 10, textbox1.rect.y + textbox_height, 2 * textbox_width + 2 * kiss_up.w + kiss_edge);
	kiss_button_new(&button_cancel, &MainWindow, "Cancel", entry.rect.x + entry.rect.w - kiss_edge - kiss_normal.w, entry.rect.y + entry.rect.h + kiss_normal.h);
	kiss_button_new(&Main_ok_button, &MainWindow, "OK", button_cancel.rect.x - 2 * kiss_normal.w, button_cancel.rect.y);	

	MainWindow.visible = 1;
	//end setup

}

void PickupItemsMenu::text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar)
{
	qsort(textbox->array->data, textbox->array->length, sizeof(void *), kiss_string_compare);
	vscrollbar->step = 0.;
	if (textbox->array->length - textbox->maxlines > 0)
		vscrollbar->step = 1. / (textbox->array->length - textbox->maxlines);
	textbox->firstline = 0;
	textbox->highlightline = -1;
	vscrollbar->fraction = 0.;
}


/* The widget arguments are widgets that this widget talks with */
void PickupItemsMenu::textbox1_event(kiss_textbox *textbox, SDL_Event *e, kiss_vscrollbar *vscrollbar2, kiss_entry *entry, int *draw)
{
	int index;

	if (kiss_textbox_event(textbox, e, draw)) {
		index = textbox->firstline + textbox->selectedline;
		if (strcmp((char *)kiss_array_data(textbox->array, index), "")) {
			kiss_string_copy(entry->text, entry->textwidth / kiss_textfont.advance, (char *)kiss_array_data(textbox->array, index), NULL);
			*draw = 1;
			entry->selectedIndex = textbox->selectedline;
			std::cout << textbox->selectedline << std::endl;
		}
	}
}

void PickupItemsMenu::vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e, kiss_textbox *textbox2, int *draw)
{
	int firstline;

	if (kiss_vscrollbar_event(vscrollbar, e, draw) &&
		textbox2->array->length) {
		firstline = (int)((textbox2->array->length -
			textbox2->maxlines) * vscrollbar->fraction + 0.5);
		if (firstline >= 0) textbox2->firstline = firstline;
		*draw = 1;
	}
}

void PickupItemsMenu::button_ok1_event(kiss_button *button, SDL_Event *e, kiss_window *window1, kiss_label *label_sel,
	kiss_entry *entry, kiss_label *label_res, int *draw, std::vector<ObjectClass*> ObjectVector)
{
	char buf[KISS_MAX_LENGTH];
	if (kiss_button_event(button, e, draw)) {
		kiss_string_copy(buf, 
		kiss_maxlength(kiss_textfont, window1->rect.w - 2 * kiss_vslider.w, label_sel->text, entry->text), label_sel->text, entry->text);
		
		this->SelectedItem = ObjectVector[entry->selectedIndex];
		window1->focus = 0;
		button->prelight = 0;
	
		*draw = 1;
		quit = 1;
	}
}

void PickupItemsMenu::button_cancel_event(kiss_button *button, SDL_Event *e, int *quit, int *draw)
{
	if (kiss_button_event(button, e, draw))
	{
		*quit = 1;
	}
}

ObjectClass* PickupItemsMenu::PickupItemsRun(Tile &tile)
{
	RepopulateList(tile);
	while (!quit) {
		/* Some code may be written here */
		SDL_Delay(10);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = 1;

			kiss_window_event(&MainWindow, &e, &draw);

			textbox1_event(&textbox1, &e, &vscrollbar1, &entry, &draw);
			vscrollbar1_event(&vscrollbar1, &e, &textbox1, &draw);
			button_ok1_event(&Main_ok_button, &e, &MainWindow, &label_sel, &entry, &label_res, &draw, tile.GetItemsPresent());
			button_cancel_event(&button_cancel, &e, &quit, &draw);
			kiss_entry_event(&entry, &e, &draw);
			
		}

		vscrollbar1_event(&vscrollbar1, NULL, &textbox1, &draw);

		if (!draw) continue;
		SDL_RenderClear(renderer);

		kiss_window_draw(&MainWindow, renderer);
		kiss_label_draw(&ItemsTextBoxLabel, renderer);

		kiss_vscrollbar_draw(&vscrollbar1, renderer);
		kiss_textbox_draw(&textbox1, renderer);
		kiss_label_draw(&label_sel, renderer);
		kiss_entry_draw(&entry, renderer);
		kiss_button_draw(&Main_ok_button, renderer);
		kiss_button_draw(&button_cancel, renderer);
	
		kiss_label_draw(&label_res, renderer);
		kiss_button_draw(&Secondary_ok_button, renderer);

		SDL_RenderPresent(renderer);
		draw = 0;
	}
	kiss_clean(&objects);
	return SelectedItem;
}

void PickupItemsMenu::RepopulateList(Tile tile)
{
	if (!tile.GetTopObject())
	{
		std::cout << "No items present in this tile" << std::endl;
		return;
	}

	std::cout << "Populating list" << std::endl;
	for (auto i = tile.GetItemsPresent().begin(); i < tile.GetItemsPresent().end(); i++)
	{
		std::cout << "enter loop" << std::endl;
		std::cout << (*i)->GetName() << std::endl;
		std::string temp = (*i)->GetName();
		char *ItemNameCstring= new char[temp.length() + 1];
		strcpy(ItemNameCstring, temp.c_str());
		kiss_array_appendstring(textbox1.array, 0, ItemNameCstring, NULL);
		
	}
	

}