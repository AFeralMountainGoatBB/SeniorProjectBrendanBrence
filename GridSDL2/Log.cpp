#include "Log.h"

void Log:: SetLogConstraints(int x, int y, int w, int h)
{
	LogConstraints.x = x;
	LogConstraints.y = y;
	LogConstraints.w = w;
	LogConstraints.h = h;
}

void Log::SetLogConstraints(SDL_Rect other)
{
	LogConstraints = other;
	std::cout << "Constraints for log: x:" << LogConstraints.x << " y: " << LogConstraints.y << std::endl;
}

void Log::SetFont(TTF_Font* Font)
{
	LogFont = Font;
}

void Log::AddLog(SDL_Renderer*& Renderer, std::string LogEntry)
{
	std::cout << "LogEntry: " << LogEntry << std::endl;
	AddStringLog(LogEntry);
	AddTextureLog(Renderer, LogEntry);
	while (StringLog.size() >= LogMaximumSize)
	{
		//deletes from back, we insert from front
		DeleteFromLog();
	}
}
void Log::AddStringLog(std::string LogEntry)
{
	//push from front so we will pop from back
	StringLog.push_front(LogEntry);
}

void Log::AddTextureLog(SDL_Renderer *& Renderer, std::string LogEntry)
{
	//create texture
	LTexture* LogAdd = new LTexture;
	//render it from text
	LogAdd->loadFromRenderedText(LogEntry, LogTextColor, Renderer, LogFont);
	//add it to the deque
	//std::cout << "Adding a log!" << std::endl;
	TextureLog.push_front(LogAdd);
}

void Log::DeleteFromLog()
{
	std::cout << "Deleting from log" << std::endl;
	TextureLog.back()->free();
	TextureLog.pop_back();
	StringLog.pop_back();
}
void Log::UpIndex()
{
	if (LocationLogIndex<StringLog.size())
	{
		LocationLogIndex++;
	}
}
void Log::DownIndex()
{
	if (LocationLogIndex > 0)
	{
		LocationLogIndex--;
	}
}
void Log::RenderLog(SDL_Renderer *& Renderer)
{
	int currentY = LogConstraints.h-40;
	//std::cout << TextureLog.size() << std::endl;
	for (int i = 0; i<TextureLog.size() && i < LinesToRender; i++)
	{
		//std::cout << i+LocationLogIndex<< StringLog[i + LocationLogIndex] << std::endl;
		TextureLog[i + LocationLogIndex]->renderTile(LogConstraints.x+50, currentY, Renderer);
		currentY -= 21;
	}
	
}