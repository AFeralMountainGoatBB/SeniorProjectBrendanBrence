#include "InventoryMenu.h"


InventoryMenu::InventoryMenu()
{
	quit = 0;
	draw = 1;
	textbox_width = 250;
	textbox_height = 250;
	renderer = kiss_init("InventoryMenu", &objects, 640, 480);
	if (!renderer)
	{
		std::cout << "Renderer wrong" << std::endl;
		return;
	}
	kiss_array_new(&a1);
	kiss_array_append(&objects, ARRAY_TYPE, &a1);


	/* Arrange the widgets nicely relative to each other */
	kiss_window_new(&MainWindow, NULL, 1, 0, 0, kiss_screen_width, kiss_screen_height);

	kiss_textbox_new(&Items, &MainWindow, 1, &a1, kiss_screen_width *.3, 3 * kiss_normal.h - kiss_screen_height / 15, textbox_width, textbox_height);
	kiss_vscrollbar_new(&vscrollbar1, &MainWindow, Items.rect.x + textbox_width, Items.rect.y, textbox_height);
	kiss_label_new(&ItemsTextBoxLabel, &MainWindow, "Items", Items.rect.x + kiss_edge, Items.rect.y - kiss_textfont.lineheight);
	kiss_entry_new(&entry, &MainWindow, 1, "Select Item to interact with", kiss_screen_width / 10, Items.rect.y + textbox_height, 2 * textbox_width + 2 * kiss_up.w + kiss_edge);
	
	kiss_button_new(&SwapButton, &MainWindow, "Swap", kiss_screen_width*.5-(.5*kiss_normal.w) , entry.rect.y + entry.rect.h + 10);
	kiss_button_new(&TwoHandButton, &MainWindow, "TwoHand", SwapButton.rect.x, SwapButton.rect.y + 30);
	kiss_button_new(&DropButton, &MainWindow, "DropItem", SwapButton.rect.x, SwapButton.rect.y+60);
	kiss_button_new(&EquipButton, &MainWindow, "(Un)Equip", SwapButton.rect.x, SwapButton.rect.y + 90);
	kiss_button_new(&button_cancel, &MainWindow, "Cancel", SwapButton.rect.x, SwapButton.rect.y+120);
	
	MainWindow.visible = 1;
	//end setup

}

void InventoryMenu::text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar)
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
void InventoryMenu::textbox1_event(kiss_textbox *textbox, SDL_Event *e, kiss_vscrollbar *vscrollbar2, kiss_entry *entry, int *draw)
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

void InventoryMenu::vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e, kiss_textbox *textbox2, int *draw)
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

void InventoryMenu::button_ok1_event(kiss_button *button, SDL_Event *e, kiss_window *window1, kiss_label *label_sel,
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

void InventoryMenu::button_cancel_event(kiss_button *button, SDL_Event *e, int *quit, int *draw)
{
	if (kiss_button_event(button, e, draw))
	{
		*quit = 1;
	}
}

ObjectClass* InventoryMenu::InventoryMenuRun(EntityClass &Source, std::vector<std::vector<Tile>>&TileMap)
{
	RepopulateList(Source);
	while (!quit) {
		/* Some code may be written here */
		SDL_Delay(10);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = 1;

			kiss_window_event(&MainWindow, &e, &draw);

			textbox1_event(&Items, &e, &vscrollbar1, &entry, &draw);
			vscrollbar1_event(&vscrollbar1, &e, &Items, &draw);
			button_cancel_event(&button_cancel, &e, &quit, &draw);
			SwapButtonEvent(&SwapButton, &e, &quit, &draw, Source);
			DropButtonEvent(&DropButton, &e, &quit, &draw, &entry, Source, TileMap);
			TwoHandButtonEvent(&TwoHandButton, &e, &quit, &draw, Source);
			EquipButtonEvent(&EquipButton, &e, &quit, &draw, &entry, Source);
			kiss_entry_event(&entry, &e, &draw);
		}

		vscrollbar1_event(&vscrollbar1, NULL, &Items, &draw);

		if (!draw) continue;
		SDL_RenderClear(renderer);

		kiss_window_draw(&MainWindow, renderer);
		kiss_label_draw(&ItemsTextBoxLabel, renderer);

		kiss_vscrollbar_draw(&vscrollbar1, renderer);
		kiss_textbox_draw(&Items, renderer);
		kiss_label_draw(&label_sel, renderer);
		kiss_entry_draw(&entry, renderer);
		kiss_button_draw(&EquipButton, renderer);
		kiss_button_draw(&TwoHandButton, renderer);
		kiss_button_draw(&SwapButton, renderer);
		kiss_button_draw(&DropButton, renderer);
		kiss_button_draw(&button_cancel, renderer);

		kiss_label_draw(&label_res, renderer);
		
		SDL_RenderPresent(renderer);
		draw = 0;
	}
	kiss_clean(&objects);
	return SelectedItem;
}

void InventoryMenu::RepopulateList(EntityClass& Source)
{
	//std::cout << "Displaying Inventory" << std::endl;
	for (int i = 0; i < Items.array->length;)
	{
		kiss_array_remove(Items.array, i);
	}
	
	//body slots (body, mainhand, offhand), then backpack, if empty print out "EMPTY"
	if (Source.GetEquipmentInSlot(BODY) != NULL)
	{
		//std::cout << Source.GetEquipmentInSlot(BODY)->GetName() << std::endl;
		std::string temp = "ARMOR - " + Source.GetEquipmentInSlot(BODY)->GetName();
		char *ItemNameCstring = new char[temp.length() + 1];
		strcpy(ItemNameCstring, temp.c_str());
		kiss_array_appendstring(Items.array, 0, ItemNameCstring, NULL);
	}
	else
	{
		std::string temp = "ARMOR - UNARMORED";
		char *ItemNameCstring = new char[temp.length() + 1];
		strcpy(ItemNameCstring, temp.c_str());
		kiss_array_appendstring(Items.array, 0, ItemNameCstring, NULL);
	}

	if (Source.IsTwoHanding() && Source.GetEquipmentInSlot(MAINHAND)!=NULL)
	{
		std::string temp = "OFFHAND - TwoHanding";
		char *ItemNameCstring = new char[temp.length() + 1];
		strcpy(ItemNameCstring, temp.c_str());
		kiss_array_appendstring(Items.array, 0, ItemNameCstring, NULL);

		temp = "MAINHAND - " + Source.GetEquipmentInSlot(MAINHAND)->GetName();
		char *ItemNameCstring2 = new char[temp.length() + 1];
		strcpy(ItemNameCstring2, temp.c_str());
		kiss_array_appendstring(Items.array, 0, ItemNameCstring2, NULL);
	}
	else
	{
		std::string temp;
		if (Source.GetEquipmentInSlot(OFFHAND) != NULL)
		{
			temp = "OFFHAND - " + Source.GetEquipmentInSlot(OFFHAND)->GetName();
		}
		else
		{
			temp = "OFFHAND - Empty";
		}
			char *ItemNameCstring = new char[temp.length() + 1];
			strcpy(ItemNameCstring, temp.c_str());
			kiss_array_appendstring(Items.array, 0, ItemNameCstring, NULL);

		if(Source.GetEquipmentInSlot(MAINHAND)!=NULL)
		{
			temp = "MAINHAND - " + Source.GetEquipmentInSlot(MAINHAND)->GetName();
		}
		else
		{
			temp = "MAINHAND - Empty";
		}
		char *ItemNameCstring3 = new char[temp.length() + 1];
		strcpy(ItemNameCstring3, temp.c_str());
		kiss_array_appendstring(Items.array, 0, ItemNameCstring3, NULL);
	}

	for (auto i = Source.GetBackPack().GetItems().begin(); i < Source.GetBackPack().GetItems().end(); i++)
	{
		std::string temp = "BACKPACK - " + (*i)->GetName();
		char *ItemNameCstring = new char[temp.length() + 1];
		strcpy(ItemNameCstring, temp.c_str());
		kiss_array_appendstring(Items.array, 0, ItemNameCstring, NULL);
	}

}

void InventoryMenu::SwapButtonEvent(kiss_button *button, SDL_Event *e, int *quit, int *draw, EntityClass& Source)
{
	if (kiss_button_event(button, e, draw))
	{
		Source.SwapWeaponHands();
		RepopulateList(Source);
	}
}

void InventoryMenu::DropButtonEvent(kiss_button *button, SDL_Event *e, int *quit, int *draw, kiss_entry* entry, EntityClass& Source, std::vector<std::vector<Tile>>&TileMap)
{
	if (kiss_button_event(button, e, draw))
	{
		int index = entry->selectedIndex;
		if (index == -1)
		{
			return;
		}
		if (index == 0) // armor
		{
			Source.DropFromEquipment(BODY, TileMap);
		}
		else if (index == 1) //offhand object
		{
			//check if two handing
			if (Source.GetEquipmentInSlot(MAINHAND) == Source.GetEquipmentInSlot(OFFHAND))
			{
				Source.TwoHandWeapon();
				Source.DropFromEquipment(MAINHAND, TileMap);
			}
			else
			{
				Source.DropFromEquipment(OFFHAND, TileMap);
			}
		}
		else if (index == 2) //mainhand object
		{
			//check if two handing
			if (Source.GetEquipmentInSlot(MAINHAND) == Source.GetEquipmentInSlot(OFFHAND))
			{
				Source.TwoHandWeapon();
				Source.DropFromEquipment(MAINHAND, TileMap);
			}
			else
			{
				Source.DropFromEquipment(MAINHAND, TileMap);
			}

		}
		else if (index > 2)//backpack object
		{
			auto TempPtr = Source.GetBackPack().GetItemAtIndex(index - 3);
			std::cout << "Dropping " << TempPtr->GetName() << std::endl;
			std::cout << BodyLocationTextMap[TempPtr->GetBodySlot()] << std::endl;
			
			Source.DropFromBackPack(index - 3, TileMap);
		} //end if index>2

		std::cout << "Drop button pressed" << std::endl;
		entry->selectedIndex = -1;
		entry->text[0] = '\0';
		RepopulateList(Source);
	}
}

void InventoryMenu::TwoHandButtonEvent(kiss_button *button, SDL_Event *e, int *quit, int *draw, EntityClass& Source)
{
	if (kiss_button_event(button, e, draw))
	{
		Source.TwoHandWeapon();
		std::cout << "TwoHand" << std::endl;
		RepopulateList(Source);
	}
}

void InventoryMenu::EquipButtonEvent(kiss_button *button, SDL_Event *e, int *quit, int *draw, kiss_entry* entry,  EntityClass& Source)
{
	if (kiss_button_event(button, e, draw))
	{
		//get where object is, backpack or equipped
		//if equipped, it goes into backpack
		//if in backpack we attempt to equip it
		int index = entry->selectedIndex;
		if (index == -1)
		{
			return;
		}
		if (index == 0) // armor
		{
			Source.UnEquip(BODY);
		}
		else if (index == 1) //offhand object
		{
			//check if two handing
			if (Source.GetEquipmentInSlot(MAINHAND) == Source.GetEquipmentInSlot(OFFHAND))
			{
				Source.TwoHandWeapon();
				Source.UnEquip(MAINHAND);
			}
			else
			{
				Source.UnEquip(OFFHAND);
			}
		}
		else if (index == 2) //mainhand object
		{
			//check if two handing
			if (Source.GetEquipmentInSlot(MAINHAND) == Source.GetEquipmentInSlot(OFFHAND))
			{
				Source.TwoHandWeapon();
				Source.UnEquip(MAINHAND);
			}
			else
			{
				Source.UnEquip(MAINHAND);
			}
			
		}
		else if (index > 2)//backpack object
		{
			auto TempPtr = Source.GetBackPack().GetItemAtIndex(index - 3);
			//std::cout << "Equipping " << TempPtr->GetName() << std::endl;
			//std::cout << BodyLocationTextMap[ TempPtr->GetBodySlot() ]<< std::endl;
			if (TempPtr->GetBodySlot() == BODY)
			{
				if (Source.GetEquipmentInSlot(BODY) == NULL)
				{
					if (Source.EquipArmor(TempPtr))
					{
						Source.GetBackPack().RemoveItemAtIndex(index - 3);
					}
				}
				else
				{
					std::cout << "Already wearing armor, remove to equip other armor" << std::endl;
				}
			}
			else if (TempPtr->GetBodySlot() == MAINHAND || TempPtr->GetBodySlot() == OFFHAND)
			{
				if (Source.EquipAsWeapon(TempPtr))
				{
					std::cout << TempPtr->GetName() << " Equipped from backpack" << std::endl;
					Source.GetBackPack().RemoveItemAtIndex(index - 3);
				}
				else
				{
					std::cout << "Item cannot be equipped now" << std::endl;
				}
			}
		} //end if index>2

		std::cout << "Equip/Unequip button pressed" << std::endl;
		entry->selectedIndex = -1;
		entry->text[0]='\0';
		RepopulateList(Source);
	}
}
