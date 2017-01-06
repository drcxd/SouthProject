#ifndef __PlayState__
#define __PlayState__

#include "GameState.h"

class PlayState : public GameState
{
public:

	virtual void update(void);
	virtual void render(void);
	virtual bool onEnter(void);
	virtual bool onExit(void);
	virtual std::string getStateID() const { return s_playID; }

private:

	static const std::string s_playID;
};
#endif // !__PlayState__
