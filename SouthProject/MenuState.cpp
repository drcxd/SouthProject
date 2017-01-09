#include "MenuState.h"
#include "SDLGameObject.h"
#include "Text.h"
#include <fstream>
#include "InputHandler.h"
#include "Game.h"
#include "PlayState.h"
#include "Scene.h"
#include "AudioManager.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update(void)
{
	for (std::vector<GameObject *>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

	if (TheInputHandler::Instance()->isEnterPressed())
	{
		TheInputHandler::Instance()->setEnterFree();
		TheGame::Instance()->getStateMachine()->changeState(new Scene("scene01"));
	}
}

void MenuState::render(void)
{
	for (std::vector<GameObject *>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool MenuState::onEnter(void)
{
	GameObject *main_background = new SDLGameObject(new LoaderParams(0, 0, 1024, 576, "main_bg"));

	m_gameObjects.push_back(main_background);

	TheAudioManager::Instance()->load("music/StartMenu.mp3", "startmenu");
	TheAudioManager::Instance()->play("startmenu");

	return true;
}

bool MenuState::onExit(void)
{
	for (std::vector<SDLGameObject *>::size_type i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	TheAudioManager::Instance()->stop();

	return true;
}