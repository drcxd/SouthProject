#include "tinyxml.h"

#include "PauseMenu.h"
#include "SDLGameObject.h"
#include "Button.h"
#include "AudioManager.h"
#include "Game.h"
#include "SaveManager.h"
#include "SaveData.h"
#include "Scene.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

// bool PauseMenu::s_bExit = false;

const std::string PauseMenu::s_menuID = "PAUSE";

bool PauseMenu::onEnter(void)
{
	GameObject *pause_background = new SDLGameObject(new LoaderParams(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, "pause_bg"));
	m_gameObjects.push_back(pause_background);

	TiXmlDocument xmlDoc;

	if (!xmlDoc.LoadFile("scripts/menu.xml"))
	{
		std::cerr << "Failed when loading menu xml file. Error : " << xmlDoc.ErrorDesc() << std::endl;
		return false;
	}

	TiXmlElement *pRoot = xmlDoc.RootElement();
	TiXmlElement *pSubRoot = nullptr;

	// Get pause menu point
	for (TiXmlElement *e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		if (e->Value() == std::string("PAUSEMENU"))
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

	TheAudioManager::Instance()->load("music/PauseMenu.mp3", "pausemenu");
	TheAudioManager::Instance()->play("pausemenu");

	static_cast<Button *>(m_gameObjects[1])->setCallback(s_resume);
	static_cast<Button *>(m_gameObjects[2])->setCallback(s_save);
	static_cast<Button *>(m_gameObjects[3])->setCallback(s_load);
	static_cast<Button *>(m_gameObjects[4])->setCallback(s_quit);

	return true;
}

bool PauseMenu::onExit(void)
{
	m_bExit = true;

	while (!m_gameObjects.empty())
	{
		m_gameObjects.back()->clean();
		m_gameObjects.pop_back();
	}

	m_gameObjects.clear();

	TheAudioManager::Instance()->stop();
	TheAudioManager::Instance()->clear("pausemenu");

	return true;
}

void PauseMenu::update(void)
{
	for (auto i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i)
	{
		(*i)->update();
		if (m_bExit)
			break;
	}
}

void PauseMenu::s_resume(void)
{
	TheGame::Instance()->getStateMachine()->popState();
}

void PauseMenu::s_save(void)
{
	SaveData &sd = TheSaveManager::Instance()->getSaveData();
	std::string sceneID;
	unsigned count, bgTimer, bgCounter, fgTimer, fgCounter, msTimer, msCounter;

	Scene *pScene = static_cast<Scene *>(TheGame::Instance()->getStateMachine()->getScene());
	if (pScene != nullptr)
	{
		pScene->getSaveInfo(sceneID, count, bgTimer, fgTimer, msTimer, bgCounter, fgCounter, msCounter);
		sd.setSceneID(sceneID);
		sd.setCount(count);
		sd.setBgTimer(bgTimer);
		sd.setBgCounter(bgCounter);
		sd.setFgTimer(fgTimer);
		sd.setFgCounter(fgCounter);
		sd.setMsTimer(msTimer);
		sd.setMsCounter(msCounter);
		TheSaveManager::Instance()->save();
	}
	else
		std::cerr << "Failed when saving game!\n";
}

void PauseMenu::s_load(void)
{
	while (!TheGame::Instance()->getStateMachine()->isEmpty())
		TheGame::Instance()->getStateMachine()->popState();
	TheSaveManager::Instance()->load();
	TheGame::Instance()->getStateMachine()->pushState(new Scene(TheSaveManager::Instance()->getSaveData().getSceneID(), true));
}

void PauseMenu::s_quit(void)
{
	TheGame::Instance()->clean();
}