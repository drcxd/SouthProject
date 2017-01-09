#include "Game.h"
#include "InputHandler.h"
#include "PlayState.h"
#include "MenuState.h"

#include <iostream>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "tinyxml.h"

Game *Game::s_pInstance = NULL; // Skeleton pointer to asure there is only one instance

// 
bool Game::init(const char *title, int xpos, int ypos,
		int width, int height, int flags)
{
    
	// Initialize SDL create window, renderer and set render color
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
	  std::cout << "Failed when initializing SDL. Error: " 
		  << SDL_GetError() << std::endl;
	  return false;
    }
    else
    {
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width,
					       height, flags);
		if (m_pWindow == NULL)
		{
			   std::cout << "Failed when creating window. Error: "
				 << SDL_GetError() << std::endl;
			return false;
		}
		else
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, NULL);

			if (m_pRenderer == NULL)
			{
				std::cout << "Failed when creating renderer. Error: "
					<< SDL_GetError() << std::endl;
				return false;
			}
			else
			{
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0,
						0, 255);
			}
		}
    }

	 // Init extended parts: img and ttf TODO: we will also initialize audio
	 // subsystem here too
	 if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
	 {
		 std::cout << "Failed when initializing SDL_image.\n";
		 return false;
	 }

	 if (TTF_Init() != 0)
	 {
		 std::cout << "Failed when initializing SDL_ttf.\n";
		 return false;
	 }

	 if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	 {
		 std::cout << "Failed when initializing SDL_mixer.\n SDL_mixer Error: " << Mix_GetError() << std::endl;
		 return false;
	 }

	 loadMedia();

	 // Create game state machine and push a menu state.
	 m_pGameStateMachine = new GameStateMachine();
	 m_pGameStateMachine->changeState(new MenuState());

	 // Set running bool true
     m_bRunning = true;

     return true;
}

void Game::handleEvents(void)
{
	TheInputHandler::Instance()->update();
}

// The following functions loop through m_gameObjects and handle each of them
void Game::render(void)
{
	SDL_RenderClear(m_pRenderer);

	// We call game statae machine render function actually do everything
	m_pGameStateMachine->render();

	SDL_RenderPresent(m_pRenderer);
}

// Destroy window and renderer
void Game::clean(void)
{
	std::cout << "Cleanning game\n";

	// Destroy window
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = NULL;

	// Destroy renderer
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = NULL;

	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
	m_bRunning = false;
}

void Game::update(void)
{
	// Acturally we call game state machine update function to do every thing
	m_pGameStateMachine->update();
}

void Game::loadMedia(void)
{
	TiXmlDocument xmlDoc;

	// Load texture xml file
	if (!xmlDoc.LoadFile("scripts/texture.xml"))
	{
		std::cout << "Failed when loading texture xml file. Error: " << xmlDoc.ErrorDesc() << "\n";
		return;
	}

	TiXmlElement *pRoot = xmlDoc.RootElement();
	std::string fileName; // Variable hold current entry texture name
	std::string textureID; // Variable hold current entry texture ID
	for (TiXmlElement *e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		fileName = e->Attribute("filename");
		textureID = e->Attribute("textureID");
		if (!TheTextureManager::Instance()->load(fileName, textureID, TheGame::Instance()->getRenderer()))
		{
			std::cout << "Failed when loading texture from file: " << fileName << " with texture ID: " <<
				textureID << std::endl;
		}
	}
}