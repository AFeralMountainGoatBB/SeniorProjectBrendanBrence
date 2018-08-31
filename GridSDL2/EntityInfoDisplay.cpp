#include "EntityInfoDisplay.h"
#include "EntityClass.h"
#include "AttackClass.h"
#include "EncounterInstance.h"

EntityInfoDisplay::EntityInfoDisplay()
{

}
EntityInfoDisplay::EntityInfoDisplay(std::string a_TextureFolderPath, std::map<std::string, LTexture*> &a_TextureMap, SDL_Rect a_viewport, TTF_Font* a_Font)
{
	m_PanelConstraints.x = a_viewport.x;
	m_PanelConstraints.y = a_viewport.y;
	m_PanelConstraints.w = a_viewport.w;
	m_PanelConstraints.h = a_viewport.h;

	m_InfoFont = a_Font;

}

void EntityInfoDisplay::SetPanelConstraints(int a_x, int a_y, int a_w, int a_h)
{
	m_PanelConstraints.x = a_x;
	m_PanelConstraints.y = a_y;
	m_PanelConstraints.w = a_w;
	m_PanelConstraints.h = a_h;
}

void EntityInfoDisplay::SetPanelConstraints(SDL_Rect a_other)
{
	m_PanelConstraints = a_other;
	//	std::cout << "Constraints for log: a_x:" << m_LogConstraints.a_x << " a_y: " << m_LogConstraints.a_y << std::endl;
}


void EntityInfoDisplay::Setup(std::string a_TextureFolderPath, std::map<std::string, LTexture*> &a_TextureMap, SDL_Rect a_viewport, TTF_Font* a_Font, SDL_Renderer *& a_renderer)
{
	m_PanelConstraints.x = a_viewport.x;
	m_PanelConstraints.y = a_viewport.y;
	m_PanelConstraints.w = a_viewport.w;
	m_PanelConstraints.h = a_viewport.h;

	m_InfoFont = a_Font;

	m_MAttack_Texture.loadFromRenderedText(m_MeleeLabel, m_InfoTextColor, a_renderer, m_InfoFont);
	m_RAttack_Texture.loadFromRenderedText(m_RangedLabel, m_InfoTextColor, a_renderer, m_InfoFont);
}

std::string EntityInfoDisplay::DetermineNameLabel(EntityClass a_ActiveUnit)
{
	return a_ActiveUnit.GetName();
}

std::pair<std::string, std::string> EntityInfoDisplay::DetermineAttackLabels(EntityClass a_ActiveUnit, EncounterInstance & a_Instance)
{
	std::string MeleeLabelStore = "";
	std::string RangedLabelStore = "";

	std::string MeleeAttackBonus = "";
	std::string RangedAttackBonus = "";

	std::string MeleeWeaponName = "";
	std::string RangedWeaponName = "";
	MeleeAttack MAttack;
	RangedAttack RAttack;

	bool MAttackPossible = true;
	bool RAttackPossible = true;
	//do what would show for melee
	if (a_ActiveUnit.GetEquipmentInSlot(MAINHAND) != nullptr && a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->IsMeleeWeapon())
	{
			MeleeWeaponName = a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetName();
			MeleeAttackBonus = std::to_string(MAttack.CalcTotalAttackBonus(a_ActiveUnit));
	}
	else if (a_ActiveUnit.GetEquipmentInSlot(OFFHAND) != nullptr && a_ActiveUnit.GetEquipmentInSlot(OFFHAND)->IsMeleeWeapon()==true)
	{
				a_ActiveUnit.SwapWeaponHands();
				MeleeWeaponName = a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetName();
				MeleeAttackBonus = std::to_string(MAttack.CalcTotalAttackBonus(a_ActiveUnit));
				a_ActiveUnit.SwapWeaponHands();
	}
	else
	{
		MeleeWeaponName = a_ActiveUnit.GetUnarmedStrike().GetName();
		MeleeAttackBonus = std::to_string(MAttack.CalcTotalAttackBonus(a_ActiveUnit));
	}

	//do what would show for ranged
	if (a_ActiveUnit.GetEquipmentInSlot(MAINHAND) != nullptr && a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->IsRangedWeapon()==true)
	{
			RangedWeaponName = a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetName();
			RangedAttackBonus = std::to_string(RAttack.CalcTotalAttackBonus(a_ActiveUnit));
		
	}else if (a_ActiveUnit.GetEquipmentInSlot(OFFHAND) != nullptr && a_ActiveUnit.GetEquipmentInSlot(OFFHAND)->IsRangedWeapon())
		{
				a_ActiveUnit.SwapWeaponHands();
				RangedWeaponName = a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetName();
				RangedAttackBonus =std::to_string(RAttack.CalcTotalAttackBonus(a_ActiveUnit));
				a_ActiveUnit.SwapWeaponHands();
		}
	else
	{
		RAttackPossible = false;
	}
	

	//attack is attackroll m_label so will determine attack roll and display it alongside 1d20
	MeleeLabelStore = MeleeWeaponName + ": 1d20 + " + MeleeAttackBonus;
	RangedLabelStore = RangedWeaponName + ": 1d20 + " + RangedAttackBonus;

	if (MAttackPossible == false)
	{
		MeleeLabelStore = "No Melee Attack Possible";
	}

	if (RAttackPossible == false)
	{
		RangedLabelStore = "No Ranged Attack Possible";
	}
	return std::make_pair(MeleeLabelStore, RangedLabelStore);
}

std::pair<std::string, std::string> EntityInfoDisplay::DetermineDamageLabels(EntityClass a_ActiveUnit, EncounterInstance & a_Instance)
{
	std::string MeleeLabelStore = "";
	std::string RangedLabelStore = "";

	std::string MeleeDamageBonus = "";
	std::string RangedDamageBonus = "";

	std::string MeleeDamageDice = "";
	std::string RangedDamageDice = "";

	std::string MeleeWeaponName = "";
	std::string RangedWeaponName = "";
	MeleeAttack MAttack;
	RangedAttack RAttack;

	bool MAttackPossible = true;
	bool RAttackPossible = true;
	//do what would show for melee
	if (a_ActiveUnit.GetEquipmentInSlot(MAINHAND) != nullptr && a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->IsMeleeWeapon())
	{
		MeleeWeaponName = a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetName();
		MeleeDamageBonus = std::to_string(MAttack.CalcTotalDamageBonus(a_ActiveUnit));
		MeleeDamageDice = std::to_string(a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetDamageDice().first) + "d" + std::to_string(a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetDamageDice().second);
	}
	else if (a_ActiveUnit.GetEquipmentInSlot(OFFHAND) != nullptr && a_ActiveUnit.GetEquipmentInSlot(OFFHAND)->IsMeleeWeapon())
	{
				a_ActiveUnit.SwapWeaponHands();
				MeleeWeaponName = a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetName();
				MeleeDamageBonus = std::to_string(MAttack.CalcTotalDamageBonus(a_ActiveUnit));
				MeleeDamageDice = std::to_string(a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetDamageDice().first) + "d" + std::to_string(a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetDamageDice().second);
				a_ActiveUnit.SwapWeaponHands();
	}
	else
	{
		MeleeWeaponName = a_ActiveUnit.GetUnarmedStrike().GetName();
		MeleeDamageBonus = std::to_string(MAttack.CalcTotalDamageBonus(a_ActiveUnit));
		MeleeDamageDice = std::to_string(a_ActiveUnit.GetUnarmedStrike().GetDamageDice().first) + "d" + std::to_string(a_ActiveUnit.GetUnarmedStrike().GetDamageDice().second);
	}

	//do what would show for ranged
	if (a_ActiveUnit.GetEquipmentInSlot(MAINHAND) != nullptr && a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->IsRangedWeapon())
	{
			RangedWeaponName = a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetName();
			RangedDamageBonus = std::to_string(RAttack.CalcTotalDamageBonus(a_ActiveUnit, a_Instance));
			RangedDamageDice = std::to_string(a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetDamageDice().first) + "d" + std::to_string(a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetDamageDice().second);
	}
	else if (a_ActiveUnit.GetEquipmentInSlot(OFFHAND) != nullptr && a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->IsRangedWeapon())
	{
			a_ActiveUnit.SwapWeaponHands();
			RangedWeaponName = a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetName();
			RangedDamageBonus = std::to_string(RAttack.CalcTotalDamageBonus(a_ActiveUnit, a_Instance));
			RangedDamageDice = std::to_string(a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetDamageDice().first) + "d" + std::to_string(a_ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetDamageDice().second);
			a_ActiveUnit.SwapWeaponHands();
	}
	else
	{
		RAttackPossible = false;
	}


	//attack is attackroll m_label so will determine attack roll and display it alongside 1d20
	MeleeLabelStore = MeleeWeaponName + ": " + MeleeDamageDice + "+" +MeleeDamageBonus;
	RangedLabelStore = RangedWeaponName + ": " + RangedDamageDice + "+" + RangedDamageBonus;

	if (MAttackPossible == false)
	{
		MeleeLabelStore = "No Melee Attack Possible";
	}

	if (RAttackPossible == false)
	{
		RangedLabelStore = "No Ranged Attack Possible";
	}
	return std::make_pair(MeleeLabelStore, RangedLabelStore);
}

std::string EntityInfoDisplay::DetermineHitPointsLabel(EntityClass a_ActiveUnit, EncounterInstance & a_Instance)
{
	std::string HitPointsLabel = "";
	std::string MaxHP = "";
	std::string CurrentHP = "";

	CurrentHP = std::to_string(a_ActiveUnit.GetHitPoints());
	MaxHP = std::to_string(a_ActiveUnit.GetMaxHitPoints());
	HitPointsLabel = "m_HitPoints: " + CurrentHP + "/" + MaxHP;
	return HitPointsLabel;
}

std::string EntityInfoDisplay::DetermineACLabel(EntityClass a_ActiveUnit, EncounterInstance & a_Instance)
{
	std::string ACLabelStore = "";
	std::string AC = "";

	AC = std::to_string(a_ActiveUnit.GetArmorClass());
	ACLabelStore = "m_ArmorClass: " + AC;
	return ACLabelStore;
}

std::string EntityInfoDisplay::DetermineAttackLeftLabel(EntityClass a_ActiveUnit, EncounterInstance & a_Instance)
{
	std::string AttackLeftLabelStore = "";
	std::string AttackLeft = "";
	bool AttackLeftBool = a_ActiveUnit.GetAttackLeft();

	if (AttackLeftBool == true)
	{
		AttackLeft = "Yes";
	}
	else
	{
		AttackLeft = "No";
	}
	AttackLeftLabelStore = "Attack Available: " + AttackLeft;

	return AttackLeftLabelStore;
}

std::string EntityInfoDisplay::DetermineMovementLabel(EntityClass a_ActiveUnit, EncounterInstance &a_Instance)
{
	std::string m_MovementLeftLabel = "";
	std::string MovementLeftNumber = "";

	MovementLeftNumber = std::to_string(a_ActiveUnit.GetMovementLeft());
	m_MovementLeftLabel = "Movement Remaining: " + MovementLeftNumber + " tiles";
	return m_MovementLeftLabel;
}

void EntityInfoDisplay::DetermineAllLabels(EntityClass a_ActiveUnit, EncounterInstance& a_Instance)
{
	SetNameLabel(DetermineNameLabel(a_ActiveUnit));

	//melee is first, ranged second
	std::pair<std::string, std::string> AttackLabels = DetermineAttackLabels(a_ActiveUnit, a_Instance);
	std::pair<std::string, std::string> DamageLabels = DetermineDamageLabels(a_ActiveUnit, a_Instance);

	SetAttackAndDamageMelee(std::make_pair(AttackLabels.first, DamageLabels.first));
	SetAttackAndDamageRanged(std::make_pair(AttackLabels.second, DamageLabels.second));

	SetACLabel(DetermineACLabel(a_ActiveUnit, a_Instance));
	SetAttackLeftLabel(DetermineAttackLeftLabel(a_ActiveUnit, a_Instance));
	SetMovementLabel(DetermineMovementLabel(a_ActiveUnit, a_Instance));
	SetHitPointsLabel(DetermineHitPointsLabel(a_ActiveUnit, a_Instance));

}

//texture functions start

void EntityInfoDisplay::SetAllTextures(SDL_Renderer *& a_renderer)
{
	SetNameLabelTexture(m_NameLabel, a_renderer);
	SetACLabelTexture(m_ACLabel, a_renderer);
	SetAttackAndDamageMeleeTexture(std::make_pair(m_MeleeAttackLabel, m_MeleeDamageLabel), a_renderer);
	SetAttackAndDamageRangedTexture(std::make_pair(m_RangedAttackLabel,m_RangedDamageLabel), a_renderer);
	SetHitPointsLabelTexture(m_HitpointsLabel, a_renderer);
	SetMovementLabelTexture(m_MovementLeftLabel, a_renderer);
	SetAttackLeftLabelTexture(m_AttackLeftLabel, a_renderer);
}

void EntityInfoDisplay::SetNameLabelTexture(std::string a_passed, SDL_Renderer *& a_renderer)
{
	m_NameLabel_Texture.loadFromRenderedText(a_passed, m_InfoTextColor, a_renderer, m_InfoFont);
}

void EntityInfoDisplay::SetACLabelTexture(std::string a_passed, SDL_Renderer *& a_renderer)
{
	m_ACLabel_Texture.loadFromRenderedText(a_passed, m_InfoTextColor, a_renderer, m_InfoFont);
}

void EntityInfoDisplay::SetAttackAndDamageMeleeTexture(std::pair<std::string, std::string> a_passed, SDL_Renderer *& a_renderer)
{
	m_MeleeAttackLabel_Texture.loadFromRenderedText(a_passed.first, m_InfoTextColor, a_renderer, m_InfoFont);
	m_MeleeAttackDamageLabel_Texture.loadFromRenderedText(a_passed.second, m_InfoTextColor, a_renderer, m_InfoFont);
}


void EntityInfoDisplay::SetAttackAndDamageRangedTexture(std::pair<std::string, std::string> a_passed, SDL_Renderer *& a_renderer)
{
	//std::string FullString = a_passed.first + "    " + a_passed.second;
	m_RangedAttackLabel_Texture.loadFromRenderedText(a_passed.first, m_InfoTextColor, a_renderer, m_InfoFont);
	m_RangedAttackDamageLabel_Texture.loadFromRenderedText(a_passed.second, m_InfoTextColor, a_renderer, m_InfoFont);
}

void EntityInfoDisplay::SetHitPointsLabelTexture(std::string a_passed, SDL_Renderer *& a_renderer)
{
	m_HitpointsLabel_Texture.loadFromRenderedText(a_passed, m_InfoTextColor, a_renderer, m_InfoFont);
}

void EntityInfoDisplay::SetMovementLabelTexture(std::string a_passed, SDL_Renderer *& a_renderer)
{
	m_MovementLeftLabel_Texture.loadFromRenderedText(a_passed, m_InfoTextColor, a_renderer, m_InfoFont);
}

void EntityInfoDisplay::SetAttackLeftLabelTexture(std::string a_passed, SDL_Renderer *& a_renderer)
{
	m_AttackLeftLabel_Texture.loadFromRenderedText(a_passed, m_InfoTextColor, a_renderer, m_InfoFont);
}

void EntityInfoDisplay::RenderPanel(SDL_Renderer *& a_renderer)
{
	int CurrentY = m_PanelConstraints.h * 1 / 10;
	int CurrentXOffset = 0;

	CurrentXOffset = m_PanelConstraints.x + ((m_PanelConstraints.w * 0.5) - m_NameLabel_Texture.getWidth() * 0.5);
	m_NameLabel_Texture.renderTile(CurrentXOffset, CurrentY, a_renderer);
	CurrentY += m_spacing;

	CurrentXOffset = m_PanelConstraints.x + ((m_PanelConstraints.w * 0.5) - m_MeleeAttackLabel_Texture.getWidth() * 0.5);
	m_MAttack_Texture.renderTile(CurrentXOffset, CurrentY, a_renderer);
	CurrentY += m_spacing;
	m_MeleeAttackLabel_Texture.renderTile(CurrentXOffset, CurrentY, a_renderer);
	CurrentY += m_spacing;
	//CurrentXOffset = m_PanelConstraints.a_x + ((m_PanelConstraints.a_w * 0.5) - m_MeleeAttackDamageLabel_Texture.getWidth() * 0.5);
	m_MeleeAttackDamageLabel_Texture.renderTile(CurrentXOffset, CurrentY, a_renderer);
	CurrentY += m_spacing;
	CurrentY += m_spacing;

	CurrentXOffset = m_PanelConstraints.x + ((m_PanelConstraints.w * 0.5) - m_RangedAttackLabel_Texture.getWidth() * 0.5);
	m_RAttack_Texture.renderTile(CurrentXOffset, CurrentY, a_renderer);
	CurrentY += m_spacing;
	m_RangedAttackLabel_Texture.renderTile(CurrentXOffset, CurrentY, a_renderer);
	CurrentY += m_spacing;
	m_RangedAttackDamageLabel_Texture.renderTile(CurrentXOffset, CurrentY, a_renderer);
	CurrentY += m_spacing;
	CurrentY += m_spacing;

	CurrentXOffset = m_PanelConstraints.x + ((m_PanelConstraints.w * 0.5) - m_HitpointsLabel_Texture.getWidth() * 0.5);
	m_HitpointsLabel_Texture.renderTile(CurrentXOffset, CurrentY, a_renderer);
	CurrentY += m_spacing;
	
	CurrentXOffset = m_PanelConstraints.x + ((m_PanelConstraints.w * 0.5) - m_ACLabel_Texture.getWidth() * 0.5);
	m_ACLabel_Texture.renderTile(CurrentXOffset, CurrentY, a_renderer);
	CurrentY += m_spacing;

	CurrentXOffset = m_PanelConstraints.x + ((m_PanelConstraints.w * 0.5) - m_MovementLeftLabel_Texture.getWidth() * 0.5);
	m_MovementLeftLabel_Texture.renderTile(CurrentXOffset, CurrentY, a_renderer);
	CurrentY += m_spacing;

	CurrentXOffset = m_PanelConstraints.x + ((m_PanelConstraints.w * 0.5) - m_AttackLeftLabel_Texture.getWidth() * 0.5);
	m_AttackLeftLabel_Texture.renderTile(CurrentXOffset, CurrentY, a_renderer);
	CurrentY += m_spacing;

}
