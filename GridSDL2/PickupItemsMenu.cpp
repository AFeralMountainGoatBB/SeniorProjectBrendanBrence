#include "PickupItemsMenu.h"

PickupItemsMenu::PickupItemsMenu()
{
	m_quit = 0;
	m_draw = 1;
	m_textbox_width = 250;
	m_textbox_height = 250;
	m_renderer = kiss_init("PickupItemsMenu", &m_objects, 640, 480);
	if (!m_renderer)
	{
		std::cout << "Renderer wrong" << std::endl;
		return;
	}
	kiss_array_new(&m_array1);
	kiss_array_append(&m_objects, ARRAY_TYPE, &m_array1);

	
	/* Arrange the widgets nicely relative to each other */
	kiss_window_new(&m_MainWindow, NULL, 1, 0, 0, kiss_screen_width, kiss_screen_height);

	kiss_textbox_new(&m_textbox1, &m_MainWindow, 1, &m_array1, kiss_screen_width / 3, 3 * kiss_normal.h - kiss_screen_height / 15, m_textbox_width, m_textbox_height);
	kiss_vscrollbar_new(&m_vscrollbar1, &m_MainWindow, m_textbox1.rect.x + m_textbox_width, m_textbox1.rect.y, m_textbox_height);
	kiss_label_new(&m_ItemsTextBoxLabel, &m_MainWindow, "m_Items", m_textbox1.rect.x + kiss_edge, m_textbox1.rect.y - kiss_textfont.lineheight);
	kiss_entry_new(&m_entry, &m_MainWindow, 1, "Select Item to pickup", kiss_screen_width / 10, m_textbox1.rect.y + m_textbox_height, 2 * m_textbox_width + 2 * kiss_up.w + kiss_edge);
	kiss_button_new(&m_button_cancel, &m_MainWindow, "Cancel", m_entry.rect.x + m_entry.rect.w - kiss_edge - kiss_normal.w, m_entry.rect.y + m_entry.rect.h + kiss_normal.h);
	kiss_button_new(&m_Main_ok_button, &m_MainWindow, "OK", m_button_cancel.rect.x - 2 * kiss_normal.w, m_button_cancel.rect.y);	

	m_entry.selectedIndex = -1;

	m_MainWindow.visible = 1;
	//end setup

}

void PickupItemsMenu::text_reset(kiss_textbox *a_textbox, kiss_vscrollbar *a_vscrollbar)
{
	qsort(a_textbox->array->data, a_textbox->array->length, sizeof(void *), kiss_string_compare);
	a_vscrollbar->step = 0.;
	if (a_textbox->array->length - a_textbox->maxlines > 0)
		a_vscrollbar->step = 1. / (a_textbox->array->length - a_textbox->maxlines);
	a_textbox->firstline = 0;
	a_textbox->highlightline = -1;
	a_vscrollbar->fraction = 0.;
}


/* The widget arguments are widgets that this widget talks with */
void PickupItemsMenu::textbox1_event(kiss_textbox *a_textbox, SDL_Event *a_event, kiss_vscrollbar *a_vscrollbar2, kiss_entry *a_entry, int *a_draw)
{
	int index;

	if (kiss_textbox_event(a_textbox, a_event, a_draw)) {
		index = a_textbox->firstline + a_textbox->selectedline;
		if (strcmp((char *)kiss_array_data(a_textbox->array, index), "")) {
			kiss_string_copy(a_entry->text, a_entry->textwidth / kiss_textfont.advance, (char *)kiss_array_data(a_textbox->array, index), NULL);
			*a_draw = 1;
			a_entry->selectedIndex = a_textbox->selectedline;
			std::cout << a_textbox->selectedline << std::endl;
		}
	}
}

void PickupItemsMenu::vscrollbar1_event(kiss_vscrollbar *a_vscrollbar, SDL_Event *a_event, kiss_textbox *a_textbox2, int *a_draw)
{
	int firstline;

	if (kiss_vscrollbar_event(a_vscrollbar, a_event, a_draw) &&
		a_textbox2->array->length) {
		firstline = (int)((a_textbox2->array->length -
			a_textbox2->maxlines) * a_vscrollbar->fraction + 0.5);
		if (firstline >= 0) a_textbox2->firstline = firstline;
		*a_draw = 1;
	}
}

void PickupItemsMenu::button_ok1_event(kiss_button *a_button, SDL_Event *a_event, kiss_window *a_window1, kiss_label *a_label_sel,
	kiss_entry *m_entry, kiss_label *a_label_res, int *a_draw, std::vector<ObjectClass*> a_ObjectVector)
{
	if (m_entry->selectedIndex < 0)
		return;
	char buf[KISS_MAX_LENGTH];
	if (kiss_button_event(a_button, a_event, a_draw)) {
		kiss_string_copy(buf, 
		kiss_maxlength(kiss_textfont, a_window1->rect.w - 2 * kiss_vslider.w, a_label_sel->text, m_entry->text), a_label_sel->text, m_entry->text);
		this->m_SelectedItem = a_ObjectVector[m_entry->selectedIndex];
		a_window1->focus = 0;
		a_button->prelight = 0;
	
		*a_draw = 1;
		m_quit = 1;
	}
}

void PickupItemsMenu::button_cancel_event(kiss_button *a_button, SDL_Event *a_event, int *a_quit, int *a_draw)
{
	if (kiss_button_event(a_button, a_event, a_draw))
	{
		*a_quit = 1;
	}
}

ObjectClass* PickupItemsMenu::PickupItemsRun(Tile &a_tile)
{
	RepopulateList(a_tile);
	while (!m_quit) {
		/* Some code may be written here */
		SDL_Delay(10);
		while (SDL_PollEvent(&m_event)) {
			if (m_event.type == SDL_QUIT)
				m_quit = 1;

			kiss_window_event(&m_MainWindow, &m_event, &m_draw);

			textbox1_event(&m_textbox1, &m_event, &m_vscrollbar1, &m_entry, &m_draw);
			vscrollbar1_event(&m_vscrollbar1, &m_event, &m_textbox1, &m_draw);
			button_ok1_event(&m_Main_ok_button, &m_event, &m_MainWindow, &m_label_sel, &m_entry, &m_label_res, &m_draw, a_tile.GetItemsPresent());
			button_cancel_event(&m_button_cancel, &m_event, &m_quit, &m_draw);
			kiss_entry_event(&m_entry, &m_event, &m_draw);
			
		}

		vscrollbar1_event(&m_vscrollbar1, NULL, &m_textbox1, &m_draw);

		if (!m_draw) continue;
		SDL_RenderClear(m_renderer);

		kiss_window_draw(&m_MainWindow, m_renderer);
		kiss_label_draw(&m_ItemsTextBoxLabel, m_renderer);

		kiss_vscrollbar_draw(&m_vscrollbar1, m_renderer);
		kiss_textbox_draw(&m_textbox1, m_renderer);
		kiss_label_draw(&m_label_sel, m_renderer);
		kiss_entry_draw(&m_entry, m_renderer);
		kiss_button_draw(&m_Main_ok_button, m_renderer);
		kiss_button_draw(&m_button_cancel, m_renderer);
	
		kiss_label_draw(&m_label_res, m_renderer);
		kiss_button_draw(&m_Secondary_ok_button, m_renderer);

		SDL_RenderPresent(m_renderer);
		m_draw = 0;
	}
	kiss_clean(&m_objects);
	return m_SelectedItem;
}

void PickupItemsMenu::RepopulateList(Tile a_tile)
{
	if (!a_tile.GetTopObject())
	{
		std::cout << "No items present in this a_tile" << std::endl;
		return;
	}

	std::cout << "Populating list" << std::endl;
	for (auto i = a_tile.GetItemsPresent().begin(); i < a_tile.GetItemsPresent().end(); i++)
	{
		std::cout << "enter loop" << std::endl;
		std::cout << (*i)->GetName() << std::endl;
		std::string temp = (*i)->GetName();
		char *ItemNameCstring= new char[temp.length() + 1];
		strcpy(ItemNameCstring, temp.c_str());
		kiss_array_appendstring(m_textbox1.array, 0, ItemNameCstring, NULL);
		
	}
	

}