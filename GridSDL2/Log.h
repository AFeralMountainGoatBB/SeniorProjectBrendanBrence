#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"
#include "Texture.h"
#include "StaticFunctions.h"
#include "Button.h"

class Log {
public:
	//log functions
	Log();
	Log(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_Font* Font);
	void Setup(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_Font* Font);
	void AddLog(SDL_Renderer *& renderer, std::string LogEntry);
	void AddStringLog(std::string LogEntry);
	void AddTextureLog(SDL_Renderer*& renderer, std::string LogEntry);
	void DeleteFromLog();
	void EventUpIndex(SDL_Event &e, button button);
	void EventDownIndex(SDL_Event &e, button button);
	
	void RenderLog(SDL_Renderer *& Renderer);
	void SetLogConstraints(int x, int y, int w, int h);
	void SetLogConstraints(SDL_Rect other);

	int GetXLogConstraint() { return LogConstraints.x; }
	int GetYLogConstraint() { return LogConstraints.y; }

	void SetFont(TTF_Font* Font);
	void HandleEvents(SDL_Event& e);

private:
	SDL_Rect LogConstraints;
	button UpIndexButton;
	button DownIndexButton;
	TTF_Font *LogFont;
	SDL_Color LogTextColor = { 0, 0, 0 };
	std::deque<std::string>StringLog;
	std::deque<LTexture*> TextureLog;
	int LogMaximumSize = 100;
	int LocationLogIndex = 0;
	int LinesToRender = 6;
	int LINEHEIGHT=20;
	std::string texturePath;

};