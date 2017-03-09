#ifndef __SaveData__
#define __SaveData__

#include <string>

class SaveData
{
public:
	SaveData() : m_sceneID("scene01"), m_bgTimer(0), m_bgCounter(0), m_fgTimer(0),
		m_fgCounter(0), m_msTimer(0), m_msCounter(0), m_count(0)
	{}

	SaveData(const std::string& sceneID, unsigned count, unsigned bgTimer, unsigned bgCounter,
		unsigned fgTimer, unsigned fgCounter, unsigned msTimer, unsigned msCounter) :
		m_sceneID(sceneID), m_bgTimer(bgTimer), m_bgCounter(bgCounter), 
		m_fgTimer(fgTimer), m_fgCounter(fgCounter), m_msTimer(msTimer), 
		m_msCounter(msCounter), m_count(count)
	{}

	void setCount(unsigned count) { m_count = count; }
	void setSceneID(const std::string &sceneID) { m_sceneID = sceneID; }
	void setBgTimer(unsigned bgTimer) { m_bgTimer = bgTimer; }
	void setBgCounter(unsigned bgCounter) { m_bgCounter = bgCounter; }
	void setFgTimer(unsigned fgTimer) { m_fgTimer = fgTimer; }
	void setFgCounter(unsigned fgCounter) { m_fgCounter = fgCounter; }
	void setMsTimer(unsigned msTimer) { m_msTimer = msTimer; }
	void setMsCounter(unsigned msCounter) { m_msCounter = msCounter; }

	unsigned getCount() const { return m_count; }
	std::string getSceneID() const { return m_sceneID; }
	unsigned getBgTimer() const { return m_bgTimer; }
	unsigned getBgCounter() const { return m_bgCounter; }
	unsigned getFgTimer() const { return m_fgTimer; }
	unsigned getFgCounter() const { return m_fgCounter; }
	unsigned getMsTimer() const { return m_msTimer; }
	unsigned getMsCounter() const { return m_msCounter; }


private:

	std::string m_sceneID;
	unsigned m_count;
	unsigned m_bgTimer;
	unsigned m_bgCounter;
	unsigned m_fgTimer;
	unsigned m_fgCounter;
	unsigned m_msTimer;
	unsigned m_msCounter;
};

#endif // !__SaveData__
