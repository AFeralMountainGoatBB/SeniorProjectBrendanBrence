#include "EntityInfoDisplay.h"
#include "EntityClass.h"
#include "AttackClass.h"
#include "EncounterInstance.h"

EntityInfoDisplay::EntityInfoDisplay()
{

}
EntityInfoDisplay::EntityInfoDisplay(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_Font* Font)
{
	PanelConstraints.x = viewport.x;
	PanelConstraints.y = viewport.y;
	PanelConstraints.w = viewport.w;
	PanelConstraints.h = viewport.h;

	InfoFont = Font;

}

void EntityInfoDisplay::SetPanelConstraints(int x, int y, int w, int h)
{
	PanelConstraints.x = x;
	PanelConstraints.y = y;
	PanelConstraints.w = w;
	PanelConstraints.h = h;
}

void EntityInfoDisplay::SetPanelConstraints(SDL_Rect other)
{
	PanelConstraints = other;
	//	std::cout << "Constraints for log: x:" << LogConstraints.x << " y: " << LogConstraints.y << std::endl;
}


void EntityInfoDisplay::Setup(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_Font* Font, SDL_Renderer *& renderer)
{
	PanelConstraints.x = viewport.x;
	PanelConstraints.y = viewport.y;
	PanelConstraints.w = viewport.w;
	PanelConstraints.h = viewport.h;

	InfoFont = Font;

	MAttack_Texture.loadFromRenderedText(MeleeLabel, InfoTextColor, renderer, InfoFont);
	RAttack_Texture.loadFromRenderedText(RangedLabel, InfoTextColor, renderer, InfoFont);
}

std::string EntityInfoDisplay::DetermineNameLabel(EntityClass ActiveUnit)
{
	return ActiveUnit.GetName();
}

std::pair<std::string, std::string> EntityInfoDisplay::DetermineAttackLabels(EntityClass ActiveUnit, EncounterInstance & Instance)
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
	if (ActiveUnit.GetEquipmentInSlot(MAINHAND) != nullptr && ActiveUnit.GetEquipmentInSlot(MAINHAND)->IsMeleeWeapon())
	{
			MeleeWeaponName = ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetName();
			MeleeAttackBonus = std::to_string(MAttack.CalcTotalAttackBonus(ActiveUnit));
	}
	else if (ActiveUnit.GetEquipmentInSlot(OFFHAND) != nullptr && ActiveUnit.GetEquipmentInSlot(OFFHAND)->IsMeleeWeapon()==true)
	{
				ActiveUnit.SwapWeaponHands();
				MeleeWeaponName = ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetName();
				MeleeAttackBonus = std::to_string(MAttack.CalcTotalAttackBonus(ActiveUnit));
				ActiveUnit.SwapWeaponHands();
	}
	else
	{
		MeleeWeaponName = ActiveUnit.GetUnarmedStrike().GetName();
		MeleeAttackBonus = std::to_string(MAttack.CalcTotalAttackBonus(ActiveUnit));
	}

	//do what would show for ranged
	if (ActiveUnit.GetEquipmentInSlot(MAINHAND) != nullptr && ActiveUnit.GetEquipmentInSlot(MAINHAND)->IsRangedWeapon()==true)
	{
			RangedWeaponName = ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetName();
			RangedAttackBonus = std::to_string(RAttack.CalcTotalAttackBonus(ActiveUnit));
		
	}else if (ActiveUnit.GetEquipmentInSlot(OFFHAND) != nullptr && ActiveUnit.GetEquipmentInSlot(OFFHAND)->IsRangedWeapon())
		{
				ActiveUnit.SwapWeaponHands();
				RangedWeaponName = ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetName();
				RangedAttackBonus =std::to_string(RAttack.CalcTotalAttackBonus(ActiveUnit));
				ActiveUnit.SwapWeaponHands();
		}
	else
	{
		RAttackPossible = false;
	}
	

	//attack is attackroll label so will determine attack roll and display it alongside 1d20
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

std::pair<std::string, std::string> EntityInfoDisplay::DetermineDamageLabels(EntityClass ActiveUnit, EncounterInstance & Instance)
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
	if (ActiveUnit.GetEquipmentInSlot(MAINHAND) != nullptr && ActiveUnit.GetEquipmentInSlot(MAINHAND)->IsMeleeWeapon())
	{
		MeleeWeaponName = ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetName();
		MeleeDamageBonus = std::to_string(MAttack.CalcTotalDamageBonus(ActiveUnit));
		MeleeDamageDice = std::to_string(ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetDamageDice().first) + "d" + std::to_string(ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetDamageDice().second);
	}
	else if (ActiveUnit.GetEquipmentInSlot(OFFHAND) != nullptr && ActiveUnit.GetEquipmentInSlot(OFFHAND)->IsMeleeWeapon())
	{
				ActiveUnit.SwapWeaponHands();
				MeleeWeaponName = ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetName();
				MeleeDamageBonus = std::to_string(MAttack.CalcTotalDamageBonus(ActiveUnit));
				MeleeDamageDice = std::to_string(ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetDamageDice().first) + "d" + std::to_string(ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetDamageDice().second);
				ActiveUnit.SwapWeaponHands();
	}
	else
	{
		MeleeWeaponName = ActiveUnit.GetUnarmedStrike().GetName();
		MeleeDamageBonus = std::to_string(MAttack.CalcTotalDamageBonus(ActiveUnit));
		MeleeDamageDice = std::to_string(ActiveUnit.GetUnarmedStrike().GetDamageDice().first) + "d" + std::to_string(ActiveUnit.GetUnarmedStrike().GetDamageDice().second);
	}

	//do what would show for ranged
	if (ActiveUnit.GetEquipmentInSlot(MAINHAND) != nullptr && ActiveUnit.GetEquipmentInSlot(MAINHAND)->IsRangedWeapon())
	{
			RangedWeaponName = ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetName();
			RangedDamageBonus = std::to_string(RAttack.CalcTotalDamageBonus(ActiveUnit, Instance));
			RangedDamageDice = std::to_string(ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetDamageDice().first) + "d" + std::to_string(ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetDamageDice().second);
	}
	else if (ActiveUnit.GetEquipmentInSlot(OFFHAND) != nullptr && ActiveUnit.GetEquipmentInSlot(MAINHAND)->IsRangedWeapon())
	{
			ActiveUnit.SwapWeaponHands();
			RangedWeaponName = ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetName();
			RangedDamageBonus = std::to_string(RAttack.CalcTotalDamageBonus(ActiveUnit, Instance));
			RangedDamageDice = std::to_string(ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetDamageDice().first) + "d" + std::to_string(ActiveUnit.GetEquipmentInSlot(MAINHAND)->GetDamageDice().second);
			ActiveUnit.SwapWeaponHands();
	}
	else
	{
		RAttackPossible = false;
	}


	//attack is attackroll label so will determine attack roll and display it alongside 1d20
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

std::string EntityInfoDisplay::DetermineHitPointsLabel(EntityClass ActiveUnit, EncounterInstance & Instance)
{
	std::string HitPointsLabel = "";
	std::string MaxHP = "";
	std::string CurrentHP = "";

	CurrentHP = std::to_string(ActiveUnit.GetHitPoints());
	MaxHP = std::to_string(ActiveUnit.GetMaxHitPoints());
	HitPointsLabel = "HitPoints: " + CurrentHP + "/" + MaxHP;
	return HitPointsLabel;
}

std::string EntityInfoDisplay::DetermineACLabel(EntityClass ActiveUnit, EncounterInstance & Instance)
{
	std::string ACLabelStore = "";
	std::string AC = "";

	AC = std::to_string(ActiveUnit.GetArmorClass());
	ACLabelStore = "ArmorClass: " + AC;
	return ACLabelStore;
}

std::string EntityInfoDisplay::DetermineAttackLeftLabel(EntityClass ActiveUnit, EncounterInstance & Instance)
{
	std::string AttackLeftLabelStore = "";
	std::string AttackLeft = "";
	bool AttackLeftBool = ActiveUnit.GetAttackLeft();

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

std::string EntityInfoDisplay::DetermineMovementLabel(EntityClass ActiveUnit, EncounterInstance &Instance)
{
	std::string MovementLeftLabel = "";
	std::string MovementLeftNumber = "";

	MovementLeftNumber = std::to_string(ActiveUnit.GetMovementLeft());
	MovementLeftLabel = "Movement Remaining: " + MovementLeftNumber + " tiles";
	return MovementLeftLabel;
}

void EntityInfoDisplay::DetermineAllLabels(EntityClass ActiveUnit, EncounterInstance& Instance)
{
	SetNameLabel(DetermineNameLabel(ActiveUnit));

	//melee is first, ranged second
	std::pair<std::string, std::string> AttackLabels = DetermineAttackLabels(ActiveUnit, Instance);
	std::pair<std::string, std::string> DamageLabels = DetermineDamageLabels(ActiveUnit, Instance);

	SetAttackAndDamageMelee(std::make_pair(AttackLabels.first, DamageLabels.first));
	SetAttackAndDamageRanged(std::make_pair(AttackLabels.second, DamageLabels.second));

	SetACLabel(DetermineACLabel(ActiveUnit, Instance));
	SetAttackLeftLabel(DetermineAttackLeftLabel(ActiveUnit, Instance));
	SetMovementLabel(DetermineMovementLabel(ActiveUnit, Instance));
	SetHitPointsLabel(DetermineHitPointsLabel(ActiveUnit, Instance));

}

//texture functions start

void EntityInfoDisplay::SetAllTextures(SDL_Renderer *& renderer)
{
	SetNameLabelTexture(NameLabel, renderer);
	SetACLabelTexture(ACLabel, renderer);
	SetAttackAndDamageMeleeTexture(std::make_pair(MeleeAttackLabel, MeleeDamageLabel), renderer);
	SetAttackAndDamageRangedTexture(std::make_pair(RangedAttackLabel,RangedDamageLabel), renderer);
	SetHitPointsLabelTexture(HitpointsLabel, renderer);
	SetMovementLabelTexture(MovementLeftLabel, renderer);
	SetAttackLeftLabelTexture(AttackLeftLabel, renderer);
}

void EntityInfoDisplay::SetNameLabelTexture(std::string passed, SDL_Renderer *& renderer)
{
	NameLabel_Texture.loadFromRenderedText(passed, InfoTextColor, renderer, InfoFont);
}

void EntityInfoDisplay::SetACLabelTexture(std::string passed, SDL_Renderer *& renderer)
{
	ACLabel_Texture.loadFromRenderedText(passed, InfoTextColor, renderer, InfoFont);
}

void EntityInfoDisplay::SetAttackAndDamageMeleeTexture(std::pair<std::string, std::string> passed, SDL_Renderer *& renderer)
{
	MeleeAttackLabel_Texture.loadFromRenderedText(passed.first, InfoTextColor, renderer, InfoFont);
	MeleeAttackDamageLabel_Texture.loadFromRenderedText(passed.second, InfoTextColor, renderer, InfoFont);
}


void EntityInfoDisplay::SetAttackAndDamageRangedTexture(std::pair<std::string, std::string> passed, SDL_Renderer *& renderer)
{
	//std::string FullString = passed.first + "    " + passed.second;
	RangedAttackLabel_Texture.loadFromRenderedText(passed.first, InfoTextColor, renderer, InfoFont);
	RangedAttackDamageLabel_Texture.loadFromRenderedText(passed.second, InfoTextColor, renderer, InfoFont);
}

void EntityInfoDisplay::SetHitPointsLabelTexture(std::string passed, SDL_Renderer *& renderer)
{
	HitpointsLabel_Texture.loadFromRenderedText(passed, InfoTextColor, renderer, InfoFont);
}

void EntityInfoDisplay::SetMovementLabelTexture(std::string passed, SDL_Renderer *& renderer)
{
	MovementLeftLabel_Texture.loadFromRenderedText(passed, InfoTextColor, renderer, InfoFont);
}

void EntityInfoDisplay::SetAttackLeftLabelTexture(std::string passed, SDL_Renderer *& renderer)
{
	AttackLeftLabel_Texture.loadFromRenderedText(passed, InfoTextColor, renderer, InfoFont);
}

void EntityInfoDisplay::RenderPanel(SDL_Renderer *& renderer)
{
	int CurrentY = PanelConstraints.h * 1 / 10;
	int CurrentXOffset = 0;

	CurrentXOffset = PanelConstraints.x + ((PanelConstraints.w * 0.5) - NameLabel_Texture.getWidth() * 0.5);
	NameLabel_Texture.renderTile(CurrentXOffset, CurrentY, renderer);
	CurrentY += spacing;

	CurrentXOffset = PanelConstraints.x + ((PanelConstraints.w * 0.5) - MeleeAttackLabel_Texture.getWidth() * 0.5);
	MAttack_Texture.renderTile(CurrentXOffset, CurrentY, renderer);
	CurrentY += spacing;
	MeleeAttackLabel_Texture.renderTile(CurrentXOffset, CurrentY, renderer);
	CurrentY += spacing;
	//CurrentXOffset = PanelConstraints.x + ((PanelConstraints.w * 0.5) - MeleeAttackDamageLabel_Texture.getWidth() * 0.5);
	MeleeAttackDamageLabel_Texture.renderTile(CurrentXOffset, CurrentY, renderer);
	CurrentY += spacing;
	CurrentY += spacing;

	CurrentXOffset = PanelConstraints.x + ((PanelConstraints.w * 0.5) - RangedAttackLabel_Texture.getWidth() * 0.5);
	RAttack_Texture.renderTile(CurrentXOffset, CurrentY, renderer);
	CurrentY += spacing;
	RangedAttackLabel_Texture.renderTile(CurrentXOffset, CurrentY, renderer);
	CurrentY += spacing;
	RangedAttackDamageLabel_Texture.renderTile(CurrentXOffset, CurrentY, renderer);
	CurrentY += spacing;
	CurrentY += spacing;

	CurrentXOffset = PanelConstraints.x + ((PanelConstraints.w * 0.5) - HitpointsLabel_Texture.getWidth() * 0.5);
	HitpointsLabel_Texture.renderTile(CurrentXOffset, CurrentY, renderer);
	CurrentY += spacing;
	
	CurrentXOffset = PanelConstraints.x + ((PanelConstraints.w * 0.5) - ACLabel_Texture.getWidth() * 0.5);
	ACLabel_Texture.renderTile(CurrentXOffset, CurrentY, renderer);
	CurrentY += spacing;

	CurrentXOffset = PanelConstraints.x + ((PanelConstraints.w * 0.5) - MovementLeftLabel_Texture.getWidth() * 0.5);
	MovementLeftLabel_Texture.renderTile(CurrentXOffset, CurrentY, renderer);
	CurrentY += spacing;

	CurrentXOffset = PanelConstraints.x + ((PanelConstraints.w * 0.5) - AttackLeftLabel_Texture.getWidth() * 0.5);
	AttackLeftLabel_Texture.renderTile(CurrentXOffset, CurrentY, renderer);
	CurrentY += spacing;

}
