/**********************************************************************************************//**
 * @file	EntityClass.h.
 *
 * @brief	Declares the entity class class
 **************************************************************************************************/

#pragma once
#include "SharedEnums.h"
#include "GeneralHeaders.h"
#include "Objects.h"
#include "ItemContainer.h"
#include "Feats.h"
#include "AttackClass.h"
//#include "TargetSystem.h"

//forward declaration of Tile Class to prevent circular dependency
class Tile;
//forward declaration of LTexture class to prevent circular dependency
class LTexture;
//forward declaration of EncounterInstance class to prevent circular dependency
class EncounterInstance;
//forward declaration of InventoryMenu Class to prevent circular dependency
class InventoryMenu;

/**********************************************************************************************//**
 * @class	EntityClass
 *
 * @brief	The storage class for individual entities
 *
 * Details: Class represents an autonomous being in the game world who has attributes and takes actions in the game world,
 * they are capable of wielding equipment and attacking other entities
 * 
 * @author	Brendan B
 * @date	8/31/2018
 **************************************************************************************************/

class EntityClass {
public:
	//constructors

	/**********************************************************************************************//**
	 * @fn	EntityClass::EntityClass(int xInitial, int yInitial, int HPMax, int HPCurrent);
	 *
	 * @brief	Constructor
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	xInitial 	The initial position of the character.
	 * @param	yInitial 	The initial position of the character.
	 * @param	HPMax	 	The hp maximum.
	 * @param	HPCurrent	The hp current.
	 **************************************************************************************************/

	EntityClass(int xInitial, int yInitial, int HPMax, int HPCurrent);

	/**********************************************************************************************//**
	 * @fn	EntityClass::EntityClass();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	EntityClass();
	//~EntityClass();

	//The dimensions of the Entity
	/** @brief	Width(pixels) of the entity */
	int m_ENTITY_WIDTH = 80;
	/** @brief	Height(pixels) of the entity */
	int m_ENTITY_HEIGHT = 80;

	/**********************************************************************************************//**
	 * @fn	virtual ControlMode EntityClass::GetControlMode();
	 *
	 * @brief	Gets control mode variable
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The control mode.
	 **************************************************************************************************/

	virtual ControlMode GetControlMode();

	/**********************************************************************************************//**
	 * @fn	virtual void EntityClass::SetControlMode(ControlMode NewControl);
	 *
	 * @brief	Sets control mode variable to the one passed
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	NewControl	The new control mode.
	 **************************************************************************************************/

	virtual void SetControlMode(ControlMode NewControl);

	//Takes key presses and adjusts the entity's movements

	/**********************************************************************************************//**
	 * @fn	virtual void EntityClass::handleEvent(SDL_Event& m_event, EncounterInstance &Instance);
	 *
	 * @brief	Handles the events passed by the user to it into reflective actions in the program
	 * 			Determines context and processes the keyboard actions into entity actions 
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	m_event 	The event struct.
	 * @param [in,out]	Instance	The instance we are in for context.
	 **************************************************************************************************/

	virtual void handleEvent(SDL_Event& m_event, EncounterInstance &Instance);

	/**********************************************************************************************//**
	 * @fn	virtual bool EntityClass::move(std::vector<std::vector<Tile>> &TileVector);
	 *
	 * @brief	Moves the entity around the tile vector. Looks at the direction the entity is facing then attempts the move
	 * 			fails if the entity is moving into a blocked tile or off of the map. Also fails if the entity does not have enough movement left
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	TileVector	The tile vector, it is the model of the map the encounter is being played on.
	 *
	 * @return	True if it succeeds and the entity is moved, false if it fails and the entity is in the same spot they started in.
	 **************************************************************************************************/

	virtual bool move(std::vector<std::vector<Tile>> &TileVector);

	/**********************************************************************************************//**
	 * @fn	void EntityClass::RollInitiative();
	 *
	 * @brief	Roll initiative iterates through each entity present in the encounter and rolls an initative score for them, which ultimately determines turn order
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void RollInitiative();

	//combat functions
	/**********************************************************************************************//**
	 * @fn	bool EntityClass::EntityMeleeAttack(std::vector<std::vector<Tile>> &TileVector, EncounterInstance & Instance);
	 *
	 * @brief	Entity melee attack, attempts to find a target in the direction the entity is facing, if a target is found it will 
	 * 			create and execute an attack action and return true, if no target is found it fails and returns false
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	TileVector	The tile vector (the map model)
	 * @param [in,out]	Instance  	The instance of the encounter we are in
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool EntityMeleeAttack(std::vector<std::vector<Tile>> &TileVector, EncounterInstance & Instance);

	/**********************************************************************************************//**
	 * @fn	EntityClass* EntityClass::EntityMeleeAttackTile(std::vector<std::vector<Tile>> &TileVector);
	 *
	 * @brief	Entity melee attack tile, selects a tile based on movedirection and finds if there is an attackable target
	 * 			in it, returns target if there is one, returns nullptr if failure
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	TileVector	The tile vector.
	 *
	 * @return	Nullptr if it fails, else a pointer to the EntityClass.
	 **************************************************************************************************/

	EntityClass* EntityMeleeAttackTile(std::vector<std::vector<Tile>> &TileVector);

	/**********************************************************************************************//**
	 * @fn	bool EntityClass::EntityRangedAttack(std::vector<std::vector<Tile>>&TileVector, EncounterInstance &Instance);
	 *
	 * @brief	Entity ranged attack, finds if there is a target where the instance's targeting system is and executes an attack action if it is
	 * 			a valid tile to attack. If there is a valid target it returns true. if no valid target returns false		
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	TileVector	The tile vector (map model we are using).
	 * @param [in,out]	Instance  	The instance of encounter we are using.
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool EntityRangedAttack(std::vector<std::vector<Tile>>&TileVector, EncounterInstance &Instance);

	/**********************************************************************************************//**
	 * @fn	bool EntityClass::EntityRangedAttack(std::vector<std::vector<Tile>>&TileVector, EncounterInstance &Instance, EntityClass* Target);
	 *
	 * @brief	Entity overloaded function for passing an already selected target, used by AIplayer
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	TileVector	The tile vector (map being used).
	 * @param [in,out]	Instance  	The instance (encounter context).
	 * @param [in,out]	Target	  	If non-null, target for the entity to attack.
	 *
	 * @return	True if it succeeds and attack is attempted, false if it fails if target isnt attackable.
	 **************************************************************************************************/

	bool EntityRangedAttack(std::vector<std::vector<Tile>>&TileVector, EncounterInstance &Instance, EntityClass* Target);

	/**********************************************************************************************//**
	 * @fn	EntityClass* EntityClass::EntityRangedAttackTile(std::vector<std::vector<Tile>> &TileVector, EncounterInstance &Instance);
	 *
	 * @brief	Entity ranged attack tile, selects a valid target if it exists at targetsystem's location, returns nullptr if no valid target could be determined
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	TileVector	The tile vector (map model)
	 * @param [in,out]	Instance  	The instance (encounter instance being used)
	 *
	 * @return	Nullptr if it fails, else a pointer to the EntityClass that will be attacked
	 **************************************************************************************************/

	EntityClass* EntityRangedAttackTile(std::vector<std::vector<Tile>> &TileVector, EncounterInstance &Instance);

	/**********************************************************************************************//**
	 * @fn	int EntityClass::GetBaseAttackBonus()
	 *
	 * @brief	Gets base attack bonus value
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The base attack bonus (int).
	 **************************************************************************************************/

	int GetBaseAttackBonus() { return m_BaseAttackBonus; }

	/**********************************************************************************************//**
	 * @fn	ObjectClass& EntityClass::GetUnarmedStrike()
	 *
	 * @brief	Gets unarmed strike
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The unarmed strike.
	 **************************************************************************************************/

	ObjectClass& GetUnarmedStrike() { return m_UnarmedStrike; }

	/**********************************************************************************************//**
	 * @fn	void EntityClass::GenerateUnarmedStrike(EncounterInstance& Instance);
	 *
	 * @brief	Generates an unarmed strike weapon for the entity and stores it in the class
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	Instance	The instance entity is in
	 **************************************************************************************************/

	void GenerateUnarmedStrike(EncounterInstance& Instance);

	/**********************************************************************************************//**
	 * @fn	int EntityClass::GetTotalDamageReduction();
	 *
	 * @brief	Gets total damage reduction
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The total damage reduction of the entity
	 **************************************************************************************************/

	int GetTotalDamageReduction();
	//end combat functions

	//combat Armor class functions

	/**********************************************************************************************//**
	 * @fn	int EntityClass::GetArmorClass();
	 *
	 * @brief	Gets armor class
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The armor class of the entity.
	 **************************************************************************************************/

	int GetArmorClass();

	/**********************************************************************************************//**
	 * @fn	int EntityClass::UpdateArmorClass();
	 *
	 * @brief	Updates the armor class
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	the new armor class.
	 **************************************************************************************************/

	int UpdateArmorClass();

	//end combat armor class functions

	/**********************************************************************************************//**
	 * @fn	bool EntityClass::GetAttackLeft()
	 *
	 * @brief	Gets if the entity has an attack left
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	True if the attack is left, false if not.
	 **************************************************************************************************/

	bool GetAttackLeft() { return m_ActionLeft; }

	/**********************************************************************************************//**
	 * @fn	void EntityClass::SetAttackLeft(bool passed)
	 *
	 * @brief	Sets attack left
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	passed - the new value for attackleft.
	 **************************************************************************************************/

	void SetAttackLeft(bool passed) { m_ActionLeft = passed; }

	/**********************************************************************************************//**
	 * @fn	virtual void EntityClass::SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap);
	 *
	 * @brief	Sets the location of this entity location, calls set rend location as well to update the rendering location of the entity as well
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param 		  	x	   	The x coordinate.
	 * @param 		  	y	   	The y coordinate.
	 * @param [in,out]	TileMap	The tile map.
	 **************************************************************************************************/

	virtual  void SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap);

	/**********************************************************************************************//**
	 * @fn	virtual void EntityClass::SetRendLocation(std::vector<std::vector<Tile>> &TileVector);
	 *
	 * @brief	Sets rend location of the entity for rendering, usually called only within setlocation
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	TileVector	The tile map.
	 **************************************************************************************************/

	virtual void SetRendLocation(std::vector<std::vector<Tile>> &TileVector);
	//calculates the middle of the tile the entity will render at

	/**********************************************************************************************//**
	 * @fn	virtual std::pair<int, int> EntityClass::CalcRendLocation(std::vector<std::vector<Tile>> &Map);
	 *
	 * @brief	Calculates the rend location given the entities location on the tilemap, and how many pixels wide / tall each tile is when rendered
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	Map	The map being used.
	 *
	 * @return	The calculated rend location.
	 **************************************************************************************************/

	virtual std::pair<int, int> CalcRendLocation(std::vector<std::vector<Tile>> &Map);

	/**********************************************************************************************//**
	 * @fn	virtual void EntityClass::SetPath(std::string Path);
	 *
	 * @brief	Sets a path for the entity's character sheet to be found at
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	Path	Pathname of the file, not including the foldername.
	 **************************************************************************************************/

	virtual void SetPath(std::string Path);

	/**********************************************************************************************//**
	 * @fn	virtual std::string EntityClass::GetPath()
	 *
	 * @brief	Gets the path
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The path.
	 **************************************************************************************************/

	virtual std::string GetPath() { return m_PathTexture; }
	//returns the location

	/**********************************************************************************************//**
	 * @fn	virtual std::pair<int, int> EntityClass::GetLocation();
	 *
	 * @brief	Gets the location
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The location of this entity.
	 **************************************************************************************************/

	virtual std::pair<int, int> GetLocation();


	/**********************************************************************************************//**
	 * @fn	virtual void EntityClass::setCamera(SDL_Rect& camera);
	 *
	 * @brief	Sets the passed camera to center over the entity
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	camera	The camera being used to center over this entity.
	 **************************************************************************************************/

	virtual void setCamera(SDL_Rect& camera);


	/**********************************************************************************************//**
	 * @fn	virtual void EntityClass::render(SDL_Rect& camera, SDL_Renderer *& Renderer);
	 *
	 * @brief	Renders this entity
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	camera  	The camera being used
	 * @param [in,out]	Renderer	[in,out] If non-null, the renderer that will be used to render this entity.
	 **************************************************************************************************/

	virtual void render(SDL_Rect& camera, SDL_Renderer *& Renderer);


	/**********************************************************************************************//**
	 * @fn	const int EntityClass::GetHitPoints()
	 *
	 * @brief	Gets the current hit points
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The current hit points.
	 **************************************************************************************************/

	const int GetHitPoints() { return m_HitPoints; }

	/**********************************************************************************************//**
	 * @fn	const int EntityClass::GetMaxHitPoints()
	 *
	 * @brief	Gets maximum hit points
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The maximum hit points.
	 **************************************************************************************************/

	const int GetMaxHitPoints() { return m_HitPointMaximum; }

	/**********************************************************************************************//**
	 * @fn	void EntityClass::SetMaxHitPoints(int passed)
	 *
	 * @brief	Sets maximum hit points and current hitpoints to reflect maximum
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	passed	The passed new value for max hitpoints.
	 **************************************************************************************************/

	void SetMaxHitPoints(int passed) { m_HitPointMaximum = passed; m_HitPoints = passed; }

	/**********************************************************************************************//**
	 * @fn	void EntityClass::SetBaseAttackBonus(int passed)
	 *
	 * @brief	Sets base attack bonus
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	passed	The passed value will be the new base attack bonus.
	 **************************************************************************************************/

	void SetBaseAttackBonus(int passed) { m_BaseAttackBonus = passed; }

	/**********************************************************************************************//**
	 * @fn	void EntityClass::AddHitPoints(int addition);
	 *
	 * @brief	Adds hit points to current hitpoints
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	addition	addition is the value added to current hitpoints.
	 **************************************************************************************************/

	void AddHitPoints(int addition);

	/**********************************************************************************************//**
	 * @fn	void EntityClass::SubHitPoints(int subtraction)
	 *
	 * @brief	Sub hit points
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	subtraction	is the value that is subtracted from current hitpoints
	 **************************************************************************************************/

	void SubHitPoints(int subtraction) { this->m_HitPoints -= subtraction; }

	/**********************************************************************************************//**
	 * @fn	void EntityClass::SetHitPoints(int SetHP)
	 *
	 * @brief	Sets hit points
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	SetHP	The new value to set the hp to
	 **************************************************************************************************/

	void SetHitPoints(int SetHP) {	m_HitPoints = SetHP; }

	/*Calculating derived values*/

	/**********************************************************************************************//**
	 * @fn	void EntityClass::SetName(std::string m_name);
	 *
	 * @brief	Sets a name
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	m_name	The name.
	 **************************************************************************************************/

	void SetName(std::string m_name);

	/**********************************************************************************************//**
	 * @fn	std::string EntityClass::GetName();
	 *
	 * @brief	Gets the name
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The name - name of entity
	 **************************************************************************************************/

	std::string GetName();

	/**********************************************************************************************//**
	 * @fn	virtual void EntityClass::SetTexture(std::map<std::string, LTexture*> &map, std::string path);
	 *
	 * @brief	Sets a texture from the main texture map, uses the passed string to find in the map the 
	 * 			texture desired and sets this texture equal to the second in the map
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	map 	[in,out] If non-null, the string - texture map that contains pointers to all loaded textures.
	 * @param 		  	path	pathname of the texture file, appends the folder file to the front of it.
	 **************************************************************************************************/

	virtual void SetTexture(std::map<std::string, LTexture*> &map, std::string path);

	/**********************************************************************************************//**
	 * @fn	virtual LTexture* EntityClass::GetTexture();
	 *
	 * @brief	Gets the texture
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	Null if it fails or value isnt set, else the texture stored.
	 **************************************************************************************************/

	virtual LTexture* GetTexture();

	/**********************************************************************************************//**
	 * @fn	void EntityClass::DisplayEntireInventory();
	 *
	 * @brief	Displays the entire inventory of the entity to console
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void DisplayEntireInventory();

	/**********************************************************************************************//**
	 * @fn	void EntityClass::DisplayFeats();
	 *
	 * @brief	Displays the feats from the entity to console
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void DisplayFeats();

	//equipment functions
	//getters

	/**********************************************************************************************//**
	 * @fn	ObjectClass* EntityClass::GetEquipmentInSlot(BodyLocation location);
	 *
	 * @brief	Gets equipment in slot passed, if no equipment in slot it will return nullptr
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	location	The location.
	 *
	 * @return	nullptr if empty slot, else the equipment in slot.
	 **************************************************************************************************/

	ObjectClass* GetEquipmentInSlot(BodyLocation location); //returns whatever is equipped in location, null if nothing

	/**********************************************************************************************//**
	 * @fn	bool EntityClass::DoesSlotExist(BodyLocation location);
	 *
	 * @brief	Query if 'location' does slot exist
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	location	The location we are checking.
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool DoesSlotExist(BodyLocation location);

	/**********************************************************************************************//**
	 * @fn	bool EntityClass::EquipAsWeapon(ObjectClass* weapon);
	 *
	 * @brief	Equip passed object as weapon, attempts to pass it to one hand slot and then the other handed slot
	 * 			returns false if no equippable hands
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param  weapon	If non-null, the weapon the function will attempt to equip.
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool EquipAsWeapon(ObjectClass* weapon);

	/**********************************************************************************************//**
	 * @fn	bool EntityClass::EquipMainHandWeapon(ObjectClass* weapon);
	 *
	 * @brief	Equip main hand weapon, tried to equip passed object into mainhand
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	weapon	If non-null, the weapon that will attempted to be placed in the mainhand
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool EquipMainHandWeapon(ObjectClass* weapon);

	/**********************************************************************************************//**
	 * @fn	bool EntityClass::EquipOffHandWeapon(ObjectClass* weapon);
	 *
	 * @brief	Equip off hand weapon, takes weapon and attempts to place it in the offhand
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	weapon	If non-null, the weapon that will be attempted to move into the offhand.
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool EquipOffHandWeapon(ObjectClass* weapon);

	/**********************************************************************************************//**
	 * @fn	void EntityClass::SwapWeaponHands();
	 *
	 * @brief	Swap weapons from mainhand to offhand and vice versa
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void SwapWeaponHands();

	/**********************************************************************************************//**
	 * @fn	void EntityClass::TwoHandWeapon();
	 *
	 * @brief	attempts to occupy both hands with the same weapon located in mainhand or undo a two handed weapon. if successful it
	 * 			will toggle the two handing status
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void TwoHandWeapon();

	/**********************************************************************************************//**
	 * @fn	void EntityClass::AddToBackPack(ObjectClass *object);
	 *
	 * @brief	Adds object to the back pack
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	object	If non-null, the object that will be attempted to add to the backpack.
	 **************************************************************************************************/

	void AddToBackPack(ObjectClass * object);

	/**********************************************************************************************//**
	 * @fn	void EntityClass::UnEquip(BodyLocation location);
	 *
	 * @brief	takes object located at the location passed and places it into the backpack, clearing where it was at the start
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	location	The location where the object will be removed.
	 **************************************************************************************************/

	void UnEquip(BodyLocation location);

	/**********************************************************************************************//**
	 * @fn	bool EntityClass::EquipArmor(ObjectClass* armor);
	 *
	 * @brief	Equip armor function tries to take object passed to it and equip it into the body slot
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	armor If non-null, the object that will be placed into body slot if possible
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool EquipArmor(ObjectClass* armor);

	/**********************************************************************************************//**
	 * @fn	void EntityClass::DropFromEquipment(BodyLocation location, std::vector<std::vector<Tile>>& TileMap);
	 *
	 * @brief	Drop from equipment, drops equipment located at location (if there is equipment there) to the ground
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param 		  	location	The location in equipment the item will be dropped from
	 * @param [in,out]	TileMap 	The tile map that the entity is located in, needed for updating items when dropped
	 **************************************************************************************************/

	void DropFromEquipment(BodyLocation location, std::vector<std::vector<Tile>>& TileMap);

	/**********************************************************************************************//**
	 * @fn	void EntityClass::DropFromBackPack(int index, std::vector<std::vector<Tile>>& TileMap);
	 *
	 * @brief	Drop from back pack, drops item in the backpack located at index to the entitys location
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param 		  	index  	Zero-based index of the backpack, zero being the first item. 
	 * @param [in,out]	TileMap	The tile map being used
	 **************************************************************************************************/

	void DropFromBackPack(int index, std::vector<std::vector<Tile>>& TileMap);

	/**********************************************************************************************//**
	 * @fn	bool EntityClass::EquipObject(ObjectClass* weapon);
	 *
	 * @brief	Equip object, attempts to equip it in objects listed slots
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	weapon	If non-null, the object being equipped.
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool EquipObject(ObjectClass* weapon);

	/**********************************************************************************************//**
	 * @fn	void EntityClass::EntityPickup(std::vector<std::vector<Tile>> &TileVector);
	 *
	 * @brief	Entity pickup, calls pickup tile to query user if they wish to pick up a tile or not
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	TileVector	The tile map active
	 **************************************************************************************************/

	void EntityPickup(std::vector<std::vector<Tile>> &TileVector);

	/**********************************************************************************************//**
	 * @fn	ObjectClass* EntityClass::EntityInventory(std::vector<std::vector<Tile>>&TileVector);
	 *
	 * @brief	Entity inventory, creates a menu object for user to interact with inventory and executes its run function, 
	 * 			returns objects if user selects one
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	TileVector	The tile map that is used in the encounter.
	 *
	 * @return	nullptr if no selected object, else a pointer to the ObjectClass.
	 **************************************************************************************************/

	ObjectClass* EntityInventory(std::vector<std::vector<Tile>>&TileVector);

	/**********************************************************************************************//**
	 * @fn	void EntityClass::EntityFeatMenu();
	 *
	 * @brief	Entity feat menu, creates feat menu and runs it for user to interact with their feats
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void EntityFeatMenu();

	/**********************************************************************************************//**
	 * @fn	ObjectClass* EntityClass::PickupTile(std::vector<std::vector<Tile>> &TileVector);
	 *
	 * @brief	Pickup tile, creates pickuptilemenu and executes it for player to interact, 
	 * 			returns pointer if user selects an item
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	TileVector	The tile vector.
	 *
	 * @return	null if it fails or user does not select an item, else a pointer to the ObjectClass selected.
	 **************************************************************************************************/

	ObjectClass* PickupTile(std::vector<std::vector<Tile>> &TileVector);

	//end equipment functions

	/**********************************************************************************************//**
	 * @fn	void EntityClass::SetAbilityScore(AbilityScoreType type, int amount);
	 *
	 * @brief	Sets ability score
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	type  	The type of score.
	 * @param	amount	The amount to set to.
	 **************************************************************************************************/

	void SetAbilityScore(AbilityScoreType type, int amount);

	/**********************************************************************************************//**
	 * @fn	void EntityClass::DisplayAbilityScores();
	 *
	 * @brief	Displays an ability scores to console
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void DisplayAbilityScores();

	/**********************************************************************************************//**
	 * @fn	std::vector<FeatClass>& EntityClass::GetFeats()
	 *
	 * @brief	Gets the feats
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The feats.
	 **************************************************************************************************/

	std::vector<FeatClass>& GetFeats() { return m_Feats; }

	/**********************************************************************************************//**
	 * @fn	std::vector<FeatClass> EntityClass::GetActiveFeats();
	 *
	 * @brief	Gets active feats
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The active feats vector of all feats active
	 **************************************************************************************************/

	std::vector<FeatClass> GetActiveFeats();

	/**********************************************************************************************//**
	 * @fn	std::vector<FeatClass*> EntityClass::GetToggleableFeats();
	 *
	 * @brief	Gets toggleable feats
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	Null if it fails or no feats found, else pointers to toggleable feats returned in vector .
	 **************************************************************************************************/

	std::vector<FeatClass*> GetToggleableFeats();

	/**********************************************************************************************//**
	 * @fn	int EntityClass::GetAbilityModifier(AbilityScoreType ability);
	 *
	 * @brief	Gets ability modifier
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	ability	The ability.
	 *
	 * @return	The ability modifier amount.
	 **************************************************************************************************/

	int GetAbilityModifier(AbilityScoreType ability);

	/**********************************************************************************************//**
	 * @fn	int EntityClass::GetAbilityScore(AbilityScoreType ability)
	 *
	 * @brief	Gets ability score
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	ability	The ability to be returned.
	 *
	 * @return	The ability score.
	 **************************************************************************************************/

	int GetAbilityScore(AbilityScoreType ability) { return m_AbilityScore[ability]; }

	/**********************************************************************************************//**
	 * @fn	int EntityClass::GetMaxDex();
	 *
	 * @brief	Gets maximum dex, calculates it based on equipment values. Iterates through finding the lowest max dex modifier
	 * 			in equipment and returns it
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The maximum dex modifier.
	 **************************************************************************************************/

	int GetMaxDex();

	/**********************************************************************************************//**
	 * @fn	int EntityClass::GetSide()
	 *
	 * @brief	Gets the team side
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The side the entity is on in the encounter
	 **************************************************************************************************/

	int GetSide() { return m_TeamSide; }

	/**********************************************************************************************//**
	 * @fn	int EntityClass::SetSide(int passed)
	 *
	 * @brief	Sets the entities teamside
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	passed	int that will be the entities new side.
	 *
	 * @return	the new side.
	 **************************************************************************************************/

	int SetSide(int passed) { m_TeamSide = passed; }

	/**********************************************************************************************//**
	 * @fn	bool EntityClass::IsTwoHanding();
	 *
	 * @brief	Query if this entity is two handing
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	True if two handing, false if not.
	 **************************************************************************************************/

	bool IsTwoHanding();

	/**********************************************************************************************//**
	 * @fn	ItemContainer& EntityClass::GetBackPack();
	 *
	 * @brief	Gets back pack object
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The back pack belonging to entity
	 **************************************************************************************************/

	ItemContainer& GetBackPack();

	/**********************************************************************************************//**
	 * @fn	virtual bool EntityClass::GetBlocksMovement()
	 *
	 * @brief	Gets if this entity blocks movement
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	virtual bool GetBlocksMovement() { return m_BlocksMovement; }

	/**********************************************************************************************//**
	 * @fn	virtual void EntityClass::SwitchBlocksMovement()
	 *
	 * @brief	toggles blocks movement value
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	virtual void SwitchBlocksMovement() { m_BlocksMovement = !m_BlocksMovement; }

	/**********************************************************************************************//**
	 * @fn	virtual void EntityClass::SetBlocksMovement(bool passed)
	 *
	 * @brief	Sets blocks movement
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	passed	new value for blocksmovement.
	 **************************************************************************************************/

	virtual void SetBlocksMovement(bool passed) { m_BlocksMovement = passed; }

	/**********************************************************************************************//**
	 * @fn	int EntityClass::GetInitiative()
	 *
	 * @brief	Gets the initiative
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The initiative of the entity
	 **************************************************************************************************/

	int GetInitiative() { return m_Initiative; }
	//TargetSystem* GetSelector() { return &Selector; }

	/**********************************************************************************************//**
	 * @fn	bool EntityClass::GetIsAlive()
	 *
	 * @brief	Gets is alive
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool GetIsAlive() { return m_isAlive;}

	/**********************************************************************************************//**
	 * @fn	void EntityClass::SetIsAlive(bool passed)
	 *
	 * @brief	Sets is alive
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	passed	True if passed.
	 **************************************************************************************************/

	void SetIsAlive(bool passed) { m_isAlive = passed; }

	/**********************************************************************************************//**
	 * @fn	bool EntityClass::isMeleeUnit();
	 *
	 * @brief	Query if this object is melee unit, determines based off of weapons held
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	True if melee unit, false if not.
	 **************************************************************************************************/

	bool isMeleeUnit();

	/**********************************************************************************************//**
	 * @fn	Direction EntityClass::GetMoveDirection()
	 *
	 * @brief	Gets move direction
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The move direction stored
	 **************************************************************************************************/

	Direction GetMoveDirection() { return m_MoveDirection; }

	/**********************************************************************************************//**
	 * @fn	void EntityClass::SetMoveDirection(Direction Passed)
	 *
	 * @brief	Sets move direction
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	Passed	The passed value will be the new move direction
	 **************************************************************************************************/

	void SetMoveDirection(Direction Passed) { m_MoveDirection = Passed; }

	/**********************************************************************************************//**
	 * @fn	void EntityClass::EndTurnResets()
	 *
	 * @brief	Ends turn resets, calls other reset functions
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void EndTurnResets() { ResetMovementLeft(); ResetActionLeft(); ResetReactionLeft(); }

	/**********************************************************************************************//**
	 * @fn	int EntityClass::GetMovementLeft()
	 *
	 * @brief	Gets movement left
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The movement left for the entity
	 **************************************************************************************************/

	int GetMovementLeft() { return m_MovementLeft; }

	/**********************************************************************************************//**
	 * @fn	void EntityClass::EntityDeath(EncounterInstance & Instance);
	 *
	 * @brief	Entity death
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	current encounter instance
	 **************************************************************************************************/

	void EntityDeath(EncounterInstance & Instance);

	/**********************************************************************************************//**
	 * @fn	void EntityClass::DropAllWornItems(Tile & tileloc, std::vector<std::vector<Tile>>&TileVector);
	 *
	 * @brief	Drop all worn items, drops everything from equipment, and everything in backpack at entitys location
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	tileloc   	The tilelocation of entity
	 * @param [in,out]	TileVector	The tile map being used
	 **************************************************************************************************/

	void DropAllWornItems(Tile & tileloc, std::vector<std::vector<Tile>>&TileVector);

	/**********************************************************************************************//**
	 * @fn	void EntityClass::ClearEquipmentInSlot(BodyLocation Location);
	 *
	 * @brief	Clears the equipment in slot described by Location
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	Location	The location in equipment to be cleared
	 **************************************************************************************************/

	void ClearEquipmentInSlot(BodyLocation Location);

protected:

private:

	//Collision box of the entity
	/** @brief	The box */
	SDL_Rect m_Box;
	/** @brief	True to blocks movement */
	bool m_BlocksMovement = true;
	/** @brief	True to attack both hands */
	bool m_AttackBothHands = false;
	//The location on the map the object is in (what tile)
	/** @brief	first is x value, second is y value */
	std::pair<unsigned, unsigned> m_Location = { 0,0 };
	/** @brief	True to attempt move */
	bool m_attemptMove;
	/** @brief	The move direction */
	Direction m_MoveDirection = STATIONARY;
	/** @brief	The face direction */
	Direction m_FaceDirection = SOUTH;

	/** @brief	The control setting */
	ControlMode m_ControlSetting = MOVEMODE;
	/** @brief	The path texture */
	std::string m_PathTexture = "clericMace.png";

	//for keeping track of who is on what side, used in AI and rendering
	/** @brief	The team side */
	int m_TeamSide = 0;
	/** @brief	The unarmed strike */
	ObjectClass m_UnarmedStrike;

	/** @brief	True if is alive, false if not */
	bool m_isAlive = true;
	/*Inherent statistics start*/
	//the string rep of the m_name of the entity, mostly for flavor and for user interaction
	/** @brief	Name of the entity */
	std::string m_EntityName = "Anonymous";

	//map of ability scores
	/** @brief	The ability score */
	std::map<AbilityScoreType, int> m_AbilityScore =
	{
	{STR, NULL},
	{DEX, NULL},
	{CON, NULL},
	{INT, NULL},
	{WIS, NULL},
	{CHA, NULL}
	};
	
	std::map<BodyLocation, ObjectClass*> m_Equipment =
	///< 11 slots
	{
		{HEAD, NULL}, //helmets n stuff
		{FACE, NULL},//masks, eyewear
		{TORSO, NULL},//shirts
		{BACK, NULL}, //capes
		{THROAT, NULL}, //necklaces / prepiats
		{ARM, NULL}, //bracers, bracelets
		{HAND, NULL}, //gloves, gauntlets
		{RING, NULL}, //magic rings
		{BODY, NULL}, //armor
		{WAIST, NULL},//belts / girdles
		{LEGS, NULL},//magic boots

		{MAINHAND, NULL}, //primary weapons or 2 hander
		{OFFHAND, NULL}
	};

	/** @brief	The back pack */
	ItemContainer m_BackPack;

	/**********************************************************************************************//**
	 * @property	std::vector <FeatClass> m_Feats
	 *
	 * @brief	Gets the feats
	 *
	 * @return	The m feats.
	 **************************************************************************************************/

	std::vector <FeatClass> m_Feats;

	/**********************************************************************************************//**
	 * @fn	void EntityClass::ResetMovementLeft()
	 *
	 * @brief	Resets the movement left
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void ResetMovementLeft() { m_MovementLeft = 3.0; }

	/**********************************************************************************************//**
	 * @fn	void EntityClass::ResetActionLeft()
	 *
	 * @brief	Resets the action left
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void ResetActionLeft() { m_ActionLeft = true; }

	/**********************************************************************************************//**
	 * @fn	void EntityClass::ResetReactionLeft()
	 *
	 * @brief	Resets the reaction left
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void ResetReactionLeft() { m_ReactionLeft = true; }
	
	/** @brief	The movement left */
	double m_MovementLeft = 3.0;
	/** @brief	The initiative */
	int m_Initiative = 0;
	/*Inherent Statistics end*/

	/*Derived Statistics Start*/
	/** @brief	The hit point maximum */
	int m_HitPointMaximum=20;
	/** @brief	The hit points */
	int m_HitPoints=m_HitPointMaximum;
	/** @brief	The base attack bonus */
	int m_BaseAttackBonus=0;
	/** @brief	The armor class */
	int m_ArmorClass=10;

	/** @brief	True to action left */
	bool m_ActionLeft = true;
	/** @brief	True to reaction left */
	bool m_ReactionLeft = true;

	/*Derived Statistics End*/

	/** @brief	The texture */
	LTexture* m_Texture;
	/** @brief	The side texture */
	LTexture* m_SideTexture;


	public:
		//mastercalls the other load functions

		/**********************************************************************************************//**
		 * @fn	bool EntityClass::LoadEntity(std::string m_name, std::pair<int, int> Location, bool PlayerControlled, int side, EncounterInstance &Instance);
		 *
		 * @brief	Loads an entity, its equipment, its feats, its statistics
		 *
		 * @author	Brendan B
		 * @date	8/31/2018
		 *
		 * @param 		  	m_name				The name of the entity being loeaded
		 * @param 		  	Location			The location of the entity
		 * @param 		  	PlayerControlled	True if player controlled.
		 * @param 		  	side				The side of the entity
		 * @param [in,out]	Instance			The encounter instance that is active
		 *
		 * @return	True if it succeeds, false if it fails.
		 **************************************************************************************************/

		bool LoadEntity(std::string m_name, std::pair<int, int> Location, bool PlayerControlled, int side, EncounterInstance &Instance);

		//loads the m_name of the character and its m_description if it has one

		/**********************************************************************************************//**
		 * @fn	bool EntityClass::LoadNameDescriptionAndTexture(std::ifstream &reader);
		 *
		 * @brief	Loads name description and texture, iterates through reader open to files
		 *
		 * @author	Brendan B
		 * @date	8/31/2018
		 *
		 * @param [in,out]	reader	The reader used to read file
		 *
		 * @return	True if it succeeds, false if it fails.
		 **************************************************************************************************/

		bool LoadNameDescriptionAndTexture(std::ifstream &reader);
		
		/**********************************************************************************************//**
		 * @fn	bool EntityClass::LoadAbilityScores(std::ifstream &reader);
		 *
		 * @brief	Loads ability scores for entity
		 *
		 * @author	Brendan B
		 * @date	8/31/2018
		 *
		 * @param [in,out]	reader	The reader used to read the file
		 *
		 * @return	True if it succeeds, false if it fails.
		 **************************************************************************************************/

		bool LoadAbilityScores(std::ifstream &reader);

		//loads equipment of character including their backpack inventory

		/**********************************************************************************************//**
		 * @fn	bool EntityClass::LoadEquipment(std::ifstream &reader, std::map<std::string, ObjectClass*> &MasterObjectList);
		 *
		 * @brief	Loads equipment on character
		 *
		 * @author	Brendan B
		 * @date	8/31/2018
		 *
		 * @param [in,out]	reader				The reader.
		 * @param [in,out]	MasterObjectList	[in,out] If non-null, list of master objects.
		 *
		 * @return	True if it succeeds, false if it fails.
		 **************************************************************************************************/

		bool LoadEquipment(std::ifstream &reader, std::map<std::string, ObjectClass*> &MasterObjectList);

		/**********************************************************************************************//**
		 * @fn	BodyLocation EntityClass::GetBodyLocation(std::string line);
		 *
		 * @brief	Gets body location by line, translates string to enum type
		 *
		 * @author	Brendan B
		 * @date	8/31/2018
		 *
		 * @param	line	The line.
		 *
		 * @return	The body location.
		 **************************************************************************************************/

		BodyLocation GetBodyLocation(std::string line);

		/**********************************************************************************************//**
		 * @fn	bool EntityClass::LoadFeats(std::ifstream &reader, EncounterInstance& Encounter);
		 *
		 * @brief	Loads the feats of the entity
		 *
		 * @author	Brendan B
		 * @date	8/31/2018
		 *
		 * @param [in,out]	reader   	The reader set to the file already open
		 * @param [in,out]	Encounter	The encounter class being used
		 *
		 * @return	True if it succeeds, false if it fails.
		 **************************************************************************************************/

		bool LoadFeats(std::ifstream &reader, EncounterInstance& Encounter);
	
	
		/**********************************************************************************************//**
		 * @fn	bool EntityClass::LoadProperties(std::ifstream &reader);
		 *
		 * @brief	Loads the properties max hit points and base attack bonus
		 *
		 * @author	Brendan B
		 * @date	8/31/2018
		 *
		 * @param [in,out]	reader	The reader.
		 *
		 * @return	True if it succeeds, false if it fails.
		 **************************************************************************************************/

		bool LoadProperties(std::ifstream &reader);
	};