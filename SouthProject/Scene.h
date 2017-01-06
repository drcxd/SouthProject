#ifndef __Scene__
#define __Scene__

#include "GameState.h"
#include "SDLGameObject.h"
#include <vector>
#include "tinyxml.h"
#include <map>
#include <fstream>
#include "Text.h"
#include "TextButton.h"

class Scene : public GameState
{
public:

	Scene(std::string scene) : m_sceneID(scene)
	{
	}

	virtual void update(void);
	virtual void render(void);
	virtual bool onEnter(void);
	virtual bool onExit(void);
	virtual std::string getStateID() const { return m_sceneID; }
	bool *getQuitPointer(void) { return &m_bQuitPointer; }

private:

	int m_count;
	int m_max;
	const std::string m_sceneID;
	GameObject *m_background;
	GameObject *m_figure;
	std::string m_text;
	std::ifstream m_input;
	std::map<std::string, GameObject *> m_objectsMap;
	std::vector<TextButton *> m_textButtons;
	std::vector<std::string> m_nextSceneIDs;
	int m_focused_point;
	bool m_bQuitPointer;

	TiXmlDocument m_xmlDoc;
	// TiXmlElement *m_pRoot;
	std::vector<std::string> m_backgrounds;
	std::vector<std::string> m_figures;
};
#endif // !__Scene__
