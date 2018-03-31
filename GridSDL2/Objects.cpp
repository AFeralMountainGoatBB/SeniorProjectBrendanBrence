#include "Objects.h"
#include "Tile.h"
#include "StaticFunctions.h"


ObjectClass::ObjectClass()
{
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = OBJECT_WIDTH;
	mBox.h = OBJECT_HEIGHT;
	//std::cout << "Entity size, H, w : " << mBox.w << " " << mBox.h << std::endl;
}

void ObjectClass::setCamera(SDL_Rect& camera)
{
	//Center the camera over the entity
	camera.x = (mBox.x + OBJECT_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (mBox.y + OBJECT_HEIGHT / 2) - SCREEN_HEIGHT / 2;

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

void ObjectClass::SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap)
{
	mLocation.first = x;
	mLocation.second = y;
	TileMap[x][y].AddItem(this);
}

std::pair<int, int> ObjectClass::GetLocation()
{
	return mLocation;
}

void ObjectClass::SetRendLocation(std::vector<std::vector<Tile>> &TileVector)
{
	std::pair<int, int> tempLoc = CalcRendLocation(TileVector);
	mBox.x = tempLoc.first;
	mBox.y = tempLoc.second;
	std::cout << "New rend location for " << ObjectName << " = " << mBox.x << " " << mBox.y << std::endl;
}

std::pair<int, int> ObjectClass::CalcRendLocation(std::vector<std::vector<Tile>> &TileVector)
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

	xOffset = 0.5 * (TileVector[xTempLoc][yTempLoc].GetWidth() - OBJECT_WIDTH);
	yOffset = 0.5 * (TileVector[xTempLoc][yTempLoc].GetWidth() - OBJECT_HEIGHT);

	RetVal.first = RetVal.first + xOffset;
	RetVal.second = RetVal.second + yOffset;

	return RetVal;
}

//render and texture functions

void ObjectClass::render(SDL_Rect& camera, SDL_Renderer *& Renderer)
{

	//If the texture is on screen
	if (checkCollision(camera, mBox))
	{
		//Show the texture
		mTexture->renderEntity(mBox.x - camera.x, mBox.y - camera.y, Renderer, &mBox);
		//std::cout << " Entity size " << mBox.h << " " << mBox.w << std::endl;
	}
}

LTexture* ObjectClass::GetTexture()
{
	return mTexture;
}

void ObjectClass::SetTexture(std::map<std::string, LTexture*> TextureMap, std::string Path)
{
	if (TextureMap.count(Path +"\\"+ mPathTexture))
	{
		mTexture = TextureMap[Path +"\\"+ mPathTexture];
		//std::cout << mPathTexture << " Loaded into " << ObjectName << std::endl;
		mTexture->setWidth(OBJECT_WIDTH);
		//mTexture->setHeight(OBJECT_HEIGHT);
	}
	else
	{
		std::cout << "No matching texture found " << mPathTexture << std::endl;
	}
}


//get properties start
bool ObjectClass::GetTwoHanded()
{
	return TwoHanded;
}

void ObjectClass::SetName(std::string PassedName)
{
	ObjectName = PassedName;
}

std::string ObjectClass::GetName()
{
	return ObjectName;
}

BodyLocation ObjectClass::GetBodySlot()
{
	return this->BodySlot;
}

float ObjectClass::GetBaseWeight()
{
	return Weight;
}

void ObjectClass::SetBaseWeight(float Weight)
{
	Weight = Weight;
}





//loading functions start reader is passed from function to function
bool ObjectClass::LoadObject()
{


	return false;
}

bool ObjectClass::LoadNameAndDescription()
{

	return false;
}

bool ObjectClass::LoadProperties()
{

	return false;
}

//loading functions end