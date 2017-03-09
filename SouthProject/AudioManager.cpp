#include "AudioManager.h"

AudioManager::~AudioManager()
{
	for (auto it = m_musicMap.begin(); it != m_musicMap.end(); ++it)
		Mix_FreeMusic(it->second);
}

bool AudioManager::load(const std::string fileName, const std::string id)
{
	Mix_Music *pMusic = Mix_LoadMUS(fileName.c_str());
	if (pMusic == nullptr)
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

void AudioManager::clear(const std::string id)
{
	m_musicMap.erase(id);

	return;
}

void AudioManager::play(const std::string id)
{
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(m_musicMap[id], -1);
}

void AudioManager::stop() const
{
	Mix_HaltMusic();
}

AudioManager *AudioManager::s_pInstance = 0;