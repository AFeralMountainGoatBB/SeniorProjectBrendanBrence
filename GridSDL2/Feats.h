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
	void AddWeaponAttackBonusSubtract(WeaponType Wtype, int amount) { WeaponAttackBonusSubtract[Wtype] = amount; }
	std::map<WeaponType, int>& GetWeaponDamageBonusSubtract() { return WeaponDamageBonusSubtract; }
	void AddWeaponDamageBonusSubtract(WeaponType Wtype, int amount) { WeaponDamageBonusAdd[Wtype] = amount; }

	//std::map<ArmorType, int>& GetArmorBonuses() { return ArmorBonusAdd; }

	std::vector<FeatClass*>&GetGeneralPreRequisites() { return GeneralPrereqs; }

	bool GetUsesRangeAbility() { return UsesRangeValueAbility; }
	void SetUsesRangeAbility(bool passed) { UsesRangeValueAbility = passed; }

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

	void AddSaveBonus(AbilityScoreType AbType, int amount) { SaveBonusAdd.push_back(std::pair<AbilityScoreType, int>( AbType, amount)); }

	void AddArmorMoveSpeedBonusAdd(ArmorType Armor, int bonus) { MoveSpeedBonusAdd[Armor] = bonus; }

	void AddCircumstanceRequired(CircumstanceType CType) { CircumstancesRequired.push_back(CType); }
	std::vector<CircumstanceType>& GetCircumstancesRequired() { return CircumstancesRequired; }

	bool IsActive() { return AbilityCurrentlyActive; }
	void SwitchActive() { AbilityCurrentlyActive = !AbilityCurrentlyActive; }

	bool IsToggleAbility() { return ToggleAbility; }
	void SetToggleAbility(bool passed) { ToggleAbility = passed; }

	int GetCurrentRangeValue() { return CurrentRangeValue; }

	void IncreaseFeat();
	void DecreaseFeat();

	int GetDodgeBonusAdd() { return DodgeBonusAdd; }
	int GetDodgeBonusSubtract() { return DodgeBonusSubtract; }
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

	std::map<ArmorType, int> ArmorBonusAdd;
	std::map<ArmorType, int> ArmorBonusSubtract;

	std::map<ArmorType, int> MoveSpeedBonusAdd;
	std::map<ArmorType, int> MoveSpeedBonusSubtract;
	
	int BaseAttackBonusAdd = 0;
	int DodgeBonusAdd = -1;
	int DodgeBonusSubtract = -1;

	std::vector<std::pair<AbilityScoreType, int>> AbilityScoreBonuses;
	std::vector <std::pair<AbilityScoreType, int>> SaveBonusAdd;

	std::vector<FeatClass*> GeneralPrereqs;
	std::vector<std::pair<FeatClass*, WeaponType>> WeaponPrereqs;
	std::vector<std::pair<FeatClass*, ArmorType>> ArmorPrereqs;
	std::vector<CircumstanceType> CircumstancesRequired;
	std::pair<AbilityScoreType, int> RequiredAbilityScores;

	bool AbilityCurrentlyActive = true;
	bool ToggleAbility = false;
	bool UsesRangeValueAbility = false;
	std::pair<int, int> RangeActivated = { 0,0 };
	int CurrentRangeValue = 0;

	int InitiativeBonus = 0;
	int EquipActionsReduction = 0;
	int RequiredBAB = 0;
	
	//loading functions
public:
	bool LoadFeatByName(std::string line);
	bool LoadFeat();

};