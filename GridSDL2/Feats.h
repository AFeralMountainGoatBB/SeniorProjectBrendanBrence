/**********************************************************************************************//**
 * @file	Feats.h.
 *
 * @brief	Declares the feats class
 **************************************************************************************************/

#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"

/**********************************************************************************************//**
 * @class	FeatClass
 *
 * @brief	A feat class, for storing information about individual feats
 *
 * @author	Brendan B
 * @date	9/1/2018
 **************************************************************************************************/

class FeatClass
{
public:

	/**********************************************************************************************//**
	 * @fn	void FeatClass::DisplayFeatFullInfo();
	 *
	 * @brief	Displays  full information to console
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/

	void DisplayFeatFullInfo();

	/**********************************************************************************************//**
	 * @fn	std::string FeatClass::GetName();
	 *
	 * @brief	Gets the name of the feat
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The name of the feat
	 **************************************************************************************************/

	std::string GetName();

	/**********************************************************************************************//**
	 * @fn	void FeatClass::SetName(std::string SetName);
	 *
	 * @brief	Sets a name for the feat
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	SetName	Name of the set
	 **************************************************************************************************/

	void SetName(std::string SetName);

	/**********************************************************************************************//**
	 * @fn	std::string FeatClass::GetDescription()
	 *
	 * @brief	Gets the description of the feat
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The description of the feat
	 **************************************************************************************************/

	std::string GetDescription() { return m_description;  }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::SetDescription(std::string Description)
	 *
	 * @brief	Sets a description
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	Description	The description.
	 **************************************************************************************************/

	void SetDescription(std::string Description) { m_description = Description; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::AddWeaponProficiency(WeaponType addWeapon)
	 *
	 * @brief	Adds a weapon proficiency to the feat
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	addWeapon	The weapontype to add
	 **************************************************************************************************/

	void AddWeaponProficiency(WeaponType addWeapon) { m_WeaponProficencyAdd.push_back(addWeapon); }

	/**********************************************************************************************//**
	 * @fn	std::vector<WeaponType>&GetWeaponProficiencies()
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @tparam	WeaponType	the weapontypes the feat adds proficiency for
	 **************************************************************************************************/

	std::vector<WeaponType>&GetWeaponProficiencies() { return m_WeaponProficencyAdd; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::AddArmorProficiency(ArmorType addArmor)
	 *
	 * @brief	Adds an armor proficiency
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	addArmor	The armortype to add
	 **************************************************************************************************/

	void AddArmorProficiency(ArmorType addArmor) { m_ArmorProficiencyAdd.push_back(addArmor); }

	/**********************************************************************************************//**
	 * @fn	std::vector<ArmorType>&GetArmorProficiencies()
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @tparam	ArmorType	Types of armor
	 **************************************************************************************************/

	std::vector<ArmorType>&GetArmorProficiencies() { return m_ArmorProficiencyAdd; }

	/**********************************************************************************************//**
	 * @fn	std::map<WeaponType, int>& FeatClass::GetWeaponAttackBonuses()
	 *
	 * @brief	Gets weapon attack bonuses
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The weapon attack bonuses.
	 **************************************************************************************************/

	std::map<WeaponType, int>& GetWeaponAttackBonuses() { return m_WeaponAttackBonusAdd; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::AddWeaponAttackBonusAdd(WeaponType Wtype, int amount)
	 *
	 * @brief	Adds a weapon attack bonus
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	Wtype 	The weapontype of the bonus.
	 * @param	amount	The amount.
	 **************************************************************************************************/

	void AddWeaponAttackBonusAdd(WeaponType Wtype, int amount) { m_WeaponAttackBonusAdd[Wtype] = amount; }

	/**********************************************************************************************//**
	 * @fn	std::map<WeaponType, int>& FeatClass::GetWeaponDamageBonuses()
	 *
	 * @brief	Gets weapon damage bonuses
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The weapon damage bonuses.
	 **************************************************************************************************/

	std::map<WeaponType, int>& GetWeaponDamageBonuses() { return m_WeaponDamageBonusAdd; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::AddWeaponDamageBonusAdd(WeaponType Wtype, int amount)
	 *
	 * @brief	Adds a weapon damage bonus
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	Wtype 	The weapon type.
	 * @param	amount	The amount.
	 **************************************************************************************************/

	void AddWeaponDamageBonusAdd(WeaponType Wtype, int amount) { m_WeaponDamageBonusAdd[Wtype] = amount; }

	/**********************************************************************************************//**
	 * @fn	std::map<WeaponType, int>& FeatClass::GetWeaponAttackBonusSubtract()
	 *
	 * @brief	Gets weapon attack bonus subtract
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The weapon attack bonus subtract
	 **************************************************************************************************/

	std::map<WeaponType, int>& GetWeaponAttackBonusSubtract() { return m_WeaponAttackBonusSubtract; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::AddWeaponAttackBonusSubtract(WeaponType Wtype, int amount)
	 *
	 * @brief	Adds a weapon attack bonus subtract
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	Wtype 	The weapon type.
	 * @param	amount	The amount.
	 **************************************************************************************************/

	void AddWeaponAttackBonusSubtract(WeaponType Wtype, int amount) { m_WeaponAttackBonusSubtract[Wtype] = amount; }

	/**********************************************************************************************//**
	 * @fn	std::map<WeaponType, int>& FeatClass::GetWeaponDamageBonusSubtract()
	 *
	 * @brief	Gets weapon damage bonus subtract
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The weapon damage bonus subtract.
	 **************************************************************************************************/

	std::map<WeaponType, int>& GetWeaponDamageBonusSubtract() { return m_WeaponDamageBonusSubtract; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::AddWeaponDamageBonusSubtract(WeaponType Wtype, int amount)
	 *
	 * @brief	Adds a weapon damage bonus subtract
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	Wtype 	The weapon type.
	 * @param	amount	The amount.
	 **************************************************************************************************/

	void AddWeaponDamageBonusSubtract(WeaponType Wtype, int amount) { m_WeaponDamageBonusAdd[Wtype] = amount; }


	/**********************************************************************************************//**
	 * @fn	bool FeatClass::GetUsesRangeAbility()
	 *
	 * @brief	Gets if uses range ability
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	True if it uses range ability, false if it isnt.
	 **************************************************************************************************/

	bool GetUsesRangeAbility() { return m_UsesRangeValueAbility; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::SetUsesRangeAbility(bool passed)
	 *
	 * @brief	Sets uses range ability
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	passed	future bool val
	 **************************************************************************************************/

	void SetUsesRangeAbility(bool passed) { m_UsesRangeValueAbility = passed; }

	/**********************************************************************************************//**
	 * @fn	std::pair<int, int> FeatClass::GetActivatedRange()
	 *
	 * @brief	Gets activated range
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The calculated activated range.
	 **************************************************************************************************/

	std::pair<int, int> GetActivatedRange() { return m_RangeActivated; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::SetRangeActivated(int lower, int upper)
	 *
	 * @brief	Sets range activated
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	lower	The lower bound / minimum val of the range
	 * @param	upper	The upper bound / max val of range
	 **************************************************************************************************/

	void SetRangeActivated(int lower, int upper) { m_RangeActivated.first = lower; m_RangeActivated.second = upper; }

	/**********************************************************************************************//**
	 * @fn	std::map<CircumstanceType, FeatClass::int>&GetCircumstanceAttackBonusAdd()
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/

	std::map<CircumstanceType, int>&GetCircumstanceAttackBonusAdd() { return m_CircumstanceAttackBonusAdd; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::AddCircumstanceAttackBonusAdd(CircumstanceType CType, int amount)
	 *
	 * @brief	Adds a circumstance attack bonus
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	CType 	The type of circumstance
	 * @param	amount	The amount
	 **************************************************************************************************/

	void AddCircumstanceAttackBonusAdd(CircumstanceType CType, int amount) { m_CircumstanceAttackBonusAdd[CType] = amount; }

	/**********************************************************************************************//**
	 * @fn	std::map<CircumstanceType, FeatClass::int>&GetCircumstanceAttackBonusSubtract()
	 *
	 * @brief	gets circumstance attack bonus for circumstance type
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/

	std::map<CircumstanceType, int>&GetCircumstanceAttackBonusSubtract() { return m_CircumstanceAttackBonusSubtract; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::AddCircumstanceAttackBonusSubtract(CircumstanceType CType, int amount)
	 *
	 * @brief	Adds a circumstance attack bonus subtract
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	CType 	The circumstance type.
	 * @param	amount	The amount.
	 **************************************************************************************************/

	void AddCircumstanceAttackBonusSubtract(CircumstanceType CType, int amount) { m_CircumstanceAttackBonusSubtract[CType] = amount; }

	/**********************************************************************************************//**
	 * @fn	std::map<CircumstanceType, FeatClass::int>&GetCircumstanceAttackDamageAdd()
	 *
	 * @brief	Gets circumstance type damage add
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/

	std::map<CircumstanceType, int>&GetCircumstanceAttackDamageAdd() { return m_CircumstanceAttackDamageAdd; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::AddCircumstanceAttackDamageAdd(CircumstanceType CType, int amount)
	 *
	 * @brief	Adds a circumstance attack damage add
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	CType 	The circumstance type.
	 * @param	amount	The amount.
	 **************************************************************************************************/

	void AddCircumstanceAttackDamageAdd(CircumstanceType CType, int amount) { m_CircumstanceAttackDamageAdd[CType] = amount; }

	/**********************************************************************************************//**
	 * @fn	std::map<CircumstanceType, FeatClass::int>&GetCircumstanceAttackDamageSubtract()
	 *
	 * @brief	get circumstance type attack damage subtract
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/

	std::map<CircumstanceType, int>&GetCircumstanceAttackDamageSubtract() { return m_CircumstanceAttackDamageSubtract; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::AddCircumstanceAttackDamageSubtract(CircumstanceType CType, int amount)
	 *
	 * @brief	Adds a circumstance attack damage subtract
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	CType 	The type.
	 * @param	amount	The amount.
	 **************************************************************************************************/

	void AddCircumstanceAttackDamageSubtract(CircumstanceType CType, int amount) { m_CircumstanceAttackDamageSubtract[CType] = amount; }

	/**********************************************************************************************//**
	 * @fn	std::map<CircumstanceType, FeatClass::int>&GetCircumstanceArmorBonusAdd()
	 *
	 * @brief	Get circumstance armor bonus add
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/

	std::map<CircumstanceType, int>&GetCircumstanceArmorBonusAdd() { return m_CircumstanceArmorBonusAdd; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::AddCircumstanceArmorBonusAdd(CircumstanceType CType, int amount)
	 *
	 * @brief	Adds a circumstance armor bonus add
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	CType 	The type.
	 * @param	amount	The amount.
	 **************************************************************************************************/

	void AddCircumstanceArmorBonusAdd(CircumstanceType CType, int amount) { m_CircumstanceArmorBonusAdd[CType] = amount; }

	/**********************************************************************************************//**
	 * @fn	std::map<CircumstanceType, FeatClass::int>&GetCircumstanceArmorBonusSubtract()
	 *
	 * @brief	get circumstance armor bonus subtract
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/

	std::map<CircumstanceType, int>&GetCircumstanceArmorBonusSubtract() { return m_CircumstanceArmorBonusSubtract; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::AddCircumstanceArmorBonusSubtract(CircumstanceType CType, int amount)
	 *
	 * @brief	Adds a circumstance armor bonus subtract 
	 * 			
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	CType 	The type.
	 * @param	amount	The amount.
	 **************************************************************************************************/

	void AddCircumstanceArmorBonusSubtract(CircumstanceType CType, int amount) { m_CircumstanceArmorBonusSubtract[CType] = amount; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::AddSaveBonus(AbilityScoreType AbType, int amount)
	 *
	 * @brief	Adds a save bonus
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	AbType	Type of the ability.
	 * @param	amount	The amount.
	 **************************************************************************************************/

	void AddSaveBonus(AbilityScoreType AbType, int amount) { m_SaveBonusAdd.push_back(std::pair<AbilityScoreType, int>( AbType, amount)); }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::AddArmorMoveSpeedBonusAdd(ArmorType Armor, int bonus)
	 *
	 * @brief	Adds an armor move speed bonus
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	Armor	The armortype
	 * @param	bonus	The bonus.
	 **************************************************************************************************/

	void AddArmorMoveSpeedBonusAdd(ArmorType Armor, int bonus) { m_MoveSpeedBonusAdd[Armor] = bonus; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::AddCircumstanceRequired(CircumstanceType CType)
	 *
	 * @brief	Adds a circumstance required
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	CType	The type.
	 **************************************************************************************************/

	void AddCircumstanceRequired(CircumstanceType CType) { m_CircumstancesRequired.push_back(CType); }

	/**********************************************************************************************//**
	 * @fn	std::vector<CircumstanceType>& FeatClass::GetCircumstancesRequired()
	 *
	 * @brief	Gets circumstances required
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The circumstances required.
	 **************************************************************************************************/

	std::vector<CircumstanceType>& GetCircumstancesRequired() { return m_CircumstancesRequired; }

	/**********************************************************************************************//**
	 * @fn	bool FeatClass::IsActive()
	 *
	 * @brief	Query if this feat is active
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	True if active, false if not.
	 **************************************************************************************************/

	bool IsActive() { return m_AbilityCurrentlyActive; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::SwitchActive()
	 *
	 * @brief	toggles active value
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/

	void SwitchActive() { m_AbilityCurrentlyActive = !m_AbilityCurrentlyActive; }

	/**********************************************************************************************//**
	 * @fn	bool FeatClass::IsToggleAbility()
	 *
	 * @brief	Query if this object is toggle ability
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	True if toggle ability, false if not.
	 **************************************************************************************************/

	bool IsToggleAbility() { return m_ToggleAbility; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::SetToggleAbility(bool passed)
	 *
	 * @brief	Sets toggle ability
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	passed	- new value for the ability
	 **************************************************************************************************/

	void SetToggleAbility(bool passed) { m_ToggleAbility = passed; }

	/**********************************************************************************************//**
	 * @fn	int FeatClass::GetCurrentRangeValue()
	 *
	 * @brief	Gets current range value
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The current range value.
	 **************************************************************************************************/

	int GetCurrentRangeValue() { return m_CurrentRangeValue; }

	/**********************************************************************************************//**
	 * @fn	void FeatClass::IncreaseFeat();
	 *
	 * @brief	Increase feat, increases the values for both positive and negative
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/

	void IncreaseFeat();

	/**********************************************************************************************//**
	 * @fn	void FeatClass::DecreaseFeat();
	 *
	 * @brief	Decrease feat, decreases the values for both positive and negative
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/

	void DecreaseFeat();

	/**********************************************************************************************//**
	 * @fn	int FeatClass::GetDodgeBonusAdd()
	 *
	 * @brief	Gets dodge bonus add
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The dodge bonus add.
	 **************************************************************************************************/

	int GetDodgeBonusAdd() { return m_DodgeBonusAdd; }

	/**********************************************************************************************//**
	 * @fn	int FeatClass::GetDodgeBonusSubtract()
	 *
	 * @brief	Gets dodge bonus subtract
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The dodge bonus subtract.
	 **************************************************************************************************/

	int GetDodgeBonusSubtract() { return m_DodgeBonusSubtract; }
private:
	/** @brief	Name of the feat */
	std::string m_FeatName = "";
	/** @brief	The description */
	std::string m_description = "";
	
	/** @brief	The weapon proficency add */
	std::vector<WeaponType> m_WeaponProficencyAdd;
	/** @brief	The armor proficiency add */
	std::vector<ArmorType> m_ArmorProficiencyAdd;

	/** @brief	The weapon attack bonus add */
	std::map<WeaponType, int> m_WeaponAttackBonusAdd;
	/** @brief	The weapon attack bonus subtract */
	std::map<WeaponType, int> m_WeaponAttackBonusSubtract;

	/** @brief	The weapon damage bonus add */
	std::map<WeaponType, int> m_WeaponDamageBonusAdd;
	/** @brief	The weapon damage bonus subtract */
	std::map<WeaponType, int> m_WeaponDamageBonusSubtract;
	std::map<CircumstanceType, int>m_CircumstanceAttackBonusAdd;
	std::map<CircumstanceType, int>m_CircumstanceAttackBonusSubtract;
	std::map<CircumstanceType, int>m_CircumstanceAttackDamageAdd;
	std::map<CircumstanceType, int>m_CircumstanceAttackDamageSubtract;
	std::map<CircumstanceType, int>m_CircumstanceArmorBonusAdd;
	std::map<CircumstanceType, int>m_CircumstanceArmorBonusSubtract;

	/** @brief	The armor bonus add */
	std::map<ArmorType, int> m_ArmorBonusAdd;
	/** @brief	The armor bonus subtract */
	std::map<ArmorType, int> m_ArmorBonusSubtract;

	/** @brief	The move speed bonus add */
	std::map<ArmorType, int> m_MoveSpeedBonusAdd;
	/** @brief	The move speed bonus subtract */
	std::map<ArmorType, int> m_MoveSpeedBonusSubtract;
	
	/** @brief	The base attack bonus add */
	int m_BaseAttackBonusAdd = 0;
	/** @brief	The dodge bonus add */
	int m_DodgeBonusAdd = -1;
	/** @brief	The dodge bonus subtract */
	int m_DodgeBonusSubtract = -1;

	/** @brief	The ability score bonuses */
	std::vector<std::pair<AbilityScoreType, int>> m_AbilityScoreBonuses;

	std::vector <std::pair<AbilityScoreType, int>> m_SaveBonusAdd;

	/** @brief	The general prereqs */
	std::vector<FeatClass*> m_GeneralPrereqs;
	/** @brief	The weapon prereqs */
	std::vector<std::pair<FeatClass*, WeaponType>> m_WeaponPrereqs;
	/** @brief	The armor prereqs */
	std::vector<std::pair<FeatClass*, ArmorType>> m_ArmorPrereqs;
	/** @brief	The circumstances required */
	std::vector<CircumstanceType> m_CircumstancesRequired;
	/** @brief	The required ability scores */
	std::pair<AbilityScoreType, int> m_RequiredAbilityScores;

	/** @brief	True to ability currently active */
	bool m_AbilityCurrentlyActive = true;
	/** @brief	True to toggle ability */
	bool m_ToggleAbility = false;
	/** @brief	True to uses range value ability */
	bool m_UsesRangeValueAbility = false;
	/** @brief	The range activated */
	std::pair<int, int> m_RangeActivated = { 0,0 };
	/** @brief	The current range value */
	int m_CurrentRangeValue = 0;

	/** @brief	The initiative bonus */
	int m_InitiativeBonus = 0;
	/** @brief	The equip actions reduction */
	int m_EquipActionsReduction = 0;
	/** @brief	The required bab */
	int RequiredBAB = 0;
	
};