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

	void quit_button_event(kiss_button *button, SDL_Event *m_event, int *m_draw, int *m_quit);
	void scenario_button_event(kiss_button *button, SDL_Event *m_event, int *m_draw, int *m_quit);

	static void PrintFile(std::string filepath);

	static void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *m_event, kiss_textbox *m_textbox2, int *m_draw);
	static void textbox2_event(kiss_textbox *textbox, SDL_Event *m_event, kiss_vscrollbar *vscrollbar2, kiss_entry *m_entry, int *m_draw);
	static void text_reset(kiss_textbox *textbox, kiss_vscrollbar *vscrollbar);

	static void button_ok2_event(kiss_button *button, SDL_Event *m_event, kiss_window *window1, kiss_window *window2, kiss_progressbar *m_progressbar, int *m_draw);
	static void button_cancel_event(kiss_button *button, SDL_Event *m_event, int *m_quit, int *m_draw);
	void button_ok1_event(kiss_button *button, SDL_Event *m_event, kiss_window *window1, kiss_window *window2, kiss_label *m_label_sel,
		kiss_entry *m_entry, kiss_label *m_label_res, kiss_progressbar *m_progressbar, int *m_draw, GameInstance &GInst);

	int ScenarioMenuRun(GameInstance &GInst);

	void ScenarioMenuUpdate(SDL_Renderer *& m_renderer);

private:
	std::string m_DirectoryPath = "Data\\Scenarios";
	std::string m_ScenarioPath = "";

	SDL_Renderer* m_renderer;
	//variables
	SDL_Event m_event;

	//widgets start

	kiss_array m_objects, m_array1, m_array2;
	kiss_window m_MainWindow, m_SecondaryWindow;
	kiss_label m_LeftTextBoxLabel = { 0 }, m_FileTextBoxLabel = { 0 }, m_label_sel = { 0 }, m_label_res = { 0 };
	kiss_button m_Main_ok_button = { 0 }, m_Secondary_ok_button = { 0 }, m_button_cancel = { 0 };
	kiss_textbox m_textbox1 = { 0 }, m_textbox2 = { 0 };
	kiss_vscrollbar m_vscrollbar1 = { 0 };
	kiss_progressbar m_progressbar = { 0 };
	kiss_entry m_entry = { 0 };
	int m_textbox_width, m_textbox_height, m_window2_width, m_window2_height, m_draw, m_quit;

	//widgets end
};