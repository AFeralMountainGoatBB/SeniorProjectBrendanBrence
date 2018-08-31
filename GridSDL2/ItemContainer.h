#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"
//#include "Tile.h"
#include "Objects.h"


class ItemContainer: public ObjectClass
{
public:
	void AddItem(ObjectClass*);
	void DisplayItems();
	std::vector<ObjectClass*>& GetItems() { return m_ItemsPresent; }
	void RemoveItemAtIndex(int index);
	ObjectClass* GetItemAtIndex(int index);

	bool isItemPresent(std::string m_name);
	void DropAllAtTile(int xpos, int ypos, Tile &passedTile, std::vector<std::vector<Tile>>&TileVector);
private:
	std::vector<ObjectClass *> m_ItemsPresent;
	int m_TotalWeight = 0;

//loading m_objects
public:
	//loads all items present in this object
	bool LoadAll();
};