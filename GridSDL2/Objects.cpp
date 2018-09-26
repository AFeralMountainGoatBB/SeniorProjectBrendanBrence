#include "Objects.h"
#include "Tile.h"
#include "StaticFunctions.h"


ObjectClass::ObjectClass()
{
	m_Box.x = 0;
	m_Box.y = 0;
	m_Box.w = m_OBJECT_WIDTH;
	m_Box.h = m_OBJECT_HEIGHT;
	//std::cout << "Entity size, H, a_w : " << m_Box.a_w << " " << m_Box.a_h << std::endl;
}

ObjectClass::ObjectClass( ObjectClass const &a_other)
{
	if (a_other.m_Box.x == NULL)
	{
		m_Box.x = 0;
	}
	else
	{
		m_Box.x = a_other.m_Box.x;
	}
	
	if (a_other.m_Box.y==NULL)
	{
		m_Box.y = 0;
	}
	else
	{
		m_Box.y = a_other.m_Box.y;
	}

	if (a_other.m_Box.w == NULL)
	{
		m_Box.w = m_OBJECT_WIDTH;
	}
	else
	{
		m_Box.w = a_other.m_Box.w;
	}

	if (a_other.m_Box.h == NULL)
	{
		m_Box.h = m_OBJECT_HEIGHT;
	}
	else
	{
		m_Box.h = a_other.m_Box.h;
	}
	
	m_PathTexture = a_other.m_PathTexture;
	m_ObjectName = a_other.m_ObjectName;
	m_ObjectDescription = a_other.m_ObjectDescription;

	m_TwoHanded = a_other.m_TwoHanded;
	m_Versatile = a_other.m_Versatile;
	for (auto i = a_other.m_weaponTypes.begin(); i != a_other.m_weaponTypes.end(); i++)
	{
		this->m_weaponTypes.push_back(*i);
	}
	for (auto i = a_other.m_damageTypes.begin(); i != a_other.m_damageTypes.end(); i++)
	{
		this->m_damageTypes.push_back(*i);
	}
	m_damageDice.first = a_other.m_damageDice.first;
	m_damageDice.second = a_other.m_damageDice.second;

	m_Weight = a_other.m_Weight;
	m_BodySlot = a_other.m_BodySlot;
	m_CritMultiplier = a_other.m_CritMultiplier;
	m_CritThreat = a_other.m_CritThreat;

	m_armorBonus = a_other.m_armorBonus;
	 m_damageReduction = a_other.m_damageReduction;
	 m_maxDexBonus = a_other.m_maxDexBonus;
	m_armorCheckPenalty = a_other.m_armorCheckPenalty;
	m_speedReduction = a_other.m_speedReduction;
	m_equipActions = a_other.m_equipActions;
	m_isShield = a_other.m_isShield;
	m_RangeIncrement = a_other.m_RangeIncrement;
	
	m_Texture = a_other.m_Texture;

	m_armorTypes = a_other.m_armorTypes;
}

void ObjectClass::SetmBox(int a_x, int a_y, int a_w, int a_h)
{
	m_Box.x = a_x;
	m_Box.y = a_y;
	m_Box.w = a_w;
	m_Box.h = a_h;
}

bool ObjectClass::IsRangedWeapon()
{
	if (std::find(m_weaponTypes.begin(), m_weaponTypes.end(), RANGED) != m_weaponTypes.end()
		|| std::find(m_weaponTypes.begin(), m_weaponTypes.end(), THROWN) != m_weaponTypes.end())
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
	if (std::find(m_weaponTypes.begin(), m_weaponTypes.end(), THROWN) != m_weaponTypes.end())
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
	if (m_weaponTypes.empty() == true)
	{
		return false;
	}
		
	if (std::find(m_weaponTypes.begin(), m_weaponTypes.end(), LIGHT) != m_weaponTypes.end())
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
	if (std::find(m_weaponTypes.begin(), m_weaponTypes.end(), MELEE) != m_weaponTypes.end())
	{
		return true;
	}
	else
	{
		return false;
	}

}


void ObjectClass::setCamera(SDL_Rect& a_camera)
{
	//Center the m_camera over the entity
	a_camera.x = (m_Box.x + m_OBJECT_WIDTH / 2) - g_SCREEN_WIDTH / 2;
	a_camera.y = (m_Box.y + m_OBJECT_HEIGHT / 2) - g_SCREEN_HEIGHT / 2;

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

void ObjectClass::SetLocation(int x, int y, std::vector < std::vector < Tile> > &a_TileMap)
{
	m_Location.first = x;
	m_Location.second = y;
	a_TileMap[x][y].AddItem(this);
	SetRendLocation(a_TileMap);
}

std::pair<int, int> ObjectClass::GetLocation()
{
	return m_Location;
}

void ObjectClass::SetRendLocation(std::vector<std::vector<Tile>> &a_TileVector)
{
	std::pair<int, int> tempLoc = CalcRendLocation(a_TileVector);
	m_Box.x = tempLoc.first;
	m_Box.y = tempLoc.second;
	std::cout << "New rend location for " << m_ObjectName << " = " << m_Box.x << " " << m_Box.y << std::endl;
}

std::pair<int, int> ObjectClass::CalcRendLocation(std::vector<std::vector<Tile>> &a_TileVector)
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

	xOffset = 0.5 * (a_TileVector[xTempLoc][yTempLoc].GetWidth() - m_OBJECT_WIDTH);
	yOffset = 0.5 * (a_TileVector[xTempLoc][yTempLoc].GetWidth() - m_OBJECT_HEIGHT);

	RetVal.first = RetVal.first + xOffset;
	RetVal.second = RetVal.second + yOffset;

	return RetVal;
}

//render and texture functions

void ObjectClass::render(SDL_Rect& a_camera, SDL_Renderer *& a_Renderer)
{

	//If the texture is on screen
	if (checkCollision(a_camera, m_Box))
	{
		//Show the texture
		m_Texture->renderEntity(m_Box.x - a_camera.x, m_Box.y - a_camera.y, a_Renderer, &m_Box);
		//std::cout << " Entity size " << m_Box.a_h << " " << m_Box.a_w << std::endl;
	}
}

LTexture* ObjectClass::GetTexture()
{
	return m_Texture;
}

void ObjectClass::SetTexture(std::map<std::string, LTexture*> a_TextureMap, std::string a_Path)
{
	if (a_TextureMap.count(a_Path +"\\"+ m_PathTexture))
	{
		m_Texture = a_TextureMap[a_Path +"\\"+ m_PathTexture];
		std::cout << m_PathTexture << " Loaded into " << m_ObjectName << std::endl;
		//m_Texture->setWidth(m_OBJECT_WIDTH);
		//m_Texture->setHeight(m_OBJECT_HEIGHT);
	}
	else
	{
		std::cout << "No matching texture found " << m_PathTexture << std::endl;
		m_Texture = a_TextureMap[a_Path + "\\" + "QuestionMark.png"];
	}
}


//get properties start
bool ObjectClass::GetTwoHanded()
{
	return m_TwoHanded;
}

void ObjectClass::SetTwoHanded(bool a_passed)
{
	m_TwoHanded = a_passed;
}

void ObjectClass::SetName(std::string a_PassedName)
{
	m_ObjectName = a_PassedName;
}

std::string ObjectClass::GetName()
{
	return m_ObjectName;
}

BodyLocation ObjectClass::GetBodySlot()
{
	return m_BodySlot;
}

const float ObjectClass::GetBaseWeight()
{
	return m_Weight;
}

void ObjectClass::SetBaseWeight(float a_Weight)
{
	this->m_Weight = a_Weight;
}

void ObjectClass::SetDamageDice(std::pair<int, DiceType> a_DamageDicePassed)
{
	m_damageDice = a_DamageDicePassed;
}

std::pair<int, DiceType> ObjectClass::GetDamageDice()
{
	return m_damageDice;
}

std::vector<DamageType>& ObjectClass::GetDamageTypes()
{
	return this->m_damageTypes;
}

void ObjectClass::AddDamageType(DamageType a_AddDamage)
{
	this->m_damageTypes.push_back(a_AddDamage);
}

void ObjectClass::SetCritInformation(int a_range, int a_multiplier)
{
	m_CritThreat = a_range;
	m_CritMultiplier = a_multiplier;
}

std::pair<int, int> ObjectClass::GetCritInformation()
{
	return std::pair<int, int>(m_CritThreat, m_CritMultiplier);
}

void ObjectClass::AddWeaponType(WeaponType a_AddType)
{
	this->m_weaponTypes.push_back(a_AddType);
}

std::vector<WeaponType>& ObjectClass:: GetWeaponType()
{
	if (m_weaponTypes.empty() == true)
	{
		m_weaponTypes.push_back(IMPROVISED);
	}
	return m_weaponTypes;
}

bool ObjectClass:: GetVersatile()
{
	return m_Versatile;
}

void ObjectClass::SetVersatile(bool a_passed)
{
	m_Versatile = a_passed;
}

//loading functions end

void ObjectClass::DisplayObjectWeaponFacts()
{

	//start weapon facts
	std::cout << "Object Name: " << m_ObjectName << std::endl;
	//std::string m_ObjectDescription = "";

	std::cout << "Damage dice: " << m_damageDice.first << "d" << m_damageDice.second << std::endl;
	
	//display weapon types
	std::cout << "Weapon Types: "<<std::endl<< "\t";
	for (auto i = m_weaponTypes.begin(); i != m_weaponTypes.end(); i++)
	{
		std::cout << WeaponTypeTextMap[(*i)] << ", ";
	}
	if (m_Versatile)
	{
		std::cout << "m_Versatile, " << std::endl;
	}

	if (m_TwoHanded)
	{
		std::cout << "Two Handed, " << std::endl;
	}
	std::cout << std::endl;


	//display damage types
	std::cout << "Damage Types: " << std::endl << "\t";
	for (auto i = m_damageTypes.begin(); i != m_damageTypes.end(); i++)
	{
		if (i != m_damageTypes.begin())
		{
			std::cout << ", " << std::endl;
		}
		std::cout << DamageTypeTextMap[(*i)];
	}
	std::cout << std::endl;

	std::cout << "a_Weight: " << m_Weight << "lb." << std::endl;
	std::cout << "Range increment: " << m_RangeIncrement << std::endl;

	std::cout << "Criticals: " << GetCritInformation().first << "/a_x" << GetCritInformation().second << std::endl;
	
	std::cout << "End " << m_ObjectName << std::endl << std::endl;
	//end weaponfacts
}

const int ObjectClass::GetArmorBonus()
{
	return m_armorBonus;
}
void ObjectClass::SetArmorBonus(int a_bonus)
{
	m_armorBonus = a_bonus;
}

int ObjectClass::GetDamageReduction()
{
	return m_damageReduction;
}
void ObjectClass::SetDamageReduction(int a_reduction)
{
	m_damageReduction = a_reduction;
}

int ObjectClass::GetMaxDexBonus()
{
	return m_maxDexBonus;
}
void ObjectClass::SetMaxDex(int a_max)
{
	m_maxDexBonus = a_max;
}

int ObjectClass::GetArmorCheckPenalty()
{
	return m_armorCheckPenalty;
}
void ObjectClass::SetArmorCheckPen(int a_penalty)
{
	m_armorCheckPenalty = a_penalty;
}

int ObjectClass::GetSpeedReduction()
{
	return m_speedReduction;
}
void ObjectClass::SetSpeedReduction(int a_speedReduction)
{
	this->m_speedReduction = a_speedReduction;
}

int ObjectClass::GetEquipActions()
{
	return m_equipActions;
}
void ObjectClass::SetEquipActions(int a_actions)
{
	m_equipActions = a_actions;
}

bool ObjectClass::GetIsShield()
{
	return m_isShield;
}

void ObjectClass::SetIsShield(bool a_isShield)
{
	m_isShield = a_isShield;
}

std::vector<ArmorType> ObjectClass::GetArmorTypes()
{
	return this->m_armorTypes;
}

void ObjectClass::AddArmorType(ArmorType a_addType)
{
	m_armorTypes.push_back(a_addType);
}

void ObjectClass::DisplayArmorInfo()
{
		//start weapon facts

		std::cout << "Object Name: " << GetName() << std::endl;

		std::cout << "Armor a_bonus " << GetArmorBonus() << std::endl;
		std::cout << "m_damageReduction " << GetDamageReduction() << std::endl;
		std::cout << "Max Dex " << GetMaxDexBonus() << std::endl;
		std::cout << "ACP " << GetArmorCheckPenalty() << std::endl;

		std::cout << "Entering loop display armor" << std::endl;
		for (auto i = m_armorTypes.begin(); i != m_armorTypes.end(); i++)
		{
			std::cout << "Entered loop" << std::endl;
			//std::cout << ArmorTypeTextMap[(*i)] << std::endl;
		}

		std::cout << "a_Weight: " << GetBaseWeight() << "lb." << std::endl;
		if (GetIsShield())
		{
			std::cout << "This is a shield" << std::endl;
		}
		std::cout << "Max speed " << GetSpeedReduction() << std::endl << std::endl;

		//end Armor info
}