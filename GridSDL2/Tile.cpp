#include "Tile.h"
#include "StaticFunctions.h"
#include "Texture.h"

Tile::Tile()
{
	//default offsets
	m_Box.x = 0;
	m_Box.y = 0;

	//still the same tile and m_width
	m_Box.w = g_TILE_WIDTH;
	m_Box.h = g_TILE_HEIGHT;
	//0 should always be a passable tile
	m_type = 0;
}

Tile::Tile(int a_x, int a_y, int a_tileType)
{
	//Get the offsets
	m_Box.x = a_x;
	m_Box.y = a_y;

	//Set the collision box
	m_Box.w = g_TILE_WIDTH;
	m_Box.h = g_TILE_HEIGHT;

	//Get the tile type
	m_type = a_tileType;

}

void Tile::render(SDL_Rect& a_camera, LTexture &a_TileTexture, SDL_Rect a_TileClips[], SDL_Renderer *&a_Renderer)
{
	//If the tile is on screen
	if (checkCollision(a_camera, m_Box))
	{
		//Show the tile
		a_TileTexture.renderTile(m_Box.x - a_camera.x, m_Box.y - a_camera.y, a_Renderer, &a_TileClips[m_type]);

		if (GetTopObject())
		{
			//std::cout << "An object is here, rendering it" << std::endl;
			GetTopObject()->render(a_camera, a_Renderer);
			//std::cout << "It rendered" << std::endl;
		}
	}
}

bool Tile::getPassable()
{
	if (m_type >= g_TILE_CENTER && m_type <= g_TILE_TOPLEFT || m_Occupied==true)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Tile::getPassableTileType()
{
	if (m_type >= g_TILE_CENTER && m_type <= g_TILE_TOPLEFT)
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
	return m_type;
}

SDL_Rect Tile::getBox()
{
	return m_Box;
}

int Tile::GetXRenderPos()
{
	return m_Box.x;
}

int Tile::GetYRenderPos()
{
	return m_Box.y;
}

int Tile::GetWidth()
{
	return m_Box.w;
}

void Tile::ClearOccupant()
{
	m_occupant = nullptr;
	m_Occupied = false;
}

void Tile::SetOccupant(EntityClass &a_Entity)
{
	m_occupant = &a_Entity;
	m_Occupied = true;
}

EntityClass* Tile::GetOccupant()
{
	return m_occupant;
}

void Tile:: AddItem(ObjectClass* a_item)
{
	
	m_ItemsPresent.push_back(a_item);
	//m_ItemsPresent.back()->DisplayObjectWeaponFacts();
}

Tile Tile::RemoveObject(ObjectClass* a_item)
{
	for (auto iter = m_ItemsPresent.begin(); iter != m_ItemsPresent.end(); iter++)
	{
		//	std::cout<<"top object m_name " << this->GetTopObject()->GetName()<<std::endl;
		if (a_item == (*iter))
		{
			std::cout << "a_item found, removing" << std::endl;
			//(*iter) = nullptr;
			this->m_ItemsPresent.erase(iter);
			return *this;
		}
		
	}
	std::cout << "a_item not found" << std::endl;
}

ObjectClass* Tile::GetTopObject()
{
	if (!m_ItemsPresent.empty())
	{
	return m_ItemsPresent[0];
	}
	else
	{
		return NULL;
	}
}

 std::vector<ObjectClass*>& Tile::GetItemsPresent()
{
	return m_ItemsPresent;
}

 bool Tile::EntityPresent()
 {
	 return m_Occupied;
 }
