#include "Text.h"
#include "Game.h"
#include "Constants.h"
#include <iostream>
#include <SDL_image.h>

Text *Text::s_pInstance = NULL;

Text::Text(void)
{
	m_pFont = TTF_OpenFont("assets/msyh.ttf", 24);
	if (m_pFont == NULL)
	{
		std::cout << "Failed when loading font. Error: " << TTF_GetError() << "\n";
	}
	else
	{
		m_textColor = { 255, 255, 255 };
	}

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
	m_pBackground = NULL;
}

void Text::setContent(std::string content)
{
	m_content = content;
	clean();
	setTexture(content);
}

void Text::draw(void)
{
	drawBackground();
	SDL_Rect destRect = { TEXT_ROW_START, SCREEN_HEIGHT / 5 * 4, m_Width, m_Height};
	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), m_pTexture, NULL, &destRect, 0, 0, SDL_FLIP_NONE);
}

void Text::drawBackground(void)
{
	SDL_Rect destRect = { 0, SCREEN_HEIGHT / 5 * 4, SCREEN_WIDTH,  SCREEN_HEIGHT / 5 };
	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), m_pBackground, NULL, &destRect, 0, 0, SDL_FLIP_NONE);
}

void Text::clean(void)
{
	if (m_pTexture != NULL)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = NULL;
	}
}

bool Text::setTexture(std::string content)
{
	SDL_Surface *tmpSurface = TTF_RenderUTF8_Solid(m_pFont, content.c_str(), m_textColor);

	if (tmpSurface == NULL)
	{
		std::cout << "Faild when creating surface from text. Error: " << TTF_GetError() << "\n";
		return false;
	}
	else
	{
		m_pTexture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), tmpSurface);

		if (m_pTexture == NULL)
		{
			std::cout << "Failed when creating text texture from surface. Error: " << SDL_GetError() << "\n";
			return false;
		}
		else
		{
			m_Width = tmpSurface->w;
			m_Height = tmpSurface->h;
		}
		SDL_FreeSurface(tmpSurface);
	}
	return true;
}

SDL_Texture *Text::getTextTexture(std::string text)
{
	SDL_Surface *tmpSurface = TTF_RenderUTF8_Solid(m_pFont, text.c_str(), m_textColor);
	SDL_Texture *textTexture;

	if (tmpSurface == NULL)
	{
		std::cout << "Failed when creating surface from text. Error: " << TTF_GetError() << "\n";
		return NULL;
	}
	else
	{
		textTexture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), tmpSurface);
		if (textTexture == NULL)
		{
			std::cout << "Failed when creating text texture from surface. Error: " << SDL_GetError() << "\n";
			return NULL;
		}
	}
	SDL_FreeSurface(tmpSurface);

	return textTexture;
}