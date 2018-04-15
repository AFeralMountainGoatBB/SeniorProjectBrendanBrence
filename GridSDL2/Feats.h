#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"

class FeatClass
{
public:
	void DisplayFeatFullInfo();

	std::string GetName();
	void SetName(std::string SetName);

	std::string GetDescription() { return description;  }
	void SetDescription(std::string Description) { description = Description; }

	bool GetAddsAbility();
	void SetAddAbility(bool SetAddsAbility);

	void AddWeaponProficiency(WeaponType addWeapon) { WeaponProficencyAdd.push_back(addWeapon); }
	std::vector<WeaponType>&GetWeaponProficiencies() { return WeaponProficencyAdd; }

	void AddArmorProficiency(ArmorType addArmor) { ArmorProficiencyAdd.push_back(addArmor); }
	std::vector<ArmorType>&GetArmorProficiencies() { return ArmorProficiencyAdd; }


	std::map<WeaponType, int>& GetWeaponAttackBonuses() { return WeaponAttackBonusAdd; }
	void AddWeaponAttackBonusAdd(WeaponType Wtype, int amount) { WeaponAttackBonusAdd[Wtype] = amount; }
	std::map<WeaponType, int>& GetWeaponDamageBonuses() { return WeaponDamageBonusAdd; }
	void AddWeaponDamageBonusAdd(WeaponType Wtype, int amount) { WeaponDamageBonusAdd[Wtype] = amount; }

	std::map<WeaponType, int>& GetWeaponAttackBonusSubtract() { return WeaponAttackBonusSubtract; }
	void AddWeaponAttackBonusSubtract(WeaponType Wtype, int amount) { WeaponAttackBonusAdd[Wtype] = amount; }
	std::map<WeaponType, int>& GetWeaponDamageBonusSubtract() { return WeaponDamageBonusSubtract; }
	void AddWeaponDamageBonusSubtract(WeaponType Wtype, int amount) { WeaponDamageBonusAdd[Wtype] = amount; }

	//std::map<ArmorType, int>& GetArmorBonuses() { return ArmorBonusAdd; }

	std::vector<FeatClass*>&GetGeneralPreRequisites() { return GeneralPrereqs; }

	void ToggleAbility();

	bool GetUsesRangeAbility() { return UsesRangeAbility; }
	void SetUsesRangeAbility(bool passed) { UsesRangeAbility = passed; }

	std::pair<int, int> GetActivatedRange() { return RangeActivated; }
	void SetRangeActivated(int lower, int upper) { RangeActivated.first = lower; RangeActivated.second = upper; }

	std::map<CircumstanceType, int>&GetCircumstanceAttackBonusAdd() { return CircumstanceAttackBonusAdd; }
	void AddCircumstanceAttackBonusAdd(CircumstanceType CType, int amount) { CircumstanceAttackBonusAdd[CType] = amount; }

	std::map<CircumstanceType, int>&GetCircumstanceAttackBonusSubtract() { return CircumstanceAttackBonusSubtract; }
	void AddCircumstanceAttackBonusSubtract(CircumstanceType CType, int amount) { CircumstanceAttackBonusSubtract[CType] = amount; }

	std::map<CircumstanceType, int>&GetCircumstanceAttackDamageAdd() { return CircumstanceAttackDamageAdd; }
	void AddCircumstanceAttackDamageAdd(CircumstanceType CType, int amount) { CircumstanceAttackDamageAdd[CType] = amount; }

	std::map<CircumstanceType, int>&GetCircumstanceAttackDamageSubtract() { return CircumstanceAttackDamageSubtract; }
	void AddCircumstanceAttackDamageSubtract(CircumstanceType CType, int amount) { CircumstanceAttackDamageSubtract[CType] = amount; }

	std::map<CircumstanceType, int>&GetCircumstanceArmorBonusAdd() { return CircumstanceArmorBonusAdd; }
	void AddCircumstanceArmorBonusAdd(CircumstanceType CType, int amount) { CircumstanceArmorBonusAdd[CType] = amount; }

	std::map<CircumstanceType, int>&GetCircumstanceArmorBonusSubtract() { return CircumstanceArmorBonusSubtract; }
	void AddCircumstanceArmorBonusSubtract(CircumstanceType CType, int amount) { CircumstanceArmorBonusSubtract[CType] = amount; }


private:
	std::string FeatName = "";
	std::string description = "";
	
	std::vector<WeaponType> WeaponProficencyAdd;
	std::vector<ArmorType> ArmorProficiencyAdd;

	std::map<WeaponType, int> WeaponAttackBonusAdd;
	std::map<WeaponType, int> WeaponAttackBonusSubtract;

	std::map<WeaponType, int> WeaponDamageBonusAdd;
	std::map<WeaponType, int> WeaponDamageBonusSubtract;
	
	std::map<CircumstanceType, int>CircumstanceAttackBonusAdd;	
	std::map<CircumstanceType, int>CircumstanceAttackBonusSubtract;

	std::map<CircumstanceType, int>CircumstanceAttackDamageAdd;
	std::map<CircumstanceType, int>CircumstanceAttackDamageSubtract;

	std::map<CircumstanceType, int>CircumstanceArmorBonusAdd;
	std::map<CircumstanceType, int>CircumstanceArmorBonusSubtract;

	int BaseAttackBonusAdd = 0;
	int DodgeBonusAdd = -1;
	int DodgeBonusSubtract = -1;

	std::vector<FeatClass*> GeneralPrereqs;
	std::vector<std::pair<FeatClass*, WeaponType>> WeaponPrereqs;
	std::vector<std::pair<FeatClass*, ArmorType>> ArmorPrereqs;
	std::vector<CircumstanceType> CircumstanceRequired;
	std::pair<AbilityType, int> RequiredAbilityScores;

	bool AbilityActive = true;
	bool ActivatedAbility = false;
	bool UsesRangeAbility = false;
	std::pair<int, int> RangeActivated = { 0,0 };

	int InitiativeBonus = 0;
	int EquipActionsReduction = 0;
	int RequiredBAB = 0;
	
	//loading functions
public:
	bool LoadFeatByName(std::string line);
	bool LoadFeat();

};