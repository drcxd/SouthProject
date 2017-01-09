/* Constants header.
 * You cna sepcify :
 * FPS
 * Window size and resolution.
 * Text background height.
 * Height and start point of one row of text.
 */

#ifndef __Constants__
#define __Constants__

const unsigned FPS = 60; // FPS
const unsigned SCREEN_WIDTH = 1024; // Window width
const unsigned SCREEN_HEIGHT = 576; // Window height
const unsigned TEXT_BG_WIDTH = 1024; // Text background width which is now the width of window
const unsigned TEXT_BG_HEIGHT = SCREEN_HEIGHT / 5; // Text background height
const unsigned TEXT_ROW_HEIGHT = TEXT_BG_HEIGHT / 3; // Height of one row of text
const unsigned TEXT_ROW_START = SCREEN_WIDTH / 24; // Start point of one row of text

const unsigned FRAME_TIME = 1000 / FPS;

#endif // !__Constants__
