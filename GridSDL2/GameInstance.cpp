#include "GameInstance.h"
#include "MainMenu.h"
#include "ScenarioMenu.h"
#include "EncounterInstance.h"
//#include "GeneralHeaders.h"


void GameInstance::StartGame()
{
	MenuOperation();
	Quit();
}

//Handles the main menu, scenariomenu, and encounterRun
int GameInstance::MenuOperation()
{
	enum MenuOptions {MAINMENU=0, SCENARIOMENU=1, QUIT=-1, ENCOUNTER= 2};
	MenuOptions Selected = MAINMENU;
	
	while (Selected != QUIT)
	{
		switch (Selected) {
		case MAINMENU:
		{
			MainMenu Main;
			Selected = (MenuOptions)Main.MainMenuRun();
			break;
		}
		case SCENARIOMENU: 
		{
			ScenarioMenu SMenu;
			Selected=(MenuOptions)SMenu.ScenarioMenuRun(*this);
			
			break;
		}
		case ENCOUNTER:
		{
			if (m_selectedScenario != "") 
			{
				Selected=(MenuOptions)EncounterRun(m_selectedScenario);//loads and runs encounter selected by ScenarioMenuRun
				m_selectedScenario = "";
			}
				
			else
				Selected = MAINMENU;
			break;
		}
		case QUIT:
		{
			return 0;
		}
		default:
		{
			std::cout << "Default case reached in menu operation, something went wrong" << std::endl;
			return 0;
		}

		} //end switch
		
	}

	return 0;
}

int GameInstance::EncounterRun(std::string a_path)
{
	//create space for entities in memory
	EncounterInstance Instance;
	Instance.ScenarioLoad(a_path);
	Instance.RunEncounter();
	return 0;
}

void GameInstance::Quit()
{
	exit(EXIT_SUCCESS);
}

std::string GameInstance::GetScenarioPath()
{
	return m_ScenarioPaths;
}

void GameInstance::SetScenarioPath(std::string a_path)
{
	m_ScenarioPaths = a_path;
}
void GameInstance::SetSelectedScenario(std::string a_path)
{
	m_selectedScenario = a_path;
}