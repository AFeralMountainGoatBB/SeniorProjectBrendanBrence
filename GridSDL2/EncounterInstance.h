#pragma once
#include "GeneralHeaders.h"
#include "Texture.h"
#include "Dot.h"
#include "Tile.h"
#include <map>
#include "EntityClass.h"
#include "PickupItemsMenu.h"
#include "Log.h"
#include "TargetSystem.h"

class EncounterInstance
{
	public:
	LTexture gDotTexture;
	LTexture gTileTexture;
	
	SDL_Texture * MenuPort;
	SDL_Texture * BottomPort;
	TTF_Font *gFont = NULL;
	SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
	//Event handler
	SDL_Event e;

	//tileset map
	std::map<std::string, std::string> SpriteSet;

	//pointer to the activeUnit whose turn it is
	EntityClass* ActiveUnit;
	void RollInitative(); 
	void NextInInitiative();
	//todo
	//vector<creatures>

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;
	
	//The window renderer
	SDL_Renderer* gRenderer = NULL;
	SDL_Rect camera = { 0, 0, (SCREEN_WIDTH/4)*3, (SCREEN_HEIGHT / 4) * 3 };

	EncounterInstance();

	void HandleEvents(SDL_Event &e);
	
	bool init(SDL_Renderer *&gRenderer, SDL_Window *&gWindow); // initializes SDL and window we are rendering too
	bool LoadAllMedia(SDL_Renderer *&Renderer, SDL_Rect &gTileClips);
	bool loadMedia(LTexture &gDotTexture, LTexture &gTileTexture, LTexture &mEntityTexture, SDL_Renderer *&Renderer, SDL_Rect &gTileClips);
	bool setTiles(SDL_Rect gTileClips[]);
	bool LoadSpriteSet();
	void ClipTileSheet(SDL_Rect gTileClips[]);
	void AllEntitySetTexture();
	void RenderAllEntities(SDL_Rect& camera, SDL_Renderer *& Renderer);

	//In encounter functions
	bool touchesWall(SDL_Rect box);

	bool checkCollision(SDL_Rect a, SDL_Rect b);

	//destruction functions
	void close(LTexture &gDotTexture, LTexture &gTileTexture, SDL_Renderer*& gRenderer, SDL_Window*& gWindow);

	//running game functions
	bool RunEncounter(); // master run function

	bool UpdateMap(); // update / draw cycle for map

	Tile GetTileAt(int x, int y);
	std::vector< std::vector<Tile>>& GetTileMap();

	void AllocateTileMap(int width, int height);
	void DebugTileMap();
	void RenderTiles(SDL_Rect camera, LTexture &gTileTexture, SDL_Rect gTileClips[], SDL_Renderer*& gRenderer);

	std::map<std::string, LTexture*>& GetTextures();
	
	void DisplayMasterObjectListNames();
	void DisplayMasterFeatListNames();

	//log functions
	void AddLog(std::string LogEntry);

	std::map<std::string, FeatClass*>& GetMasterFeatList() { return MasterFeatList; }
	
	TargetSystem& GetTargetSystem() { return TargetSys; }
	
	int GetMapHeight() { return TileMapHeight; }
	int GetMapWidth() { return TileMapWidth; }

private: 
	static const int TileMapWidth = LEVEL_WIDTH / TILE_WIDTH;
	static const int TileMapHeight = LEVEL_HEIGHT / TILE_HEIGHT;
	std::vector < std::vector < Tile> > TileMap;
	std::vector<EntityClass*> EntityList;
	std::list<EntityClass*> InitiativeList;
	std::vector<ObjectClass*> ObjectList;
	TargetSystem TargetSys;
	
	std::map<std::string, ObjectClass*> MasterObjectList;
	std::map<std::string, FeatClass*> MasterFeatList;
	
	Log ActionLog;

	//resources stuff
	std::string FontPath = "Data\\Fonts";
	std::string TextureFolderPath = "Data\\Textures"; //parent directory for textures
	std::string CharacterFolderPath = "Data\\Characters";
	std::string ItemFolderPath = "Data\\Items";
	std::string MapFolderPath = "Data\\Maps";
	std::string FeatFolderPath = "Data\\Feats";
	std::vector<std::string> WeaponLists = { "SimpleWeapons.txt", "MartialWeapons.txt", "ExoticWeapons.txt"};
	std::vector<std::string> ArmorLists = { "BaseArmorList.txt" };
	std::vector<std::string> FeatLists = { "BaseProficiencies.txt", "GeneralFeats.txt" };
	std::string CurrentMapPath = "";
	std::map<std::string, LTexture*> Textures;
	std::string TilePath = "";
	

	//loading functions 
public:
	std::string GetTextureFolderPath();
	void SetTextureFolderPath(std::string NewPath);

	std::string GetCharacterFolderPath();
	void SetCharacterFolderPath();

	std::string GetItemFolderPath();
	void SetItemFolderPath();

	std::map<std::string, ObjectClass*> & GetObjectList();

	//mastercalls all other load functions
	//passes map name to loadmap, gets location of objects and entities and constructs vectors of strings
	bool ScenarioLoad(std::string path); 

	//loads all loose objects on the tiles, passed by ScenarioLoad
	bool LoadObjectIntoTile(int x, int y, std::string name);

	bool LoadWeaponList(std::string path);
	bool LoadArmorList(std::string path);
	bool LoadFeatList(std::string line);
	bool AddEachWeaponFeat(std::ifstream& reader, int StartPos, WeaponType type);
	bool LoadFeat(std::ifstream &reader, int place);

	std::string RemoveComments(std::string line);
	//loads all 

};