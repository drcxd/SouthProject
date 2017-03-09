#ifndef __SaveManager__
#define __SaveManager__

#include <string>

#include "SaveData.h"

class SaveManager
{
public:

	static SaveManager *Instance(void)
	{
		if (s_pInstance == nullptr)
			s_pInstance = new SaveManager();
		return s_pInstance;
	}

	bool save(void);
	bool load(void);
	SaveData &getSaveData(void) { return m_saveData; }

private:

	static SaveManager *s_pInstance;
	SaveManager(void) {}

	SaveData m_saveData;
};

typedef SaveManager TheSaveManager;
#endif