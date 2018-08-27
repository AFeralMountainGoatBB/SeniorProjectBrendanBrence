#pragma once
#include "GeneralHeaders.h"

//this class is for the objects that will be always present during the encounter, namely on the left side of the screen and the bottom
//will have labels for relevant information and a log on bottom
class EncounterEndScreen
{
public:
	SDL_Renderer *renderer;
	SDL_Event e;
	kiss_array objects;
	kiss_window window;
	kiss_label labelPWin = { 0 }, labelCWin = { 0 };
	
	kiss_button QuitButton = { 0 };
	char message[KISS_MAX_LENGTH];

	int quit = 0;
	int draw;

	bool Pwin = false;
	bool Cwin = false;

	EncounterEndScreen();
	void Show(bool playerWin, bool ComputerWin);

	void quit_button_event(kiss_button *button, SDL_Event *e);
	
	void EndScreenSetWinner(bool playerWin, bool AIWin);
	void EndScreenUpdate(SDL_Renderer *& renderer);
	void EndScreenRun();

};