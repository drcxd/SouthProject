#ifndef __TextButton__
#define __TextButton__

#include "SDLGameObject.h"
#include "InputHandler.h"
#include "Game.h"
#include "Text.h"

class TextButton
{
public:

	TextButton(int x, int y, std::string text, std::string nextSceneID);
	~TextButton(void);
	
	void update(bool *quitPointer);
	void clean(void);
	void draw(void);
	void setFocused(bool b);
	bool isFocused(void);
	bool isShowed(void);

private:

	std::string m_text;
	SDL_Texture *m_pTexture;
	SDL_Rect m_destRect;

	bool m_focused;
	bool m_showed;
	

	void jumpToScene(void);
	const std::string m_nextSceneID;
};

#endif
