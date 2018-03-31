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
	
	int GetTotalWeight();
	void AddWeight();
	void SubtractWeight();

private:
	std::vector<ObjectClass *> ItemsPresent;
	int TotalWeight = 0;
};