#include "Armor.h"
#include "Tile.h"
#include "StaticFunctions.h"

ArmorObject::ArmorObject()
{
	SetName("UnknownArmor");
	SetArmorBonus(0);
	SetDamageReduction(0);
	SetMaxDex(0);
	SetArmorCheckPen(0);
	SetSpeedReduction(0);
	SetIsShield(false);
	SetBaseWeight(0);
}

ArmorObject::ArmorObject( ArmorObject const &other)
{
	if (other.mBox.x == NULL)
	{
		mBox.x = 0;
	}
	else
	{
		mBox.x = other.mBox.x;
	}

	if (other.mBox.y == NULL)
	{
		mBox.y = 0;
	}
	else
	{
		mBox.y = other.mBox.y;
	}

	if (other.mBox.w == NULL)
	{
		mBox.w = OBJECT_WIDTH;
	}
	else
	{
		mBox.w = other.mBox.w;
	}

	if (other.mBox.h == NULL)
	{
		mBox.h = OBJECT_HEIGHT;
	}
	else
	{
		mBox.h = other.mBox.h;
	}

	//copy constructor, copy all units
	//	int tempint = other.ArmorBonus;
	SetName(const_cast<ArmorObject&>(other).GetName());
	SetArmorBonus(other.ArmorBonus);
	SetDamageReduction(other.DamageReduction);
	SetMaxDex(other.MaxDexBonus);
	SetArmorCheckPen(other.ArmorCheckPenalty);
	SetSpeedReduction(other.SpeedReduction);
	SetIsShield(other.IsShield);
	SetBaseWeight(const_cast<ArmorObject&>(other).GetBaseWeight());
	SetPathTexture(other.mPathTexture);
	this->mTexture = other.mTexture;
	for (auto i = other.ArmorTypes.begin(); i != other.ArmorTypes.end(); i++)
	{
		AddArmorType((*i));
	}
	
}

ArmorObject::ArmorObject(ObjectClass &other)
{
	
	//copy constructor, copy all units
	//	int tempint = other.ArmorBonus;
	SetName(other.GetName());
	//std::cout << "Armor bonus of 'other' " << other.GetArmorBonus() << "of "<< other.GetName() << std::endl;
	this->SetArmorBonus(other.GetArmorBonus());
	SetDamageReduction(other.GetDamageReduction());
	SetMaxDex(other.GetMaxDexBonus());
	SetArmorCheckPen(other.GetArmorCheckPenalty());
	SetSpeedReduction(other.GetSpeedReduction());
	SetIsShield(other.GetIsShield());
	SetBaseWeight(other.GetBaseWeight());
	//std::cout << "Made it to loop armor copy construct" << std::endl;
	ArmorTypes = other.GetArmorTypes();
	SetPathTexture(other.GetPathTexture());
	this->mTexture = other.GetTexture();
	//DisplayArmorInfo();
}


const int ArmorObject::GetArmorBonus()
{
	return ArmorBonus;
}
void ArmorObject::SetArmorBonus(int bonus)
{
	ArmorBonus = bonus;
}

int ArmorObject::GetDamageReduction()
{
	return DamageReduction;
}
void ArmorObject::SetDamageReduction(int reduction)
{
	DamageReduction = reduction;
}

int ArmorObject::GetMaxDexBonus()
{
	return MaxDexBonus;
}
void ArmorObject::SetMaxDex(int max) 
{
	MaxDexBonus = max;
}

int ArmorObject::GetArmorCheckPenalty()
{
	return ArmorCheckPenalty;
}
void ArmorObject::SetArmorCheckPen(int penalty)
{
	ArmorCheckPenalty = penalty;
}

int ArmorObject::GetSpeedReduction()
{
	return SpeedReduction;
}
void ArmorObject::SetSpeedReduction(int SpeedReduction)
{
	this->SpeedReduction = SpeedReduction;
}

int ArmorObject::GetEquipActions()
{
	return EquipActions;
}
void ArmorObject::SetEquipActions(int actions)
{
	EquipActions = actions;
}

bool ArmorObject::GetIsShield()
{
	return IsShield;
}

void ArmorObject::SetIsShield(bool isShield)
{
	IsShield = isShield;
}

std::vector<ArmorType> ArmorObject::GetArmorTypes()
{
	return this->ArmorTypes;
}

void ArmorObject::AddArmorType(ArmorType addType)
{
	ArmorTypes.push_back(addType);
}

void ArmorObject::DisplayArmorInfo() 
{
	//start weapon facts

	std::cout << "Object Name: " << GetName() << std::endl;

	std::cout << "Armor bonus " << GetArmorBonus() << std::endl;
	std::cout << "DamageReduction " << GetDamageReduction() << std::endl;
	std::cout << "Max Dex " << GetMaxDexBonus() << std::endl;
	std::cout << "ACP " << GetArmorCheckPenalty() << std::endl;
	
	for (int i = 0; i != GetArmorTypes().size(); i++)
	{
		std::cout << ArmorTypeTextMap[ArmorTypes[i]] << std::endl;
	}
	
	std::cout << "Weight: " << GetBaseWeight() << "lb." << std::endl;
	if(GetIsShield())
	{
		std::cout << "This is a shield" << std::endl;
	}
	std::cout << "Max speed " << GetSpeedReduction() << std::endl << std::endl;
	
	//end Armor info
}

void ArmorObject::SetTexture(std::map<std::string, LTexture*> TextureMap, std::string Path)
{
	if (TextureMap.count(Path + "\\" + mPathTexture))
	{
		mTexture = TextureMap[Path + "\\" + mPathTexture];
		std::cout << mPathTexture << " Loaded into " << ObjectName << std::endl;
		//mTexture->setWidth(OBJECT_WIDTH);
		//mTexture->setHeight(OBJECT_HEIGHT);
	}
	else
	{
		std::cout << "No matching texture found " << mPathTexture << std::endl;
		mTexture = TextureMap[Path + "\\" + "QuestionMark.png"];
	}
}

void ArmorObject::SetLocation(int x, int y, std::vector<std::vector<Tile> > &TileMap)
{
	mLocation.first = x;
	mLocation.second = y;
	mBox.x = mLocation.first;
	mBox.y = mLocation.second;
	std::cout << mLocation.first << "," << mLocation.second << std::endl;
	SetRendLocation(TileMap);
	TileMap[x][y].AddItem(this);
}

void ArmorObject::SetRendLocation(std::vector<std::vector<Tile>> &TileVector)
{
	std::pair<int, int> tempLoc = CalcRendLocation(TileVector);
	mBox.x = tempLoc.first;
	mBox.y = tempLoc.second;
	std::cout << "New rend location for " << ObjectName << " = " << mBox.x << " " << mBox.y << std::endl;
}

std::pair<int, int> ArmorObject::CalcRendLocation(std::vector<std::vector<Tile>> &TileVector)
{
	//std::cout << "Calc rend location" << std::endl;
	std::pair <int, int> RetVal;
	int xTempLoc = mLocation.first;
	int yTempLoc = mLocation.second;

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


void ArmorObject::render(SDL_Rect& camera, SDL_Renderer *& Renderer)
{
	//If the texture is on screen
	if (checkCollision(camera, mBox))
	{
		//Show the texture
		mTexture->renderEntity(mBox.x - camera.x, mBox.y - camera.y, Renderer, &mBox);
		//std::cout << " Entity size " << mBox.h << " " << mBox.w << std::endl;
	}
}
