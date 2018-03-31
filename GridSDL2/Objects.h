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
	std::string GetName();
	void SetName(std::string name);

	WeaponType GetWeaponTypes();
	void AddWeaponType(WeaponType WeaponType);
	void SetWeaponTypes(std::vector<WeaponType> WeaponTypes);

	DiceType GetDamageDice();
	void SetDamageDice(DiceType DamageDice);
	DiceType CalculateDamageDice();

	float GetWeight();
	void SetWeight(float weight);

	bool GetTwoHanded();
	void SetTwoHanded(bool isTwoHanded);

	//render and location functions
	//sets location
	void SetLocation(int x, int y, std::vector < std::vector < Tile> > &TileMap);
	//sets where the entity will render
	void SetRendLocation(std::vector<std::vector<Tile>> &TileVector);
	//calculates the middle of the tile the entity will render at
	std::pair<int, int> CalcRendLocation(std::vector<std::vector<Tile>> &Map);

	//returns the location
	std::pair<int, int> GetLocation();

	//Centers the camera over the entity
	void setCamera(SDL_Rect& camera);

	//Shows the entity on the screen
	LTexture* GetTexture();
	void SetTexture(std::map<std::string, LTexture*> TextureMap, std::string Path);
	void render(SDL_Rect& camera, SDL_Renderer *& Renderer);
	//end render and location functions

	void RemoveObject(std::vector<std::vector<Tile>> &Map, int index);

	BodyLocation GetBodySlot();
	void SetBodySlot(BodyLocation);


	float GetBaseWeight();
	void SetBaseWeight(float Weight);
private:
	//render stuff (also some model stuff)
	SDL_Rect mBox;
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
	DiceType DamageDice;
	float Weight=0.0; //how much does the item weigh? Unimportant save for carrying capacity and determining 2h for improvised weapons

	bool TwoHanded; //does it have to take up both hand slots?
	bool Versatile; //can it be weilded in 2 hands? (example, longsword)


	BodyLocation BodySlot=MAINHAND; //indicates where this weapon can be used (manhand and offhand are interchangable)

	int CritMultiplier;
	int CritThreat = 20;





	//loading functions
public:
	bool LoadObject();
	bool LoadNameAndDescription();
	bool LoadProperties();

};