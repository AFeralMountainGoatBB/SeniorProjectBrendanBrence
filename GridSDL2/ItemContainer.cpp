#include "ItemContainer.h"
#include "Tile.h"

class ObjectClass;
void ItemContainer::AddItem(ObjectClass* a_item)
{
	this->m_ItemsPresent.push_back(a_item);
}

void ItemContainer::DisplayItems()
{
	for (auto iter = m_ItemsPresent.begin(); iter != m_ItemsPresent.end(); iter++)
	{
		std::cout << (*iter)->GetName() << std::endl;
	}
}

void ItemContainer::RemoveItemAtIndex(int a_index)
{
	if (a_index < m_ItemsPresent.size())
	{
		m_ItemsPresent.erase(m_ItemsPresent.begin() + a_index);
	}
}

void ItemContainer::DropAllAtTile(int a_xPos, int a_yPos, Tile & a_tilePassed, std::vector<std::vector<Tile>>&a_TileVector)
{
	for (auto it = m_ItemsPresent.begin(); it != m_ItemsPresent.end(); it++)
	{
		if ((*it) != nullptr)
		{
			(*it)->SetLocation(a_xPos, a_yPos, a_TileVector);
		}
	}
	m_ItemsPresent.clear();
}

ObjectClass* ItemContainer::GetItemAtIndex(int a_index)
{
	if (a_index < m_ItemsPresent.size())
	{
		return m_ItemsPresent[a_index];
	}
	else return NULL;
}


bool ItemContainer::LoadAll()
{
	bool success= true;

	return success;
}

bool ItemContainer::isItemPresent(std::string a_name)
{
	for (auto it = m_ItemsPresent.begin(); it != m_ItemsPresent.end(); it++)
	{
		if ((*it)->GetName() == a_name)
		{
			return true;
		}
	}

	return false;
}