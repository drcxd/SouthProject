#include "TextureManager.h"
#include <SDL_image.h>

/* TheTextureManager handles with texture loading, storage and rendering. */

TextureManager* TextureManager::s_pInstance = NULL;

// Load the texture specified by the fileName, saved with id in member variable m_textureMap
bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer *pRenderer)
{
	SDL_Surface *pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == NULL)
	{
		return false;
	}

	SDL_Texture *pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);
	pTempSurface = NULL;

	if (pTexture == NULL)
	{
		return false;
	}

	m_textureMap[id] = pTexture;

	return true;
}

// Draw the texture specified by id on (x, y) with width and height
void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer *pRenderer,
	SDL_RendererFlip flip)
{
	SDL_Rect destRect;

	destRect.w = width;
	destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], NULL, &destRect, 0, 0, flip);
}

// Advanced draw function with addtional param row and frame
void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow,
	int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}