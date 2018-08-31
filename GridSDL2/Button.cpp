#include "Button.h"
#include <functional>

button::button()
{
	m_Position.x = 0;
	m_Position.y = 0;
}

/*
button::button(int a_x, int a_y, int m_width, int m_height, void (Log::*funct)(), std::string a_textureName, std::map<std::string, LTexture*> &a_TextureMap, std::string a_Path)
{
	m_Position.a_x = a_x;
	m_Position.a_y = a_y;
	m_Position.h = m_height;
	m_Position.w = m_width;

	//On_Click = funct;
	m_TexturePath = a_textureName;

	if (a_TextureMap.count(a_Path + "\\" + a_textureName)) 
	{
		m_Texture = a_TextureMap[a_Path + "\\" + a_textureName];
		std::cout << a_textureName << " Loaded into " << this->m_name <<  std::endl;
	}
	else
	{
		std::cout << "No matching texture found " << a_Path << "\\" << a_textureName << std::endl;
		m_Texture = a_TextureMap[a_Path + "\\" + "QuestionMark.png"];
	}


}
*/

void button::SetTexture(std::string a_textureName, std::map<std::string, LTexture*> &a_TextureMap, std::string a_Path)
{
	if (a_TextureMap.count(a_Path + "\\" + a_textureName))
	{
		m_Texture = a_TextureMap[a_Path + "\\" + a_textureName];
		std::cout << a_textureName << " Loaded into " << this->m_name << std::endl;
	}
	else
	{
		std::cout << "No matching texture found " << a_Path << "\\" << a_textureName << std::endl;
		m_Texture = a_TextureMap[a_Path + "\\" + "QuestionMark.png"];
	}
}

void button::setPosition(int a_x, int a_y, int a_width, int a_height)
{
	m_Position.x = a_x;
	m_Position.y = a_y;
	m_Position.h = a_height;
	m_Position.w = a_width;
}

void button::render(SDL_Renderer*& a_renderer)
{
	//std::cout << "rendering at" << m_Position.a_x+50 << ", " << m_Position.a_y << " Height " <<m_Position.h << " m_width " << m_Position.w <<std::endl;	
	m_Texture->renderEntity(m_Position.x, m_Position.y, a_renderer, &m_Position);
}