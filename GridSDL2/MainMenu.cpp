#include "MainMenu.h"

MainMenu::MainMenu()
{
	kiss_array_new(&m_objects);
	m_renderer = kiss_init("Main Menu", &m_objects, 1000, 600);
	if (!m_renderer)
		return;

	kiss_window_new(&m_window, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
	strcpy(m_message, "Table Top Battle Map Main Menu");
	kiss_label_new(&m_label, &m_window, m_message, (m_window.rect.w / 2 - strlen(m_message) * kiss_textfont.advance / 2), (m_window.rect.h / 2 - (kiss_textfont.fontheight + 2 * kiss_normal.h) / 2));
	m_label.textcolor.r = 255;
	
	kiss_button_new(&m_QuitButton, &m_window, "Quit", (m_window.rect.w / 2 - (kiss_normal.w) / 2), (m_label.rect.y + kiss_textfont.fontheight + 2 * kiss_normal.h)+10);
	strcpy(m_message ,"Scenario Select");

	m_ScenarioButton.normalimg = kiss_normal_long;
	m_ScenarioButton.activeimg = kiss_active_long;
	m_ScenarioButton.prelightimg = kiss_prelight_long;
	kiss_button_new(&m_ScenarioButton, &m_window, m_message, (m_window.rect.w / 2 - kiss_normal_long.w / 2), (m_label.rect.y + kiss_textfont.fontheight + kiss_normal_long.h));
	
	m_ScenarioButton.rect.w = (strlen(m_message) * kiss_textfont.advance)+30;

	m_window.visible = 1;
}

int MainMenu::MainMenuRun()
{
	int m_draw = 1;
	std::cout << (int)m_retval << std::endl;
	while (m_retval == CONTINUE) {
		SDL_Delay(10);
		//std::cout << " main loop " << (int)m_retval << std::endl;
		while (SDL_PollEvent(&m_event))
		{
			if (m_event.type == SDL_QUIT)
			{
				m_retval = QUIT;
			}

			kiss_window_event(&m_window, &m_event, &m_draw);
			scenario_button_event(&m_ScenarioButton, &m_event, &m_draw);
			quit_button_event(&m_QuitButton, &m_event, &m_draw);
		}
		if (!m_draw) 
		{
		continue;
		}
		MainMenUUpdate(m_renderer);
		m_draw = 0;
		//std::cout << "Entering this shit yo" << std::endl;
	}
	kiss_clean(&m_objects);
	return (int)m_retval;

}

void MainMenu::MainMenUUpdate(SDL_Renderer *& a_renderer)
{
		SDL_RenderClear(a_renderer);
		kiss_window_draw(&m_window, a_renderer);
		kiss_label_draw(&m_label, a_renderer);
		kiss_button_draw(&m_ScenarioButton, a_renderer);
		kiss_button_draw(&m_QuitButton, a_renderer);
		SDL_RenderPresent(a_renderer); 
}

void MainMenu::quit_button_event(kiss_button *a_button, SDL_Event *a_event, int *a_draw)
{
	if (kiss_button_event(a_button, a_event, a_draw)) 
	{
	m_retval = QUIT;
	}
		
}

void MainMenu::scenario_button_event(kiss_button *a_button, SDL_Event *a_event, int *a_draw)
{
	if (kiss_button_event(a_button, a_event, a_draw)) {
		m_retval = SCENARIOMENU;
	std::cout << "Scenario Select a_button" << std::endl;
	}
}