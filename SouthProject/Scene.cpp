#include "Scene.h"
#include "InputHandler.h"
#include "Constants.h"
#include "AudioManager.h"

#include <iostream>

bool Scene::onEnter(void)
{
	TiXmlDocument m_xmlDoc;

	if (!m_xmlDoc.LoadFile("scripts/test.xml"))
	{
		std::cout << "Failed when loading xml file. Error: " << m_xmlDoc.ErrorDesc() << "\n";
		return false;
	}

	TiXmlElement *pRoot = m_xmlDoc.RootElement();
	TiXmlElement *pSceneRoot = NULL;

	// Get current scene root
	for (TiXmlElement *e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == m_sceneID)
		{
			pSceneRoot = e;
		}
	}
	TiXmlElement *pSubRoot = NULL;

	// Get total page number of the scene
	for (TiXmlElement *e = pSceneRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		if (e->Value() == std::string("PAGE"))
			pSubRoot = e;
	{
		TiXmlElement *e = pSubRoot->FirstChildElement();
		e->Attribute("pageNumber", &m_max);
	}

	// Open text file
	for (TiXmlElement *e = pSceneRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("TEXT"))
		{
			pSubRoot = e;
		}
	}
	{
		TiXmlElement *e = pSubRoot->FirstChildElement();
		std::string fileName = e->Attribute("filename");
		m_input.open(fileName.c_str());
		m_textLines = e->Attribute("lines");
	}

	/*for (TiXmlElement *e = pSubRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::string fileName = e->Attribute("filename");
		m_input.open(fileName.c_str());
	}*/

	// Load music
	for (TiXmlElement *e = pSceneRoot->FirstChildElement(); e != 0; e = e->NextSiblingElement())
		if (e->Value() == std::string("MUSIC"))
			pSubRoot = e;
	for (TiXmlElement *e = pSubRoot->FirstChildElement(); e != 0; e = e->NextSiblingElement())
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
	for (TiXmlElement *e = pSceneRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("BACKGROUND"))
		{
			pSubRoot = e;
		}
	}
	for (TiXmlElement *e = pSubRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::string objectID;
		int pages;
		objectID = e->Attribute("objectID");
		e->Attribute("pages", &pages);
		m_backgrounds.push_back(std::pair<std::string, int>(objectID, pages));
	}

	// Get figure queue
	for (TiXmlElement *e = pSceneRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("FIGURE"))
		{
			pSubRoot = e;
		}
	}
	for (TiXmlElement *e = pSubRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::string objectID;
		int pages;
		objectID = e->Attribute("objectID");
		e->Attribute("pages", &pages);
		m_figures.push_back(std::pair<std::string, int>(objectID, pages));
	}

	// Get next scene ID
	for (TiXmlElement *e = pSceneRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("CHOICES"))
		{
			pSubRoot = e;
		}
	}
	for (TiXmlElement *e = pSubRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::string nextSceneID;
		nextSceneID = e->Attribute("nextSceneID");
		m_nextSceneIDs.push_back(nextSceneID);
	}

	// Load objects
	for (TiXmlElement *e = pSceneRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("OBJECTS"))
		{
			pSubRoot = e;
		}
	}
	for (TiXmlElement *e = pSubRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
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
	m_objectsMap[std::string("null")] = NULL;

	// Get first background, character, music and text
	m_count = 0;
	m_bgCounter = m_fgCounter = m_msCounter = 0;
	m_bgTimer = m_backgrounds[m_bgCounter].second;
	m_fgTimer = m_figures[m_fgCounter].second;
	m_msTimer = m_music[m_fgCounter].second;
	m_background = m_objectsMap[m_backgrounds[m_bgCounter].first];
	m_figure = m_objectsMap[m_figures[m_fgCounter].first];
	TheAudioManager::Instance()->play(m_music[m_msCounter].first);
	// Read text depend on current lines.
	for (unsigned i = 0; i < m_textLines.at(m_count) - '0'; i++)
	{
		std::getline(m_input, m_text, '\n');
		TheTextManager::Instance()->setContent(m_text, i);
	}

	m_bQuitPointer = false;

	return true;
}

bool Scene::onExit(void)
{
	TheAudioManager::Instance()->stop();
	for (std::vector<std::string>::size_type i = 0; i < m_textButtons.size(); i++)
	{
		delete m_textButtons[i];
		m_textButtons[i] = NULL;
	}
	return true;
}

void Scene::update()
{
	if (TheInputHandler::Instance()->isEnterPressed())
	{
		m_count++;
		if (m_count < m_max)
		{
			TheInputHandler::Instance()->setEnterFree();

			// Handle background timer and counter and change background if necessary
			m_bgTimer--;
			if (m_bgTimer == 0)
			{
				m_bgCounter++;
				if (m_bgCounter < m_backgrounds.size())
				{
					m_background = m_objectsMap[m_backgrounds[m_bgCounter].first];
					m_bgTimer = m_backgrounds[m_bgCounter].second;
				}
			}

			// Handle figure timer and counter and change figure if necessary
			m_fgTimer--;
			if (m_fgTimer == 0)
			{
				m_fgCounter++;
				if (m_fgCounter < m_figures.size())
				{
					m_figure = m_objectsMap[m_figures[m_fgCounter].first];
					m_fgTimer = m_figures[m_fgCounter].second;
				}
			}

			// Handle music timer and counter and change music if necessary
			m_msTimer--;
			if (m_msTimer == 0)
			{
				m_msCounter++;
				if (m_msCounter < m_music.size())
				{
					TheAudioManager::Instance()->stop();
					TheAudioManager::Instance()->play(m_music[m_msCounter].first);
					m_msTimer = m_music[m_msCounter].second;
				}
			}

			// Read text depend on current lines.
			for (unsigned i = 0; i < m_textLines.at(m_count) - '0'; i++)
			{
				std::getline(m_input, m_text, '\n');
				TheTextManager::Instance()->setContent(m_text, i);
			}
		}
		else if (m_count == m_max)
		{
			TheInputHandler::Instance()->setEnterFree();
			std::string tmpStr;
			for (std::vector<std::string>::size_type i = 0; i < m_nextSceneIDs.size(); i++)
			{
				std::getline(m_input, tmpStr, '\n');
				TextButton *pTextButton = new TextButton(TEXT_ROW_START, SCREEN_HEIGHT / 5 * 4 + i * TEXT_ROW_HEIGHT, 
					tmpStr, m_nextSceneIDs[i]);
				if (i == 0)
				{
					pTextButton->setFocused(true);
				}
				m_textButtons.push_back(pTextButton);
			}
			m_focused_point = 0;
		}
		else
		{
			m_count--;
		}
	}


	if (TheInputHandler::Instance()->isUpPressed())
	{
		TheInputHandler::Instance()->setUpFree();
		m_focused_point--;
		if (m_focused_point < 0)
		{
			m_focused_point++;
		}
		else
		{
			m_textButtons[m_focused_point + 1]->setFocused(false);
			m_textButtons[m_focused_point]->setFocused(true);
		}
	}

	if (TheInputHandler::Instance()->isDownPressed())
	{
		TheInputHandler::Instance()->setDownFree();
		m_focused_point++;
		if (m_focused_point > m_nextSceneIDs.size() - 1) 
		{
			m_focused_point--;
		}
		else
		{
			m_textButtons[m_focused_point - 1]->setFocused(false);
			m_textButtons[m_focused_point]->setFocused(true);
		}
	}

	if (m_count == m_max)
	{
		for (std::vector<TextButton *>::size_type i = 0; i < m_textButtons.size(); i++)
		{
			m_textButtons[i]->update(&m_bQuitPointer);
		}
	}

	if (m_bQuitPointer)
	{
		TheGame::Instance()->getStateMachine()->changeState(new Scene(m_nextSceneIDs[m_focused_point]));
	}
}

void Scene::render(void)
{
	if (m_background != NULL)
	{
		m_background->draw();
	}
	if (m_figure != NULL)
	{
		m_figure->draw();
	}
	if (m_count < m_max)
	{
		TheTextManager::Instance()->draw();
	}
	else if (m_count == m_max)
	{
		TheTextManager::Instance()->drawBackground();
		for (std::vector<TextButton *>::size_type i = 0; i < m_textButtons.size(); i++)
		{
			m_textButtons[i]->draw();
		}
	}
}

