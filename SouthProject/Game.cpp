#include "Game.h"
#include "InputHandler.h"
#include "PlayState.h"
#include "MenuState.h"
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "tinyxml.h"

Game* Game::s_pInstance = NULL;

bool Game::init(const char *title, int xpos, int ypos,
		int width, int height, int flags)
{
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

	 // Init extended parts
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

	 // Now we do media loading here
	 /*TheTextureManager::Instance()->load("image/main_bg.png", "main_bg", TheGame::Instance()->getRenderer());
	 TheTextureManager::Instance()->load("image/morning.png", "morning", TheGame::Instance()->getRenderer());
	 TheTextureManager::Instance()->load("image/yukino.png", "yukino", TheGame::Instance()->getRenderer());
	 TheTextureManager::Instance()->load("image/noon.png", "noon", TheGame::Instance()->getRenderer());
	 TheTextureManager::Instance()->load("image/afternoon.png", "afternoon", TheGame::Instance()->getRenderer());*/
	 loadMedia();

	 m_pGameStateMachine = new GameStateMachine();
	 m_pGameStateMachine->changeState(new MenuState());

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

	m_pGameStateMachine->render();

	SDL_RenderPresent(m_pRenderer);
}

void Game::clean(void)
{
	std::cout << "Cleanning game\n";
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = NULL;
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = NULL;

	SDL_Quit();
	m_bRunning = false;
}

void Game::update(void)
{
	m_pGameStateMachine->update();
}

void Game::loadMedia(void)
{
	TiXmlDocument xmlDoc;

	if (!xmlDoc.LoadFile("scripts/texture.xml"))
	{
		std::cout << "Failed when loading texture xml file. Error: " << xmlDoc.ErrorDesc() << "\n";
		return;
	}

	TiXmlElement *pRoot = xmlDoc.RootElement();
	std::string fileName;
	std::string textureID;
	for (TiXmlElement *e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		fileName = e->Attribute("filename");
		textureID = e->Attribute("textureID");
		if (!TheTextureManager::Instance()->load(fileName, textureID, TheGame::Instance()->getRenderer()))
		{
			std::cout << "Failed when loading texture from file: " << fileName << " with texture ID: " <<
				textureID << "\n";
		}
	}
}