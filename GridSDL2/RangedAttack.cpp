#include "AttackClass.h"
#include "EntityClass.h"
#include "EncounterInstance.h"
#include "MapAlgorithms.h"
#include <limits>

RangedAttack::RangedAttack()
{
}

void RangedAttack::AttackNormal(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance) {
		TempFeats = Source.GetActiveFeats();
	std::string DamageResult = "";
	std::string AttackResult = Source.GetName() + " attacks at range " + Target.GetName() + ": ";
	std::vector<CircumstanceType> Circumstances;
	Circumstances.push_back(RANGEDATTACK);
	SightAlgorithm CheckSight;

	Distance = CalcDistance(Source, Target, Instance);
	AttackResult += std::to_string(Distance) + "ft. attack ";
	if (Distance <= 30)
	{
		Circumstances.push_back(POINTBLANK);
	}

	std::pair<bool, bool> BlockObstructed;
	BlockObstructed = CheckSight.CheckAll(Source.GetLocation(), Target.GetLocation(), Instance.GetTileMap());
	if (BlockObstructed.first == true)
	{
		std::cout << "Tile is blocked" << std::endl;
		Instance.AddLog("Tile is blocked, cannot be attacked from this positon");
		return;
	}
	else if (BlockObstructed.second == true)
	{
		std::cout << "Tile is obstructed" << std::endl;
		Instance.AddLog("Target has cover from attack");
		Circumstances.push_back(TARGETHASCOVER);
	}
	else
	{
		std::cout << "Tile is not blocked or obstructed" << std::endl;
	}

	//get mainhand weapon (or whichever is ranged), check for bonuses / penalties add up
	Weapon = Source.GetEquipmentInSlot(MAINHAND);
	if (Weapon == nullptr)
	{
		*Weapon = Source.GetUnarmedStrike();
	}
	if (!Weapon->IsRangedWeapon())
	{
		Weapon = Source.GetEquipmentInSlot(OFFHAND);
	}
	if (!Weapon->IsRangedWeapon())
	{
		AttackResult = "Something went wrong, no ranged weapons equipped";
		Instance.AddLog(AttackResult);
		return;
	}
	if (Weapon->IsThrowingWeapon())
	{
		if(Weapon->IsLightWeapon())
		if (Source.GetAbilityModifier(DEX) >= Source.GetAbilityModifier(STR))
		{
			UsesAttributeForAttackRoll = DEX;
			UsesAttributeForDamageRoll = DEX;
		}
		else
		{
			UsesAttributeForAttackRoll = STR;
			UsesAttributeForDamageRoll = STR;
		}
	}

	int TotalAttackRollBonus = TotalWeaponTypeAttackBonus(Source, Weapon);
	if (BlockObstructed.second == true)
	{
		TotalAttackRollBonus -= 4;
	}
	//roll dice and add bonus
	int RollAmount = DiceRoll(D20);
	AttackResult += std::to_string(RollAmount); 
	if (TotalAttackRollBonus > 0)
	{
		AttackResult += "+";
	}
	else
	{
		AttackResult += "-";
	}
	AttackResult += std::to_string(TotalAttackRollBonus);
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
			}
			else
			{
				//std::cout << "Crit fail" << std::endl;
				Critical = false;
				AttackResult += "*Fail, NonCritical*";
			}
		}
		int CritMult = Weapon->GetCritInformation().second;

		DamageResult += Source.GetName() + " Damages " + Target.GetName() + " ";

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

		DamageResult += "=" + std::to_string(totalDamageRoll) + " ";
		if (Critical)
		{
			DamageResult += "(X" + std::to_string(CritMult) + ") ";
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

void RangedAttack::AttackDualWield(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance) {

}

int RangedAttack::CalcTotalAttackBonus(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance)
{
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
	//check if opponent is prone (+4 to hit melee, -4 ranged)
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
	int BaBAndAttb = Source.GetBaseAttackBonus() + Source.GetAbilityModifier(UsesAttributeForAttackRoll);
	TotalAttackRollBonus += BaBAndAttb;

	return TotalAttackRollBonus;
}

int RangedAttack::TotalWeaponTypeAttackBonus(EntityClass &Source, ObjectClass* WeaponCalc)
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

	int BaBAndStrength = Source.GetBaseAttackBonus() + Source.GetAbilityModifier(UsesAttributeForAttackRoll);
	TotalAttackBonus += BaBAndStrength;

	return TotalAttackBonus;
}

int RangedAttack::CalcTotalDamageBonus(EntityClass &Source, EntityClass &Target, EncounterInstance &Instance)
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
	
	TotalDamageBonus += Source.GetAbilityModifier(UsesAttributeForDamageRoll);
	return TotalDamageBonus;
}

int RangedAttack::CalcDistance(EntityClass &Source, EntityClass &Target, EncounterInstance& Instance)
{
	//squareroot of absolute value of((x2-x1)^2 + (y2 - y1)^2)
	//1 will be source, 2 be target
	int x1 = Source.GetLocation().first*5;
	int x2 = Target.GetLocation().first*5;
	int y1 = Source.GetLocation().second*5;
	int y2 = Target.GetLocation().second*5;

	int xSquareTotal = (x2 - x1) * (x2 - x1);
	int ySquareTotal = (y2 - y1) * (y2 - y1);

	int TotalDistance=sqrt(abs(xSquareTotal + ySquareTotal));

	return TotalDistance;
}

bool RangedAttack::CheckProficiency(EntityClass &Source)
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
