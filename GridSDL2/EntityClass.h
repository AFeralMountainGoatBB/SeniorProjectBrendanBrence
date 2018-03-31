#pragma once
#include "SharedEnums.h"
#include "GeneralHeaders.h"
#include "Objects.h"
#include "ItemContainer.h"

class Tile;
class LTexture;

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
	void handleEvent(SDL_Event& e);

	//Moves the entity and checks for out of bounds and collision
	void move(std::vector<std::vector<Tile>> &TileVector);

	//combat functions
	bool EntityAttack(std::vector<std::vector<Tile>> &TileVector);
	EntityClass* EntityAttackTile(std::vector<std::vector<Tile>> &TileVector);
	bool MeleeAttackRoll(EntityClass &Target);
	int MeleeAttackDamage(EntityClass &Target);
	bool RangedAttackRoll(EntityClass &Target);
	int RangedAttackDamage(EntityClass &Target);
	void TakeDamage(int DamageRecived, DamageType DamageType);
	//end combat functions

	//combat Armor class functions
	const int GetArmorClass();
	const int GetTouchArmorClass();

	//end combat armor class functions


	//sets location
	void SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap);
	//sets where the entity will render
	void SetRendLocation(std::vector<std::vector<Tile>> &TileVector);
	//calculates the middle of the tile the entity will render at
	std::pair<int, int> CalcRendLocation(std::vector<std::vector<Tile>> &Map);
	void SetPath(std::string Path);
	std::string GetPath();
	//returns the location
	std::pair<int, int> GetLocation();

	//Centers the camera over the entity
	void setCamera(SDL_Rect& camera);

	//Shows the entity on the screen
	void render(SDL_Rect& camera, SDL_Renderer *& Renderer);

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
	void SetName(std::string name);
	std::string GetName();

	void SetTexture(std::map<std::string, LTexture*> &map, std::string path);

	LTexture* GetTexture();

	void DisplayEntireInventory();

	//equipment functions
	//getters
	ObjectClass* GetEquipmentInSlot(BodyLocation location); //returns whatever is equipped in location, null if nothing
	bool DoesSlotExist(BodyLocation location);
	ObjectClass* GetMainHandWeapon();
	ObjectClass* GetOffHandWeapon();
	ObjectClass* GetBodyEquip(); //body slot holds armor

	ObjectClass GetHeadEquip(); //helmets
	ObjectClass GetFaceEquip(); //masks and stuff
	ObjectClass GetArmsEquip(); // arms for bracers
	ObjectClass GetHandsEquip(); //gloves
	ObjectClass GetLegsEquip(); //magic boots
	//setters
	bool EquipAsWeapon(ObjectClass*);
	bool EquipMainHandWeapon(ObjectClass*);
	bool EquipOffHandWeapon(ObjectClass*);

	void EquipArmor(ObjectClass*);

	bool EquipObject(ObjectClass*);
	void EntityPickup(std::vector<std::vector<Tile>> &TileVector);
	ObjectClass* PickupTile(std::vector<std::vector<Tile>> &TileVector);
	//end equipment functions

protected:

private:

	//Collision box of the entity
	SDL_Rect mBox;
	//

	//The location on the map the object is in
	std::pair<int, int> mLocation = { 0,0 }; //first is x value, second is y value
	bool attemptMove;
	Direction MoveDirection = STATIONARY;
	Direction FaceDirection = SOUTH;

	ControlMode ControlSetting = MOVEMODE;
	std::string mPathTexture = "clericMace.png";

	/*Inherent statistics start*/
	//the string rep of the name of the entity, mostly for flavor and for user interaction
	std::string EntityName = "Anonymous";

	//map of ability scores
	std::map<AbilityType, int> AbilityScore =
	{
	{STR, NULL},
	{DEX, NULL},
	{CON, NULL},
	{INT, NULL},
	{WIS, NULL},
	{CHA, NULL}
	};

	std::vector<CreatureType> Type;

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
		bool LoadEntity(std::string name, int Location, bool PlayerControlled);

		//loads the name of the character and its description if it has one
		bool LoadNameAndDescription(std::ifstream reader);
		
		//loads the ability scores
		bool LoadAbilityScores(std::ifstream reader);

		//loads equipment of character including their backpack inventory
		bool LoadEquipment(std::ifstream reader);

		//loads feats of character 
		bool LoadFeats(std::ifstream reader);
		
		//loads properties of character not covered by ability scores, equipments and feats
		bool LoadProperties(std::ifstream reader);
	};