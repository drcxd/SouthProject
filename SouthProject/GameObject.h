/* The virtual class which only provide a pattern. */

#ifndef __GameObject__
#define __GameObject__

#include <string>
#include <SDL.h>
#include "LoaderParams.h"

class GameObject
{
public:

	virtual void draw(void) = 0;
	virtual void update(void) = 0;
	virtual void clean(void) = 0;

protected:

	GameObject(const LoaderParams* pParams) {}
	virtual ~GameObject() {}
};
#endif // !__GameObject__
