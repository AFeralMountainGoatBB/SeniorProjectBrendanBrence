#include "FeatMenu.h"


FeatMenu::FeatMenu()
{
	m_quit = 0;
	m_draw = 1;
	m_textbox_width = 400;
	m_textbox_height = 250;
	m_renderer = kiss_init("FeatMenu", &m_objects, 640, 480);
	if (!m_renderer)
	{
		std::cout << "Renderer wrong" << std::endl;
		return;
	}
	kiss_array_new(&m_array1);
	kiss_array_append(&m_objects, ARRAY_TYPE, &m_array1);


	/* Arrange the widgets nicely relative to each other */
	kiss_window_new(&m_MainWindow, NULL, 1, 0, 0, kiss_screen_width, kiss_screen_height);


	kiss_textbox_new(&m_Feats, &m_MainWindow, 1, &m_array1, kiss_screen_width *0.15, 3 * kiss_normal.h - kiss_screen_height / 15, m_textbox_width+50, m_textbox_height);
	kiss_vscrollbar_new(&m_vscrollbar1, &m_MainWindow, m_Feats.rect.x + m_textbox_width, m_Feats.rect.y, m_textbox_height);
	kiss_label_new(&m_FeatsTextBoxLabel, &m_MainWindow, "m_Feats", m_Feats.rect.x + kiss_edge, m_Feats.rect.y - kiss_textfont.lineheight);
	kiss_entry_new(&m_entry, &m_MainWindow, 1, "Select Item to interact with", kiss_screen_width / 10, m_Feats.rect.y + m_textbox_height, m_textbox_width + 2 * kiss_up.w + kiss_edge);
	
	kiss_button_new(&m_ToggleFeatButton, &m_MainWindow, "Toggle", kiss_screen_width*.5 - (.5*kiss_normal.w), m_entry.rect.y + m_entry.rect.h + 10);
	kiss_button_new(&m_IncreaseFeatButton, &m_MainWindow, "+", m_ToggleFeatButton.rect.x+60, m_ToggleFeatButton.rect.y);
	kiss_button_new(&m_DecreaseFeatButton, &m_MainWindow, "-", m_ToggleFeatButton.rect.x-60, m_ToggleFeatButton.rect.y);
	kiss_button_new(&m_FeatDescriptionButton, &m_MainWindow, "Description", m_ToggleFeatButton.rect.x, m_ToggleFeatButton.rect.y + 30);
	kiss_button_new(&m_button_cancel, &m_MainWindow, "Cancel", m_FeatDescriptionButton.rect.x, m_FeatDescriptionButton.rect.y + 30);


	kiss_window_new(&m_DescriptionWindow, NULL, 1, 0, 0, 200, 200);
	kiss_button_new(&m_DescriptionOkButton, &m_DescriptionWindow, "OK", m_DescriptionWindow.rect.w / 2 - m_DescriptionOkButton.rect.x / 2, m_DescriptionWindow.rect.h*.8);
	kiss_label_new(&m_Descript1, &m_DescriptionWindow, "", m_DescriptionWindow.rect.w*0.2, m_DescriptionWindow.rect.h*0.2);
	kiss_label_new(&m_Descript2, &m_DescriptionWindow, "", m_Descript1.rect.x,m_Descript1.rect.y+m_Descript1.rect.h+5);
	kiss_label_new(&m_Descript3, &m_DescriptionWindow, "", m_Descript2.rect.x, m_Descript2.rect.y + m_Descript2.rect.h + 5);


	m_MainWindow.visible = 1;
	m_DescriptionWindow.visible = 0;
	//end setup

}

void FeatMenu::text_reset(kiss_textbox *a_textbox, kiss_vscrollbar *a_vscrollbar)
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
void FeatMenu::textbox1_event(kiss_textbox *a_textbox, SDL_Event *a_event, kiss_vscrollbar *a_vscrollbar2, kiss_entry *a_entry, int *a_draw)
{
	int index;

	if (kiss_textbox_event(a_textbox, a_event, a_draw)) {
		index = a_textbox->firstline + a_textbox->selectedline;
		if (strcmp((char *)kiss_array_data(a_textbox->array, index), "")) {
			kiss_string_copy(a_entry->text, a_entry->textwidth / kiss_textfont.advance, (char *)kiss_array_data(a_textbox->array, index), NULL);
			*a_draw = 1;
			a_entry->selectedIndex = a_textbox->selectedline;
			//std::cout << a_textbox->selectedline << std::endl;
		}
	}
}

void FeatMenu::vscrollbar1_event(kiss_vscrollbar *a_vscrollbar, SDL_Event *a_event, kiss_textbox *a_textbox2, int *a_draw)
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

void FeatMenu::CloseDescriptionEvent(kiss_button *a_button, SDL_Event *a_event, kiss_window *a_window1, kiss_label *a_label_sel,
	kiss_entry *a_entry, kiss_label *a_label_res, int *a_Source, EntityClass& Source)
{
	char buf[KISS_MAX_LENGTH];
	if (kiss_button_event(a_button, a_event, a_Source)) {
		kiss_string_copy(buf,
			kiss_maxlength(kiss_textfont, a_window1->rect.w - 2 * kiss_vslider.w, a_label_sel->text, a_entry->text), a_label_sel->text, a_entry->text);
		if (a_entry->selectedIndex > 2)
			//this->m_SelectedItem = a_Source.GetBackPack().GetItems()[a_entry->selectedIndex];

			a_window1->focus = 0;
		a_button->prelight = 0;

		*a_Source = 1;
		m_quit = 1;
	}
}

void FeatMenu::button_cancel_event(kiss_button *a_button, SDL_Event *a_event, int *a_quit, int *a_draw)
{
	if (kiss_button_event(a_button, a_event, a_draw))
	{
		*a_quit = 1;
	}
}

void FeatMenu::FeatMenuRun(EntityClass &a_Source)
{
	RepopulateList(a_Source);
	while (!m_quit) {
		/* Some code may be written here */
		SDL_Delay(10);
		while (SDL_PollEvent(&m_event)) {
			if (m_event.type == SDL_QUIT)
				m_quit = 1;

			kiss_window_event(&m_MainWindow, &m_event, &m_draw);

			textbox1_event(&m_Feats, &m_event, &m_vscrollbar1, &m_entry, &m_draw);
			vscrollbar1_event(&m_vscrollbar1, &m_event, &m_Feats, &m_draw);
			button_cancel_event(&m_button_cancel, &m_event, &m_quit, &m_draw);
			ToggleFeatEvent(&m_ToggleFeatButton, &m_event, &m_quit, &m_draw, &m_entry, a_Source);
			IncreaseFeatEvent(&m_IncreaseFeatButton, &m_event, &m_quit, &m_draw, &m_entry, a_Source);
			DecreaseFeatEvent(&m_DecreaseFeatButton, &m_event, &m_quit, &m_draw, &m_entry, a_Source);
			ViewFeatDescriptionEvent(&m_FeatDescriptionButton, &m_event, &m_quit, &m_draw, &m_entry, a_Source);
			kiss_entry_event(&m_entry, &m_event, &m_draw);
		}

		vscrollbar1_event(&m_vscrollbar1, NULL, &m_Feats, &m_draw);

		if (!m_draw) continue;
		SDL_RenderClear(m_renderer);

		kiss_window_draw(&m_MainWindow, m_renderer);
		kiss_label_draw(&m_FeatsTextBoxLabel, m_renderer);

		kiss_vscrollbar_draw(&m_vscrollbar1, m_renderer);
		kiss_textbox_draw(&m_Feats, m_renderer);
		kiss_label_draw(&m_label_sel, m_renderer);

		kiss_label_draw(&m_Descript1, m_renderer);
		kiss_label_draw(&m_Descript2, m_renderer);
		kiss_label_draw(&m_Descript3, m_renderer);

		kiss_entry_draw(&m_entry, m_renderer);
		kiss_button_draw(&m_FeatDescriptionButton, m_renderer);
		kiss_button_draw(&m_ToggleFeatButton, m_renderer);
		kiss_button_draw(&m_IncreaseFeatButton, m_renderer);
		kiss_button_draw(&m_DecreaseFeatButton, m_renderer);
		kiss_button_draw(&m_button_cancel, m_renderer);

		kiss_label_draw(&m_label_res, m_renderer);

		SDL_RenderPresent(m_renderer);
		m_draw = 0;
	}
	kiss_clean(&m_objects);
	return;
}

void FeatMenu::RepopulateList(EntityClass& a_Source)
{
	//std::cout << "Displaying Inventory" << std::endl;
	for (int i = 0; i < m_Feats.array->length;)
	{
		kiss_array_remove(m_Feats.array, i);
	}
	//std::cout << "Checking for togglefeats" << std::endl;
	auto ToggleFeats = a_Source.GetToggleableFeats();
	//toggleable feats
	if (!ToggleFeats.empty())
	{
		//std::cout << "There are toggleable feats." << std::endl;
		for (auto it = ToggleFeats.begin(); it != ToggleFeats.end(); it++)
		{
				std::string temp = (*it)->GetName();
				if ((*it)->GetUsesRangeAbility())
				{
					temp += (": " + std::to_string((*it)->GetCurrentRangeValue()) + "/" + std::to_string((*it)->GetActivatedRange().second));
				}
				else
				{
					temp += ": ";
				}
				if ((*it)->IsActive())
				{
					temp += (" - m_Active");
				}
				else
				{
					temp += (" - Off");
				}
				char *ItemNameCstring = new char[temp.length() + 1];
				strcpy(ItemNameCstring, temp.c_str());
				kiss_array_appendstring(m_Feats.array, 0, ItemNameCstring, NULL);
			}
		}
	else 
	{
		std::string temp = "No Toggleable feats";
		char *ItemNameCstring = new char[temp.length() + 1];
		strcpy(ItemNameCstring, temp.c_str());
		kiss_array_appendstring(m_Feats.array, 0, ItemNameCstring, NULL);
	}
}

void FeatMenu::ToggleFeatEvent(kiss_button *a_button, SDL_Event *a_event, int *a_quit, int *a_draw, kiss_entry* a_entry, EntityClass& a_Source)
{
	if (kiss_button_event(a_button, a_event, a_draw))
	{
		unsigned index = a_entry->selectedIndex;
		if (a_Source.GetToggleableFeats().empty())
		{
			return;
		}
		if (index >= a_Source.GetToggleableFeats().size())
		{
			return;
		}
		a_Source.GetToggleableFeats()[index]->SwitchActive();
		RepopulateList(a_Source);
	}
}

void FeatMenu::ViewFeatDescriptionEvent(kiss_button *a_button, SDL_Event *a_event, int *a_quit, int *a_draw, kiss_entry* a_entry, EntityClass& a_Source)
{
	if (kiss_button_event(a_button, a_event, a_draw))
	{
		unsigned index = a_entry->selectedIndex;
		if (!a_Source.GetToggleableFeats().empty() && index < a_Source.GetToggleableFeats().size())
		{
			
			return;
		}
		//printout to other m_window? std::string desc = a_Source.GetToggleableFeats()[index]
		RepopulateList(a_Source);
	}
}

void FeatMenu::IncreaseFeatEvent(kiss_button *a_button, SDL_Event *a_event, int *a_quit, int *a_draw,kiss_entry * a_entry, EntityClass& a_Source)
{
	if (kiss_button_event(a_button, a_event, a_draw))
	{
		unsigned index = a_entry->selectedIndex;
		if (!a_Source.GetToggleableFeats().empty() && index < a_Source.GetToggleableFeats().size())
		{
			a_Source.GetToggleableFeats()[index]->IncreaseFeat();
		}
		RepopulateList(a_Source);
	}
}

void FeatMenu::DecreaseFeatEvent(kiss_button *a_button, SDL_Event *a_event, int *a_quit, int *a_entry, kiss_entry * m_entry, EntityClass& a_Source)
{
	if (kiss_button_event(a_button, a_event, a_entry))
	{
		unsigned index = m_entry->selectedIndex;
		if (!a_Source.GetToggleableFeats().empty() && index < a_Source.GetToggleableFeats().size())
		{
			a_Source.GetToggleableFeats()[index]->DecreaseFeat();
		}
		RepopulateList(a_Source);
	}
}
