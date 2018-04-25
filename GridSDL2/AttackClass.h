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
	AbilityScoreType UsesAttributeForAttackRoll;
	AbilityScoreType UsesAttributeForDamageRoll;
	
};

class MeleeAttack : public AttackClass
{
public:
	void AttackNormal(EntityClass &Source, EntityClass &Target, EncounterInstance &Instance);
	void AttackDualWield(EntityClass &Source, EntityClass &Target, EncounterInstance &Instance);

	int CalcTotalAttackBonus(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance);
	int CalcTotalDamageBonus(EntityClass &Source, EntityClass &Target, EncounterInstance &Instance);

	int CritThreatRoll(EntityClass &Source);
	
AbilityScoreType UsesAttributeForAttackRoll=STR;
AbilityScoreType UsesAttributeForDamageRoll=STR;
private:
	bool CritThreat;
	std::vector<FeatClass> TempFeats;
	std::string AttackResult;
	std::string DamageResult;
	std::vector<CircumstanceType> Circumstances;
	ObjectClass* Weapon;
	bool CheckProficiency(EntityClass &Source);
	int TotalWeaponTypeAttackBonus(EntityClass &Source, ObjectClass* Weapon);
	int TotalCircumstanceAttackBonus(EntityClass &Source, std::vector<CircumstanceType> circumstances);
};

class RangedAttack :public AttackClass
{
public:
	RangedAttack();
	std::string AttackNormal();
	std::string AttackDualWield();

	AbilityScoreType UsesAttributeForAttackRoll = DEX;
	AbilityScoreType UsesAttributeForDamageroll = DEX;
	int RangeOfAttack;
private:
};

class SpecialAttack :public AttackClass
{


};