#include "AttackClass.h"
#include "EntityClass.h"
#include "EncounterInstance.h"
//bool for full attack?

void MeleeAttack::AttackNormal(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance)
{
	DetermineAndSetWeapon(Source); //semi redundant, guards against nullptr exceptions
	
	std::string DamageResult = "";
	std::string AttackResult = Source.GetName() + " attacks " + Target.GetName()+ ": ";
	
	int TotalAttackRollBonus = this->CalcTotalAttackBonus(Source);

	//roll dice and add bonus
	int RollAmount = DiceRoll(D20);
	AttackResult += std::to_string(RollAmount) + "+" + std::to_string(TotalAttackRollBonus);
	
	AttackResult += "=" + std::to_string(RollAmount + TotalAttackRollBonus);
	if (RollAmount >= Weapon->GetCritInformation().first)
	{
		Critical = true;	
	}
	
	AttackResult += " AC: " + std::to_string(Target.GetArmorClass());
	if (Target.GetArmorClass() <= (RollAmount + TotalAttackRollBonus))
	{
		int TotalDamageBonus = CalcTotalDamageBonus(Source);
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
	auto TempWeaponTypes = Weapon->GetWeaponType();
	std::vector<FeatClass> ProfFeats;
	for (auto i = TempFeats.begin(); i != TempFeats.end(); i++)
	{
		if ((i)->GetWeaponProficiencies().size()>0)
		{
			//std::cout << "Found a weapon proficiency feat: " << (*i).GetName() << std::endl;
			ProfFeats.push_back(*i);
		}
	}

	//check for the type of weapon and if there are matching feats
	for (auto Type = TempWeaponTypes.begin(); Type != TempWeaponTypes.end(); Type++)
	{
		//std::cout << "checking for type " << WeaponTypeTextMap[(*Type)] << std::endl;
		//check the proficency feats
		for (auto i = ProfFeats.begin(); i != ProfFeats.end(); i++)
		{
			auto it = find((i)->GetWeaponProficiencies().begin(), (i)->GetWeaponProficiencies().end(), (*Type));
			if ((it != (i)->GetWeaponProficiencies().end())) //found
			{
				//std::cout << "Found proficient feat for weapontype: " << WeaponTypeTextMap[(*Type)] << " feat is: " << (*i).GetName() << std::endl;
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

int MeleeAttack::CalcTotalAttackBonus(EntityClass & Source)
{	
	int TotalAttackRollBonus = 0;	
	if (Weapon == nullptr)
	{
		DetermineAndSetWeapon(Source);
		DetermineAttbUsed(Source);
	}

	int TotalFeatBonus = TotalFeatAttackBonus(Source);
	
	TotalAttackRollBonus += TotalFeatBonus;

	//add base attack bonus and strength bonus (or dex bonus)!
	int BaBAndStrength = Source.GetBaseAttackBonus() + Source.GetAbilityModifier(UsesAttributeForAttackRoll);
	TotalAttackRollBonus += BaBAndStrength;

	return TotalAttackRollBonus;
}

int MeleeAttack::TotalFeatAttackBonus(EntityClass &Source)
{
	int TotalAttackBonus = 0;

	TempFeats = Source.GetActiveFeats();

	if (std::find(Circumstances.begin(), Circumstances.end(), MELEEATTACK) == Circumstances.end())
	{
		Circumstances.push_back(MELEEATTACK);
	}
	
	if (Source.IsTwoHanding())
	{
		if (std::find(Circumstances.begin(), Circumstances.end(), TWOHANDING) == Circumstances.end())
		{
			Circumstances.push_back(TWOHANDING);
		}
	}

	auto TempWeaponTypes = Weapon->GetWeaponType();
	std::cout << "Checking feat bonuses for weapon type for weapon: " << Weapon->GetName() << std::endl;	
	//get the feats that match the weapontype attackroll for bonuses(add) (subtract)
	for (auto it = TempFeats.begin(); it != TempFeats.end(); it++)
	{
		for (auto Type = TempWeaponTypes.begin(); Type != TempWeaponTypes.end(); Type++)
		{
			if ((*it).GetWeaponAttackBonuses().count(*Type)) //true if > 0
			{
				std::cout << "Found feat: " << (*it).GetName() << " applies to: " << Weapon->GetName() << std::endl;
				std::cout << (*it).GetName() << "adds " << (*it).GetWeaponAttackBonuses()[*Type] << " to attack " << std::endl;
				TotalAttackBonus += ((*it).GetWeaponAttackBonuses())[*Type];
			}	
			if ((*it).GetWeaponAttackBonusSubtract().count(*Type)) //true if > 0
			{
				std::cout << "Found feat: " << (*it).GetName() << " applies to: " << Weapon->GetName() << std::endl;
				std::cout << (*it).GetName() << " subtracts " << (*it).GetWeaponAttackBonuses()[*Type] << " from attack " << std::endl;
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

	//check for proficency
	bool isProficient = CheckProficiency(Source);
	if (isProficient != true)
	{
		std::cout << "Character not proficient" << std::endl;
		TotalAttackBonus -= 4;
	}
	std::cout << "Total feat attack bonus" << TotalAttackBonus << std::endl;
	return TotalAttackBonus;
}

int MeleeAttack::CalcTotalDamageBonus(EntityClass &Source)
{
	if (Weapon == nullptr)
	{
		DetermineAndSetWeapon(Source);
		DetermineAttbUsed(Source);
	}
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

void MeleeAttack::DetermineAttbUsed(EntityClass &Source)
{
	if (Weapon->IsLightWeapon())
	{
		if (Source.GetAbilityModifier(DEX) >= Source.GetAbilityModifier(STR))
		{
			UsesAttributeForAttackRoll = DEX;
			UsesAttributeForDamageRoll = DEX;
		}
	}
}

void MeleeAttack::DetermineAndSetWeapon(EntityClass &Source)
{
	Weapon = Source.GetEquipmentInSlot(MAINHAND);
	if (Weapon == nullptr)
	{
		Weapon = &Source.GetUnarmedStrike();
		std::cout << "setting to unarmed attack" << Weapon->GetName() << std::endl;
	}
}