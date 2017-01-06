#include "Game.h"
#include "Constants.h"

const unsigned FPS = 60;
const unsigned FRAME_TIME = 1000 / FPS;

int main(int argc, char *argv[])
{
	unsigned int total_frames = 0;
    TheGame::Instance()->init("SouthProject 01", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

	 unsigned start_time, finish_time;
     while (TheGame::Instance()->running())
     {
		 start_time = SDL_GetTicks();
		 TheGame::Instance()->handleEvents();
		 TheGame::Instance()->update();
		 TheGame::Instance()->render();
		 finish_time = SDL_GetTicks();
		 if (finish_time - start_time < FRAME_TIME)
		 {
			 SDL_Delay(FRAME_TIME - (finish_time - start_time));
		 }
     }
     TheGame::Instance()->clean();

     return 0;
}
