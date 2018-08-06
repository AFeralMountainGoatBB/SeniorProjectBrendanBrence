#include "AttackClass.h"
#include "EntityClass.h"
#include "EncounterInstance.h"
//bool for full attack?
void MeleeAttack::AttackNormal(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance)
{
	TempFeats = Source.GetActiveFeats();
	std::string DamageResult = "";
	std::string AttackResult = Source.GetName() + " attacks " + Target.GetName()+ ": ";
	std::vector<CircumstanceType> Circumstances;
	Circumstances.push_back(MELEEATTACK);
	if (Source.IsTwoHanding())
	{
		Circumstances.push_back(TWOHANDING);
	}
	
	//get mainhand weapon, check for bonuses / penalties add up
	Weapon = Source.GetEquipmentInSlot(MAINHAND);
	if (Weapon == nullptr)
	{
		Weapon = &Source.GetUnarmedStrike();
	}
	if (Weapon->IsLightWeapon())
	{
		if (Source.GetAbilityModifier(DEX) >= Source.GetAbilityModifier(STR))
		{
			UsesAttributeForAttackRoll = DEX;
			UsesAttributeForDamageRoll = DEX;
		}
	}
	
	int TotalAttackRollBonus = TotalWeaponTypeAttackBonus(Source, Weapon);

	//roll dice and add bonus
	int RollAmount = DiceRoll(D20);
	AttackResult += std::to_string(RollAmount) + "+" + std::to_string(TotalAttackRollBonus);
	if (TotalAttackRollBonus > 0)
	{
		AttackResult += "+"; 
	}
	AttackResult += "=" + std::to_string(RollAmount + TotalAttackRollBonus);
	if (RollAmount >= Weapon->GetCritInformation().first)
	{
		Critical = true;	
		//todo calc crit bonuses
	}
	
	AttackResult += " AC: " + std::to_string(Target.GetArmorClass());
	if (Target.GetArmorClass() <= (RollAmount + TotalAttackRollBonus))
	{
		int TotalDamageBonus = CalcTotalDamageBonus(Source, Target, Instance);
		//attack connected
		AttackResult += " *Hit*";

		if (Critical)
		{		
			AttackResult += " *Threat*";
			RollAmount = DiceRoll(D20);
			AttackResult += "Crit Check = " + std::to_string(RollAmount + TotalAttackRollBonus);
			if ((RollAmount + TotalAttackRollBonus /*+ CritThreatBonus*/) >= Target.GetArmorClass())
			{
			AttackResult += " Success! x" + std::to_string(Weapon->GetCritInformation().second) + " Damage*";
			}else
			{
			//std::cout << "Crit fail" << std::endl;
			Critical = false;
			AttackResult += "*Crit Fail*";
			}	
		}
		int CritMult = Weapon->GetCritInformation().second;
		
		DamageResult += Source.GetName() + " Damages " + Target.GetName()+" ";

		int totalDamageRoll = 0;
		for (int i = 0; i < Weapon->GetDamageDice().first; i++)
		{
			totalDamageRoll += DiceRoll(Weapon->GetDamageDice().second);
		}
		totalDamageRoll += TotalDamageBonus;
		DamageResult += std::to_string(Weapon->GetDamageDice().first) + "d" + std::to_string(Weapon->GetDamageDice().second);

		if (TotalDamageBonus >= 0)
		{
			DamageResult += "+" + std::to_string(TotalDamageBonus);
		}
		else
		{
			DamageResult += std::to_string(TotalDamageBonus);
		}
		if (Critical)
		{
			totalDamageRoll = totalDamageRoll * CritMult;
		}
		if (totalDamageRoll < 1)
		{
			totalDamageRoll = 1;
		}

		DamageResult += "=" + std::to_string(totalDamageRoll)+ " ";
		if (Critical)
		{
			DamageResult += "(X" + std::to_string(CritMult) +") ";
		}
		DamageResult += Target.GetName() + " Resists " + std::to_string(Target.GetTotalDamageReduction());
		//do damage

		Instance.AddLog(AttackResult);
		Instance.AddLog(DamageResult);
	}
	else //hit missed
	{
		AttackResult += "*Miss*";
		Instance.AddLog(AttackResult);
	}
	
	return;
}

bool MeleeAttack::CheckProficiency(EntityClass &Source)
{
	std::vector<WeaponType> TempWeaponTypes = Weapon->GetWeaponType();
	std::vector<FeatClass> ProfFeats;
	for (auto i = TempFeats.begin(); i != TempFeats.end(); i++)
	{
		if ((i)->GetWeaponProficiencies().size()>0)
		{
			ProfFeats.push_back(*i);
		}
	}

	//check for the type of weapon and if there are matching feats
	for (auto Type = TempWeaponTypes.begin(); Type != TempWeaponTypes.end(); Type++)
	{
		//check the proficency feats
		for (auto i = ProfFeats.begin(); i != ProfFeats.end(); i++)
		{
			auto it = find((i)->GetWeaponProficiencies().begin(), (i)->GetWeaponProficiencies().end(), (*Type));
			if (!(it == (i)->GetWeaponProficiencies().end())) //found
			{
				return true;
			}
		}
	}
	return false;
}

void MeleeAttack::AttackDualWield(EntityClass&Source, EntityClass & Target, EncounterInstance &Instance)
{

	return;
}

int MeleeAttack::CalcTotalAttackBonus(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance)
{
	Circumstances.push_back(MELEEATTACK);
	if (Source.IsTwoHanding())
	{
		Circumstances.push_back(TWOHANDING);
	}
	
	//get mainhand weapon, check for bonuses / penalties add up
	Weapon = Source.GetEquipmentInSlot(MAINHAND);
	if (Weapon == nullptr)
	{
		*Weapon = Source.GetUnarmedStrike();
	}
	std::vector<WeaponType> TempWeaponTypes = Weapon->GetWeaponType();
	int CritMult = Weapon->GetCritInformation().second;
	int TotalAttackRollBonus = 0;

	std::vector<FeatClass> TempFeats = Source.GetActiveFeats();
	//check for proficency
	bool isProficient = CheckProficiency(Source);
	int TotalWeaponAttackBonus = TotalWeaponTypeAttackBonus(Source, Weapon);
	//check if opponent is prone (+4 to hit melee)
	if (Target.IsProne())
	{
		TotalAttackRollBonus += 4;
	}
	if (isProficient != true)
	{
		TotalAttackRollBonus -= 4;
	}

	TotalAttackRollBonus += TotalWeaponAttackBonus;
	//add base attack bonus and strength bonus!
	int BaBAndStrength = Source.GetBaseAttackBonus() + Source.GetAbilityModifier(UsesAttributeForAttackRoll);
	TotalAttackRollBonus += BaBAndStrength;

	return TotalAttackRollBonus;
}

int MeleeAttack::TotalWeaponTypeAttackBonus(EntityClass &Source, ObjectClass* WeaponCalc)
{
	int TotalAttackBonus = 0;
	auto TempWeaponTypes = Weapon->GetWeaponType();
	//get the feats that match the weapontype attackroll for bonuses(add) (subtract)
	for (auto it = TempFeats.begin(); it != TempFeats.end(); it++)
	{
		for (auto Type = TempWeaponTypes.begin(); Type != TempWeaponTypes.end(); Type++)
		{
			if ((*it).GetWeaponAttackBonuses().count(*Type)) //true if > 0
			{
				TotalAttackBonus += ((*it).GetWeaponAttackBonuses())[*Type];
			}	
			if ((*it).GetWeaponAttackBonusSubtract().count(*Type)) //true if > 0
			{
				TotalAttackBonus -= ((*it).GetWeaponAttackBonusSubtract())[*Type];
			}
		}
	}
	
	//add circumstance feats to hit in
	for (auto it = TempFeats.begin(); it != TempFeats.end(); it++)
	{
		for (auto Type = Circumstances.begin(); Type != Circumstances.end(); Type++)
		{
			if ((*it).GetCircumstanceAttackBonusAdd().count(*Type))
			{
				TotalAttackBonus += ((*it).GetCircumstanceAttackBonusAdd())[(*Type)];
			}
			if ((*it).GetCircumstanceAttackBonusSubtract().count(*Type))
			{
				TotalAttackBonus -= ((*it).GetCircumstanceAttackBonusSubtract())[(*Type)];
			}
		}
	}
	bool isProficient = CheckProficiency(Source);
	if (isProficient != true)
	{
		TotalAttackBonus -= 4;
	}

	int BaBAndAttb = Source.GetBaseAttackBonus() + Source.GetAbilityModifier(UsesAttributeForAttackRoll);
	TotalAttackBonus += BaBAndAttb;

	return TotalAttackBonus;
}

int MeleeAttack::CalcTotalDamageBonus(EntityClass &Source, EntityClass &Target, EncounterInstance &Instance)
{
	int TotalDamageBonus = 0;
	//add damage bonuses
	//weapontypes
	for (auto it = TempFeats.begin(); it != TempFeats.end(); it++)
	{
		for (auto Type = Weapon->GetWeaponType().begin(); Type != Weapon->GetWeaponType().end(); Type++)
		{
			if ((*it).GetWeaponDamageBonuses().count(*Type)) //true if > 0
			{
				TotalDamageBonus += ((*it).GetWeaponDamageBonuses())[*Type];
			}
			if ((*it).GetWeaponDamageBonusSubtract().count(*Type)) //true if > 0
			{
				TotalDamageBonus -= ((*it).GetWeaponDamageBonusSubtract())[*Type];
			}
		}
	}
	//circumstance bonuses to damage
	for (auto it = TempFeats.begin(); it != TempFeats.end(); it++)
	{
		for (auto Type = Circumstances.begin(); Type != Circumstances.end(); Type++)
		{
			if ((*it).GetCircumstanceAttackDamageAdd().count(*Type))
			{
				TotalDamageBonus += ((*it).GetCircumstanceAttackDamageAdd())[(*Type)];
			}
			if ((*it).GetCircumstanceAttackDamageSubtract().count(*Type))
			{
				TotalDamageBonus -= ((*it).GetCircumstanceAttackDamageSubtract())[(*Type)];
			}
		}
	}
	//damage calculations
	//calc damage
	//get weapon damage bonuses, then circumstance damage bonuses, added all together, add str bonus
	if (Source.IsTwoHanding() || find(Weapon->GetWeaponType().begin(), Weapon->GetWeaponType().end(), LIGHT) != Weapon->GetWeaponType().end())
	{
		TotalDamageBonus += (Source.GetAbilityModifier(STR)*1.5);
	}
	else
	{
		TotalDamageBonus += Source.GetAbilityModifier(STR);
	}
	return TotalDamageBonus;
}
