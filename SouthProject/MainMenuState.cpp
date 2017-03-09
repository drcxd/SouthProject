#include "tinyxml.h"

#include "MainMenuState.h"
#include "SDLGameObject.h"
#include "Game.h"
#include "Scene.h"
#include "AudioManager.h"
#include "Button.h"
#include "SaveManager.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

bool MainMenuState::s_bExit = false;

const std::string MainMenuState::s_menuID = "MENU";

bool MainMenuState::onEnter(void)
{
	GameObject *main_background = new SDLGameObject(new LoaderParams(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, "main_bg"));

	m_gameObjects.push_back(main_background);

	TiXmlDocument xmlDoc;

	if (!xmlDoc.LoadFile("scripts/menu.xml"))
	{
		std::cerr << "Failed when loading menu xml file. Error : " << xmlDoc.ErrorDesc() << std::endl;
		return false;
	}

	TiXmlElement *pRoot = xmlDoc.RootElement();
	TiXmlElement *pSubRoot = 0;

	// Get main menu root
	for (TiXmlElement *e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		if (e->Value() == std::string("MAINMENU"))
			pSubRoot = e;

	// Load button objects
	for (TiXmlElement *e = pSubRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		int x, y, width, height;
		std::string textureID, objectID;

		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		textureID = e->Attribute("textureID");
		objectID = e->Attribute("objectID");

		Button *pButton = new Button(new LoaderParams(x, y, width, height, textureID));
		m_gameObjects.push_back(pButton);
	}

	TheAudioManager::Instance()->load("music/StartMenu.mp3", "startmenu");
	TheAudioManager::Instance()->play("startmenu");

	static_cast<Button *>(m_gameObjects[1])->setCallback(s_menuToScene);
	static_cast<Button *>(m_gameObjects[2])->setCallback(s_menuToLoad);
	static_cast<Button *>(m_gameObjects[3])->setCallback(s_exit);

	return true;
}

bool MainMenuState::onExit(void)
{
	s_bExit = true;

	while (!m_gameObjects.empty())
	{
		m_gameObjects.back()->clean();
		m_gameObjects.pop_back();
	}

	m_gameObjects.clear();

	TheAudioManager::Instance()->stop();
	TheAudioManager::Instance()->clear("startmenu");

	return true;
}

void MainMenuState::update(void)
{
	for (auto i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i)
	{
		(*i)->update();
		if (s_bExit)
			break;
	}
}

void MainMenuState::s_menuToScene(void)
{
	TheGame::Instance()->getStateMachine()->changeState(new Scene("scene01", false));
}

void MainMenuState::s_menuToLoad(void)
{
	while (!TheGame::Instance()->getStateMachine()->isEmpty())
		TheGame::Instance()->getStateMachine()->popState();
	TheSaveManager::Instance()->load();
	TheGame::Instance()->getStateMachine()->pushState(new Scene(TheSaveManager::Instance()->getSaveData().getSceneID(), true));
}

void MainMenuState::s_exit(void)
{
	TheGame::Instance()->clean();
}