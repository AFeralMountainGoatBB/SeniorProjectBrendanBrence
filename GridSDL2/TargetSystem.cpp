#include "TargetSystem.h"
#include "Tile.h"
#include "SharedEnums.h"

TargetSystem::TargetSystem()
{
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = TARGET_WIDTH;
	mBox.h = TARGET_HEIGHT;
}

void TargetSystem::HandleTurn(SDL_Event& e)
{

}

void TargetSystem::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//change the location
		switch (e.key.keysym.sym)
		{
			//move to encounter handle
		case SDLK_s:MoveDirection = STATIONARY; break;
		case SDLK_w:MoveDirection = NORTH; break;
		case SDLK_a:MoveDirection = WEST; break;
		case SDLK_d:MoveDirection = EAST; break;
		case SDLK_x:MoveDirection = SOUTH; break;

		case SDLK_e:MoveDirection = NORTHEAST; break;
		case SDLK_q:MoveDirection = NORTHWEST; break;
		case SDLK_z:MoveDirection = SOUTHWEST; break;
		case SDLK_c:MoveDirection = SOUTHEAST; break;

		case SDLK_UP: MoveDirection = NORTH; break;
		case SDLK_DOWN: MoveDirection = SOUTH; break;
		case SDLK_LEFT: MoveDirection = WEST; break;
		case SDLK_RIGHT: MoveDirection = EAST; break;
		case SDLK_RETURN:{
			SetControlMode(SELECTTARGETMODE);
			this->Active = false;
			break;
		}

		}
	}
}
bool TargetSystem::move(std::vector<std::vector<Tile>> &TileVector)
{
	bool success = false;
	if (MoveDirection == STATIONARY)
	{
		return false;
	}
	switch (MoveDirection)
	{
		//check if we can move to the tile to next spot
		//move to the tile if we can
		//change moveDir to stationary
	case NORTH:
		if (mLocation.second != 0)
		{
			mLocation.second--;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
	
		break;

	case NORTHEAST:
		if (mLocation.second != 0 &&
			mLocation.first < TileVector.size() - 1)
		{
			mLocation.first++;
			mLocation.second--;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		break;

	case EAST:
		if (mLocation.first < TileVector.size() - 1)
		{
			mLocation.first++;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		break;

	case SOUTHEAST:
		if (mLocation.first < TileVector.size() - 1
			&&
			mLocation.second < TileVector[0].size() - 1)
		{
			mLocation.first++;
			mLocation.second++;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		break;

	case SOUTH:
		if (mLocation.second < TileVector[0].size() - 1)
		{
			success = true;
			mLocation.second++;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		break;

	case SOUTHWEST:
		if (mLocation.second < TileVector[0].size() - 1
			&&
			mLocation.first != 0)
		{
			
			mLocation.second++;
			mLocation.first--;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
			break;

	case WEST:
		if (mLocation.first != 0)
		{
			mLocation.first--;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		
		break;

	case NORTHWEST:
		if (mLocation.first != 0 
			&&
			mLocation.second != 0 )
		{
			mLocation.first--;
			mLocation.second--;
			success = true;
		}
		else
		{
			std::cout << "Cannot move there" << std::endl;
			success = false;
		}
		break;
	} //end switch statement


	SetRendLocation(TileVector);
	MoveDirection = STATIONARY;
	return success;
}

void TargetSystem::SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap) 
{
	mLocation.first = x;
	mLocation.second = y;
	
	this->SetRendLocation(TileMap);
}

void TargetSystem::SetRendLocation(std::vector<std::vector<Tile>> &TileVector)
{
	std::pair<int, int> tempLoc = CalcRendLocation(TileVector);
	mBox.x = tempLoc.first;
	mBox.y = tempLoc.second;
}

std::pair<int, int> TargetSystem::CalcRendLocation(std::vector<std::vector<Tile>> &TileVector) 
{
	//std::cout << "Calc rend location" << std::endl;
	std::pair <int, int> RetVal;
	int xTempLoc = GetLocation().first;
	int yTempLoc = GetLocation().second;

	std::cout << xTempLoc << "  " << yTempLoc << std::endl;

	int xOffset = 0;
	int yOffset = 0;
	//std::cout << "Accessing vector" << std::endl;
	RetVal.first = TileVector[xTempLoc][yTempLoc].GetXRenderPos();
	RetVal.second = TileVector[xTempLoc][yTempLoc].GetYRenderPos();

	xOffset = 0.5 * (TileVector[xTempLoc][yTempLoc].GetWidth() - ENTITY_WIDTH);
	yOffset = 0.5 * (TileVector[xTempLoc][yTempLoc].GetWidth() - ENTITY_HEIGHT);

	RetVal.first = RetVal.first + xOffset;
	RetVal.second = RetVal.second + yOffset;

	return RetVal;

}

std::pair<int, int> TargetSystem::GetLocation() 
{
	return std::pair<int, int>(mLocation.first, mLocation.second);
}

//Centers the camera over the entity
void TargetSystem::setCamera(SDL_Rect& camera) 
{
	//Center the camera over the entity
	camera.x = (mBox.x + ENTITY_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (mBox.y + ENTITY_HEIGHT / 2) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

//Shows the entity on the screen
void TargetSystem::render(SDL_Rect& camera, SDL_Renderer *& Renderer)
{
	if (this->Active == false)
	{
		return;
	}
	//If the texture is on screen
	if (checkCollision(camera, mBox))
	{
		//Show the texture
		mTexture->renderEntity(mBox.x - camera.x, mBox.y - camera.y, Renderer, &mBox);
		//std::cout << " Entity size " << mBox.h << " " << mBox.w << std::endl;
	}
}

void TargetSystem::SetTexture(std::map<std::string, LTexture*> &TextureMap, std::string Path)
{
	if (TextureMap.count(Path + "\\" + mPathTexture))
	{
		mTexture = TextureMap[Path + "\\" + mPathTexture];
		//std::cout << mPathTexture << " Loaded into " << EntityName << std::endl;
	}
	else
	{
		std::cout << "No matching texture found " << Path << "\\" << mPathTexture << std::endl;
		mTexture = TextureMap[Path + "\\" + "QuestionMark.png"];
	}
}

LTexture* TargetSystem::GetTexture()
{
	return mTexture;
}