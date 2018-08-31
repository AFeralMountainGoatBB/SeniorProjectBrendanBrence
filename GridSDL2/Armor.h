#pragma once
#include "SharedEnums.h"
#include "GeneralHeaders.h"
#include "Objects.h"

class Tile;
class ArmorObject : public ObjectClass
{
public:
	ArmorObject();
	ArmorObject(const ArmorObject &Other);
	ArmorObject(ObjectClass &Other);

	void SetBodySlot(BodyLocation location) { m_BodySlot = location; }
	BodyLocation GetBodySlot() { return this->m_BodySlot; }

	const int GetArmorBonus();
	void SetArmorBonus(int bonus);

	int GetDamageReduction();
	void SetDamageReduction(int reduction);

	int GetMaxDexBonus();
	void SetMaxDex(int max);

	int GetArmorCheckPenalty();
	void SetArmorCheckPen(int penalty);

	int GetSpeedReduction();
	void SetSpeedReduction(int m_speedReduction);

	int GetEquipActions();
	void SetEquipActions(int actions);

	bool GetIsShield();
	void SetIsShield(bool isShield);

	std::vector<ArmorType> GetArmorTypes();
	void AddArmorType(ArmorType added);

	void DisplayArmorInfo();
	
	std::string GetName() { return m_ObjectName; }
	void SetName(std::string m_name) { m_ObjectName = m_name; }

	std::pair<int, int> GetLocation(){return m_Location;}

private:
	int m_armorBonus=0;
	int m_damageReduction=0;
	int m_maxDexBonus=0;
	int m_armorCheckPenalty=0;
	int m_speedReduction=0;
	int m_equipActions=0;
	bool m_isShield = false;

	//not loaded into master list
	
	std::vector<ArmorType> m_armorTypes = {};
	std::vector<WeaponType> m_weaponTypes = { IMPROVISED };
	std::vector<DamageType> m_damageTypes = {BLUNT};

	std::pair<int, DiceType> m_damageDice = { 1, D4 };
	//inherited values
	SDL_Rect m_Box = { 0,0,70,70 };
	std::string m_PathTexture = "Armor1.png";
	LTexture* m_Texture;
	std::pair<int, int> m_Location = { 0,0 };

	//The dimensions of the Entity
	int m_OBJECT_WIDTH = 70;
	int m_OBJECT_HEIGHT = 70;

	//Model information
	std::string m_ObjectName = "";
	std::string m_ObjectDescription = "";

	float m_Weight = 0.0; //how much does the item weigh? Unimportant save for carrying capacity and determining 2h for improvised weapons

	bool m_TwoHanded; //does it have to take up both hand slots?
	bool m_Versatile; //can it be weilded in 2 hands? (example, longsword)

	int m_RangeIncrement = 0;
	BodyLocation m_BodySlot = BODY; //indicates where this item can be used (manhand and offhand are interchangable)

	int m_CritMultiplier = 2;
	int m_CritThreat = 20;

public:
	//rendering functions
	LTexture * GetTexture() { return m_Texture; }
	void SetPathTexture(std::string path) { m_PathTexture = path; }
	std::string GetPathTexture() { return m_PathTexture; }
	void SetTexture(std::map<std::string, LTexture*> TextureMap, std::string Path);

	void SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap);
	//sets where the entity will render
	void SetRendLocation(std::vector<std::vector<Tile>> &TileVector);
	//calculates the middle of the tile the entity will render at
	std::pair<int, int> CalcRendLocation(std::vector<std::vector<Tile>> &Map);

	void render(SDL_Rect& camera, SDL_Renderer *& Renderer);

};