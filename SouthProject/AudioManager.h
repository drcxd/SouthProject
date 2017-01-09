#ifndef __AudioManager__
#define __AudioManager__

#include <SDL_mixer.h>
#include <map>
#include <string>
#include <iostream>

class AudioManager
{
public:

	static AudioManager *Instance()
	{
		if (s_pInstance == 0)
			s_pInstance = new AudioManager();
		return s_pInstance;
	}

	bool load(std::string fileName, std::string id);
	void play(std::string id);
	void stop();

private:

	AudioManager() {}
	~AudioManager();

	static AudioManager *s_pInstance;

	std::map<std::string, Mix_Music *> m_musicMap;

};

typedef AudioManager TheAudioManager;
#endif

