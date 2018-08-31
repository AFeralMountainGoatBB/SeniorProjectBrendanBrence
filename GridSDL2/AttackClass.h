#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"
//#include "EntityClass.h"
#include "StaticFunctions.h"

class EncounterInstance;
class EntityClass;
class ObjectClass;
class FeatClass;
//Attack Organization
class AttackClass
{
public:
	//v functions
	virtual void AttackNormal(EntityClass &Source, EntityClass &Target, EncounterInstance &Instance) = 0;
	virtual void AttackDualWield(EntityClass &Source, EntityClass &Target, EncounterInstance &Instance) = 0;
	//data
	AbilityScoreType m_UsesAttributeForAttackRoll;
	AbilityScoreType m_UsesAttributeForDamageRoll;
	
};

class MeleeAttack : public AttackClass
{
public:
	void AttackNormal(EntityClass &Source, EntityClass &Target, EncounterInstance &Instance);
	void AttackDualWield(EntityClass &Source, EntityClass &Target, EncounterInstance &Instance);

	void DetermineAndSetWeapon(EntityClass &Source);

	int CalcTotalDamageBonus(EntityClass &Source);

	int CalcTotalAttackBonus(EntityClass & Source);

	void DetermineAttbUsed(EntityClass & Source);

	int TotalFeatAttackBonus(EntityClass &Source);
	

private:
	AbilityScoreType m_UsesAttributeForAttackRoll=STR;
	AbilityScoreType m_UsesAttributeForDamageRoll=STR;
	bool m_Critical=false;
	std::vector<FeatClass> m_TempFeats;
	std::string m_AttackResult;
	std::string m_DamageResult;
	std::vector<CircumstanceType> m_Circumstances;
	ObjectClass* m_Weapon;
	bool CheckProficiency(EntityClass &Source);
	
};

class RangedAttack :public AttackClass
{
public:
	RangedAttack();
	void AttackNormal(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance);
	void AttackDualWield(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance);

	int CalcTotalAttackBonus(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance);
	int CalcTotalDamageBonus(EntityClass &Source, EncounterInstance &Instance);

	int CalcTotalAttackBonus(EntityClass & Source);

	int CalcDistance(EntityClass &Source, EntityClass &Target, EncounterInstance& Instance);
	int CalcDistancePenalty(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance);

	bool DetermineAndSetWeapon(EntityClass &Source);
	void DetermineAttbUsed(EntityClass &Source);

	int TotalFeatAttackBonus(EntityClass&Source);

	void UseAmmo(EntityClass &Source);

private:
	AbilityScoreType m_UsesAttributeForAttackRoll = DEX;
	AbilityScoreType m_UsesAttributeForDamageRoll = DEX;
	bool m_Critical = false;
	std::vector<FeatClass> m_TempFeats;
	std::string m_AttackResult;
	std::string m_DamageResult;
	std::vector<CircumstanceType> m_Circumstances;
	ObjectClass* m_Weapon;
	int m_Distance;
	bool CheckProficiency(EntityClass &Source);

};
