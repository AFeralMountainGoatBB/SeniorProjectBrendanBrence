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
	void AddLog(SDL_Renderer *& m_renderer, std::string LogEntry);
	void AddStringLog(std::string LogEntry);
	void AddTextureLog(SDL_Renderer*& m_renderer, std::string LogEntry);
	void DeleteFromLog();
	void EventUpIndex(SDL_Event &m_event, button button);
	void EventDownIndex(SDL_Event &m_event, button button);
	
	void RenderLog(SDL_Renderer *& Renderer);
	void SetLogConstraints(int x, int y, int w, int h);
	void SetLogConstraints(SDL_Rect other);

	int GetXPanelConstraint() { return m_LogConstraints.x; }
	int GetYPanelConstraint() { return m_LogConstraints.y; }

	void SetFont(TTF_Font* Font);
	void HandleEvents(SDL_Event& m_event);

private:
	SDL_Rect m_LogConstraints;
	button m_UpIndexButton;
	button m_DownIndexButton;
	TTF_Font *m_LogFont;
	SDL_Color m_LogTextColor = { 0, 0, 0 };
	std::deque<std::string>m_StringLog;
	std::deque<LTexture*> m_TextureLog;
	int m_LogMaximumSize = 100;
	int m_LocationLogIndex = 0;
	int m_LinesToRender = 6;
	int m_LINEHEIGHT = 20;
	std::string m_texturePath;

};