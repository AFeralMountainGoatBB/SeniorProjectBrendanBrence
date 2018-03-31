#pragma once
#include "GeneralHeaders.h"
#include "Tile.h"
#include "Dot.h"
#include "Texture.h"
#include "StaticFunctions.h"



class GameInstance
{
public:

	std::string ScenarioPath = "";
	GameInstance();
	
	~GameInstance();
	
	//StartGame handles every other function
	int StartGame();
	int GuiTesting();
	int StartGame2();

	//Initializes SDL
	void InitializeSDL();

	//Handles the main menu and calls ScenarioMenu
	int MenuOperation();

	bool ScenarioLoad();

	int EncounterRun();

	void Quit();

	/*Heirarchy of these calls
	MenuOperation (calls mainmenu functions and scenariomenufunctions) 
	-> EncounterRun (on return from scenariomenu) 
	->Scenario load(intermediate) 
	-> EncounterRun, runs encounterclass functions and returns to MenuOperation
	*/

private:


};