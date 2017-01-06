#include <iostream>
#include <vector>
#include "tinyxml.h"
#include "SDLGameObject.h"

class SceneParser
{
public:

	bool parseScene(const char* stateFile, std::string sceneID, std::vector<GameObject *> *pObjects);
	std::vector<std::string> *getText(void) { return &m_pText; }
	std::vector<std::string> *getBackground(void) { return &m_pBackground; }
	std::vector<std::string> *getFigure(void) { return &m_pFigures; }

private:

	void parseObjects(TiXmlElement *pStateRoot, std::vector<GameObject *> *pObjects);
	void parseText(TiXmlElement *pStateRoot, std::vector<std::string> *pText);
	void parseBackground(TiXmlElement *pStateRoot, std::vector<std::string> *pText);
	void parseFigures(TiXmlElement *pStateRoot, std::vector<std::string> *pFigures);

	std::vector<std::string> m_pText;
	std::vector<std::string> m_pBackground;
	std::vector<std::string> m_pFigures;
};