#pragma once
#include "GeneralHeaders.h"

//this class is for the m_objects that will be always present during the encounter, namely on the left side of the screen and the bottom
//will have labels for relevant information and a log on bottom
class EncounterEndScreen
{
public:


	EncounterEndScreen();
	void Show(bool playerWin, bool ComputerWin);

	void quit_button_event(kiss_button *button, SDL_Event *m_event);
	
	void EndScreenSetWinner(bool playerWin, bool AIWin);
	void EndScreenUpdate(SDL_Renderer *& m_renderer);
	void EndScreenRun();

private:
	SDL_Renderer * m_renderer;
	SDL_Event m_event;
	kiss_array m_objects;
	kiss_window m_window;
	kiss_label m_labelPWin = { 0 }, m_labelCWin = { 0 };

	kiss_button m_QuitButton = { 0 };
	char m_message[KISS_MAX_LENGTH];

	int m_quit = 0;
	int m_draw;

	bool m_Pwin = false;
	bool m_Cwin = false;
};