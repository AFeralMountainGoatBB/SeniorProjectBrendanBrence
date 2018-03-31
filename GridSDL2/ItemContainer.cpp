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