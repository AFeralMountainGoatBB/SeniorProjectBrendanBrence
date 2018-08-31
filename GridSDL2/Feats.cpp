#include "Feats.h"

std::string FeatClass::GetName()
{
	return m_FeatName;
}

void FeatClass::SetName(std::string a_name)
{
	this->m_FeatName = a_name;
}

bool FeatClass::LoadFeat()
{
	bool success = true;


	return success;
}

void FeatClass::DisplayFeatFullInfo()
{
	std::cout << "m_FeatName " << GetName() << std::endl;

	//std::cout << "Bonuses to weapon types:" << std::endl;
	if (m_ToggleAbility)
	{
		std::cout << "Feat is ToggleAble" << std::endl;
	}
	if (m_UsesRangeValueAbility)
	{
		std::cout << "Uses Range, 0s will be placeholders " << m_RangeActivated.first << "x" << m_RangeActivated.second << std::endl;
	}
	
	for (auto i = WeaponTypeTextMap.begin(); i != WeaponTypeTextMap.end(); i++)
	{
		int total = 0;

		if (m_WeaponAttackBonusAdd.count((*i).first))
		{
			total += m_WeaponAttackBonusAdd[(*i).first];

		}
		if (m_WeaponAttackBonusSubtract.count((*i).first))
		{
			total += m_WeaponAttackBonusSubtract[(*i).first];
		}
		if (total != 0 || m_UsesRangeValueAbility)
		{
			std::cout << (*i).second << " Current AttackRoll: " << total << std::endl;
			total = 0;
		}

		if (m_WeaponDamageBonusAdd.count((*i).first))
		{
			total += m_WeaponDamageBonusAdd[(*i).first];
		}
		if (m_WeaponDamageBonusSubtract.count((*i).first))
		{
			total += m_WeaponDamageBonusSubtract[(*i).first];
		}
		if (total != 0 || m_UsesRangeValueAbility)
		{
			std::cout << (*i).second << " Current DamageRoll: " << total << std::endl << std::endl;
			total = 0;
		}
		//std::cout <<  std::endl;

	}

	if (m_BaseAttackBonusAdd > 0)
	{
		std::cout << "Base attack bonus increase" << m_BaseAttackBonusAdd << std::endl;
	}
		//std::cout <<  std::endl;

	}

void FeatClass::IncreaseFeat()
{
	//if it isnt a range feat, return
	if (!m_UsesRangeValueAbility)
	{
		return;
	}
	if (m_CurrentRangeValue < m_RangeActivated.second)
	{
		m_CurrentRangeValue++;
		for (auto it = m_WeaponAttackBonusAdd.begin(); it != m_WeaponAttackBonusAdd.end(); it++)
		{
				(*it).second++;
		}
		for (auto it = m_WeaponAttackBonusSubtract.begin(); it != m_WeaponAttackBonusSubtract.end(); it++)
		{
				(*it).second++;
		}
		for (auto it = m_WeaponDamageBonusAdd.begin(); it != m_WeaponDamageBonusAdd.end(); it++)
		{
			
				(*it).second++;
			
		}
		for (auto it = m_WeaponDamageBonusSubtract.begin(); it != m_WeaponDamageBonusSubtract.end(); it++)
		{
			
				(*it).second++;
			
		}
		//circumstances start
		for (auto it = m_CircumstanceArmorBonusAdd.begin(); it != m_CircumstanceArmorBonusAdd.end(); it++)
		{
			
				(*it).second++;
			
		}
		for (auto it = m_CircumstanceArmorBonusSubtract.begin(); it != m_CircumstanceArmorBonusSubtract.end(); it++)
		{
			
				(*it).second++;
			
		}
		//circumstance for attack and damage
		for (auto it = m_CircumstanceAttackBonusAdd.begin(); it != m_CircumstanceAttackBonusAdd.end(); it++)
		{
				(*it).second++;
		}
		for (auto it = m_CircumstanceAttackBonusSubtract.begin(); it != m_CircumstanceAttackBonusSubtract.end(); it++)
		{
				(*it).second++;
		}

		for (auto it = m_CircumstanceAttackDamageAdd.begin(); it != m_CircumstanceAttackDamageAdd.end(); it++)
		{
				(*it).second++;
		}
		for (auto it = m_CircumstanceAttackDamageSubtract.begin(); it != m_CircumstanceAttackDamageSubtract.end(); it++)
		{
			(*it).second++;
		}
	}
	//go through all structures that add + subtract, if the m_entry exists then increment it (while less than range max)
}

void FeatClass:: DecreaseFeat()
{
	//if it isnt a range feat, return
	if (!m_UsesRangeValueAbility)
	{
		return;
	}
	if (m_CurrentRangeValue > 0 && m_CurrentRangeValue > m_RangeActivated.first)
	{
		m_CurrentRangeValue--;


		for (auto it = m_WeaponAttackBonusAdd.begin(); it != m_WeaponAttackBonusAdd.end(); it++)
		{
			(*it).second--;
		}
		for (auto it = m_WeaponAttackBonusSubtract.begin(); it != m_WeaponAttackBonusSubtract.end(); it++)
		{
				(*it).second--;
		}
		for (auto it = m_WeaponDamageBonusAdd.begin(); it != m_WeaponDamageBonusAdd.end(); it++)
		{
				(*it).second--;
		}
		for (auto it = m_WeaponDamageBonusSubtract.begin(); it != m_WeaponDamageBonusSubtract.end(); it++)
		{
				(*it).second--;
		}
		//circumstances start
		for (auto it = m_CircumstanceArmorBonusAdd.begin(); it != m_CircumstanceArmorBonusAdd.end(); it++)
		{
				(*it).second--;
		}
		for (auto it = m_CircumstanceArmorBonusSubtract.begin(); it != m_CircumstanceArmorBonusSubtract.end(); it++)
		{
				(*it).second--;
		}
		//circumstance for attack and damage
		for (auto it = m_CircumstanceAttackBonusAdd.begin(); it != m_CircumstanceAttackBonusAdd.end(); it++)
		{
				(*it).second--;
		}
		for (auto it = m_CircumstanceAttackBonusSubtract.begin(); it != m_CircumstanceAttackBonusSubtract.end(); it++)
		{
				(*it).second--;
		}

		for (auto it = m_CircumstanceAttackDamageAdd.begin(); it != m_CircumstanceAttackDamageAdd.end(); it++)
		{

				(*it).second--;
		}
		for (auto it = m_CircumstanceAttackDamageSubtract.begin(); it != m_CircumstanceAttackDamageSubtract.end(); it++)
		{
				(*it).second--;
		}
	}
	//if the m_entry exists then decrement it (while greater than range min, or 0)
}
