#include "MainMenu.h"

MainMenu::MainMenu()
{
	kiss_array_new(&objects);
	renderer = kiss_init("Main Menu", &objects, 1000, 600);
	if (!renderer)
		return;

	kiss_window_new(&window, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);
	strcpy(message, "WotC Lawsuit bait Main Menu");
	kiss_label_new(&label, &window, message, (window.rect.w / 2 - strlen(message) * kiss_textfont.advance / 2), (window.rect.h / 2 - (kiss_textfont.fontheight + 2 * kiss_normal.h) / 2));
	label.textcolor.r = 255;
	
	kiss_button_new(&QuitButton, &window, "Quit", (window.rect.w / 2 - kiss_normal.w / 2), (label.rect.y + kiss_textfont.fontheight + 2 * kiss_normal.h)+10);
	strcpy(message ,"Scenario Select");

	ScenarioButton.normalimg = kiss_normal_long;
	ScenarioButton.activeimg = kiss_active_long;
	ScenarioButton.prelightimg = kiss_prelight_long;
	kiss_button_new(&ScenarioButton, &window, message, (window.rect.w / 2 - kiss_normal_long.w / 2), (label.rect.y + kiss_textfont.fontheight + kiss_normal_long.h));
	
	ScenarioButton.rect.w = (strlen(message) * kiss_textfont.advance);

	window.visible = 1;
}

int MainMenu::MainMenuRun()
{
	int draw = 1;
	std::cout << (int)retval << std::endl;
	while (retval == CONTINUE) {
		SDL_Delay(10);
		//std::cout << " main loop " << (int)retval << std::endl;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				retval = QUIT;
			}

			kiss_window_event(&window, &e, &draw);
			scenario_button_event(&ScenarioButton, &e, &draw);
			quit_button_event(&QuitButton, &e, &draw);
		}
		if (!draw) 
		{
		continue;
		}
		MainMenUUpdate(renderer);
		draw = 0;
		//std::cout << "Entering this shit yo" << std::endl;
	}
	kiss_clean(&objects);
	return (int)retval;

}

void MainMenu::MainMenUUpdate(SDL_Renderer *& renderer)
{
		SDL_RenderClear(renderer);
		kiss_window_draw(&window, renderer);
		kiss_label_draw(&label, renderer);
		kiss_button_draw(&ScenarioButton, renderer);
		kiss_button_draw(&QuitButton, renderer);
		SDL_RenderPresent(renderer); 
}

void MainMenu::quit_button_event(kiss_button *button, SDL_Event *e, int *draw)
{
	if (kiss_button_event(button, e, draw)) 
	{
	retval = QUIT;
	}
		
}

void MainMenu::scenario_button_event(kiss_button *button, SDL_Event *e, int *draw)
{
	if (kiss_button_event(button, e, draw)) {
		retval = SCENARIOMENU;
	std::cout << "Scenario Select button" << std::endl;
	}
}