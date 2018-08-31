#include "ScenarioMenu.h"
class GameInstance;
static void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);

ScenarioMenu::ScenarioMenu()
{
	m_quit = 0;
	m_draw = 1;
	m_textbox_width = 250;
	m_textbox_height = 250;
	m_window2_width = 400;
	m_window2_height = 168;
	m_renderer = kiss_init("ScenarioMenu", &m_objects, 640, 480);
	if (!m_renderer)
	{
		std::cout << "Renderer wrong" << std::endl;
		return;
	}
	kiss_array_new(&m_array1);
	kiss_array_append(&m_objects, ARRAY_TYPE, &m_array1);
	kiss_array_new(&m_array2);
	kiss_array_append(&m_objects, ARRAY_TYPE, &m_array2);

	/* Arrange the widgets nicely relative to each other */
	kiss_window_new(&m_MainWindow, NULL, 1, 0, 0, kiss_screen_width, kiss_screen_height);

	/*kiss_textbox_new(&m_textbox1, &m_MainWindow, 1, &m_array1, kiss_screen_width / 2 - (2 * m_textbox_width + 2 * kiss_up.w - kiss_edge) / 2,
		3 * kiss_normal.h, m_textbox_width, m_textbox_height);
*/
//	kiss_vscrollbar_new(&m_vscrollbar1, &m_MainWindow, m_textbox1.rect.x + m_textbox_width, m_textbox1.rect.y, m_textbox_height);
	kiss_textbox_new(&m_textbox2, &m_MainWindow, 1, &m_array2, kiss_screen_width / 3 , 3*kiss_normal.h-kiss_screen_height/15, m_textbox_width, m_textbox_height);
	kiss_vscrollbar_new(&m_vscrollbar1, &m_MainWindow, m_textbox2.rect.x + m_textbox_width, m_textbox2.rect.y, m_textbox_height);
	kiss_label_new(&m_FileTextBoxLabel, &m_MainWindow, "Files", m_textbox2.rect.x + kiss_edge, m_textbox2.rect.y - kiss_textfont.lineheight);
	kiss_entry_new(&m_entry, &m_MainWindow, 1, "Select a file", kiss_screen_width/10, m_textbox2.rect.y+m_textbox_height, 2 * m_textbox_width + 2 * kiss_up.w + kiss_edge);
	kiss_button_new(&m_button_cancel, &m_MainWindow, "Cancel", m_entry.rect.x + m_entry.rect.w - kiss_edge - kiss_normal.w, m_entry.rect.y + m_entry.rect.h + kiss_normal.h);
	kiss_button_new(&m_Main_ok_button, &m_MainWindow, "OK", m_button_cancel.rect.x - 2 * kiss_normal.w, m_button_cancel.rect.y);
	
	//secondary m_window
	kiss_window_new(&m_SecondaryWindow, NULL, 1, kiss_screen_width / 2 - m_window2_width / 2, kiss_screen_height / 2 - m_window2_height / 2, m_window2_width, m_window2_height);
	kiss_label_new(&m_label_res, &m_SecondaryWindow, "", m_SecondaryWindow.rect.x + kiss_up.w, m_SecondaryWindow.rect.y + kiss_vslider.h);
	m_label_res.textcolor = kiss_blue;
	kiss_progressbar_new(&m_progressbar, &m_SecondaryWindow, m_SecondaryWindow.rect.x + kiss_up.w - kiss_edge, m_SecondaryWindow.rect.y + m_SecondaryWindow.rect.h / 2 - kiss_bar.h / 2 - kiss_border, m_SecondaryWindow.rect.w - 2 * kiss_up.w + 2 * kiss_edge);
	kiss_button_new(&m_Secondary_ok_button, &m_SecondaryWindow, "OK", m_SecondaryWindow.rect.x + m_SecondaryWindow.rect.w / 2 - kiss_normal.w / 2, m_progressbar.rect.y + m_progressbar.rect.h + 2 * kiss_vslider.h);


	kiss_array_free(m_textbox1.array);
	kiss_array_free(m_textbox2.array);
	kiss_array_new(m_textbox1.array);
	kiss_array_new(m_textbox2.array);

	//kiss_string_copy(a_label_sel.text, (2 * m_textbox1.rect.w + 2 * kiss_up.w) / kiss_textfont.advance, buf, ending);
	
	//populate the a_textbox here
	for (auto & p : fs::directory_iterator(m_DirectoryPath))
	{
		std::string FileName = p.path().string();
		char *FileNameCstr = new char[FileName.length() + 1];
		strcpy(FileNameCstr, FileName.c_str());

		kiss_array_appendstring(m_textbox2.array, 0, FileNameCstr, NULL);

	}

	text_reset(&m_textbox2, &m_vscrollbar1);
	/* Do that, and all widgets associated with the m_window will show */

	m_MainWindow.visible = 1;
	//end setup
	
}

void ScenarioMenu::text_reset(kiss_textbox *a_textbox, kiss_vscrollbar *a_vscrollbar)
{
	qsort(a_textbox->array->data, a_textbox->array->length, sizeof(void *), kiss_string_compare);
	a_vscrollbar->step = 0.;
	if (a_textbox->array->length - a_textbox->maxlines > 0)
		a_vscrollbar->step = 1. / (a_textbox->array->length - a_textbox->maxlines);
	a_textbox->firstline = 0;
	a_textbox->highlightline = -1;
	a_vscrollbar->fraction = 0.;
}


/* The widget arguments are widgets that this widget talks with */ 
void ScenarioMenu::textbox2_event(kiss_textbox *a_textbox, SDL_Event *a_event,	kiss_vscrollbar *a_vscrollbar2, kiss_entry *a_entry, int *a_draw)
{
	int index;

	if (kiss_textbox_event(a_textbox, a_event, a_draw)) {
		index = a_textbox->firstline + a_textbox->selectedline;
		if (strcmp((char *)kiss_array_data(a_textbox->array, index), "")) {
			kiss_string_copy(a_entry->text, a_entry->textwidth / kiss_textfont.advance, (char *)kiss_array_data(a_textbox->array, index), NULL);
			*a_draw = 1;
			std::cout << a_textbox->selectedline << std::endl;
			a_entry->selectedIndex = a_textbox->selectedline;
		}
	}
}

void ScenarioMenu::vscrollbar1_event(kiss_vscrollbar *a_vscrollbar, SDL_Event *a_event, kiss_textbox *a_textbox2, int *a_draw)
{
	int firstline;

	if (kiss_vscrollbar_event(a_vscrollbar, a_event, a_draw) &&
		a_textbox2->array->length) {
		firstline = (int)((a_textbox2->array->length -
			a_textbox2->maxlines) * a_vscrollbar->fraction + 0.5);
		if (firstline >= 0) a_textbox2->firstline = firstline;
		*a_draw = 1;
	}
}

void ScenarioMenu::PrintFile(std::string a_filepath)
{
	std::fstream bobby;
	bobby.open(a_filepath);
	std::string output = "";
	while (std::getline(bobby, output))
	{
		std::cout << output << std::endl;
	}
}

void ScenarioMenu::button_ok1_event(kiss_button *a_button, SDL_Event *a_event,	kiss_window *a_window1, kiss_window *a_window2, kiss_label *a_label_sel,
	kiss_entry *a_entry, kiss_label *a_label_res, kiss_progressbar *a_progressbar, int *a_draw, GameInstance &a_GInst)
{
	char buf[KISS_MAX_LENGTH];

	if (kiss_button_event(a_button, a_event, a_draw)) {
		kiss_string_copy(buf, kiss_maxlength(kiss_textfont,	a_window2->rect.w - 2 * kiss_vslider.w, a_label_sel->text, a_entry->text), a_label_sel->text, a_entry->text);
		kiss_string_copy(a_label_res->text, KISS_MAX_LABEL, "The following path was selected:\n", buf);
		a_GInst.SetSelectedScenario(a_entry->text);
		PrintFile(a_GInst.GetScenarioPath());
		//a_window2->visible = 1;
		//a_window2->focus = 1;
		m_quit = 1;
		a_button->prelight = 0;
		a_progressbar->fraction = 0.;
		a_progressbar->run = 1;
		*a_draw = 1;
	}
}

void ScenarioMenu::button_cancel_event(kiss_button *a_button, SDL_Event *a_event,	int *a_quit, int *a_draw)
{
	if (kiss_button_event(a_button, a_event, a_draw))
	{
		*a_quit = 1;
	}
}

void ScenarioMenu::button_ok2_event(kiss_button *a_button, SDL_Event *a_event, kiss_window *a_window1, kiss_window *a_window2,	kiss_progressbar *a_progressbar, int *a_draw)
{
	if (kiss_button_event(a_button, a_event, a_draw)) {
		a_window2->visible = 0;
		a_window1->focus = 1;
		a_button->prelight = 0;
		a_progressbar->fraction = 0.;
		a_progressbar->run = 0;
		*a_draw = 1;
	}

}

int ScenarioMenu::ScenarioMenuRun(GameInstance &a_GInst)
{
	while (!m_quit) {

		/* Some code may be written here */

		SDL_Delay(10);
		while (SDL_PollEvent(&m_event)) {
			if (m_event.type == SDL_QUIT)
				m_quit = 1;

			kiss_window_event(&m_SecondaryWindow, &m_event, &m_draw);
			kiss_window_event(&m_MainWindow, &m_event, &m_draw);
		
			textbox2_event(&m_textbox2, &m_event, &m_vscrollbar1, &m_entry, &m_draw);
			vscrollbar1_event(&m_vscrollbar1, &m_event, &m_textbox2, &m_draw);
			button_ok1_event(&m_Main_ok_button, &m_event, &m_MainWindow, &m_SecondaryWindow, &m_label_sel, &m_entry, &m_label_res, &m_progressbar, &m_draw, a_GInst);
			button_cancel_event(&m_button_cancel, &m_event, &m_quit, &m_draw);
			kiss_entry_event(&m_entry, &m_event, &m_draw);
			button_ok2_event(&m_Secondary_ok_button, &m_event, &m_MainWindow, &m_SecondaryWindow, &m_progressbar, &m_draw);
		}

		//vscrollbar1_event(&m_vscrollbar1, NULL, &m_textbox1, &a_draw);
		vscrollbar1_event(&m_vscrollbar1, NULL, &m_textbox2, &m_draw);
		kiss_progressbar_event(&m_progressbar, NULL, &m_draw);

		if (!m_draw) continue;
		SDL_RenderClear(m_renderer);

		kiss_window_draw(&m_MainWindow, m_renderer);
		kiss_label_draw(&m_LeftTextBoxLabel, m_renderer);
		kiss_label_draw(&m_FileTextBoxLabel, m_renderer);
	//	kiss_textbox_draw(&m_textbox1, renderer);
		kiss_vscrollbar_draw(&m_vscrollbar1, m_renderer);
		kiss_textbox_draw(&m_textbox2, m_renderer);

		kiss_label_draw(&m_label_sel, m_renderer);
		kiss_entry_draw(&m_entry, m_renderer);
		kiss_button_draw(&m_Main_ok_button, m_renderer);
		kiss_button_draw(&m_button_cancel, m_renderer);
		kiss_window_draw(&m_SecondaryWindow, m_renderer);
		kiss_label_draw(&m_label_res, m_renderer);
		kiss_button_draw(&m_Secondary_ok_button, m_renderer);

		SDL_RenderPresent(m_renderer);
		m_draw = 0;
	}
	kiss_clean(&m_objects);
	return 2;
}