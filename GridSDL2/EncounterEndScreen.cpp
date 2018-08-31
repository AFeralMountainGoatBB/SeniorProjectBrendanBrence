#include "EncounterEndScreen.h"


EncounterEndScreen::EncounterEndScreen()
{
	m_quit = 0;
	m_draw = 1;

	m_renderer = kiss_init("EncounterEndScreen", &m_objects, 300, 150);
	if (!m_renderer)
	{
		std::cout << "Renderer wrong" << std::endl;
		return;
	}
	kiss_array_new(&m_objects);

	/* Arrange the widgets nicely relative to each other */
	kiss_window_new(&m_window, NULL, 1, 0, 0, kiss_screen_width, kiss_screen_height);
	kiss_label_new(&m_labelPWin, &m_window, "Game Over, Player has won", kiss_screen_width*.25 - (.5*kiss_normal.w), kiss_screen_height*.2);
	kiss_label_new(&m_labelCWin, &m_window, "Game Over, AI has won", m_labelPWin.rect.x, kiss_screen_height*.2);

	m_labelPWin.visible = 0;
	m_labelCWin.visible = 0;

	kiss_button_new(&m_QuitButton, &m_window, "Exit", kiss_screen_width*.5 - (.5*kiss_normal.w), kiss_screen_height*.7);
	m_window.visible = 1;

	/*kiss_textbox_new(&m_textbox1, &m_MainWindow, 1, &m_array1, kiss_screen_width / 2 - (2 * m_textbox_width + 2 * kiss_up.w - kiss_edge) / 2,
	3 * kiss_normal.h, m_textbox_width, m_textbox_height);
	*/
	/*//	kiss_vscrollbar_new(&m_vscrollbar1, &m_MainWindow, m_textbox1.rect.x + m_textbox_width, m_textbox1.rect.y, m_textbox_height);
	kiss_label_new(&m_label, &m_window, "Game Over", m_label.rect.x + kiss_edge, m_label.rect.y - kiss_textfont.lineheight);
	kiss_button_new(&m_QuitButton, &m_window, "Exit", m_QuitButton.rect.x - 2 * kiss_normal.w, m_QuitButton.rect.y);*/
//	m_window.visible = 1;
}

void EncounterEndScreen::Show(bool a_playerWin, bool a_ComputerWin)
{

	if (a_playerWin == true)
	{
		m_Pwin = true;
	}
	else if (a_ComputerWin == true)
	{
		m_Cwin = true;
	}
	
}


void EncounterEndScreen::quit_button_event(kiss_button *a_button, SDL_Event *a_event)
{
	if (kiss_button_event(a_button, a_event, &m_draw))
	{
		m_quit = 1;
	}
}


void EncounterEndScreen::EndScreenUpdate(SDL_Renderer *& a_renderer)
{

}

void EncounterEndScreen::EndScreenRun()
{
	while (!m_quit) {

		/* Some code may be written here */

		SDL_Delay(10);
		while (SDL_PollEvent(&m_event)) {
			if (m_event.type == SDL_QUIT)
				m_quit = 1;

			kiss_window_event(&m_window, &m_event, &m_draw);
			quit_button_event(&m_QuitButton, &m_event);
		}

		if (!m_draw) continue;
		SDL_RenderClear(m_renderer);
		
		kiss_window_draw(&m_window, m_renderer);
		if (m_Pwin == true)
		{
			kiss_label_draw(&m_labelPWin, m_renderer);
		}
		if (m_Cwin == true)
		{
		kiss_label_draw(&m_labelCWin, m_renderer);
		}

		kiss_button_draw(&m_QuitButton, m_renderer);

		SDL_RenderPresent(m_renderer);
		m_draw = 0;
	}
	kiss_clean(&m_objects);
	return;
}