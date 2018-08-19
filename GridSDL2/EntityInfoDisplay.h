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
	void Setup(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_Font* Font, SDL_Renderer *& renderer);

	std::string DetermineNameLabel(EntityClass ActiveUnit);
	void SetNameLabel(std::string NamePassed) { NameLabel = NamePassed; }
	void SetNameLabelTexture(std::string passed, SDL_Renderer *& renderer);

	std::pair<std::string, std::string> DetermineAttackLabels(EntityClass ActiveUnit, EncounterInstance & Instance);

	std::pair<std::string, std::string> DetermineDamageLabels(EntityClass ActiveUnit, EncounterInstance & Instance);
	
	void SetAttackAndDamageMelee(std::pair<std::string, std::string> passed) { MeleeAttackLabel = passed.first; MeleeDamageLabel = passed.second; }
	void SetAttackAndDamageRanged(std::pair<std::string, std::string> passed) { RangedAttackLabel = passed.first; RangedDamageLabel = passed.second; }
	
	void SetAttackAndDamageMeleeTexture(std::pair<std::string, std::string> passed, SDL_Renderer *& renderer);
	void SetAttackAndDamageRangedTexture(std::pair<std::string, std::string> passed, SDL_Renderer *& renderer);
	
	std::string DetermineHitPointsLabel(EntityClass ActiveUnit, EncounterInstance & Instance);
	void SetHitPointsLabel(std::string passed) { HitpointsLabel = passed; }
	void SetHitPointsLabelTexture(std::string HitPointsLabel, SDL_Renderer *& renderer);

	std::string DetermineACLabel(EntityClass ActiveUnit, EncounterInstance & Instance);
	void SetACLabel(std::string passed) { ACLabel = passed; }
	void SetACLabelTexture(std::string ACLabel, SDL_Renderer *& renderer);

	std::string DetermineMovementLabel(EntityClass ActiveUnit, EncounterInstance & Instance);
	void SetMovementLabel(std::string passed) { MovementLeftLabel = passed; }
	void SetMovementLabelTexture(std::string MovementLabel, SDL_Renderer *& renderer);

	std::string DetermineAttackLeftLabel(EntityClass ActiveUnit, EncounterInstance & Instance);
	void SetAttackLeftLabel(std::string passed) { AttackLeftLabel = passed; }
	void SetAttackLeftLabelTexture(std::string AttackLeftLabel, SDL_Renderer *& renderer);

	void SetPanelConstraints(int x, int y, int w, int h);
	void SetPanelConstraints(SDL_Rect other);

	int GetXPanelConstraint() { return PanelConstraints.x; }
	int GetYPanelConstraint() { return PanelConstraints.y; }

	void DetermineAllLabels(EntityClass ActiveUnit, EncounterInstance & Instance); //determines and sets all labels
	void SetAllTextures(SDL_Renderer *& renderer);

	void RenderPanel(SDL_Renderer *& renderer);

	void SetFont(TTF_Font* Font);
	void HandleEvents(SDL_Event& e);

private:
	SDL_Rect PanelConstraints;
	LTexture NameLabel_Texture;
	LTexture RAttack_Texture;
	LTexture MAttack_Texture;
	LTexture MeleeAttackLabel_Texture;
	LTexture MeleeAttackDamageLabel_Texture;
	LTexture RangedAttackLabel_Texture;
	LTexture RangedAttackDamageLabel_Texture;
	LTexture HitpointsLabel_Texture;
	LTexture ACLabel_Texture;
	LTexture MovementLeftLabel_Texture;
	LTexture AttackLeftLabel_Texture;

	std::string NameLabel="";

	std::string MeleeLabel="Melee Attack:";
	std::string MeleeAttackLabel="";
	std::string MeleeDamageLabel="";

	std::string RangedLabel="Ranged AttacK:";
	std::string RangedAttackLabel=""; 
	std::string RangedDamageLabel="";

	std::string HitpointsLabel="";
	std::string ACLabel="";
	std::string MovementLeftLabel="";
	std::string AttackLeftLabel="";
	TTF_Font *InfoFont;
	SDL_Color InfoTextColor = { 0, 0, 0 };
	
	std::string texturePath;
	int spacing = 20;

};