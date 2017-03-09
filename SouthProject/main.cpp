/* Program entrance of game.
 */

#include "Game.h"

#include <string>

#include "tinyxml.h"

int FPS; // FPS

int X;
int Y;
int SCREEN_WIDTH; // Window width
int SCREEN_HEIGHT; // Window height

int TEXT_BG_WIDTH; // Text background width which is now the width of window
int TEXT_BG_HEIGHT; // Text background height

int TEXT_ROW_HEIGHT; // Height of one row of text
int TEXT_ROW_START; // Start point of one row of text

std::string title;

unsigned FRAME_TIME;

int main(int argc, char *argv[])
{
	// Get general system info include: 
	// title, screen width and height, x and y position etc.
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile("scripts/environment.xml"))
	{
		std::cerr << "Falied load envrioment xml file. Error: " << xmlDoc.ErrorDesc() << std::endl;
		return -1;
	}
	else
	{
		TiXmlElement *pRoot = xmlDoc.RootElement();
		TiXmlElement *e = pRoot->FirstChildElement();
		e->Attribute("x", &X);
		e = e->NextSiblingElement();
		e->Attribute("y", &Y);
		e = e->NextSiblingElement();
		e->Attribute("screen_width", &SCREEN_WIDTH);
		e = e->NextSiblingElement();
		e->Attribute("screen_height", &SCREEN_HEIGHT);
		e = e->NextSiblingElement();
		e->Attribute("fps", &FPS);
		e = e->NextSiblingElement();
		title = e->Attribute("title");
	}

	TEXT_BG_WIDTH = SCREEN_WIDTH; // Text background width which is now the width of window
	TEXT_BG_HEIGHT = SCREEN_HEIGHT / 5; // Text background height
	TEXT_ROW_HEIGHT = TEXT_BG_HEIGHT / 3; // Height of one row of text
	TEXT_ROW_START = SCREEN_WIDTH / 24; // Start point of one row of text
	FRAME_TIME = 1000 / FPS;
	
	unsigned int total_frames = 0; // variable to count total frame 
	unsigned start_time = 0, finish_time = 0; // Timer to calculate actual frame time

    TheGame::Instance()->init(title.c_str(), X, Y, SCREEN_WIDTH, SCREEN_HEIGHT, NULL); 

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
