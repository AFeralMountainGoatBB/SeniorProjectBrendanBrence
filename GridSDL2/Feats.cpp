#include "Feats.h"

std::string FeatClass::GetName()
{
	return FeatName;
}

void FeatClass::SetName(std::string name)
{
	this->FeatName = name;
}

bool FeatClass::LoadFeat()
{
	bool success = true;


	return success;
}

void FeatClass::DisplayFeatFullInfo()
{
	std::cout << "FeatName " << GetName() << std::endl;

	//std::cout << "Bonuses to weapon types:" << std::endl;
	if (ToggleAbility)
	{
		std::cout << "Feat is ToggleAble" << std::endl;
	}
	if (UsesRangeValueAbility)
	{
		std::cout << "Uses Range, 0s will be placeholders " << RangeActivated.first << "x" << RangeActivated.second << std::endl;
	}
	
	for (auto i = WeaponTypeTextMap.begin(); i != WeaponTypeTextMap.end(); i++)
	{
		int total = 0;

		if (WeaponAttackBonusAdd.count((*i).first))
		{
			total += WeaponAttackBonusAdd[(*i).first];

		}
		if (WeaponAttackBonusSubtract.count((*i).first))
		{
			total += WeaponAttackBonusSubtract[(*i).first];
		}
		if (total != 0 || UsesRangeValueAbility)
		{
			std::cout << (*i).second << " Current AttackRoll: " << total << std::endl;
			total = 0;
		}

		if (WeaponDamageBonusAdd.count((*i).first))
		{
			total += WeaponDamageBonusAdd[(*i).first];
		}
		if (WeaponDamageBonusSubtract.count((*i).first))
		{
			total += WeaponDamageBonusSubtract[(*i).first];
		}
		if (total != 0 || UsesRangeValueAbility)
		{
			std::cout << (*i).second << " Current DamageRoll: " << total << std::endl << std::endl;
			total = 0;
		}
		//std::cout <<  std::endl;

	}

	if (BaseAttackBonusAdd > 0)
	{
		std::cout << "Base attack bonus increase" << BaseAttackBonusAdd << std::endl;
	}
		//std::cout <<  std::endl;

	}

void FeatClass::IncreaseFeat()
{
	//if it isnt a range feat, return
	if (!UsesRangeValueAbility)
	{
		return;
	}
	if (CurrentRangeValue < RangeActivated.second)
	{
		CurrentRangeValue++;
		for (auto it = WeaponAttackBonusAdd.begin(); it != WeaponAttackBonusAdd.end(); it++)
		{
				(*it).second++;
		}
		for (auto it = WeaponAttackBonusSubtract.begin(); it != WeaponAttackBonusSubtract.end(); it++)
		{
				(*it).second++;
		}
		for (auto it = WeaponDamageBonusAdd.begin(); it != WeaponDamageBonusAdd.end(); it++)
		{
			
				(*it).second++;
			
		}
		for (auto it = WeaponDamageBonusSubtract.begin(); it != WeaponDamageBonusSubtract.end(); it++)
		{
			
				(*it).second++;
			
		}
		//circumstances start
		for (auto it = CircumstanceArmorBonusAdd.begin(); it != CircumstanceArmorBonusAdd.end(); it++)
		{
			
				(*it).second++;
			
		}
		for (auto it = CircumstanceArmorBonusSubtract.begin(); it != CircumstanceArmorBonusSubtract.end(); it++)
		{
			
				(*it).second++;
			
		}
		//circumstance for attack and damage
		for (auto it = CircumstanceAttackBonusAdd.begin(); it != CircumstanceAttackBonusAdd.end(); it++)
		{
				(*it).second++;
		}
		for (auto it = CircumstanceAttackBonusSubtract.begin(); it != CircumstanceAttackBonusSubtract.end(); it++)
		{
				(*it).second++;
		}

		for (auto it = CircumstanceAttackDamageAdd.begin(); it != CircumstanceAttackDamageAdd.end(); it++)
		{
				(*it).second++;
		}
		for (auto it = CircumstanceAttackDamageSubtract.begin(); it != CircumstanceAttackDamageSubtract.end(); it++)
		{
			(*it).second++;
		}
	}
	//go through all structures that add + subtract, if the entry exists then increment it (while less than range max)
}

void FeatClass:: DecreaseFeat()
{
	//if it isnt a range feat, return
	if (!UsesRangeValueAbility)
	{
		return;
	}
	if (CurrentRangeValue > 0 && CurrentRangeValue > RangeActivated.first)
	{
		CurrentRangeValue--;


		for (auto it = WeaponAttackBonusAdd.begin(); it != WeaponAttackBonusAdd.end(); it++)
		{
			(*it).second--;
		}
		for (auto it = WeaponAttackBonusSubtract.begin(); it != WeaponAttackBonusSubtract.end(); it++)
		{
				(*it).second--;
		}
		for (auto it = WeaponDamageBonusAdd.begin(); it != WeaponDamageBonusAdd.end(); it++)
		{
				(*it).second--;
		}
		for (auto it = WeaponDamageBonusSubtract.begin(); it != WeaponDamageBonusSubtract.end(); it++)
		{
				(*it).second--;
		}
		//circumstances start
		for (auto it = CircumstanceArmorBonusAdd.begin(); it != CircumstanceArmorBonusAdd.end(); it++)
		{
				(*it).second--;
		}
		for (auto it = CircumstanceArmorBonusSubtract.begin(); it != CircumstanceArmorBonusSubtract.end(); it++)
		{
				(*it).second--;
		}
		//circumstance for attack and damage
		for (auto it = CircumstanceAttackBonusAdd.begin(); it != CircumstanceAttackBonusAdd.end(); it++)
		{
				(*it).second--;
		}
		for (auto it = CircumstanceAttackBonusSubtract.begin(); it != CircumstanceAttackBonusSubtract.end(); it++)
		{
				(*it).second--;
		}

		for (auto it = CircumstanceAttackDamageAdd.begin(); it != CircumstanceAttackDamageAdd.end(); it++)
		{

				(*it).second--;
		}
		for (auto it = CircumstanceAttackDamageSubtract.begin(); it != CircumstanceAttackDamageSubtract.end(); it++)
		{
				(*it).second--;
		}
	}
	//if the entry exists then decrement it (while greater than range min, or 0)
}
