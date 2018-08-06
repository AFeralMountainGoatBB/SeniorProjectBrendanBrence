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
	ObjectClass* GetTopObject(); //will return NULL if no objects present
	std::vector<ObjectClass*>& GetItemsPresent(); //returns the entire vector of objects present
	void AddItem(ObjectClass* Item);
	Tile RemoveObject(ObjectClass*);
	bool EntityPresent();
	void RemoveObjectString(std::string ObjectName);

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
		mBox.x = other->mBox.x;
		mBox.y = other->mBox.y;
		mBox.h = other->mBox.h;
		mBox.w = other->mBox.w;

		mType = other->mType;
		mOccupied = other->mOccupied;
		PosX = other->PosX;
		PosY = other->PosY;

	}

	int GetXPosition() { return PosX; }
	int GetYPosition() { return PosY; }
	
private:
	//The attributes of the tile
	SDL_Rect mBox;

	//The tile type
	int mType;

	//bool to see if space is occupied, for collision purposes
	bool mOccupied;
	
	//pointer to the entity that is standing in this space (tiles can only have, at most, one entity in their space)
	EntityClass* Occupant = NULL;

	int PosX;
	int PosY;

	//some way to list objects in the space
	std::vector<ObjectClass*> ItemsPresent; 


};
