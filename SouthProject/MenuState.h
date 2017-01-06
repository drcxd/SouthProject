#ifndef __MenuState__
#define __MenuState__

#include "GameObject.h"
#include "GameState.h"
#include <vector>

class MenuState : public GameState
{
public:

	virtual void update(void);
	virtual void render(void);
	virtual bool onEnter(void);
	virtual bool onExit(void);
	virtual std::string getStateID(void) const { return s_menuID; }

private:

	static const std::string s_menuID;
	std::vector<GameObject *> m_gameObjects;
};

#endif