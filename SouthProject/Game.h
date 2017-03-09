#ifndef __Game__
#define __Game__

#include <vector>

#include <SDL.h>

#include "TextureManager.h"
#include "GameObject.h"
#include "GameStateMachine.h"

class Game
{
public:

     ~Game(void) {}

	 // Process control functions
     bool init(const char* title, int xpos, int ypos,
	       int width, int height, int flags);
	 void render(void);
     void update(void);
     void handleEvents(void);
	 void clean(void);
	 void loadMedia(void);

	 // Getters
	 SDL_Renderer *getRenderer() const { return m_pRenderer; }
	 bool running(void) { return m_bRunning; }
	 GameStateMachine *getStateMachine(void) { return m_pGameStateMachine; }

	 // Skeleton
	 static Game *Instance()
	 {
		 if (s_pInstance == nullptr)
		 {
			 s_pInstance = new Game();
		 }

		 return s_pInstance;
	 }

private:

     SDL_Window *m_pWindow;
     SDL_Renderer *m_pRenderer;
     bool m_bRunning;
	 std::vector<GameObject *> m_gameObjects;
	 GameStateMachine *m_pGameStateMachine;

	 static Game* s_pInstance;
	 Game(void) {}
};

typedef Game TheGame;

#endif __Game__
