#include "EncounterInstance.h"
#include "Armor.h"

EncounterInstance::EncounterInstance()
{
	

}



bool EncounterInstance::init(SDL_Renderer *&gRenderer, SDL_Window *&gWindow)
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

		//Create window
		gWindow = SDL_CreateWindow("WotC Lawsuit bait", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			std::cout << "Window created" << std::endl;
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

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


SDL_Texture* loadTexture(std::string path, SDL_Renderer *& gRenderer)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

//get every texture file, create corresponding texture with loadfromfile and store it in the encounter's map
bool EncounterInstance::LoadAllMedia(SDL_Renderer *&Renderer, SDL_Rect &gTileClips)
{
	bool Success = true;
	//std::cout << "Loading gfont" << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
	gFont = TTF_OpenFont("Baldur.ttf", 20);
	ActionLog.SetFont(gFont);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		Success = false;
	}

	for (auto & Iterator : fs::directory_iterator(GetTextureFolderPath()))
	{
		Textures[Iterator.path().string()] = new LTexture();
	//	if(TempTexture.loadFromFile(Iterator.path().string(), Renderer))
		if (Textures[Iterator.path().string()]->loadFromFile(Iterator.path().string(), Renderer))
		{
			//Textures[Iterator.path().string()]= &TempTexture;
			std::cout << "Loaded " << Iterator.path().string() << std::endl;
			std::cout<< Textures[Iterator.path().string()]->getWidth() << std::endl;
			
		}
		else
		{
			std::cout << "Failed to load " << Iterator.path().string() << std::endl;
			Success = false;
		}

	}
	std::cout << "Test" << Textures[GetTextureFolderPath() + "\\tiles.png"]->getWidth() << std::endl;
	
	
	if (!gTileTexture.loadFromFile(SpriteSet["TileSet"], Renderer))
	{
		printf("Failed to load tile set texture!\n");
		Success = false;
	}
	
	//loadMenuPortTest

	MenuPort = loadTexture("menu background parchment 3 black background vertical.png", Renderer);
	//MenuPort = loadTexture("MenuPortTest.png", Renderer);
	BottomPort = loadTexture("menu background parchment 3 black background horizontal.png", Renderer);

	if (!MenuPort)
	{
		std::cout << "Failed to load MenuPort" << std::endl;
	}

	//loadBottomPortTest
	if (!BottomPort)
	{
		std::cout << "Failed to load BottomPort" << std::endl;
	}

	return Success;
}

bool EncounterInstance::loadMedia(LTexture &gDotTexture, LTexture &gTileTexture, LTexture &mEntityTexture, SDL_Renderer *&Renderer, SDL_Rect &gTileClips)
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if (!gDotTexture.loadFromFile("dot.bmp", Renderer))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}
	else
	{
		Textures["dot.bmp"] = &gDotTexture;
	}

/*	if (!KnifeTexture.loadFromFile("pixelknife.png", Renderer))
	{
		std::cout << "Failed to load knife texture!" << std::endl;
		success = false;
	}
	else
	{
		Textures[GetTextureFolderPath() + "\\pixelknife.png"] = &KnifeTexture;
	}

	if (!mEntityTexture.loadFromFile("clericMace.png", Renderer))
	{
		std::cout << "Failed to load Entity texture" << std::endl;
		success = false;
	}
	else
	{
		Textures[GetTextureFolderPath() +"\\clericMace.png"] = &mEntityTexture;
		std::cout << " Loaded clericMace.png" << std::endl;
	}
	*/
	//Load tile texture
	if (!gTileTexture.loadFromFile(SpriteSet["TileSet"], Renderer))
	{
		printf("Failed to load tile set texture!\n");
		success = false;
	}

	//Load tile map
	if (!setTiles(&gTileClips))
	{
		printf("Failed to load tile set!\n");
		success = false;
	}
	//loadMenuPortTest

	MenuPort = loadTexture("menu background parchment 3 black background vertical.png", Renderer);
	//MenuPort = loadTexture("MenuPortTest.png", Renderer);
	BottomPort = loadTexture("menu background parchment 3 black background horizontal.png", Renderer);

	if (!MenuPort)
	{
		std::cout << "Failed to load MenuPort" << std::endl;
	}

	//loadBottomPortTest
	if(!BottomPort)
	{
		std::cout << "Failed to load BottomPort" << std::endl;
	}

	return success;
}

void EncounterInstance::close(LTexture &gDotTexture, LTexture &gTileTexture, SDL_Renderer*& gRenderer, SDL_Window*& gWindow)
{
	//Deallocate tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		//delete tiles
		}

	//Free loaded images
	//gDotTexture.free();
	gTileTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool EncounterInstance::checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

bool EncounterInstance::setTiles(SDL_Rect gTileClips[])
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::cout << "Loading the map at: " << this->MapFolderPath + "\\" + this->CurrentMapPath << std::endl;
	std::ifstream map(this->MapFolderPath + "\\" + this->CurrentMapPath);

	//If the map couldn't be loaded
	if (!map)
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		AllocateTileMap(TileMapWidth, TileMapHeight);
		//Initialize the tiles
		for (int YPos = 0; YPos < TileMapHeight; YPos++)
		{
			for (int XPos = 0; XPos < TileMapWidth; XPos++)
			{		
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
			{
			//	std::cout << "Tile type loaded" << std::endl;
				TileMap[XPos][YPos] = new Tile(x, y, tileType);
				//tiles[i] = new Tile(x, y, tileType);
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
			x += TILE_WIDTH;

			//If we've gone too far
			if (x >= LEVEL_WIDTH)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
			}
			//std::cout << "Row Complete " << std::endl;
		//Clip the sprite sheet
		}
		DebugTileMap();
	}
		
	if (tilesLoaded)
		{
			ClipTileSheet(gTileClips);		
		}
	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}

void EncounterInstance::DebugTileMap()
{
	for (int y =0; y < TileMap[0].size(); y++)
	{
		for (int i = 0; i < TileMap.size(); i++)
		{
			std::cout << TileMap[i][y].getType() << "  ";
		}
		std::cout << std::endl;
	}
}

void EncounterInstance::ClipTileSheet(SDL_Rect gTileClips[])
{
	gTileClips[TILE_RED].x = 0;
	gTileClips[TILE_RED].y = 0;
	gTileClips[TILE_RED].w = TILE_WIDTH;
	gTileClips[TILE_RED].h = TILE_HEIGHT;

	gTileClips[TILE_GREEN].x = 0;
	gTileClips[TILE_GREEN].y = 80;
	gTileClips[TILE_GREEN].w = TILE_WIDTH;
	gTileClips[TILE_GREEN].h = TILE_HEIGHT;

	gTileClips[TILE_BLUE].x = 0;
	gTileClips[TILE_BLUE].y = 160;
	gTileClips[TILE_BLUE].w = TILE_WIDTH;
	gTileClips[TILE_BLUE].h = TILE_HEIGHT;

	gTileClips[TILE_TOPLEFT].x = 80;
	gTileClips[TILE_TOPLEFT].y = 0;
	gTileClips[TILE_TOPLEFT].w = TILE_WIDTH;
	gTileClips[TILE_TOPLEFT].h = TILE_HEIGHT;

	gTileClips[TILE_LEFT].x = 80;
	gTileClips[TILE_LEFT].y = 80;
	gTileClips[TILE_LEFT].w = TILE_WIDTH;
	gTileClips[TILE_LEFT].h = TILE_HEIGHT;

	gTileClips[TILE_BOTTOMLEFT].x = 80;
	gTileClips[TILE_BOTTOMLEFT].y = 160;
	gTileClips[TILE_BOTTOMLEFT].w = TILE_WIDTH;
	gTileClips[TILE_BOTTOMLEFT].h = TILE_HEIGHT;

	gTileClips[TILE_TOP].x = 160;
	gTileClips[TILE_TOP].y = 0;
	gTileClips[TILE_TOP].w = TILE_WIDTH;
	gTileClips[TILE_TOP].h = TILE_HEIGHT;

	gTileClips[TILE_CENTER].x = 160;
	gTileClips[TILE_CENTER].y = 80;
	gTileClips[TILE_CENTER].w = TILE_WIDTH;
	gTileClips[TILE_CENTER].h = TILE_HEIGHT;

	gTileClips[TILE_BOTTOM].x = 160;
	gTileClips[TILE_BOTTOM].y = 160;
	gTileClips[TILE_BOTTOM].w = TILE_WIDTH;
	gTileClips[TILE_BOTTOM].h = TILE_HEIGHT;

	gTileClips[TILE_TOPRIGHT].x = 240;
	gTileClips[TILE_TOPRIGHT].y = 0;
	gTileClips[TILE_TOPRIGHT].w = TILE_WIDTH;
	gTileClips[TILE_TOPRIGHT].h = TILE_HEIGHT;

	gTileClips[TILE_RIGHT].x = 240;
	gTileClips[TILE_RIGHT].y = 80;
	gTileClips[TILE_RIGHT].w = TILE_WIDTH;
	gTileClips[TILE_RIGHT].h = TILE_HEIGHT;

	gTileClips[TILE_BOTTOMRIGHT].x = 240;
	gTileClips[TILE_BOTTOMRIGHT].y = 160;
	gTileClips[TILE_BOTTOMRIGHT].w = TILE_WIDTH;
	gTileClips[TILE_BOTTOMRIGHT].h = TILE_HEIGHT;
}

bool EncounterInstance::touchesWall(SDL_Rect box)
{
	//std::cout << "Checking box" << std::endl;
	//Go through the tiles
	for (int y = 0; y < TileMap[0].size(); y++)
	{
		for (int x = 0; x < TileMap.size(); x++)
		{
			if ((TileMap[x][y].getType() >= TILE_CENTER) && (TileMap[x][y].getType() <= TILE_TOPLEFT))
			{
				if (checkCollision(box, TileMap[x][y].getBox()))
				{
					return true;
				}
			}
			//TileMap[x][y].render(camera, gTileTexture, gTileClips, gRenderer);
		}
	}

	//If no wall tiles were touched
	return false;
}

void EncounterInstance::AllocateTileMap(int width, int height)
{
	TileMap.resize(width);
	for (int i = 0; i < width; i++)
	{
		//std::cout << "Resizing " << i << std::endl;
		TileMap[i].resize(height);
	}
	std::cout << "Vectors Resized" << std::endl;
}

void EncounterInstance::RenderTiles(SDL_Rect camera, LTexture &gTileTexture, SDL_Rect gTileClips[], SDL_Renderer*& gRenderer)
{
	for (int y = 0; y < TileMap[0].size(); y++)
	{
		for (int x = 0; x < TileMap.size(); x++)
		{
			//std::cout << "Rendering tile " << x << ", " << y << std::endl;
			TileMap[x][y].render(camera, gTileTexture, gTileClips, gRenderer);
		}
	}
}

std::vector< std::vector<Tile>>& EncounterInstance::GetTileMap()
{
	//std::cout << "Returning tilemap" << std::endl;
	return TileMap;
}

std::map<std::string, LTexture*>& EncounterInstance::GetTextures()
{
	return Textures;
}


bool EncounterInstance::RunEncounter()
{
	//set up viewports, lefthandside is menu, bottom is log righthand side is map / gamescreen
	SDL_Rect topLeftViewport;
	topLeftViewport.x = 0;
	topLeftViewport.y = 0;
	topLeftViewport.w = SCREEN_WIDTH / 4;
	topLeftViewport.h = (SCREEN_HEIGHT/4)*3;

	SDL_Rect topRightViewPort;
	topRightViewPort.x = (SCREEN_WIDTH / 4);
	topRightViewPort.y = 0;
	topRightViewPort.w = (SCREEN_WIDTH / 4) * 3;
	topRightViewPort.h = (SCREEN_WIDTH / 4) * 3;

	SDL_Rect BottomViewPort;
	BottomViewPort.x = 0;
	BottomViewPort.y = (SCREEN_HEIGHT / 4) * 3;
	BottomViewPort.h = (SCREEN_HEIGHT / 4);
	BottomViewPort.w = SCREEN_WIDTH;
			
	LTexture gTextTexture;
	SDL_Color textColor = { 0, 0, 0 };
	if (!gTextTexture.loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");
	}

	ActionLog.AddLog(gRenderer, "Hi please work");
	ActionLog.AddLog(gRenderer, "pleas fucking work");
	ActionLog.AddLog(gRenderer, "Lemony snicket is dead");
	ActionLog.AddLog(gRenderer, "I just checked on google");
	ActionLog.AddLog(gRenderer, "Hes definitely dead, tell kira");
	ActionLog.SetLogConstraints(BottomViewPort);

			bool quit = false;
			
			AllEntitySetTexture();
			ActiveUnit = EntityList.front();
			std::cout << "Active unit is named:" << ActiveUnit->GetName() << std::endl;
		//	ActiveUnit->SetTexture(GetTextures(), GetTextureFolderPath());
			std::cout << "Camera created, sdl event created, textures created and assigned, entering running loop" << std::endl;
			while (!quit)
			{
			//	std::cout << "starting event loop" << std::endl;
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//Handle input for the dot
				//	dot.handleEvent(e);
					ActiveUnit->handleEvent(e);
				}

				//Move the dot
				//dot.move(*this);
				//dot.setCamera(camera);

				//move the entity
				//std::cout << "Moving man" << std::endl;
			//	std::cout << "starting control activeunit structure" << std::endl;

				//control structure for controlling units
				switch (ActiveUnit->GetControlMode())
				{
				case(MOVEMODE):
					ActiveUnit->move(GetTileMap());
					break;
				case(ATTACKMODE):
					ActiveUnit->EntityAttack(GetTileMap());
					break;
				case(PICKUPMODE):
					ActiveUnit->EntityPickup(GetTileMap());
					ActiveUnit->SetControlMode(MOVEMODE);
					break;
				}

				ActiveUnit->setCamera(camera);
		//		std::cout << "Man Moved" << std::endl;

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
			//	std::cout << "RenderClear" << std::endl;
				
				//Render level
				SDL_RenderSetViewport(gRenderer, &topRightViewPort);
				
				//std::cout << "Renderviewport set " << std::endl;

				//std::cout << "rendering tiles" << std::endl;

				//render tileset
				RenderTiles(camera, gTileTexture, gTileClips, gRenderer);
				
				//std::cout << "LevelRendered?" << std::endl;

				//Render dot
				//dot.render(camera, gDotTexture, gRenderer);
				RenderAllEntities(camera, gRenderer);
				gTextTexture.renderTile((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture.getHeight()) / 2, gRenderer);

			//	std::cout << "People rendered" << std::endl;

				SDL_RenderSetViewport(gRenderer, &topLeftViewport);
				SDL_RenderCopy(gRenderer, MenuPort, NULL, NULL);
				
				//MenuPort.render(topLeftViewport.x, topLeftViewport.y, gRenderer);
				SDL_RenderSetViewport(gRenderer, &BottomViewPort);
				SDL_RenderCopy(gRenderer, BottomPort, NULL, NULL);
				ActionLog.RenderLog(gRenderer);
				//BottomPort.render(BottomViewPort.x, BottomViewPort.y, gRenderer);

				//SDL_RenderCopy();
				//SDL_RenderCopyEx();

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		
		//Free resources and close SDL
		close(gDotTexture, gTileTexture, gRenderer, gWindow);
	

	return 0;
	return true;
}

void EncounterInstance::AddLog(std::string LogEntry)
{
	std::cout << LogEntry << std::endl;
	AddStringLog(LogEntry);
	AddTextureLog(LogEntry);
	while(StringLog.size() >= LogMaximumSize)
	{
		//deletes from back, we insert from front
		DeleteFromLog();
	}
}
void EncounterInstance::AddStringLog(std::string LogEntry)
{
	//push from front so we will pop from back
	StringLog.push_front(LogEntry);
}

void EncounterInstance::AddTextureLog(std::string LogEntry )
{
	//create texture
	LTexture* LogAdd = new LTexture;
	//render it from text
	LogAdd->loadFromRenderedText(LogEntry, LogTextColor, gRenderer, gFont);
	//add it to the deque
	TextureLog.push_front(LogAdd);
}

void EncounterInstance::DeleteFromLog()
{
	std::cout << "Deleting from log" << std::endl;
	TextureLog.back()->free();
	TextureLog.pop_back();
	StringLog.pop_back();
}
void EncounterInstance::UpIndex()
{
	if (LocationLogIndex<StringLog.size())
	{
		LocationLogIndex++;
	}
}
void EncounterInstance::DownIndex()
{
	if (LocationLogIndex > 0)
	{
		LocationLogIndex--;
	}
}
void EncounterInstance::RenderLog(SDL_Rect Viewport )
{


}

std::string EncounterInstance::GetTextureFolderPath()
{
	return TextureFolderPath;
}

void EncounterInstance::AllEntitySetTexture()
{
	for (auto i = EntityList.begin(); i != EntityList.end(); i++)
	{
		(*i)->SetTexture(GetTextures(), GetTextureFolderPath());
	}
}

void EncounterInstance::RenderAllEntities(SDL_Rect& camera, SDL_Renderer *& Renderer)
{
	for (auto i = EntityList.begin(); i != EntityList.end(); i++)
	{
		(*i)->render(camera, Renderer);
	}
}

bool EncounterInstance::LoadSpriteSet()
{
	//tileset sheet path
	SpriteSet["TileSet"] = "tiles2.png";
	//objects sheet path

	return true;
}

std::string EncounterInstance::GetCharacterFolderPath()
{
	return CharacterFolderPath;
}

std::string EncounterInstance::GetItemFolderPath()
{
	return ItemFolderPath;
}

//loading functions
bool EncounterInstance::ScenarioLoad(std::string Path)
{
	if (!init(gRenderer, gWindow))
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		LoadSpriteSet();
		std::cout << "Init complete" << std::endl;
		if (!LoadAllMedia(gRenderer, *gTileClips))
		{
			std::cout << "Failed to load media!" << std::endl;
		}
		else
		{
			std::cout << "Loaded media successfully!" << std::endl;
		}
	}
	std::cout << "Trying to load " << Path << std::endl;
	std::string line = "";
	std::ifstream Scenario(Path);
	if (!Scenario)
	{
		std::cout << "File empty or error opening" << std::endl;
		return false;
	}

	if (Scenario.is_open())
	{
		//load feats, weapons, then armor
		for (auto i = FeatLists.begin(); i != FeatLists.end(); i++)
		{
			LoadFeatList((*i));
		}
		for (auto i = WeaponLists.begin(); i != WeaponLists.end(); i++)
		{
			LoadWeaponList((*i));
		}
		for (auto i = ArmorLists.begin(); i != ArmorLists.end(); i++)
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
				
			//	std::cout << line << std::endl;
				try {
					line = line.substr(line.find(":")+1);
					line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
					this->CurrentMapPath = line + ".map";
					this->setTiles(gTileClips);
				}
				catch (std::exception const & error)
				{
					std::cout << "Error encountered in scenarioload" << error.what() << std::endl;
				}
			}

			if (line.find("Character:")!=std::string::npos && !EndCharacters)
			{
				//parse name and location
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
			//	std::cout << line << " No spaces, now we find path" << std::endl;

				path = line.substr(0, line.find_first_of(","));
				path = path + ".txt";
				location = line.substr(line.find(",")+1, line.length()-line.find(")")+1);
				std::cout << "path: " << path << std::endl;

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
				EntityList.push_back(new EntityClass);
				std::cout << "Trying to load character with information:" << std::endl;
				std::cout << "Path:" << path << std::endl;
				std::cout << "Character location:" << TempCharacterLocation.first << ", " << TempCharacterLocation.second << std::endl;
				std::cout << "PlayerControlled: ";
				if (PlayerControlled)
					std::cout << "Yes" << std::endl;
				else
					std::cout << "No" << std::endl;
				std::cout << "On side: " << tempSide << std:: endl;
				//load new character from this line, will contain the path of the character, 
				//its position in this scenario and wether or not it is player controlled

				EntityList.back()->LoadEntity(path, TempCharacterLocation, PlayerControlled, tempSide, *this);
				
				//the character will be fully loaded at this point and we can move on
				continue;
			}

			if (line.find("Item:") != std::string::npos && !EndItems)
			{
				int temploc = 0;
				int tempSide = 0;
				std::pair<int, int> TempItemLocation = { 0,0 };
				std::string name = "";
				std::string location = "";
				try {
					temploc = line.find(":") + 1;
					line = line.substr(temploc, line.length());
					line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
					//	std::cout << line << " No spaces, now we find path" << std::endl;

					name = line.substr(0, line.find_first_of(","));
					location = line.substr(line.find(",") + 1, line.length() - line.find(")") + 1);
					std::cout << "name: " << name << std::endl;

					//std::cout << "Location: " << location << std::endl;
					location = location.substr(location.find_first_of("(") + 1, line.length() - location.find_first_of(")") + 1);
					//	std::cout << "location: " << location << std::endl;
					TempItemLocation.first = stoi(location.substr(0, location.find_first_of(",")));
					TempItemLocation.second = stoi(location.substr(location.find_first_of(",") + 1, location.length()));
				}
				catch (std::exception const & error)
				{
					std::cout << "error : " << error.what() << std::endl;
					std::cout << "Error in Item section base file" << std::endl;
				}

				//create new object in master object list
				std::cout << "Trying to load item with information:" << std::endl;
				std::cout << "Item location:" << TempItemLocation.first << ", " << TempItemLocation.second << std::endl;
				LoadObjectIntoTile(TempItemLocation.first, TempItemLocation.second, name);
				

				//the character will be fully loaded at this point and we can move on
				continue;
			}
		}
		Scenario.clear();
		Scenario.seekg(0, Scenario.beg);
	}

	return true;
}

bool EncounterInstance::LoadObjectIntoTile(int x, int y, std::string name)
{
	if (MasterObjectList.count(name))
	{
		std::cout << "Object " << name << " found, loading" << std::endl;
		if (x < TileMap.size()&& y<TileMap.size() &&x>=0 && y>=0)
		{
			std::cout << "Object loading" << std::endl;
			ObjectClass* NewObject = new ObjectClass(*MasterObjectList[name]);
			//NewObject->DisplayObjectWeaponFacts();
			//NewObject->DisplayArmorInfo();
			ObjectList.push_back(new ObjectClass(*MasterObjectList[name]));
			ObjectList.back()->SetLocation(x, y, TileMap);
			ObjectList.back()->SetRendLocation(TileMap);
			ObjectList.back()->SetTexture(Textures, GetTextureFolderPath());
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

bool EncounterInstance::LoadWeaponList(std::string list)
{
	//SimpleWeapons.txt
	//MartialWeapons.txt
	//ExoticWeapons.txt
	std::ifstream reader;
	reader.open(GetItemFolderPath() + "\\" + list);

	if (reader.is_open())
	{
		std::string line = "";
		std::string name = "";
		std::string TempString = "";
		std::cout << "Loading weapon list: " << list<< std::endl;
		try {
			while (getline(reader, line))
			{
				//remove comments
				if (line.find("//") != std::string::npos)
				{
					int endchar = line.find("//");
					line = line.substr(0, endchar);
					//	std::cout << "ResultAfterComment " << line << std::endl;
				}
				if (line.find_first_not_of(' ') == std::string::npos)
				{
					continue;
				}
				//std::cout << "Raw line: " << line << std::endl;	

				name = line.substr(0, line.find_first_of(","));

				line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end()); //remove all spaces
	
				//std::cout << "New object: " << name << std::endl;
				MasterObjectList.insert(std::pair<std::string, ObjectClass*>(name, new ObjectClass));
				line = line.substr(line.find(name + ',') + name.length() + 1);
				//std::cout << "Line no name " << line << std::endl;

				//get two handed
				if (line.find("TwoHanded") != std::string::npos)
				{
					MasterObjectList[name]->SetTwoHanded(true);
				}
				MasterObjectList[name]->SetName(name);
				//get damage --------------------------------
				TempString = line.substr(0, line.find(","));

				int tempint1 = stoi(TempString.substr(0, TempString.find("d")));
			//	std::cout << TempString.substr(0, TempString.find("d") - 1) << std::endl;
				int tempint2 = stoi(TempString.substr(TempString.find("d")+1));
			//	std::cout << numdice << " " << Damage << std::endl;
				MasterObjectList[name]->SetDamageDice(std::pair<int, DiceType>(tempint1, (DiceType)tempint2));

				//get crit multiplier ---------------------------------
				line = line.substr(line.find_first_of(",")+1);
			//	std::cout << line << std::endl;
				TempString = line.substr(0, line.find_first_of(","));
				//std::cout << TempString << std::endl;
				tempint1 = stoi(TempString.substr(0, TempString.find("/x")));
				tempint2 = stoi(TempString.substr(TempString.find("/x") + 2));
				MasterObjectList[name]->SetCritInformation(tempint1, tempint2);
				//std::cout << MasterObjectList[name]->GetCritInformation().first << MasterObjectList[name]->GetCritInformation().second << std::endl;
			
				//get range increment --------------------------------
				line = line.substr(line.find_first_of(",")+1);
				//std::cout << line << std::endl;
				TempString = line.substr(0, line.find_first_of(","));
				TempString = TempString.substr(0, TempString.find_first_of("ft"));
				tempint1 = stoi(TempString);
				MasterObjectList[name]->SetRangeIncrement(tempint1);
			//	std::cout << "range increment: " << TempString << std::endl;

				//get base weight
				line = line.substr(line.find_first_of(",") + 1);
				TempString = line.substr(0, line.find_first_of("lb"));
				float TempWeight = stof(TempString);
			//	tempint1 = stoi(TempString);
				MasterObjectList[name]->SetBaseWeight(TempWeight);
			//	std::cout << "weight: " << TempWeight << std::endl;


				//get damage types ------------
				line = line.substr(line.find_first_of(",")+1);
			//	std::cout << line << std::endl;

				MasterObjectList[name]->GetWeaponType().clear();
				while (FindDamageType(line) != UNKNOWNDAMAGETYPE)
				{
					DamageType TempD = FindDamageType(line);
					MasterObjectList[name]->AddDamageType(TempD);	
					line.erase(line.find(DamageTypeTextMap[TempD]), DamageTypeTextMap[TempD].length());
					//line.erase(line.find(""
					//std::cout << "Adding DamageTypes: " << line << std::endl;
					line = line.substr(line.find(",")+1);					
				}

				while (FindWeaponType(line) != UNKNOWNWEAPONTYPE)
				{
					WeaponType TempW = FindWeaponType(line);
					MasterObjectList[name]->AddWeaponType(TempW);
					line.erase(line.find(WeaponTypeTextMap[TempW]), WeaponTypeTextMap[TempW].length());
				//	std::cout << "adding weapon type:" << line << std::endl;
					
					if (line.find(",") == std::string::npos)
					{
						break;
					}
					//line = line.substr(line.find(",") + 1);
				}
				WeaponType TempW = FindWeaponType(list);
				MasterObjectList[name]->AddWeaponType(TempW);
				//determine if weapon is versitile
				auto it = find(MasterObjectList[name]->GetWeaponType().begin(), MasterObjectList[name]->GetWeaponType().end(), LIGHT);
				if (it != MasterObjectList[name]->GetWeaponType().end())
				{
					MasterObjectList[name]->SetVersatile(false);
				}
				//std::cout << "Weapon Loaded:" << std::endl;
			//	MasterObjectList[name]->DisplayObjectWeaponFacts();
					//line structure is
					//Dagger, 			1d4, 19/x2, 10ft, 1lb, piercing, light, dagger
			}
			return true;
		}
		catch(std::exception const & error)
		{
			std::cout << "Error in loading objects: " << error.what() << std::endl;
			//return false;
		}
	}

}

bool EncounterInstance::LoadArmorList(std::string list)
{
	//3.5 armor list
	std::ifstream reader;
	reader.open(GetItemFolderPath() + "\\" + list);

	if (reader.is_open())
	{
		std::string line = "";
		std::string name = "";
		std::string TempString = "";
		//std::cout << "Loading armor list: " << list << std::endl;
		try {
			while (getline(reader, line))
			{
				line = RemoveComments(line);

				if (line.find_first_not_of(' ') == std::string::npos)
				{
					continue;
				}
				//std::cout << "Raw line: " << line << std::endl;	

				name = line.substr(0, line.find_first_of(","));

				line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end()); //remove all spaces
				line = line.substr(line.find(name) + name.length()+1);
				if (line.find("Shield") == std::string::npos)
				{
					name = name + " Armor";
				}
			//	std::cout << "New object: " << name << std::endl;
				ArmorObject* TempArmor= new ArmorObject;
			//	MasterObjectList.insert(std::pair<std::string, ObjectClass*>(name, new ArmorObject));
				
			//	std::cout << "Line no name " << line << std::endl;

				TempString = line.substr(0, line.find(","));
				int TempInt1 = stoi(TempString);
				TempArmor->SetArmorBonus(TempInt1);
				TempArmor->SetName(name);

				//std::cout <<"Tempstring " << TempString << std::endl;
				//std::cout << "ArmorBonus:" << stoi(TempString) << std::endl;
				//TempString = TempString.substr(1, TempString.find(","));
				//	std::cout << TempString << std::endl;

				//get damage reduction now
				line = line.substr(line.find(",")+1);
			//	std::cout << line << std::endl;
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
				

				//ArmorCheckPenalty
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
				//std::cout << "Weight " << stoi(TempString) << std::endl;
				TempInt1 = stoi(TempString);
				TempArmor->SetBaseWeight((float)TempInt1);

				line = line.substr(line.find(",")+1);
			//	std::cout << "Define tag " << line << std::endl;

				if (line.find("Light") != std::string::npos)
				{
					TempArmor->AddArmorType(LIGHTARMOR);
				}
				if (line.find("Medium") != std::string::npos)
				{
					TempArmor->AddArmorType(MEDIUMARMOR);
				}
				if (line.find("Heavy") != std::string::npos)
				{
					TempArmor->AddArmorType(HEAVYARMOR);
				}
				if (line.find("TowerShield") != std::string::npos)
				{
					TempArmor->AddArmorType(TOWERSHIELD);
				}
				else if (line.find("Shield")!=std::string::npos)
				{
					TempArmor->AddArmorType(SHIELD);
				}

			//	std::cout << "Armor loaded" << std::endl;
				MasterObjectList[name] = TempArmor;

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
	return MasterObjectList;
}

bool EncounterInstance::LoadFeatList(std::string list)
{
	std::ifstream reader;
	reader.open(FeatFolderPath + "\\" + list);

	std::cout << "Loading featlist start:" <<list<< std::endl;

	if (reader.is_open())
	{
		std::string line = "";
		std::string name = "";
		std::string TempString = "";
		std::cout << "Loading feat list: " << list << std::endl;
		//get if it is a single feat or group of feats
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
bool EncounterInstance::LoadFeat(std::ifstream &reader, int StartFeat)
{
	
	std::string line = "";
	std::string name = "";
	std::string description = "";
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
	while (getline(reader, line)&&Each ==false)
	{
		try {
			line = RemoveComments(line);
			if (line.find("EACH") != std::string::npos)
			{
				Each = true;
				if (line.find("WEAPONTYPE")!=std::string::npos)
				{
					//limit it to certain groups soon
					for (auto i = WeaponTypeTextMap.begin()++; i != WeaponTypeTextMap.end(), (*i).first!=SIMPLE; i++) 
					{
						if (!AddEachWeaponFeat(reader, StartFeat, (*i).first))
						{
							success = false;
						}
					}
				} 
				else if(line.find("ARMORTYPE") != std::string::npos)
				{
					for (auto i = ArmorTypeTextMap.begin(); i != ArmorTypeTextMap.end(); i++)
					{
						//AddEachArmorFeat();
					}	
				}
				break;
			} //end if find EACH
			//std::cout << "Line loading feat:" << line << std::endl;
			if (line.find("</Feat>") != std::string::npos)
			{
				break;
			}

			if (line.find("FeatName:") != std::string::npos)
			{
				line = line.substr(line.find("FeatName:"));
				name = line.substr(line.find(":") + 1);
				std::cout << "New Feat Name " << name << std::endl;
				TempFeat->SetName(name);
			}
			//start reading data
			if (line.find("FeatDescription:") != std::string::npos)
			{
				description = line;
				description = description.substr(line.find("\"") + 1, line.find_last_of("\"") - 1);
				std::cout << "FeatDescription:" << description << std::endl;
				TempFeat->SetDescription(description);
			}

			if (line.find("Prerequisites:") != std::string::npos)
			{
				PreReq = line.substr(line.find(":") + 1);
				std::cout << "PreReqs:" << PreReq << std::endl;
				//todo when creating levelup system
			}

			if (line.find("Benefit:") != std::string::npos)
			{
				Benefit = line.substr(line.find(":")+1);
				std::cout << "Benefit:" << Benefit << std::endl;
				if (Benefit.find("RANGE(") != std::string::npos)
				{
					//UsesRange = true;
					Bonuses = Benefit.substr(Benefit.find("RANGE("));
					Bonuses = Bonuses.substr(Bonuses.find("RANGE(") + 6, Bonuses.find(")") - 6);
					std::cout << "Bonuses range: " << Bonuses << std::endl;
					std::string TempRange = Bonuses;
					std::cout << TempRange.substr(0, TempRange.find("x")) << std::endl;
					range.first=std::stoi(TempRange.substr(0, TempRange.find("x")));
					range.second = std::stoi(TempRange.substr(TempRange.find("x")+1));
					std::cout << range.first << "x" << range.second << std::endl;
					TempFeat->SetRangeActivated(range.first, range.second);
					TempFeat->SetUsesRangeAbility(true);
				}
				Benefit = Benefit.substr(Benefit.find(",")+1);
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
					
					std::cout << "TempS: " << TempString << std::endl;
					if (TempString.find("AttackRoll") != std::string::npos)
					{
						std::string Affects = TempString.substr(TempString.find("AttackRoll") + 10);
						std::cout << "AttackRoll affects: " << Affects << std::endl;

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
							//range not found, so it is a fixed amount
							std::cout << "Amount increase " << TempString.substr(0, TempString.find("AttackRoll")) << std::endl;
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
							//range not found, so it is a fixed amount
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
						else //range not found, so it is a fixed amount
						{
						//std::cout << "Amount increase " << TempString.substr(0, TempString.find("Dodge")) << std::endl;
						int tempint1 = stoi(TempString.substr(0, TempString.find("Dodge")));
						CircumstanceType CType = FindCircumstanceType(Benefit);
						if (CType != UNKNOWNCIRCUMSTANCE)
						{
							TempFeat->AddCircumstanceAttackDamageAdd(CType, tempint1);
						}
					}
				} //end if Dodge found

					if (TempString.find("Proficiency") != std::string::npos)
					{
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

					if (Benefit.find(",") == std::string::npos)
					{
						Benefit = Benefit.substr(Benefit.find(".") + 1);
					}
					else
					{
						Benefit = Benefit.substr(Benefit.find(",")+1);
					}
					
				}	

			} //end if find(benefit):
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
		MasterFeatList[TempFeat->GetName()] = TempFeat;
		MasterFeatList[TempFeat->GetName()]->DisplayFeatFullInfo();
	}//end of while loop
	
	return true;
	}
	

//helper
std::string EncounterInstance::RemoveComments(std::string line)
{
	if (line.find("//") != std::string::npos)
	{
		int endchar = line.find("//");
		line = line.substr(0, endchar);
		//	std::cout << "ResultAfterComment " << line << std::endl;
	}
	return line;
}

bool EncounterInstance::AddEachWeaponFeat(std::ifstream & reader, int StartPos, WeaponType Wtype) 
{
	//start at beginning of feat
	reader.seekg(StartPos, std::ios::beg);

	std::string line;
	std::string TempString;
	std::string name;
	std::pair<WeaponType, int> TempBonus;
	int tempint1;
//	int tempint2;
	
	FeatClass* TempFeat = new FeatClass;

	while (getline(reader, line))
	{
		//start reading data, try block to stop stoi from crashing program from bad reads
		try {
			line = RemoveComments(line);

			//std::cout << "Line loading feat:" << line << std::endl;
			if (line.find("</Feat>") != std::string::npos)
			{
				break;
			}

			if (line.find("FeatName:") != std::string::npos)
			{
				line = line.substr(line.find("FeatName:"));
				name = line.substr(line.find(":") + 1);
				std::string temp = "WEAPONTYPE EACH";
				
				name.replace(name.find("WEAPONTYPE"), temp.length(), WeaponTypeTextMap[Wtype]);
				TempFeat->SetName(name);
			//	std::cout << "New Feat Name " << name << std::endl;
			}
			
			if (line.find("FeatDescription:") != std::string::npos)
			{
				std::string description = line;
				description = description.substr(line.find("\"") + 1, line.find_last_of("\"") - 1);
			//	std::cout << "FeatDescription:" << description << std::endl;
				TempFeat->SetDescription(description);
			}

			if (line.find("Prerequisites:") != std::string::npos)
			{
				std::string PreReq = line.substr(line.find(":") + 1);
			//	std::cout << "PreReqs:" << PreReq << std::endl;
				//TBD later, when a leveling machine can be implemented, otherwise irrelevant as we wont check for illegal characters at loadtime
			}

			if (line.find("Benefit:") != std::string::npos)
			{
				std::string Benefit = "";
				std::string Bonuses = "";
				std::pair<int, int> range;
			//	ReplaceWeaponType(line, Wtype);

				Benefit = line.substr(line.find(":") + 1);
			//	std::cout << "Benefit:" << Benefit << std::endl;

				if (Benefit.find("RANGE(") != std::string::npos)
				{
					TempFeat->SetUsesRangeAbility(true);
					Bonuses = Benefit.substr(Benefit.find("RANGE("));
					Bonuses = Bonuses.substr(Bonuses.find("RANGE(") + 6, Bonuses.find(")") - 6);
					//	std::cout << "Bonuses range: " << Bonuses << std::endl;
					std::string TempRange = Bonuses;
					//std::cout << TempRange.substr(0, TempRange.find("x")) << std::endl;
					range.first = std::stoi(TempRange.substr(0, TempRange.find("x")));
					range.second = std::stoi(TempRange.substr(TempRange.find("x") + 1));
					//std::cout << range.first << "x" << range.second << std::endl;
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
							TempFeat->AddWeaponAttackBonusAdd(Wtype, tempint1);
					}
					if (TempString.find("DamageRoll") != std::string::npos)
					{
							tempint1 = stoi(TempString.substr(0, TempString.find("DamageRoll")));
							TempFeat->AddWeaponDamageBonusAdd(Wtype, tempint1);
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
	MasterFeatList[TempFeat->GetName()]= TempFeat;
	MasterFeatList[TempFeat->GetName()]->DisplayFeatFullInfo();
	return true;
}

void EncounterInstance::DisplayMasterFeatListNames()
{
	for (auto i = MasterFeatList.begin(); i != MasterFeatList.end(); i++)
	{
		std::cout << (*i).first << std::endl;
	}
}

void EncounterInstance::DisplayMasterObjectListNames()
{
	for (auto i = MasterObjectList.begin(); i != MasterObjectList.end(); i++)
	{
		std::cout << (*i).first << std::endl;
	}
}