#include "Log.h"
Log::Log()
{

}
Log::Log(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_Font* Font)
{
	LogConstraints.x = viewport.x;
	LogConstraints.y = viewport.y;
	LogConstraints.w = viewport.w;
	LogConstraints.h = viewport.h;

	LogFont = Font;
	//DownIndexButton.click = &Log::DownIndex;

	UpIndexButton.setPosition(LogConstraints.x, LogConstraints.y+80, 30, 30);
	DownIndexButton.setPosition(LogConstraints.x, LogConstraints.y, 30, 30);
	UpIndexButton.SetTexture("UpArrow.png", TextureMap, TextureFolderPath);
	DownIndexButton.SetTexture("DownArrow.png", TextureMap, TextureFolderPath);
}

void Log::Setup(std::string TextureFolderPath, std::map<std::string, LTexture*> &TextureMap, SDL_Rect viewport, TTF_Font* Font)
{
	LogConstraints.x = viewport.x;
	LogConstraints.y = viewport.y;
	LogConstraints.w = viewport.w;
	LogConstraints.h = viewport.h;

	LogFont = Font;
	//UpIndexButton();
	//DownIndexButton(&Log::DownIndex);

	UpIndexButton.SetName("UpIndexButton");
	DownIndexButton.SetName("DownIndexButton");
	UpIndexButton.setPosition(viewport.x+20, viewport.h-viewport.h*.8, 30, 30);
	DownIndexButton.setPosition(viewport.x+20, viewport.h-viewport.h*.2, 30, 30);
	UpIndexButton.SetTexture("UpArrow.png", TextureMap, TextureFolderPath);
	DownIndexButton.SetTexture("DownArrow.png", TextureMap, TextureFolderPath);
	UpIndexButton.SetYOffset(viewport.y);
	DownIndexButton.SetYOffset(viewport.y);
	//UpIndexButton.setFunction(&UpIndex);
}

void Log::HandleEvents(SDL_Event& e)
{
	EventUpIndex(e, UpIndexButton);
	EventDownIndex(e, DownIndexButton);
}

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
//	std::cout << "Constraints for log: x:" << LogConstraints.x << " y: " << LogConstraints.y << std::endl;
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
	//std::cout << "Deleting from log" << std::endl;
	TextureLog.back()->free();
	TextureLog.pop_back();
	StringLog.pop_back();
}

void Log::EventUpIndex(SDL_Event& e, button button )
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		//Check if mouse is in button
		//check if mouse is inside the button 
		if (x > button.GetXPos() && x < button.GetYPos() + button.GetWidth() && y < button.GetYPos() + button.GetHeight() + button.GetYOffset() && y > button.GetYPos() +button.GetYOffset())
		{
			//std::cout << "Button pressed" << std::endl;
			if (LocationLogIndex<StringLog.size()-LinesToRender)
			{
				LocationLogIndex++;
			}
		}
	}
}

void Log::EventDownIndex(SDL_Event &e, button button)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		//check if mouse is inside the button 
		if (x > button.GetXPos() && x < button.GetYPos() + button.GetWidth() && y < button.GetYPos() + button.GetHeight() + button.GetYOffset() && y > button.GetYPos() + button.GetYOffset())
		{
			//std::cout << "Button pressed" << std::endl;
			if (LocationLogIndex > 0)
			{
				LocationLogIndex--;
			}
		}
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
	UpIndexButton.render(Renderer);
	DownIndexButton.render(Renderer);
}