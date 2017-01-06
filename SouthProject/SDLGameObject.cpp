#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams)
{
	m_x = pParams->getX();
	m_y = pParams->getY();
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();

	m_currentRow = 1;
	m_currentFrame = 1;
}

void SDLGameObject::draw(void)
{
	TheTextureManager::Instance()->draw(m_textureID, m_x, m_y, m_width, m_height,
		TheGame::Instance()->getRenderer());
}

void SDLGameObject::update(void)
{
}

void SDLGameObject::clean(void)
{
}
