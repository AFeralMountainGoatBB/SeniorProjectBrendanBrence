/**********************************************************************************************//**
 * @file	AttackClass.h.
 *
 * @brief	Declares the attack class, Declares the RangedAttackClass, Declares the MeleeAttackClass
 **************************************************************************************************/


#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"
#include "StaticFunctions.h"

//fwd declarations to prevent circular dependencies
class EncounterInstance;
class EntityClass;
class ObjectClass;
class FeatClass;

/**********************************************************************************************//**
 * @class	AttackClass
 *
 * @brief	An abstract base class.
 *
 * @author	Brendan B
 * @date	9/4/2018
 **************************************************************************************************/

class AttackClass
{
public:
	/**********************************************************************************************//**
	 * @fn	virtual void AttackClass::AttackNormal(EntityClass &Source, EntityClass &Target, EncounterInstance &Instance) = 0;
	 *
	 * @brief	Attack normal
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source  	source for attack
	 * @param [in,out]	Target  	Target for the attack
	 * @param [in,out]	Instance	The instance.
	 **************************************************************************************************/

	virtual void AttackNormal(EntityClass &Source, EntityClass &Target, EncounterInstance &Instance) = 0;

	//data
	/** @brief	The uses attribute for attack roll */
	AbilityScoreType m_UsesAttributeForAttackRoll;
	/** @brief	The uses attribute for damage roll */
	AbilityScoreType m_UsesAttributeForDamageRoll;
	
};

/**********************************************************************************************//**
 * @class	MeleeAttack
 *
 * @brief	A melee attack class, inherits from AttackClass, for making touch range attacks
 *
 * @author	Brendan B
 * @date	9/4/2018
 **************************************************************************************************/

class MeleeAttack : public AttackClass
{
public:

	/**********************************************************************************************//**
	 * @fn	void MeleeAttack::AttackNormal(EntityClass &Source, EntityClass &Target, EncounterInstance &Instance);
	 *
	 * @brief	Attack normal
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source  	Source for the attack
	 * @param [in,out]	Target  	Target for the attack
	 * @param [in,out]	Instance	The instance the attack is happening in
	 **************************************************************************************************/

	void AttackNormal(EntityClass &Source, EntityClass &Target, EncounterInstance &Instance);

	/**********************************************************************************************//**
	 * @fn	void MeleeAttack::DetermineAndSetWeapon(EntityClass &Source);
	 *
	 * @brief	Determine and set weapon being used, looks for melee weapons in source hands and select that one
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source	Source for the attack
	 **************************************************************************************************/

	void DetermineAndSetWeapon(EntityClass &Source);

	/**********************************************************************************************//**
	 * @fn	int MeleeAttack::CalcTotalDamageBonus(EntityClass &Source);
	 *
	 * @brief	Calculates the total damage bonus
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source	Source for the attack
	 *
	 * @return	The calculated total damage bonus.
	 **************************************************************************************************/

	int CalcTotalDamageBonus(EntityClass &Source);

	/**********************************************************************************************//**
	 * @fn	int MeleeAttack::CalcTotalAttackBonus(EntityClass & Source);
	 *
	 * @brief	Calculates the total attack bonus
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source	Source for the attack
	 *
	 * @return	The calculated total attack bonus.
	 **************************************************************************************************/

	int CalcTotalAttackBonus(EntityClass & Source);

	/**********************************************************************************************//**
	 * @fn	void MeleeAttack::DetermineAttbUsed(EntityClass & Source);
	 *
	 * @brief	Determine attribute used for the attack
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source	Source for the attack
	 **************************************************************************************************/

	void DetermineAttbUsed(EntityClass & Source);

	/**********************************************************************************************//**
	 * @fn	int MeleeAttack::TotalFeatAttackBonus(EntityClass &Source);
	 *
	 * @brief	Total feat attack bonus, iterates through every feat the user has to determine
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source	Source for the attack
	 *
	 * @return	The total number of feat attack bonus.
	 **************************************************************************************************/

	int TotalFeatAttackBonus(EntityClass &Source);
	

private:
	/** @brief	The uses attribute for attack roll */
	AbilityScoreType m_UsesAttributeForAttackRoll=STR;
	/** @brief	The uses attribute for damage roll */
	AbilityScoreType m_UsesAttributeForDamageRoll=STR;
	/** @brief	True to critical */
	bool m_Critical=false;
	/** @brief	The temporary feats */
	std::vector<FeatClass> m_TempFeats;
	/** @brief	The attack result */
	std::string m_AttackResult;
	/** @brief	The damage result */
	std::string m_DamageResult;
	/** @brief	The circumstances */
	std::vector<CircumstanceType> m_Circumstances;
	/** @brief	The weapon */
	ObjectClass* m_Weapon;

	/**********************************************************************************************//**
	 * @fn	bool MeleeAttack::CheckProficiency(EntityClass &Source);
	 *
	 * @brief	Check proficiency, if the user is proficient in the weapon they are using for the attack
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source	Source for the attack
	 *
	 * @return	True if they are, false if they arent
	 **************************************************************************************************/

	bool CheckProficiency(EntityClass &Source);
	
};

/**********************************************************************************************//**
 * @class	RangedAttack
 *
 * @brief	A ranged attack class containing information and algorithms for making ranged attacks
 *
 * @author	Brendan B
 * @date	9/4/2018
 **************************************************************************************************/

class RangedAttack :public AttackClass
{
public:

	/**********************************************************************************************//**
	 * @fn	RangedAttack::RangedAttack();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 **************************************************************************************************/

	RangedAttack();

	/**********************************************************************************************//**
	 * @fn	void RangedAttack::AttackNormal(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance);
	 *
	 * @brief	Attack normal
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source  	Source for the attack
	 * @param [in,out]	Target  	Target for the attack
	 * @param [in,out]	Instance	The instance the attack is taking place in
	 **************************************************************************************************/

	void AttackNormal(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance);



	/**********************************************************************************************//**
	 * @fn	int RangedAttack::CalcTotalDamageBonus(EntityClass &Source, EncounterInstance &Instance);
	 *
	 * @brief	Calculates the total damage bonus
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source  	Source for the attack
	 * @param [in,out]	Instance	The instance the attack 
	 *
	 * @return	The calculated total damage bonus.
	 **************************************************************************************************/

	int CalcTotalDamageBonus(EntityClass &Source, EncounterInstance &Instance);

	/**********************************************************************************************//**
	 * @fn	int RangedAttack::CalcTotalAttackBonus(EntityClass & Source);
	 *
	 * @brief	Calculates the total attack bonus
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source	Source for the attack
	 *
	 * @return	The calculated total attack bonus.
	 **************************************************************************************************/

	int CalcTotalAttackBonus(EntityClass & Source);

	/**********************************************************************************************//**
	 * @fn	int RangedAttack::CalcDistance(EntityClass &Source, EntityClass &Target, EncounterInstance& Instance);
	 *
	 * @brief	Calculates the distance
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source  	Source for the attack
	 * @param [in,out]	Target  	Target for the attack
	 * @param [in,out]	Instance	The instance the attack takes place in
	 *
	 * @return	The calculated distance.
	 **************************************************************************************************/

	int CalcDistance(EntityClass &Source, EntityClass &Target, EncounterInstance& Instance);

	/**********************************************************************************************//**
	 * @fn	int RangedAttack::CalcDistancePenalty(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance);
	 *
	 * @brief	Calculates the distance penalty, takes distance and divides it through by the weapon's range penalty
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source  	Source for the attack
	 * @param [in,out]	Target  	Target for the attack
	 * @param [in,out]	Instance	The instance attack takes place in
	 *
	 * @return	The calculated distance penalty.
	 **************************************************************************************************/

	int CalcDistancePenalty(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance);

	/**********************************************************************************************//**
	 * @fn	bool RangedAttack::DetermineAndSetWeapon(EntityClass &Source);
	 *
	 * @brief	Determine and set weapon, looks for ranged or throwing weapons in the entity's hand, prioritizes ranged over throwing and 
	 * 			mainhand over offhand
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source	Source for the attack
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool DetermineAndSetWeapon(EntityClass &Source);

	/**********************************************************************************************//**
	 * @fn	void RangedAttack::DetermineAttbUsed(EntityClass &Source);
	 *
	 * @brief	Determine attribute used by the attack for attack and damage bonuses
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source	Source for the attack
	 **************************************************************************************************/

	void DetermineAttbUsed(EntityClass &Source);

	/**********************************************************************************************//**
	 * @fn	int RangedAttack::TotalFeatAttackBonus(EntityClass&Source);
	 *
	 * @brief	Total feat attack bonus, looks through all feats for placeable attacks
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source	Source for the attack
	 *
	 * @return	The total number of feat attack bonus.
	 **************************************************************************************************/

	int TotalFeatAttackBonus(EntityClass&Source);

	/**********************************************************************************************//**
	 * @fn	void RangedAttack::UseAmmo(EntityClass &Source);
	 *
	 * @brief	Use ammo, 'ammo' only exists for ranged weapons, deletes the weapon being used for the attack
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source	Source for the attack
	 **************************************************************************************************/

	void UseAmmo(EntityClass &Source);

private:
	/** @brief	The uses attribute for attack roll */
	AbilityScoreType m_UsesAttributeForAttackRoll = DEX;
	/** @brief	The uses attribute for damage roll */
	AbilityScoreType m_UsesAttributeForDamageRoll = DEX;
	/** @brief	True to critical */
	bool m_Critical = false;
	/** @brief	The temporary feats */
	std::vector<FeatClass> m_TempFeats;
	/** @brief	The attack result */
	std::string m_AttackResult;
	/** @brief	The damage result */
	std::string m_DamageResult;
	/** @brief	The circumstances */
	std::vector<CircumstanceType> m_Circumstances;
	/** @brief	The weapon */
	ObjectClass* m_Weapon;
	/** @brief	The distance */
	int m_Distance;

	/**********************************************************************************************//**
	 * @fn	bool RangedAttack::CheckProficiency(EntityClass &Source);
	 *
	 * @brief	Check proficiency, checks if entity is proficient with weapon being used
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param [in,out]	Source	Source for the attack
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool CheckProficiency(EntityClass &Source);

};
