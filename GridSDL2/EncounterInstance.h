/**********************************************************************************************//**
 * @file	EncounterInstance.h.
 *
 * @brief	Declares the encounter instance class
 **************************************************************************************************/

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

 //fwd declaration of aiplayer to avoid circular dependencies
class AIPlayer;

/**********************************************************************************************//**
 * @class	EncounterInstance
 *
 * @brief	An encounter instance, controls the round and encompasses all the entities and information needed to run a round
 * 			also encompasses textures and secondary info
 *
 * @author	Brendan B
 * @date	8/31/2018
 **************************************************************************************************/

class EncounterInstance
{
	public:

	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::RollInitative();
	 *
	 * @brief	Roll initative, rolls d20 for everyone in the encounter and sets their initative score, which determines
	 * 			turn order
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void RollInitative(); 

	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::NextInInitiative();
	 *
	 * @brief	Next in initiative, finds the next unit in the initative order and changes the active unit
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void NextInInitiative();

	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::RemoveDeadFromLists();
	 *
	 * @brief	Removes the dead from lists, goes through all units and checks if they are alive or not and removes them if they arent
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void RemoveDeadFromLists();

	/**********************************************************************************************//**
	 * @fn	bool EncounterInstance::CheckForEndOfEncounter();
	 *
	 * @brief	Determines if the encounter has a winner and therefore if it is over
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	True if a winner is found, false if no winner.
	 **************************************************************************************************/

	bool CheckForEndOfEncounter();

	/**********************************************************************************************//**
	 * @fn	bool EncounterInstance::CheckPlayerWin();
	 *
	 * @brief	Determines if player won
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	True if player won, false if not.
	 **************************************************************************************************/

	bool CheckPlayerWin();

	/**********************************************************************************************//**
	 * @fn	bool EncounterInstance::CheckAIWin();
	 *
	 * @brief	Determines if AI won
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	True if ai won, false if not
	 **************************************************************************************************/

	bool CheckAIWin();

	/**********************************************************************************************//**
	 * @fn	EncounterInstance::EncounterInstance();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	EncounterInstance();

	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::HandleEvents(SDL_Event &m_event);
	 *
	 * @brief	Handles the event described by m_event
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	m_event	The event being processed
	 **************************************************************************************************/

	void HandleEvents(SDL_Event &m_event);

	/**********************************************************************************************//**
	 * @fn	bool EncounterInstance::init(SDL_Renderer *&a_Renderer, SDL_Window *&a_EncounterWindow);
	 *
	 * @brief	Initializes this object and initalizes SDL to be prepared to render
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	a_Renderer		 	[in,out] If non-null, the renderer to be initialized
	 * @param [in,out]	a_EncounterWindow	[in,out] If non-null, the encounter window to be initalized.
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool init(SDL_Renderer *&a_Renderer, SDL_Window *&a_EncounterWindow); // initializes SDL and m_window we are rendering to

	/**********************************************************************************************//**
	 * @fn	bool EncounterInstance::LoadAllMedia(SDL_Renderer *&Renderer, SDL_Rect &TileClips);
	 *
	 * @brief	Loads all media in the texture folder for the encounter to render properly
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	Renderer  	[in,out] If non-null, the renderer being used.
	 * @param [in,out]	TileClips	The tile clips map that is being loaded into
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool LoadAllMedia(SDL_Renderer *&Renderer, SDL_Rect &TileClips);


	/**********************************************************************************************//**
	 * @fn	bool EncounterInstance::setTiles(SDL_Rect gTileClips[]);
	 *
	 * @brief	Sets the tiles based on the set passed, clips the tiles and sets them
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	TileClips	The tile clip storage
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool setTiles(SDL_Rect TileClips[]);

	/**********************************************************************************************//**
	 * @fn	bool EncounterInstance::LoadSpriteSet();
	 *
	 * @brief	Loads sprite set that the tiles are clipped from
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool LoadSpriteSet();

	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::ClipTileSheet(SDL_Rect TileClips[]);
	 *
	 * @brief	Clip tile sheet, does the actual clipping
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	TileClips	The tile clip structure where the textures are stored
	 **************************************************************************************************/

	void ClipTileSheet(SDL_Rect TileClips[]);

	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::AllEntitySetTexture();
	 *
	 * @brief	All entity set texture, goes through every entity and loads textures from the main map into it
	 * 			
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void AllEntitySetTexture();

	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::RenderAllEntities(SDL_Rect& camera, SDL_Renderer *& Renderer);
	 *
	 * @brief	Renders all entities
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	camera  	The camera being used
	 * @param [in,out]	Renderer	[in,out] If non-null, the renderer being used
	 **************************************************************************************************/

	void RenderAllEntities(SDL_Rect& camera, SDL_Renderer *& Renderer);


	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::close(SDL_Renderer*& a_Renderer, SDL_Window*& a_EncounterWindow);
	 *
	 * @brief	Closes the encounter, destroys window and renderer and frees resources (textures) up
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	a_Renderer		 	[in,out] If non-null, the renderer.
	 * @param [in,out]	a_EncounterWindow	[in,out] If non-null, the encounter window.
	 **************************************************************************************************/

	void close( SDL_Renderer*& gRenderer, SDL_Window*& m_EncounterWindow);

	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::SetPorts(SDL_Rect& Bottom, SDL_Rect& TopRight, SDL_Rect & TopLeft);
	 *
	 * @brief	Sets the port dimensions to fit on the encounter window
	 *
	 * @author	Brendan B
	 * @date	9/3/2018
	 *
	 * @param [in,out]	Bottom  	The bottom port
	 * @param [in,out]	TopRight	The top right port
	 * @param [in,out]	TopLeft 	The top left port
	 **************************************************************************************************/

	void SetPorts(SDL_Rect& Bottom, SDL_Rect& TopRight, SDL_Rect & TopLeft);

	/**********************************************************************************************//**
	 * @fn	bool EncounterInstance::RunEncounter();
	 *
	 * @brief	master executes the encounter and handles the main game loop, the setup and such
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool RunEncounter(); // master run function

/**********************************************************************************************//**
 * @fn	void EncounterInstance::HandleUnitMode(bool &quitBool, AIPlayer& ActiveAIPlayer);
 *
 * @brief	Handles the unit mode for the active unit
 *
 * @author	Brendan B
 * @date	9/3/2018
 *
 * @param [in,out]	quitBool	  	True to quit bool.
 * @param [in,out]	ActiveAIPlayer	The active ai player.
 **************************************************************************************************/

void HandleUnitMode(bool &quitBool, AIPlayer& ActiveAIPlayer);

	/**********************************************************************************************//**
	 * @fn	bool EncounterInstance::UpdateMap(SDL_Rect &bottomport, SDL_Rect &topLeftPort, SDL_Rect &topRightPort);
	 *
	 * @brief	Updates the map and renders it
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	void UpdateMap(SDL_Rect &bottomport, SDL_Rect &topLeftPort, SDL_Rect &topRightPort); // update / draw cycle for map

	/**********************************************************************************************//**
	 * @fn	std::vector< std::vector<Tile>>& EncounterInstance::GetTileMap();
	 *
	 * @brief	Gets tile map
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The tile map.
	 **************************************************************************************************/

	std::vector< std::vector<Tile>>& GetTileMap();

	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::AllocateTileMap(int width, int height);
	 *
	 * @brief	Allocate tile map
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	width 	The width of the map in tiles
	 * @param	height	The height of the map in tiles
	 **************************************************************************************************/

	void AllocateTileMap(int width, int height);

	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::DebugTileMap();
	 *
	 * @brief	Debug tile map, prints to console tile types in grid
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void DebugTileMap();

	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::RenderTiles(SDL_Rect camera, LTexture &TileTexture, SDL_Rect TileClips[], SDL_Renderer*& a_Renderer);
	 *
	 * @brief	Renders the tiles, calls lower functions to render each tile sequentially in the proper place
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param 		  	camera			The camera being used
	 * @param [in,out]	TileTexture	The tile texture, of the texture that was clipped
	 * @param 		  	TileClips  	The tile clips setting
	 * @param [in,out]	a_Renderer   	[in,out] If non-null, the renderer being used
	 **************************************************************************************************/

	void RenderTiles(SDL_Rect camera, LTexture &TileTexture, SDL_Rect TileClips[], SDL_Renderer*& Renderer);

	/**********************************************************************************************//**
	 * @fn	std::map<std::string, LTexture*>& EncounterInstance::GetTextures();
	 *
	 * @brief	Gets the textures
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	Null if it fails, else the textures.
	 **************************************************************************************************/

	std::map<std::string, LTexture*>& GetTextures();

	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::DisplayMasterObjectListNames();
	 *
	 * @brief	Displays a master object list names to console
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void DisplayMasterObjectListNames();

	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::DisplayMasterFeatListNames();
	 *
	 * @brief	Displays a master feat list names to console
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 **************************************************************************************************/

	void DisplayMasterFeatListNames();


	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::AddLog(std::string LogEntry);
	 *
	 * @brief	Adds a log to the internal log storage to be displayed
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	LogEntry	The log entry being added
	 **************************************************************************************************/

	void AddLog(std::string LogEntry);

	/**********************************************************************************************//**
	 * @fn	std::map<std::string, FeatClass*>& EncounterInstance::GetMasterFeatList()
	 *
	 * @brief	Gets master feat list
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	Null if it fails, else the master feat list.
	 **************************************************************************************************/

	std::map<std::string, FeatClass*>& GetMasterFeatList() { return m_MasterFeatList; }

	/**********************************************************************************************//**
	 * @fn	TargetSystem& EncounterInstance::GetTargetSystem()
	 *
	 * @brief	Gets target system
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The target system.
	 **************************************************************************************************/

	TargetSystem& GetTargetSystem() { return m_TargetSys; }

	/**********************************************************************************************//**
	 * @fn	int EncounterInstance::GetMapHeight()
	 *
	 * @brief	Gets map height
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The map height.
	 **************************************************************************************************/

	int GetMapHeight() { return m_TileMapHeight; }

	/**********************************************************************************************//**
	 * @fn	int EncounterInstance::GetMapWidth()
	 *
	 * @brief	Gets map width
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The map width.
	 **************************************************************************************************/

	int GetMapWidth() { return m_TileMapWidth; }

	/**********************************************************************************************//**
	 * @fn	ObjectClass& EncounterInstance::GetObjectFromMasterList(std::string m_name)
	 *
	 * @brief	Gets object from master list by name
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	m_name	The name.
	 *
	 * @return	The object from master list.
	 **************************************************************************************************/

	ObjectClass& GetObjectFromMasterList(std::string m_name) { return *m_MasterObjectList[m_name]; }

private: 
	/** @brief	Width of the tile map */
	static const int m_TileMapWidth = g_LEVEL_WIDTH / g_TILE_WIDTH;
	/** @brief	Height of the tile map */
	static const int m_TileMapHeight = g_LEVEL_HEIGHT / g_TILE_HEIGHT;

	/** @brief	vector of vector of tiles */
	std::vector < std::vector < Tile> > m_TileMap;
	/** @brief	List of entities */
	std::vector<EntityClass*> m_EntityList;
	/** @brief	List of initiatives */
	std::list<EntityClass*> m_InitiativeList;
	/** @brief	List of objects */
	std::vector<ObjectClass*> m_ObjectList;
	/** @brief	Target system */
	TargetSystem m_TargetSys;

	/** @brief	The encounter window */
	SDL_Window* m_EncounterWindow = NULL;

	//The m_window renderer
	/** @brief	The renderer */
	SDL_Renderer* m_Renderer = nullptr;
	/** @brief	The camera */
	SDL_Rect m_camera = { 0, 0, (g_SCREEN_WIDTH / 4) * 3, (g_SCREEN_HEIGHT / 4) * 3 };


	/** @brief	The menu port */
	SDL_Texture * m_MenuPort;
	/** @brief	The bottom port */
	SDL_Texture * m_BottomPort;
	/** @brief	The master font */
	TTF_Font *m_MasterFont = NULL;
	/** @brief	The encounter tile clips[g total tile sprites] */
	SDL_Rect m_EncounterTileClips[g_TOTAL_TILE_SPRITES];
	//Event handler
	/** @brief	The event */
	SDL_Event m_event;

	//tileset map
	/** @brief	Set the sprite belongs to */
	std::map<std::string, std::string> m_SpriteSet;

	//pointer to the activeUnit whose turn it is
	/** @brief	The active unit */
	EntityClass* m_ActiveUnit;

	/** @brief	The tile texture */
	LTexture m_TileTexture;
	
	/** @brief	List of master objects */
	std::map<std::string, ObjectClass*> m_MasterObjectList;
	/** @brief	List of master feats */
	std::map<std::string, FeatClass*> m_MasterFeatList;
	
	/** @brief	The action log */
	Log m_ActionLog;
	/** @brief	The information panel */
	EntityInfoDisplay m_InfoPanel;

	//resources stuff
	/** @brief	Full pathname of the font file */
	std::string m_FontPath = "Data\\Fonts";
	/** @brief	parent directory for textures */
	std::string m_TextureFolderPath = "Data\\Textures";
	/** @brief	Full pathname of the character folder file */
	std::string m_CharacterFolderPath = "Data\\Characters";
	/** @brief	Full pathname of the item folder file */
	std::string m_ItemFolderPath = "Data\\Items";
	/** @brief	Full pathname of the map folder file */
	std::string m_MapFolderPath = "Data\\Maps";
	/** @brief	Full pathname of the feat folder file */
	std::string m_FeatFolderPath = "Data\\Feats";
	/** @brief	The weapon lists */
	std::vector<std::string> m_WeaponLists = { "SimpleWeapons.txt", "MartialWeapons.txt", "ExoticWeapons.txt"};
	/** @brief	The armor lists */
	std::vector<std::string> m_ArmorLists = { "BaseArmorList.txt" };
	/** @brief	The feat lists */
	std::vector<std::string> m_FeatLists = { "BaseProficiencies.txt", "GeneralFeats.txt" };
	/** @brief	Full pathname of the current map file */
	std::string m_CurrentMapPath = "";
	/** @brief	The textures */
	std::map<std::string, LTexture*> m_Textures;
	/** @brief	Full pathname of the tile file */
	std::string m_TilePath = "";

public:

	/**********************************************************************************************//**
	 * @fn	std::string EncounterInstance::GetFontFolderPath();
	 *
	 * @brief	Gets font folder path
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The font folder path.
	 **************************************************************************************************/

	std::string GetFontFolderPath() { return m_FontPath; }

	/**********************************************************************************************//**
	 * @fn	std::string EncounterInstance::GetTextureFolderPath();
	 *
	 * @brief	Gets texture folder path
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The texture folder path.
	 **************************************************************************************************/

	std::string GetTextureFolderPath();

	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::SetTextureFolderPath(std::string NewPath);
	 *
	 * @brief	Sets texture folder path
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	NewPath	Full pathname of the new file.
	 **************************************************************************************************/

	void SetTextureFolderPath(std::string NewPath) { m_TextureFolderPath = NewPath; }

	/**********************************************************************************************//**
	 * @fn	std::string EncounterInstance::GetCharacterFolderPath();
	 *
	 * @brief	Gets character folder path
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The character folder path.
	 **************************************************************************************************/

	std::string GetCharacterFolderPath();

	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::SetCharacterFolderPath();
	 *
	 * @brief	Sets character folder path
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 * 			
	 * @param	NewPath	Full pathname of the new file.
	 **************************************************************************************************/

	void SetCharacterFolderPath(std::string NewPath) { m_CharacterFolderPath = NewPath; }

	/**********************************************************************************************//**
	 * @fn	std::string EncounterInstance::GetItemFolderPath();
	 *
	 * @brief	Gets item folder path
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	The item folder path.
	 **************************************************************************************************/

	std::string GetItemFolderPath();

	/**********************************************************************************************//**
	 * @fn	void EncounterInstance::SetItemFolderPath();
	 *
	 * @brief	Sets item folder path
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 * 			
	 * @param	NewPath	Full pathname of the new file.
	 **************************************************************************************************/

	void SetItemFolderPath(std::string NewPath) { m_ItemFolderPath = NewPath; }

	/**********************************************************************************************//**
	 * @fn	std::map<std::string, ObjectClass*> & EncounterInstance::GetObjectList();
	 *
	 * @brief	Gets object list
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @return	Null if it fails, else the object list.
	 **************************************************************************************************/

	std::map<std::string, ObjectClass*> & GetObjectList();

	
	//passes map m_name to loadmap, gets location of m_objects and entities and constructs vectors of strings

	/**********************************************************************************************//**
	 * @fn	bool EncounterInstance::ScenarioLoad(std::string path);
	 *
	 * @brief	Scenario load, initializes SDL and does initial setup of encounter as well as mastercalling all other load functions
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	path	Full pathname of the scenario file
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool ScenarioLoad(std::string path); 


	/**********************************************************************************************//**
	 * @fn	bool EncounterInstance::LoadObjectIntoTile(int x, int y, std::string m_name);
	 *
	 * @brief	Loads objects into tile, called to load objects not on entities
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	x	  	The x coordinate where the object is located
	 * @param	y	  	The y coordinate where the object is located
	 * @param	m_name	The name of the object
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool LoadObjectIntoTile(int x, int y, std::string m_name);

	/**********************************************************************************************//**
	 * @fn	bool EncounterInstance::LoadWeaponList(std::string path);
	 *
	 * @brief	Loads weapon list, loads weapon list into master object list by parsing text file
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	path	Full pathname of the file.
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool LoadWeaponList(std::string path);

	/**********************************************************************************************//**
	 * @fn	bool EncounterInstance::LoadArmorList(std::string path);
	 *
	 * @brief	Loads armor list, loads armor list from parsing text file into master object list
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	path	Full pathname of the file.
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool LoadArmorList(std::string path);

	/**********************************************************************************************//**
	 * @fn	bool EncounterInstance::LoadFeatList(std::string line);
	 *
	 * @brief	Loads feat list, parses from text file to load feat into master feat list
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	line	The name of the file
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool LoadFeatList(std::string line);

	/**********************************************************************************************//**
	 * @fn	bool EncounterInstance::AddEachWeaponFeat(std::ifstream& reader, int StartPos, WeaponType type);
	 *
	 * @brief	Adds an each weapon feat, a type of feat that applies to every weapon type present in master enum
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	reader  	The reader that will load lines from text file
	 * @param 		  	StartPos	The start position of the reader
	 * @param 		  	type		The type of weapon being loaded
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool AddEachWeaponFeat(std::ifstream& reader, int StartPos, WeaponType type);

	/**********************************************************************************************//**
	 * @fn	bool EncounterInstance::LoadFeat(std::ifstream &reader, int place);
	 *
	 * @brief	Loads a normal feat from a file
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param [in,out]	reader	The reader reading from file
	 * @param 		  	place 	The place where the reader should start in the file
	 *
	 * @return	True if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool LoadFeat(std::ifstream &reader, int place);

	/**********************************************************************************************//**
	 * @fn	std::string EncounterInstance::RemoveComments(std::string line);
	 *
	 * @brief	Removes the comments in the line passed
	 *
	 * @author	Brendan B
	 * @date	8/31/2018
	 *
	 * @param	line	The line where comments will be removed
	 *
	 * @return	A std::string without comments
	 **************************************************************************************************/

	std::string RemoveComments(std::string line);

};