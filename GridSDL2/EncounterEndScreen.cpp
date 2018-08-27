#include "EncounterEndScreen.h"


EncounterEndScreen::EncounterEndScreen()
{
	quit = 0;
	draw = 1;

	renderer = kiss_init("EncounterEndScreen", &objects, 300, 150);
	if (!renderer)
	{
		std::cout << "Renderer wrong" << std::endl;
		return;
	}
	kiss_array_new(&objects);

	/* Arrange the widgets nicely relative to each other */
	kiss_window_new(&window, NULL, 1, 0, 0, kiss_screen_width, kiss_screen_height);
	kiss_label_new(&labelPWin, &window, "Game Over, Player has won", kiss_screen_width*.25 - (.5*kiss_normal.w), kiss_screen_height*.2);
	kiss_label_new(&labelCWin, &window, "Game Over, AI has won", labelPWin.rect.x, kiss_screen_height*.2);

	labelPWin.visible = 0;
	labelCWin.visible = 0;

	kiss_button_new(&QuitButton, &window, "Exit", kiss_screen_width*.5 - (.5*kiss_normal.w), kiss_screen_height*.7);
	window.visible = 1;

	/*kiss_textbox_new(&textbox1, &MainWindow, 1, &a1, kiss_screen_width / 2 - (2 * textbox_width + 2 * kiss_up.w - kiss_edge) / 2,
	3 * kiss_normal.h, textbox_width, textbox_height);
	*/
	/*//	kiss_vscrollbar_new(&vscrollbar1, &MainWindow, textbox1.rect.x + textbox_width, textbox1.rect.y, textbox_height);
	kiss_label_new(&label, &window, "Game Over", label.rect.x + kiss_edge, label.rect.y - kiss_textfont.lineheight);
	kiss_button_new(&QuitButton, &window, "Exit", QuitButton.rect.x - 2 * kiss_normal.w, QuitButton.rect.y);*/
//	window.visible = 1;
}

void EncounterEndScreen::Show(bool playerWin, bool ComputerWin)
{

	if (playerWin == true)
	{
		Pwin = true;
	}
	else if (ComputerWin == true)
	{
		Cwin = true;
	}
	
}


void EncounterEndScreen::quit_button_event(kiss_button *button, SDL_Event *e)
{
	if (kiss_button_event(button, e, &draw))
	{
		quit = 1;
	}
}


void EncounterEndScreen::EndScreenUpdate(SDL_Renderer *& renderer)
{

}

void EncounterEndScreen::EndScreenRun()
{
	while (!quit) {

		/* Some code may be written here */

		SDL_Delay(10);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = 1;

			kiss_window_event(&window, &e, &draw);
			quit_button_event(&QuitButton, &e);
		}

		if (!draw) continue;
		SDL_RenderClear(renderer);
		
		kiss_window_draw(&window, renderer);
		if (Pwin == true)
		{
			kiss_label_draw(&labelPWin, renderer);
		}
		if (Cwin == true)
		{
		kiss_label_draw(&labelCWin, renderer);
		}

		kiss_button_draw(&QuitButton, renderer);

		SDL_RenderPresent(renderer);
		draw = 0;
	}
	kiss_clean(&objects);
	return;
}