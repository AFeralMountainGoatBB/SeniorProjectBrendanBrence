/**********************************************************************************************//**
 * @file	Armor.h.
 *
 * @brief	Declares the armor class
 **************************************************************************************************/

#pragma once
#include "SharedEnums.h"
#include "GeneralHeaders.h"
#include "Objects.h"

//fwd declaration of tile to avoid circular dependency
class Tile;

/**********************************************************************************************//**
 * @class	ArmorObject
 *
 * @brief	An armor object. inherited from object class, armor objects are made for equipment to protect entities
 *
 * @author	Brendan B
 * @date	9/1/2018
 **************************************************************************************************/

class ArmorObject : public ObjectClass
{
public:

	/**********************************************************************************************//**
	 * @fn	ArmorObject::ArmorObject();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/
	 
	ArmorObject();

	/**********************************************************************************************//**
	 * @fn	ArmorObject::ArmorObject(const ArmorObject &Other);
	 *
	 * @brief	Copy constructor
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	Other	The other object being copied, const.
	 **************************************************************************************************/

	ArmorObject(const ArmorObject &Other);

	/**********************************************************************************************//**
	 * @fn	ArmorObject::ArmorObject(ObjectClass &Other);
	 *
	 * @brief	Constructor
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param [in,out]	Other	The other object being copied.
	 **************************************************************************************************/

	ArmorObject(ObjectClass &Other);

	/**********************************************************************************************//**
	 * @fn	void ArmorObject::SetBodySlot(BodyLocation location)
	 *
	 * @brief	Sets body location for armor
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	location	The location being set to.
	 **************************************************************************************************/

	void SetBodySlot(BodyLocation location) { m_BodySlot = location; }

	/**********************************************************************************************//**
	 * @fn	BodyLocation ArmorObject::GetBodySlot()
	 *
	 * @brief	Gets body slot
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The body location
	 **************************************************************************************************/

	BodyLocation GetBodySlot() { return this->m_BodySlot; }

	/**********************************************************************************************//**
	 * @fn	const int ArmorObject::GetArmorBonus();
	 *
	 * @brief	Gets armor bonus
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The armor bonus.
	 **************************************************************************************************/

	const int GetArmorBonus();

	/**********************************************************************************************//**
	 * @fn	void ArmorObject::SetArmorBonus(int bonus);
	 *
	 * @brief	Sets armor bonus
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	bonus	The bonus.
	 **************************************************************************************************/

	void SetArmorBonus(int bonus);

	/**********************************************************************************************//**
	 * @fn	int ArmorObject::GetDamageReduction();
	 *
	 * @brief	Gets damage reduction
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The damage reduction.
	 **************************************************************************************************/

	int GetDamageReduction();

	/**********************************************************************************************//**
	 * @fn	void ArmorObject::SetDamageReduction(int reduction);
	 *
	 * @brief	Sets damage reduction
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	reduction	The reduction being set.
	 **************************************************************************************************/

	void SetDamageReduction(int reduction);

	/**********************************************************************************************//**
	 * @fn	int ArmorObject::GetMaxDexBonus();
	 *
	 * @brief	Gets maximum dex bonus
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The maximum dex bonus.
	 **************************************************************************************************/

	int GetMaxDexBonus();

	/**********************************************************************************************//**
	 * @fn	void ArmorObject::SetMaxDex(int max);
	 *
	 * @brief	Sets maximum dex
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	max	The maximum dex bonus allowed by this object.
	 **************************************************************************************************/

	void SetMaxDex(int max);

	/**********************************************************************************************//**
	 * @fn	int ArmorObject::GetArmorCheckPenalty();
	 *
	 * @brief	Gets armor check penalty
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The armor check penalty.
	 **************************************************************************************************/

	int GetArmorCheckPenalty();

	/**********************************************************************************************//**
	 * @fn	void ArmorObject::SetArmorCheckPen(int penalty);
	 *
	 * @brief	Sets armor check pen
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	penalty	The new penalty.
	 **************************************************************************************************/

	void SetArmorCheckPen(int penalty);

	/**********************************************************************************************//**
	 * @fn	int ArmorObject::GetSpeedReduction();
	 *
	 * @brief	Gets speed reduction
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The speed reduction.
	 **************************************************************************************************/

	int GetSpeedReduction();

	/**********************************************************************************************//**
	 * @fn	void ArmorObject::SetSpeedReduction(int m_speedReduction);
	 *
	 * @brief	Sets speed reduction
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	m_speedReduction	The new speed reduction.
	 **************************************************************************************************/

	void SetSpeedReduction(int m_speedReduction);

	/**********************************************************************************************//**
	 * @fn	bool ArmorObject::GetIsShield();
	 *
	 * @brief	Gets is shield
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	True if it is a shield, false if it isnt.
	 **************************************************************************************************/

	bool GetIsShield();

	/**********************************************************************************************//**
	 * @fn	void ArmorObject::SetIsShield(bool isShield);
	 *
	 * @brief	Sets is shield
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	isShield	True if is shield, false if not.
	 **************************************************************************************************/

	void SetIsShield(bool isShield);

	/**********************************************************************************************//**
	 * @fn	std::vector<ArmorType> ArmorObject::GetArmorTypes();
	 *
	 * @brief	Gets armor types
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The armor types.
	 **************************************************************************************************/

	std::vector<ArmorType> GetArmorTypes();

	/**********************************************************************************************//**
	 * @fn	void ArmorObject::AddArmorType(ArmorType added);
	 *
	 * @brief	Adds an armor type
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	added	The added type.
	 **************************************************************************************************/

	void AddArmorType(ArmorType added);

	/**********************************************************************************************//**
	 * @fn	void ArmorObject::DisplayArmorInfo();
	 *
	 * @brief	Displays an armor information to console
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 **************************************************************************************************/

	void DisplayArmorInfo();

	/**********************************************************************************************//**
	 * @fn	std::string ArmorObject::GetName()
	 *
	 * @brief	Gets the name
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The name of the object.
	 **************************************************************************************************/

	std::string GetName() { return m_ObjectName; }

	/**********************************************************************************************//**
	 * @fn	void ArmorObject::SetName(std::string m_name)
	 *
	 * @brief	Sets a name
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	m_name	The new name.
	 **************************************************************************************************/

	void SetName(std::string m_name) { m_ObjectName = m_name; }

	/**********************************************************************************************//**
	 * @fn	std::pair<int, int> ArmorObject::GetLocation()
	 *
	 * @brief	Gets the location
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The location the object is at on the tilemap.
	 **************************************************************************************************/

	std::pair<int, int> GetLocation(){return m_Location;}

private:
	/** @brief	The armor bonus */
	int m_armorBonus=0;
	/** @brief	The damage reduction */
	int m_damageReduction=0;
	/** @brief	The maximum dex bonus */
	int m_maxDexBonus=0;
	/** @brief	The armor check penalty */
	int m_armorCheckPenalty=0;
	/** @brief	The speed reduction */
	int m_speedReduction=0;

	/** @brief	True if is shield, false if not */
	bool m_isShield = false;

	//not loaded into master list
	
	/** @brief	List of types of the armors */
	std::vector<ArmorType> m_armorTypes = {};
	/** @brief	List of types of the weapons */
	std::vector<WeaponType> m_weaponTypes = { IMPROVISED };
	/** @brief	List of types of the damages */
	std::vector<DamageType> m_damageTypes = {BLUNT};

	/** @brief	The damage dice */
	std::pair<int, DiceType> m_damageDice = { 1, D4 };
	//inherited values
	/** @brief	The box */
	SDL_Rect m_Box = { 0,0,70,70 };
	/** @brief	The path texture */
	std::string m_PathTexture = "Armor1.png";
	/** @brief	The texture */
	LTexture* m_Texture;
	/** @brief	The location */
	std::pair<int, int> m_Location = { 0,0 };

	//The dimensions of the Entity
	/** @brief	Width of the object */
	int m_OBJECT_WIDTH = 70;
	/** @brief	Height of the object */
	int m_OBJECT_HEIGHT = 70;

	//Model information
	/** @brief	Name of the object */
	std::string m_ObjectName = "";
	/** @brief	Information describing the object */
	std::string m_ObjectDescription = "";

	/**********************************************************************************************//**
	 * @brief	how much does the item weigh? Unimportant save for carrying capacity and determining
	 * 			2h for improvised weapons
	 **************************************************************************************************/

	float m_Weight = 0.0;

	/** @brief	does it have to take up both hand slots? */
	bool m_TwoHanded;
	/** @brief	can it be weilded in 2 hands? (example, longsword) */
	bool m_Versatile;

	/** @brief	The range increment */
	int m_RangeIncrement = 0;
	/** @brief	indicates where this item can be used (manhand and offhand are interchangable) */
	BodyLocation m_BodySlot = BODY;

	/** @brief	The crit multiplier */
	int m_CritMultiplier = 2;
	/** @brief	The crit threat */
	int m_CritThreat = 20;

public:
	//rendering functions

	/**********************************************************************************************//**
	 * @fn	LTexture * ArmorObject::GetTexture()
	 *
	 * @brief	Gets the texture
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	Null if it fails, else the texture.
	 **************************************************************************************************/

	LTexture * GetTexture() { return m_Texture; }

	/**********************************************************************************************//**
	 * @fn	void ArmorObject::SetPathTexture(std::string path)
	 *
	 * @brief	Sets path texture
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param	path	Full pathname of the file.
	 **************************************************************************************************/

	void SetPathTexture(std::string path) { m_PathTexture = path; }

	/**********************************************************************************************//**
	 * @fn	std::string ArmorObject::GetPathTexture()
	 *
	 * @brief	Gets path texture
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @return	The path texture.
	 **************************************************************************************************/

	std::string GetPathTexture() { return m_PathTexture; }

	/**********************************************************************************************//**
	 * @fn	void ArmorObject::SetTexture(std::map<std::string, LTexture*> TextureMap, std::string Path);
	 *
	 * @brief	Sets a texture based on word being sent
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param [in,out]	TextureMap	If non-null, the texture map.
	 * @param 		  	Path	  	Full pathname of the file.
	 **************************************************************************************************/

	void SetTexture(std::map<std::string, LTexture*> TextureMap, std::string Path);

	/**********************************************************************************************//**
	 * @fn	void ArmorObject::SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap);
	 *
	 * @brief	Sets a location were the object will appear on the tilemap, also calls rendlocation to set rending info
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param 		  	x	   	The x coordinate to be set
	 * @param 		  	y	   	The y coordinate to be set
	 * @param [in,out]	TileMap	The tile map.
	 **************************************************************************************************/

	void SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap);
	//sets where the entity will render

	/**********************************************************************************************//**
	 * @fn	void ArmorObject::SetRendLocation(std::vector<std::vector<Tile>> &TileVector);
	 *
	 * @brief	Sets rend location
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param [in,out]	TileVector	The tile map being used.
	 **************************************************************************************************/

	void SetRendLocation(std::vector<std::vector<Tile>> &TileVector);
	//calculates the middle of the tile the entity will render at

	/**********************************************************************************************//**
	 * @fn	std::pair<int, int> ArmorObject::CalcRendLocation(std::vector<std::vector<Tile>> &Map);
	 *
	 * @brief	Calculates the rend location based on tilewidth
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param [in,out]	Map	The map being used.
	 *
	 * @return	The calculated rend location to be set
	 **************************************************************************************************/

	std::pair<int, int> CalcRendLocation(std::vector<std::vector<Tile>> &Map);

	/**********************************************************************************************//**
	 * @fn	void ArmorObject::render(SDL_Rect& camera, SDL_Renderer *& Renderer);
	 *
	 * @brief	Renders this object
	 *
	 * @author	Brendan B
	 * @date	9/1/2018
	 *
	 * @param [in,out]	camera  	The camera being used
	 * @param [in,out]	Renderer	[in,out] If non-null, the active renderer.
	 **************************************************************************************************/

	void render(SDL_Rect& camera, SDL_Renderer *& Renderer);

};