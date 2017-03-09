#include <iostream>

#include <SDL_image.h>

#include "Text.h"
#include "Game.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int TEXT_BG_WIDTH;
extern int TEXT_BG_HEIGHT;
extern int TEXT_ROW_HEIGHT;
extern int TEXT_ROW_START;

Text *Text::s_pInstance = nullptr;

Text::Text(void)
{
	// Open font file
	m_pFont = TTF_OpenFont("assets/msyh.ttf", 24);

	if (m_pFont == nullptr)
		std::cout << "Failed when loading font. Error: " << TTF_GetError() << "\n";
	else
		m_textColor = { 255, 255, 255 }; // Set font color

	// Create background picture and set alpha
	SDL_Surface *tmp = IMG_Load("image/text_bg.png");
	m_pBackground = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), tmp);
	SDL_FreeSurface(tmp);
	SDL_SetTextureBlendMode(m_pBackground, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(m_pBackground, 127);
}

Text::~Text(void)
{
	clean();
	SDL_DestroyTexture(m_pBackground);
	m_pBackground = nullptr;
}

// Set text content and generate and store texture of it
void Text::setContent(const std::string &content, unsigned i)
{
	if (i == 0)
		clean();
	m_Content = content;
	setTexture(content);
}

// Create and store text texture and its width and height
bool Text::setTexture(std::string content)
{
	SDL_Surface *tmpSurface = TTF_RenderUTF8_Solid(m_pFont, content.c_str(), m_textColor);

	if (tmpSurface == nullptr)
	{
		std::cerr << "Faild when creating surface from text. Error: " << TTF_GetError() << "\n";
		return false;
	}
	else
	{
		SDL_Texture *pTexture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), tmpSurface);
		if (pTexture == nullptr)
		{
			std::cerr << "Failed to create text texture from surface. Error: " << SDL_GetError() << std::endl;
			return false;
		}
		else
		{
			m_pTextures.push_back(pTexture);
			m_Widths.push_back(tmpSurface->w);
			m_Heights.push_back(tmpSurface->h);
		}
		SDL_FreeSurface(tmpSurface);
	}
	return true;
}

// Function that return texture of given text
SDL_Texture *Text::getTextTexture(const std::string &text)
{
	SDL_Surface *tmpSurface = TTF_RenderUTF8_Solid(m_pFont, text.c_str(), m_textColor);
	SDL_Texture *textTexture;

	if (tmpSurface == nullptr)
	{
		std::cout << "Failed when creating surface from text. Error: " << TTF_GetError() << "\n";
		return nullptr;
	}
	else
	{
		textTexture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), tmpSurface);
		if (textTexture == nullptr)
		{
			std::cout << "Failed when creating text texture from surface. Error: " << SDL_GetError() << "\n";
			return nullptr;
		}
	}
	SDL_FreeSurface(tmpSurface);

	return textTexture;
}

// Draw background and text
void Text::draw(void)
{
	drawBackground();
	for (auto it = m_pTextures.begin(); it != m_pTextures.end(); ++it)
	{
		SDL_Rect destRect = { TEXT_ROW_START, SCREEN_HEIGHT / 5 * 4 + (it - m_pTextures.begin()) * TEXT_ROW_HEIGHT, 
			m_Widths[it - m_pTextures.begin()], m_Heights[it - m_pTextures.begin()] };
		SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), *it, nullptr, &destRect, 0, 0, SDL_FLIP_NONE);
	}
}

// Called by Text::draw
// Actually draw background
void Text::drawBackground(void)
{
	SDL_Rect destRect = { 0, SCREEN_HEIGHT / 5 * 4, TEXT_BG_WIDTH,  TEXT_BG_HEIGHT };
	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), m_pBackground, nullptr, &destRect, 0, 0, SDL_FLIP_NONE);
}

// Destroy texture ,free the pointer and clean all vector
void Text::clean(void)
{
	for (auto it = m_pTextures.begin(); it != m_pTextures.end(); ++it)
		if (*it != nullptr)
		{
			SDL_DestroyTexture(*it);
			*it = nullptr;
		}
	while (!m_pTextures.empty())
		m_pTextures.pop_back();
	while (!m_Widths.empty())
		m_Widths.pop_back();
	while (!m_Heights.empty())
		m_Heights.pop_back();
}
