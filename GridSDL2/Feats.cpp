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
	std::cout << "FeatName" << GetName() << std::endl;

	std::cout << "Bonuses to weapon types:" << std::endl;
	if (UsesRangeAbility)
	{
		std::cout << "Uses Range " << RangeActivated.first << "x" << RangeActivated.second << std::endl;
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
		if (total != 0 || UsesRangeAbility)
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
		if (total != 0 || UsesRangeAbility)
		{
			std::cout << (*i).second << " Current DamageRoll: " << total << std::endl << std::endl;
			total = 0;
		}
		//std::cout <<  std::endl;

	}
}