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
	std::vector<ObjectClass*>& GetItems() { return ItemsPresent; }
	void RemoveItemAtIndex(int index);
	ObjectClass* GetItemAtIndex(int index);

	bool isItemPresent(std::string name);

private:
	std::vector<ObjectClass *> ItemsPresent;
	int TotalWeight = 0;

//loading objects
public:
	//loads all items present in this object
	bool LoadAll();
};