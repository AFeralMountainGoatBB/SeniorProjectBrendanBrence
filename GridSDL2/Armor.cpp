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

ArmorObject::ArmorObject( ArmorObject const &a_other)
{
	if (a_other.m_Box.x == NULL)
	{
		m_Box.x = 0;
	}
	else
	{
		m_Box.x = a_other.m_Box.x;
	}

	if (a_other.m_Box.y == NULL)
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

	//copy constructor, copy all units
	//	int tempint = a_other.m_armorBonus;
	SetName(const_cast<ArmorObject&>(a_other).GetName());
	SetArmorBonus(a_other.m_armorBonus);
	SetDamageReduction(a_other.m_damageReduction);
	SetMaxDex(a_other.m_maxDexBonus);
	SetArmorCheckPen(a_other.m_armorCheckPenalty);
	SetSpeedReduction(a_other.m_speedReduction);
	SetIsShield(a_other.m_isShield);
	SetBaseWeight(const_cast<ArmorObject&>(a_other).GetBaseWeight());
	SetPathTexture(a_other.m_PathTexture);
	this->m_Texture = a_other.m_Texture;
	for (auto i = a_other.m_armorTypes.begin(); i != a_other.m_armorTypes.end(); i++)
	{
		AddArmorType((*i));
	}
	
}

ArmorObject::ArmorObject(ObjectClass &a_other)
{
	
	//copy constructor, copy all units
	//	int tempint = a_other.m_armorBonus;
	SetName(a_other.GetName());
	//std::cout << "Armor a_bonus of 'a_other' " << a_other.GetArmorBonus() << "of "<< a_other.GetName() << std::endl;
	this->SetArmorBonus(a_other.GetArmorBonus());
	SetDamageReduction(a_other.GetDamageReduction());
	SetMaxDex(a_other.GetMaxDexBonus());
	SetArmorCheckPen(a_other.GetArmorCheckPenalty());
	SetSpeedReduction(a_other.GetSpeedReduction());
	SetIsShield(a_other.GetIsShield());
	SetBaseWeight(a_other.GetBaseWeight());
	//std::cout << "Made it to loop armor copy construct" << std::endl;
	m_armorTypes = a_other.GetArmorTypes();
	SetPathTexture(a_other.GetPathTexture());
	this->m_Texture = a_other.GetTexture();
	//DisplayArmorInfo();
}


const int ArmorObject::GetArmorBonus()
{
	return m_armorBonus;
}
void ArmorObject::SetArmorBonus(int a_bonus)
{
	m_armorBonus = a_bonus;
}

int ArmorObject::GetDamageReduction()
{
	return m_damageReduction;
}
void ArmorObject::SetDamageReduction(int a_reduction)
{
	m_damageReduction = a_reduction;
}

int ArmorObject::GetMaxDexBonus()
{
	return m_maxDexBonus;
}
void ArmorObject::SetMaxDex(int a_max) 
{
	m_maxDexBonus = a_max;
}

int ArmorObject::GetArmorCheckPenalty()
{
	return m_armorCheckPenalty;
}
void ArmorObject::SetArmorCheckPen(int a_penalty)
{
	m_armorCheckPenalty = a_penalty;
}

int ArmorObject::GetSpeedReduction()
{
	return m_speedReduction;
}
void ArmorObject::SetSpeedReduction(int a_speedReduction)
{
	this->m_speedReduction = a_speedReduction;
}

bool ArmorObject::GetIsShield()
{
	return m_isShield;
}

void ArmorObject::SetIsShield(bool a_isShield)
{
	m_isShield = a_isShield;
}

std::vector<ArmorType> ArmorObject::GetArmorTypes()
{
	return this->m_armorTypes;
}

void ArmorObject::AddArmorType(ArmorType a_addType)
{
	m_armorTypes.push_back(a_addType);
}

void ArmorObject::DisplayArmorInfo() 
{
	//start weapon facts

	std::cout << "Object Name: " << GetName() << std::endl;

	std::cout << "Armor a_bonus " << GetArmorBonus() << std::endl;
	std::cout << "m_damageReduction " << GetDamageReduction() << std::endl;
	std::cout << "Max Dex " << GetMaxDexBonus() << std::endl;
	std::cout << "ACP " << GetArmorCheckPenalty() << std::endl;
	
	for (int i = 0; i != GetArmorTypes().size(); i++)
	{
		std::cout << ArmorTypeTextMap[m_armorTypes[i]] << std::endl;
	}
	
	std::cout << "m_Weight: " << GetBaseWeight() << "lb." << std::endl;
	if(GetIsShield())
	{
		std::cout << "This is a shield" << std::endl;
	}
	std::cout << "Max speed " << GetSpeedReduction() << std::endl << std::endl;
	
	//end Armor info
}

void ArmorObject::SetTexture(std::map<std::string, LTexture*> a_TextureMap, std::string a_Path)
{
	if (a_TextureMap.count(a_Path + "\\" + m_PathTexture))
	{
		m_Texture = a_TextureMap[a_Path + "\\" + m_PathTexture];
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

void ArmorObject::SetLocation(int a_x, int a_y, std::vector<std::vector<Tile> > &a_TileMap)
{
	m_Location.first = a_x;
	m_Location.second = a_y;
	m_Box.x = m_Location.first;
	m_Box.y = m_Location.second;
	std::cout << m_Location.first << "," << m_Location.second << std::endl;
	SetRendLocation(a_TileMap);
	a_TileMap[a_x][a_y].AddItem(this);
}

void ArmorObject::SetRendLocation(std::vector<std::vector<Tile>> &a_TileVector)
{
	std::pair<int, int> tempLoc = CalcRendLocation(a_TileVector);
	m_Box.x = tempLoc.first;
	m_Box.y = tempLoc.second;
	std::cout << "New rend location for " << m_ObjectName << " = " << m_Box.x << " " << m_Box.y << std::endl;
}

std::pair<int, int> ArmorObject::CalcRendLocation(std::vector<std::vector<Tile>> &a_TileVector)
{
	//std::cout << "Calc rend location" << std::endl;
	std::pair <int, int> RetVal;
	int xTempLoc = m_Location.first;
	int yTempLoc = m_Location.second;

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


void ArmorObject::render(SDL_Rect& a_camera, SDL_Renderer *& a_Renderer)
{
	//If the texture is on screen
	if (checkCollision(a_camera, m_Box))
	{
		//Show the texture
		m_Texture->renderEntity(m_Box.x - a_camera.x, m_Box.y - a_camera.y, a_Renderer, &m_Box);
		//std::cout << " Entity size " << m_Box.h << " " << m_Box.w << std::endl;
	}
}
