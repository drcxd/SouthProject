#ifndef __Scene__
#define __Scene__

#include <vector>
#include <map>
#include <fstream>
#include <utility>
#include <string>

#include "tinyxml.h"

#include "GameState.h"
#include "SDLGameObject.h"
#include "Text.h"
#include "TextButton.h"

class Scene : public GameState
{
public:

	Scene(std::string scene, bool load) : m_sceneID(scene), m_bIsLoaded(load)
	{
	}

	virtual void update(void);
	virtual void render(void);
	virtual bool onEnter(void);
	virtual bool onExit(void);
	virtual std::string getStateID() const { return m_sceneID; }
	bool *getQuitPointer(void) { return &m_bQuit; }
	void getSaveInfo(std::string &sceneID, unsigned &count, unsigned &bgTimer, unsigned &fgTimer,
		unsigned &msTimer, unsigned &bgCounter, unsigned &fgCounter, unsigned &msCounter);

private:

	bool m_bIsLoaded;

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
	int m_focused_point;

	bool m_bQuit;

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
