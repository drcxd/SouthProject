#ifndef __GameState__
#define __GameState__

#include <string>

class GameState
{
public:

	virtual void update(void) = 0;
	virtual void render(void) = 0;

	virtual bool onEnter(void) = 0;
	virtual bool onExit(void) = 0;

	virtual std::string getStateID() const = 0;
};

#endif // !__GameState__
