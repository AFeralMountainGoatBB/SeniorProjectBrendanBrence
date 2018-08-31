#pragma once
#include "GeneralHeaders.h"
#include "Texture.h"
#include "Tile.h"
#include <map>
#include "EntityClass.h"
#include "PickupItemsMenu.h"
#include "Log.h"
#include "TargetSystem.h"
#include "EntityInfoDisplay.h"
#include "EncounterEndScreen.h"

class AIPlayer;

class EncounterInstance
{
	public:
	void RollInitative(); 
	void NextInInitiative();
	void RemoveDeadFromLists();

	void EndOfTurnChecks();
	void EndOfEncounterRound();
	bool CheckForEndOfEncounter();
	bool CheckPlayerWin();
	bool CheckAIWin();
	
	EncounterInstance();

	void HandleEvents(SDL_Event &m_event);
	
	bool init(SDL_Renderer *&gRenderer, SDL_Window *&m_EncounterWindow); // initializes SDL and m_window we are rendering to
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
	void close(LTexture &gTileTexture, SDL_Renderer*& gRenderer, SDL_Window*& m_EncounterWindow);

	//running game functions
	bool RunEncounter(); // master run function

	bool UpdateMap(); // update / m_draw cycle for map

	Tile & GetTileAt(int x, int y);
	std::vector< std::vector<Tile>>& GetTileMap();

	void AllocateTileMap(int width, int height);
	void DebugTileMap();
	void RenderTiles(SDL_Rect camera, LTexture &gTileTexture, SDL_Rect gTileClips[], SDL_Renderer*& gRenderer);

	std::map<std::string, LTexture*>& GetTextures();
	
	void DisplayMasterObjectListNames();
	void DisplayMasterFeatListNames();

	//log functions
	void AddLog(std::string LogEntry);

	std::map<std::string, FeatClass*>& GetMasterFeatList() { return m_MasterFeatList; }
	
	TargetSystem& GetTargetSystem() { return m_TargetSys; }
	
	int GetMapHeight() { return m_TileMapHeight; }
	int GetMapWidth() { return m_TileMapWidth; }

	ObjectClass& GetObjectFromMasterList(std::string m_name) { return *m_MasterObjectList[m_name]; }

private: 
	static const int m_TileMapWidth = g_LEVEL_WIDTH / g_TILE_WIDTH;
	static const int m_TileMapHeight = g_LEVEL_HEIGHT / g_TILE_HEIGHT;
	std::vector < std::vector < Tile> > m_TileMap;
	std::vector<EntityClass*> m_EntityList;
	std::list<EntityClass*> m_InitiativeList;
	std::vector<ObjectClass*> m_ObjectList;
	TargetSystem m_TargetSys;

	//The m_window we'll be rendering to
	SDL_Window* m_EncounterWindow = NULL;

	//The m_window renderer
	SDL_Renderer* m_Renderer = NULL;
	SDL_Rect m_camera = { 0, 0, (g_SCREEN_WIDTH / 4) * 3, (g_SCREEN_HEIGHT / 4) * 3 };


	SDL_Texture * m_MenuPort;
	SDL_Texture * m_BottomPort;
	TTF_Font *m_MasterFont = NULL;
	SDL_Rect m_EncounterTileClips[g_TOTAL_TILE_SPRITES];
	//Event handler
	SDL_Event m_event;

	//tileset map
	std::map<std::string, std::string> m_SpriteSet;

	//pointer to the activeUnit whose turn it is
	EntityClass* m_ActiveUnit;

	LTexture m_TileTexture;
	
	std::map<std::string, ObjectClass*> m_MasterObjectList;
	std::map<std::string, FeatClass*> m_MasterFeatList;
	
	Log m_ActionLog;
	EntityInfoDisplay m_InfoPanel;

	//resources stuff
	std::string m_FontPath = "Data\\Fonts";
	std::string m_TextureFolderPath = "Data\\Textures"; //parent directory for textures
	std::string m_CharacterFolderPath = "Data\\Characters";
	std::string m_ItemFolderPath = "Data\\Items";
	std::string m_MapFolderPath = "Data\\Maps";
	std::string m_FeatFolderPath = "Data\\Feats";
	std::vector<std::string> m_WeaponLists = { "SimpleWeapons.txt", "MartialWeapons.txt", "ExoticWeapons.txt"};
	std::vector<std::string> m_ArmorLists = { "BaseArmorList.txt" };
	std::vector<std::string> m_FeatLists = { "BaseProficiencies.txt", "GeneralFeats.txt" };
	std::string m_CurrentMapPath = "";
	std::map<std::string, LTexture*> m_Textures;
	std::string m_TilePath = "";
	

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
	//passes map m_name to loadmap, gets location of m_objects and entities and constructs vectors of strings
	bool ScenarioLoad(std::string path); 

	//loads all loose m_objects on the tiles, passed by ScenarioLoad
	bool LoadObjectIntoTile(int x, int y, std::string m_name);

	bool LoadWeaponList(std::string path);
	bool LoadArmorList(std::string path);
	bool LoadFeatList(std::string line);
	bool AddEachWeaponFeat(std::ifstream& reader, int StartPos, WeaponType type);
	bool LoadFeat(std::ifstream &reader, int place);

	std::string RemoveComments(std::string line);
	//loads all 

};