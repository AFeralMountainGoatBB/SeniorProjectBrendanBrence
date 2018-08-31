#include "GameInstance.h"
#include "MainMenu.h"
#include "ScenarioMenu.h"
#include "EncounterInstance.h"
//#include "GeneralHeaders.h"

GameInstance::GameInstance()
{

}

GameInstance::~GameInstance() 
{

}


int GameInstance::GuiTesting()
{
	SDL_Renderer *m_renderer;
	SDL_Event m_event;
	kiss_array m_objects;
	kiss_window m_window;
	//extern kiss_textfont;
	kiss_label m_label = { 0 };
	kiss_button button = { 0 }; 
	char m_message[KISS_MAX_LENGTH];
	int m_draw, m_quit;

	m_quit = 0; 
	m_draw = 1;
	kiss_array_new(&m_objects);
	m_renderer = kiss_init("Hello kiss_sdl", &m_objects, 320, 120); 
	if (!m_renderer)
		return 1;
	kiss_window_new(&m_window, NULL, 0, 0, 0,  kiss_screen_width, kiss_screen_height); 
	strcpy(m_message, "Hello World!");
	kiss_label_new(&m_label, &m_window, m_message, m_window.rect.w / 2 - strlen(m_message) * kiss_textfont.advance / 2, m_window.rect.h / 2 -(kiss_textfont.fontheight + 2 * kiss_normal.h) / 2);
	m_label.textcolor.r = 255;
	kiss_button_new(&button, &m_window, "OK", (m_window.rect.w / 2 - kiss_normal.w / 2), (m_label.rect.y + kiss_textfont.fontheight + kiss_normal.h));
	m_window.visible = 1; while (!m_quit) { SDL_Delay(10);
	while (SDL_PollEvent(&m_event)) 
	{ 
		if (m_event.type == SDL_QUIT) 
			m_quit = 1; 
		kiss_window_event(&m_window, &m_event, &m_draw);
		//Main.quit_button_event(&button, &m_event, &m_draw, &m_quit); 
	} 
	if (!m_draw)
		continue;
	SDL_RenderClear(m_renderer);
	kiss_window_draw(&m_window, m_renderer);
	kiss_label_draw(&m_label, m_renderer);
	kiss_button_draw(&button, m_renderer);
	SDL_RenderPresent(m_renderer); 
	m_draw = 0;
	}
	kiss_clean(&m_objects);
	return 0;
};

//StartGame handles every other function
int GameInstance::StartGame()
{
	
	return 0;
}

//Initializes SDL
void GameInstance::InitializeSDL()
{

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

	//one pass loading implementation started to be written

	return 0;
}

void GameInstance::Quit()
{

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