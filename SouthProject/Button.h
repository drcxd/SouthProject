#ifndef __Button__
#define __Button__

#include "SDLGameObject.h"

class Button : public SDLGameObject
{
public:

	Button(const LoaderParams *pParams) : SDLGameObject(pParams), m_callback(nullptr), m_bReleased(true) {}

	void draw(void);
	void update(void);
	void clean(void);

	void setCallback(void(*callback)()) { m_callback = callback; }
	int getCallbackID(void) { return m_callbackID; }

private:

	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_ON = 1,
		CLICKED = 2
	};

	bool m_bReleased;
	int m_callbackID;
	void(*m_callback)();
};


#endif