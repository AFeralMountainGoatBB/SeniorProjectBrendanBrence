#include "Armor.h"

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

	for (auto i = other.ArmorTypes.begin(); i != other.ArmorTypes.end(); i++)
	{
		AddArmorType((*i));
	}
}


ArmorObject::ArmorObject(ObjectClass const &other)
{
	//copy constructor, copy all units
	//	int tempint = other.ArmorBonus;
//	other.GetName();
	SetName(static_cast<ObjectClass>(other).GetName());
	SetArmorBonus(static_cast<ObjectClass>(other).GetArmorBonus());
	SetDamageReduction(static_cast<ObjectClass>(other).GetDamageReduction());
	SetMaxDex(static_cast<ObjectClass>(other).GetMaxDexBonus());
	SetArmorCheckPen(static_cast<ObjectClass>(other).GetArmorCheckPenalty());
	SetSpeedReduction(static_cast<ObjectClass>(other).GetSpeedReduction());
	SetIsShield(static_cast<ObjectClass>(other).GetIsShield());
	SetBaseWeight(static_cast<ObjectClass>(other).GetBaseWeight());

	for (auto i = static_cast<ObjectClass>(other).GetArmorTypes().begin(); i != static_cast<ObjectClass>(other).GetArmorTypes().end(); i++)
	{
		AddArmorType((*i));
	}
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

std::vector<ArmorType>& ArmorObject::GetArmorTypes()
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
	
	for (auto i = GetArmorTypes().begin(); i != GetArmorTypes().end(); i++)
	{
		std::cout << ArmorTypeTextMap[(*i)] << std::endl;
	}
	
	std::cout << "Weight: " << GetBaseWeight() << "lb." << std::endl;
	if(GetIsShield())
	{
		std::cout << "This is a shield" << std::endl;
	}
	std::cout << "Max speed " << GetSpeedReduction() << std::endl << std::endl;
	
	//end Armor info
}