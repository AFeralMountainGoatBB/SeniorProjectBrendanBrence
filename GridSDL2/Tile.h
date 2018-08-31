#pragma once
#include "GeneralHeaders.h"
#include "EntityClass.h"
#include "Objects.h"

class LTexture;

class Tile
{
public:
	//Initializes position and type
	Tile();
	Tile(int x, int y, int tileType);

	//Shows the tile
	void render(SDL_Rect& camera, LTexture &TileTexture, SDL_Rect gTileClips[], SDL_Renderer*& Renderer);
	int GetXRenderPos();
	int GetYRenderPos();
	int GetWidth();
	ObjectClass* GetTopObject(); //will return NULL if no m_objects present
	std::vector<ObjectClass*>& GetItemsPresent(); //returns the entire vector of m_objects present
	void AddItem(ObjectClass* Item);
	Tile RemoveObject(ObjectClass*);
	bool EntityPresent();
	void RemoveObjectString(std::string m_ObjectName);

	void ClearOccupant();
	void SetOccupant(EntityClass &Entity);
	EntityClass* GetOccupant();

	//Get the tile type
	int getType();

	bool getPassable();
	bool getPassableTileType();

	//Get the collision box
	SDL_Rect getBox();

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

	int GetXPosition() { return m_posX; }
	int GetYPosition() { return m_posY; }
	
private:
	//The attributes of the tile
	SDL_Rect m_Box;

	//The tile type
	int m_type;

	//bool to see if space is occupied, for collision purposes
	bool m_Occupied;
	
	//pointer to the entity that is standing in this space (tiles can only have, at most, one entity in their space)
	EntityClass* m_occupant = nullptr;

	int m_posX;
	int m_posY;

	//some way to list m_objects in the space
	std::vector<ObjectClass*> m_ItemsPresent; 


};
