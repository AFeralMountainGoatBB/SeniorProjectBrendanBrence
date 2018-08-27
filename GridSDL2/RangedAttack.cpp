#include "AttackClass.h"
#include "EntityClass.h"
#include "EncounterInstance.h"
#include "MapAlgorithms.h"
#include <limits>

RangedAttack::RangedAttack()
{

}

void RangedAttack::AttackNormal(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance) 
{
	TempFeats = Source.GetActiveFeats();

	std::string DamageResult = "";
	std::string AttackResult = Source.GetName() + " attacks at range " + Target.GetName() + ": ";

	if (!DetermineAndSetWeapon(Source)) //determines weapon being used, if no weapons equipped 
	{
		AttackResult = "Something went wrong, no ranged weapons equipped";
		Instance.AddLog(AttackResult);
		return;
	}

	SightAlgorithm CheckSight;

	Distance = CalcDistance(Source, Target, Instance);
	AttackResult += std::to_string(Distance) + "ft. attack ";
	int DistancePenalty = CalcDistancePenalty(Source, Target, Instance);

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
	//	std::cout << "Tile is not blocked or obstructed" << std::endl;
	}

	int TotalAttackRollBonus = CalcTotalAttackBonus(Source);
	if (BlockObstructed.second == true)
	{
		TotalAttackRollBonus -= 4;
	}
	TotalAttackRollBonus -= DistancePenalty;

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
		int TotalDamageBonus = CalcTotalDamageBonus(Source, Instance);
		//attack connected
		AttackResult += " *Hit*";

		if (Critical)
		{
			AttackResult += " *Threat*";
			RollAmount = DiceRoll(D20);
			AttackResult += "Crit Check = " + std::to_string(RollAmount + TotalAttackRollBonus);
			if ((RollAmount + TotalAttackRollBonus ) >= Target.GetArmorClass())
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
		totalDamageRoll -= (Target.GetTotalDamageReduction());
		Target.SubHitPoints(totalDamageRoll);
		if (Target.GetHitPoints()<=0)
		{
			std::cout << "Target: " << Target.GetName() << std::endl;
			Target.EntityDeath(Instance);
		}
		Instance.AddLog(AttackResult);
		Instance.AddLog(DamageResult);
	}
	else //hit missed
	{
		AttackResult += "*Miss*";
		Instance.AddLog(AttackResult);
	}

	UseAmmo(Source);

	return;
}

void RangedAttack::AttackDualWield(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance) {

}

int RangedAttack::CalcTotalAttackBonus(EntityClass & Source)
{
	DetermineAndSetWeapon(Source);
	std::vector<WeaponType> TempWeaponTypes = Weapon->GetWeaponType();
	int CritMult = Weapon->GetCritInformation().second;
	int TotalAttackRollBonus = 0;

	int TotalWeaponAttackBonus = TotalFeatAttackBonus(Source);
	
	TotalAttackRollBonus += TotalWeaponAttackBonus;
	//add base attack bonus and strength or dex bonus!
	int BaBAndAttb = Source.GetBaseAttackBonus() + Source.GetAbilityModifier(UsesAttributeForAttackRoll);
	TotalAttackRollBonus += BaBAndAttb;
	//std::cout << "Bab and attribute bonuses: " << Source.GetBaseAttackBonus() << ", " << Source.GetAbilityModifier(UsesAttributeForAttackRoll) << std::endl;

	return TotalAttackRollBonus;
}

int RangedAttack::TotalFeatAttackBonus(EntityClass&Source)
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
	//	std::cout << "Character not proficient" << std::endl;
		TotalAttackBonus -= 4;
	}
	std::cout << "Total feat attack bonus" << TotalAttackBonus << std::endl;
	return TotalAttackBonus;
}

int RangedAttack::CalcTotalDamageBonus(EntityClass &Source, EncounterInstance &Instance)
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

int RangedAttack::CalcDistancePenalty(EntityClass &Source, EntityClass &Target, EncounterInstance & Instance)
{
	int rangeincrement = Weapon->GetRangeIncrement();
	int distance = CalcDistance(Source, Target, Instance);
	std::cout << "Range increment of " << Weapon->GetName() << " " << rangeincrement << std::endl;
	int totalpenalty = 0;
	
	if (rangeincrement != 0)
	{
		totalpenalty = Distance / rangeincrement;
	}
	else
	{
		std::cout << "Error: Range increment is zero" << std::endl;
	}
	
	std::cout << "total penalty for: " << Distance << " Distance with increment " << rangeincrement << std::endl;

	return totalpenalty;
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

	if (TotalDistance <= 30)
	{
		if (find(Circumstances.begin(), Circumstances.end(), POINTBLANK) == Circumstances.end())
		{
			Circumstances.push_back(POINTBLANK);
		}
	}
	return TotalDistance;
}

bool RangedAttack::CheckProficiency(EntityClass &Source)
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

bool RangedAttack::DetermineAndSetWeapon(EntityClass &Source)
{
	Weapon = Source.GetEquipmentInSlot(MAINHAND);
	if (Weapon != nullptr && Weapon->IsRangedWeapon())
	{
		DetermineAttbUsed(Source);
		return true;
	}
	Weapon = Source.GetEquipmentInSlot(OFFHAND);
	if (Weapon != nullptr && Weapon->IsRangedWeapon())
	{
		DetermineAttbUsed(Source);
		return true;
	}
	std::cout << "Something went wrong, no ranged weapon equipped" << std::endl;
	return false;
}

void RangedAttack::DetermineAttbUsed(EntityClass &Source)
{
	if (Weapon != nullptr && Weapon->IsRangedWeapon())
	{
		if (Weapon->IsThrowingWeapon() && (Source.GetAbilityModifier(STR) > Source.GetAbilityModifier(DEX)))
		{
			UsesAttributeForAttackRoll = STR;
			UsesAttributeForDamageRoll = STR;
			std::cout << "str ranged wep" << std::endl;
		}
		else
		{
			std::cout << "dex ranged wep" << std::endl;
			UsesAttributeForAttackRoll = DEX;
			UsesAttributeForDamageRoll = DEX;
		}
		return;
	}
}

void RangedAttack::UseAmmo(EntityClass &Source)
{
	if (Weapon->IsThrowingWeapon())
	{
		if ((Source.GetEquipmentInSlot(MAINHAND) != nullptr) && (Source.GetEquipmentInSlot(MAINHAND)->GetName()==Weapon->GetName()))
		{
			Source.ClearEquipmentInSlot(MAINHAND);
		}
		else if ((Source.GetEquipmentInSlot(OFFHAND) != nullptr) && (Source.GetEquipmentInSlot(OFFHAND)->GetName() == Weapon->GetName()))
		{
			Source.ClearEquipmentInSlot(OFFHAND);
		}
	}

}