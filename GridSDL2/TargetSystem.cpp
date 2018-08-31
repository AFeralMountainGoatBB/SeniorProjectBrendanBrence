#include "TargetSystem.h"
#include "Tile.h"
#include "SharedEnums.h"

TargetSystem::TargetSystem()
{
	m_Box.x = 0;
	m_Box.y = 0;
	m_Box.w = m_TARGET_WIDTH;
	m_Box.h = m_TARGET_HEIGHT;
}

void TargetSystem::HandleTurn(SDL_Event& a_event)
{

}

void TargetSystem::handleEvent(SDL_Event& a_event)
{
	//If a key was pressed
	if (a_event.type == SDL_KEYDOWN && a_event.key.repeat == 0)
	{
		//change the location
		switch (a_event.key.keysym.sym)
		{
			//move to encounter handle
		case SDLK_s:m_MoveDirection = STATIONARY; break;
		case SDLK_w:m_MoveDirection = NORTH; break;
		case SDLK_a:m_MoveDirection = WEST; break;
		case SDLK_d:m_MoveDirection = EAST; break;
		case SDLK_x:m_MoveDirection = SOUTH; break;

		case SDLK_e:m_MoveDirection = NORTHEAST; break;
		case SDLK_q:m_MoveDirection = NORTHWEST; break;
		case SDLK_z:m_MoveDirection = SOUTHWEST; break;
		case SDLK_c:m_MoveDirection = SOUTHEAST; break;

		case SDLK_UP: m_MoveDirection = NORTH; break;
		case SDLK_DOWN: m_MoveDirection = SOUTH; break;
		case SDLK_LEFT: m_MoveDirection = WEST; break;
		case SDLK_RIGHT: m_MoveDirection = EAST; break;
		case SDLK_RETURN:{
			SetControlMode(SELECTTARGETMODE);
			this->m_Active = false;
			break;
		}

		}
	}
}
bool TargetSystem::move(std::vector<std::vector<Tile>> &a_TileVector)
{
	bool success = false;
	if (m_MoveDirection == STATIONARY)
	{
		return false;
	}
	switch (m_MoveDirection)
	{
		//check if we can move to the tile to next spot
		//move to the tile if we can
		//change moveDir to stationary
	case NORTH:
		if (m_Location.second != 0)
		{
			m_Location.second--;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
	
		break;

	case NORTHEAST:
		if (m_Location.second != 0 &&
			m_Location.first < a_TileVector.size() - 1)
		{
			m_Location.first++;
			m_Location.second--;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		break;

	case EAST:
		if (m_Location.first < a_TileVector.size() - 1)
		{
			m_Location.first++;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		break;

	case SOUTHEAST:
		if (m_Location.first < a_TileVector.size() - 1
			&&
			m_Location.second < a_TileVector[0].size() - 1)
		{
			m_Location.first++;
			m_Location.second++;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		break;

	case SOUTH:
		if (m_Location.second < a_TileVector[0].size() - 1)
		{
			success = true;
			m_Location.second++;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		break;

	case SOUTHWEST:
		if (m_Location.second < a_TileVector[0].size() - 1
			&&
			m_Location.first != 0)
		{
			
			m_Location.second++;
			m_Location.first--;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
			break;

	case WEST:
		if (m_Location.first != 0)
		{
			m_Location.first--;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		
		break;

	case NORTHWEST:
		if (m_Location.first != 0 
			&&
			m_Location.second != 0 )
		{
			m_Location.first--;
			m_Location.second--;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		break;
	} //end switch statement


	SetRendLocation(a_TileVector);
	m_MoveDirection = STATIONARY;
	return success;
}

void TargetSystem::SetLocation(int a_x, int a_y, std::vector < std::vector < Tile> > &a_TileMap) 
{
	m_Location.first = a_x;
	m_Location.second = a_y;
	
	this->SetRendLocation(a_TileMap);
}

void TargetSystem::SetRendLocation(std::vector<std::vector<Tile>> &a_TileVector)
{
	std::pair<int, int> tempLoc = CalcRendLocation(a_TileVector);
	m_Box.x = tempLoc.first;
	m_Box.y = tempLoc.second;
}

std::pair<int, int> TargetSystem::CalcRendLocation(std::vector<std::vector<Tile>> &a_TileVector) 
{
	//std::cout << "Calc rend location" << std::endl;
	std::pair <int, int> RetVal;
	int xTempLoc = GetLocation().first;
	int yTempLoc = GetLocation().second;

	std::cout << xTempLoc << "  " << yTempLoc << std::endl;

	int xOffset = 0;
	int yOffset = 0;
	//std::cout << "Accessing vector" << std::endl;
	RetVal.first = a_TileVector[xTempLoc][yTempLoc].GetXRenderPos();
	RetVal.second = a_TileVector[xTempLoc][yTempLoc].GetYRenderPos();

	xOffset = 0.5 * (a_TileVector[xTempLoc][yTempLoc].GetWidth() - m_ENTITY_WIDTH);
	yOffset = 0.5 * (a_TileVector[xTempLoc][yTempLoc].GetWidth() - m_ENTITY_HEIGHT);

	RetVal.first = RetVal.first + xOffset;
	RetVal.second = RetVal.second + yOffset;

	return RetVal;

}

std::pair<int, int> TargetSystem::GetLocation() 
{
	return std::pair<int, int>(m_Location.first, m_Location.second);
}

//Centers the m_camera over the entity
void TargetSystem::setCamera(SDL_Rect& a_camera) 
{
	//Center the m_camera over the entity
	a_camera.x = (m_Box.x + m_ENTITY_WIDTH / 2) - g_SCREEN_WIDTH / 2;
	a_camera.y = (m_Box.y + m_ENTITY_HEIGHT / 2) - g_SCREEN_HEIGHT / 2;

	//Keep the m_camera in bounds
	if (a_camera.x < 0)
	{
		a_camera.x = 0;
	}
	if (a_camera.y < 0)
	{
		a_camera.y = 0;
	}
	if (a_camera.x > g_LEVEL_WIDTH - a_camera.w)
	{
		a_camera.x = g_LEVEL_WIDTH - a_camera.w;
	}
	if (a_camera.y > g_LEVEL_HEIGHT - a_camera.h)
	{
		a_camera.y = g_LEVEL_HEIGHT - a_camera.h;
	}
}

//Shows the entity on the screen
void TargetSystem::render(SDL_Rect& a_camera, SDL_Renderer *& a_Renderer)
{
	if (this->m_Active == false)
	{
		return;
	}
	//If the texture is on screen
	if (checkCollision(a_camera, m_Box))
	{
		//Show the texture
		m_Texture->renderEntity(m_Box.x - a_camera.x, m_Box.y - a_camera.y, a_Renderer, &m_Box);
		//std::cout << " Entity size " << m_Box.h << " " << m_Box.w << std::endl;
	}
}

void TargetSystem::SetTexture(std::map<std::string, LTexture*> &a_TextureMap, std::string a_Path)
{
	if (a_TextureMap.count(a_Path + "\\" + m_PathTexture))
	{
		m_Texture = a_TextureMap[a_Path + "\\" + m_PathTexture];
		//std::cout << m_PathTexture << " Loaded into " << m_EntityName << std::endl;
	}
	else
	{
		std::cout << "No matching texture found " << a_Path << "\\" << m_PathTexture << std::endl;
		m_Texture = a_TextureMap[a_Path + "\\" + "QuestionMark.png"];
	}
}

LTexture* TargetSystem::GetTexture()
{
	return m_Texture;
}