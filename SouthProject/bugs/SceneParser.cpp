#include "SceneParser.h"



	bool SceneParser::parseScene(const char* stateFile, std::string sceneID, std::vector<GameObject *> *pObjects)
	{
		TiXmlDocument xmlDoc;

		if (!xmlDoc.LoadFile(stateFile))
		{
			std::cout << "Failed when loading xml file. Error: " << xmlDoc.ErrorDesc() << "\n";
			return false;
		}

		TiXmlElement *pRoot = xmlDoc.RootElement();

		TiXmlElement *pStateRoot = NULL;

		for (TiXmlElement *e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			if (e->Value() == sceneID)
			{
				pStateRoot = e;
			}
		}

		TiXmlElement *pSubRoot = NULL;

		for (TiXmlElement *e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			if (e->Value() == std::string("OBJCETS"))
			{
				pSubRoot = e;
			}
		}

		parseObjects(pSubRoot, pObjects);

		for (TiXmlElement *e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			if (e->Value() == std::string("BACKGROUND"))
			{
				pSubRoot = e;
			}
		}

		parseBackground(pSubRoot, &m_pBackground);

		for (TiXmlElement *e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			if (e->Value() == std::string("TEXT"))
			{
				pSubRoot = e;
			}
		}

		parseText(pSubRoot, &m_pText);

		for (TiXmlElement *e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			if (e->Value() == std::string("FIGURE"))
			{
				pSubRoot = e;
			}
		}

		parseFigures(pStateRoot, &m_pFigures);

		return true;
	}