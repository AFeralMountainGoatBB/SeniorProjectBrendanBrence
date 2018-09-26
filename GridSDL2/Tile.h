/**********************************************************************************************//**
 * @file	Tile.h.
 *
 * @brief	Declares the tile class
 **************************************************************************************************/

#pragma once
#include "GeneralHeaders.h"
#include "EntityClass.h"
#include "Objects.h"

//fwd declaration of LTexture to prevent circular dependencies
class LTexture;

/**********************************************************************************************//**
 * @class	Tile
 *
 * @brief	A tile, stores information relating to itself including its render location, 
 * 			its location on the tilemap, if units are present or not, its tiletype, and what items are present
 *
 * @author	Brendan B
 * @date	9/1/2018
 **************************************************************************************************/
class Tile
{
public:
	//Initializes position and type

	/**********************************************************************************************//**
	 * @fn	Tile::Tile();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/

	Tile();

	/**********************************************************************************************//**
	 * @fn	Tile::Tile(int x, int y, int tileType);
	 *
	 * @brief	Constructor at location with tiletype
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	x			The x coordinate of the tile
	 * @param	y			The y coordinate of the tile
	 * @param	tileType	Type of the tile it is
	 **************************************************************************************************/

	Tile(int x, int y, int tileType);


	/**********************************************************************************************//**
	 * @fn	void Tile::render(SDL_Rect& camera, LTexture &TileTexture, SDL_Rect TileClips[], SDL_Renderer*& Renderer);
	 *
	 * @brief	Renders this tile
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param [in,out]	camera	   	The active
	 * @param [in,out]	TileTexture	The tile texture.
	 * @param 		  	gTileClips 	The tile clip, what part being used
	 * @param [in,out]	Renderer   	[in,out] If non-null, the renderer active
	 **************************************************************************************************/

	void render(SDL_Rect& camera, LTexture &TileTexture, SDL_Rect TileClips[], SDL_Renderer*& Renderer);

	/**********************************************************************************************//**
	 * @fn	int Tile::GetXRenderPos();
	 *
	 * @brief	Get x coordinate render position
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The x coordinate render position.
	 **************************************************************************************************/

	int GetXRenderPos();

	/**********************************************************************************************//**
	 * @fn	int Tile::GetYRenderPos();
	 *
	 * @brief	Get y coordinate render position
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The y coordinate render position.
	 **************************************************************************************************/

	int GetYRenderPos();

	/**********************************************************************************************//**
	 * @fn	int Tile::GetWidth();
	 *
	 * @brief	Gets the width
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The width.
	 **************************************************************************************************/

	int GetWidth();

	/**********************************************************************************************//**
	 * @fn	int Tile::GetHeight();
	 *
	 * @brief	Gets the height
	 *
	 * @author	Brendan B
	 * @date	9/3/2018
	 *
	 * @return	The height.
	 **************************************************************************************************/

	int GetHeight();

	/**********************************************************************************************//**
	 * @fn	ObjectClass* Tile::GetTopObject();
	 *
	 * @brief	Gets top object on the item stack
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	Null if it fails or is empty, else the top object.
	 **************************************************************************************************/

	ObjectClass* GetTopObject(); //will return NULL if no m_objects present

	/**********************************************************************************************//**
	 * @fn	std::vector<ObjectClass*>& Tile::GetItemsPresent();
	 *
	 * @brief	Gets items present
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	Null if it fails or empty, else the items present.
	 **************************************************************************************************/

	std::vector<ObjectClass*>& GetItemsPresent(); //returns the entire vector of m_objects present

	/**********************************************************************************************//**
	 * @fn	void Tile::AddItem(ObjectClass* Item);
	 *
	 * @brief	Adds an item
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param [in,out]	Item	If non-null, the item being added
	 **************************************************************************************************/

	void AddItem(ObjectClass* Item);

	/**********************************************************************************************//**
	 * @fn	Tile Tile::RemoveObject(ObjectClass* object);
	 *
	 * @brief	Removes the object described by object
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param [in,out]	object	If non-null, the item being removed.
	 *
	 * @return	the new tile info.
	 **************************************************************************************************/

	Tile RemoveObject(ObjectClass* object);

	/**********************************************************************************************//**
	 * @fn	bool Tile::EntityPresent();
	 *
	 * @brief	Determines if an entity is present
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	True if entity is present, false if it none exist.
	 **************************************************************************************************/

	bool EntityPresent();

	/**********************************************************************************************//**
	 * @fn	void Tile::ClearOccupant();
	 *
	 * @brief	Clears the occupant status
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/

	void ClearOccupant();

	/**********************************************************************************************//**
	 * @fn	void Tile::SetOccupant(EntityClass &Entity);
	 *
	 * @brief	Sets an occupant in the tile
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param [in,out]	Entity	The entity now present.
	 **************************************************************************************************/

	void SetOccupant(EntityClass &Entity);

	/**********************************************************************************************//**
	 * @fn	EntityClass* Tile::GetOccupant();
	 *
	 * @brief	Gets the occupant
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	Null if it fails or empty, else the occupant.
	 **************************************************************************************************/

	EntityClass* GetOccupant();

	/**********************************************************************************************//**
	 * @fn	int Tile::getType();
	 *
	 * @brief	Gets the type of tile
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The type of tile.
	 **************************************************************************************************/

	int getType();

	/**********************************************************************************************//**
	 * @fn	bool Tile::getPassable();
	 *
	 * @brief	Gets if tile passable
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	True if passable, false if not passable.
	 **************************************************************************************************/

	bool getPassable();

	/**********************************************************************************************//**
	 * @fn	bool Tile::getPassableTileType();
	 *
	 * @brief	Gets if the tile type of this tile is passable
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	True if it is passable, false if it is blocked
	 **************************************************************************************************/

	bool getPassableTileType();


	/**********************************************************************************************//**
	 * @fn	SDL_Rect Tile::getBox();
	 *
	 * @brief	Gets the m_box
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The box
	 **************************************************************************************************/

	SDL_Rect getBox();

	/**********************************************************************************************//**
	 * @fn	void Tile::operator=(const Tile* other)
	 *
	 * @brief	Assignment operator
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	other	The other tile.
	 **************************************************************************************************/

	void operator=(const Tile* other)
	{
		m_Box.x = other->m_Box.x;
		m_Box.y = other->m_Box.y;
		m_Box.h = other->m_Box.h;
		m_Box.w = other->m_Box.w;

		m_type = other->m_type;
		m_Occupied = other->m_Occupied;
		m_posX = other->m_posX;
		m_posY = other->m_posY;

	}

	/**********************************************************************************************//**
	 * @fn	int Tile::GetXPosition()
	 *
	 * @brief	Get x coordinate position
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The x coordinate position.
	 **************************************************************************************************/

	int GetXPosition() { return m_posX; }

	/**********************************************************************************************//**
	 * @fn	int Tile::GetYPosition()
	 *
	 * @brief	Get y coordinate position
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The y coordinate position.
	 **************************************************************************************************/

	int GetYPosition() { return m_posY; }
	
private:
	//The attributes of the tile
	/** @brief	The box */
	SDL_Rect m_Box;

	//The tile type
	/** @brief	The type */
	int m_type;

	//bool to see if space is occupied, for collision purposes
	/** @brief	True if occupied */
	bool m_Occupied;
	
	//pointer to the entity that is standing in this space (tiles can only have, at most, one entity in their space)
	/** @brief	The occupant */
	EntityClass* m_occupant = nullptr;

	/** @brief	The position x coordinate */
	int m_posX;
	/** @brief	The position y coordinate */
	int m_posY;

	//some way to list m_objects in the space
	/** @brief	The items present */
	std::vector<ObjectClass*> m_ItemsPresent; 

};
