#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"
//#include "Tile.h"
#include "Texture.h"

class Tile;
class ObjectClass
{
public:
	ObjectClass();
	ObjectClass(const ObjectClass &other);
	void SetmBox(int x, int y, int w, int h);
	void DisplayObjectWeaponFacts();

	virtual std::string GetName();
	virtual void SetName(std::string name);

	//WeaponType GetWeaponTypes();
	void AddWeaponType(WeaponType WeaponType);
	std::vector<WeaponType>& GetWeaponType();
	void SetWeaponTypes(std::vector<WeaponType> WeaponTypes);

	std::pair<int, DiceType> GetDamageDice();
	void SetDamageDice(std::pair<int,DiceType> DamageDice);
	std::pair<int, DiceType> CalculateDamageDice();

	bool GetTwoHanded();
	void SetTwoHanded(bool isTwoHanded);

	bool GetVersatile();
	void SetVersatile(bool passed);

	void SetCritInformation(int range, int multiplier);
	std::pair<int, int> GetCritInformation();

	//render and location functions
	//sets location
	virtual void SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap);
	//sets where the entity will render
	virtual void SetRendLocation(std::vector<std::vector<Tile>> &TileVector);
	//calculates the middle of the tile the entity will render at
	virtual std::pair<int, int> CalcRendLocation(std::vector<std::vector<Tile>> &Map);

	//returns the location
	virtual std::pair<int, int> GetLocation();

	//Centers the camera over the entity
	void setCamera(SDL_Rect& camera);

	//Shows the entity on the screen
	virtual LTexture* GetTexture();
	virtual void SetTexture(std::map<std::string, LTexture*> TextureMap, std::string Path);
	virtual void render(SDL_Rect& camera, SDL_Renderer *& Renderer);
	//end render and location functions

	void RemoveObject(std::vector<std::vector<Tile>> &Map, int index);

	virtual BodyLocation GetBodySlot();
	virtual void SetBodySlot(BodyLocation location) { BodySlot = location; }

	const int GetRangeIncrement();
	void SetRangeIncrement(int increment);

	const float GetBaseWeight();
	void SetBaseWeight(float Weight);

	std::vector<DamageType>& GetDamageTypes();
	void AddDamageType(DamageType AddType);

	bool IsRangedWeapon();
	bool IsThrowingWeapon();

	void operator=(const ObjectClass* other)
	{
		mBox.x = other->mBox.x;
		mBox.y = other->mBox.y;
		mBox.h = other->mBox.h;
		mBox.w = other->mBox.w;

		mPathTexture = other->mPathTexture;
		ObjectName = other->ObjectName;
		ObjectDescription = other->ObjectDescription;

		TwoHanded = other->TwoHanded;
		Versatile = other->Versatile;
		for (auto i = other->WeaponTypes.begin(); i != other->WeaponTypes.end(); i++)
		{
			this->WeaponTypes.push_back(*i);
		}

		DamageDice.first = other->DamageDice.first;
		DamageDice.second = other->DamageDice.second;

		Weight = other->Weight;
		BodySlot = other->BodySlot;
		CritMultiplier = other->CritMultiplier;
		CritThreat = other->CritThreat;
	}

	virtual void SetPathTexture(std::string path) { mPathTexture = path; }
	virtual std::string GetPathTexture() { return mPathTexture; }
private:
	//render stuff (also some model stuff)
	SDL_Rect mBox = { 0,0,70,70 };
	std::string mPathTexture = "pixelknife.png";
	LTexture* mTexture;
	std::pair<int, int> mLocation = { 0,0 };

	//The dimensions of the Entity
	int OBJECT_WIDTH = 70;
	int OBJECT_HEIGHT = 70;

	//Model information
	std::string ObjectName= "";
	std::string ObjectDescription = "";
	std::vector<WeaponType> WeaponTypes = { IMPROVISED }; //types of weapon this is, default improvised
	std::vector<DamageType> DamageTypes = {};

	std::pair<int, DiceType> DamageDice = { 1, D3 };
	float Weight=0.0; //how much does the item weigh? Unimportant save for carrying capacity and determining 2h for improvised weapons

	bool TwoHanded; //does it have to take up both hand slots?
	bool Versatile; //can it be weilded in 2 hands? (example, longsword)

	int RangeIncrement = 0;
	BodyLocation BodySlot=MAINHAND; //indicates where this weapon can be used (manhand and offhand are interchangable)

	int CritMultiplier=2;
	int CritThreat = 20;


	//loading functions
public:
	bool LoadObject();
	bool LoadObjectByName(std::string line);
	bool LoadNameAndDescription();
	bool LoadProperties();


	//virtual functions
	
	virtual const int GetArmorBonus();
	virtual void SetArmorBonus(int bonus);

	virtual int GetDamageReduction();
	virtual void SetDamageReduction(int reduction);

	virtual int GetMaxDexBonus();
	virtual void SetMaxDex(int max);

	virtual int GetArmorCheckPenalty();
	virtual void SetArmorCheckPen(int penalty);

	virtual int GetSpeedReduction();
	virtual void SetSpeedReduction(int SpeedReduction);

	virtual int GetEquipActions();
	virtual void SetEquipActions(int actions);

	virtual bool GetIsShield();
	virtual void SetIsShield(bool isShield);

	virtual std::vector<ArmorType> GetArmorTypes();
	virtual void AddArmorType(ArmorType added);

	virtual void DisplayArmorInfo();

	private:
		int ArmorBonus = 0;
		int DamageReduction = 0;
		int MaxDexBonus = 100;
		int ArmorCheckPenalty = 0;
		int SpeedReduction = 100;
		int EquipActions = 1;
		bool IsShield = false;

		//not loaded into master list
		std::vector<Modifier> Modifiers = {};
		std::vector<ArmorType> ArmorTypes = {};
};