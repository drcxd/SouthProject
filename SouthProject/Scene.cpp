#include "Scene.h"
#include "InputHandler.h"
#include "Constants.h"

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

	// Open text file
	TiXmlElement *pSubRoot = NULL;
	for (TiXmlElement *e = pSceneRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("TEXT"))
		{
			pSubRoot = e;
		}
	}
	for (TiXmlElement *e = pSubRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::string fileName = e->Attribute("filename");
		m_input.open(fileName.c_str());
	}

	m_max = 0;
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
		objectID = e->Attribute("objectID");
		m_backgrounds.push_back(objectID);
		m_max++;
	}

	// Get figure root
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
		objectID = e->Attribute("objectID");
		m_figures.push_back(objectID);
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

	// Get first background and character
	m_count = 0;
	m_background = m_objectsMap[m_backgrounds[m_count]];
	m_figure = m_objectsMap[m_figures[m_count]];
	std::getline(m_input, m_text, '\n');
	TheTextManager::Instance()->setContent(m_text);

	m_bQuitPointer = false;

	return true;
}

bool Scene::onExit(void)
{
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
			m_background = m_objectsMap[m_backgrounds[m_count]];
			m_figure = m_objectsMap[m_figures[m_count]];
			std::getline(m_input, m_text, '\n');
			TheTextManager::Instance()->setContent(m_text);
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
		if (m_focused_point > m_nextSceneIDs.size() - 1) // hardcoding, will change it later
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

