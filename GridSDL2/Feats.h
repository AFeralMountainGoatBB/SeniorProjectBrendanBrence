#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"

class FeatClass
{
public:
	std::string GetName();
	void SetName(std::string SetName);

	std::string GetDescription();
	void SetDescription(std::string Description);

	bool GetAddsAbility();
	void SetAddAbility(bool SetAddsAbility);

	void AddWeaponProficiency(WeaponType);

	



private:
	std::string FeatName = "";
	std::string description = "";
	bool AddsAbility = false;
	std::vector<WeaponType> WeaponProficiencyAdd;
	std::vector<ArmorType> ArmorProficiencyAdd;
	std::map<WeaponType, int> WeaponBonusAdd;
	std::map<ArmorType, int> ArmorBonusAdd;
	//int BonusAmount;
};