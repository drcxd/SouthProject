#ifndef __Scene__
#define __Scene__

#include "GameState.h"
#include "SDLGameObject.h"
#include "Text.h"
#include "TextButton.h"

#include <vector>
#include <map>
#include <fstream>
#include <utility>
#include <string>

#include "tinyxml.h"


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

	int m_count; // Total pages count
	int m_max; // Varaiable holds total page number

	const std::string m_sceneID;

	GameObject *m_background;
	GameObject *m_figure;

	std::string m_text;
	std::string m_textLines;
	std::ifstream m_input;

	std::vector<TextButton *> m_textButtons;
	std::vector<std::string> m_nextSceneIDs;
	unsigned m_focused_point;

	bool m_bQuitPointer;

	TiXmlDocument m_xmlDoc;
	// TiXmlElement *m_pRoot;

	std::vector<std::pair<std::string, int>> m_backgrounds;
	unsigned m_bgTimer;
	unsigned m_bgCounter;
	std::vector<std::pair<std::string, int>> m_figures;
	unsigned m_fgTimer;
	unsigned m_fgCounter;
	std::vector<std::pair<std::string, int>> m_music;
	unsigned m_msTimer;
	unsigned m_msCounter;
	std::map<std::string, GameObject *> m_objectsMap;
};
#endif // !__Scene__
