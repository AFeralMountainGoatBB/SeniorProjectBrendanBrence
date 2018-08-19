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

ObjectClass::ObjectClass( ObjectClass const &other)
{
	if (other.mBox.x == NULL)
	{
		mBox.x = 0;
	}
	else
	{
		mBox.x = other.mBox.x;
	}
	
	if (other.mBox.y==NULL)
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
	
	mPathTexture = other.mPathTexture;
	ObjectName = other.ObjectName;
	ObjectDescription = other.ObjectDescription;

	TwoHanded = other.TwoHanded;
	Versatile = other.Versatile;
	for (auto i = other.WeaponTypes.begin(); i != other.WeaponTypes.end(); i++)
	{
		this->WeaponTypes.push_back(*i);
	}
	for (auto i = other.DamageTypes.begin(); i != other.DamageTypes.end(); i++)
	{
		this->DamageTypes.push_back(*i);
	}
	DamageDice.first = other.DamageDice.first;
	DamageDice.second = other.DamageDice.second;

	Weight = other.Weight;
	BodySlot = other.BodySlot;
	CritMultiplier = other.CritMultiplier;
	CritThreat = other.CritThreat;

	ArmorBonus = other.ArmorBonus;
	 DamageReduction = other.DamageReduction;
	 MaxDexBonus = other.MaxDexBonus;
	ArmorCheckPenalty = other.ArmorCheckPenalty;
	SpeedReduction = other.SpeedReduction;
	EquipActions = other.EquipActions;
	IsShield = other.IsShield;
	RangeIncrement = other.RangeIncrement;
	
	mTexture = other.mTexture;

	ArmorTypes = other.ArmorTypes;
}

void ObjectClass::SetmBox(int x, int y, int w, int h)
{
	mBox.x = x;
	mBox.y = y;
	mBox.w = w;
	mBox.h = h;
}

bool ObjectClass::IsRangedWeapon()
{
	if (std::find(WeaponTypes.begin(), WeaponTypes.end(), RANGED) != WeaponTypes.end()
		|| std::find(WeaponTypes.begin(), WeaponTypes.end(), THROWN) != WeaponTypes.end())
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

bool ObjectClass::IsThrowingWeapon()
{
	if (std::find(WeaponTypes.begin(), WeaponTypes.end(), THROWN) != WeaponTypes.end())
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool ObjectClass::IsLightWeapon()
{
	if (WeaponTypes.empty() == true)
	{
		return false;
	}
		
	if (std::find(WeaponTypes.begin(), WeaponTypes.end(), LIGHT) != WeaponTypes.end())
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool ObjectClass::IsMeleeWeapon()
{
	if (std::find(WeaponTypes.begin(), WeaponTypes.end(), MELEE) != WeaponTypes.end())
	{
		return true;
	}
	else
	{
		return false;
	}

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
	SetRendLocation(TileMap);
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


//get properties start
bool ObjectClass::GetTwoHanded()
{
	return TwoHanded;
}

void ObjectClass::SetTwoHanded(bool passed)
{
	TwoHanded = passed;
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
	return BodySlot;
}

const float ObjectClass::GetBaseWeight()
{
	return Weight;
}

void ObjectClass::SetBaseWeight(float Weight)
{
	this->Weight = Weight;
}

void ObjectClass::SetDamageDice(std::pair<int, DiceType> DamageDicePassed)
{
	DamageDice = DamageDicePassed;
}

std::pair<int, DiceType> ObjectClass::GetDamageDice()
{
	return DamageDice;
}

std::vector<DamageType>& ObjectClass::GetDamageTypes()
{
	return this->DamageTypes;
}

void ObjectClass::AddDamageType(DamageType AddDamage)
{
	this->DamageTypes.push_back(AddDamage);
}

void ObjectClass::SetCritInformation(int range, int multiplier)
{
	CritThreat = range;
	CritMultiplier = multiplier;
}

std::pair<int, int> ObjectClass::GetCritInformation()
{
	return std::pair<int, int>(CritThreat, CritMultiplier);
}

void ObjectClass::AddWeaponType(WeaponType AddType)
{
	this->WeaponTypes.push_back(AddType);
}

std::vector<WeaponType>& ObjectClass:: GetWeaponType()
{
	if (WeaponTypes.empty() == true)
	{
		WeaponTypes.push_back(IMPROVISED);
	}
	return WeaponTypes;
}


//loading functions start reader is passed from function to function
bool ObjectClass::LoadObject()
{


	return false;
}

bool ObjectClass::LoadObjectByName(std::string line)
{

	return true;
}

bool ObjectClass::LoadNameAndDescription()
{

	return false;
}

bool ObjectClass::LoadProperties()
{

	return false;
}

bool ObjectClass:: GetVersatile()
{
	return Versatile;
}

void ObjectClass::SetVersatile(bool passed)
{
	Versatile = passed;
}

//loading functions end

void ObjectClass::DisplayObjectWeaponFacts()
{

	//start weapon facts
	std::cout << "Object Name: " << ObjectName << std::endl;
	//std::string ObjectDescription = "";

	std::cout << "Damage dice: " << DamageDice.first << "d" << DamageDice.second << std::endl;
	
	//display weapon types
	std::cout << "Weapon Types: "<<std::endl<< "\t";
	for (auto i = WeaponTypes.begin(); i != WeaponTypes.end(); i++)
	{
		std::cout << WeaponTypeTextMap[(*i)] << ", ";
	}
	if (Versatile)
	{
		std::cout << "Versatile, " << std::endl;
	}

	if (TwoHanded)
	{
		std::cout << "Two Handed, " << std::endl;
	}
	std::cout << std::endl;


	//display damage types
	std::cout << "Damage Types: " << std::endl << "\t";
	for (auto i = DamageTypes.begin(); i != DamageTypes.end(); i++)
	{
		if (i != DamageTypes.begin())
		{
			std::cout << ", " << std::endl;
		}
		std::cout << DamageTypeTextMap[(*i)];
	}
	std::cout << std::endl;

	std::cout << "Weight: " << Weight << "lb." << std::endl;
	std::cout << "Range increment: " << RangeIncrement << std::endl;

	std::cout << "Criticals: " << GetCritInformation().first << "/x" << GetCritInformation().second << std::endl;
	
	std::cout << "End " << ObjectName << std::endl << std::endl;
	//end weaponfacts
}

const int ObjectClass::GetArmorBonus()
{
	return ArmorBonus;
}
void ObjectClass::SetArmorBonus(int bonus)
{
	ArmorBonus = bonus;
}

int ObjectClass::GetDamageReduction()
{
	return DamageReduction;
}
void ObjectClass::SetDamageReduction(int reduction)
{
	DamageReduction = reduction;
}

int ObjectClass::GetMaxDexBonus()
{
	return MaxDexBonus;
}
void ObjectClass::SetMaxDex(int max)
{
	MaxDexBonus = max;
}

int ObjectClass::GetArmorCheckPenalty()
{
	return ArmorCheckPenalty;
}
void ObjectClass::SetArmorCheckPen(int penalty)
{
	ArmorCheckPenalty = penalty;
}

int ObjectClass::GetSpeedReduction()
{
	return SpeedReduction;
}
void ObjectClass::SetSpeedReduction(int SpeedReduction)
{
	this->SpeedReduction = SpeedReduction;
}

int ObjectClass::GetEquipActions()
{
	return EquipActions;
}
void ObjectClass::SetEquipActions(int actions)
{
	EquipActions = actions;
}

bool ObjectClass::GetIsShield()
{
	return IsShield;
}

void ObjectClass::SetIsShield(bool isShield)
{
	IsShield = isShield;
}

std::vector<ArmorType> ObjectClass::GetArmorTypes()
{
	return this->ArmorTypes;
}

void ObjectClass::AddArmorType(ArmorType addType)
{
	ArmorTypes.push_back(addType);
}

void ObjectClass::DisplayArmorInfo()
{
		//start weapon facts

		std::cout << "Object Name: " << GetName() << std::endl;

		std::cout << "Armor bonus " << GetArmorBonus() << std::endl;
		std::cout << "DamageReduction " << GetDamageReduction() << std::endl;
		std::cout << "Max Dex " << GetMaxDexBonus() << std::endl;
		std::cout << "ACP " << GetArmorCheckPenalty() << std::endl;

		std::cout << "Entering loop display armor" << std::endl;
		for (auto i = ArmorTypes.begin(); i != ArmorTypes.end(); i++)
		{
			std::cout << "Entered loop" << std::endl;
			//std::cout << ArmorTypeTextMap[(*i)] << std::endl;
		}

		std::cout << "Weight: " << GetBaseWeight() << "lb." << std::endl;
		if (GetIsShield())
		{
			std::cout << "This is a shield" << std::endl;
		}
		std::cout << "Max speed " << GetSpeedReduction() << std::endl << std::endl;

		//end Armor info
}