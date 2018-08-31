#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"

class FeatClass
{
public:
	void DisplayFeatFullInfo();

	std::string GetName();
	void SetName(std::string SetName);

	std::string GetDescription() { return m_description;  }
	void SetDescription(std::string Description) { m_description = Description; }

	bool GetAddsAbility();
	void SetAddAbility(bool SetAddsAbility);

	void AddWeaponProficiency(WeaponType addWeapon) { m_WeaponProficencyAdd.push_back(addWeapon); }
	std::vector<WeaponType>&GetWeaponProficiencies() { return m_WeaponProficencyAdd; }

	void AddArmorProficiency(ArmorType addArmor) { m_ArmorProficiencyAdd.push_back(addArmor); }
	std::vector<ArmorType>&GetArmorProficiencies() { return m_ArmorProficiencyAdd; }

	std::map<WeaponType, int>& GetWeaponAttackBonuses() { return m_WeaponAttackBonusAdd; }
	void AddWeaponAttackBonusAdd(WeaponType Wtype, int amount) { m_WeaponAttackBonusAdd[Wtype] = amount; }
	std::map<WeaponType, int>& GetWeaponDamageBonuses() { return m_WeaponDamageBonusAdd; }
	void AddWeaponDamageBonusAdd(WeaponType Wtype, int amount) { m_WeaponDamageBonusAdd[Wtype] = amount; }

	std::map<WeaponType, int>& GetWeaponAttackBonusSubtract() { return m_WeaponAttackBonusSubtract; }
	void AddWeaponAttackBonusSubtract(WeaponType Wtype, int amount) { m_WeaponAttackBonusSubtract[Wtype] = amount; }
	std::map<WeaponType, int>& GetWeaponDamageBonusSubtract() { return m_WeaponDamageBonusSubtract; }
	void AddWeaponDamageBonusSubtract(WeaponType Wtype, int amount) { m_WeaponDamageBonusAdd[Wtype] = amount; }

	//std::map<ArmorType, int>& GetArmorBonuses() { return m_ArmorBonusAdd; }

	std::vector<FeatClass*>&GetGeneralPreRequisites() { return m_GeneralPrereqs; }

	bool GetUsesRangeAbility() { return m_UsesRangeValueAbility; }
	void SetUsesRangeAbility(bool passed) { m_UsesRangeValueAbility = passed; }

	std::pair<int, int> GetActivatedRange() { return m_RangeActivated; }
	void SetRangeActivated(int lower, int upper) { m_RangeActivated.first = lower; m_RangeActivated.second = upper; }

	std::map<CircumstanceType, int>&GetCircumstanceAttackBonusAdd() { return m_CircumstanceAttackBonusAdd; }
	void AddCircumstanceAttackBonusAdd(CircumstanceType CType, int amount) { m_CircumstanceAttackBonusAdd[CType] = amount; }

	std::map<CircumstanceType, int>&GetCircumstanceAttackBonusSubtract() { return m_CircumstanceAttackBonusSubtract; }
	void AddCircumstanceAttackBonusSubtract(CircumstanceType CType, int amount) { m_CircumstanceAttackBonusSubtract[CType] = amount; }

	std::map<CircumstanceType, int>&GetCircumstanceAttackDamageAdd() { return m_CircumstanceAttackDamageAdd; }
	void AddCircumstanceAttackDamageAdd(CircumstanceType CType, int amount) { m_CircumstanceAttackDamageAdd[CType] = amount; }

	std::map<CircumstanceType, int>&GetCircumstanceAttackDamageSubtract() { return m_CircumstanceAttackDamageSubtract; }
	void AddCircumstanceAttackDamageSubtract(CircumstanceType CType, int amount) { m_CircumstanceAttackDamageSubtract[CType] = amount; }

	std::map<CircumstanceType, int>&GetCircumstanceArmorBonusAdd() { return m_CircumstanceArmorBonusAdd; }
	void AddCircumstanceArmorBonusAdd(CircumstanceType CType, int amount) { m_CircumstanceArmorBonusAdd[CType] = amount; }

	std::map<CircumstanceType, int>&GetCircumstanceArmorBonusSubtract() { return m_CircumstanceArmorBonusSubtract; }
	void AddCircumstanceArmorBonusSubtract(CircumstanceType CType, int amount) { m_CircumstanceArmorBonusSubtract[CType] = amount; }

	void AddSaveBonus(AbilityScoreType AbType, int amount) { m_SaveBonusAdd.push_back(std::pair<AbilityScoreType, int>( AbType, amount)); }

	void AddArmorMoveSpeedBonusAdd(ArmorType Armor, int bonus) { m_MoveSpeedBonusAdd[Armor] = bonus; }

	void AddCircumstanceRequired(CircumstanceType CType) { m_CircumstancesRequired.push_back(CType); }
	std::vector<CircumstanceType>& GetCircumstancesRequired() { return m_CircumstancesRequired; }

	bool IsActive() { return m_AbilityCurrentlyActive; }
	void SwitchActive() { m_AbilityCurrentlyActive = !m_AbilityCurrentlyActive; }

	bool IsToggleAbility() { return m_ToggleAbility; }
	void SetToggleAbility(bool passed) { m_ToggleAbility = passed; }

	int GetCurrentRangeValue() { return m_CurrentRangeValue; }

	void IncreaseFeat();
	void DecreaseFeat();

	int GetDodgeBonusAdd() { return m_DodgeBonusAdd; }
	int GetDodgeBonusSubtract() { return m_DodgeBonusSubtract; }
private:
	std::string m_FeatName = "";
	std::string m_description = "";
	
	std::vector<WeaponType> m_WeaponProficencyAdd;
	std::vector<ArmorType> m_ArmorProficiencyAdd;

	std::map<WeaponType, int> m_WeaponAttackBonusAdd;
	std::map<WeaponType, int> m_WeaponAttackBonusSubtract;

	std::map<WeaponType, int> m_WeaponDamageBonusAdd;
	std::map<WeaponType, int> m_WeaponDamageBonusSubtract;
	
	std::map<CircumstanceType, int>m_CircumstanceAttackBonusAdd;	
	std::map<CircumstanceType, int>m_CircumstanceAttackBonusSubtract;

	std::map<CircumstanceType, int>m_CircumstanceAttackDamageAdd;
	std::map<CircumstanceType, int>m_CircumstanceAttackDamageSubtract;

	std::map<CircumstanceType, int>m_CircumstanceArmorBonusAdd;
	std::map<CircumstanceType, int>m_CircumstanceArmorBonusSubtract;

	std::map<ArmorType, int> m_ArmorBonusAdd;
	std::map<ArmorType, int> m_ArmorBonusSubtract;

	std::map<ArmorType, int> m_MoveSpeedBonusAdd;
	std::map<ArmorType, int> m_MoveSpeedBonusSubtract;
	
	int m_BaseAttackBonusAdd = 0;
	int m_DodgeBonusAdd = -1;
	int m_DodgeBonusSubtract = -1;

	std::vector<std::pair<AbilityScoreType, int>> m_AbilityScoreBonuses;
	std::vector <std::pair<AbilityScoreType, int>> m_SaveBonusAdd;

	std::vector<FeatClass*> m_GeneralPrereqs;
	std::vector<std::pair<FeatClass*, WeaponType>> m_WeaponPrereqs;
	std::vector<std::pair<FeatClass*, ArmorType>> m_ArmorPrereqs;
	std::vector<CircumstanceType> m_CircumstancesRequired;
	std::pair<AbilityScoreType, int> m_RequiredAbilityScores;

	bool m_AbilityCurrentlyActive = true;
	bool m_ToggleAbility = false;
	bool m_UsesRangeValueAbility = false;
	std::pair<int, int> m_RangeActivated = { 0,0 };
	int m_CurrentRangeValue = 0;

	int m_InitiativeBonus = 0;
	int m_EquipActionsReduction = 0;
	int RequiredBAB = 0;
	
	//loading functions
public:
	bool LoadFeatByName(std::string line);
	bool LoadFeat();

};