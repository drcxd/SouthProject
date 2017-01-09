#include "AudioManager.h"

AudioManager::~AudioManager()
{
	for (std::map<std::string, Mix_Music *>::iterator it = m_musicMap.begin(); it != m_musicMap.end(); it++)
		Mix_FreeMusic(it->second);
}

bool AudioManager::load(std::string fileName, std::string id)
{
	Mix_Music *pMusic = Mix_LoadMUS(fileName.c_str());
	if (pMusic == 0)
	{
		std::cerr << "Failed to load music file " << fileName << std::endl;
		std::cerr << "SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}
	else
	{
		m_musicMap[id] = pMusic;
		return true;
	}
}

void AudioManager::play(std::string id)
{
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(m_musicMap[id], -1);
}

void AudioManager::stop()
{
	Mix_HaltMusic();
}

AudioManager *AudioManager::s_pInstance = 0;