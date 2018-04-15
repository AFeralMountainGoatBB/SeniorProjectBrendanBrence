#pragma once
#include "GeneralHeaders.h"
#include <string>
#include <iostream>
#include <filesystem>
#include "GameInstance.h"

//std::filesystem;

/*int main()
{
	std::string path = "path_to_directory";
	for (auto & p : fs::directory_iterator(path))
		std::cout << p << std::endl;
}*/

class ScenarioMenu
{
public:
	ScenarioMenu();
	std::string DirectoryPath = "Data\\Scenarios";
	std::string ScenarioPath = "";

	SDL_Renderer* renderer;
	//variables
	SDL_Event e;

	//widgets start

	kiss_array objects, a1, a2;
	kiss_window MainWindow, SecondaryWindow;
	kiss_label LeftTextBoxLabel = { 0 }, FileTextBoxLabel = { 0 }, label_sel = { 0 }, label_res = { 0 };
	kiss_button Main_ok_button = { 0 }, Secondary_ok_button = { 0 }, button_cancel = { 0 };
	kiss_textbox textbox1 = { 0 }, textbox2 = { 0 };
	kiss_vscrollbar vscrollbar1 = { 0 };
	kiss_progressbar progressbar = { 0 };
	kiss_entry entry = { 0 };
	int textbox_width, textbox_height, window2_width, window2_height, draw, quit;

	//widgets end


	void quit_button_event(kiss_button *button, SDL_Event *e, int *draw, int *quit);
	void scenario_button_event(kiss_button *button, SDL_Event *e, int *draw, int *quit);

	static void PrintFile(std::string filepath);

	static void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e, kiss_textbox *textbox2, int *draw);
	static void textbox2_event(kiss_textbox *textbox, SDL_Event *e, kiss_vscrollbar *vscrollbar2, kiss_entry *entry, int *draw);
	static void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);

	static void button_ok2_event(kiss_button *button, SDL_Event *e, kiss_window *window1, kiss_window *window2, kiss_progressbar *progressbar, int *draw);
	static void button_cancel_event(kiss_button *button, SDL_Event *e, int *quit, int *draw);
	void button_ok1_event(kiss_button *button, SDL_Event *e, kiss_window *window1, kiss_window *window2, kiss_label *label_sel,
		kiss_entry *entry, kiss_label *label_res, kiss_progressbar *progressbar, int *draw, GameInstance &GInst);

	int ScenarioMenuRun(GameInstance &GInst);

	void ScenarioMenuUpdate(SDL_Renderer *& renderer);


};