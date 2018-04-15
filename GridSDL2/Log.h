#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"
#include "Texture.h"
#include "StaticFunctions.h"

class Log {
public:
	//log functions
	void AddLog(SDL_Renderer *& renderer, std::string LogEntry);
	void AddStringLog(std::string LogEntry);
	void AddTextureLog(SDL_Renderer*& renderer, std::string LogEntry);
	void DeleteFromLog();
	void UpIndex();
	void DownIndex();
	void RenderLog(SDL_Renderer *& Renderer);

	void SetLogConstraints(int x, int y, int w, int h);
	void SetLogConstraints(SDL_Rect other);

	int NumberOfLines();
	void SetFont(TTF_Font* Font);

private:
	SDL_Rect LogConstraints;
	TTF_Font *LogFont;
	SDL_Color LogTextColor = { 0, 0, 0 };
	std::deque<std::string>StringLog;
	std::deque<LTexture*> TextureLog;
	int LogMaximumSize = 100;
	int LocationLogIndex = 0;
	int LinesToRender = 6;
	int LINEHEIGHT=0;
};