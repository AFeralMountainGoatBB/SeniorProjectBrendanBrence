#include "ItemContainer.h"

class ObjectClass;
void ItemContainer::AddItem(ObjectClass* item)
{
	this->ItemsPresent.push_back(item);
}

void ItemContainer::DisplayItems()
{
	for (auto iter = ItemsPresent.begin(); iter != ItemsPresent.end(); iter++)
	{
		std::cout << (*iter)->GetName() << std::endl;
	}
}

void ItemContainer::RemoveItemAtIndex(int index)
{
	if (index < ItemsPresent.size())
	{
		ItemsPresent.erase(ItemsPresent.begin() + index);
	}

}

ObjectClass* ItemContainer::GetItemAtIndex(int index)
{
	if (index < ItemsPresent.size())
	{
		return ItemsPresent[index];
	}
	else return NULL;
}


bool ItemContainer::LoadAll()
{
	bool success= true;

	return success;
}

bool ItemContainer::isItemPresent(std::string name)
{
	for (auto it = ItemsPresent.begin(); it != ItemsPresent.end(); it++)
	{
		if ((*it)->GetName() == name)
		{
			return true;
		}
	}

	return false;
}