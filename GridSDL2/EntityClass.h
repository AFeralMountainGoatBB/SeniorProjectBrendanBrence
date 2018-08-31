#pragma once
#include "SharedEnums.h"
#include "GeneralHeaders.h"
#include "Objects.h"
#include "ItemContainer.h"
#include "Feats.h"
#include "AttackClass.h"
//#include "TargetSystem.h"

class Tile;
class LTexture;
class EncounterInstance;
class InventoryMenu;

/*
There are inherent statistics and derived statistics
Inherent statistics for all entities:
Ability scores:

Creature Type and subtypes (and race)

m_Feats and Abilities:
	Including proficiencies and languages

(Class characters) # of levels and what kind, Skill ranks
(Loaded characters) Current HP

Then derived stats will be calculated:
Max Hp,
AC, 
Attack values (ranged and melee per weapon)
Damage Values, 
Ability Modifiers,
Size Modifiers,
saving throws,
skill modifiers
*/

class EntityClass {
public:
	//constructors
	EntityClass(int xInitial, int yInitial, int HPMax, int HPCurrent);
	EntityClass();
	//~EntityClass();

	//The dimensions of the Entity
	int m_ENTITY_WIDTH = 80;
	int m_ENTITY_HEIGHT = 80;

	virtual ControlMode GetControlMode();
	virtual void SetControlMode(ControlMode NewControl);

	//Takes key presses and adjusts the entity's movements
	virtual void handleEvent(SDL_Event& m_event, EncounterInstance &Instance);

	//Moves the entity and checks for out of bounds and collision
	virtual bool move(std::vector<std::vector<Tile>> &TileVector);
	void RollInitiative();

	//combat functions
	bool EntityMeleeAttack(std::vector<std::vector<Tile>> &TileVector, EncounterInstance & Instance);
	EntityClass* EntityMeleeAttackTile(std::vector<std::vector<Tile>> &TileVector);
	bool EntityRangedAttack(std::vector<std::vector<Tile>>&TileVector, EncounterInstance &Instance);
	bool EntityRangedAttack(std::vector<std::vector<Tile>>&TileVector, EncounterInstance &Instance, EntityClass* Target);
	EntityClass* EntityRangedAttackTile(std::vector<std::vector<Tile>> &TileVector, EncounterInstance &Instance);

	int GetBaseAttackBonus() { return m_BaseAttackBonus; }
	ObjectClass& GetUnarmedStrike() { return m_UnarmedStrike; }
	void GenerateUnarmedStrike(EncounterInstance& Instance);
	void TakeDamage(int DamageRecived, DamageType DamageType);
	int GetTotalDamageReduction();
	//end combat functions

	//combat Armor class functions
	int GetArmorClass();
	int UpdateArmorClass();
	//const int GetTouchArmorClass();

	//end combat armor class functions

	bool GetAttackLeft() { return m_ActionLeft; }
	void SetAttackLeft(bool passed) { m_ActionLeft = passed; }

	//sets location
	virtual  void SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap);
	//sets where the entity will render
	virtual void SetRendLocation(std::vector<std::vector<Tile>> &TileVector);
	//calculates the middle of the tile the entity will render at
	virtual std::pair<int, int> CalcRendLocation(std::vector<std::vector<Tile>> &Map);
	virtual void SetPath(std::string Path);
	virtual std::string GetPath() { return m_PathTexture; }
	//returns the location
	virtual std::pair<int, int> GetLocation();

	//Centers the m_camera over the entity
	virtual void setCamera(SDL_Rect& camera);

	//Shows the entity on the screen
	virtual void render(SDL_Rect& camera, SDL_Renderer *& Renderer);

	//Getters
	const int GetHitPoints() { return m_HitPoints; }
	const int GetMaxHitPoints() { return m_HitPointMaximum; }
	void SetMaxHitPoints(int passed) { m_HitPointMaximum = passed; m_HitPoints = passed; }
	void SetBaseAttackBonus(int passed) { m_BaseAttackBonus = passed; }

	const bool IsBroke();

	//Setters
	void AddHitPoints(int addition);
	void SubHitPoints(int subtraction) { this->m_HitPoints -= subtraction; }
	void SetHitPoints(int SetHP) {	m_HitPoints = SetHP; }

	/*Calculating derived values*/
	void SetName(std::string m_name);
	std::string GetName();

	virtual void SetTexture(std::map<std::string, LTexture*> &map, std::string path);

	virtual LTexture* GetTexture();

	void DisplayEntireInventory();
	void DisplayFeats();

	//equipment functions
	//getters
	ObjectClass* GetEquipmentInSlot(BodyLocation location); //returns whatever is equipped in location, null if nothing
	bool DoesSlotExist(BodyLocation location);
	
	//setters
	bool EquipAsWeapon(ObjectClass*);
	bool EquipMainHandWeapon(ObjectClass*);
	bool EquipOffHandWeapon(ObjectClass*);
	void SwapWeaponHands();
	void TwoHandWeapon();

	void AddToBackPack(ObjectClass *);
	void UnEquip(BodyLocation location);
	bool EquipArmor(ObjectClass*);
	void DropFromEquipment(BodyLocation location, std::vector<std::vector<Tile>>& TileMap);
	void DropFromBackPack(int index, std::vector<std::vector<Tile>>& TileMap);

	bool EquipObject(ObjectClass*);
	void EntityPickup(std::vector<std::vector<Tile>> &TileVector);
	ObjectClass* EntityInventory(std::vector<std::vector<Tile>>&TileVector);
	void EntityFeatMenu();
	ObjectClass* PickupTile(std::vector<std::vector<Tile>> &TileVector);

	//end equipment functions

	void SetAbilityScore(AbilityScoreType type, int amount);
	void DisplayAbilityScores();

	std::vector<FeatClass>& GetFeats() { return m_Feats; }
	std::vector<FeatClass> GetActiveFeats();
	std::vector<FeatClass*> GetToggleableFeats();

	int GetAbilityModifier(AbilityScoreType ability);
	int GetAbilityScore(AbilityScoreType ability) { return m_AbilityScore[ability]; }
	int GetMaxDex();

	int GetSide() { return m_TeamSide; }
	int SetSide(int passed) { m_TeamSide = passed; }

	bool IsTwoHanding();
	bool IsDualWielding();

	ItemContainer& GetBackPack();

	virtual bool GetBlocksMovement() { return m_BlocksMovement; }
	virtual void SwitchBlocksMovement() { m_BlocksMovement = !m_BlocksMovement; }
	virtual void SetBlocksMovement(bool passed) { m_BlocksMovement = passed; }

	int GetInitiative() { return m_Initiative; }
	//TargetSystem* GetSelector() { return &Selector; }
	bool GetIsAlive() { return m_isAlive;}
	void SetIsAlive(bool passed) { m_isAlive = passed; }

	bool isMeleeUnit();

	Direction GetMoveDirection() { return m_MoveDirection; }
	void SetMoveDirection(Direction Passed) { m_MoveDirection = Passed; }
	void EndTurnResets() { ResetMovementLeft(); ResetActionLeft(); ResetReactionLeft(); }

	int GetMovementLeft() { return m_MovementLeft; }

	void EntityDeath(EncounterInstance & Instance);
	void DropAllWornItems(Tile & tileloc, std::vector<std::vector<Tile>>&TileVector);

	void ClearEquipmentInSlot(BodyLocation Location);

protected:

private:

	//Collision box of the entity
	SDL_Rect m_Box;
	bool m_BlocksMovement = true;
	bool m_AttackBothHands = false;
	//The location on the map the object is in (what tile)
	std::pair<unsigned, unsigned> m_Location = { 0,0 }; //first is x value, second is y value
	bool m_attemptMove;
	Direction m_MoveDirection = STATIONARY;
	Direction m_FaceDirection = SOUTH;

	ControlMode m_ControlSetting = MOVEMODE;
	std::string m_PathTexture = "clericMace.png";

	//for keeping track of who is on what side, used in AI and rendering
	int m_TeamSide = 0;
	ObjectClass m_UnarmedStrike;

	bool m_isAlive = true;
	/*Inherent statistics start*/
	//the string rep of the m_name of the entity, mostly for flavor and for user interaction
	std::string m_EntityName = "Anonymous";

	//map of ability scores
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
	{ //11 slots
		{HEAD, NULL}, //helmets n stuff
		{FACE, NULL},//masks, eyewear
		{TORSO, NULL},//shirts
		{BACK, NULL}, //capes
		{THROAT, NULL}, //necklaces / prepiats
		{ARM, NULL}, //bracers, bracelets
		{HAND, NULL}, //gloves, gauntlets
		{RING, NULL}, //magic rings, yo
		{BODY, NULL}, //armor
		{WAIST, NULL},//belts / girdles
		{LEGS, NULL},//magic boots

		{MAINHAND, NULL}, //primary weapons or 2 hander
		{OFFHAND, NULL}
	};

	ItemContainer m_BackPack;
	std::vector <FeatClass> m_Feats;
	

	void ResetMovementLeft() { m_MovementLeft = 3.0; }
	void ResetActionLeft() { m_ActionLeft = true; }
	void ResetReactionLeft() { m_ReactionLeft = true; }
	
	double m_MovementLeft = 3.0;
	int m_Initiative = 0;
	/*Inherent Statistics end*/

	/*Derived Statistics Start*/
	int m_HitPointMaximum=20;
	int m_HitPoints=m_HitPointMaximum;
	int m_BaseAttackBonus=0;
	int m_ArmorClass=10;

	bool m_ActionLeft = true;
	bool m_ReactionLeft = true;

	/*Derived Statistics End*/

	LTexture* m_Texture;
	LTexture* m_SideTexture;


	public:
		//mastercalls the other load functions
		bool LoadEntity(std::string m_name, std::pair<int, int> Location, bool PlayerControlled, int side, EncounterInstance &Instance);

		//loads the m_name of the character and its m_description if it has one
		bool LoadNameDescriptionAndTexture(std::ifstream &reader);
		
		//loads the ability scores
		bool LoadAbilityScores(std::ifstream &reader);

		//loads equipment of character including their backpack inventory
		bool LoadEquipment(std::ifstream &reader, std::map<std::string, ObjectClass*> &MasterObjectList);
		BodyLocation GetBodyLocation(std::string line);

		//loads feats of character 
		bool LoadFeats(std::ifstream &reader, EncounterInstance& Encounter);

		bool LoadLevels(std::ifstream &reader, EncounterInstance& Encounter);
		
		//loads properties of character not covered by ability scores, equipments and feats
		bool LoadProperties(std::ifstream &reader);
	};