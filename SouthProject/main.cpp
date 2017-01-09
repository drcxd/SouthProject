/* Program entrance of game.
 */

#include "Game.h"
#include "Constants.h"

int main(int argc, char *argv[])
{
	extern const unsigned FPS;
	extern const unsigned FRAME_TIME;
	unsigned int total_frames = 0; // variable to count total frame 
	unsigned start_time = 0, finish_time = 0; // Timer to calculate actual frame time

	// TODO: Summary init function
    TheGame::Instance()->init("SouthProject 01", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, NULL); 

     while (TheGame::Instance()->running()) 
     {
		 start_time = SDL_GetTicks(); // get actual start time of per frame
		 TheGame::Instance()->handleEvents();
		 TheGame::Instance()->update();
		 TheGame::Instance()->render();
		 finish_time = SDL_GetTicks(); // get actual end time of per frame
		 if (finish_time - start_time < FRAME_TIME)
		 {
			 SDL_Delay(FRAME_TIME - (finish_time - start_time)); // Pause game if actual frame time is less than frame time.
		 }
     }
     TheGame::Instance()->clean();

     return 0;
}
