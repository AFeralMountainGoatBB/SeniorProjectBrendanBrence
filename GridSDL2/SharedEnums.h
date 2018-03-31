#pragma once
#include <map>
#include <string>
/*
SIZE    AC  SP*	Hide	Actual size     general weight  occupies    Reach Tall/Long  Carrying Capacity Biped / other
_____________________________________________________________________________________
Tiny	+2	−8	+8		1 ft.–2 ft.		1 lb.–8 lb.		2-1/2 ft.	0 ft.	0 ft.		×1/2	×3/4
Small	+1	−8	+4		2 ft.–4 ft.		8 lb.–60 lb.	5 ft.		5 ft.	5 ft.		×3/4	×1
Medium	+0	+0	+0		4 ft.–8 ft.		60 lb.–500 lb.	5 ft.		5 ft.	5 ft.		×1		×1-1/2
Large	−1	+4	−4		8 ft.–16 ft.	500 lb.–2 tons	10 ft.		10 ft.	5 ft.		×2		×3
Hugeee	−2	+8	−8		16 ft.–32 ft.	2 tons–16 tons	15 ft.		15 ft.	10 ft.		×4		×6

*Special attack mod
*/

enum EntitySize {
	TINY, // rats and tiny creatures
	SMALL, //Children, some elves, fey, pups
	MEDIUM, // Adult Humans, wolves, small bears, deer
	LARGE, // horses, smaller giants, seige engines
	VERYLARGE, //big ol giants of legend, used to be 'HUGE'
	BUILDING //customsize for rocks, trees, 
};

enum DiceType {
	D100 = 100,
	D20 = 20,
	D12 = 12,
	D10 = 10,
	D8 = 8,
	D6 = 6,
	D4 = 4,
	D3 = 3
};

enum CreatureType {
	ANIMAL,
	HUMANOID,
	GIANT,
	FEY,
	UNDEAD,
	//more to be added, maybe turned into class
};

enum AbilityType {
	STR, //strength
	CON, //constitution
	DEX, //dexterity
	INT, //intelligence
	WIS, //wisdom
	CHA //charisma
};

enum DamageType
{
	BLUNT,
	PIERCE,
	SLASH,
	MAGIC,
	FIRE
	//will add more at some point probably
};

enum WeaponType
{
	POLEARM,
	AXE,
	SWORD,
	HAMMER,
	BOW,
	CROSSBOW,
	SIMPLE,
	MARTIAL,
	EXOTIC,
	NATURAL,
	UNARMED, 
	IMPROVISED
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
	TRADEGOOD
};

enum ArmorType
{
	LIGHTARMOR,
	MEDIUMARMOR,
	HEAVYARMOR,
	SHIELD,
	TOWERSHIELD
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
	ATTACKMODE,
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