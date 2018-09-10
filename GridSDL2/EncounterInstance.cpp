#include "EncounterInstance.h"
#include "Armor.h"
#include "AIPlayer.h"
#include "InventoryMenu.h"

EncounterInstance::EncounterInstance()
{
}

bool EncounterInstance::init(SDL_Renderer *&a_Renderer, SDL_Window *&a_EncounterWindow)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create m_window
		a_EncounterWindow = SDL_CreateWindow("TableTopBattleMap", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, g_SCREEN_WIDTH, g_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (a_EncounterWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			std::cout << "Window created" << std::endl;
			//Create renderer for m_window
			a_Renderer = SDL_CreateRenderer(a_EncounterWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (a_Renderer == NULL)
			{
				printf("a_Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(a_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

SDL_Texture* loadTexture(std::string a_path, SDL_Renderer *& a_Renderer)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified a_path
	SDL_Surface* loadedSurface = IMG_Load(a_path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", a_path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(a_Renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", a_path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

//get every texture file, create corresponding texture with loadfromfile and store it in the encounter's map
bool EncounterInstance::LoadAllMedia(SDL_Renderer *&a_Renderer, SDL_Rect &a_TileClips)
{
	bool Success = true;
	//std::cout << "Loading gfont" << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
	m_MasterFont = TTF_OpenFont("Data//Fonts//Baldur.ttf", 20);
	m_ActionLog.SetFont(m_MasterFont);
	if (m_MasterFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		Success = false;
	}

	for (auto & Iterator : fs::directory_iterator(GetTextureFolderPath()))
	{
		m_Textures[Iterator.path().string()] = new LTexture();
	//	if(TempTexture.loadFromFile(Iterator.a_path().string(), a_Renderer))
		if (m_Textures[Iterator.path().string()]->loadFromFile(Iterator.path().string(), a_Renderer))
		{
			//m_Textures[Iterator.a_path().string()]= &TempTexture;
			std::cout << "Loaded " << Iterator.path().string() << std::endl;
			std::cout<< m_Textures[Iterator.path().string()]->getWidth() << std::endl;
			
		}
		else
		{
			std::cout << "Failed to load " << Iterator.path().string() << std::endl;
			Success = false;
		}

	}
	//std::cout << "Test" << m_Textures[GetTextureFolderPath() + "\\tiles.png"]->getWidth() << std::endl;
	
	
	if (!m_TileTexture.loadFromFile(m_SpriteSet["TileSet"], a_Renderer))
	{
		printf("Failed to load tile set texture!\n");
		Success = false;
	}
	
	//loadMenuPortTest

	m_MenuPort = loadTexture("menu background parchment 3 black background vertical.png", a_Renderer);
	//m_MenuPort = loadTexture("MenuPortTest.png", a_Renderer);
	m_BottomPort = loadTexture("menu background parchment 3 black background horizontal.png", a_Renderer);

	if (!m_MenuPort)
	{
		std::cout << "Failed to load m_MenuPort" << std::endl;
	}

	//loadBottomPortTest
	if (!m_BottomPort)
	{
		std::cout << "Failed to load m_BottomPort" << std::endl;
	}

	return Success;
}

void EncounterInstance::close(SDL_Renderer*& a_Renderer, SDL_Window*& a_EncounterWindow)
{
	//Deallocate tiles
	for (int i = 0; i < g_TOTAL_TILES; ++i)
	{
		//delete tiles
	}

	//Free loaded images
	for (auto it = m_Textures.begin(); it != m_Textures.end(); it++)
	{
		(*it).second->free();
	}

	//Destroy m_window	
	SDL_DestroyRenderer(a_Renderer);
	SDL_DestroyWindow(a_EncounterWindow);
	a_EncounterWindow = NULL;
	a_Renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool EncounterInstance::setTiles(SDL_Rect a_TileClips[])
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::cout << "Loading the map at: " << this->m_MapFolderPath + "\\" + this->m_CurrentMapPath << std::endl;
	std::ifstream map(this->m_MapFolderPath + "\\" + this->m_CurrentMapPath);

	//If the map couldn't be loaded
	if (!map)
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		AllocateTileMap(m_TileMapWidth, m_TileMapHeight);
		//Initialize the tiles
		for (int YPos = 0; YPos < m_TileMapHeight; YPos++)
		{
			for (int XPos = 0; XPos < m_TileMapWidth; XPos++)
			{		
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a_a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a_a valid tile number
			if ((tileType >= 0) && (tileType < g_TOTAL_TILE_SPRITES))
			{
			//	std::cout << "Tile type loaded" << std::endl;
				m_TileMap[XPos][YPos] = new Tile(x, y, tileType);
			//	m_TileMap[XPos][YPos].
				//tiles[i] = new Tile(a_x, a_y, tileType);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", YPos);
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += g_TILE_WIDTH;

			//If we've gone too far
			if (x >= g_LEVEL_WIDTH)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += g_TILE_HEIGHT;
			}
			}
			//std::cout << "Row Complete " << std::endl;
		//Clip the sprite sheet
		}
		DebugTileMap();
	}
		
	if (tilesLoaded)
		{
			ClipTileSheet(a_TileClips);		
		}
	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}

void EncounterInstance::DebugTileMap()
{
	for (unsigned y = 0; y < m_TileMap[0].size(); y++)
	{
		for (unsigned i = 0; i < m_TileMap.size(); i++)
		{
			std::cout << m_TileMap[i][y].getType() << "  ";
		}
		std::cout << std::endl;
	}
}

void EncounterInstance::ClipTileSheet(SDL_Rect a_TileClips[])
{
	a_TileClips[g_TILE_GRASS].x = 0;
	a_TileClips[g_TILE_GRASS].y = 0;
	a_TileClips[g_TILE_GRASS].w = g_TILE_WIDTH;
	a_TileClips[g_TILE_GRASS].h = g_TILE_HEIGHT;

	a_TileClips[g_TILE_DIRT].x = 0;
	a_TileClips[g_TILE_DIRT].y = 80;
	a_TileClips[g_TILE_DIRT].w = g_TILE_WIDTH;
	a_TileClips[g_TILE_DIRT].h = g_TILE_HEIGHT;

	a_TileClips[g_TILE_STONE].x = 0;
	a_TileClips[g_TILE_STONE].y = 160;
	a_TileClips[g_TILE_STONE].w = g_TILE_WIDTH;
	a_TileClips[g_TILE_STONE].h = g_TILE_HEIGHT;

	a_TileClips[g_TILE_TOPLEFT].x = 80;
	a_TileClips[g_TILE_TOPLEFT].y = 0;
	a_TileClips[g_TILE_TOPLEFT].w = g_TILE_WIDTH;
	a_TileClips[g_TILE_TOPLEFT].h = g_TILE_HEIGHT;

	a_TileClips[g_TILE_LEFT].x = 80;
	a_TileClips[g_TILE_LEFT].y = 80;
	a_TileClips[g_TILE_LEFT].w = g_TILE_WIDTH;
	a_TileClips[g_TILE_LEFT].h = g_TILE_HEIGHT;

	a_TileClips[g_TILE_BOTTOMLEFT].x = 80;
	a_TileClips[g_TILE_BOTTOMLEFT].y = 160;
	a_TileClips[g_TILE_BOTTOMLEFT].w = g_TILE_WIDTH;
	a_TileClips[g_TILE_BOTTOMLEFT].h = g_TILE_HEIGHT;

	a_TileClips[g_TILE_TOP].x = 160;
	a_TileClips[g_TILE_TOP].y = 0;
	a_TileClips[g_TILE_TOP].w = g_TILE_WIDTH;
	a_TileClips[g_TILE_TOP].h = g_TILE_HEIGHT;

	a_TileClips[g_TILE_CENTER].x = 160;
	a_TileClips[g_TILE_CENTER].y = 80;
	a_TileClips[g_TILE_CENTER].w = g_TILE_WIDTH;
	a_TileClips[g_TILE_CENTER].h = g_TILE_HEIGHT;

	a_TileClips[g_TILE_BOTTOM].x = 160;
	a_TileClips[g_TILE_BOTTOM].y = 160;
	a_TileClips[g_TILE_BOTTOM].w = g_TILE_WIDTH;
	a_TileClips[g_TILE_BOTTOM].h = g_TILE_HEIGHT;

	a_TileClips[g_TILE_TOPRIGHT].x = 240;
	a_TileClips[g_TILE_TOPRIGHT].y = 0;
	a_TileClips[g_TILE_TOPRIGHT].w = g_TILE_WIDTH;
	a_TileClips[g_TILE_TOPRIGHT].h = g_TILE_HEIGHT;

	a_TileClips[g_TILE_RIGHT].x = 240;
	a_TileClips[g_TILE_RIGHT].y = 80;
	a_TileClips[g_TILE_RIGHT].w = g_TILE_WIDTH;
	a_TileClips[g_TILE_RIGHT].h = g_TILE_HEIGHT;

	a_TileClips[g_TILE_WATER].x = 240;
	a_TileClips[g_TILE_WATER].y = 160;
	a_TileClips[g_TILE_WATER].w = g_TILE_WIDTH;
	a_TileClips[g_TILE_WATER].h = g_TILE_HEIGHT;
}

void EncounterInstance::AllocateTileMap(int a_width, int a_height)
{
	m_TileMap.resize(a_width);
	for (int i = 0; i < a_width; i++)
	{
		//std::cout << "Resizing " << i << std::endl;
		m_TileMap[i].resize(a_height);
	}
	std::cout << "Vectors Resized" << std::endl;
}

void EncounterInstance::RenderTiles(SDL_Rect a_camera, LTexture &a_TileTexture, SDL_Rect a_TileClips[], SDL_Renderer*& a_Renderer)
{
	for (unsigned y = 0; y < m_TileMap[0].size(); y++)
	{
		for (unsigned x = 0; x < m_TileMap.size(); x++)
		{
			//std::cout << "Rendering tile " << a_x << ", " << a_y << std::endl;
			m_TileMap[x][y].render(a_camera, a_TileTexture, a_TileClips, a_Renderer);
		}
	}
}

std::vector< std::vector<Tile>>& EncounterInstance::GetTileMap()
{
	//std::cout << "Returning tilemap" << std::endl;
	return m_TileMap;
}

std::map<std::string, LTexture*>& EncounterInstance::GetTextures()
{
	return m_Textures;
}

void EncounterInstance::RollInitative()
{
	m_InitiativeList.clear(); //make a_list empty

	//roll init for every entity and insert it into the a_list at the correct spot
	for (auto it = m_EntityList.begin(); it != m_EntityList.end(); it++)
	{
		std::cout << (*it)->GetName() << std::endl;
		(*it)->RollInitiative();

		for (auto ins = m_InitiativeList.begin(); ins != m_InitiativeList.end();)
		{
			if ((*it)->GetInitiative() > (*ins)->GetInitiative())
			{
				m_InitiativeList.insert(ins, (*it));
				break;
			}
			ins++;
			//check if it is the last element in initative
			if (ins == (m_InitiativeList.end()))
			{
				m_InitiativeList.push_back((*it));
			}
		}
		if (m_InitiativeList.empty())
		{
			m_InitiativeList.push_back((*it));
		}
	}

	std::cout << "m_Initiative:" << std::endl;
	for (auto it = m_InitiativeList.begin(); it != m_InitiativeList.end(); it++)
	{
		std::cout << "    " << (*it)->GetName() << std::endl;
	}
}

void EncounterInstance::NextInInitiative()
{
	//iterate through initative list
	for (auto it = m_InitiativeList.begin(); it != m_InitiativeList.end(); it++)
	{
		if (m_ActiveUnit == (*it))
		{
			it++;
			if (it == m_InitiativeList.end())
			{
				m_ActiveUnit = m_InitiativeList.front();
			}
			else
			{
				m_ActiveUnit = (*it);
			}
			return;
		}
	}
}

void EncounterInstance::RemoveDeadFromLists()
{
	auto it = m_InitiativeList.begin();

	while (it != m_InitiativeList.end()) {
		if ((*it)->GetHitPoints()<=0) {
			it = m_InitiativeList.erase(it);
		}
		else ++it;
	}

	auto ite = m_EntityList.begin();

	while (ite != m_EntityList.end()) {
		if ((*ite)->GetHitPoints() <= 0) {
			ite = m_EntityList.erase(ite);
		}
		else ++ite;
	}
	
}

void EncounterInstance::HandleEvents(SDL_Event &a_event)
{
	//If a_a key was pressed
	if (a_event.type == SDL_KEYDOWN && a_event.key.repeat == 0)
	{
		//change the location
		switch (a_event.key.keysym.sym)
		{
		case SDLK_SPACE: //next turn!
		{
			//reset values
			m_ActiveUnit->EndTurnResets();
			NextInInitiative();
			m_InfoPanel.DetermineAllLabels(*m_ActiveUnit, *this);
			m_InfoPanel.SetAllTextures(m_Renderer);
			break;
		}	
		}
	}
}

void EncounterInstance::SetPorts(SDL_Rect& a_Bottom, SDL_Rect& a_topRight, SDL_Rect & a_topLeft)
{
	a_topLeft.x = 0;
	a_topLeft.y = 0;
	a_topLeft.w = g_SCREEN_WIDTH / 4;
	a_topLeft.h = (g_SCREEN_HEIGHT / 4) * 3;

	a_topRight.x = (g_SCREEN_WIDTH / 4);
	a_topRight.y = 0;
	a_topRight.w = (g_SCREEN_WIDTH / 4) * 3;
	a_topRight.h = (g_SCREEN_WIDTH / 4) * 3;

	a_Bottom.x = 0;
	a_Bottom.y = (g_SCREEN_HEIGHT / 4) * 3;
	a_Bottom.h = (g_SCREEN_HEIGHT / 4);
	a_Bottom.w = g_SCREEN_WIDTH;

}

void EncounterInstance::HandleUnitMode(bool &a_quitBool, AIPlayer& a_ActiveAIPlayer)
{
	switch (m_ActiveUnit->GetControlMode())
	{
	case(MOVEMODE):
		if (m_ActiveUnit->move(GetTileMap()) == true)
		{
			m_InfoPanel.DetermineAllLabels(*m_ActiveUnit, *this);
			m_InfoPanel.SetAllTextures(m_Renderer);
		}
		break;
	case(MELEEATTACKMODE):
		m_ActiveUnit->EntityMeleeAttack(GetTileMap(), *this);
		a_quitBool = CheckForEndOfEncounter();
		m_InfoPanel.DetermineAllLabels(*m_ActiveUnit, *this);
		m_InfoPanel.SetAllTextures(m_Renderer);
		break;
	case(PICKUPMODE):
		m_ActiveUnit->EntityPickup(GetTileMap());
		m_ActiveUnit->SetControlMode(MOVEMODE);
		a_quitBool = CheckForEndOfEncounter();
		m_InfoPanel.DetermineAllLabels(*m_ActiveUnit, *this);
		m_InfoPanel.SetAllTextures(m_Renderer);
		break;
	case(INVENTORYMODE):
		m_ActiveUnit->EntityInventory(GetTileMap());
		m_ActiveUnit->SetControlMode(MOVEMODE);
		a_quitBool = CheckForEndOfEncounter();
		m_InfoPanel.DetermineAllLabels(*m_ActiveUnit, *this);
		m_InfoPanel.SetAllTextures(m_Renderer);
		break;
	case(FEATOPTIONMODE):
		m_ActiveUnit->EntityFeatMenu();
		m_ActiveUnit->SetControlMode(MOVEMODE);
		a_quitBool = CheckForEndOfEncounter();
		m_InfoPanel.DetermineAllLabels(*m_ActiveUnit, *this);
		m_InfoPanel.SetAllTextures(m_Renderer);
		break;
	case(RANGEDATTACKMODE):
		if (m_TargetSys.GetControlMode() == SELECTTARGETMODE)
		{
			m_ActiveUnit->SetControlMode(MOVEMODE);
			m_ActiveUnit->EntityRangedAttack(GetTileMap(), *this);
			m_TargetSys.SetControlMode(MOVEMODE);
			m_InfoPanel.DetermineAllLabels(*m_ActiveUnit, *this);
			m_InfoPanel.SetAllTextures(m_Renderer);
		}
		a_quitBool = CheckForEndOfEncounter();
		break;
	case (AIMODE):
		a_ActiveAIPlayer.AITurn(m_TileMap, *m_ActiveUnit, *this);
		//m_ActiveUnit->SetControlMode(MOVEMODE);
		a_quitBool = CheckForEndOfEncounter();
		m_ActiveUnit->EndTurnResets();
		NextInInitiative();
		m_InfoPanel.DetermineAllLabels(*m_ActiveUnit, *this);
		m_InfoPanel.SetAllTextures(m_Renderer);
		break;
	default:
		return;
	}
}

bool EncounterInstance::RunEncounter()
{
	//set up viewports, lefthandside is menu, bottom is log righthand side is map / gamescreen
	SDL_Rect topLeftViewport;
	SDL_Rect topRightViewPort;
	SDL_Rect BottomViewPort;
	
	SetPorts(BottomViewPort, topRightViewPort, topLeftViewport);

	m_ActionLog.Setup(m_TextureFolderPath, m_Textures, BottomViewPort, m_MasterFont);
	m_ActionLog.SetLogConstraints(BottomViewPort);
	m_InfoPanel.Setup(m_TextureFolderPath, m_Textures, topLeftViewport, m_MasterFont, m_Renderer);
	m_InfoPanel.SetPanelConstraints(topLeftViewport);

	bool m_quit = false;	
	AIPlayer EnemyPlayers;
	AllEntitySetTexture();
	RollInitative();
	m_ActiveUnit = m_InitiativeList.front();
	m_InfoPanel.DetermineAllLabels(*m_ActiveUnit, *this);
	m_InfoPanel.SetAllTextures(m_Renderer);
			while (!m_quit)
			{
				if (m_ActiveUnit->GetSide() != 1)
				{
					m_ActiveUnit->SetControlMode(AIMODE);
				}

				//Handle events on queue
				while (SDL_PollEvent(&m_event) != 0)
				{
					//User requests m_quit
					if (m_event.type == SDL_QUIT)
					{
						m_quit = true;
					}
					if (m_TargetSys.GetActive()==true)
					{
						m_TargetSys.handleEvent(m_event);
						m_TargetSys.move(m_TileMap);
					}
					else
					{
						m_ActiveUnit->handleEvent(m_event, *this);
					}
					
					m_ActionLog.HandleEvents(m_event);
					this->HandleEvents(m_event);
				}
				SDL_RenderSetViewport(m_Renderer, &BottomViewPort);

				//run controlling unit structure
				HandleUnitMode(m_quit, EnemyPlayers);
				UpdateMap(BottomViewPort, topLeftViewport, topRightViewPort);
			
			}

			EncounterEndScreen EndScreen;
			EndScreen.Show(CheckPlayerWin(), CheckAIWin());
			EndScreen.EndScreenRun();

		//Free resources and close SDL
			this->close(m_Renderer, m_EncounterWindow);
	return 0;
	return true;
}

void EncounterInstance::UpdateMap(SDL_Rect &bottomPort, SDL_Rect &topLeftPort, SDL_Rect &topRightPort)
{
	if (m_TargetSys.GetActive())
	{
		m_TargetSys.setCamera(m_camera);
	}
	else
	{
		m_ActiveUnit->setCamera(m_camera);
	}
	//Clear screen
	SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(m_Renderer);
	//	std::cout << "RenderClear" << std::endl;

	//Render level
	SDL_RenderSetViewport(m_Renderer, &topRightPort);
	//render tileset
	RenderTiles(m_camera, m_TileTexture, m_EncounterTileClips, m_Renderer);
	RenderAllEntities(m_camera, m_Renderer);

	//this is information of the selected unit renderport
	SDL_RenderSetViewport(m_Renderer, &topLeftPort);
	SDL_RenderCopy(m_Renderer, m_MenuPort, NULL, NULL);
	m_InfoPanel.RenderPanel(m_Renderer);

	//m_MenuPort.render(topLeftViewport.a_x, topLeftViewport.a_y, m_Renderer);
	//this is the log viewport
	SDL_RenderSetViewport(m_Renderer, &bottomPort);
	SDL_RenderCopy(m_Renderer, m_BottomPort, NULL, NULL);
	m_ActionLog.RenderLog(m_Renderer);
	//m_BottomPort.render(BottomViewPort.a_x, BottomViewPort.a_y, m_Renderer);

	//Update screen
	SDL_RenderPresent(m_Renderer);
}

void EncounterInstance::AddLog(std::string a_Log)
{
	m_ActionLog.AddLog(m_Renderer, a_Log);
}
std::string EncounterInstance::GetTextureFolderPath()
{
	return m_TextureFolderPath;
}

void EncounterInstance::AllEntitySetTexture()
{
	//std::cout << "Setting textures for entities" << std::endl;
	for (auto i = m_EntityList.begin(); i != m_EntityList.end(); i++)
	{
		(*i)->SetTexture(GetTextures(), GetTextureFolderPath());
	}
	m_TargetSys.SetTexture(GetTextures(), GetTextureFolderPath());
	std::cout << "Settings textures successfull" << std::endl;
}

void EncounterInstance::RenderAllEntities(SDL_Rect& a_camera, SDL_Renderer *& a_Renderer)
{
	for (auto i = m_EntityList.begin(); i != m_EntityList.end(); i++)
	{
		(*i)->render(a_camera, a_Renderer);
	}
	m_TargetSys.render(a_camera, a_Renderer);
}

bool EncounterInstance::LoadSpriteSet()
{
	//tileset sheet a_path
	m_SpriteSet["TileSet"] = GetTextureFolderPath() + "//tiles2.png";
	//m_objects sheet a_path

	return true;
}

std::string EncounterInstance::GetCharacterFolderPath()
{
	return m_CharacterFolderPath;
}

std::string EncounterInstance::GetItemFolderPath()
{
	return m_ItemFolderPath;
}

bool EncounterInstance::CheckForEndOfEncounter()
{
	bool playerWin = CheckPlayerWin();
	bool AIWin = CheckAIWin();

	if (playerWin == true)
	{
		//set m_message
		return true;
	}

	if (AIWin == true)
	{
		//set m_message
		return true;
	}
	
	return false;
}

bool EncounterInstance::CheckPlayerWin()
{
	bool win = true;
	for (auto it = m_EntityList.begin(); it!=m_EntityList.end(); it++)
	{
		if ((*it)->GetSide() != 1)
		{
			win = false;
		}
	} //end loop
	return win;
}

bool EncounterInstance::CheckAIWin()
{
	bool win = true;
	for (auto it = m_EntityList.begin(); it != m_EntityList.end(); it++)
	{
		if ((*it)->GetSide() == 1)
		{
			win = false;
		}
	}
	return win;
}

//loading functions
bool EncounterInstance::ScenarioLoad(std::string a_Path)
{
	if (!init(m_Renderer, m_EncounterWindow))
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		LoadSpriteSet();
		std::cout << "Init complete" << std::endl;
		if (!LoadAllMedia(m_Renderer, *m_EncounterTileClips))
		{
			std::cout << "Failed to load media!" << std::endl;
		}
		else
		{
			std::cout << "Loaded media successfully!" << std::endl;
		}
	}
	std::cout << "Trying to load " << a_Path << std::endl;
	std::string line = "";
	std::ifstream Scenario(a_Path);
	if (!Scenario)
	{
		std::cout << "File empty or error opening" << std::endl;
		return false;
	}

	if (Scenario.is_open())
	{
		//load feats, weapons, then armor
		for (auto i = m_FeatLists.begin(); i != m_FeatLists.end(); i++)
		{
			LoadFeatList((*i));
		}
		for (auto i = m_WeaponLists.begin(); i != m_WeaponLists.end(); i++)
		{
			LoadWeaponList((*i));
		}
		for (auto i = m_ArmorLists.begin(); i != m_ArmorLists.end(); i++)
		{
			LoadArmorList((*i));
		}
		
		bool Mapfound = false;
		bool EndCharacters = false;
		bool EndItems = false;

		while (getline(Scenario, line))
		{
			std::cout << line << std::endl;
			//remove comments
			line = RemoveComments(line);

			if (line.find("Map:")!=(std::string::npos)&&!Mapfound)
			{
				
			//	std::cout << a_line << std::endl;
				try {
					line = line.substr(line.find(":")+1);
					line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
					this->m_CurrentMapPath = line + ".map";
					this->setTiles(m_EncounterTileClips);
				}
				catch (std::exception const & error)
				{
					std::cout << "Error encountered in scenarioload" << error.what() << std::endl;
				}
			}

			if (line.find("Character:")!=std::string::npos && !EndCharacters)
			{
				//parse a_name and location
				int temploc=0;
				int tempSide = 0;
				std::pair<int, int> TempCharacterLocation = { 0,0 };
				std::string path="";
				std::string location = "";
				bool PlayerControlled = false;
				if (line.find("Player") != std::string::npos)
				{
					PlayerControlled = true;
				}
				try {
				temploc = line.find(":")+1;
				line = line.substr(temploc, line.length());
				line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
			//	std::cout << a_line << " No spaces, now we find a_path" << std::endl;

				path = line.substr(0, line.find_first_of(","));
				path = path + ".txt";
				location = line.substr(line.find(",")+1, line.length()-line.find(")")+1);
				std::cout << "a_path: " << path << std::endl;

				//std::cout << "Location: " << location << std::endl;
				location = location.substr(location.find_first_of("(")+1, line.length()-location.find_first_of(")")+1);
			//	std::cout << "location: " << location << std::endl;
				TempCharacterLocation.first = stoi(location.substr(0, location.find_first_of(",")));
				TempCharacterLocation.second = stoi(location.substr(location.find_first_of(",")+1, location.length()));

				line = line.substr(line.find_last_of(",")+1);
				std::cout << "Line: " << line << std::endl;
				tempSide = stoi(line);
				}
				catch (std::exception const & error)
				{
					std::cout << "error : " << error.what() << std::endl;
					std::cout << "Error in character section base file" << std::endl;
				}

				//create new character pointer in entitylist, call to load character
				m_EntityList.push_back(new EntityClass);
				std::cout << "Trying to load character with information:" << std::endl;
				std::cout << "a_Path:" << path << std::endl;
				std::cout << "Character location:" << TempCharacterLocation.first << ", " << TempCharacterLocation.second << std::endl;
				std::cout << "PlayerControlled: ";
				if (PlayerControlled)
					std::cout << "Yes" << std::endl;
				else
					std::cout << "No" << std::endl;
				std::cout << "On side: " << tempSide << std:: endl;
				//load new character from this a_line, will contain the a_path of the character, 
				//its position in this scenario and wether or not it is player controlled

				m_EntityList.back()->LoadEntity(path, TempCharacterLocation, PlayerControlled, tempSide, *this);
				
				//the character will be fully loaded at this point and we can move on
				continue;
			}

			if (line.find("Item:") != std::string::npos && !EndItems)
			{
				int temploc = 0;
				int tempSide = 0;
				std::pair<int, int> TempItemLocation = { 0,0 };
				std::string m_name = "";
				std::string location = "";
				try {
					temploc = line.find(":") + 1;
					line = line.substr(temploc, line.length());
					
					//	std::cout << a_line << " No spaces, now we find a_path" << std::endl;
					m_name = line.substr(0, line.find_first_of(","));
					line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
					location = line.substr(line.find(",") + 1);
					std::cout << "a_name: " << m_name << std::endl;

					std::cout << "Location: " << location << std::endl;
					location = location.substr(location.find_first_of("(") + 1, line.length() - location.find_first_of(")") + 1);
					std::cout << "location: " << location << std::endl;
					TempItemLocation.first = stoi(location.substr(0, location.find_first_of(",")));
					std::cout << location.substr(location.find_first_of(",") + 1, location.find_first_of(")") - location.find_first_of(",") + 1);
					TempItemLocation.second = stoi(location.substr(location.find_first_of(",") + 1, location.find_first_of(")") - location.find_first_of(",")+1));
				}
				catch (std::exception const & error)
				{
					std::cout << "error : " << error.what() << std::endl;
					std::cout << "Error in Item section base file" << std::endl;
				}

				//create new object in master object a_list
				std::cout << "Trying to load item with information:" << std::endl;
				std::cout << "Item location:" << TempItemLocation.first << ", " << TempItemLocation.second << std::endl;
				LoadObjectIntoTile(TempItemLocation.first, TempItemLocation.second, m_name);
				

				//the character will be fully loaded at this point and we can move on
				continue;
			}
		}
		Scenario.clear();
		Scenario.seekg(0, Scenario.beg);
	}

	return true;
}

bool EncounterInstance::LoadObjectIntoTile(int a_x, int a_y, std::string a_name)
{
	if (m_MasterObjectList.count(a_name))
	{
		if (a_x < m_TileMap.size() && a_y < m_TileMap.size() && a_x >= 0 && a_y >= 0)
		{	
		std::cout << "Object " << a_name << " found, loading" << std::endl;
		if (a_name.find("Armor") != std::string::npos || a_name.find("Shield") != std::string::npos)
		{
			//std::cout << "Object loading" << std::endl;
			ArmorObject* NewObject = new ArmorObject(*m_MasterObjectList[a_name]);
			//NewObject->DisplayObjectWeaponFacts();
			//NewObject->DisplayArmorInfo();
			NewObject->SetLocation(a_x, a_y, m_TileMap);
			//NewObject->SetTexture(m_Textures, m_TextureFolderPath);
			m_ObjectList.push_back(NewObject);
		//	m_ObjectList.back()->SetLocation(a_x, a_y, m_TileMap);
			//m_ObjectList.back()->SetRendLocation(m_TileMap);
			//m_ObjectList.back()->SetTexture(m_Textures, GetTextureFolderPath());
		}
		else 
		{
			//std::cout << "Object loading" << std::endl;
			//ObjectClass* NewObject = new ObjectClass(*m_MasterObjectList[a_name]);
			//NewObject->DisplayObjectWeaponFacts();
			//NewObject->DisplayArmorInfo();
			m_ObjectList.push_back(new ObjectClass(*m_MasterObjectList[a_name]));
			m_ObjectList.back()->SetLocation(a_x, a_y, m_TileMap);
			//m_ObjectList.back()->SetRendLocation(m_TileMap);
			m_ObjectList.back()->SetTexture(m_Textures, GetTextureFolderPath());
		}
		}
		else
		{
			std::cout << "Tile mentioned outside of bounds, not loading" << std::endl;
			return false;
		}
		
	}
	else
	{
		std::cout << "Object not found" << std::endl;
		return false;
	}
	return true;
}

bool EncounterInstance::LoadWeaponList(std::string a_list)
{
	//SimpleWeapons.txt
	//MartialWeapons.txt
	//ExoticWeapons.txt
	std::ifstream reader;
	reader.open(GetItemFolderPath() + "\\" + a_list);

	if (reader.is_open())
	{
		std::string line = "";
		std::string m_name = "";
		std::string TempString = "";
		std::cout << "Loading weapon a_list: " << a_list<< std::endl;
		try {
			while (getline(reader, line))
			{
				//remove comments
				if (line.find("//") != std::string::npos)
				{
					int endchar = line.find("//");
					line = line.substr(0, endchar);
					//	std::cout << "ResultAfterComment " << a_line << std::endl;
				}
				if (line.find_first_not_of(' ') == std::string::npos)
				{
					continue;
				}
				std::cout << "Raw a_line: " << line << std::endl;	

				m_name = line.substr(0, line.find_first_of(","));

				auto f = [](unsigned char c) { return isspace((int)c); };
				line.erase(std::remove_if(line.begin(), line.end(), f), line.end()); //remove all spaces
	
				//std::cout << "New object: " << a_name << std::endl;
				m_MasterObjectList.insert(std::pair<std::string, ObjectClass*>(m_name, new ObjectClass));
				m_MasterObjectList[m_name]->SetTexture(m_Textures, m_TextureFolderPath);
				line = line.substr(line.find(m_name + ',') + m_name.length() + 1);
				//std::cout << "Line no a_name " << a_line << std::endl;

				//get two handed
				if (line.find("m_TwoHanded") != std::string::npos)
				{
					m_MasterObjectList[m_name]->SetTwoHanded(true);
				}
				m_MasterObjectList[m_name]->SetName(m_name);
				//get damage --------------------------------
				TempString = line.substr(0, line.find(","));

				int tempint1 = stoi(TempString.substr(0, TempString.find("d")));
			//	std::cout << TempString.substr(0, TempString.find("d") - 1) << std::endl;
				int tempint2 = stoi(TempString.substr(TempString.find("d")+1));
			//	std::cout << numdice << " " << Damage << std::endl;
				m_MasterObjectList[m_name]->SetDamageDice(std::pair<int, DiceType>(tempint1, (DiceType)tempint2));

				//get crit multiplier ---------------------------------
				line = line.substr(line.find_first_of(",")+1);
			//	std::cout << a_line << std::endl;
				TempString = line.substr(0, line.find_first_of(","));
				//std::cout << TempString << std::endl;
				tempint1 = stoi(TempString.substr(0, TempString.find("/a_x")));
				tempint2 = stoi(TempString.substr(TempString.find("/a_x") + 2));
				m_MasterObjectList[m_name]->SetCritInformation(tempint1, tempint2);
				//std::cout << m_MasterObjectList[a_name]->GetCritInformation().first << m_MasterObjectList[a_name]->GetCritInformation().second << std::endl;
			
				//get range increment --------------------------------
				line = line.substr(line.find_first_of(",")+1);
				//std::cout << a_line << std::endl;
				TempString = line.substr(0, line.find_first_of(","));
				TempString = TempString.substr(0, TempString.find_first_of("ft"));
				tempint1 = stoi(TempString);
				m_MasterObjectList[m_name]->SetRangeIncrement(tempint1);
			//	std::cout << "range increment of " <<a_name << ": " << tempint1 << std::endl;
			//	std::cout << "range increment of " << a_name << ": " << m_MasterObjectList[a_name]->GetRangeIncrement()<< std::endl;

				//get base weight
				line = line.substr(line.find_first_of(",") + 1);
				TempString = line.substr(0, line.find_first_of("lb"));
				float TempWeight = stof(TempString);
			//	tempint1 = stoi(TempString);
				m_MasterObjectList[m_name]->SetBaseWeight(TempWeight);
			//	std::cout << "weight: " << TempWeight << std::endl;


				//get damage types ------------
				line = line.substr(line.find_first_of(",")+1);
			//	std::cout << a_line << std::endl;

				m_MasterObjectList[m_name]->GetWeaponType().clear();
				while (FindDamageType(line) != UNKNOWNDAMAGETYPE)
				{
					DamageType TempD = FindDamageType(line);
					m_MasterObjectList[m_name]->AddDamageType(TempD);	
					line.erase(line.find(DamageTypeTextMap[TempD]), DamageTypeTextMap[TempD].length());
					//a_line.erase(a_line.find(""
					//std::cout << "Adding m_damageTypes: " << a_line << std::endl;
					line = line.substr(line.find(",")+1);					
				}
				
				while (FindWeaponType(line) != UNKNOWNWEAPONTYPE)
				{
					WeaponType TempW = FindWeaponType(line);
					m_MasterObjectList[m_name]->AddWeaponType(TempW);
					line.erase(line.find(WeaponTypeTextMap[TempW]), WeaponTypeTextMap[TempW].length());
				//	std::cout << "adding weapon type:" << a_line << std::endl;
					
					if (line.find(",") == std::string::npos)
					{
						break;
					}
					//a_line = a_line.substr(a_line.find(",") + 1);
				}
				WeaponType TempW = FindWeaponType(a_list); //this a_line looks at what the a_list is called, and returns if it has simple, martial, or any other type in the a_name
				m_MasterObjectList[m_name]->AddWeaponType(TempW);
				//determine if weapon is versitile
				auto it = find(m_MasterObjectList[m_name]->GetWeaponType().begin(), m_MasterObjectList[m_name]->GetWeaponType().end(), LIGHT);
				if (it != m_MasterObjectList[m_name]->GetWeaponType().end())
				{
					m_MasterObjectList[m_name]->SetVersatile(false);
				}
				//std::cout << "m_Weapon Loaded:" << std::endl;
			//	m_MasterObjectList[a_name]->DisplayObjectWeaponFacts();
					//a_line structure is
					//Dagger, 			1d4, 19/x2, 10ft, 1lb, piercing, light, dagger
			}
			return true;
		}
		catch(std::exception const & error)
		{
			std::cout << "Error in loading m_objects: " << error.what() << std::endl;
			//return false;
		}
	}

}

bool EncounterInstance::LoadArmorList(std::string a_list)
{
	//3.5 armor a_list
	std::ifstream reader;
	reader.open(GetItemFolderPath() + "\\" + a_list);

	if (reader.is_open())
	{
		std::string line = "";
		std::string m_name = "";
		std::string TempString = "";
		//std::cout << "Loading armor a_list: " << a_list << std::endl;
		try {
			while (getline(reader, line))
			{
				line = RemoveComments(line);

				if (line.find_first_not_of(' ') == std::string::npos)
				{
					continue;
				}
				//std::cout << "Raw a_line: " << a_line << std::endl;	

				m_name = line.substr(0, line.find_first_of(","));

				line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end()); //remove all spaces
				line = line.substr(line.find(m_name) + m_name.length()+1);
				if (line.find("Shield") == std::string::npos)
				{
					m_name = m_name + " Armor";
				}
			//	std::cout << "New object: " << a_name << std::endl;
				ArmorObject* TempArmor= new ArmorObject;
			//	m_MasterObjectList.insert(std::pair<std::string, ObjectClass*>(a_name, new ArmorObject));
				
			//	std::cout << "Line no a_name " << a_line << std::endl;

				TempString = line.substr(0, line.find(","));
				int TempInt1 = stoi(TempString);
				TempArmor->SetArmorBonus(TempInt1);
				TempArmor->SetName(m_name);

				//std::cout <<"Tempstring " << TempString << std::endl;
				//std::cout << "m_armorBonus:" << stoi(TempString) << std::endl;
				//TempString = TempString.substr(1, TempString.find(","));
				//	std::cout << TempString << std::endl;

				//get damage reduction now
				line = line.substr(line.find(",")+1);
			//	std::cout << a_line << std::endl;
				TempString = line.substr(0, line.find(","));
				
				TempString = TempString.substr(0, TempString.find("/-"));
			//	std::cout << "dr? " << TempString << std::endl;
				TempArmor->SetDamageReduction(stoi(TempString));

				//max dex
				line = line.substr(line.find(",") + 1);
				TempString = line.substr(0, line.find(","));
				if (TempString.find("-")!=std::string::npos)
				{
					TempArmor->SetMaxDex(100);
				}
				else
				{
					//std::cout << "MaxDex " << stoi(TempString) << std::endl;
					TempArmor->SetMaxDex(stoi(TempString));
				}
				

				//m_armorCheckPenalty
				line = line.substr(line.find(",") + 1);
				TempString = line.substr(0, line.find(","));
			//	std::cout << "ACP " << stoi(TempString) << std::endl;
				TempArmor->SetArmorCheckPen(stoi(TempString));

				//get speed
				line = line.substr(line.find(",") + 1);
				TempString = line.substr(0, line.find(","));
			//	std::cout << "Speed " << TempString << std::endl;
				if (TempString.find("-") != std::string::npos)
				{
					TempArmor->SetSpeedReduction(100);
				}
				else
				{
					TempInt1 = stoi(TempString) / 5 / 2;
					TempArmor->SetSpeedReduction(TempInt1);
				}
				

				//get weight
				line = line.substr(line.find(",") + 1);
				TempString = line.substr(0, line.find(","));
				//std::cout << "m_Weight " << stoi(TempString) << std::endl;
				TempInt1 = stoi(TempString);
				TempArmor->SetBaseWeight((float)TempInt1);

				line = line.substr(line.find(",")+1);
			//	std::cout << "Define tag " << a_line << std::endl;

				if (line.find("Light") != std::string::npos)
				{
					TempArmor->SetPathTexture("LightArmor.png");
					TempArmor->AddArmorType(LIGHTARMOR);
					TempArmor->SetBodySlot(BODY);
				}
				if (line.find("Medium") != std::string::npos)
				{
					TempArmor->SetPathTexture("MediumArmor.png");
					TempArmor->AddArmorType(MEDIUMARMOR);
					TempArmor->SetBodySlot(BODY);
				}
				if (line.find("Heavy") != std::string::npos)
				{
					TempArmor->SetPathTexture("HeavyArmor.png");
					TempArmor->AddArmorType(HEAVYARMOR);
					TempArmor->SetBodySlot(BODY);
				}
				if (line.find("TowerShield") != std::string::npos)
				{
					TempArmor->SetPathTexture("TowerShield.png");
					TempArmor->AddArmorType(TOWERSHIELD);
					TempArmor->SetBodySlot(OFFHAND);
				}
				else if (line.find("Shield")!=std::string::npos)
				{
					TempArmor->SetPathTexture("Shield.png");
					TempArmor->AddArmorType(SHIELD);
					TempArmor->SetBodySlot(OFFHAND);
				}
				TempArmor->SetTexture(m_Textures, m_TextureFolderPath);
			//	std::cout << "Armor loaded" << std::endl;
				m_MasterObjectList[m_name] = TempArmor;
			//	m_MasterObjectList[a_name]->DisplayArmorInfo();
				//display armor facts
				//TempArmor->DisplayArmorInfo();
			}
		}
		catch (std::exception const & error)
		{
			std::cout << "Error in loading armor: " << error.what() << std::endl;
			//return false;
		}
	}
	return true;
}

std::map<std::string, ObjectClass*>& EncounterInstance::GetObjectList()
{
	return m_MasterObjectList;
}

bool EncounterInstance::LoadFeatList(std::string a_list)
{
	std::ifstream reader;
	reader.open(m_FeatFolderPath + "\\" + a_list);

	std::cout << "Loading featlist start:" <<a_list<< std::endl;

	if (reader.is_open())
	{
		std::string line = "";
		std::string m_name = "";
		std::string TempString = "";
		std::cout << "Loading feat a_list: " << a_list << std::endl;
		//get if it is a_a single feat or group of feats
		while (getline(reader, line))
		{
			line = RemoveComments(line);
			if (line.find("<Feat>") != std::string::npos)
			{
				int StartFeat = reader.tellg();
				LoadFeat(reader, StartFeat);
			}
		}
		//

	}
	return true;
}
bool EncounterInstance::LoadFeat(std::ifstream &a_reader, int a_startFeat)
{
	std::string line = "";
	std::string m_name = "";
	std::string m_description = "";
	std::string PreReq = "";
	std::string Bonuses = "";
	std::string Special = "";
	std::string Benefit = "";
	std::string BonusList = "";
	bool UsesRange = false;
	std::pair<int, int> range;
	bool Each = false;

	//remember at end of loop if each = true delete tempfeat and do not add it to masterlist, it will be empty
	FeatClass* TempFeat = new FeatClass;
	bool success = true;
	while (getline(a_reader, line) && Each == false)
	{
		try {
			line = RemoveComments(line);
			if (line.find("EACH") != std::string::npos)
			{
				Each = true;
				if (line.find("WEAPONTYPE") != std::string::npos)
				{
					//limit it to certain groups soon
					for (auto i = WeaponTypeTextMap.begin()++; i != WeaponTypeTextMap.end(), (*i).first != SIMPLE; i++)
					{
						if (!AddEachWeaponFeat(a_reader, a_startFeat, (*i).first))
						{
							success = false;
						}
					}
				}
				else if (line.find("ARMORTYPE") != std::string::npos)
				{
					for (auto i = ArmorTypeTextMap.begin(); i != ArmorTypeTextMap.end(); i++)
					{
						//AddEachArmorFeat();
					}
				}
				break;
			} //end if find EACH
			//std::cout << "Line loading feat:" << a_line << std::endl;
			if (line.find("</Feat>") != std::string::npos)
			{
				m_MasterFeatList[TempFeat->GetName()] = TempFeat;
				m_MasterFeatList[TempFeat->GetName()]->DisplayFeatFullInfo();
				break;
			}

			if (line.find("m_FeatName:") != std::string::npos)
			{
				line = line.substr(line.find("m_FeatName:"));
				m_name = line.substr(line.find(":") + 1);
				std::cout << "New Feat Name " << m_name << std::endl;
				TempFeat->SetName(m_name);
			}
			//start reading data
			if (line.find("FeatDescription:") != std::string::npos)
			{
				m_description = line;
				m_description = m_description.substr(line.find("\"") + 1, line.find_last_of("\"") - 1);
			//	std::cout << "FeatDescription:" << m_description << std::endl;
				TempFeat->SetDescription(m_description);
			}


			if (line.find("Benefit:") != std::string::npos)
			{
				Benefit = line.substr(line.find(":") + 1);
				//std::cout << "Benefit:" << Benefit << std::endl;
				if (Benefit.find("RANGE(") != std::string::npos)
				{
					//UsesRange = true;
					Bonuses = Benefit.substr(Benefit.find("RANGE("));
					Bonuses = Bonuses.substr(Bonuses.find("RANGE(") + 6, Bonuses.find(")") - 6);
					//std::cout << "Bonuses range: " << Bonuses << std::endl;
					std::string TempRange = Bonuses;
					//std::cout << TempRange.substr(0, TempRange.find("a_x")) << std::endl;
					range.first = std::stoi(TempRange.substr(0, TempRange.find("a_x")));
					range.second = std::stoi(TempRange.substr(TempRange.find("a_x") + 1));
					//std::cout << range.first << "a_x" << range.second << std::endl;
					TempFeat->SetRangeActivated(range.first, range.second);
					TempFeat->SetUsesRangeAbility(true);
				}
				Benefit = Benefit.substr(Benefit.find(",") + 1);
				while (Benefit.find(",") != std::string::npos || Benefit.find(".") != std::string::npos)
				{
					std::string TempString = "";
					if (Benefit.find(",") == std::string::npos)
					{
						TempString = Benefit.substr(0, Benefit.find("."));
					}
					else
					{
						TempString = Benefit.substr(0, Benefit.find(","));
					}
					//remove spaces
					TempString.erase(std::remove_if(TempString.begin(), TempString.end(), isspace), TempString.end());

				//	std::cout << "TempS: " << TempString << std::endl;
					if (TempString.find("AttackRoll") != std::string::npos)
					{
						std::string Affects = TempString.substr(TempString.find("AttackRoll") + 10);
						//std::cout << "AttackRoll affects: " << Affects << std::endl;
						
						if (TempFeat->GetUsesRangeAbility())
						{
							CircumstanceType CType = FindCircumstanceType(Affects);
							std::string sign = TempString.substr(TempString.find("RANGE") - 1, 1);
							//std::cout << sign << std::endl;
							if (sign == "-")
							{
								if (Affects.find("ALLWEAPONS-") != std::string::npos)
								{
									for (auto i = WeaponTypeTextMap.begin(); i != WeaponTypeTextMap.end(), (*i).first != SIMPLE; i++)
									{
										if (Affects.find((*i).second) != std::string::npos)
										{
											continue;
										}
										TempFeat->AddWeaponAttackBonusSubtract((*i).first, 0);
									}

								}
								else if (Affects.find("ALLWEAPONS") != std::string::npos)
								{
									for (auto i = WeaponTypeTextMap.begin(); i != WeaponTypeTextMap.end(), (*i).first != SIMPLE; i++)
									{
										TempFeat->AddWeaponAttackBonusSubtract((*i).first, 0);
									}
								}
								else if (CType != UNKNOWNCIRCUMSTANCE)
								{
									TempFeat->AddCircumstanceAttackBonusSubtract(CType, 0);
								}
							}//end sign ="-"
							else if (sign == "+")
							{
								if (Affects.find("ALLWEAPONS-") != std::string::npos)
								{
									for (auto i = WeaponTypeTextMap.begin(); i != WeaponTypeTextMap.end(), (*i).first != SIMPLE; i++)
									{
										if (Affects.find((*i).second) != std::string::npos)
										{
											continue;
										}
										TempFeat->AddWeaponAttackBonusAdd((*i).first, 0);
									}

								}
								else if (Affects.find("ALLWEAPONS") != std::string::npos)
								{
									for (auto i = WeaponTypeTextMap.begin(); i != WeaponTypeTextMap.end(), (*i).first != SIMPLE; i++)
									{
										TempFeat->AddWeaponAttackBonusAdd((*i).first, 0);
									}
								}
								else if (CType != UNKNOWNCIRCUMSTANCE)
								{
									TempFeat->AddCircumstanceAttackDamageAdd(CType, 0);
								}
							}//end sign = +
						} // end if(range found)
						else
						{
							//range not found, so it is a_a fixed amount
						//	std::cout << "Amount increase " << TempString.substr(0, TempString.find("AttackRoll")) << std::endl;
							int tempint1 = stoi(TempString.substr(0, TempString.find("AttackRoll")));
							CircumstanceType CType = FindCircumstanceType(Benefit);
							WeaponType TempWType = FindWeaponType(TempString);
							if (TempWType != UNKNOWNWEAPONTYPE)
							{
								TempFeat->AddWeaponAttackBonusAdd(TempWType, tempint1);
							}
							else if (CType != UNKNOWNCIRCUMSTANCE)
							{
								TempFeat->AddCircumstanceAttackDamageAdd(CType, tempint1);
							}
						}
					} //end if attack roll found

					if (TempString.find("DamageRoll") != std::string::npos)
					{
						std::string Affects = TempString.substr(TempString.find("DamageRoll") + 10);
						//std::cout << "DamageRoll affects: " << Affects << std::endl;

						if (TempFeat->GetUsesRangeAbility())
						{
							std::string sign = TempString.substr(TempString.find("RANGE") - 1, 1);
							//std::cout << sign << std::endl;
							CircumstanceType CType = FindCircumstanceType(Benefit);
							if (sign == "-")
							{
								if (Affects.find("ALLWEAPONS-") != std::string::npos)
								{
									for (auto i = WeaponTypeTextMap.begin(); i != WeaponTypeTextMap.end(), (*i).first != SIMPLE; i++)
									{
										if (Affects.find((*i).second) != std::string::npos)
										{
											continue;
										}
										TempFeat->AddWeaponDamageBonusSubtract((*i).first, 0);
									}
								}
								else if (Affects.find("ALLWEAPONS") != std::string::npos)
								{
									for (auto i = WeaponTypeTextMap.begin(); i != WeaponTypeTextMap.end(), (*i).first != SIMPLE; i++)
									{
										TempFeat->AddWeaponDamageBonusSubtract((*i).first, 0);
									}
								}
								else if (CType != UNKNOWNCIRCUMSTANCE)
								{
									TempFeat->AddCircumstanceAttackDamageSubtract(CType, 0);
								}
							}//end sign ="-"
							else if (sign == "+")
							{
								if (Affects.find("ALLWEAPONS-") != std::string::npos)
								{
									for (auto i = WeaponTypeTextMap.begin(); i != WeaponTypeTextMap.end(), (*i).first != SIMPLE; i++)
									{
										if (Affects.find((*i).second) != std::string::npos)
										{
											continue;
										}
										TempFeat->AddWeaponDamageBonusAdd((*i).first, 0);
									}

								}
								else if (Affects.find("ALLWEAPONS") != std::string::npos)
								{
									for (auto i = WeaponTypeTextMap.begin(); i != WeaponTypeTextMap.end(), (*i).first != SIMPLE; i++)
									{
										TempFeat->AddWeaponDamageBonusAdd((*i).first, 0);
									}
								}
								else if (CType != UNKNOWNCIRCUMSTANCE)
								{
									TempFeat->AddCircumstanceAttackDamageAdd(CType, 0);
								}
							}//end sign = +
						} // end if(range found)
						else
						{
							//range not found, so it is a_a fixed amount
							//std::cout << "Amount increase " << TempString.substr(0, TempString.find("DamageRoll")) << std::endl;
							int tempint1 = stoi(TempString.substr(0, TempString.find("DamageRoll")));

							//check for weapontype, if not weapontype then circumstance
							WeaponType TempWType = FindWeaponType(TempString);
							if (TempWType != UNKNOWNWEAPONTYPE)
							{
								TempFeat->AddWeaponDamageBonusAdd(TempWType, tempint1);
							}
							else
							{
								CircumstanceType TempCType = FindCircumstanceType(TempString);
								if (TempCType != UNKNOWNCIRCUMSTANCE)
								{
									TempFeat->AddCircumstanceAttackDamageAdd(TempCType, tempint1);
								}
							}
						}
					}//end if damageroll found

					if (TempString.find("Dodge") != std::string::npos)
					{
						std::string Affects = TempString.substr(TempString.find("Dodge") + 5);
						//std::cout << "Dodge affects: " << Affects << std::endl;

						if (TempFeat->GetUsesRangeAbility())
						{
							CircumstanceType CType = FindCircumstanceType(Affects);
							std::string sign = TempString.substr(TempString.find("RANGE") - 1, 1);
							//std::cout << sign << std::endl;
							if (sign == "-")
							{
								if (Affects.find("ALL-") != std::string::npos)
								{
									for (auto i = CircumstanceTypeTextMap.begin(); i != CircumstanceTypeTextMap.end(); i++)
									{
										if (Affects.find((*i).second) != std::string::npos)
										{
											continue;
										}
										TempFeat->AddCircumstanceArmorBonusSubtract((*i).first, 0);
									}

								}
								else if (Affects.find("ALL") != std::string::npos)
								{
									for (auto i = CircumstanceTypeTextMap.begin(); i != CircumstanceTypeTextMap.end(); i++)
									{
										TempFeat->AddCircumstanceArmorBonusSubtract((*i).first, 0);
									}
								}
								else if (CType != UNKNOWNCIRCUMSTANCE)
								{
									TempFeat->AddCircumstanceArmorBonusSubtract(CType, 0);
								}
							}//end sign ="-"
							else if (sign == "+")
							{
								if (Affects.find("ALL-") != std::string::npos)
								{
									for (auto i = CircumstanceTypeTextMap.begin(); i != CircumstanceTypeTextMap.end(); i++)
									{
										if (Affects.find((*i).second) != std::string::npos)
										{
											continue;
										}
										TempFeat->AddCircumstanceArmorBonusAdd((*i).first, 0);
									}

								}
								else if (Affects.find("ALL") != std::string::npos)
								{
									for (auto i = CircumstanceTypeTextMap.begin(); i != CircumstanceTypeTextMap.end(); i++)
									{
										TempFeat->AddCircumstanceArmorBonusAdd((*i).first, 0);
									}
								}
								else if (CType != UNKNOWNCIRCUMSTANCE)
								{
									TempFeat->AddCircumstanceArmorBonusAdd(CType, 0);
								}
							}//end sign = +
						} // end if(range found)
						else //range not found, so it is a_a fixed amount
						{
							//std::cout << "Amount increase " << TempString.substr(0, TempString.find("Dodge")) << std::endl;
							int tempint1 = stoi(TempString.substr(0, TempString.find("Dodge")));
							CircumstanceType CType = FindCircumstanceType(Benefit);
							if (TempString.find("ALL") != std::string::npos)
							{
								for (auto i = CircumstanceTypeTextMap.begin(); i != CircumstanceTypeTextMap.end(); i++)
								{
									if (TempString.find("ALL-") != std::string::npos && TempString.find((*i).second) != std::string::npos)
									{
										continue;
									}
									if (tempint1 > 0)
									{
										TempFeat->AddCircumstanceArmorBonusAdd((*i).first, 0);
									}
									else if (tempint1 < 0)
									{
										TempFeat->AddCircumstanceArmorBonusSubtract((*i).first, 0);
									}
								}
							}
							else if (CType != UNKNOWNCIRCUMSTANCE)
							{
								if (tempint1 > 0)
								{
									TempFeat->AddCircumstanceArmorBonusAdd(CType, tempint1);
								}
								else if (tempint1 < 0)
								{
									TempFeat->AddCircumstanceArmorBonusSubtract(CType, tempint1);
								}
							}

						}
					} //end if Dodge found

					if (TempString.find("Proficiency") != std::string::npos)
					{
						std::cout << "PROFICIENCY FEAT HERE!!!!" << std::endl;
						std::cout << "PROFICIENCY FEAT HERE!!!!" << std::endl;
						std::cout << "PROFICIENCY FEAT HERE!!!!" << std::endl;
						if (TempString.find("WeaponProficiency") != std::string::npos)
						{
							WeaponType WType = FindWeaponType(TempString);
							if (WType != UNKNOWNWEAPONTYPE)
							{
								TempFeat->AddWeaponProficiency(WType);
							}
						}
						if (TempString.find("ArmorProficiency") != std::string::npos)
						{
							ArmorType AType = FindArmorType(TempString);
							if (AType != UNKNOWNARMORTYPE)
							{
								TempFeat->AddArmorProficiency(AType);
							}
						}
					}

					if (FindAbilityScoreType(TempString) != UNKNOWNABILITYSCORETYPE)
					{
						AbilityScoreType AbType = FindAbilityScoreType(TempString);
						std::string Affects = TempString.substr(TempString.find(AbilityScoreTextMap[AbType]) + AbilityScoreTextMap[AbType].length());

						if (TempFeat->GetUsesRangeAbility())
						{
							CircumstanceType CType = FindCircumstanceType(Affects);
							std::string sign = TempString.substr(TempString.find("RANGE") - 1, 1);
							//std::cout << sign << std::endl;
							if (Affects.find("ALL") != std::string::npos)
							{
								for (auto i = CircumstanceTypeTextMap.begin(); i != CircumstanceTypeTextMap.end(); i++)
								{
									if (Affects.find("ALL-") != std::string::npos)
									{
										if (Affects.find((*i).second) != std::string::npos)
										{
											continue;
										}
									}
									if (sign == "-")
									{
										TempFeat->AddCircumstanceArmorBonusSubtract((*i).first, 0);
									}
									if (sign == "+")
									{
										TempFeat->AddCircumstanceArmorBonusAdd((*i).first, 0);
									}
								}
							}
							else if (CType != UNKNOWNCIRCUMSTANCE)
							{
								TempFeat->AddCircumstanceArmorBonusSubtract(CType, 0);
							}
						} // end if(range found)
						else //range not found, so it is a_a fixed amount
						{
							//std::cout << "Amount increase " << TempString.substr(0, TempString.find("Dodge")) << std::endl;
							int tempint1 = stoi(TempString.substr(0, TempString.find(AbilityScoreTextMap[AbType])));
							CircumstanceType CType = FindCircumstanceType(Benefit);
							if (TempString.find("ALL") != std::string::npos)
							{
								for (auto i = CircumstanceTypeTextMap.begin(); i != CircumstanceTypeTextMap.end(); i++)
								{
									if (TempString.find("ALL-") != std::string::npos && TempString.find((*i).second) != std::string::npos)
									{
										continue;
									}
									if (tempint1 > 0)
									{
										TempFeat->AddCircumstanceArmorBonusAdd((*i).first, tempint1);
									}
									else if (tempint1 < 0)
									{
										TempFeat->AddCircumstanceArmorBonusSubtract((*i).first, tempint1);
									}
								}
							}
							else if (CType != UNKNOWNCIRCUMSTANCE)
							{
								if (tempint1 > 0)
								{
									TempFeat->AddCircumstanceArmorBonusAdd(CType, tempint1);
								}
								else if (tempint1 < 0)
								{
									TempFeat->AddCircumstanceArmorBonusSubtract(CType, tempint1);
								}
							}
						}
					}

					if (TempString.find("Fortitude") != std::string::npos || TempString.find("Will") != std::string::npos || TempString.find("Reflex") != std::string::npos)
						{
						AbilityScoreType AbType = UNKNOWNABILITYSCORETYPE;
							if (TempString.find("Fortitude") != std::string::npos)
							{
								AbType = CON;
							}
							if (TempString.find("Will") != std::string::npos)
							{
								AbType = WIS;
							}
							if (TempString.find("Reflex") != std::string::npos)
							{
								AbType = DEX;
							}
							std::string Affects = TempString.substr(TempString.find(AbilityScoreTextMap[AbType]) + AbilityScoreTextMap[AbType].length());

							if (TempFeat->GetUsesRangeAbility())
							{
								/*
								CircumstanceType CType = FindCircumstanceType(Affects);
								std::string sign = TempString.substr(TempString.find("RANGE") - 1, 1);
								//std::cout << sign << std::endl;
								if (Affects.find("ALL") != std::string::npos)
								{
									for (auto i = CircumstanceTypeTextMap.begin(); i != CircumstanceTypeTextMap.end(); i++)
									{
										if (Affects.find("ALL-") != std::string::npos)
										{
											if (Affects.find((*i).second) != std::string::npos)
											{
												continue;
											}
										}
										if (sign == "-")
										{
											TempFeat->AddSaveBonus((*i).first, 0);
										}
										if (sign == "+")
										{
											TempFeat->AddCircumstanceArmorBonusAdd((*i).first, 0);
										}
									}
								}
								else if (CType != UNKNOWNCIRCUMSTANCE)
								{
									TempFeat->AddCircumstanceArmorBonusSubtract(CType, 0);
								}
								*/
							} // end if(range found)
							else //range not found, so it is a_a fixed amount
							{
								//std::cout << "Amount increase " << TempString.substr(0, TempString.find("Dodge")) << std::endl;
								int tempint1 = stoi(TempString.substr(0, TempString.find(AbilityScoreTextMap[AbType])));
								CircumstanceType CType = FindCircumstanceType(Benefit);
								if (TempString.find("ALL") != std::string::npos)
								{
									TempFeat->AddSaveBonus(AbType, tempint1);
								}
							}

							if (TempString.find("MovementBonus") != std::string::npos)
							{
								//todo
							}

							if (Benefit.find(",") == std::string::npos)
							{
								Benefit = Benefit.substr(Benefit.find(".") + 1);
							}
							else
							{
								Benefit = Benefit.substr(Benefit.find(",") + 1);
							}

						}

					//unfinished, functional for standard feats
					if (TempString.find("MovementSpeed") != std::string::npos)
					{
						std::string Affects = TempString.substr(TempString.find("MovementSpeed") + 13);
						//std::cout << "Amount increase " << TempString.substr(0, TempString.find("Dodge")) << std::endl;
						int tempint1 = stoi(TempString.substr(0, TempString.find("MovementSpeed")));
						ArmorType AmType = FindArmorType(Benefit);
						if (TempString.find("ALL") != std::string::npos)
						{
							for (auto i = CircumstanceTypeTextMap.begin(); i != CircumstanceTypeTextMap.end(); i++)
							{
								if (TempString.find("ALL-") != std::string::npos && TempString.find((*i).second) != std::string::npos)
								{
									continue;
								}
								if (tempint1 > 0)
								{
									TempFeat->AddCircumstanceArmorBonusAdd((*i).first, tempint1);
								}
								else if (tempint1 < 0)
								{
									TempFeat->AddCircumstanceArmorBonusSubtract((*i).first, tempint1);
								}
							}
						}
						else if (AmType != UNKNOWNARMORTYPE)
						{
							if (tempint1 > 0)
							{
								TempFeat->AddArmorMoveSpeedBonusAdd(AmType, tempint1);
							}
							else if (tempint1 < 0)
							{
								//TempFeat->AddArmorSpeedBonusSubtract(AmType, tempint1);
							}
						}
					}

					if (Benefit.find(",") != std::string::npos)
					{
						Benefit = Benefit.substr(Benefit.find(",") + 1);
					}
					else
					{
						Benefit = Benefit.substr(Benefit.find(".") + 1);
					}
					}
			}//end if find(benefit):

			if (line.find("Special:")!=std::string::npos)
			{
				std::string Special = line.substr(line.find(":") + 1);
				std::cout << "Special:" << Special << std::endl;
				std::string TempString;
				while (Special.find(",") != std::string::npos || Special.find(".") != std::string::npos)
				{
					if (Special.find(",") == std::string::npos)
					{
						TempString = Special.substr(0, Special.find("."));
					}
					else
					{
						TempString = Special.substr(0, Special.find(","));
					}
					//remove spaces
					TempString.erase(std::remove_if(TempString.begin(), TempString.end(), isspace), TempString.end());
					CircumstanceType CType = FindCircumstanceType(TempString);
					std::cout << "TempString: " << TempString << std::endl;
					if (CType != UNKNOWNCIRCUMSTANCE)
					{
						TempFeat->AddCircumstanceRequired(CType);
					}
					else if (TempString.find("Toggle") != std::string::npos)
					{
						TempFeat->SetToggleAbility(true);
					}
					if (Special.find(",") != std::string::npos)
					{
						Special = Special.substr(Special.find(",") + 1);
					}
					else
					{
						Special = Special.substr(Special.find(".") + 1);
					}

				}

			}
				}//end of try statement
				catch (std::exception & error)
				{
					std::cout << "Error in LoadFeat: " << error.what() << std::endl;
					return false;
				}
				if (Each)
				{
					return success;
				}
				
			}//end of while loop
			
			return true;
	}

//helper
std::string EncounterInstance::RemoveComments(std::string a_line)
{
	if (a_line.find("//") != std::string::npos)
	{
		int endchar = a_line.find("//");
		a_line = a_line.substr(0, endchar);
		//	std::cout << "ResultAfterComment " << a_line << std::endl;
	}
	return a_line;
}

bool EncounterInstance::AddEachWeaponFeat(std::ifstream & a_reader, int a_StartPos, WeaponType a_Wtype) 
{
	//start at beginning of feat
	a_reader.seekg(a_StartPos, std::ios::beg);

	std::string line;
	std::string TempString;
	std::string m_name;
	std::pair<WeaponType, int> TempBonus;
	int tempint1;
//	int tempint2;
	
	FeatClass* TempFeat = new FeatClass;

	while (getline(a_reader, line))
	{
		//start reading data, try block to stop stoi from crashing program from bad reads
		try {
			line = RemoveComments(line);

			//std::cout << "Line loading feat:" << a_line << std::endl;
			if (line.find("</Feat>") != std::string::npos)
			{
				break;
			}

			if (line.find("m_FeatName:") != std::string::npos)
			{
				line = line.substr(line.find("m_FeatName:"));
				m_name = line.substr(line.find(":")+1);
				std::string temp = "WEAPONTYPE EACH";
				
				m_name.replace(m_name.find("WEAPONTYPE"), temp.length(), WeaponTypeTextMap[a_Wtype]);
				TempFeat->SetName(m_name);
				std::cout << "New Feat Name " << m_name << std::endl;
			}
			
			if (line.find("FeatDescription:") != std::string::npos)
			{
				std::string m_description = line;
				m_description = m_description.substr(line.find("\"") + 1, line.find_last_of("\"") - 1);
			//	std::cout << "FeatDescription:" << m_description << std::endl;
				TempFeat->SetDescription(m_description);
			}

			if (line.find("Prerequisites:") != std::string::npos)
			{
				std::string PreReq = line.substr(line.find(":") + 1);
			//	std::cout << "PreReqs:" << PreReq << std::endl;
				//TBD later, when a_a leveling machine can be implemented, otherwise irrelevant as we wont check for illegal characters at loadtime
			}

			if (line.find("Benefit:") != std::string::npos)
			{
				std::string Benefit = "";
				std::string Bonuses = "";
				std::pair<int, int> range;
			//	ReplaceWeaponType(a_line, a_Wtype);

				Benefit = line.substr(line.find(":") + 1);
			//	std::cout << "Benefit:" << Benefit << std::endl;

				if (Benefit.find("RANGE(") != std::string::npos)
				{
					TempFeat->SetUsesRangeAbility(true);
					Bonuses = Benefit.substr(Benefit.find("RANGE("));
					Bonuses = Bonuses.substr(Bonuses.find("RANGE(") + 6, Bonuses.find(")") - 6);
					//	std::cout << "Bonuses range: " << Bonuses << std::endl;
					std::string TempRange = Bonuses;
					//std::cout << TempRange.substr(0, TempRange.find("a_x")) << std::endl;
					range.first = std::stoi(TempRange.substr(0, TempRange.find("a_x")));
					range.second = std::stoi(TempRange.substr(TempRange.find("a_x") + 1));
					//std::cout << range.first << "a_x" << range.second << std::endl;
				}			
				
				while (Benefit.find(",") != std::string::npos || Benefit.find(".") != std::string::npos)
				{
					
					std::string TempString = "";
					if (Benefit.find(",") == std::string::npos)
					{
						TempString = Benefit.substr(0, Benefit.find("."));
					}
					else
					{
						TempString = Benefit.substr(0, Benefit.find(","));
					}

					//std::cout << "TempString: " << TempString << std::endl;
					//remove spaces before parsing
					Benefit.erase(std::remove_if(Benefit.begin(), Benefit.end(), isspace), Benefit.end());
		
					//get the kind of bonus and amount, each feats always apply to whatever their EACH is
					if (TempString.find("AttackRoll") != std::string::npos)
					{	
							tempint1 = stoi(TempString.substr(0, TempString.find("AttackRoll")));
							TempFeat->AddWeaponAttackBonusAdd(a_Wtype, tempint1);
					}
					if (TempString.find("DamageRoll") != std::string::npos)
					{
							tempint1 = stoi(TempString.substr(0, TempString.find("DamageRoll")));
							TempFeat->AddWeaponDamageBonusAdd(a_Wtype, tempint1);
					}
					//may add different bonuses later
					if (Benefit.find(",") != std::string::npos)
					{
						Benefit = Benefit.substr(Benefit.find(",") + 1);
					}
					else
					{
						Benefit = Benefit.substr(Benefit.find(".") + 1);
					}
					
				}
			}
		}
		catch (std::exception & error)
		{
			std::cout << "Error in LoadFeat: " << error.what() << std::endl;
			return false;
		}	
	}
	m_MasterFeatList[TempFeat->GetName()]= TempFeat;
	//m_MasterFeatList[TempFeat->GetName()]->DisplayFeatFullInfo();
	return true;
}

void EncounterInstance::DisplayMasterFeatListNames()
{
	for (auto i = m_MasterFeatList.begin(); i != m_MasterFeatList.end(); i++)
	{
		std::cout << (*i).first << std::endl;
	}
}

void EncounterInstance::DisplayMasterObjectListNames()
{
	for (auto i = m_MasterObjectList.begin(); i != m_MasterObjectList.end(); i++)
	{
		std::cout << (*i).first << std::endl;
	}
}