/* Constants header.
 * Technically, the variable defined here is not constants.
 * But these variable won't change once were specified by 
 * the user through xml file. So I still call them constants.
 */
#pragma once
//#ifndef __Constants__
//#define __Constants__

#include <string>

unsigned FPS = 60; // FPS

unsigned X;
unsigned Y;
unsigned SCREEN_WIDTH = 1024; // Window width
unsigned SCREEN_HEIGHT = 576; // Window height

unsigned TEXT_BG_WIDTH = 1024; // Text background width which is now the width of window
unsigned TEXT_BG_HEIGHT = SCREEN_HEIGHT / 5; // Text background height

unsigned TEXT_ROW_HEIGHT = TEXT_BG_HEIGHT / 3; // Height of one row of text
unsigned TEXT_ROW_START = SCREEN_WIDTH / 24; // Start point of one row of text

std::string title;

const unsigned FRAME_TIME = 1000 / FPS;

//#endif // !__Constants__
