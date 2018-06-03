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

Feats and Abilities:
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
	EntityClass(int xInitial, int yInitial, int HPMax, int HPCurrent, EntitySize ThisSize);
	EntityClass();

	//The dimensions of the Entity
	int ENTITY_WIDTH = 80;
	int ENTITY_HEIGHT = 80;

	ControlMode GetControlMode();
	void SetControlMode(ControlMode NewControl);

	//Takes key presses and adjusts the entity's movements
	virtual void handleEvent(SDL_Event& e, EncounterInstance &Instance);

	//Moves the entity and checks for out of bounds and collision
	virtual void move(std::vector<std::vector<Tile>> &TileVector);
	void RollInitiative();

	//combat functions
	bool EntityMeleeAttack(std::vector<std::vector<Tile>> &TileVector, EncounterInstance & Instance);
	EntityClass* EntityMeleeAttackTile(std::vector<std::vector<Tile>> &TileVector);
	bool EntityRangedAttack(std::vector<std::vector<Tile>>&TileVector, EncounterInstance &Instance);
	EntityClass* EntityRangedAttackTile(std::vector<std::vector<Tile>> &TileVector, EncounterInstance &Instance);

	int GetBaseAttackBonus() { return BaseAttackBonus; }
	ObjectClass GetUnarmedStrike();
	bool MeleeAttackRoll(EntityClass &Target);
	int MeleeAttackDamage(EntityClass &Target);
	bool RangedAttackRoll(EntityClass &Target);
	int RangedAttackDamage(EntityClass &Target);
	void TakeDamage(int DamageRecived, DamageType DamageType);
	int GetTotalDamageReduction();
	//end combat functions

	//combat Armor class functions
	const int GetArmorClass();
	//const int GetTouchArmorClass();

	//end combat armor class functions


	//sets location
	virtual  void SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap);
	//sets where the entity will render
	virtual void SetRendLocation(std::vector<std::vector<Tile>> &TileVector);
	//calculates the middle of the tile the entity will render at
	virtual std::pair<int, int> CalcRendLocation(std::vector<std::vector<Tile>> &Map);
	virtual void SetPath(std::string Path);
	virtual std::string GetPath() { return mPathTexture; }
	//returns the location
	virtual std::pair<int, int> GetLocation();

	//Centers the camera over the entity
	virtual void setCamera(SDL_Rect& camera);

	//Shows the entity on the screen
	virtual void render(SDL_Rect& camera, SDL_Renderer *& Renderer);

	//Getters
	const int GetHitPoints();
	const bool IsBroke();

	//Setters
	void UpdateArmorClass();
	void AddHitPoints(int addition);
	void SubHitPoints(int subtraction);
	void SetHitPoints(int SetHP);
	void RemoveHitPoints(int removal);
	void SetSize(EntitySize PassedSize);
	const EntitySize GetSize();

	/*Calculating derived values*/
	int TotalAttackBonus();
	int MaxHitPoints();
	void SetName(std::string name);
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

	std::vector<FeatClass>& GetFeats() { return Feats; }
	std::vector<FeatClass> GetActiveFeats();
	std::vector<FeatClass*> GetToggleableFeats();

	bool IsProne() { return isProne; }
	void SwitchProne() { isProne = !isProne; }

	int GetAbilityModifier(AbilityScoreType ability);
	int GetAbilityScore(AbilityScoreType ability) { return AbilityScore[ability]; }
	int GetMaxDex();



	bool IsTwoHanding();
	bool IsDualWielding();

	ItemContainer& GetBackPack();

	virtual bool GetBlocksMovement() { return BlocksMovement; }
	virtual void SwitchBlocksMovement() { BlocksMovement = !BlocksMovement; }
	virtual void SetBlocksMovement(bool passed) { BlocksMovement = passed; }

	int GetInitiative() { return Initiative; }
	//TargetSystem* GetSelector() { return &Selector; }
protected:

private:
//	TargetSystem Selector;
	int Initiative = 0;
	//Collision box of the entity
	SDL_Rect mBox;
	bool BlocksMovement = true;
	bool AttackBothHands = false;
	//The location on the map the object is in (what tile)
	std::pair<unsigned, unsigned> mLocation = { 0,0 }; //first is x value, second is y value
	bool attemptMove;
	Direction MoveDirection = STATIONARY;
	Direction FaceDirection = SOUTH;

	ControlMode ControlSetting = MOVEMODE;
	std::string mPathTexture = "clericMace.png";

	//for keeping track of who is on what side, used in AI and rendering
	int TeamSide = 0;
	ObjectClass UnarmedStrike;

	bool isProne = false;
	/*Inherent statistics start*/
	//the string rep of the name of the entity, mostly for flavor and for user interaction
	std::string EntityName = "Anonymous";

	//map of ability scores
	std::map<AbilityScoreType, int> AbilityScore =
	{
	{STR, NULL},
	{DEX, NULL},
	{CON, NULL},
	{INT, NULL},
	{WIS, NULL},
	{CHA, NULL}
	};

	//std::vector<CreatureType> Type;

	//std::vector<ObjectClass> Equipment;
	//std::vector<FeatClass> Feats;

	
	std::map<BodyLocation, ObjectClass*> Equipment =
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

	ItemContainer BackPack;
	std::vector <FeatClass> Feats;
	
	int HitPoints=HitPointMaximum;
	EntitySize ThisSize;
	/*Inherent Statistics end*/

	/*Derived Statistics Start*/
	int HitPointMaximum=20;
	int BaseAttackBonus=0;
	int ArmorClass=10;


	/*Derived Statistics End*/

	LTexture* mTexture;


	public:
		//mastercalls the other load functions
		bool LoadEntity(std::string name, std::pair<int, int> Location, bool PlayerControlled, int side, EncounterInstance &Instance);

		//loads the name of the character and its description if it has one
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