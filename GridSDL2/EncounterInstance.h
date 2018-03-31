#pragma once
#include "GeneralHeaders.h"
#include "Texture.h"
#include "Dot.h"
#include "Tile.h"
#include <map>
#include "EntityClass.h"
#include "PickupItemsMenu.h"

class EncounterInstance
{
	public:
	LTexture gDotTexture;
	LTexture gTileTexture;
	LTexture mEntityTexture;
	LTexture ObjectTexture;
	LTexture KnifeTexture;

	//std::map<std::string, LTexture> Textures;

	SDL_Texture * MenuPort;
	SDL_Texture * BottomPort;
	SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
	//Event handler
	SDL_Event e;

	//tileset map
	std::map<std::string, std::string> SpriteSet;

	//The dot that will be moving around on the screen
	Dot dot;
	EntityClass man;
	EntityClass Dummy;
	std::unique_ptr<ObjectClass> Dagger= std::make_unique<ObjectClass>();
	//todo
	//vector<creatures>

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;
	SDL_Rect camera = { 0, 0, (SCREEN_WIDTH/4)*3, (SCREEN_HEIGHT / 4) * 3 };

	EncounterInstance();

	//loading functions
	
	bool init(SDL_Renderer *&gRenderer, SDL_Window *&gWindow); // initializes SDL and window we are rendering too
	bool LoadAllMedia(SDL_Renderer *&Renderer, SDL_Rect &gTileClips);
	bool loadMedia(LTexture &gDotTexture, LTexture &gTileTexture, LTexture &mEntityTexture, SDL_Renderer *&Renderer, SDL_Rect &gTileClips);
	bool setTiles(SDL_Rect gTileClips[]);
	bool LoadSpriteSet();
	void ClipTileSheet(SDL_Rect gTileClips[]);

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
	std::string GetTextureFolderPath();
	void SetTextureFolderPath(std::string NewPath);

	

private: 
	static const int TileMapWidth = LEVEL_WIDTH / TILE_WIDTH;
	static const int TileMapHeight = LEVEL_HEIGHT / TILE_HEIGHT;
	std::vector < std::vector < Tile> > TileMap;
	std::vector<EntityClass*> EntityList;
	std::vector<EntityClass*> InitiativeList;
	

	//texture stuff
	std::string TextureFolderPath = "Data\\Textures"; //parent directory for textures
	std::map<std::string, LTexture*> Textures;

	


	//loading functions 
public:
	//mastercalls all other load functions
	//passes map name to loadmap, gets location of objects and entities and constructs vectors of strings
	bool ScenarioLoad(std::string path); 

	//loads the map and tiles into memory (SetTiles)
	bool LoadMap(std::string path);

	//loads all entities passed by ScenarioLoad
	bool LoadEntities(std::vector<std::pair<std::string, int>> );

	//loads all loose objects on the tiles, passed by ScenarioLoad
	bool LoadObjects(std::vector<std::pair<std::string, int>> ObjectsAndLocation);

	//loads all 
};