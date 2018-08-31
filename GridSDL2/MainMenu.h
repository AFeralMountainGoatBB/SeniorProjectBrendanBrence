#pragma once
#include "GeneralHeaders.h"

class MainMenu
{
public:
	
	MainMenu();

	void quit_button_event(kiss_button *button, SDL_Event *m_event, int *m_draw);
	void scenario_button_event(kiss_button *button, SDL_Event *m_event, int *m_draw);

	void MainMenUUpdate(SDL_Renderer *& m_renderer);
	int MainMenuRun();

private:
	//variables
	SDL_Renderer * m_renderer;
	SDL_Event m_event;
	kiss_array m_objects;
	kiss_window m_window;
	kiss_label m_label = { 0 };
	kiss_button m_ScenarioButton = { 0 };
	kiss_button m_QuitButton = { 0 };
	char m_message[KISS_MAX_LENGTH];

	enum option { CONTINUE = 0, QUIT = -1, SCENARIOMENU = 1 };
	option m_retval = CONTINUE;

};