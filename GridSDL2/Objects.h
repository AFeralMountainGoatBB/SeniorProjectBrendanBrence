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
	virtual void SetName(std::string m_name);

	//WeaponType GetWeaponTypes();
	void AddWeaponType(WeaponType WeaponType);
	std::vector<WeaponType>& GetWeaponType();
	void SetWeaponTypes(std::vector<WeaponType> m_weaponTypes);

	std::pair<int, DiceType> GetDamageDice();
	void SetDamageDice(std::pair<int,DiceType> m_damageDice);

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

	//Centers the m_camera over the entity
	void setCamera(SDL_Rect& camera);

	//Shows the entity on the screen
	virtual LTexture* GetTexture();
	virtual void SetTexture(std::map<std::string, LTexture*> TextureMap, std::string Path);
	virtual void render(SDL_Rect& camera, SDL_Renderer *& Renderer);
	//end render and location functions

	void RemoveObject(std::vector<std::vector<Tile>> &Map, int index);

	virtual BodyLocation GetBodySlot();
	virtual void SetBodySlot(BodyLocation location) { m_BodySlot = location; }

	int GetRangeIncrement() { return m_RangeIncrement; }
	void SetRangeIncrement(int passed) { this->m_RangeIncrement = passed; }

	const float GetBaseWeight();
	void SetBaseWeight(float m_Weight);

	std::vector<DamageType>& GetDamageTypes();
	void AddDamageType(DamageType AddType);

	bool IsRangedWeapon();
	bool IsThrowingWeapon();
	bool IsLightWeapon();
	bool IsMeleeWeapon();

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

	virtual void SetPathTexture(std::string path) { m_PathTexture = path; }
	virtual std::string GetPathTexture() { return m_PathTexture; }
private:
	//render stuff (also some model stuff)
	SDL_Rect m_Box = { 0,0,70,70 };
	std::string m_PathTexture = "pixelknife.png";
	LTexture* m_Texture;
	std::pair<int, int> m_Location = { 0,0 };

	//The dimensions of the Entity
	int m_OBJECT_WIDTH = 70;
	int m_OBJECT_HEIGHT = 70;

	//Model information
	std::string m_ObjectName= "";
	std::string m_ObjectDescription = "";
	std::vector<WeaponType> m_weaponTypes = { }; //types of weapon this is, default improvised
	std::vector<DamageType> m_damageTypes = {};

	std::pair<int, DiceType> m_damageDice = { 1, D3 };
	float m_Weight=0.0; //how much does the item weigh? Unimportant save for carrying capacity and determining 2h for improvised weapons

	bool m_TwoHanded; //does it have to take up both hand slots?
	bool m_Versatile; //can it be weilded in 2 hands? (example, longsword)

	int m_RangeIncrement = 0;
	BodyLocation m_BodySlot=MAINHAND; //indicates where this weapon can be used (manhand and offhand are interchangable)

	int m_CritMultiplier=2;
	int m_CritThreat = 20;


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
	virtual void SetSpeedReduction(int m_speedReduction);

	virtual int GetEquipActions();
	virtual void SetEquipActions(int actions);

	virtual bool GetIsShield();
	virtual void SetIsShield(bool isShield);

	virtual std::vector<ArmorType> GetArmorTypes();
	virtual void AddArmorType(ArmorType added);

	virtual void DisplayArmorInfo();

	private:
		int m_armorBonus = 0;
		int m_damageReduction = 0;
		int m_maxDexBonus = 100;
		int m_armorCheckPenalty = 0;
		int m_speedReduction = 100;
		int m_equipActions = 1;
		bool m_isShield = false;

		//not loaded into master list
		
		std::vector<ArmorType> m_armorTypes = {};
};