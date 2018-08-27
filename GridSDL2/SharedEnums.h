#pragma once
#include <map>
#include <string>
#include <iostream>

enum DiceType {
	D100 = 100,
	D20 = 20,
	D12 = 12,
	D10 = 10,
	D8 = 8,
	D6 = 6,
	D4 = 4,
	D3 = 3,
	D2 = 2
};

enum AbilityScoreType {
	STR=1, //strength
	CON=3, //constitution
	DEX=2, //dexterity
	INT=4, //intelligence
	WIS=5, //wisdom
	CHA=6, //charisma
	UNKNOWNABILITYSCORETYPE=999
};

enum DamageType
{
	BLUNT,
	PIERCE,
	SLASH,
	MAGIC,
	FIRE,
	UNKNOWNDAMAGETYPE=999
	//will add more at some point probably
};

enum WeaponType
{
	POLEARM=0,
	AXE=1,
	SWORD=2,
	CLOSE=3,
	HAMMER=4,
	MACE=5,
	BOW=6,
	CROSSBOW=7,
	THROWN=8,
	NATURAL=9,
	UNARMED=10, 

	SIMPLE,
	MARTIAL,
	IMPROVISED,
	EXOTIC,
	LIGHT,
	AMMO,
	RANGED,
	MELEE,
	UNKNOWNWEAPONTYPE=999
};

//starts at 0, ends at UNKNOWN
enum CircumstanceType
{
	DUALWIELDING, //weapon in each hand type of attack
	TWOHANDING, //both hands on the weapon attack
	POINTBLANK, //within 30 ft
	MELEEATTACK, // melee attack
	RANGEDATTACK, // ranged attack
	OPPORTUNITYATTACK, //opportunity attack
	TARGETHASCOVER,
	UNKNOWNCIRCUMSTANCE=999
};

enum AttackRollType
{
	NORMAL,
	CRITICAL,
	DISARM,
	TRIP,
	FULL, 
	SHIELDBASH,
	UNKNOWNATTACKTYPE=999
};

enum BodyLocation {
	HEAD=1, //helmet, headbands, phylactery, hats
	FACE, //masks, eyewear
	TORSO, //shirts
	BACK, //capes
	THROAT, //necklaces / prepiats
	ARM, //bracers, bracelets
	HAND, //gloves, gauntlets
	RING, //magic rings, yo
	BODY, //armor
	WAIST, //belts / girdles
	LEGS, //magic boots
	MAINHAND, //primary weapons or 2 hander
	OFFHAND, //secondary weapons or 2 hander
	TRADEGOOD, //unused as of now
	UNKNOWNBODYSLOTTYPE=999
};

enum ArmorType
{
	UNARMORED = 0,
	LIGHTARMOR = 1,
	MEDIUMARMOR = 2,
	HEAVYARMOR = 3,
	SHIELD = 4,
	TOWERSHIELD = 5,
	UNKNOWNARMORTYPE=999
};

enum Direction
{
	NORTH,
	NORTHEAST,
	EAST,
	SOUTHEAST,
	SOUTH,
	SOUTHWEST,
	WEST,
	NORTHWEST, 
	STATIONARY
};

enum ControlMode
{
	MOVEMODE, 
	PICKUPMODE,
	INVENTORYMODE,
	FEATOPTIONMODE,
	MELEEATTACKMODE,
	RANGEDATTACKMODE,
	AIMODE,
	SELECTTARGETMODE,
	NOCONTROLMODE
};

#ifndef BODY_LOCATION_TEXT_MAP
#define BODY_LOCATION_TEXT_MAP

static std::map <BodyLocation, std::string> BodyLocationTextMap = {
	{HEAD, "Head"}, //helmet, headbands, phylactery, hats
	{FACE, "Face"}, //masks, eyewear
	{TORSO, "Torso"}, //shirts
	{BACK, "Back" }, //capes
	{THROAT, "Throat"}, //necklaces / prepiats
	{ARM, "Arms"}, //bracers, bracelets
	{HAND, "Hands"},//gloves, gauntlets
	{RING, "Ring"}, //magic rings, yo
	{BODY, "Body"}, //armor
	{WAIST, "Waist"},//belts / girdles
	{LEGS, "Legs"}, //magic boots
	{MAINHAND, "MainHand"}, //primary weapons or 2 hander
	{OFFHAND, "Offhand"},//secondary weapons or 2 hander
	{TRADEGOOD, "TradeGood"}
};
#endif // !BODY_LOCATION_TEXT_MAP

#ifndef ABILITY_SCORE_TEXT_MAP
#define ABILITY_SCORE_TEXT_MAP
static std::map<AbilityScoreType, std::string> AbilityScoreTextMap =
{
	{STR, "Strength"},
	{DEX, "Dexterity"},
	{CON, "Constitution"},
	{INT, "Intelligence"},
	{WIS, "Wisdom"},
	{CHA, "Charisma"}
};

#endif

#ifndef DAMAGE_TYPE_TEXT_MAP
#define DAMAGE_TYPE_TEXT_MAP
static std::map<DamageType, std::string> DamageTypeTextMap =
{
	{ PIERCE, "Pierce" },
	{ BLUNT, "Blunt" },
	{ SLASH, "Slash" },
	{ MAGIC, "Magic" },
	{ FIRE, "Fire" }
};
#endif

static std::map<CircumstanceType, std::string> CircumstanceTypeTextMap =
{
	{DUALWIELDING, "DualWielding"},
	{TWOHANDING, "TwoHanding" },
	{POINTBLANK, "PointBlank"},
	{MELEEATTACK, "Melee" },
	{RANGEDATTACK, "Ranged"},
	{OPPORTUNITYATTACK, "Opportunity"},
	{UNKNOWNCIRCUMSTANCE , "Unknown"}

};

#ifndef WEAPON_TYPE_TEXT_MAP
#define WEAPON_TYPE_TEXT_MAP
static std::map<WeaponType, std::string> WeaponTypeTextMap =
{
	{POLEARM, "Polearm" }, //spears, other things
	{AXE, "Axe"}, //axes from 2h axes to smaller axes, etc
	{SWORD,"Sword"}, //shortswords, rapiers, longswords, greatswords
	{CLOSE,"Close"}, //daggers, short weapons meant to fight close in, shield bash, etc most light weapons
	{HAMMER,"Hammer"}, //hammers and picks
	{MACE, "Mace"}, //maces and clubs, weapons of mass bludgening damage
	{BOW, "Bow"}, //shortbows, longbows, composite bows
	{CROSSBOW, "Crossbow"}, //light, heavy, hand
	{THROWN, "Thrown"}, //throwing weapons
	{NATURAL,"Natural"}, //claws and such
	{UNARMED,"Unarmed"}, //fists, gauntets, cestus, brass knuckles
	//unarmed is 10, the 11th entry here

	{SIMPLE, "Simple"},
	{MARTIAL, "Martial"},
	{EXOTIC, "Exotic"},

	{IMPROVISED,"Improvised"},
	{LIGHT, "Light"},
	{AMMO, "Ammo"},
	{RANGED, "Ranged"},
	{MELEE, "Melee" },
	{UNKNOWNWEAPONTYPE, "Unknown"}
};

#endif

static std::map<ArmorType, std::string> ArmorTypeTextMap =
{
	{LIGHTARMOR, "Light Armor"},
	{MEDIUMARMOR, "Medium Armor"},
	{HEAVYARMOR, "Heavy Armor"},
	{SHIELD, "Normal Shield"},
	{TOWERSHIELD, "Tower Shield"}
};


static WeaponType FindWeaponType(std::string line)
{
	for (auto i = WeaponTypeTextMap.begin(); i != WeaponTypeTextMap.end(); i++)
	{
		if (line.find((*i).second) != std::string::npos)
		{
			//	std::cout << "Weapon type found:" << (*i).second << std::endl;
			return (*i).first;
		}
	}
	return UNKNOWNWEAPONTYPE;
}

static DamageType FindDamageType(std::string line)
{
	for (auto i = DamageTypeTextMap.begin(); i != DamageTypeTextMap.end(); i++)
	{
		if (line.find((*i).second) != std::string::npos)
		{
			//	std::cout << "Damage type found:" << (*i).second << std::endl;
			return (*i).first;
		}
	}
	return UNKNOWNDAMAGETYPE;
}

static ArmorType FindArmorType(std::string line)
{
	for (auto i = ArmorTypeTextMap.begin(); i != ArmorTypeTextMap.end(); i++)
	{
		if (line.find((*i).second) != std::string::npos)
		{
		return (*i).first;
		}
	}
	return UNKNOWNARMORTYPE;
}

static CircumstanceType FindCircumstanceType(std::string line)
{
	for (auto i = CircumstanceTypeTextMap.begin(); i != CircumstanceTypeTextMap.end(); i++)
	{
		if (line.find((*i).second) != std::string::npos)
		{
			return (*i).first;
		}
	}
	return UNKNOWNCIRCUMSTANCE;
}

static AbilityScoreType FindAbilityScoreType(std::string line)
{
	for (auto i = AbilityScoreTextMap.begin(); i != AbilityScoreTextMap.end(); i++)
	{
		if (line.find((*i).second) != std::string::npos)
		{
			return (*i).first;
		}
	}
	return UNKNOWNABILITYSCORETYPE;
}
