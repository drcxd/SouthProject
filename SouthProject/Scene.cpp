#include <iostream>

#include "Scene.h"
#include "InputHandler.h"
#include "AudioManager.h"
#include "PauseMenu.h"
#include "SaveManager.h"

extern int SCREEN_HEIGHT;
extern int TEXT_ROW_HEIGHT;
extern int TEXT_ROW_START;

void Scene::update()
{
	if (TheInputHandler::Instance()->isEnterPressed())
	{
		++m_count;
		if (m_count < m_max)
		{
			TheInputHandler::Instance()->setEnterFree();

			// Handle background timer and counter and change background if necessary
			--m_bgTimer;
			if (m_bgTimer == 0)
			{
				++m_bgCounter;
				if (m_bgCounter < m_backgrounds.size())
				{
					m_background = m_objectsMap[m_backgrounds[m_bgCounter].first];
					m_bgTimer = m_backgrounds[m_bgCounter].second;
				}
			}

			// Handle figure timer and counter and change figure if necessary
			--m_fgTimer;
			if (m_fgTimer == 0)
			{
				++m_fgCounter;
				if (m_fgCounter < m_figures.size())
				{
					m_figure = m_objectsMap[m_figures[m_fgCounter].first];
					m_fgTimer = m_figures[m_fgCounter].second;
				}
			}

			// Handle music timer and counter and change music if necessary
			--m_msTimer;
			if (m_msTimer == 0)
			{
				++m_msCounter;
				if (m_msCounter < m_music.size())
				{
					TheAudioManager::Instance()->stop();
					TheAudioManager::Instance()->play(m_music[m_msCounter].first);
					m_msTimer = m_music[m_msCounter].second;
				}
			}

			// Read text depend on current lines.
			for (int i = 0; i < m_textLines.at(m_count) - '0'; ++i)
			{
				std::getline(m_input, m_text, '\n');
				TheTextManager::Instance()->setContent(m_text, i);
			}
		}
		else if (m_count == m_max)
		{
			TheInputHandler::Instance()->setEnterFree();
			std::string tmpStr;
			for (decltype(m_nextSceneIDs.size()) i = 0; i < m_nextSceneIDs.size(); ++i)
			{
				std::getline(m_input, tmpStr, '\n');
				TextButton *pTextButton = new TextButton(TEXT_ROW_START, SCREEN_HEIGHT / 5 * 4 + i * TEXT_ROW_HEIGHT,
					tmpStr, m_nextSceneIDs[i]);
				if (i == 0)
					pTextButton->setFocused(true);
				m_textButtons.push_back(pTextButton);
			}
			m_focused_point = 0;
		}
		else
			m_count--;
	}


	if (m_count == m_max && TheInputHandler::Instance()->isUpPressed())
	{
		TheInputHandler::Instance()->setUpFree();
		--m_focused_point;
		if (m_focused_point < 0)
			++m_focused_point;
		else
		{
			m_textButtons[m_focused_point + 1]->setFocused(false);
			m_textButtons[m_focused_point]->setFocused(true);
		}
	}

	if (m_count == m_max && TheInputHandler::Instance()->isDownPressed())
	{
		TheInputHandler::Instance()->setDownFree();
		++m_focused_point;
		if (m_focused_point > m_nextSceneIDs.size() - 1)
			--m_focused_point;
		else
		{
			m_textButtons[m_focused_point - 1]->setFocused(false);
			m_textButtons[m_focused_point]->setFocused(true);
		}
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->pushState(new PauseMenu());
	}


	if (m_count == m_max)
	{
		for (decltype(m_textButtons.size()) i = 0; i < m_textButtons.size(); ++i)
			m_textButtons[i]->update(&m_bQuit);
	}

	if (m_bQuit)
	{
		TheGame::Instance()->getStateMachine()->changeState(new Scene(m_nextSceneIDs[m_focused_point], false));
	}
}

void Scene::render(void)
{
	if (m_background != nullptr)
		m_background->draw();
	if (m_figure != nullptr)
		m_figure->draw();
	if (m_count < m_max)
		TheTextManager::Instance()->draw();
	else if (m_count == m_max)
	{
		TheTextManager::Instance()->drawBackground();
		for (auto i : m_textButtons)
			i->draw();
	}
}

bool Scene::onEnter(void)
{
	TiXmlDocument m_xmlDoc;

	if (!m_xmlDoc.LoadFile("scripts/scenes.xml"))
	{
		std::cerr << "Failed when loading scenes xml file. Error: " << m_xmlDoc.ErrorDesc() << "\n";
		return false;
	}

	TiXmlElement *pRoot = m_xmlDoc.RootElement();
	TiXmlElement *pSceneRoot = nullptr;

	// Get current scene root
	for (TiXmlElement *e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		if (e->Value() == m_sceneID)
			pSceneRoot = e;
	TiXmlElement *pSubRoot = nullptr;

	// Get total page number of the scene
	for (TiXmlElement *e = pSceneRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		if (e->Value() == std::string("PAGE"))
			pSubRoot = e;
	{
		TiXmlElement *e = pSubRoot->FirstChildElement();
		e->Attribute("pageNumber", &m_max);
	}

	// Open text file
	for (TiXmlElement *e = pSceneRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		if (e->Value() == std::string("TEXT"))
			pSubRoot = e;
	{
		TiXmlElement *e = pSubRoot->FirstChildElement();
		std::string fileName = e->Attribute("filename");
		m_input.open(fileName.c_str());
		m_textLines = e->Attribute("lines");
	}

	// Load music
	for (TiXmlElement *e = pSceneRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		if (e->Value() == std::string("MUSIC"))
			pSubRoot = e;
	for (TiXmlElement *e = pSubRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		std::string fileName, id;
		int pages;
		fileName = e->Attribute("filename");
		id = e->Attribute("id");
		e->Attribute("pages", &pages);
		TheAudioManager::Instance()->load(fileName, id);
		m_music.push_back(std::pair<std::string, int>(id, pages));
	}

	// Get background queue
	for (TiXmlElement *e = pSceneRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		if (e->Value() == std::string("BACKGROUND"))
			pSubRoot = e;
	for (TiXmlElement *e = pSubRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		std::string objectID;
		int pages;
		objectID = e->Attribute("objectID");
		e->Attribute("pages", &pages);
		m_backgrounds.push_back(std::pair<std::string, int>(objectID, pages));
	}

	// Get figure queue
	for (TiXmlElement *e = pSceneRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		if (e->Value() == std::string("FIGURE"))
			pSubRoot = e;
	for (TiXmlElement *e = pSubRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		std::string objectID;
		int pages;
		objectID = e->Attribute("objectID");
		e->Attribute("pages", &pages);
		m_figures.push_back(std::pair<std::string, int>(objectID, pages));
	}

	// Get next scene ID
	for (TiXmlElement *e = pSceneRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		if (e->Value() == std::string("CHOICES"))
			pSubRoot = e;
	for (TiXmlElement *e = pSubRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		std::string nextSceneID;
		nextSceneID = e->Attribute("nextSceneID");
		m_nextSceneIDs.push_back(nextSceneID);
	}

	// Load objects
	for (TiXmlElement *e = pSceneRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		if (e->Value() == std::string("OBJECTS"))
			pSubRoot = e;
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

		GameObject *pGameObject = new SDLGameObject(new LoaderParams(x, y, width, height, textureID));
		m_objectsMap[objectID] = pGameObject;
	}
	m_objectsMap[std::string("null")] = nullptr;

	if (m_bIsLoaded)
	{
		SaveData sd = TheSaveManager::Instance()->getSaveData();
		m_count = sd.getCount();
		m_bgCounter = sd.getBgCounter();
		m_fgCounter = sd.getFgCounter();
		m_msCounter = sd.getMsCounter();
		m_bgTimer = sd.getBgTimer();
		m_fgTimer = sd.getFgTimer();
		m_msTimer = sd.getMsTimer();
	}
	else
	{
		// Get first background, character, music and text
		m_count = 0;
		m_bgCounter = m_fgCounter = m_msCounter = 0;
		m_bgTimer = m_backgrounds[m_bgCounter].second;
		m_fgTimer = m_figures[m_fgCounter].second;
		m_msTimer = m_music[m_fgCounter].second;
	}
	m_background = m_objectsMap[m_backgrounds[m_bgCounter].first];
	m_figure = m_objectsMap[m_figures[m_fgCounter].first];
	TheAudioManager::Instance()->play(m_music[m_msCounter].first);
	// Read text depend on current lines.
	for (int i = 0; i < m_textLines.at(m_count) - '0'; ++i)
	{
		std::getline(m_input, m_text, '\n');
		TheTextManager::Instance()->setContent(m_text, i);
	}

	m_bQuit = false;

	return true;
}

bool Scene::onExit(void)
{
	TheAudioManager::Instance()->stop();

	for (decltype(m_textButtons.size()) i = 0; i < m_textButtons.size(); ++i)
	{
		delete m_textButtons[i]; // Here we delete the textButtons we new before
		m_textButtons[i] = nullptr;
	}

	for (auto i = m_music.begin(); i != m_music.end(); ++i)
	{
		TheAudioManager::Instance()->clear((*i).first);
	}

	return true;
}

void Scene::getSaveInfo(std::string &sceneID, unsigned &count, unsigned &bgTimer, unsigned &fgTimer,
	unsigned &msTimer, unsigned &bgCounter, unsigned &fgCounter, unsigned &msCounter)
{
	sceneID = m_sceneID;
	count = m_count;
	bgTimer = m_bgTimer;
	fgTimer = m_fgTimer;
	msTimer = m_msTimer;
	bgCounter = m_bgCounter;
	fgCounter = m_fgCounter;
	msCounter = m_msCounter;
}