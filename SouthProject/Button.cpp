#include <utility>

#include "Button.h"
#include "InputHandler.h"

void Button::draw(void)
{
	SDLGameObject::draw();
}

void Button::update(void)
{
	std::pair<int, int> mousePos = TheInputHandler::Instance()->getMousePosition();

	if (mousePos.first < m_x + m_width && mousePos.first > m_x &&
		mousePos.second < m_y + m_height && mousePos.second > m_y)
	{
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			if (m_callback != 0)
				m_callback();
			m_bReleased = false;
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
			m_bReleased = true;
	}
}

void Button::clean(void)
{
	SDLGameObject::clean();
}