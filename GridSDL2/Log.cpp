#include "Log.h"
Log::Log()
{

}
Log::Log(std::string a_TextureFolderPath, std::map<std::string, LTexture*> &a_TextureMap, SDL_Rect a_viewport, TTF_Font* a_Font)
{
	m_LogConstraints.x = a_viewport.x;
	m_LogConstraints.y = a_viewport.y;
	m_LogConstraints.w = a_viewport.w;
	m_LogConstraints.h = a_viewport.h;

	m_LogFont = a_Font;
	//m_DownIndexButton.click = &Log::DownIndex;

	m_UpIndexButton.setPosition(m_LogConstraints.x, m_LogConstraints.y+80, 30, 30);
	m_DownIndexButton.setPosition(m_LogConstraints.x, m_LogConstraints.y, 30, 30);
	m_UpIndexButton.SetTexture("UpArrow.png", a_TextureMap, a_TextureFolderPath);
	m_DownIndexButton.SetTexture("DownArrow.png", a_TextureMap, a_TextureFolderPath);
}

void Log::Setup(std::string a_TextureFolderPath, std::map<std::string, LTexture*> &a_TextureMap, SDL_Rect a_viewport, TTF_Font* a_Font)
{
	m_LogConstraints.x = a_viewport.x;
	m_LogConstraints.y = a_viewport.y;
	m_LogConstraints.w = a_viewport.w;
	m_LogConstraints.h = a_viewport.h;

	m_LogFont = a_Font;
	//m_UpIndexButton();
	//m_DownIndexButton(&Log::DownIndex);

	m_UpIndexButton.SetName("m_UpIndexButton");
	m_DownIndexButton.SetName("m_DownIndexButton");
	m_UpIndexButton.setPosition(a_viewport.x+20, a_viewport.h-a_viewport.h*.8, 30, 30);
	m_DownIndexButton.setPosition(a_viewport.x+20, a_viewport.h-a_viewport.h*.2, 30, 30);
	m_UpIndexButton.SetTexture("UpArrow.png", a_TextureMap, a_TextureFolderPath);
	m_DownIndexButton.SetTexture("DownArrow.png", a_TextureMap, a_TextureFolderPath);
	m_UpIndexButton.SetYOffset(a_viewport.y);
	m_DownIndexButton.SetYOffset(a_viewport.y);
	//m_UpIndexButton.setFunction(&UpIndex);
}

void Log::HandleEvents(SDL_Event& a_event)
{
	EventUpIndex(a_event, m_UpIndexButton);
	EventDownIndex(a_event, m_DownIndexButton);
}

void Log:: SetLogConstraints(int a_x, int a_y, int a_w, int a_h)
{
	m_LogConstraints.x = a_x;
	m_LogConstraints.y = a_y;
	m_LogConstraints.w = a_w;
	m_LogConstraints.h = a_h;
}

void Log::SetLogConstraints(SDL_Rect a_other)
{
	m_LogConstraints = a_other;
//	std::cout << "Constraints for log: a_x:" << m_LogConstraints.a_x << " a_y: " << m_LogConstraints.a_y << std::endl;
}

void Log::SetFont(TTF_Font* a_Font)
{
	m_LogFont = a_Font;
}

void Log::AddLog(SDL_Renderer*& a_Renderer, std::string a_LogEntry)
{
	std::cout << "a_LogEntry: " << a_LogEntry << std::endl;
	AddStringLog(a_LogEntry);
	AddTextureLog(a_Renderer, a_LogEntry);
	while (m_StringLog.size() >= m_LogMaximumSize)
	{
		//deletes from back, we insert from front
		DeleteFromLog();
	}
}
void Log::AddStringLog(std::string a_LogEntry)
{
	//push from front so we will pop from back
	m_StringLog.push_front(a_LogEntry);
}

void Log::AddTextureLog(SDL_Renderer *& a_Renderer, std::string a_LogEntry)
{
	//create texture
	LTexture* LogAdd = new LTexture;
	//render it from text
	LogAdd->loadFromRenderedText(a_LogEntry, m_LogTextColor, a_Renderer, m_LogFont);
	//add it to the deque
	//std::cout << "Adding a log!" << std::endl;
	m_TextureLog.push_front(LogAdd);
}

void Log::DeleteFromLog()
{
	//std::cout << "Deleting from log" << std::endl;
	m_TextureLog.back()->free();
	m_TextureLog.pop_back();
	m_StringLog.pop_back();
}

void Log::EventUpIndex(SDL_Event& a_event, button a_button )
{
	if (a_event.type == SDL_MOUSEBUTTONDOWN)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		//Check if mouse is in a_button
		//check if mouse is inside the a_button 
		if (x > a_button.GetXPos() && x < a_button.GetYPos() + a_button.GetWidth() && y < a_button.GetYPos() + a_button.GetHeight() + a_button.GetYOffset() && y > a_button.GetYPos() +a_button.GetYOffset())
		{
			//std::cout << "Button pressed" << std::endl;
			if (m_LocationLogIndex<m_StringLog.size()-m_LinesToRender)
			{
				m_LocationLogIndex++;
			}
		}
	}
}

void Log::EventDownIndex(SDL_Event &a_event, button a_button)
{
	if (a_event.type == SDL_MOUSEBUTTONDOWN)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		//check if mouse is inside the a_button 
		if (x > a_button.GetXPos() && x < a_button.GetYPos() + a_button.GetWidth() && y < a_button.GetYPos() + a_button.GetHeight() + a_button.GetYOffset() && y > a_button.GetYPos() + a_button.GetYOffset())
		{
			//std::cout << "Button pressed" << std::endl;
			if (m_LocationLogIndex > 0)
			{
				m_LocationLogIndex--;
			}
		}
	}
	
}
void Log::RenderLog(SDL_Renderer *& a_Renderer)
{
	int currentY = m_LogConstraints.h-40;
	//std::cout << m_TextureLog.size() << std::endl;
	for (int i = 0; i<m_TextureLog.size() && i < m_LinesToRender; i++)
	{
		//std::cout << i+m_LocationLogIndex<< m_StringLog[i + m_LocationLogIndex] << std::endl;
		m_TextureLog[i + m_LocationLogIndex]->renderTile(m_LogConstraints.x+50, currentY, a_Renderer);
		currentY -= 21;
	}
	m_UpIndexButton.render(a_Renderer);
	m_DownIndexButton.render(a_Renderer);
}