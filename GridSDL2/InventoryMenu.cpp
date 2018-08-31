#include "InventoryMenu.h"


InventoryMenu::InventoryMenu()
{
	m_quit = 0;
	m_draw = 1;
	m_textbox_width = 250;
	m_textbox_height = 250;
	m_renderer = kiss_init("InventoryMenu", &m_objects, 640, 480);
	if (!m_renderer)
	{
		std::cout << "Renderer wrong" << std::endl;
		return;
	}
	kiss_array_new(&m_array1);
	kiss_array_append(&m_objects, ARRAY_TYPE, &m_array1);


	/* Arrange the widgets nicely relative to each other */
	kiss_window_new(&m_MainWindow, NULL, 1, 0, 0, kiss_screen_width, kiss_screen_height);

	kiss_textbox_new(&m_Items, &m_MainWindow, 1, &m_array1, kiss_screen_width *.3, 3 * kiss_normal.h - kiss_screen_height / 15, m_textbox_width, m_textbox_height);
	kiss_vscrollbar_new(&m_vscrollbar1, &m_MainWindow, m_Items.rect.x + m_textbox_width, m_Items.rect.y, m_textbox_height);
	kiss_label_new(&m_ItemsTextBoxLabel, &m_MainWindow, "m_Items", m_Items.rect.x + kiss_edge, m_Items.rect.y - kiss_textfont.lineheight);
	kiss_entry_new(&m_entry, &m_MainWindow, 1, "Select Item to interact with", kiss_screen_width / 10, m_Items.rect.y + m_textbox_height, 2 * m_textbox_width + 2 * kiss_up.w + kiss_edge);
	
	kiss_button_new(&m_SwapButton, &m_MainWindow, "Swap", kiss_screen_width*.5-(.5*kiss_normal.w) , m_entry.rect.y + m_entry.rect.h + 10);
	kiss_button_new(&m_TwoHandButton, &m_MainWindow, "TwoHand", m_SwapButton.rect.x, m_SwapButton.rect.y + 30);
	kiss_button_new(&m_DropButton, &m_MainWindow, "DropItem", m_SwapButton.rect.x, m_SwapButton.rect.y+60);
	kiss_button_new(&m_EquipButton, &m_MainWindow, "(Un)Equip", m_SwapButton.rect.x, m_SwapButton.rect.y + 90);
	kiss_button_new(&m_button_cancel, &m_MainWindow, "Cancel", m_SwapButton.rect.x, m_SwapButton.rect.y+120);
	
	m_MainWindow.visible = 1;
	//end setup

}

void InventoryMenu::text_reset(kiss_textbox *a_textbox, kiss_vscrollbar *a_vscrollbar)
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
void InventoryMenu::textbox1_event(kiss_textbox *a_textbox, SDL_Event *a_event, kiss_vscrollbar *a_vscrollbar2, kiss_entry *a_entry, int *a_draw)
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

void InventoryMenu::vscrollbar1_event(kiss_vscrollbar *a_vscrollbar, SDL_Event *a_event, kiss_textbox *a_textbox2, int *a_draw)
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

void InventoryMenu::button_ok1_event(kiss_button *a_button, SDL_Event *a_event, kiss_window *a_window1, kiss_label *a_label_sel,
	kiss_entry *a_entry, kiss_label *a_label_res, int *a_draw, EntityClass&a_Source)
{
	char buf[KISS_MAX_LENGTH];
	if (kiss_button_event(a_button, a_event, a_draw)) {
		kiss_string_copy(buf,
			kiss_maxlength(kiss_textfont, a_window1->rect.w - 2 * kiss_vslider.w, a_label_sel->text, a_entry->text), a_label_sel->text, a_entry->text);
		if (a_entry->selectedIndex > 2)
		//this->m_SelectedItem = a_draw.GetBackPack().GetItems()[a_entry->selectedIndex];

		a_window1->focus = 0;
		a_button->prelight = 0;

		*a_draw = 1;
		m_quit = 1;
	}
}

void InventoryMenu::button_cancel_event(kiss_button *a_button, SDL_Event *a_event, int *a_quit, int *a_draw)
{
	if (kiss_button_event(a_button, a_event, a_draw))
	{
		*a_quit = 1;
	}
}

ObjectClass* InventoryMenu::InventoryMenuRun(EntityClass &a_Source, std::vector<std::vector<Tile>>&a_TileMap)
{
	RepopulateList(a_Source);
	while (!m_quit) {
		/* Some code may be written here */
		SDL_Delay(10);
		while (SDL_PollEvent(&m_event)) {
			if (m_event.type == SDL_QUIT)
				m_quit = 1;

			kiss_window_event(&m_MainWindow, &m_event, &m_draw);

			textbox1_event(&m_Items, &m_event, &m_vscrollbar1, &m_entry, &m_draw);
			vscrollbar1_event(&m_vscrollbar1, &m_event, &m_Items, &m_draw);
			button_cancel_event(&m_button_cancel, &m_event, &m_quit, &m_draw);
			SwapButtonEvent(&m_SwapButton, &m_event, &m_quit, &m_draw, a_Source);
			DropButtonEvent(&m_DropButton, &m_event, &m_quit, &m_draw, &m_entry, a_Source, a_TileMap);
			TwoHandButtonEvent(&m_TwoHandButton, &m_event, &m_quit, &m_draw, a_Source);
			EquipButtonEvent(&m_EquipButton, &m_event, &m_quit, &m_draw, &m_entry, a_Source);
			kiss_entry_event(&m_entry, &m_event, &m_draw);
		}

		vscrollbar1_event(&m_vscrollbar1, NULL, &m_Items, &m_draw);

		if (!m_draw) continue;
		SDL_RenderClear(m_renderer);

		kiss_window_draw(&m_MainWindow, m_renderer);
		kiss_label_draw(&m_ItemsTextBoxLabel, m_renderer);

		kiss_vscrollbar_draw(&m_vscrollbar1, m_renderer);
		kiss_textbox_draw(&m_Items, m_renderer);
		kiss_label_draw(&m_label_sel, m_renderer);
		kiss_entry_draw(&m_entry, m_renderer);
		kiss_button_draw(&m_EquipButton, m_renderer);
		kiss_button_draw(&m_TwoHandButton, m_renderer);
		kiss_button_draw(&m_SwapButton, m_renderer);
		kiss_button_draw(&m_DropButton, m_renderer);
		kiss_button_draw(&m_button_cancel, m_renderer);

		kiss_label_draw(&m_label_res, m_renderer);
		
		SDL_RenderPresent(m_renderer);
		m_draw = 0;
	}
	kiss_clean(&m_objects);
	return m_SelectedItem;
}

void InventoryMenu::RepopulateList(EntityClass& a_Source)
{
	//std::cout << "Displaying Inventory" << std::endl;
	for (int i = 0; i < m_Items.array->length;)
	{
		kiss_array_remove(m_Items.array, i);
	}
	
	//body slots (body, mainhand, offhand), then backpack, if empty print out "EMPTY"
	if (a_Source.GetEquipmentInSlot(BODY) != NULL)
	{
		//std::cout << a_draw.GetEquipmentInSlot(BODY)->GetName() << std::endl;
		std::string temp = "ARMOR - " + a_Source.GetEquipmentInSlot(BODY)->GetName();
		char *ItemNameCstring = new char[temp.length() + 1];
		strcpy(ItemNameCstring, temp.c_str());
		kiss_array_appendstring(m_Items.array, 0, ItemNameCstring, NULL);
	}
	else
	{
		std::string temp = "ARMOR - UNARMORED";
		char *ItemNameCstring = new char[temp.length() + 1];
		strcpy(ItemNameCstring, temp.c_str());
		kiss_array_appendstring(m_Items.array, 0, ItemNameCstring, NULL);
	}

	if (a_Source.IsTwoHanding() && a_Source.GetEquipmentInSlot(MAINHAND)!=NULL)
	{
		std::string temp = "OFFHAND - TwoHanding";
		char *ItemNameCstring = new char[temp.length() + 1];
		strcpy(ItemNameCstring, temp.c_str());
		kiss_array_appendstring(m_Items.array, 0, ItemNameCstring, NULL);

		temp = "MAINHAND - " + a_Source.GetEquipmentInSlot(MAINHAND)->GetName();
		char *ItemNameCstring2 = new char[temp.length() + 1];
		strcpy(ItemNameCstring2, temp.c_str());
		kiss_array_appendstring(m_Items.array, 0, ItemNameCstring2, NULL);
	}
	else
	{
		std::string temp;
		if (a_Source.GetEquipmentInSlot(OFFHAND) != NULL)
		{
			temp = "OFFHAND - " + a_Source.GetEquipmentInSlot(OFFHAND)->GetName();
		}
		else
		{
			temp = "OFFHAND - Empty";
		}
			char *ItemNameCstring = new char[temp.length() + 1];
			strcpy(ItemNameCstring, temp.c_str());
			kiss_array_appendstring(m_Items.array, 0, ItemNameCstring, NULL);

		if(a_Source.GetEquipmentInSlot(MAINHAND)!=NULL)
		{
			temp = "MAINHAND - " + a_Source.GetEquipmentInSlot(MAINHAND)->GetName();
		}
		else
		{
			temp = "MAINHAND - Empty";
		}
		char *ItemNameCstring3 = new char[temp.length() + 1];
		strcpy(ItemNameCstring3, temp.c_str());
		kiss_array_appendstring(m_Items.array, 0, ItemNameCstring3, NULL);
	}

	for (auto i = a_Source.GetBackPack().GetItems().begin(); i < a_Source.GetBackPack().GetItems().end(); i++)
	{
		std::string temp = "BACKPACK - " + (*i)->GetName();
		char *ItemNameCstring = new char[temp.length() + 1];
		strcpy(ItemNameCstring, temp.c_str());
		kiss_array_appendstring(m_Items.array, 0, ItemNameCstring, NULL);
	}

}

void InventoryMenu::SwapButtonEvent(kiss_button *a_button, SDL_Event *a_event, int *a_quit, int *a_draw, EntityClass& a_Source)
{
	if (kiss_button_event(a_button, a_event, a_draw))
	{
		a_Source.SwapWeaponHands();
		RepopulateList(a_Source);
	}
}

void InventoryMenu::DropButtonEvent(kiss_button *a_button, SDL_Event *a_event, int *a_quit, int *a_draw, kiss_entry* a_entry, EntityClass& a_Source, std::vector<std::vector<Tile>>&a_TileMap)
{
	if (kiss_button_event(a_button, a_event, a_draw))
	{
		int index = a_entry->selectedIndex;
		if (index == -1)
		{
			return;
		}
		if (index == 0) // armor
		{
			a_Source.DropFromEquipment(BODY, a_TileMap);
		}
		else if (index == 1) //offhand object
		{
			//check if two handing
			if (a_Source.GetEquipmentInSlot(MAINHAND) == a_Source.GetEquipmentInSlot(OFFHAND))
			{
				a_Source.TwoHandWeapon();
				a_Source.DropFromEquipment(MAINHAND, a_TileMap);
			}
			else
			{
				a_Source.DropFromEquipment(OFFHAND, a_TileMap);
			}
		}
		else if (index == 2) //mainhand object
		{
			//check if two handing
			if (a_Source.GetEquipmentInSlot(MAINHAND) == a_Source.GetEquipmentInSlot(OFFHAND))
			{
				a_Source.TwoHandWeapon();
				a_Source.DropFromEquipment(MAINHAND, a_TileMap);
			}
			else
			{
				a_Source.DropFromEquipment(MAINHAND, a_TileMap);
			}

		}
		else if (index > 2)//backpack object
		{
			auto TempPtr = a_Source.GetBackPack().GetItemAtIndex(index - 3);
			std::cout << "Dropping " << TempPtr->GetName() << std::endl;
			std::cout << BodyLocationTextMap[TempPtr->GetBodySlot()] << std::endl;
			
			a_Source.DropFromBackPack(index - 3, a_TileMap);
		} //end if index>2

		std::cout << "Drop a_button pressed" << std::endl;
		a_entry->selectedIndex = -1;
		a_entry->text[0] = '\0';
		RepopulateList(a_Source);
	}
}

void InventoryMenu::TwoHandButtonEvent(kiss_button *a_button, SDL_Event *a_event, int *a_quit, int *a_draw, EntityClass& a_Source)
{
	if (kiss_button_event(a_button, a_event, a_draw))
	{
		a_Source.TwoHandWeapon();
		std::cout << "TwoHand" << std::endl;
		RepopulateList(a_Source);
	}
}

void InventoryMenu::EquipButtonEvent(kiss_button *a_button, SDL_Event *a_event, int *a_quit, int *a_draw, kiss_entry* a_entry,  EntityClass& a_Source)
{
	if (kiss_button_event(a_button, a_event, a_draw))
	{
		//get where object is, backpack or equipped
		//if equipped, it goes into backpack
		//if in backpack we attempt to equip it
		int index = a_entry->selectedIndex;
		if (index == -1)
		{
			return;
		}
		if (index == 0) // armor
		{
			a_Source.UnEquip(BODY);
		}
		else if (index == 1) //offhand object
		{
			//check if two handing
			if (a_Source.GetEquipmentInSlot(MAINHAND) == a_Source.GetEquipmentInSlot(OFFHAND))
			{
				a_Source.TwoHandWeapon();
				a_Source.UnEquip(MAINHAND);
			}
			else
			{
				a_Source.UnEquip(OFFHAND);
			}
		}
		else if (index == 2) //mainhand object
		{
			//check if two handing
			if (a_Source.GetEquipmentInSlot(MAINHAND) == a_Source.GetEquipmentInSlot(OFFHAND))
			{
				a_Source.TwoHandWeapon();
				a_Source.UnEquip(MAINHAND);
			}
			else
			{
				a_Source.UnEquip(MAINHAND);
			}
			
		}
		else if (index > 2)//backpack object
		{
			auto TempPtr = a_Source.GetBackPack().GetItemAtIndex(index - 3);
			std::cout << "Equipping " << TempPtr->GetName() << std::endl;
			//std::cout << BodyLocationTextMap[ TempPtr->GetBodySlot() ]<< std::endl;
			if (TempPtr->GetBodySlot() == BODY)
			{
				if (a_Source.GetEquipmentInSlot(BODY) == NULL)
				{
					if (a_Source.EquipArmor(TempPtr))
					{
						a_Source.GetBackPack().RemoveItemAtIndex(index - 3);
					}
				}
				else
				{
					std::cout << "Already wearing armor, remove to equip other armor" << std::endl;
				}
			}
			else if (TempPtr->GetBodySlot() == MAINHAND || TempPtr->GetBodySlot() == OFFHAND)
			{
				if (a_Source.EquipAsWeapon(TempPtr)==true)
				{
					std::cout << TempPtr->GetName() << " Equipped from backpack" << std::endl;
					a_Source.GetBackPack().RemoveItemAtIndex(index - 3);
				}
				else
				{
					std::cout << "Item cannot be equipped now" << std::endl;
				}
			}
			//if ()
		} //end if index>2

		std::cout << "Equip/Unequip a_button pressed" << std::endl;
		a_entry->selectedIndex = -1;
		a_entry->text[0]='\0';
		RepopulateList(a_Source);
	}
}
