#include "TextButton.h"
#include "Scene.h"

TextButton::TextButton(int x, int y, std::string text, std::string nextSceneID) :
	m_nextSceneID(nextSceneID), m_text(text)
{
	m_destRect.x = x;
	m_destRect.y = y;
	m_focused = false;
	m_showed = false;
	m_pTexture = NULL;
	m_pTexture = TheTextManager::Instance()->getTextTexture(m_text);
	if (m_pTexture == NULL)
	{
		std::cout << "Failed when creating texture for text button\n";
	}
	else
	{
		SDL_QueryTexture(m_pTexture, NULL, NULL, &(m_destRect.w), &(m_destRect.h));
	}
}

TextButton::~TextButton(void)
{
	clean();
}

void TextButton::setFocused(bool b)
{
	m_focused = b;
}

bool TextButton::isFocused(void)
{
	return m_focused;
}

bool TextButton::isShowed(void)
{
	return m_showed;
}

void TextButton::update(bool *quitPointer)
{
	if (m_focused)
	{
		SDL_SetTextureColorMod(m_pTexture, 255, 128, 255);
	}
	else
	{
		SDL_SetTextureColorMod(m_pTexture, 255, 255, 255);
	}
	if (m_showed && m_focused && TheInputHandler::Instance()->isEnterPressed())
	{
		TheInputHandler::Instance()->setEnterFree();
		*quitPointer = true;
	}
}

void TextButton::clean(void)
{
	SDL_DestroyTexture(m_pTexture);
}

//void TextButton::jumpToScene(void)
//{
//	TheGame::Instance()->getStateMachine()->changeState(new Scene(m_nextSceneID));
//}

void TextButton::draw(void)
{
	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), m_pTexture, NULL, &m_destRect, 0, NULL, SDL_FLIP_NONE);
	m_showed = true;
}