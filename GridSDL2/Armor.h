#pragma once
#include "SharedEnums.h"
#include "GeneralHeaders.h"
#include "Objects.h"

class ArmorObject : public ObjectClass
{
public:
	ArmorObject();
	ArmorObject(const ArmorObject &Other);
	ArmorObject( ObjectClass const &Other);


	const int GetArmorBonus();
	void SetArmorBonus(int bonus);

	int GetDamageReduction();
	void SetDamageReduction(int reduction);

	int GetMaxDexBonus();
	void SetMaxDex(int max);

	int GetArmorCheckPenalty();
	void SetArmorCheckPen(int penalty);

	int GetSpeedReduction();
	void SetSpeedReduction(int SpeedReduction);

	int GetEquipActions();
	void SetEquipActions(int actions);

	bool GetIsShield();
	void SetIsShield(bool isShield);

	std::vector<ArmorType>& GetArmorTypes();
	void AddArmorType(ArmorType added);

	void DisplayArmorInfo();

private:
	int ArmorBonus=0;
	int DamageReduction=0;
	int MaxDexBonus=0;
	int ArmorCheckPenalty=0;
	int SpeedReduction=0;
	int EquipActions=0;
	bool IsShield = false;

	//not loaded into master list
	std::vector<Modifier> Modifiers = {};
	std::vector<ArmorType> ArmorTypes = {};

	//inherited values
	SDL_Rect mBox = { 0,0,70,70 };
	std::string mPathTexture = "Armor1.png";
	LTexture* mTexture;
	std::pair<int, int> mLocation = { 0,0 };

	//The dimensions of the Entity
	int OBJECT_WIDTH = 70;
	int OBJECT_HEIGHT = 70;

	//Model information
	std::string ObjectName = "";
	std::string ObjectDescription = "";
	std::vector<WeaponType> WeaponTypes = { IMPROVISED }; //types of weapon this is, default improvised
	std::vector<DamageType> DamageTypes = {BLUNT};

	std::pair<int, DiceType> DamageDice = { 1, D3 };
	float Weight = 0.0; //how much does the item weigh? Unimportant save for carrying capacity and determining 2h for improvised weapons

	bool TwoHanded; //does it have to take up both hand slots?
	bool Versatile; //can it be weilded in 2 hands? (example, longsword)

	int RangeIncrement = 0;
	BodyLocation BodySlot = BODY; //indicates where this weapon can be used (manhand and offhand are interchangable)

	int CritMultiplier = 2;
	int CritThreat = 20;

};