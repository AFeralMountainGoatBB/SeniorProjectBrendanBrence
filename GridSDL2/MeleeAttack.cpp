#include "AttackClass.h"
#include "EntityClass.h"
#include "EncounterInstance.h"
//bool for full attack?
void MeleeAttack::AttackNormal(EntityClass & Source, EntityClass &Target, EncounterInstance &Instance)
{
	std::string DamageResult = "";
	std::string AttackResult = Source.GetName() + " attacks " + Target.GetName()+ ":";
	std::vector<CircumstanceType> Circumstances;
	Circumstances.push_back(MELEEATTACK);
	if (Source.IsTwoHanding())
	{
		Circumstances.push_back(TWOHANDING);
	}
	ObjectClass* TempObjPtr;
	int TotalAttackRollBonus = 0;
	//get mainhand weapon, check for bonuses / penalties add up
	TempObjPtr = Source.GetEquipmentInSlot(MAINHAND);
	if (TempObjPtr == nullptr)
	{
		*TempObjPtr = Source.GetUnarmedStrike();
	}
	std::vector<WeaponType> TempWeaponTypes = TempObjPtr->GetWeaponType();
	int CritMult = TempObjPtr->GetCritInformation().second;
	
	TempFeats = Source.GetActiveFeats();
	//check for proficency
	bool isProficient = CheckProficiency(Source);
	std::vector<FeatClass> ProfFeats;
	//make sure the current circumstances match the circumstances required by the feat.
	for (auto i = TempFeats.begin(); i != TempFeats.end();)
	{
		if (!std::includes( Circumstances.begin(), Circumstances.end(), (*i).GetCircumstancesRequired().begin(), (*i).GetCircumstancesRequired().end()))
		{
			TempFeats.erase(i);
		}
		else
		{
			i++;
		}
	}


	int TotalFeatBonus = 0;
	//get the feats that match the weapontype attackroll for bonuses(add)
	for (auto it = TempFeats.begin(); it != TempFeats.end(); it++)
	{
		for (auto Type = TempWeaponTypes.begin(); Type != TempWeaponTypes.end(); Type++)
		{
			if ((*it).GetWeaponAttackBonuses().count(*Type)) //true if > 0
			{
				TotalFeatBonus +=  ((*it).GetWeaponAttackBonuses())[*Type];
			}
		}
	}
	//get the feats that match the weapontype attackroll for bonuses(subtract)
	for (auto it = TempFeats.begin(); it != TempFeats.end(); it++)
	{
		for (auto Type = TempWeaponTypes.begin(); Type != TempWeaponTypes.end(); Type++)
		{
			if ((*it).GetWeaponAttackBonusSubtract().count(*Type)) //true if > 0
			{
				TotalFeatBonus += ((*it).GetWeaponAttackBonusSubtract())[*Type];
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
				TotalFeatBonus +=  ((*it).GetCircumstanceAttackBonusAdd())[(*Type)];
			}
			if ((*it).GetCircumstanceAttackBonusSubtract().count(*Type))
			{
				TotalFeatBonus += ((*it).GetCircumstanceAttackBonusSubtract())[(*Type)];
			}
		}
	}

	//check if opponent is prone (+4 to hit melee)
	if (Target.IsProne())
	{
		TotalAttackRollBonus += 4;
	}
	if (isProficient != true)
	{
		TotalAttackRollBonus -= 4;
	}
	TotalAttackRollBonus += TotalFeatBonus;
	//add base attack bonus and strength bonus!
	int BaBAndStrength = Source.GetBaseAttackBonus()+Source.GetAbilityModifier(UsesAttributeForAttackRoll);
	TotalAttackRollBonus += BaBAndStrength;

	int CritThreatBonus = 0;
	int RollAmount = DiceRoll(D20);
	AttackResult += std::to_string(RollAmount) + "+" + std::to_string(BaBAndStrength);
	if (TotalAttackRollBonus - BaBAndStrength > 0)
	{
		AttackResult += "+"; 
	}
	AttackResult+=std::to_string(TotalAttackRollBonus - BaBAndStrength);
	bool criticalThreat = false;
	if (RollAmount >= TempObjPtr->GetCritInformation().first)
	{
		criticalThreat = true;
		//todo calc crit bonuses
	}
	std::cout << Source.GetName() << " Attack roll total bonus: " << TotalAttackRollBonus << " Rolls a " << RollAmount << "=" << RollAmount+TotalAttackRollBonus << std::endl;
	//this should be sum of all roll bonuses at this point! check against target's defence
	std::cout << "Defender " << Target.GetName() << " total armor class is" << Target.GetArmorClass() << std::endl;
	AttackResult += "=" + std::to_string(RollAmount + TotalAttackRollBonus);
	AttackResult += " AC: " + std::to_string(Target.GetArmorClass());
	int TotalDamageBonus = 0;
	if (Target.GetArmorClass() <= (RollAmount + TotalAttackRollBonus))
	{	//attack connected
		AttackResult += " *Hit*";
		if (criticalThreat)
		{
			AttackResult += " *Threat*";
		}
		//weapontypes
		for (auto it = TempFeats.begin(); it != TempFeats.end(); it++)
		{
			for (auto Type = TempWeaponTypes.begin(); Type != TempWeaponTypes.end(); Type++)
			{
				if ((*it).GetWeaponDamageBonuses().count(*Type)) //true if > 0
				{
					TotalDamageBonus += ((*it).GetWeaponDamageBonuses())[*Type];
				}
			}
		}
		for (auto it = TempFeats.begin(); it != TempFeats.end(); it++)
		{
			for (auto Type = TempWeaponTypes.begin(); Type != TempWeaponTypes.end(); Type++)
			{
				if ((*it).GetWeaponDamageBonusSubtract().count(*Type)) //true if > 0
				{
					TotalDamageBonus += ((*it).GetWeaponDamageBonusSubtract())[*Type];
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
					TotalDamageBonus += ((*it).GetCircumstanceAttackDamageSubtract())[(*Type)];
				}
			}
		}
		//damage calculations
		//calc damage
		//get weapon damage bonuses, then circumstance damage bonuses, added all together, add str bonus
		if (Source.IsTwoHanding() || find(TempWeaponTypes.begin(), TempWeaponTypes.end(), LIGHT)!=TempWeaponTypes.end())
		{
			TotalDamageBonus += (Source.GetAbilityModifier(STR)*1.5);
		}
		else
		{
			TotalDamageBonus += Source.GetAbilityModifier(STR);
		}
		if (criticalThreat)
		{
			RollAmount = DiceRoll(D20);
			if ((RollAmount + TotalAttackRollBonus + CritThreatBonus)>=Target.GetArmorClass())
			{
				//std::cout << "Critical hit" << std::endl;
				AttackResult += "*Critical x" + std::to_string(CritMult) + "*";
			}
			else
			{
				//std::cout << "Crit fail" << std::endl;
				criticalThreat = false;
				AttackResult += "*Crit Fail*";
			}
		}
		
		std::cout << AttackResult << std::endl;
		
		DamageResult += Source.GetName() + " Damages " + Target.GetName()+" ";

		int totalDamageRoll = 0;
		for (int i = 0; i < TempObjPtr->GetDamageDice().first; i++)
		{
			totalDamageRoll += DiceRoll(TempObjPtr->GetDamageDice().second);
		}
		if (criticalThreat)
		{
			totalDamageRoll = totalDamageRoll * CritMult;
		}
		DamageResult += std::to_string(TempObjPtr->GetDamageDice().first) + "d" + std::to_string(TempObjPtr->GetDamageDice().second);

		if (TotalDamageBonus > 0)
		{
			DamageResult += "+" + std::to_string(TotalDamageBonus);
		}
		else
		{
			DamageResult += std::to_string(TotalDamageBonus);
		}
		
		if (totalDamageRoll < 1)
		{
			totalDamageRoll = 1;
		}
		DamageResult += "=" + std::to_string(TotalDamageBonus + totalDamageRoll);
		/*std::cout << Source.GetName() << "hits and deals" << TotalDamageBonus + totalDamageRoll << 
			" to " << Target.GetName() << " DR absorbs"; //<< Target.GetTotalDamageReduction();
		*/
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
	//get the feats that match the weapontype attackroll for bonuses(add)
	for (auto it = TempFeats.begin(); it != TempFeats.end(); it++)
	{
		for (auto Type = TempWeaponTypes.begin(); Type != TempWeaponTypes.end(); Type++)
		{
			if ((*it).GetWeaponAttackBonuses().count(*Type)) //true if > 0
			{
				TotalAttackBonus += ((*it).GetWeaponAttackBonuses())[*Type];
			}
		}
	}
	//get the feats that match the weapontype attackroll for bonuses(subtract)
	for (auto it = TempFeats.begin(); it != TempFeats.end(); it++)
	{
		for (auto Type = TempWeaponTypes.begin(); Type != TempWeaponTypes.end(); Type++)
		{
			if ((*it).GetWeaponAttackBonusSubtract().count(*Type)) //true if > 0
			{
				TotalAttackBonus += ((*it).GetWeaponAttackBonusSubtract())[*Type];
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
				TotalAttackBonus += ((*it).GetCircumstanceAttackBonusSubtract())[(*Type)];
			}
		}
	}
}