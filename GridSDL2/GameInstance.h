/**********************************************************************************************//**
 * @file	GameInstance.h.
 *
 * @brief	Declares the game instance class
 **************************************************************************************************/

#pragma once
#include "GeneralHeaders.h"
#include "Tile.h"
#include "Texture.h"
#include "StaticFunctions.h"

/**********************************************************************************************//**
 * @class	GameInstance
 *
 * @brief	A game instance class, contains encounter instance and everything else needed to run the game
 *
 * @author	Brendan B
 * @date	9/4/2018
 **************************************************************************************************/

class GameInstance
{
public:

	/**********************************************************************************************//**
	 * @fn	void GameInstance::StartGame();
	 *
	 * @brief	Starts the main menu which calls the encounterrun etc, when it returns it means the user quits
	 * 			so calls Quit function to end the game
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @return	void
	 **************************************************************************************************/

	void StartGame();

	
	/**********************************************************************************************//**
	 * @fn	int GameInstance::MenuOperation();
	 *
	 * @brief	Menu operation calls submenu scenario load
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @return	An int responding to what the user requests
	 **************************************************************************************************/

	int MenuOperation();

	/**********************************************************************************************//**
	 * @fn	void GameInstance::EncounterRun(std::string path);
	 *
	 * @brief	Encounter run runs the encounter, handles the code that needs to be excecuted around it for it to function properly
	 * 			runs based on what scenario the user selected
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param	path	Full pathname of the chosen scenario
	 * 					
	 * @return int based on encounter result
	 **************************************************************************************************/

	int EncounterRun(std::string path);

	/**********************************************************************************************//**
	 * @fn	void GameInstance::SetSelectedScenario(std::string path);
	 *
	 * @brief	Sets selected scenario
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param	path	Full pathname of the selected scenario
	 **************************************************************************************************/

	void SetSelectedScenario(std::string path);

	/**********************************************************************************************//**
	 * @fn	void GameInstance::Quit();
	 *
	 * @brief	Quits this object and calls exit()
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 **************************************************************************************************/

	void Quit();

	/**********************************************************************************************//**
	 * @fn	std::string GameInstance::GetScenarioPath();
	 *
	 * @brief	Gets scenario path stored
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @return	The scenario path.
	 **************************************************************************************************/

	std::string GetScenarioPath();

	/**********************************************************************************************//**
	 * @fn	void GameInstance::SetScenarioPath(std::string path);
	 *
	 * @brief	Sets scenario path
	 *
	 * @author	Brendan B
	 * @date	9/4/2018
	 *
	 * @param	path	Full pathname of the file.
	 **************************************************************************************************/

	void SetScenarioPath(std::string path);
private:
	/** @brief	The scenario paths */
	std::string m_ScenarioPaths="Data\\Scenarios";
	/** @brief	The selected scenario */
	std::string m_selectedScenario = "";

};