#include "ScenarioMenu.h"
class GameInstance;
static void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);

ScenarioMenu::ScenarioMenu()
{
	quit = 0;
	draw = 1;
	textbox_width = 250;
	textbox_height = 250;
	window2_width = 400;
	window2_height = 168;
	renderer = kiss_init("ScenarioMenu", &objects, 640, 480);
	if (!renderer)
	{
		std::cout << "Renderer wrong" << std::endl;
		return;
	}
	kiss_array_new(&a1);
	kiss_array_append(&objects, ARRAY_TYPE, &a1);
	kiss_array_new(&a2);
	kiss_array_append(&objects, ARRAY_TYPE, &a2);

	/* Arrange the widgets nicely relative to each other */
	kiss_window_new(&MainWindow, NULL, 1, 0, 0, kiss_screen_width, kiss_screen_height);

	/*kiss_textbox_new(&textbox1, &MainWindow, 1, &a1, kiss_screen_width / 2 - (2 * textbox_width + 2 * kiss_up.w - kiss_edge) / 2,
		3 * kiss_normal.h, textbox_width, textbox_height);
*/
//	kiss_vscrollbar_new(&vscrollbar1, &MainWindow, textbox1.rect.x + textbox_width, textbox1.rect.y, textbox_height);
	kiss_textbox_new(&textbox2, &MainWindow, 1, &a2, kiss_screen_width / 3 , 3*kiss_normal.h-kiss_screen_height/15, textbox_width, textbox_height);
	kiss_vscrollbar_new(&vscrollbar1, &MainWindow, textbox2.rect.x + textbox_width, textbox2.rect.y, textbox_height);
	kiss_label_new(&FileTextBoxLabel, &MainWindow, "Files", textbox2.rect.x + kiss_edge, textbox2.rect.y - kiss_textfont.lineheight);
	kiss_entry_new(&entry, &MainWindow, 1, "Select a file", kiss_screen_width/10, textbox2.rect.y+textbox_height, 2 * textbox_width + 2 * kiss_up.w + kiss_edge);
	kiss_button_new(&button_cancel, &MainWindow, "Cancel", entry.rect.x + entry.rect.w - kiss_edge - kiss_normal.w, entry.rect.y + entry.rect.h + kiss_normal.h);
	kiss_button_new(&Main_ok_button, &MainWindow, "OK", button_cancel.rect.x - 2 * kiss_normal.w, button_cancel.rect.y);
	
	//secondary window
	kiss_window_new(&SecondaryWindow, NULL, 1, kiss_screen_width / 2 - window2_width / 2, kiss_screen_height / 2 - window2_height / 2, window2_width, window2_height);
	kiss_label_new(&label_res, &SecondaryWindow, "", SecondaryWindow.rect.x + kiss_up.w, SecondaryWindow.rect.y + kiss_vslider.h);
	label_res.textcolor = kiss_blue;
	kiss_progressbar_new(&progressbar, &SecondaryWindow, SecondaryWindow.rect.x + kiss_up.w - kiss_edge, SecondaryWindow.rect.y + SecondaryWindow.rect.h / 2 - kiss_bar.h / 2 - kiss_border, SecondaryWindow.rect.w - 2 * kiss_up.w + 2 * kiss_edge);
	kiss_button_new(&Secondary_ok_button, &SecondaryWindow, "OK", SecondaryWindow.rect.x + SecondaryWindow.rect.w / 2 - kiss_normal.w / 2, progressbar.rect.y + progressbar.rect.h + 2 * kiss_vslider.h);


	kiss_array_free(textbox1.array);
	kiss_array_free(textbox2.array);
	kiss_array_new(textbox1.array);
	kiss_array_new(textbox2.array);

	//kiss_string_copy(label_sel.text, (2 * textbox1.rect.w + 2 * kiss_up.w) / kiss_textfont.advance, buf, ending);
	
	//populate the textbox here
	for (auto & p : fs::directory_iterator(DirectoryPath))
	{
		std::string FileName = p.path().string();
		char *FileNameCstr = new char[FileName.length() + 1];
		strcpy(FileNameCstr, FileName.c_str());

		kiss_array_appendstring(textbox2.array, 0, FileNameCstr, NULL);

	}

	text_reset(&textbox2, &vscrollbar1);
	/* Do that, and all widgets associated with the window will show */

	MainWindow.visible = 1;
	//end setup
	
}


void ScenarioMenu::text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar)
{
	qsort(textbox->array->data, textbox->array->length, sizeof(void *), kiss_string_compare);
	vscrollbar->step = 0.;
	if (textbox->array->length - textbox->maxlines > 0)
		vscrollbar->step = 1. / (textbox->array->length - textbox->maxlines);
	textbox->firstline = 0;
	textbox->highlightline = -1;
	vscrollbar->fraction = 0.;
}


/* The widget arguments are widgets that this widget talks with */ 
void ScenarioMenu::textbox2_event(kiss_textbox *textbox, SDL_Event *e,	kiss_vscrollbar *vscrollbar2, kiss_entry *entry, int *draw)
{
	int index;

	if (kiss_textbox_event(textbox, e, draw)) {
		index = textbox->firstline + textbox->selectedline;
		if (strcmp((char *)kiss_array_data(textbox->array, index), "")) {
			kiss_string_copy(entry->text, entry->textwidth / kiss_textfont.advance, (char *)kiss_array_data(textbox->array, index), NULL);
			*draw = 1;
			std::cout << textbox->selectedline << std::endl;
			entry->selectedIndex = textbox->selectedline;
		}
	}
}

void ScenarioMenu::vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e, kiss_textbox *textbox2, int *draw)
{
	int firstline;

	if (kiss_vscrollbar_event(vscrollbar, e, draw) &&
		textbox2->array->length) {
		firstline = (int)((textbox2->array->length -
			textbox2->maxlines) * vscrollbar->fraction + 0.5);
		if (firstline >= 0) textbox2->firstline = firstline;
		*draw = 1;
	}
}

void ScenarioMenu::PrintFile(std::string filepath)
{
	std::fstream bobby;
	bobby.open(filepath);
	std::string output = "";
	while (std::getline(bobby, output))
	{
		std::cout << output << std::endl;
	}
}

void ScenarioMenu::button_ok1_event(kiss_button *button, SDL_Event *e,	kiss_window *window1, kiss_window *window2, kiss_label *label_sel,
	kiss_entry *entry, kiss_label *label_res, kiss_progressbar *progressbar, int *draw, GameInstance &GInst)
{
	char buf[KISS_MAX_LENGTH];

	if (kiss_button_event(button, e, draw)) {
		kiss_string_copy(buf, kiss_maxlength(kiss_textfont,	window2->rect.w - 2 * kiss_vslider.w, label_sel->text, entry->text), label_sel->text, entry->text);
		kiss_string_copy(label_res->text, KISS_MAX_LABEL, "The following path was selected:\n", buf);
		GInst.ScenarioPath = entry->text;
		PrintFile(GInst.ScenarioPath);
		window2->visible = 1;
		window2->focus = 1;
		window1->focus = 0;
		button->prelight = 0;
		progressbar->fraction = 0.;
		progressbar->run = 1;
		*draw = 1;
	}
}

void ScenarioMenu::button_cancel_event(kiss_button *button, SDL_Event *e,	int *quit, int *draw)
{
	if (kiss_button_event(button, e, draw))
	{
		*quit = 1;
	}
}

void ScenarioMenu::button_ok2_event(kiss_button *button, SDL_Event *e, kiss_window *window1, kiss_window *window2,	kiss_progressbar *progressbar, int *draw)
{
	if (kiss_button_event(button, e, draw)) {
		window2->visible = 0;
		window1->focus = 1;
		button->prelight = 0;
		progressbar->fraction = 0.;
		progressbar->run = 0;
		*draw = 1;
	}
}

int ScenarioMenu::ScenarioMenuRun(GameInstance &GInst)
{
	while (!quit) {

		/* Some code may be written here */

		SDL_Delay(10);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = 1;

			kiss_window_event(&SecondaryWindow, &e, &draw);
			kiss_window_event(&MainWindow, &e, &draw);
		//	textbox1_event(&textbox1, &e, &vscrollbar1, &textbox2, &vscrollbar2, &label_sel, &draw);
			//vscrollbar1_event(&vscrollbar1, &e, &textbox1, &draw);
			textbox2_event(&textbox2, &e, &vscrollbar1, &entry, &draw);
			vscrollbar1_event(&vscrollbar1, &e, &textbox2, &draw);
			button_ok1_event(&Main_ok_button, &e, &MainWindow, &SecondaryWindow, &label_sel, &entry, &label_res, &progressbar, &draw, GInst);
			button_cancel_event(&button_cancel, &e, &quit, &draw);
			kiss_entry_event(&entry, &e, &draw);
			button_ok2_event(&Secondary_ok_button, &e, &MainWindow, &SecondaryWindow, &progressbar, &draw);
		}

		//vscrollbar1_event(&vscrollbar1, NULL, &textbox1, &draw);
		vscrollbar1_event(&vscrollbar1, NULL, &textbox2, &draw);
		kiss_progressbar_event(&progressbar, NULL, &draw);

		if (!draw) continue;
		SDL_RenderClear(renderer);

		kiss_window_draw(&MainWindow, renderer);
		kiss_label_draw(&LeftTextBoxLabel, renderer);
		kiss_label_draw(&FileTextBoxLabel, renderer);
	//	kiss_textbox_draw(&textbox1, renderer);
		kiss_vscrollbar_draw(&vscrollbar1, renderer);
		kiss_textbox_draw(&textbox2, renderer);

		kiss_label_draw(&label_sel, renderer);
		kiss_entry_draw(&entry, renderer);
		kiss_button_draw(&Main_ok_button, renderer);
		kiss_button_draw(&button_cancel, renderer);
		kiss_window_draw(&SecondaryWindow, renderer);
		kiss_label_draw(&label_res, renderer);
		kiss_button_draw(&Secondary_ok_button, renderer);

		SDL_RenderPresent(renderer);
		draw = 0;
	}
	kiss_clean(&objects);
	return 0;
}