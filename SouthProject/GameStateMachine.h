#ifndef __GameStateMachine__
#define __GameStateMachine__

#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:

	void pushState(GameState *pState);
	void changeState(GameState *pState);
	void popState(void);
	void update(void);
	void render(void);

private:

	std::vector<GameState *> m_gameStates;
};
#endif // !__GameStateMachine__
