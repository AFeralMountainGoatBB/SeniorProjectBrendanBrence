#include "FeatMenu.h"


FeatMenu::FeatMenu()
{
	quit = 0;
	draw = 1;
	textbox_width = 250;
	textbox_height = 250;
	renderer = kiss_init("FeatMenu", &objects, 640, 480);
	if (!renderer)
	{
		std::cout << "Renderer wrong" << std::endl;
		return;
	}
	kiss_array_new(&a1);
	kiss_array_append(&objects, ARRAY_TYPE, &a1);


	/* Arrange the widgets nicely relative to each other */
	kiss_window_new(&MainWindow, NULL, 1, 0, 0, kiss_screen_width, kiss_screen_height);


	kiss_textbox_new(&Feats, &MainWindow, 1, &a1, kiss_screen_width *.3, 3 * kiss_normal.h - kiss_screen_height / 15, textbox_width, textbox_height);
	kiss_vscrollbar_new(&vscrollbar1, &MainWindow, Feats.rect.x + textbox_width, Feats.rect.y, textbox_height);
	kiss_label_new(&FeatsTextBoxLabel, &MainWindow, "Feats", Feats.rect.x + kiss_edge, Feats.rect.y - kiss_textfont.lineheight);
	kiss_entry_new(&entry, &MainWindow, 1, "Select Item to interact with", kiss_screen_width / 10, Feats.rect.y + textbox_height, 2 * textbox_width + 2 * kiss_up.w + kiss_edge);
	
	kiss_button_new(&ToggleFeatButton, &MainWindow, "Toggle", kiss_screen_width*.5 - (.5*kiss_normal.w), entry.rect.y + entry.rect.h + 10);
	kiss_button_new(&IncreaseFeatButton, &MainWindow, "+", ToggleFeatButton.rect.x+60, ToggleFeatButton.rect.y);
	kiss_button_new(&DecreaseFeatButton, &MainWindow, "-", ToggleFeatButton.rect.x-60, ToggleFeatButton.rect.y);
	kiss_button_new(&FeatDescriptionButton, &MainWindow, "Description", ToggleFeatButton.rect.x, ToggleFeatButton.rect.y + 30);
	kiss_button_new(&button_cancel, &MainWindow, "Cancel", FeatDescriptionButton.rect.x, FeatDescriptionButton.rect.y + 30);


	kiss_window_new(&DescriptionWindow, NULL, 1, 0, 0, 200, 200);
	kiss_button_new(&DescriptionOkButton, &DescriptionWindow, "OK", DescriptionWindow.rect.w / 2 - DescriptionOkButton.rect.x / 2, DescriptionWindow.rect.h*.8);
	kiss_label_new(&Descript1, &DescriptionWindow, "", DescriptionWindow.rect.w*0.2, DescriptionWindow.rect.h*0.2);
	kiss_label_new(&Descript2, &DescriptionWindow, "", Descript1.rect.x,Descript1.rect.y+Descript1.rect.h+5);
	kiss_label_new(&Descript3, &DescriptionWindow, "", Descript2.rect.x, Descript2.rect.y + Descript2.rect.h + 5);


	MainWindow.visible = 1;
	DescriptionWindow.visible = 0;
	//end setup

}

void FeatMenu::text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar)
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
void FeatMenu::textbox1_event(kiss_textbox *textbox, SDL_Event *e, kiss_vscrollbar *vscrollbar2, kiss_entry *entry, int *draw)
{
	int index;

	if (kiss_textbox_event(textbox, e, draw)) {
		index = textbox->firstline + textbox->selectedline;
		if (strcmp((char *)kiss_array_data(textbox->array, index), "")) {
			kiss_string_copy(entry->text, entry->textwidth / kiss_textfont.advance, (char *)kiss_array_data(textbox->array, index), NULL);
			*draw = 1;
			entry->selectedIndex = textbox->selectedline;
			//std::cout << textbox->selectedline << std::endl;
		}
	}
}

void FeatMenu::vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e, kiss_textbox *textbox2, int *draw)
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

void FeatMenu::CloseDescriptionEvent(kiss_button *button, SDL_Event *e, kiss_window *window1, kiss_label *label_sel,
	kiss_entry *entry, kiss_label *label_res, int *draw, EntityClass& Source)
{
	char buf[KISS_MAX_LENGTH];
	if (kiss_button_event(button, e, draw)) {
		kiss_string_copy(buf,
			kiss_maxlength(kiss_textfont, window1->rect.w - 2 * kiss_vslider.w, label_sel->text, entry->text), label_sel->text, entry->text);
		if (entry->selectedIndex > 2)
			//this->SelectedItem = Source.GetBackPack().GetItems()[entry->selectedIndex];

			window1->focus = 0;
		button->prelight = 0;

		*draw = 1;
		quit = 1;
	}
}

void FeatMenu::button_cancel_event(kiss_button *button, SDL_Event *e, int *quit, int *draw)
{
	if (kiss_button_event(button, e, draw))
	{
		*quit = 1;
	}
}

void FeatMenu::FeatMenuRun(EntityClass &Source)
{
	RepopulateList(Source);
	while (!quit) {
		/* Some code may be written here */
		SDL_Delay(10);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = 1;

			kiss_window_event(&MainWindow, &e, &draw);

			textbox1_event(&Feats, &e, &vscrollbar1, &entry, &draw);
			vscrollbar1_event(&vscrollbar1, &e, &Feats, &draw);
			button_cancel_event(&button_cancel, &e, &quit, &draw);
			ToggleFeatEvent(&ToggleFeatButton, &e, &quit, &draw, &entry, Source);
			IncreaseFeatEvent(&IncreaseFeatButton, &e, &quit, &draw, &entry, Source);
			DecreaseFeatEvent(&DecreaseFeatButton, &e, &quit, &draw, &entry, Source);
			ViewFeatDescriptionEvent(&FeatDescriptionButton, &e, &quit, &draw, &entry, Source);
			kiss_entry_event(&entry, &e, &draw);
		}

		vscrollbar1_event(&vscrollbar1, NULL, &Feats, &draw);

		if (!draw) continue;
		SDL_RenderClear(renderer);

		kiss_window_draw(&MainWindow, renderer);
		kiss_label_draw(&FeatsTextBoxLabel, renderer);

		kiss_vscrollbar_draw(&vscrollbar1, renderer);
		kiss_textbox_draw(&Feats, renderer);
		kiss_label_draw(&label_sel, renderer);

		kiss_label_draw(&Descript1, renderer);
		kiss_label_draw(&Descript2, renderer);
		kiss_label_draw(&Descript3, renderer);

		kiss_entry_draw(&entry, renderer);
		kiss_button_draw(&FeatDescriptionButton, renderer);
		kiss_button_draw(&ToggleFeatButton, renderer);
		kiss_button_draw(&IncreaseFeatButton, renderer);
		kiss_button_draw(&DecreaseFeatButton, renderer);
		kiss_button_draw(&button_cancel, renderer);

		kiss_label_draw(&label_res, renderer);

		SDL_RenderPresent(renderer);
		draw = 0;
	}
	kiss_clean(&objects);
	return;
}

void FeatMenu::RepopulateList(EntityClass& Source)
{
	//std::cout << "Displaying Inventory" << std::endl;
	for (int i = 0; i < Feats.array->length;)
	{
		kiss_array_remove(Feats.array, i);
	}
	//std::cout << "Checking for togglefeats" << std::endl;
	auto ToggleFeats = Source.GetToggleableFeats();
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
					temp += (" - Active");
				}
				else
				{
					temp += (" - Off");
				}
				char *ItemNameCstring = new char[temp.length() + 1];
				strcpy(ItemNameCstring, temp.c_str());
				kiss_array_appendstring(Feats.array, 0, ItemNameCstring, NULL);
			}
		}
	else 
	{
		std::string temp = "No Toggleable feats";
		char *ItemNameCstring = new char[temp.length() + 1];
		strcpy(ItemNameCstring, temp.c_str());
		kiss_array_appendstring(Feats.array, 0, ItemNameCstring, NULL);
	}
}

void FeatMenu::ToggleFeatEvent(kiss_button *button, SDL_Event *e, int *quit, int *draw, kiss_entry* entry, EntityClass& Source)
{
	if (kiss_button_event(button, e, draw))
	{
		unsigned index = entry->selectedIndex;
		if (Source.GetToggleableFeats().empty())
		{
			return;
		}
		if (index >= Source.GetToggleableFeats().size())
		{
			return;
		}
		Source.GetToggleableFeats()[index]->SwitchActive();
		RepopulateList(Source);
	}
}

void FeatMenu::ViewFeatDescriptionEvent(kiss_button *button, SDL_Event *e, int *quit, int *draw, kiss_entry* entry, EntityClass& Source)
{
	if (kiss_button_event(button, e, draw))
	{
		unsigned index = entry->selectedIndex;
		if (!Source.GetToggleableFeats().empty() && index < Source.GetToggleableFeats().size())
		{
			
			return;
		}
		//printout to other window? std::string desc = Source.GetToggleableFeats()[index]
		RepopulateList(Source);
	}
}

void FeatMenu::IncreaseFeatEvent(kiss_button *button, SDL_Event *e, int *quit, int *draw,kiss_entry * entry, EntityClass& Source)
{
	if (kiss_button_event(button, e, draw))
	{
		unsigned index = entry->selectedIndex;
		if (!Source.GetToggleableFeats().empty() && index < Source.GetToggleableFeats().size())
		{
			Source.GetToggleableFeats()[index]->IncreaseFeat();
		}
		RepopulateList(Source);
	}
}

void FeatMenu::DecreaseFeatEvent(kiss_button *button, SDL_Event *e, int *quit, int *draw, kiss_entry * entry, EntityClass& Source)
{
	if (kiss_button_event(button, e, draw))
	{
		unsigned index = entry->selectedIndex;
		if (!Source.GetToggleableFeats().empty() && index < Source.GetToggleableFeats().size())
		{
			Source.GetToggleableFeats()[index]->DecreaseFeat();
		}
		RepopulateList(Source);
	}
}
