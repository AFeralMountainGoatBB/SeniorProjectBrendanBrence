#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"
//#include "Tile.h"
#include "Objects.h"

/**********************************************************************************************//**
 * @class	ItemContainer
 *
 * @brief	Container for items, it is a custom struct for objectclass meant to represent things like backpacks
 *
 * @author	Brendan B
 * @date	9/5/2018
 **************************************************************************************************/

class ItemContainer: public ObjectClass
{
public:

	/**********************************************************************************************//**
	 * @fn	void ItemContainer::AddItem(ObjectClass* item);
	 *
	 * @brief	Adds an item to the itemcontainer
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param [in,out]	item	If non-null, the item being added
	 **************************************************************************************************/

	void AddItem(ObjectClass* item);

	/**********************************************************************************************//**
	 * @fn	void ItemContainer::DisplayItems();
	 *
	 * @brief	Displays the items to console
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 **************************************************************************************************/

	void DisplayItems();

	/**********************************************************************************************//**
	 * @fn	std::vector<ObjectClass*>& ItemContainer::GetItems()
	 *
	 * @brief	Gets the items present in the itemcontainer
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @return	Null if it fails, else the items.
	 **************************************************************************************************/

	std::vector<ObjectClass*>& GetItems() { return m_ItemsPresent; }

	/**********************************************************************************************//**
	 * @fn	void ItemContainer::RemoveItemAtIndex(int index);
	 *
	 * @brief	Removes the item at index described by index value
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param	index	Zero-based index of the.
	 **************************************************************************************************/

	void RemoveItemAtIndex(int index);

	/**********************************************************************************************//**
	 * @fn	ObjectClass* ItemContainer::GetItemAtIndex(int index);
	 *
	 * @brief	Gets item at index
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param	index	Zero-based index of the vector
	 *
	 * @return	Null if it fails, else the item at index.
	 **************************************************************************************************/

	ObjectClass* GetItemAtIndex(int index);

	/**********************************************************************************************//**
	 * @fn	bool ItemContainer::isItemPresent(std::string m_name);
	 *
	 * @brief	Query if item present that matches the name passed
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param	m_name	The name.
	 *
	 * @return	True if item present, false if not.
	 **************************************************************************************************/

	bool isItemPresent(std::string m_name);

	/**********************************************************************************************//**
	 * @fn	void ItemContainer::DropAllAtTile(int xpos, int ypos, Tile &passedTile, std::vector<std::vector<Tile>>&TileVector);
	 *
	 * @brief	Drop all items present at tile and then clears the vector
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	xpos	  	The xpos.
	 * @param 		  	ypos	  	The ypos.
	 * @param [in,out]	passedTile	The passed tile to drop the items in
	 * @param [in,out]	TileVector	The tile vector takes place in
	 **************************************************************************************************/

	void DropAllAtTile(int xpos, int ypos, Tile &passedTile, std::vector<std::vector<Tile>>&TileVector);
private:
	/** @brief	The items present */
	std::vector<ObjectClass *> m_ItemsPresent;
	/** @brief	The total weight */
	int m_TotalWeight = 0;

};