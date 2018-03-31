#pragma once
#include "GeneralHeaders.h"

class MainMenu
{
public:
	//variables
	SDL_Renderer* renderer;
	SDL_Event e;
	kiss_array objects;
	kiss_window window;
	kiss_label label = { 0 };
	kiss_button ScenarioButton = { 0 };
	kiss_button QuitButton = { 0 };
	char message[KISS_MAX_LENGTH];

	enum option { CONTINUE = 0, QUIT = -1, SCENARIOMENU = 1 };
	option retval = CONTINUE;

	MainMenu();

	void quit_button_event(kiss_button *button, SDL_Event *e, int *draw);
	void scenario_button_event(kiss_button *button, SDL_Event *e, int *draw);

	void MainMenUUpdate(SDL_Renderer *& renderer);
	int MainMenuRun();

};