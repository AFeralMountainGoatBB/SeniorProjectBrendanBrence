#pragma once
#include "GeneralHeaders.h"
#include "GeneralHeaders.h"
#include "SharedEnums.h"
#include "Texture.h"
#include "StaticFunctions.h"
#include "Button.h"

class EntityClass;
class EncounterInstance;

class EntityInfoDisplay
{
public:
	//Panel functions
	EntityInfoDisplay();
	EntityInfoDisplay(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_Font* Font);
	void Setup(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_Font* Font, SDL_Renderer *& m_renderer);

	std::string DetermineNameLabel(EntityClass ActiveUnit);
	void SetNameLabel(std::string NamePassed) { m_NameLabel = NamePassed; }
	void SetNameLabelTexture(std::string passed, SDL_Renderer *& m_renderer);

	std::pair<std::string, std::string> DetermineAttackLabels(EntityClass ActiveUnit, EncounterInstance & Instance);

	std::pair<std::string, std::string> DetermineDamageLabels(EntityClass ActiveUnit, EncounterInstance & Instance);
	
	void SetAttackAndDamageMelee(std::pair<std::string, std::string> passed) { m_MeleeAttackLabel = passed.first; m_MeleeDamageLabel = passed.second; }
	void SetAttackAndDamageRanged(std::pair<std::string, std::string> passed) { m_RangedAttackLabel = passed.first; m_RangedDamageLabel = passed.second; }
	
	void SetAttackAndDamageMeleeTexture(std::pair<std::string, std::string> passed, SDL_Renderer *& m_renderer);
	void SetAttackAndDamageRangedTexture(std::pair<std::string, std::string> passed, SDL_Renderer *& m_renderer);
	
	std::string DetermineHitPointsLabel(EntityClass ActiveUnit, EncounterInstance & Instance);
	void SetHitPointsLabel(std::string passed) { m_HitpointsLabel = passed; }
	void SetHitPointsLabelTexture(std::string HitPointsLabel, SDL_Renderer *& m_renderer);

	std::string DetermineACLabel(EntityClass ActiveUnit, EncounterInstance & Instance);
	void SetACLabel(std::string passed) { m_ACLabel = passed; }
	void SetACLabelTexture(std::string m_ACLabel, SDL_Renderer *& m_renderer);

	std::string DetermineMovementLabel(EntityClass ActiveUnit, EncounterInstance & Instance);
	void SetMovementLabel(std::string passed) { m_MovementLeftLabel = passed; }
	void SetMovementLabelTexture(std::string MovementLabel, SDL_Renderer *& m_renderer);

	std::string DetermineAttackLeftLabel(EntityClass ActiveUnit, EncounterInstance & Instance);
	void SetAttackLeftLabel(std::string passed) { m_AttackLeftLabel = passed; }
	void SetAttackLeftLabelTexture(std::string m_AttackLeftLabel, SDL_Renderer *& m_renderer);

	void SetPanelConstraints(int x, int y, int w, int h);
	void SetPanelConstraints(SDL_Rect other);

	int GetXPanelConstraint() { return m_PanelConstraints.x; }
	int GetYPanelConstraint() { return m_PanelConstraints.y; }

	void DetermineAllLabels(EntityClass ActiveUnit, EncounterInstance & Instance); //determines and sets all labels
	void SetAllTextures(SDL_Renderer *& m_renderer);

	void RenderPanel(SDL_Renderer *& m_renderer);

	void SetFont(TTF_Font* Font);
	void HandleEvents(SDL_Event& m_event);

private:
	SDL_Rect m_PanelConstraints;
	LTexture m_NameLabel_Texture;
	LTexture m_RAttack_Texture;
	LTexture m_MAttack_Texture;
	LTexture m_MeleeAttackLabel_Texture;
	LTexture m_MeleeAttackDamageLabel_Texture;
	LTexture m_RangedAttackLabel_Texture;
	LTexture m_RangedAttackDamageLabel_Texture;
	LTexture m_HitpointsLabel_Texture;
	LTexture m_ACLabel_Texture;
	LTexture m_MovementLeftLabel_Texture;
	LTexture m_AttackLeftLabel_Texture;

	std::string m_NameLabel="";

	std::string m_MeleeLabel="Melee Attack:";
	std::string m_MeleeAttackLabel="";
	std::string m_MeleeDamageLabel="";

	std::string m_RangedLabel="Ranged AttacK:";
	std::string m_RangedAttackLabel=""; 
	std::string m_RangedDamageLabel="";

	std::string m_HitpointsLabel="";
	std::string m_ACLabel="";
	std::string m_MovementLeftLabel="";
	std::string m_AttackLeftLabel="";
	TTF_Font *m_InfoFont;
	SDL_Color m_InfoTextColor = { 0, 0, 0 };
	
	std::string m_texturePath;
	int m_spacing = 20;

};