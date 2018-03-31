#include "EncounterInstance.h"

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
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	
	if (!setTiles(&gTileClips))
	{
		std::cout << "Failed to load tile set!" << std::endl;
		Success = false;
	}
		
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

	if (!KnifeTexture.loadFromFile("pixelknife.png", Renderer))
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
	gDotTexture.free();
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
	std::ifstream map("lazy.map");

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
	/*
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		//If the tile is a wall type tile
		if ((tiles[i]->getType() >= TILE_CENTER) && (tiles[i]->getType() <= TILE_TOPLEFT))
		{
			//If the collision box touches the wall tile
			if (checkCollision(box, tiles[i]->getBox()))
			{
				return true;
			}
		}
	}
	*/

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
	std::cout << "EncounterRunning" << std::endl;
	Dummy.SetName("TargetDummy");
	
	Dagger->SetName("Dagger");
	std::cout << "SetName dagger" << std::endl;
	//man.SetPath("pixelknife.png");
	
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
	//SDL_RenderSetViewport(gRenderer, &topLeftViewport);
	
	LoadSpriteSet();
	//Start up SDL and create window
	if (!init(gRenderer, gWindow))
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		std::cout << "Init complete" << std::endl;

		//Load media
	//	if (!loadMedia(gDotTexture, gTileTexture, mEntityTexture, gRenderer, *gTileClips))
		if (!LoadAllMedia(gRenderer, *gTileClips))
		{
			std::cout << "Failed to load media!" << std::endl;
		}
		else
		{
			std::cout << "Loaded media" << std::endl;
			//Main loop flag
			
			bool quit = false;
		
			Dummy.SetTexture(GetTextures(), GetTextureFolderPath());
			man.SetTexture(GetTextures(), GetTextureFolderPath());
			Dagger->SetTexture(GetTextures(), GetTextureFolderPath());

			Dagger->SetLocation(0, 3, TileMap);	
			std::cout << "Dagger location set" << std::endl;
			Dagger->SetRendLocation(TileMap);
		
			Dummy.SetLocation(0, 5, TileMap);
			Dummy.SetRendLocation(TileMap);
			std::cout << "Dummy location set" << std::endl;

			//While application is running
			std::cout << "Camera created, sdl event created, textures created and assigned, entering running loop" << std::endl;
			while (!quit)
			{
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
					man.handleEvent(e);
				}

				//Move the dot
				//dot.move(*this);
				//dot.setCamera(camera);

				//move the entity
				//std::cout << "Moving man" << std::endl;

				//control structure for controlling units
				switch (man.GetControlMode())
				{
				case(MOVEMODE):
					man.move(GetTileMap());
					break;
				case(ATTACKMODE):
					man.EntityAttack(GetTileMap());
					break;
				case(PICKUPMODE):
					man.EntityPickup(GetTileMap());
					man.SetControlMode(MOVEMODE);
					break;
				}

				man.setCamera(camera);
		//		std::cout << "Man Moved" << std::endl;

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
			//	std::cout << "RenderClear" << std::endl;

				//Render level
				SDL_RenderSetViewport(gRenderer, &topRightViewPort);

			//	std::cout << "Renderviewport set " << std::endl;

				//render tileset
				RenderTiles(camera, gTileTexture, gTileClips, gRenderer);
				
				//std::cout << "LevelRendered?" << std::endl;

				//Render dot
				//dot.render(camera, gDotTexture, gRenderer);
				man.render(camera,  gRenderer);
				Dummy.render(camera,  gRenderer);

				//std::cout << "People rendered" << std::endl;

				SDL_RenderSetViewport(gRenderer, &topLeftViewport);
				SDL_RenderCopy(gRenderer, MenuPort, NULL, NULL);
				//MenuPort.render(topLeftViewport.x, topLeftViewport.y, gRenderer);
				SDL_RenderSetViewport(gRenderer, &BottomViewPort);
				SDL_RenderCopy(gRenderer, BottomPort, NULL, NULL);
				//BottomPort.render(BottomViewPort.x, BottomViewPort.y, gRenderer);

				//SDL_RenderCopy();
				//SDL_RenderCopyEx();

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
		//Free resources and close SDL
		close(gDotTexture, gTileTexture, gRenderer, gWindow);
	}

	return 0;
	return true;
}

std::string EncounterInstance::GetTextureFolderPath()
{
	return TextureFolderPath;
}

bool EncounterInstance::LoadSpriteSet()
{
	//tileset sheet path
	SpriteSet["TileSet"] = "tiles2.png";
	//objects sheet path

	//Character Representation spritesheet path

	//

	return true;
}



//loading functions
bool EncounterInstance::ScenarioLoad(std::string Path)
{
	std::string line = "";
	std::ifstream Scenario(Path);
	if (!Scenario)
	{
		std::cout << "File empty or error opening" << std::endl;
		return false;
	}

	if (Scenario.is_open())
	{
		while (getline(Scenario, line))
		{
			std::cout << line << std::endl;
			if (line.find("//")!=std::string::npos)
			{
				int endchar = line.find("//");
				line = line.substr(0, endchar);
				std::cout << "ResultAfterComment " << line << std::endl;
			}

			if (line.find("Character:")!=std::string::npos)
			{
				//parse name and location
				int temploc=0;
				int temploc2=0;
				std::string path="";
				std::string location = "";
				bool PlayerControlled = false;
				if (line.find("Player") != std::string::npos)
				{
					PlayerControlled = true;
				}

				temploc = line.find(":");
				line = line.substr(temploc, line.length());
				line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
				std::cout << line << std::endl;
				path = line.substr(0, line.find(","));

				//create new character pointer in entitylist, call to load character
				EntityList.push_back(new EntityClass);
				//load new character from this line, will contain the path of the character, 
				//its position in this scenario and wether or not it is player controlled
				

			}
		}
		Scenario.clear();
		Scenario.seekg(0, Scenario.beg);
	}


	return true;
}