#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::s_pInstance = NULL;

void InputHandler::onKeyDown(void)
{
	m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp(SDL_Event event)
{
	switch (event.key.keysym.scancode)
	{
	case SDL_SCANCODE_RETURN: m_bEnterPressed = true; break;
	case SDL_SCANCODE_UP: m_bUpPressed = true; break;
	case SDL_SCANCODE_DOWN: m_bDownPressed = true; break;
	}
}

InputHandler::InputHandler(void) : m_bEnterPressed(false), m_bUpPressed(false), m_bDownPressed(false)
{
	m_keystates = NULL;
}

void InputHandler::update(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->clean();
			break;
		case SDL_KEYDOWN:
			onKeyDown();
			break;
		case SDL_KEYUP:
			onKeyUp(event);
			break;
		default:
			break;
		}
	}
}

void InputHandler::clean(void)
{}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (m_keystates != NULL)
	{
		if (m_keystates[key] == 1)
		{
			return true;
		}
	}

	return false;
}

bool InputHandler::isEnterPressed(void)
{
	return m_bEnterPressed;
}

bool InputHandler::isUpPressed(void)
{
	return m_bUpPressed;
}

bool InputHandler::isDownPressed(void)
{
	return m_bDownPressed;
}

void InputHandler::setEnterFree(void)
{
	m_bEnterPressed = false;
}

void InputHandler::setUpFree(void)
{
	m_bUpPressed = false;
}

void InputHandler::setDownFree(void)
{
	m_bDownPressed = false;
}