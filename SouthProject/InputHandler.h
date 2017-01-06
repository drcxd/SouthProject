#ifndef __InputHandler__
#define __InputHandler__

#include <SDL.h>

class InputHandler
{
public:

	static InputHandler* Instance()
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new InputHandler();
		}

		return s_pInstance;
	}

	void update(void);
	void clean(void);

	bool isKeyDown(SDL_Scancode key);
	bool isEnterPressed(void);
	void setEnterFree(void);
	bool isUpPressed(void);
	void setUpFree(void);
	bool isDownPressed(void);
	void setDownFree(void);
	void onKeyDown(void);
	void onKeyUp(SDL_Event e);
	const Uint8* getKeyboardState(void) { return m_keystates; }

private:

	InputHandler(void);
	~InputHandler(void) {}

	bool m_bEnterPressed;
	bool m_bUpPressed;
	bool m_bDownPressed;
	static InputHandler *s_pInstance;
	const Uint8* m_keystates;
};

typedef InputHandler TheInputHandler;
#endif // !__InputHandler__
