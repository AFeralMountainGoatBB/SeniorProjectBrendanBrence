#include "Button.h"
#include <functional>

button::button()
{
	mPosition.x = 0;
	mPosition.y = 0;
}

/*
button::button(int x, int y, int width, int height, void (Log::*funct)(), std::string textureName, std::map<std::string, LTexture*> &TextureMap, std::string Path)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.h = height;
	mPosition.w = width;

	//On_Click = funct;
	TexturePath = textureName;

	if (TextureMap.count(Path + "\\" + textureName)) 
	{
		mTexture = TextureMap[Path + "\\" + textureName];
		std::cout << textureName << " Loaded into " << this->name <<  std::endl;
	}
	else
	{
		std::cout << "No matching texture found " << Path << "\\" << textureName << std::endl;
		mTexture = TextureMap[Path + "\\" + "QuestionMark.png"];
	}


}
*/

void button::SetTexture(std::string textureName, std::map<std::string, LTexture*> &TextureMap, std::string Path)
{
	if (TextureMap.count(Path + "\\" + textureName))
	{
		mTexture = TextureMap[Path + "\\" + textureName];
		std::cout << textureName << " Loaded into " << this->name << std::endl;
	}
	else
	{
		std::cout << "No matching texture found " << Path << "\\" << textureName << std::endl;
		mTexture = TextureMap[Path + "\\" + "QuestionMark.png"];
	}
}

void button::setPosition(int x, int y, int width, int height)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.h = height;
	mPosition.w = width;
}

void button::render(SDL_Renderer*& renderer)
{
	//std::cout << "rendering at" << mPosition.x+50 << ", " << mPosition.y << " Height " <<mPosition.h << " width " << mPosition.w <<std::endl;	
	mTexture->renderEntity(mPosition.x, mPosition.y, renderer, &mPosition);
}