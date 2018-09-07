/**********************************************************************************************//**
 * @file	EntityInfoDisplay.h.
 *
 * @brief	Declares the entity information display class
 **************************************************************************************************/

#pragma once
#include "GeneralHeaders.h"
#include "GeneralHeaders.h"
#include "SharedEnums.h"
#include "Texture.h"
#include "StaticFunctions.h"
#include "Button.h"

//fwd declarations to avoid circular dependencies
class EntityClass;
class EncounterInstance;

/**********************************************************************************************//**
 * @class	EntityInfoDisplay
 *
 * @brief	An entity information display.
 *
 * @author	Brendan B
 * @date	9/5/2018
 **************************************************************************************************/

class EntityInfoDisplay
{
public:
	/**********************************************************************************************//**
	 * @fn	EntityInfoDisplay::EntityInfoDisplay();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 **************************************************************************************************/

	EntityInfoDisplay();

	/**********************************************************************************************//**
	 * @fn	EntityInfoDisplay::EntityInfoDisplay(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_Font* Font);
	 *
	 * @brief	Constructor with given params to initialize or setup up necessary information
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	TextureFolderPath	Full pathname of the texture folder file.
	 * @param [in,out]	TextureMap		 	[in,out] If non-null, the texture map.
	 * @param 		  	viewport		 	The viewport.
	 * @param [in,out]	Font			 	If non-null, the font.
	 **************************************************************************************************/

	EntityInfoDisplay(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_Font* Font);

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::Setup(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_Font* Font, SDL_Renderer *& m_renderer);
	 *
	 * @brief	Setup necessary information, gets textures for static labels and sets them
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	TextureFolderPath	Full pathname of the texture folder file.
	 * @param [in,out]	TextureMap		 	[in,out] If non-null, the texture map.
	 * @param 		  	viewport		 	The viewport.
	 * @param [in,out]	Font			 	If non-null, the font.
	 * @param [in,out]	m_renderer		 	[in,out] If non-null, the renderer.
	 **************************************************************************************************/

	void Setup(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_Font* Font, SDL_Renderer *& m_renderer);

	/**********************************************************************************************//**
	 * @fn	std::string EntityInfoDisplay::DetermineNameLabel(EntityClass ActiveUnit);
	 *
	 * @brief	Determine name label, gets active entities name and returns it
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param	ActiveUnit	The active unit name is pulled from
	 *
	 * @return	A std::string that is the active units name
	 **************************************************************************************************/

	std::string DetermineNameLabel(EntityClass ActiveUnit);

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetNameLabel(std::string NamePassed)
	 *
	 * @brief	Sets name label
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param	NamePassed	The name passed.
	 **************************************************************************************************/

	void SetNameLabel(std::string NamePassed) { m_NameLabel = NamePassed; }

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetNameLabelTexture(std::string passed, SDL_Renderer *& m_renderer);
	 *
	 * @brief	Sets name label texture equal to name label
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	passed	  	The passed name in string format
	 * @param [in,out]	m_renderer	[in,out] If non-null, the renderer.
	 **************************************************************************************************/

	void SetNameLabelTexture(std::string passed, SDL_Renderer *& m_renderer);

	/**********************************************************************************************//**
	 * @fn	std::pair<std::string, std::string> EntityInfoDisplay::DetermineAttackLabels(EntityClass ActiveUnit, EncounterInstance & Instance);
	 *
	 * @brief	Determine attack labels, calculates attack bonuses for melee attack and or ranged attack, if possible and sets the labels appropiately
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	ActiveUnit	The active unit.
	 * @param [in,out]	Instance  	The instance.
	 *
	 * @return	A std::pair&lt;std::string,std::string&gt;
	 **************************************************************************************************/

	std::pair<std::string, std::string> DetermineAttackLabels(EntityClass ActiveUnit, EncounterInstance & Instance);

	/**********************************************************************************************//**
	 * @fn	std::pair<std::string, std::string> EntityInfoDisplay::DetermineDamageLabels(EntityClass ActiveUnit, EncounterInstance & Instance);
	 *
	 * @brief	Determine damage labels, calculates damage bonuses for melee attack and or ranged attack, if they are possible, sets labels appropiately
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	ActiveUnit	The active unit.
	 * @param [in,out]	Instance  	The instance.
	 *
	 * @return	A std::pair&lt;std::string,std::string&gt;
	 **************************************************************************************************/

	std::pair<std::string, std::string> DetermineDamageLabels(EntityClass ActiveUnit, EncounterInstance & Instance);

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetAttackAndDamageMelee(std::pair<std::string, std::string> passed)
	 *
	 * @brief	Sets attack and damage melee labels based on pair of passed vals
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param	passed	The passed vals, a pair of strings, first is melee attack second is ranged
	 **************************************************************************************************/

	void SetAttackAndDamageMelee(std::pair<std::string, std::string> passed) { m_MeleeAttackLabel = passed.first; m_MeleeDamageLabel = passed.second; }

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetAttackAndDamageRanged(std::pair<std::string, std::string> passed)
	 *
	 * @brief	Sets attack and damage ranged labels
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param	passed	The passed.
	 **************************************************************************************************/

	void SetAttackAndDamageRanged(std::pair<std::string, std::string> passed) { m_RangedAttackLabel = passed.first; m_RangedDamageLabel = passed.second; }

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetAttackAndDamageMeleeTexture(std::pair<std::string, std::string> passed, SDL_Renderer *& m_renderer);
	 *
	 * @brief	Sets attack and damage melee labels
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	passed	  	The passed pair of strings that represent the attack and damage, first is attack second is damage
	 * @param [in,out]	m_renderer	[in,out] If non-null, the renderer.
	 **************************************************************************************************/

	void SetAttackAndDamageMeleeTexture(std::pair<std::string, std::string> passed, SDL_Renderer *& m_renderer);

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetAttackAndDamageRangedTexture(std::pair<std::string, std::string> passed, SDL_Renderer *& m_renderer);
	 *
	 * @brief	Sets attack and damage ranged textures to passed values
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	passed	  	The passed pair of strings, first is attack, second is damage
	 * @param [in,out]	m_renderer	[in,out] If non-null, the renderer.
	 **************************************************************************************************/

	void SetAttackAndDamageRangedTexture(std::pair<std::string, std::string> passed, SDL_Renderer *& m_renderer);

	/**********************************************************************************************//**
	 * @fn	std::string EntityInfoDisplay::DetermineHitPointsLabel(EntityClass ActiveUnit, EncounterInstance & Instance);
	 *
	 * @brief	Determine hit points label, calculates the current and max hitpoints of the entity, and returns them in a string format
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	ActiveUnit	The active unit.
	 * @param [in,out]	Instance  	The instance.
	 *
	 * @return	A std::string.
	 **************************************************************************************************/

	std::string DetermineHitPointsLabel(EntityClass ActiveUnit, EncounterInstance & Instance);

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetHitPointsLabel(std::string passed)
	 *
	 * @brief	Sets hit points label to the passed value
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param	passed	The passed string, which will be in the format 'Current hitpoints / max hitpoints'
	 **************************************************************************************************/

	void SetHitPointsLabel(std::string passed) { m_HitpointsLabel = passed; }

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetHitPointsLabelTexture(std::string HitPointsLabel, SDL_Renderer *& m_renderer);
	 *
	 * @brief	Sets hit points label texture to passed hitpoints label
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	HitPointsLabel	The hit points label.
	 * @param [in,out]	m_renderer	  	[in,out] If non-null, the renderer.
	 **************************************************************************************************/

	void SetHitPointsLabelTexture(std::string HitPointsLabel, SDL_Renderer *& m_renderer);

	/**********************************************************************************************//**
	 * @fn	std::string EntityInfoDisplay::DetermineACLabel(EntityClass ActiveUnit, EncounterInstance & Instance);
	 *
	 * @brief	Determine the armorclass label
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	ActiveUnit	The active unit.
	 * @param [in,out]	Instance  	The instance.
	 *
	 * @return	A std::string that is the Armor class of the unit in string representation
	 **************************************************************************************************/

	std::string DetermineACLabel(EntityClass ActiveUnit, EncounterInstance & Instance);

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetACLabel(std::string passed)
	 *
	 * @brief	Sets armorclass label
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param	passed	The passed string value to be armorclass label
	 **************************************************************************************************/

	void SetACLabel(std::string passed) { m_ACLabel = passed; }

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetACLabelTexture(std::string m_ACLabel, SDL_Renderer *& m_renderer);
	 *
	 * @brief	Sets ac label texture, calculates and sets the texture
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	m_ACLabel 	The AC label.
	 * @param [in,out]	m_renderer	[in,out] If non-null, the renderer.
	 **************************************************************************************************/

	void SetACLabelTexture(std::string m_ACLabel, SDL_Renderer *& m_renderer);

	/**********************************************************************************************//**
	 * @fn	std::string EntityInfoDisplay::DetermineMovementLabel(EntityClass ActiveUnit, EncounterInstance & Instance);
	 *
	 * @brief	Determine movement label
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	ActiveUnit	The active unit.
	 * @param [in,out]	Instance  	The instance.
	 *
	 * @return	A std::string.
	 **************************************************************************************************/

	std::string DetermineMovementLabel(EntityClass ActiveUnit, EncounterInstance & Instance);

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetMovementLabel(std::string passed)
	 *
	 * @brief	Sets movement label
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param	passed	The passed string is the new label
	 **************************************************************************************************/

	void SetMovementLabel(std::string passed) { m_MovementLeftLabel = passed; }

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetMovementLabelTexture(std::string MovementLabel, SDL_Renderer *& m_renderer);
	 *
	 * @brief	Sets movement label texture
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	MovementLabel	The movement label.
	 * @param [in,out]	m_renderer   	[in,out] If non-null, the renderer.
	 **************************************************************************************************/

	void SetMovementLabelTexture(std::string MovementLabel, SDL_Renderer *& m_renderer);

	/**********************************************************************************************//**
	 * @fn	std::string EntityInfoDisplay::DetermineAttackLeftLabel(EntityClass ActiveUnit, EncounterInstance & Instance);
	 *
	 * @brief	Determine attack left label, determines if the attack is left and represents it
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	ActiveUnit	The active unit.
	 * @param [in,out]	Instance  	The instance.
	 *
	 * @return	A std::string representation of attackleft
	 **************************************************************************************************/

	std::string DetermineAttackLeftLabel(EntityClass ActiveUnit, EncounterInstance & Instance);

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetAttackLeftLabel(std::string passed)
	 *
	 * @brief	Sets attack left label
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param	passed	The passed string representation of attackleft
	 **************************************************************************************************/

	void SetAttackLeftLabel(std::string passed) { m_AttackLeftLabel = passed; }

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetAttackLeftLabelTexture(std::string m_AttackLeftLabel, SDL_Renderer *& m_renderer);
	 *
	 * @brief	Sets attack left label texture
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	m_AttackLeftLabel	The attack left label.
	 * @param [in,out]	m_renderer		 	[in,out] If non-null, the renderer.
	 **************************************************************************************************/

	void SetAttackLeftLabelTexture(std::string m_AttackLeftLabel, SDL_Renderer *& m_renderer);

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetPanelConstraints(int x, int y, int w, int h);
	 *
	 * @brief	Sets panel constraints
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param	x	The x coordinate.
	 * @param	y	The y coordinate.
	 * @param	w	The width.
	 * @param	h	The height.
	 **************************************************************************************************/

	void SetPanelConstraints(int x, int y, int w, int h);

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetPanelConstraints(SDL_Rect other);
	 *
	 * @brief	Sets panel constraints equal to passed SDL_Rect
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param	other	The other.
	 **************************************************************************************************/

	void SetPanelConstraints(SDL_Rect other);

	/**********************************************************************************************//**
	 * @fn	int EntityInfoDisplay::GetXPanelConstraint()
	 *
	 * @brief	Get x coordinate panel constraint
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @return	The x coordinate panel constraint.
	 **************************************************************************************************/

	int GetXPanelConstraint() { return m_PanelConstraints.x; }

	/**********************************************************************************************//**
	 * @fn	int EntityInfoDisplay::GetYPanelConstraint()
	 *
	 * @brief	Get y coordinate panel constraint
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @return	The y coordinate panel constraint.
	 **************************************************************************************************/

	int GetYPanelConstraint() { return m_PanelConstraints.y; }

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::DetermineAllLabels(EntityClass ActiveUnit, EncounterInstance & Instance);
	 *
	 * @brief	Determine all labels, calls all other determine functions to determine every part of the info display
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param 		  	ActiveUnit	The active unit.
	 * @param [in,out]	Instance  	The instance.
	 **************************************************************************************************/

	void DetermineAllLabels(EntityClass ActiveUnit, EncounterInstance & Instance); //determines and sets all labels

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetAllTextures(SDL_Renderer *& m_renderer);
	 *
	 * @brief	Sets all textures, calls all other set texture functions
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param [in,out]	m_renderer	[in,out] If non-null, the renderer.
	 **************************************************************************************************/

	void SetAllTextures(SDL_Renderer *& m_renderer);

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::RenderPanel(SDL_Renderer *& m_renderer);
	 *
	 * @brief	Renders the panel described by m_renderer, renders the info display in a hardcoded relation to one another
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param [in,out]	m_renderer	[in,out] If non-null, the renderer.
	 **************************************************************************************************/

	void RenderPanel(SDL_Renderer *& m_renderer);

	/**********************************************************************************************//**
	 * @fn	void EntityInfoDisplay::SetFont(TTF_Font* Font);
	 *
	 * @brief	Sets a font
	 *
	 * @author	Brendan B
	 * @date	9/5/2018
	 *
	 * @param [in,out]	Font	If non-null, the font.
	 **************************************************************************************************/

	void SetFont(TTF_Font* Font) { m_InfoFont = Font; }


private:
	/** @brief	The panel constraints */
	SDL_Rect m_PanelConstraints;
	/** @brief	The name label texture */
	LTexture m_NameLabel_Texture;
	/** @brief	The r attack texture */
	LTexture m_RAttack_Texture;
	/** @brief	The m attack texture */
	LTexture m_MAttack_Texture;
	/** @brief	The melee attack label texture */
	LTexture m_MeleeAttackLabel_Texture;
	/** @brief	The melee attack damage label texture */
	LTexture m_MeleeAttackDamageLabel_Texture;
	/** @brief	The ranged attack label texture */
	LTexture m_RangedAttackLabel_Texture;
	/** @brief	The ranged attack damage label texture */
	LTexture m_RangedAttackDamageLabel_Texture;
	/** @brief	The hitpoints label texture */
	LTexture m_HitpointsLabel_Texture;
	/** @brief	The AC label texture */
	LTexture m_ACLabel_Texture;
	/** @brief	The movement left label texture */
	LTexture m_MovementLeftLabel_Texture;
	/** @brief	The attack left label texture */
	LTexture m_AttackLeftLabel_Texture;

	/** @brief	The name label */
	std::string m_NameLabel="";

	/** @brief	The attack */
	std::string m_MeleeLabel="Melee Attack:";
	/** @brief	The melee attack label */
	std::string m_MeleeAttackLabel="";
	/** @brief	The melee damage label */
	std::string m_MeleeDamageLabel="";

	/** @brief	The attac k */
	std::string m_RangedLabel="Ranged AttacK:";
	/** @brief	The ranged attack label */
	std::string m_RangedAttackLabel=""; 
	/** @brief	The ranged damage label */
	std::string m_RangedDamageLabel="";

	/** @brief	The hitpoints label */
	std::string m_HitpointsLabel="";
	/** @brief	The AC label */
	std::string m_ACLabel="";
	/** @brief	The movement left label */
	std::string m_MovementLeftLabel="";
	/** @brief	The attack left label */
	std::string m_AttackLeftLabel="";
	/** @brief	The information font */
	TTF_Font *m_InfoFont;
	/** @brief	The information text color */
	SDL_Color m_InfoTextColor = { 0, 0, 0 };
	
	/** @brief	Full pathname of the texture file */
	std::string m_texturePath;
	/** @brief	The spacing */
	int m_spacing = 20;

};