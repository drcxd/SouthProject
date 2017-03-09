#ifndef __MainMenuState__
#define __MainMenuState__

#include "MenuState.h"

class MainMenuState : public MenuState
{
public:
	
	virtual bool onEnter(void);
	virtual bool onExit(void);
	virtual void update(void);
	virtual std::string getStateID(void) const { return s_menuID; }

private:

	static const std::string s_menuID;
	static bool s_bExit;

	static void s_menuToScene(void);
	static void s_menuToLoad(void);
	static void s_exit(void);

};

#endif