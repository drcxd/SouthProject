#include <fstream>
#include <iostream>

#include "SaveManager.h"

SaveManager* SaveManager::s_pInstance = nullptr;

bool SaveManager::save(void)
{
	std::ofstream writer("save/save.dat");
	if (writer.is_open())
		writer << m_saveData.getSceneID() << " " << m_saveData.getCount() << " "
		<< m_saveData.getBgTimer() << " " << m_saveData.getBgCounter() << " " 
		<< m_saveData.getFgTimer() << " " << m_saveData.getFgCounter() << " " 
		<< m_saveData.getMsTimer() << " " << m_saveData.getMsCounter() << std::endl;
	else
	{
		std::cerr << "Failed when writing save file.\n";
		writer.close();
		return false;
	}
	writer.close();

	return true;
}

bool SaveManager::load(void)
{
	std::string sceneID;
	unsigned count, bgTimer, bgCounter, fgTimer, fgCounter, msTimer, msCounter;
	std::ifstream reader("save/save.dat");

	if (reader.is_open())
		reader >> sceneID >> count >> bgTimer >> bgCounter >> fgTimer >> fgCounter >> msTimer
		>> msCounter;
	else
	{
		std::cerr << "Failed when reading save file.\n";
		reader.close();
		return false;
	}

	m_saveData.setSceneID(sceneID);
	m_saveData.setCount(count);
	m_saveData.setBgTimer(bgTimer);
	m_saveData.setBgCounter(bgCounter);
	m_saveData.setFgTimer(fgTimer);
	m_saveData.setFgCounter(fgCounter);
	m_saveData.setMsTimer(msTimer);
	m_saveData.setMsCounter(msCounter);

	return true;
}
