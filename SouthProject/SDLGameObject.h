/* The base class of every actul game object presents in window. */

#include "GameObject.h"

#ifndef __SDLGameObject__
#define __SDLGameObject__

class SDLGameObject : public GameObject
{
public:

	SDLGameObject(const LoaderParams* pParams);

	void draw(void);
	void update(void);
	void clean(void); // The clean function don't do anything here
							  // Because a SDLGameObejct has no allocated resource

protected:

	int m_x;
	int m_y;

	int m_height;
	int m_width;

	int m_currentFrame;
	int m_currentRow;

	std::string m_textureID;
};
#endif // !__SDLGameObject__

