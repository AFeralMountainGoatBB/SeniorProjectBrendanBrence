/**********************************************************************************************//**
 * @file	Objects.h.
 *
 * @brief	Declares the objects class
 **************************************************************************************************/

#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"
//#include "Tile.h"
#include "Texture.h"

//fwd declaration 
class Tile;

/**********************************************************************************************//**
 * @class	ObjectClass
 *
 * @brief	An object class.
 *
 * @author	Brendan B
 * @date	9/7/2018
 **************************************************************************************************/

class ObjectClass
{
public:

	/**********************************************************************************************//**
	 * @fn	ObjectClass::ObjectClass();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 **************************************************************************************************/

	ObjectClass();

	/**********************************************************************************************//**
	 * @fn	ObjectClass::ObjectClass(const ObjectClass &other);
	 *
	 * @brief	Copy constructor
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	other	The other object being copied
	 **************************************************************************************************/

	ObjectClass(const ObjectClass &other);

	/**********************************************************************************************//**
	 * @fn	void ObjectClass::SetmBox(int x, int y, int w, int h);
	 *
	 * @brief	Setm box, sets the dimensions of the box
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	x	The x coordinate.
	 * @param	y	The y coordinate.
	 * @param	w	The width.
	 * @param	h	The height.
	 **************************************************************************************************/

	void SetmBox(int x, int y, int w, int h);

	/**********************************************************************************************//**
	 * @fn	void ObjectClass::DisplayObjectWeaponFacts();
	 *
	 * @brief	Displays an object weapon facts, output to console
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 **************************************************************************************************/

	void DisplayObjectWeaponFacts();

	/**********************************************************************************************//**
	 * @fn	virtual std::string ObjectClass::GetName();
	 *
	 * @brief	Gets the name
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The name.
	 **************************************************************************************************/

	virtual std::string GetName();

	/**********************************************************************************************//**
	 * @fn	virtual void ObjectClass::SetName(std::string m_name);
	 *
	 * @brief	Sets a name
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	m_name	The name.
	 **************************************************************************************************/

	virtual void SetName(std::string m_name);

	//WeaponType GetWeaponTypes();

	/**********************************************************************************************//**
	 * @fn	void ObjectClass::AddWeaponType(WeaponType WeaponType);
	 *
	 * @brief	Adds a weapon type
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	WeaponType	Type of the weapon.
	 **************************************************************************************************/

	void AddWeaponType(WeaponType WeaponType);

	/**********************************************************************************************//**
	 * @fn	std::vector<WeaponType>& ObjectClass::GetWeaponType();
	 *
	 * @brief	Gets weapon type
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The weapon types
	 **************************************************************************************************/

	std::vector<WeaponType>& GetWeaponType();

	/**********************************************************************************************//**
	 * @fn	std::pair<int, DiceType> ObjectClass::GetDamageDice();
	 *
	 * @brief	Gets damage dice
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The damage dice.
	 **************************************************************************************************/

	std::pair<int, DiceType> GetDamageDice();

	/**********************************************************************************************//**
	 * @fn	void ObjectClass::SetDamageDice(std::pair<int,DiceType> m_damageDice);
	 *
	 * @brief	Sets damage dice
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	m_damageDice	The damage dice.
	 **************************************************************************************************/

	void SetDamageDice(std::pair<int,DiceType> m_damageDice);

	/**********************************************************************************************//**
	 * @fn	bool ObjectClass::GetTwoHanded();
	 *
	 * @brief	Gets two handed
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	True if it is two handed, false if it isnt
	 **************************************************************************************************/

	bool GetTwoHanded();

	/**********************************************************************************************//**
	 * @fn	void ObjectClass::SetTwoHanded(bool isTwoHanded);
	 *
	 * @brief	Sets two handed
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	isTwoHanded	True if is two handed, false if not.
	 **************************************************************************************************/

	void SetTwoHanded(bool isTwoHanded);

	/**********************************************************************************************//**
	 * @fn	bool ObjectClass::GetVersatile();
	 *
	 * @brief	Gets the versatile
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool GetVersatile();

	/**********************************************************************************************//**
	 * @fn	void ObjectClass::SetVersatile(bool passed);
	 *
	 * @brief	Sets a versatile
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	passed	True if passed.
	 **************************************************************************************************/

	void SetVersatile(bool passed);

	/**********************************************************************************************//**
	 * @fn	void ObjectClass::SetCritInformation(int range, int multiplier);
	 *
	 * @brief	Sets crit information
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	range	  	The range of the critical, what it crits on
	 * @param	multiplier	The multiplier, how much more damage it does
	 **************************************************************************************************/

	void SetCritInformation(int range, int multiplier);

	/**********************************************************************************************//**
	 * @fn	std::pair<int, int> ObjectClass::GetCritInformation();
	 *
	 * @brief	Gets crit information
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The crit information.
	 **************************************************************************************************/

	std::pair<int, int> GetCritInformation();


	/**********************************************************************************************//**
	 * @fn	virtual void ObjectClass::SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap);
	 *
	 * @brief	Sets a location, to be found on the tilemap
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param 		  	x	   	The x coordinate.
	 * @param 		  	y	   	The y coordinate.
	 * @param [in,out]	TileMap	The tile map.
	 **************************************************************************************************/

	virtual void SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap);
	//sets where the entity will render

	/**********************************************************************************************//**
	 * @fn	virtual void ObjectClass::SetRendLocation(std::vector<std::vector<Tile>> &TileVector);
	 *
	 * @brief	Sets rend location, called usually by setlocation, to set where the object should render
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	TileVector	The tile vector.
	 **************************************************************************************************/

	virtual void SetRendLocation(std::vector<std::vector<Tile>> &TileVector);

	/**********************************************************************************************//**
	 * @fn	virtual std::pair<int, int> ObjectClass::CalcRendLocation(std::vector<std::vector<Tile>> &Map);
	 *
	 * @brief	Calculates the rend location
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	Map	The map.
	 *
	 * @return	The calculated rend location.
	 **************************************************************************************************/

	virtual std::pair<int, int> CalcRendLocation(std::vector<std::vector<Tile>> &Map);

	/**********************************************************************************************//**
	 * @fn	virtual std::pair<int, int> ObjectClass::GetLocation();
	 *
	 * @brief	Gets the location
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The location.
	 **************************************************************************************************/

	virtual std::pair<int, int> GetLocation();

	//Centers the m_camera over the entity

	/**********************************************************************************************//**
	 * @fn	void ObjectClass::setCamera(SDL_Rect& camera);
	 *
	 * @brief	Sets a camera
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	camera	The camera.
	 **************************************************************************************************/

	void setCamera(SDL_Rect& camera);

	//Shows the entity on the screen

	/**********************************************************************************************//**
	 * @fn	virtual LTexture* ObjectClass::GetTexture();
	 *
	 * @brief	Gets the texture
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	Null if it fails, else the texture.
	 **************************************************************************************************/

	virtual LTexture* GetTexture();

	/**********************************************************************************************//**
	 * @fn	virtual void ObjectClass::SetTexture(std::map<std::string, LTexture*> TextureMap, std::string Path);
	 *
	 * @brief	Sets a texture
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	TextureMap	If non-null, the texture map.
	 * @param 		  	Path	  	Full pathname of the file.
	 **************************************************************************************************/

	virtual void SetTexture(std::map<std::string, LTexture*> TextureMap, std::string Path);

	/**********************************************************************************************//**
	 * @fn	virtual void ObjectClass::render(SDL_Rect& camera, SDL_Renderer *& Renderer);
	 *
	 * @brief	Renders this object
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param [in,out]	camera  	The camera.
	 * @param [in,out]	Renderer	[in,out] If non-null, the renderer.
	 **************************************************************************************************/

	virtual void render(SDL_Rect& camera, SDL_Renderer *& Renderer);

	/**********************************************************************************************//**
	 * @fn	virtual BodyLocation ObjectClass::GetBodySlot();
	 *
	 * @brief	Gets body slot
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The body slot.
	 **************************************************************************************************/

	virtual BodyLocation GetBodySlot();

	/**********************************************************************************************//**
	 * @fn	virtual void ObjectClass::SetBodySlot(BodyLocation location)
	 *
	 * @brief	Sets body slot
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	location	The location.
	 **************************************************************************************************/

	virtual void SetBodySlot(BodyLocation location) { m_BodySlot = location; }

	/**********************************************************************************************//**
	 * @fn	int ObjectClass::GetRangeIncrement()
	 *
	 * @brief	Gets range increment
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The range increment.
	 **************************************************************************************************/

	int GetRangeIncrement() { return m_RangeIncrement; }

	/**********************************************************************************************//**
	 * @fn	void ObjectClass::SetRangeIncrement(int passed)
	 *
	 * @brief	Sets range increment
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	passed	The passed value
	 **************************************************************************************************/

	void SetRangeIncrement(int passed) { this->m_RangeIncrement = passed; }

	/**********************************************************************************************//**
	 * @fn	const float ObjectClass::GetBaseWeight();
	 *
	 * @brief	Gets base weight
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The base weight.
	 **************************************************************************************************/

	const float GetBaseWeight();

	/**********************************************************************************************//**
	 * @fn	void ObjectClass::SetBaseWeight(float m_Weight);
	 *
	 * @brief	Sets base weight
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	m_Weight	The weight.
	 **************************************************************************************************/

	void SetBaseWeight(float m_Weight);

	/**********************************************************************************************//**
	 * @fn	std::vector<DamageType>& ObjectClass::GetDamageTypes();
	 *
	 * @brief	Gets damage types
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The damage types.
	 **************************************************************************************************/

	std::vector<DamageType>& GetDamageTypes();

	/**********************************************************************************************//**
	 * @fn	void ObjectClass::AddDamageType(DamageType AddType);
	 *
	 * @brief	Adds a damage type
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	AddType	Type of damage to add to list of damage types
	 **************************************************************************************************/

	void AddDamageType(DamageType AddType);

	/**********************************************************************************************//**
	 * @fn	bool ObjectClass::IsRangedWeapon();
	 *
	 * @brief	Query if this object is ranged weapon
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	True if ranged weapon, false if not.
	 **************************************************************************************************/

	bool IsRangedWeapon();

	/**********************************************************************************************//**
	 * @fn	bool ObjectClass::IsThrowingWeapon();
	 *
	 * @brief	Query if this object is throwing weapon
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	True if throwing weapon, false if not.
	 **************************************************************************************************/

	bool IsThrowingWeapon();

	/**********************************************************************************************//**
	 * @fn	bool ObjectClass::IsLightWeapon();
	 *
	 * @brief	Query if this object is light weapon
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	True if light weapon, false if not.
	 **************************************************************************************************/

	bool IsLightWeapon();

	/**********************************************************************************************//**
	 * @fn	bool ObjectClass::IsMeleeWeapon();
	 *
	 * @brief	Query if this object is melee weapon
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	True if melee weapon, false if not.
	 **************************************************************************************************/

	bool IsMeleeWeapon();

	/**********************************************************************************************//**
	 * @fn	void ObjectClass::operator=(const ObjectClass* other)
	 *
	 * @brief	Assignment operator
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	other	The other object copy
	 **************************************************************************************************/

	void operator=(const ObjectClass* other)
	{
		m_Box.x = other->m_Box.x;
		m_Box.y = other->m_Box.y;
		m_Box.h = other->m_Box.h;
		m_Box.w = other->m_Box.w;

		m_PathTexture = other->m_PathTexture;
		m_ObjectName = other->m_ObjectName;
		m_ObjectDescription = other->m_ObjectDescription;

		m_TwoHanded = other->m_TwoHanded;
		m_Versatile = other->m_Versatile;
		for (auto i = other->m_weaponTypes.begin(); i != other->m_weaponTypes.end(); i++)
		{
			this->m_weaponTypes.push_back(*i);
		}

		m_damageDice.first = other->m_damageDice.first;
		m_damageDice.second = other->m_damageDice.second;

		m_Weight = other->m_Weight;
		m_BodySlot = other->m_BodySlot;
		m_CritMultiplier = other->m_CritMultiplier;
		m_CritThreat = other->m_CritThreat;
	}

	/**********************************************************************************************//**
	 * @fn	virtual void ObjectClass::SetPathTexture(std::string path)
	 *
	 * @brief	Sets path texture
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	path	Full pathname of the file.
	 **************************************************************************************************/

	virtual void SetPathTexture(std::string path) { m_PathTexture = path; }

	/**********************************************************************************************//**
	 * @fn	virtual std::string ObjectClass::GetPathTexture()
	 *
	 * @brief	Gets path texture
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The path texture.
	 **************************************************************************************************/

	virtual std::string GetPathTexture() { return m_PathTexture; }
private:
	//render stuff (also some model stuff)
	/** @brief	The box */
	SDL_Rect m_Box = { 0,0,70,70 };
	/** @brief	The path texture */
	std::string m_PathTexture = "pixelknife.png";
	/** @brief	The texture */
	LTexture* m_Texture;
	/** @brief	The location */
	std::pair<int, int> m_Location = { 0,0 };

	/** @brief	Width of the object */
	int m_OBJECT_WIDTH = 70;
	/** @brief	Height of the object */
	int m_OBJECT_HEIGHT = 70;

	
	/** @brief	Name of the object */
	std::string m_ObjectName= "";
	/** @brief	Information describing the object */
	std::string m_ObjectDescription = "";
	/** @brief	types of weapon this is, default improvised */
	std::vector<WeaponType> m_weaponTypes = { };
	/** @brief	List of types of the damages */
	std::vector<DamageType> m_damageTypes = {};

	/** @brief	The damage dice */
	std::pair<int, DiceType> m_damageDice = { 1, D3 };

	/**********************************************************************************************//**
	 * @brief	how much does the item weigh? Unimportant save for carrying capacity and determining
	 * 			2h for improvised weapons
	 **************************************************************************************************/

	float m_Weight=0.0;

	/** @brief	does it have to take up both hand slots? */
	bool m_TwoHanded;
	/** @brief	can it be weilded in 2 hands? (example, longsword) */
	bool m_Versatile;

	/** @brief	The range increment */
	int m_RangeIncrement = 0;
	/** @brief	indicates where this weapon can be used (manhand and offhand are interchangable) */
	BodyLocation m_BodySlot=MAINHAND;

	/** @brief	The crit multiplier */
	int m_CritMultiplier=2;
	/** @brief	The crit threat */
	int m_CritThreat = 20;

public:

	//virtual functions

	/**********************************************************************************************//**
	 * @fn	virtual const int ObjectClass::GetArmorBonus();
	 *
	 * @brief	Gets armor bonus
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The armor bonus.
	 **************************************************************************************************/

	virtual const int GetArmorBonus();

	/**********************************************************************************************//**
	 * @fn	virtual void ObjectClass::SetArmorBonus(int bonus);
	 *
	 * @brief	Sets armor bonus
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	bonus	The armor bonus
	 **************************************************************************************************/

	virtual void SetArmorBonus(int bonus);

	/**********************************************************************************************//**
	 * @fn	virtual int ObjectClass::GetDamageReduction();
	 *
	 * @brief	Gets damage reduction
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The damage reduction.
	 **************************************************************************************************/

	virtual int GetDamageReduction();

	/**********************************************************************************************//**
	 * @fn	virtual void ObjectClass::SetDamageReduction(int reduction);
	 *
	 * @brief	Sets damage reduction
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	reduction	The reduction.
	 **************************************************************************************************/

	virtual void SetDamageReduction(int reduction);

	/**********************************************************************************************//**
	 * @fn	virtual int ObjectClass::GetMaxDexBonus();
	 *
	 * @brief	Gets maximum dex bonus
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The maximum dex bonus.
	 **************************************************************************************************/

	virtual int GetMaxDexBonus();

	/**********************************************************************************************//**
	 * @fn	virtual void ObjectClass::SetMaxDex(int max);
	 *
	 * @brief	Sets maximum dex
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	max	The maximum.
	 **************************************************************************************************/

	virtual void SetMaxDex(int max);

	/**********************************************************************************************//**
	 * @fn	virtual int ObjectClass::GetArmorCheckPenalty();
	 *
	 * @brief	Gets armor check penalty
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The armor check penalty.
	 **************************************************************************************************/

	virtual int GetArmorCheckPenalty();

	/**********************************************************************************************//**
	 * @fn	virtual void ObjectClass::SetArmorCheckPen(int penalty);
	 *
	 * @brief	Sets armor check pen
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	penalty	The penalty.
	 **************************************************************************************************/

	virtual void SetArmorCheckPen(int penalty);

	/**********************************************************************************************//**
	 * @fn	virtual int ObjectClass::GetSpeedReduction();
	 *
	 * @brief	Gets speed reduction
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The speed reduction.
	 **************************************************************************************************/

	virtual int GetSpeedReduction();

	/**********************************************************************************************//**
	 * @fn	virtual void ObjectClass::SetSpeedReduction(int m_speedReduction);
	 *
	 * @brief	Sets speed reduction
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	m_speedReduction	The speed reduction.
	 **************************************************************************************************/

	virtual void SetSpeedReduction(int m_speedReduction);

	/**********************************************************************************************//**
	 * @fn	virtual int ObjectClass::GetEquipActions();
	 *
	 * @brief	Gets equip actions
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The equip actions.
	 **************************************************************************************************/

	virtual int GetEquipActions();

	/**********************************************************************************************//**
	 * @fn	virtual void ObjectClass::SetEquipActions(int actions);
	 *
	 * @brief	Sets equip actions
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	actions	The actions.
	 **************************************************************************************************/

	virtual void SetEquipActions(int actions);

	/**********************************************************************************************//**
	 * @fn	virtual bool ObjectClass::GetIsShield();
	 *
	 * @brief	Gets is shield
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	virtual bool GetIsShield();

	/**********************************************************************************************//**
	 * @fn	virtual void ObjectClass::SetIsShield(bool isShield);
	 *
	 * @brief	Sets is shield
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	isShield	True if is shield, false if not.
	 **************************************************************************************************/

	virtual void SetIsShield(bool isShield);

	/**********************************************************************************************//**
	 * @fn	virtual std::vector<ArmorType> ObjectClass::GetArmorTypes();
	 *
	 * @brief	Gets armor types
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @return	The armor types.
	 **************************************************************************************************/

	virtual std::vector<ArmorType> GetArmorTypes();

	/**********************************************************************************************//**
	 * @fn	virtual void ObjectClass::AddArmorType(ArmorType added);
	 *
	 * @brief	Adds an armor type
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 *
	 * @param	added	The added armor type
	 **************************************************************************************************/

	virtual void AddArmorType(ArmorType added);

	/**********************************************************************************************//**
	 * @fn	virtual void ObjectClass::DisplayArmorInfo();
	 *
	 * @brief	Displays an armor information, outputs to console
	 *
	 * @author	Brendan B
	 * @date	9/7/2018
	 **************************************************************************************************/

	virtual void DisplayArmorInfo();

	private:
		/** @brief	The armor bonus */
		int m_armorBonus = 0;
		/** @brief	The damage reduction */
		int m_damageReduction = 0;
		/** @brief	The maximum dex bonus */
		int m_maxDexBonus = 100;
		/** @brief	The armor check penalty */
		int m_armorCheckPenalty = 0;
		/** @brief	The speed reduction */
		int m_speedReduction = 100;
		/** @brief	The equip actions */
		int m_equipActions = 1;
		/** @brief	True if is shield, false if not */
		bool m_isShield = false;

		/** @brief	List of types of the armors */
		std::vector<ArmorType> m_armorTypes = {};
};