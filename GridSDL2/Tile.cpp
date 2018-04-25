#include "Tile.h"
#include "StaticFunctions.h"
#include "Texture.h"

Tile::Tile()
{
	//default offsets
	mBox.x = 0;
	mBox.y = 0;

	//still the same tile and width
	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;
	//0 should always be a passable tile
	mType = 0;
}

Tile::Tile(int x, int y, int tileType)
{
	//Get the offsets
	mBox.x = x;
	mBox.y = y;

	//Set the collision box
	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;

	//Get the tile type
	mType = tileType;

}

void Tile::render(SDL_Rect& camera, LTexture &TileTexture, SDL_Rect gTileClips[], SDL_Renderer *&Renderer)
{
	//If the tile is on screen
	if (checkCollision(camera, mBox))
	{
		//Show the tile
		TileTexture.renderTile(mBox.x - camera.x, mBox.y - camera.y, Renderer, &gTileClips[mType]);

		if (GetTopObject())
		{
			//std::cout << "An object is here, rendering it" << std::endl;
			GetTopObject()->render(camera, Renderer);
			//std::cout << "It rendered" << std::endl;
		}
	}
}

bool Tile::getPassable()
{
	if (mType >= TILE_CENTER && mType <= TILE_TOPLEFT || mOccupied==true)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int Tile::getType()
{
	return mType;
}

SDL_Rect Tile::getBox()
{
	return mBox;
}

int Tile::GetXRenderPos()
{
	return mBox.x;
}

int Tile::GetYRenderPos()
{
	return mBox.y;
}

int Tile::GetWidth()
{
	return mBox.w;
}


void Tile::ClearOccupant()
{
	Occupant = NULL;
	mOccupied = false;
}

void Tile::SetOccupant(EntityClass &Entity)
{
	Occupant = &Entity;
	mOccupied = true;
}

EntityClass* Tile::GetOccupant()
{
	return Occupant;
}

void Tile:: AddItem(ObjectClass* Item)
{
	
	ItemsPresent.push_back(Item);
	//ItemsPresent.back()->DisplayObjectWeaponFacts();
}

Tile Tile::RemoveObject(ObjectClass* item)
{
	for (auto iter = ItemsPresent.begin(); iter != ItemsPresent.end(); iter++)
	{
		//	std::cout<<"top object name " << this->GetTopObject()->GetName()<<std::endl;
		if (item == (*iter))
		{
			std::cout << "Item found, removing" << std::endl;
			//(*iter) = nullptr;
			this->ItemsPresent.erase(iter);
			return *this;
		}
		
	}
	std::cout << "Item not found" << std::endl;
}

ObjectClass* Tile::GetTopObject()
{
	if (!ItemsPresent.empty())
	{
	return ItemsPresent[0];
	}
	else
	{
		return NULL;
	}
}

 std::vector<ObjectClass*>& Tile::GetItemsPresent()
{
	return ItemsPresent;
}