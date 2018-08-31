#include "AttackClass.h"
#include "EntityClass.h"
#include "EncounterInstance.h"
//bool for full attack?

void MeleeAttack::AttackNormal(EntityClass & a_Source, EntityClass &a_Target, EncounterInstance &a_Instance)
{
	DetermineAndSetWeapon(a_Source); //semi redundant, guards against nullptr exceptions
	
	std::string m_DamageResult = "";
	std::string m_AttackResult = a_Source.GetName() + " attacks " + a_Target.GetName()+ ": ";
	
	int TotalAttackRollBonus = this->CalcTotalAttackBonus(a_Source);

	//roll dice and add bonus
	int RollAmount = DiceRoll(D20);
	m_AttackResult += std::to_string(RollAmount) + "+" + std::to_string(TotalAttackRollBonus);
	
	m_AttackResult += "=" + std::to_string(RollAmount + TotalAttackRollBonus);
	if (RollAmount >= m_Weapon->GetCritInformation().first)
	{
		m_Critical = true;	
	}
	
	m_AttackResult += " AC: " + std::to_string(a_Target.GetArmorClass());
	if (a_Target.GetArmorClass() <= (RollAmount + TotalAttackRollBonus))
	{
		int TotalDamageBonus = CalcTotalDamageBonus(a_Source);
		//attack connected
		m_AttackResult += " *Hit*";

		if (m_Critical)
		{		
			m_AttackResult += " *Threat*";
			RollAmount = DiceRoll(D20);
			m_AttackResult += "Crit Check = " + std::to_string(RollAmount + TotalAttackRollBonus);
			if ((RollAmount + TotalAttackRollBonus /*+ CritThreatBonus*/) >= a_Target.GetArmorClass())
			{
			m_AttackResult += " Success! x" + std::to_string(m_Weapon->GetCritInformation().second) + " Damage*";
			}else
			{
			//std::cout << "Crit fail" << std::endl;
			m_Critical = false;
			m_AttackResult += "*Crit Fail*";
			}	
		}
		int CritMult = m_Weapon->GetCritInformation().second;
		
		m_DamageResult += a_Source.GetName() + " Damages " + a_Target.GetName()+" ";

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

		m_DamageResult += "=" + std::to_string(totalDamageRoll)+ " ";
		if (m_Critical)
		{
			m_DamageResult += "(X" + std::to_string(CritMult) +") ";
		}
		m_DamageResult += a_Target.GetName() + " Resists " + std::to_string(a_Target.GetTotalDamageReduction());
		//do damage

		totalDamageRoll -= (a_Target.GetTotalDamageReduction());
		a_Target.SubHitPoints(totalDamageRoll);
		if (a_Target.GetHitPoints() <= 0)
		{
			std::cout << "a_Target: " << a_Target.GetName() << " Has died" << std::endl;
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
	
	return;
}

bool MeleeAttack::CheckProficiency(EntityClass &a_Source)
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

void MeleeAttack::AttackDualWield(EntityClass&a_Source, EntityClass & a_Target, EncounterInstance &a_Instance)
{

	return;
}

int MeleeAttack::CalcTotalAttackBonus(EntityClass & a_Source)
{	
	int TotalAttackRollBonus = 0;	
	if (m_Weapon == nullptr)
	{
		DetermineAndSetWeapon(a_Source);
		DetermineAttbUsed(a_Source);
	}

	int TotalFeatBonus = TotalFeatAttackBonus(a_Source);
	
	TotalAttackRollBonus += TotalFeatBonus;

	//add base attack bonus and strength bonus (or dex bonus)!
	int BaBAndStrength = a_Source.GetBaseAttackBonus() + a_Source.GetAbilityModifier(m_UsesAttributeForAttackRoll);
	TotalAttackRollBonus += BaBAndStrength;

	return TotalAttackRollBonus;
}

int MeleeAttack::TotalFeatAttackBonus(EntityClass &a_Source)
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
		std::cout << "Character not proficient" << std::endl;
		TotalAttackBonus -= 4;
	}
	std::cout << "Total feat attack bonus" << TotalAttackBonus << std::endl;
	return TotalAttackBonus;
}

int MeleeAttack::CalcTotalDamageBonus(EntityClass &a_Source)
{
	if (m_Weapon == nullptr)
	{
		DetermineAndSetWeapon(a_Source);
		DetermineAttbUsed(a_Source);
	}
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
	//damage calculations
	//calc damage
	//get weapon damage bonuses, then circumstance damage bonuses, added all together, add str bonus
	if (a_Source.IsTwoHanding() || find(m_Weapon->GetWeaponType().begin(), m_Weapon->GetWeaponType().end(), LIGHT) != m_Weapon->GetWeaponType().end())
	{
		TotalDamageBonus += (a_Source.GetAbilityModifier(STR)*1.5);
	}
	else
	{
		TotalDamageBonus += a_Source.GetAbilityModifier(STR);
	}
	return TotalDamageBonus;
}

void MeleeAttack::DetermineAttbUsed(EntityClass &a_Source)
{
	if (m_Weapon->IsLightWeapon())
	{
		if (a_Source.GetAbilityModifier(DEX) >= a_Source.GetAbilityModifier(STR))
		{
			m_UsesAttributeForAttackRoll = DEX;
			m_UsesAttributeForDamageRoll = DEX;
		}
	}
}

void MeleeAttack::DetermineAndSetWeapon(EntityClass &a_Source)
{
	m_Weapon = a_Source.GetEquipmentInSlot(MAINHAND);
	if (m_Weapon == nullptr)
	{
		m_Weapon = &a_Source.GetUnarmedStrike();
		std::cout << "setting to unarmed attack" << m_Weapon->GetName() << std::endl;
	}
}