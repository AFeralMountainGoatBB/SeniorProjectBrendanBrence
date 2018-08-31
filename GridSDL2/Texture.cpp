#include "GeneralHeaders.h"
#include "Texture.h"

LTexture::LTexture()
{
	//Initialize
	m_Texture = NULL;
	m_Width = 0;
	m_Height = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string a_path, SDL_Renderer *&a_Renderer)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified a_path
	SDL_Surface* loadedSurface = IMG_Load(a_path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", a_path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(a_Renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", a_path.c_str(), SDL_GetError());
		}
		else
		{
			//std::cout << "made texture successfully" << std::endl;
			//Get image dimensions
			m_Width = loadedSurface->w;
			//std::cout << "mwidth = " <<  m_Width << std::endl;
			m_Height = loadedSurface->h;
			//std::cout << "m_Height = " << m_Height << std::endl;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	m_Texture = newTexture;
	return m_Texture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (this->m_Texture != NULL)
	{
		SDL_DestroyTexture(this->m_Texture);
		this->m_Texture = NULL;
		m_Width = 0;
		m_Height = 0;
	}
}

void LTexture::setColor(Uint8 a_red, Uint8 a_green, Uint8 a_blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(m_Texture, a_red, a_green, a_blue);
}

void LTexture::setBlendMode(SDL_BlendMode a_blending)
{
	//Set a_blending function
	SDL_SetTextureBlendMode(m_Texture, a_blending);
}

void LTexture::setAlpha(Uint8 a_alpha)
{
	//Modulate texture a_alpha
	SDL_SetTextureAlphaMod(m_Texture, a_alpha);
}

void LTexture::renderTile(int a_x, int a_y, SDL_Renderer*& a_Renderer, SDL_Rect* a_clip, double a_angle, SDL_Point* a_center, SDL_RendererFlip a_flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { a_x, a_y, m_Width, m_Height };

	//Set a_clip rendering dimensions
	//a_clip is the box we are clipping tiles from, 
	//important for sprite sheets, will mess up from entities moving around if we do not rewrite this, 
	//will size the destination size
	if (a_clip != NULL)
	{
		renderQuad.w = a_clip->w;
		renderQuad.h = a_clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(a_Renderer, m_Texture, a_clip, &renderQuad, a_angle, a_center, a_flip);
}


void LTexture::renderEntity(int x, int y, SDL_Renderer*& a_Renderer, SDL_Rect* a_clip, double a_angle, SDL_Point* a_center, SDL_RendererFlip a_flip)
{
	//std::cout << "Startin to render" << std::endl;
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_Width, m_Height };
	//std::cout << "Renderquad created" << std::endl;

	if (a_clip != NULL)
	{
		renderQuad.w = a_clip->w;
		renderQuad.h = a_clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(a_Renderer, m_Texture, NULL, &renderQuad, a_angle, a_center, a_flip);
}


int LTexture::getWidth()
{
	return m_Width;
}

int LTexture::getHeight()
{
	return m_Height;
}

void LTexture::setWidth(int a_width)
{
	m_Width = a_width;
}

void LTexture::setHeight(int a_height)
{
	this->m_Height = a_height;
}

void LTexture::setTexture(SDL_Texture* a_Texture)
{
	m_Texture = a_Texture;
}

bool LTexture::loadFromRenderedText(std::string a_textureText, SDL_Color a_textColor, SDL_Renderer*& a_Renderer, TTF_Font *a_Font)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(a_Font, a_textureText.c_str(), a_textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		m_Texture = SDL_CreateTextureFromSurface(a_Renderer, textSurface);
		if (m_Texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			m_Width = textSurface->w;
			m_Height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return m_Texture != NULL;
}