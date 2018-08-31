#include "AttackClass.h"
#include "EntityClass.h"
#include "EncounterInstance.h"
#include "MapAlgorithms.h"
#include <limits>

RangedAttack::RangedAttack()
{

}

void RangedAttack::AttackNormal(EntityClass & a_Source, EntityClass &a_Target, EncounterInstance &a_Instance) 
{
	m_TempFeats = a_Source.GetActiveFeats();

	std::string m_DamageResult = "";
	std::string m_AttackResult = a_Source.GetName() + " attacks at range " + a_Target.GetName() + ": ";

	if (!DetermineAndSetWeapon(a_Source)) //determines weapon being used, if no weapons equipped 
	{
		m_AttackResult = "Something went wrong, no ranged weapons equipped";
		a_Instance.AddLog(m_AttackResult);
		return;
	}

	SightAlgorithm CheckSight;

	m_Distance = CalcDistance(a_Source, a_Target, a_Instance);
	m_AttackResult += std::to_string(m_Distance) + "ft. attack ";
	int DistancePenalty = CalcDistancePenalty(a_Source, a_Target, a_Instance);

	std::pair<bool, bool> BlockObstructed;
	BlockObstructed = CheckSight.CheckAll(a_Source.GetLocation(), a_Target.GetLocation(), a_Instance.GetTileMap());
	if (BlockObstructed.first == true)
	{
		std::cout << "Tile is blocked" << std::endl;
		a_Instance.AddLog("Tile is blocked, cannot be attacked from this positon");
		return;
	}
	else if (BlockObstructed.second == true)
	{
		std::cout << "Tile is obstructed" << std::endl;
		a_Instance.AddLog("a_Target has cover from attack");
		m_Circumstances.push_back(TARGETHASCOVER);
	}
	else
	{
	//	std::cout << "Tile is not blocked or obstructed" << std::endl;
	}

	int TotalAttackRollBonus = CalcTotalAttackBonus(a_Source);
	if (BlockObstructed.second == true)
	{
		TotalAttackRollBonus -= 4;
	}
	TotalAttackRollBonus -= DistancePenalty;

	//roll dice and add bonus
	int RollAmount = DiceRoll(D20);
	m_AttackResult += std::to_string(RollAmount); 
	if (TotalAttackRollBonus > 0)
	{
		m_AttackResult += "+";
	}
	else
	{
		m_AttackResult += "-";
	}
	m_AttackResult += std::to_string(TotalAttackRollBonus);
	m_AttackResult += "=" + std::to_string(RollAmount + TotalAttackRollBonus);
	if (RollAmount >= m_Weapon->GetCritInformation().first)
	{
		m_Critical = true;
		//todo calc crit bonuses
	}

	m_AttackResult += " AC: " + std::to_string(a_Target.GetArmorClass());
	if (a_Target.GetArmorClass() <= (RollAmount + TotalAttackRollBonus))
	{
		int TotalDamageBonus = CalcTotalDamageBonus(a_Source, a_Instance);
		//attack connected
		m_AttackResult += " *Hit*";

		if (m_Critical)
		{
			m_AttackResult += " *Threat*";
			RollAmount = DiceRoll(D20);
			m_AttackResult += "Crit Check = " + std::to_string(RollAmount + TotalAttackRollBonus);
			if ((RollAmount + TotalAttackRollBonus ) >= a_Target.GetArmorClass())
			{
				m_AttackResult += " Success! x" + std::to_string(m_Weapon->GetCritInformation().second) + " Damage*";
			}
			else
			{
				//std::cout << "Crit fail" << std::endl;
				m_Critical = false;
				m_AttackResult += "*Fail, NonCritical*";
			}
		}
		int CritMult = m_Weapon->GetCritInformation().second;

		m_DamageResult += a_Source.GetName() + " Damages " + a_Target.GetName() + " ";

		int totalDamageRoll = 0;
		for (int i = 0; i < m_Weapon->GetDamageDice().first; i++)
		{
			totalDamageRoll += DiceRoll(m_Weapon->GetDamageDice().second);
		}
		totalDamageRoll += TotalDamageBonus;
		m_DamageResult += std::to_string(m_Weapon->GetDamageDice().first) + "d" + std::to_string(m_Weapon->GetDamageDice().second);

		if (TotalDamageBonus >= 0)
		{
			m_DamageResult += "+" + std::to_string(TotalDamageBonus);
		}
		else
		{
			m_DamageResult += std::to_string(TotalDamageBonus);
		}
		if (m_Critical)
		{
			totalDamageRoll = totalDamageRoll * CritMult;
		}
		if (totalDamageRoll < 1)
		{
			totalDamageRoll = 1;
		}

		m_DamageResult += "=" + std::to_string(totalDamageRoll) + " ";
		if (m_Critical)
		{
			m_DamageResult += "(X" + std::to_string(CritMult) + ") ";
		}
		m_DamageResult += a_Target.GetName() + " Resists " + std::to_string(a_Target.GetTotalDamageReduction());
		//do damage
		totalDamageRoll -= (a_Target.GetTotalDamageReduction());
		a_Target.SubHitPoints(totalDamageRoll);
		if (a_Target.GetHitPoints()<=0)
		{
			std::cout << "a_Target: " << a_Target.GetName() << std::endl;
			a_Target.EntityDeath(a_Instance);
		}
		a_Instance.AddLog(m_AttackResult);
		a_Instance.AddLog(m_DamageResult);
	}
	else //hit missed
	{
		m_AttackResult += "*Miss*";
		a_Instance.AddLog(m_AttackResult);
	}

	UseAmmo(a_Source);

	return;
}

void RangedAttack::AttackDualWield(EntityClass & a_Source, EntityClass &a_Target, EncounterInstance &a_Instance) {

}

int RangedAttack::CalcTotalAttackBonus(EntityClass & a_Source)
{
	DetermineAndSetWeapon(a_Source);
	std::vector<WeaponType> TempWeaponTypes = m_Weapon->GetWeaponType();
	int CritMult = m_Weapon->GetCritInformation().second;
	int TotalAttackRollBonus = 0;

	int TotalWeaponAttackBonus = TotalFeatAttackBonus(a_Source);
	
	TotalAttackRollBonus += TotalWeaponAttackBonus;
	//add base attack bonus and strength or dex bonus!
	int BaBAndAttb = a_Source.GetBaseAttackBonus() + a_Source.GetAbilityModifier(m_UsesAttributeForAttackRoll);
	TotalAttackRollBonus += BaBAndAttb;
	//std::cout << "Bab and attribute bonuses: " << a_Source.GetBaseAttackBonus() << ", " << a_Source.GetAbilityModifier(m_UsesAttributeForAttackRoll) << std::endl;

	return TotalAttackRollBonus;
}

int RangedAttack::TotalFeatAttackBonus(EntityClass&a_Source)
{
	int TotalAttackBonus = 0;

	m_TempFeats = a_Source.GetActiveFeats();

	if (std::find(m_Circumstances.begin(), m_Circumstances.end(), MELEEATTACK) == m_Circumstances.end())
	{
		m_Circumstances.push_back(MELEEATTACK);
	}

	if (a_Source.IsTwoHanding())
	{
		if (std::find(m_Circumstances.begin(), m_Circumstances.end(), TWOHANDING) == m_Circumstances.end())
		{
			m_Circumstances.push_back(TWOHANDING);
		}
	}

	auto TempWeaponTypes = m_Weapon->GetWeaponType();
	std::cout << "Checking feat bonuses for weapon type for weapon: " << m_Weapon->GetName() << std::endl;
	//get the feats that match the weapontype attackroll for bonuses(add) (subtract)
	for (auto it = m_TempFeats.begin(); it != m_TempFeats.end(); it++)
	{
		for (auto Type = TempWeaponTypes.begin(); Type != TempWeaponTypes.end(); Type++)
		{
			if ((*it).GetWeaponAttackBonuses().count(*Type)) //true if > 0
			{
				std::cout << "Found feat: " << (*it).GetName() << " applies to: " << m_Weapon->GetName() << std::endl;
				std::cout << (*it).GetName() << "adds " << (*it).GetWeaponAttackBonuses()[*Type] << " to attack " << std::endl;
				TotalAttackBonus += ((*it).GetWeaponAttackBonuses())[*Type];
			}
			if ((*it).GetWeaponAttackBonusSubtract().count(*Type)) //true if > 0
			{
				std::cout << "Found feat: " << (*it).GetName() << " applies to: " << m_Weapon->GetName() << std::endl;
				std::cout << (*it).GetName() << " subtracts " << (*it).GetWeaponAttackBonuses()[*Type] << " from attack " << std::endl;
				TotalAttackBonus -= ((*it).GetWeaponAttackBonusSubtract())[*Type];
			}
		}
	}
	//add circumstance feats to hit in
	for (auto it = m_TempFeats.begin(); it != m_TempFeats.end(); it++)
	{
		for (auto Type = m_Circumstances.begin(); Type != m_Circumstances.end(); Type++)
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
	bool isProficient = CheckProficiency(a_Source);
	if (isProficient != true)
	{
	//	std::cout << "Character not proficient" << std::endl;
		TotalAttackBonus -= 4;
	}
	std::cout << "Total feat attack bonus" << TotalAttackBonus << std::endl;
	return TotalAttackBonus;
}

int RangedAttack::CalcTotalDamageBonus(EntityClass &a_Source, EncounterInstance &a_Instance)
{
	int TotalDamageBonus = 0;
	//add damage bonuses
	//weapontypes
	for (auto it = m_TempFeats.begin(); it != m_TempFeats.end(); it++)
	{
		for (auto Type = m_Weapon->GetWeaponType().begin(); Type != m_Weapon->GetWeaponType().end(); Type++)
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
	for (auto it = m_TempFeats.begin(); it != m_TempFeats.end(); it++)
	{
		for (auto Type = m_Circumstances.begin(); Type != m_Circumstances.end(); Type++)
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

	TotalDamageBonus += a_Source.GetAbilityModifier(m_UsesAttributeForDamageRoll);
	return TotalDamageBonus;
}

int RangedAttack::CalcDistancePenalty(EntityClass &a_Source, EntityClass &a_Target, EncounterInstance & a_Instance)
{
	int rangeincrement = m_Weapon->GetRangeIncrement();
	int distance = CalcDistance(a_Source, a_Target, a_Instance);
	std::cout << "Range increment of " << m_Weapon->GetName() << " " << rangeincrement << std::endl;
	int totalpenalty = 0;
	
	if (rangeincrement != 0)
	{
		totalpenalty = m_Distance / rangeincrement;
	}
	else
	{
		std::cout << "Error: Range increment is zero" << std::endl;
	}
	
	std::cout << "total penalty for: " << m_Distance << " m_Distance with increment " << rangeincrement << std::endl;

	return totalpenalty;
}

int RangedAttack::CalcDistance(EntityClass &a_Source, EntityClass &a_Target, EncounterInstance& a_Instance)
{
	//squareroot of absolute value of((x2-x1)^2 + (y2 - y1)^2)
	//1 will be source, 2 be target
	int x1 = a_Source.GetLocation().first*5;
	int x2 = a_Target.GetLocation().first*5;
	int y1 = a_Source.GetLocation().second*5;
	int y2 = a_Target.GetLocation().second*5;

	int xSquareTotal = (x2 - x1) * (x2 - x1);
	int ySquareTotal = (y2 - y1) * (y2 - y1);

	int TotalDistance=sqrt(abs(xSquareTotal + ySquareTotal));

	if (TotalDistance <= 30)
	{
		if (find(m_Circumstances.begin(), m_Circumstances.end(), POINTBLANK) == m_Circumstances.end())
		{
			m_Circumstances.push_back(POINTBLANK);
		}
	}
	return TotalDistance;
}

bool RangedAttack::CheckProficiency(EntityClass &a_Source)
{
	auto TempWeaponTypes = m_Weapon->GetWeaponType();
	std::vector<FeatClass> ProfFeats;
	for (auto i = m_TempFeats.begin(); i != m_TempFeats.end(); i++)
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

bool RangedAttack::DetermineAndSetWeapon(EntityClass &a_Source)
{
	m_Weapon = a_Source.GetEquipmentInSlot(MAINHAND);
	if (m_Weapon != nullptr && m_Weapon->IsRangedWeapon())
	{
		DetermineAttbUsed(a_Source);
		return true;
	}
	m_Weapon = a_Source.GetEquipmentInSlot(OFFHAND);
	if (m_Weapon != nullptr && m_Weapon->IsRangedWeapon())
	{
		DetermineAttbUsed(a_Source);
		return true;
	}
	std::cout << "Something went wrong, no ranged weapon equipped" << std::endl;
	return false;
}

void RangedAttack::DetermineAttbUsed(EntityClass &a_Source)
{
	if (m_Weapon != nullptr && m_Weapon->IsRangedWeapon())
	{
		if (m_Weapon->IsThrowingWeapon() && (a_Source.GetAbilityModifier(STR) > a_Source.GetAbilityModifier(DEX)))
		{
			m_UsesAttributeForAttackRoll = STR;
			m_UsesAttributeForDamageRoll = STR;
			std::cout << "str ranged wep" << std::endl;
		}
		else
		{
			std::cout << "dex ranged wep" << std::endl;
			m_UsesAttributeForAttackRoll = DEX;
			m_UsesAttributeForDamageRoll = DEX;
		}
		return;
	}
}

void RangedAttack::UseAmmo(EntityClass &a_Source)
{
	if (m_Weapon->IsThrowingWeapon())
	{
		if ((a_Source.GetEquipmentInSlot(MAINHAND) != nullptr) && (a_Source.GetEquipmentInSlot(MAINHAND)->GetName()==m_Weapon->GetName()))
		{
			a_Source.ClearEquipmentInSlot(MAINHAND);
		}
		else if ((a_Source.GetEquipmentInSlot(OFFHAND) != nullptr) && (a_Source.GetEquipmentInSlot(OFFHAND)->GetName() == m_Weapon->GetName()))
		{
			a_Source.ClearEquipmentInSlot(OFFHAND);
		}
	}

}